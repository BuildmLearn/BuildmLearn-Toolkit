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

#include "miscellaneous/localization.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/application.h"

#include <QPointer>
#include <QTranslator>
#include <QDir>
#include <QFileInfoList>
#include <QLocale>


QPointer<Localization> Localization::s_instance;

Localization::Localization(QObject *parent)
  : QObject(parent) {
}

Localization::~Localization() {
  qDebug("Destroying Localization instance.");
}

Localization *Localization::instance() {
  if (s_instance.isNull()) {
    s_instance = new Localization(qApp);
  }

  return s_instance;
}

QString Localization::desiredLanguage() {
  return qApp->settings()->value(APP_CFG_GEN,
                                     "language",
                                     QLocale::system().name()).toString();
}

void Localization::load() {
  QTranslator *qt_translator = new QTranslator(qApp);
  QTranslator *app_translator = new QTranslator(qApp);
  QString desired_localization = desiredLanguage();

  if (app_translator->load(QString("buildmlearn-toolkit-%1.qm").arg(desired_localization),
                           APP_LANG_PATH,
                           "-")) {
    Application::installTranslator(app_translator);
    qDebug("Application localization '%s' loaded successfully.",
           qPrintable(desired_localization));
  }
  else {
    qWarning("Application localization '%s' was not loaded.",
             qPrintable(desired_localization));

    desired_localization = DEFAULT_LOCALE;
  }

  if (qt_translator->load(QString("qt-%1.qm").arg(desired_localization),
                          APP_LANG_PATH,
                          "-")) {
    Application::installTranslator(qt_translator);
    qDebug("Qt localization '%s' loaded successfully.",
           qPrintable(desired_localization));
  }
  else {
    qWarning("Qt localization '%s' was not loaded.",
             qPrintable(desired_localization));
  }

  m_loadedLanguage = desired_localization;
  QLocale::setDefault(QLocale(desired_localization));
}

QList<Language> Localization::installedLanguages() {
  QList<Language> languages;
  QDir file_dir(APP_LANG_PATH);
  QTranslator translator;

  // Iterate all found language files.
  foreach (const QFileInfo &file, file_dir.entryInfoList(QStringList() << "buildmlearn-toolkit-*.qm",
                                                         QDir::Files,
                                                         QDir::Name)) {
    if (translator.load(file.absoluteFilePath())) {
      Language new_language;
      new_language.m_name = translator.translate("QObject", "LANG_NAME");
      new_language.m_code = translator.translate("QObject", "LANG_ABBREV");
      new_language.m_author = translator.translate("QObject", "LANG_AUTHOR");
      new_language.m_email = translator.translate("QObject", "LANG_EMAIL");

      languages << new_language;
    }
  }
  return languages;
}

