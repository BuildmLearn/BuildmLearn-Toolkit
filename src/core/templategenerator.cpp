#include "core/templategenerator.h"

#include "definitions/definitions.h"
#include "core/templatecore.h"
#include "core/templatefactory.h"
#include "core/templateeditor.h"
#include "gui/formmain.h"
#include "miscellaneous/application.h"
#include "miscellaneous/iofactory.h"

#include <QMutex>
#include <QInputDialog>


TemplateGenerator::TemplateGenerator(QObject *parent) : QObject(parent) {
}

TemplateGenerator::~TemplateGenerator() {
}

void TemplateGenerator::generateMobileApplication(TemplateCore *core) { 
  if (qApp->closeLock()->tryLock()) {
    bool ok;
    QString input_file_name = QInputDialog::getText(qApp->mainForm(), tr("Specify application output file name"),
                                                    tr("Type here custom output application file name or leave the default value intact if you are satisfied with it."),
                                                    QLineEdit::Normal,
                                                    qApp->templateManager()->applicationFileName(core->editor()->projectName()), &ok);

    if (!ok || input_file_name.isEmpty()) {
      // User aborted the process or entered empty file name.
      //emit generationFinished(TemplateCore::Aborted);
      qApp->closeLock()->unlock();
      return;
    }

    // Append necessary suffix.
    if (!input_file_name.endsWith(".apk")) {
      input_file_name += ".apk";
    }

    connect(core, SIGNAL(generationProgress(int,QString)), this, SIGNAL(generationProgress(int,QString)));
    emit generationStarted();

    // TODO: upravit signaturu metody generationMobileApplication,
    // aby brala i ten vstupni nazev ciloveho apk souboru.

    QString output_file;
    TemplateCore::GenerationResult result = core->generateMobileApplication(input_file_name, output_file);

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

void TemplateGenerator::refreshWorkspace() {
  cleanWorkspace();
  QDir().mkpath(qApp->templateManager()->tempDirectory() + "/" + APP_LOW_NAME);
}
