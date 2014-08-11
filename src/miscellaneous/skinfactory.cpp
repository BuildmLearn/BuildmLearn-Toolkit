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

#include "miscellaneous/skinfactory.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/application.h"

#include <QDir>
#include <QStyleFactory>
#include <QDomDocument>
#include <QDomElement>


SkinFactory::SkinFactory(QObject *parent) : QObject(parent) {
}

SkinFactory::~SkinFactory() {
  qDebug("Destroying SkinFactory instance.");
}

void SkinFactory::loadCurrentSkin() {
  QString skin_name_from_settings = selectedSkinName();
  bool skin_parsed;
  Skin skin_data = skinInfo(skin_name_from_settings, &skin_parsed);

  if (skin_parsed) {
    loadSkinFromData(skin_data);

    // Set this 'Skin' object as active one.
    m_currentSkin = skin_data;

    qDebug("Skin '%s' loaded.", qPrintable(skin_name_from_settings));
  }
  else {
#if defined(DEBUG)
      qCritical("Skin '%s' not loaded because its data are corrupted. No skin is loaded now!",
                qPrintable(skin_name_from_settings));
#else
      qFatal("Skin '%s' not loaded because its data are corrupted. No skin is loaded now!",
             qPrintable(skin_name_from_settings));
#endif
  }
}

bool SkinFactory::loadSkinFromData(const Skin &skin) {
  qDebug("Loading skin '%s'.", qPrintable(skin.m_baseName));

  // Here we use "/" instead of QDir::separator() because CSS2.1 url field
  // accepts '/' as path elements separator.
  //
  // "##" is placeholder for the actual path to skin file. This is needed for using
  // images within the QSS file.
  // So if one uses "##/images/border.png" in QSS then it is
  // replaced by fully absolute path and target file can
  // be safely loaded.
  QString raw_data = skin.m_rawData;

  if (!raw_data.isEmpty()) {
    QString parsed_data = raw_data.replace("##",
                                           APP_SKIN_PATH + '/' +
                                           skin.m_baseFolder);
    qApp->setStyleSheet(parsed_data);
  }

  // Iterate supported styles and load one.
  foreach (const QString &style, skin.m_stylesNames) {
    if (qApp->setStyle(style) != 0) {
      qDebug("Style '%s' loaded.", qPrintable(style));
      break;
    }
  }

  return true;
}


void SkinFactory::setCurrentSkinName(const QString &skin_name) {
  qApp->settings()->setValue(APP_CFG_GUI, "skin", skin_name);
}

QString SkinFactory::selectedSkinName() {
  return qApp->settings()->value(APP_CFG_GUI,
                                 "skin",
                                 APP_SKIN_DEFAULT).toString();
}

Skin SkinFactory::skinInfo(const QString &skin_name, bool *ok) {
  Skin skin;
  QString styles;
  QFile skin_file(APP_SKIN_PATH + QDir::separator() + skin_name);
  QDomDocument dokument;

  if (!skin_file.open(QIODevice::Text | QIODevice::ReadOnly) || !dokument.setContent(&skin_file, true)) {
    if (ok) {
      *ok = false;
    }

    return skin;
  }

  QDomNode skin_node = dokument.namedItem("skin");

  // Obtain visible skin name.
  skin.m_visibleName = skin_node.namedItem("name").toElement().text();

  // Obtain skin raw data.
  skin.m_rawData = skin_node.namedItem("data").toElement().text();
  skin.m_rawData = QByteArray::fromBase64(skin.m_rawData.toLocal8Bit());

  // Obtain style name.
  styles = skin_node.namedItem("style").toElement().text();
  skin.m_stylesNames = styles.split(',', QString::SkipEmptyParts);

  // Obtain author.
  skin.m_author = skin_node.namedItem("author").namedItem("name").toElement().text();

  // Obtain email.
  skin.m_email = skin_node.namedItem("author").namedItem("email").toElement().text();

  // Obtain version.
  skin.m_version = skin_node.attributes().namedItem("version").toAttr().value();

  // Obtain other information.
  skin.m_baseName = QString(skin_name).replace(QDir::separator(), '/');
  skin.m_baseFolder = skin.m_baseName.split('/', QString::SkipEmptyParts).at(0);

  // Obtain simulator image.
  QString simulator_image = skin_node.namedItem("simulator").
                            namedItem("main").toElement().text();

  skin.m_simulatorBackgroundMain = APP_SKIN_PATH + '/' + skin.m_baseFolder + '/' + simulator_image;
  skin.m_simulatorBackgroundMain = skin.m_simulatorBackgroundMain.replace('\\', '/');

  skin.m_simulatorStyle = skin_node.namedItem("simulator").namedItem("style").toElement().text();
  skin.m_simulatorStyle = QByteArray::fromBase64(skin.m_simulatorStyle.toLocal8Bit());

  // Free resources.
  skin_file.close();
  skin_file.deleteLater();

  if (ok) {
    *ok = !skin.m_author.isEmpty() && !skin.m_version.isEmpty() &&
          !skin.m_baseName.isEmpty() && !skin.m_email.isEmpty();
  }

  return skin;
}

QList<Skin> SkinFactory::installedSkins() {
  QList<Skin> skins;
  bool skin_load_ok;
  QStringList skin_directories = QDir(APP_SKIN_PATH).entryList(QDir::Dirs |
                                                               QDir::NoDotAndDotDot |
                                                               QDir::NoSymLinks |
                                                               QDir::Readable);

  foreach (const QString &base_directory, skin_directories) {
    // Check skins installed in this base directory.
    QStringList skin_files = QDir(APP_SKIN_PATH + QDir::separator() + base_directory).entryList(QStringList() << "*.xml",
                                                                                                QDir::Files | QDir::Readable | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    foreach (const QString &skin_file, skin_files) {
      // Check if skin file is valid and add it if it is valid.
      Skin skin_info = skinInfo(base_directory + QDir::separator() + skin_file,
                                &skin_load_ok);

      if (skin_load_ok) {
        skins.append(skin_info);
      }
    }
  }

  return skins;
}
