#include "core/templategenerator.h"

#include "core/templatecore.h"
#include "miscellaneous/application.h"

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

    disconnect(core, SIGNAL(generationProgress(int,QString)), this, SLOT(generateMobileApplication(TemplateCore*)));

    if (result == TemplateCore::Success) {
      emit generationFinished(result, output_file);
    }
    else {
      emit generationFinished(result);
    }

    qApp->closeLock()->unlock();
  }
}
