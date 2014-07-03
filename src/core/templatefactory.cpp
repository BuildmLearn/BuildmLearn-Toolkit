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

#include "core/templatefactory.h"

#include "definitions/definitions.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/application.h"
#include "templates/quiz/quizentrypoint.h"
#include "templates/flashcard/flashcardentrypoint.h"
#include "templates/mlearning/basicmlearningentrypoint.h"

#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif


TemplateFactory::TemplateFactory(QObject *parent)
  : QObject(parent), m_availableTemplates(QHash<QString, TemplateEntryPoint*>()),
    m_activeEntryPoint(NULL), m_activeCore(NULL) {
  setupTemplates();
}

TemplateFactory::~TemplateFactory() {
  qDebug("Destroying TemplateFactory instance.");
}

QList<TemplateEntryPoint*> TemplateFactory::availableTemplates() {
  return m_availableTemplates.values();
}

QString TemplateFactory::tempDirectory() const {
#if QT_VERSION >= 0x050000
  return qApp->settings()->value(APP_CFG_TEMPLATES, "temp_directory",
                                 QStandardPaths::writableLocation(QStandardPaths::TempLocation)).toString();
#else
  return qApp->settings()->value(APP_CFG_TEMPLATES, "temp_directory",
                                 QDesktopServices::storageLocation(QDesktopServices::TempLocation)).toString();
#endif
}

void TemplateFactory::setTempDirectory(const QString &temp_directory) {
  qApp->settings()->setValue(APP_CFG_TEMPLATES, "temp_directory", temp_directory);
}

QString TemplateFactory::outputDirectory() const {
#if QT_VERSION >= 0x050000
  return qApp->settings()->value(APP_CFG_TEMPLATES, "output_directory",
                                 QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
#else
  return qApp->settings()->value(APP_CFG_TEMPLATES, "output_directory",
                                 QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
#endif
}

void TemplateFactory::setOutputDirectory(const QString &output_directory) {
  qApp->settings()->setValue(APP_CFG_TEMPLATES, "output_directory", output_directory);
}

QString TemplateFactory::applicationFileNamePattern() const {
  return qApp->settings()->value(APP_CFG_TEMPLATES, "application_file_name_pattern",
                                 "application-%1-%2-%3.apk").toString();
}

void TemplateFactory::setApplicationFileNamePattern(const QString &file_name_pattern) {
  qApp->settings()->setValue(APP_CFG_TEMPLATES, "application_file_name_pattern", file_name_pattern);
}

void TemplateFactory::clearEntryAndCore() {
  if (m_activeEntryPoint != NULL) {
    m_activeEntryPoint = NULL;
  }

  if (m_activeCore != NULL) {
    m_activeCore->deleteLater();
    m_activeCore = NULL;
  }
}

void TemplateFactory::startNewProject(TemplateEntryPoint *entry_point) {
  // Start new project with selected template entry point.
  clearEntryAndCore();

  m_activeEntryPoint = entry_point;
  m_activeCore = entry_point->createNewCore();

  emit newTemplateCoreCreated(m_activeCore);
}

void TemplateFactory::loadProject(const QString &bundle_file_name) {
  // TODO: Load project from XML bundle file.
  // Detect which template is it, then start new project with that template
  // and fill data in.
}

void TemplateFactory::setupTemplates() {
  // TODO: Fill in needed template entry points.
  TemplateEntryPoint *flashcard_entry = new FlashCardEntryPoint(this);
  m_availableTemplates.insert(flashcard_entry->typeIndentifier(), flashcard_entry);

  TemplateEntryPoint *info_entry = new BasicmLearningEntryPoint(this);
  m_availableTemplates.insert(info_entry->typeIndentifier(), info_entry);

  TemplateEntryPoint *quiz_entry = new QuizEntryPoint(this);
  m_availableTemplates.insert(quiz_entry->typeIndentifier(), quiz_entry);
}
