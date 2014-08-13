/*
  Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the BuildmLearn nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "templates/quiz/quizcore.h"

#include "templates/quiz/quizeditor.h"
#include "templates/quiz/quizsimulator.h"
#include "miscellaneous/application.h"
#include "miscellaneous/iofactory.h"
#include "core/templatefactory.h"
#include "core/templateentrypoint.h"
#include "core/templategenerator.h"
#include "definitions/definitions.h"

#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QProcess>


QuizCore::QuizCore(TemplateEntryPoint *entry_point, QObject *parent)
  : TemplateCore(entry_point, parent) {
  m_editor = new QuizEditor(this);
  m_simulator = new QuizSimulator(this);
}

QuizCore::~QuizCore() {
  qDebug("Destroying QuizCore instance.");
}

TemplateCore::GenerationResult QuizCore::generateMobileApplication(const QString &input_apk_file, QString &output_file) {
  emit generationProgress(5, tr("Preparing workspace..."));

  qApp->templateManager()->generator()->cleanWorkspace();

  emit generationProgress(10, tr("Extracting raw data from editor..."));

  // We need data which will be imported into apk/zip file.
  QString quiz_data = editor()->generateBundleData();

  if (quiz_data.isEmpty()) {
    // No date received, this is big problem.
    return BundleProblem;
  }

  QString temp_folder = qApp->templateManager()->tempDirectory();
  QDir temp_directory(temp_folder);
  QString base_folder = temp_folder + "/" + APP_LOW_NAME;
  QDir base_directory(base_folder);

  // Preparation of target bundle file
  emit generationProgress(20, tr("Creating base temporary folder..."));

  temp_directory.mkdir(APP_LOW_NAME);
  base_directory.mkdir("assets");

  QFile index_file(base_folder + "/assets/quiz_content.xml");
  index_file.open(QIODevice::WriteOnly | QIODevice::Text);

  emit generationProgress(30, tr("Writting quiz data into file..."));

  QTextStream out(&index_file);
  out << quiz_data;

  out.flush();
  index_file.close();

  emit generationProgress(40, tr("Copying template apk file..."));

  // Copying of target apk file.
  QString new_apk_name = input_apk_file;
  if (!QFile::copy(APP_TEMPLATES_PATH + "/" + entryPoint()->baseFolder() + "/" + entryPoint()->mobileApplicationApkFile(),
                   base_folder + "/" + new_apk_name)) {
    qApp->templateManager()->generator()->cleanWorkspace();
    return CopyProblem;
  }

  emit generationProgress(60, tr("Inserting data into apk file..."));

  // Inserting bundle file into apk file.
  QProcess zip;

  zip.setWorkingDirectory(base_folder);
  zip.start(qApp->zipUtilityPath(), QStringList() << "-m" << "-r" << new_apk_name << "assets");
  zip.waitForFinished();

  if (zip.exitCode() != EXIT_STATUS_ZIP_NORMAL) {
    // Error during inserting quiz data via zip.
    qApp->templateManager()->generator()->cleanWorkspace();
    return ZipProblem;
  }

  emit generationProgress(70, tr("Signing apk file..."));

  // Signing and renaming target file.
  QString pem_certificate = QDir::toNativeSeparators(APP_CERT_PATH + "/" + CERTIFICATE_PATH);
  QString pk_certificate = QDir::toNativeSeparators(APP_CERT_PATH + "/" + KEY_PATH);
  QProcess signapk;

  signapk.setWorkingDirectory(base_folder);
  signapk.start(qApp->javaInterpreterPath(), QStringList() << "-jar" << qApp->signApkUtlityPath() <<
                pem_certificate << pk_certificate << new_apk_name <<
                QDir::toNativeSeparators(new_apk_name + ".new"));
  signapk.waitForFinished();

  if (signapk.exitCode() != EXIT_STATUS_SIGNAPK_WORKING) {
    qApp->templateManager()->generator()->cleanWorkspace();
    return SignApkProblem;
  }

  emit generationProgress(90, tr("Copying final apk file to output directory..."));

  // Now, our file is created. We need to move it to target directory.
  if (!IOFactory::copyFile(base_folder + "/" + new_apk_name + ".new",
                           qApp->templateManager()->outputDirectory() + "/" + new_apk_name)) {
    qApp->templateManager()->generator()->cleanWorkspace();
    return CopyProblem;
  }

  output_file = QDir(qApp->templateManager()->outputDirectory()).filePath(new_apk_name);

  // Removing temporary files and exit.
  qApp->templateManager()->generator()->cleanWorkspace();
  return Success;
}

QuizEditor *QuizCore::quizEditor() {
  return static_cast<QuizEditor*>(m_editor);
}

QuizSimulator *QuizCore::quizSimulator() {
  return static_cast<QuizSimulator*>(m_simulator);
}
