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

#include "miscellaneous/settings.h"

#include "definitions/definitions.h"
#include "miscellaneous/application.h"

#include <QDebug>
#include <QDir>


Settings::Settings(const QString &file_name, Format format,
                   const Type &status, QObject *parent)
  : QSettings(file_name, format, parent), m_initializationStatus(status) {
}

Settings::~Settings() {
  checkSettings();
  qDebug("Deleting Settings instance.");
}

QSettings::Status Settings::checkSettings() {
  qDebug("Syncing settings.");

  sync();
  return status();
}

Settings* Settings::setupSettings(QObject *parent) {
  Settings *new_settings;

  // If settings file exists in executable file working directory
  // (in subdirectory APP_CFG_PATH), then use it (portable settings).
  // Otherwise use settings file stored in homePath();
  QString relative_path = QDir::separator() + QString(APP_CFG_PATH) +
                          QDir::separator() + QString(APP_CFG_FILE);

  QString app_path = qApp->applicationDirPath();
  QString app_path_file = app_path + relative_path;

  // Check if portable settings are available.
  if (QFile(app_path_file).exists()) {
    // Portable settings are available, use them.
    new_settings = new Settings(app_path_file, QSettings::IniFormat,
                                Settings::Portable, parent);

    qDebug("Initializing settings in '%s' (portable way).",
           qPrintable(QDir::toNativeSeparators(app_path_file)));
  }
  else {
    // Portable settings are NOT available, store them in
    // user's home directory.
    QString home_path = QDir::homePath() + QDir::separator() +
                        QString(APP_LOW_H_NAME);
    QString home_path_file = home_path + relative_path;

    new_settings = new Settings(home_path_file, QSettings::IniFormat,
                                Settings::NonPortable, parent);

    qDebug("Initializing settings in '%s' (non-portable way).",
           qPrintable(QDir::toNativeSeparators(home_path_file)));
  }

  return new_settings;
}
