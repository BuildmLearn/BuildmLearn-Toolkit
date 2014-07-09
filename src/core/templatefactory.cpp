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
#include "core/templategenerator.h"
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

#include <QDateTime>


TemplateFactory::TemplateFactory(QObject *parent)
  : QObject(parent), m_availableTemplates(QHash<QString, TemplateEntryPoint*>()),
    m_activeEntryPoint(NULL), m_activeCore(NULL),
    m_generator(new TemplateGenerator(this)) {
  setupTemplates();
}

TemplateFactory::~TemplateFactory() {
  qDebug("Destroying TemplateFactory instance.");
}

QList<TemplateEntryPoint*> TemplateFactory::availableTemplates() {
  QList<TemplateEntryPoint*> entries;

  foreach (TemplateEntryPoint *entry, m_availableTemplates.values()) {
    for (int i = 0; i <= entries.size(); i++) {
      if (i == entries.size()) {
        entries.append(entry);
        break;
      }
      else if (entry->humanName() < entries.at(i)->humanName()) {
        entries.insert(i, entry);
        break;
      }
    }
  }

  return entries;
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

QString TemplateFactory::applicationFileName(const QString &project_name) {
  if (activeEntryPoint() != NULL) {
    return applicationFileNamePattern().arg(activeEntryPoint()->name(),
                                            project_name,
                                            QDateTime::currentDateTime().toString(""));
  }
  else {
    return QString();
  }
}

QDomDocument TemplateFactory::generateBundleHeader(const QString &template_type, const QString &author_name, const QString &author_email, const QString &project_title, const QString &project_description, const QString &template_version) {
  QDomDocument xml_bundle;
  QDomElement root_element = xml_bundle.createElement("buildmlearn_application");
  QDomElement author_element = xml_bundle.createElement("author");
  QDomElement name_element = xml_bundle.createElement("name");
  QDomElement email_element = xml_bundle.createElement("email");
  QDomElement title_element = xml_bundle.createElement("title");
  QDomElement description_element = xml_bundle.createElement("description");
  QDomElement version_element = xml_bundle.createElement("version");
  QDomElement data_element = xml_bundle.createElement("data");


  root_element.setAttribute("type", template_type);
  name_element.appendChild(xml_bundle.createTextNode(author_name));
  email_element.appendChild(xml_bundle.createTextNode(author_email));
  title_element.appendChild(xml_bundle.createTextNode(project_title));
  description_element.appendChild(xml_bundle.createTextNode(project_description));
  version_element.appendChild(xml_bundle.createTextNode(template_version));

  author_element.appendChild(name_element);
  author_element.appendChild(email_element);

  root_element.appendChild(author_element);
  root_element.appendChild(title_element);
  root_element.appendChild(description_element);
  root_element.appendChild(version_element);
  root_element.appendChild(data_element);

  xml_bundle.appendChild(root_element);

  return xml_bundle;
}

bool TemplateFactory::entryPointIsLessThan(TemplateEntryPoint *s1, TemplateEntryPoint &s2) {
  return s1->humanName() < s2.humanName();
}

void TemplateFactory::quit() {
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

TemplateGenerator *TemplateFactory::generator() const {
  return m_generator;
}
