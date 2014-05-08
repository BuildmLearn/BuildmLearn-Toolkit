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

#include "miscellaneous/systemfactory.h"

#include "definitions/definitions.h"
#include "network-web/networkfactory.h"
#include "application.h"

#if defined(Q_OS_WIN)
#include <QSettings>
#endif

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>


SystemFactory::SystemFactory() {
}

SystemFactory::~SystemFactory() {
}

QPair<UpdateInfo, QNetworkReply::NetworkError> SystemFactory::checkForUpdates() {
  QPair<UpdateInfo, QNetworkReply::NetworkError> result;
  QByteArray releases_xml;

  result.second = NetworkFactory::downloadFile(RELEASES_LIST,
                                               5000,
                                               releases_xml);

  if (result.second == QNetworkReply::NoError) {
    result.first = parseUpdatesFile(releases_xml);
  }

  return result;
}

UpdateInfo SystemFactory::parseUpdatesFile(const QByteArray &updates_file) {
  UpdateInfo update;
  QDomDocument document; document.setContent(updates_file, false);
  QDomNodeList releases = document.elementsByTagName("release");

  if (releases.size() == 1) {
    QDomElement rel_elem = releases.at(0).toElement();
    QString type = rel_elem.attributes().namedItem("type").toAttr().value();

    update.m_availableVersion = rel_elem.attributes().namedItem("version").toAttr().value();
    update.m_changes = rel_elem.namedItem("changes").toElement().text();

    QDomNodeList urls = rel_elem.elementsByTagName("url");

    for (int j = 0; j < urls.size(); j++) {
      UpdateUrl url;
      QDomElement url_elem = urls.at(j).toElement();

      url.m_fileUrl = url_elem.text();
      url.m_os = url_elem.attributes().namedItem("os").toAttr().value();
      url.m_platform = url_elem.attributes().namedItem("platform").toAttr().value();

      update.m_urls.insert(url.m_os,
                           url);
    }

    if (type == "maintenance") {
      update.m_type = UpdateInfo::Maintenance;
    }
    else {
      update.m_type = UpdateInfo::Evolution;
    }
  }
  else {
    update.m_availableVersion = QString();
  }


  return update;
}
