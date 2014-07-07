#include "core/templategenerator.h"

#include "core/templatecore.h"
#include "miscellaneous/application.h"

#include <QMutex>


TemplateGenerator::TemplateGenerator(QObject *parent) : QObject(parent) {
}

TemplateGenerator::~TemplateGenerator() {
}

bool TemplateGenerator::generateMobileApplication(TemplateCore *core) {
  if (qApp->closeLock()->tryLock()) {
    connect(core, SIGNAL(generationProgress(int,QString)), this, SIGNAL(generationProgress(int,QString)));
    emit generationStarted();
      TemplateCore::GenerationResult result = core->generateMobileApplication();

    disconnect(core, SIGNAL(generationProgress(int,QString)), this, SLOT(generateMobileApplication(TemplateCore*)));

    if (result == TemplateCore::Success) {
      emit generationFinished(0, tr("success"));
    }
    else {
      emit generationFinished(1, tr("success"));
    }

    qApp->closeLock()->unlock();

    return result;
  }
  else {
    return false;
  }
}
