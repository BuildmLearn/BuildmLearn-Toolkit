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

#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H

#include <QMetaType>
#include <QHash>
#include <QPair>
#include <QNetworkReply>


class UpdateUrl {
  public:
    QString m_fileUrl;
    QString m_platform;
    QString m_os;
};

class UpdateInfo {
  public:
    enum UpdateType {
      // Corresponding enum to "maintenace" from UPDATES file.
      Maintenance,
      // Corresponding enum to "evolution" from UPDATES file.
      Evolution
    };

    explicit UpdateInfo() {
      m_availableVersion = m_changes = "";
    }

    QString m_availableVersion;
    QString m_changes;
    UpdateType m_type;
    QHash<QString, UpdateUrl> m_urls;
};

Q_DECLARE_METATYPE(UpdateInfo)

class SystemFactory {
  public:
    virtual ~SystemFactory();

    // Performs parsing of downloaded file with list of updates.
    static UpdateInfo parseUpdatesFile(const QByteArray &updates_file);

    // Tries to download list with new updates.
    static QPair<UpdateInfo, QNetworkReply::NetworkError> checkForUpdates();

  private:
    explicit SystemFactory();
};

#endif // SYSTEMFACTORY_H
