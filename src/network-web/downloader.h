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


#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

#include <QNetworkReply>
#include <QSslError>

#include "definitions/definitions.h"


class SilentNetworkAccessManager;
class QTimer;

/// \brief Simple file downloader with progress reporting.
class Downloader : public QObject {
    Q_OBJECT

  public:
    /// \brief Constructor.
    /// \param parent Parent to this instance.
    explicit Downloader(QObject *parent = 0);
    virtual ~Downloader();

  public slots:
    /// \brief Performs asynchronous download of given file. Redirections are handled.
    /// \param url URL of file to be downloaded.
    /// \param protected_contents Are contents of URL protected?
    /// \param username Username if contents are protected.
    /// \param password Password if contents are protected.
    void downloadFile(const QString &url,
                      bool protected_contents = false,
                      const QString &username = QString(),
                      const QString &password = QString());

    /// \brief Uploads given bundle_data to store server via HTTP POST.
    /// \param url URL to store server
    /// \param bundle_data
    void uploadBundleFile(QString url, const QString &bundle_data,
                          const QString &key, const QString &author_name,
                          const QString &author_email, const QString &application_name,
                          const QString &application_icon);

  signals:
    /// \brief Emitted when new progress is known.
    /// \param bytes_received Number of bytes received.
    /// \param bytes_total Number of bytes total.
    void progress(qint64 bytes_received, qint64 bytes_total);

    /// \brief Emitted if file download or upload completes (un)successfully.
    /// \param status Status of file download/upload.
    /// \param contents QByteArray containing downloaded file (if any) or post reply.
    void completed(QNetworkReply::NetworkError status, QByteArray contents = QByteArray());

  private slots:
    // Called when current reply is processed.
    void finished(QNetworkReply *reply);

    // Called when progress of downloaded file changes.
    void progressInternal(qint64 bytes_received, qint64 bytes_total);

    // Called when current operation times out.
    void timeout();

  private:
    // Issues new network requests.
    void runGetRequest(const QNetworkRequest &request);
    void runPostRequest(const QNetworkRequest &request, const QByteArray &data);

  private:
    QNetworkReply *m_activeReply;
    SilentNetworkAccessManager *m_downloadManager;
    QTimer *m_timer;
};

#endif // DOWNLOADER_H
