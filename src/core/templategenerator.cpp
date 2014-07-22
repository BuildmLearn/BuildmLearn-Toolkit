#include "core/templategenerator.h"

#include "definitions/definitions.h"
#include "core/templatecore.h"
#include "core/templatefactory.h"
#include "core/templateeditor.h"
#include "miscellaneous/application.h"
#include "miscellaneous/iofactory.h"

#include <QMutex>


TemplateGenerator::TemplateGenerator(QObject *parent) : QObject(parent) {
}

TemplateGenerator::~TemplateGenerator() {
}

void TemplateGenerator::generateMobileApplication(TemplateCore *core) { 
  if (qApp->closeLock()->tryLock()) {
    connect(core, SIGNAL(generationProgress(int,QString)), this, SIGNAL(generationProgress(int,QString)));

    emit generationStarted();

    QString output_file;    
    TemplateCore::GenerationResult result = core->generateMobileApplication(output_file);

    disconnect(core, SIGNAL(generationProgress(int,QString)), this, SIGNAL(generationProgress(int,QString)));

    if (result == TemplateCore::Success) {
      emit generationFinished(result, output_file);
    }
    else {
      emit generationFinished(result);
    }

    qApp->closeLock()->unlock();
  }
  else {
    qApp->trayIcon()->showMessage(tr("Cannot generate application"),
                                  tr("Master generation lock is locked, try to\ngenerate application later."),
                                  QSystemTrayIcon::Warning);
  }
}

void TemplateGenerator::cleanWorkspace() {
  IOFactory::removeDirectory(qApp->templateManager()->tempDirectory() + "/" + APP_LOW_NAME);
}
