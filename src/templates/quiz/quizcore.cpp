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
#include "core/templatefactory.h"
#include "core/templateentrypoint.h"

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

TemplateCore::GenerationResult QuizCore::generateMobileApplication() {
  emit generationProgress(10, tr("Extracting raw data from editor..."));

  // We need data which will be imported into apk/zip file.
  QString quiz_data = editor()->generateBundleData();

  if (quiz_data.isEmpty()) {
    // No date received, this is big problem.
    //return BundleProblem;
  }

  QString temp_folder = qApp->templateManager()->tempDirectory();
  QDir temp_directory(temp_folder);

  // Preparation of target bundle file
  emit generationProgress(20, tr("Creating base temporary folder..."));

  temp_directory.mkdir("assets");

  QFile index_file(temp_folder + "/assets/quiz_content.xml");
  index_file.open(QIODevice::WriteOnly | QIODevice::Text);

  emit generationProgress(30, tr("Writting quiz data into file..."));

  QTextStream out(&index_file);
  out << quiz_data;

  out.flush();
  index_file.close();

  QString new_apk_name = qApp->templateManager()->applicationFileNamePattern().arg(entryPoint()->name(),
                                                                                   quizEditor()->m_ui->m_txtName->lineEdit()->text(),
                                                                                   QDateTime::currentDateTime().toString(""));

  // Copying of target apk file.
  QFile::copy(entryPoint()->mobileApplicationApkFile(),
              temp_folder + "/" + new_apk_name);

  // Inserting bundle file into apk file.
  QProcess zip;

  zip.setWorkingDirectory(temp_folder);
  zip.start(qApp->zipUtilityPath(), QStringList() << "-m" << "-r" << new_apk_name << "assets");
  zip.waitForFinished();

  int zip_out = zip.exitCode();

  // Signing and renaming target file.

  // Removing temporary files.

  return Success;
}

void QuizCore::launch() {
  quizEditor()->launch();
  quizSimulator()->launch();
}

QuizEditor *QuizCore::quizEditor() {
  return static_cast<QuizEditor*>(m_editor);
}

QuizSimulator *QuizCore::quizSimulator() {
  return static_cast<QuizSimulator*>(m_simulator);
}
