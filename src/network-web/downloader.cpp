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


#include "network-web/downloader.h"

#include "network-web/silentnetworkaccessmanager.h"

#include <QTimer>
#include <QHttpMultiPart>


Downloader::Downloader(QObject *parent)
  : QObject(parent),
    m_activeReply(NULL),
    m_downloadManager(new SilentNetworkAccessManager(this)),
    m_timer(new QTimer(this)) {

  m_timer->setInterval(2000);
  m_timer->setSingleShot(true);

  connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
  connect(m_downloadManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

Downloader::~Downloader() {
  m_downloadManager->deleteLater();
}

void Downloader::downloadFile(const QString &url, bool protected_contents,
                              const QString &username, const QString &password) {
  QNetworkRequest request;
  QObject originatingObject;

  // Set credential information as originating object.
  originatingObject.setProperty("protected", protected_contents);
  originatingObject.setProperty("username", username);
  originatingObject.setProperty("password", password);
  request.setOriginatingObject(&originatingObject);

  // Set url for this reques.
  request.setUrl(url);

  runGetRequest(request);
}

void Downloader::uploadBundleFile(QString url, const QString &bundle_data,
                                  const QString &key, const QString &author_name,
                                  const QString &author_email, const QString &application_name) {
  QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);

  QHttpPart key_part;
  key_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"key\""));
  key_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
  key_part.setBody(key.toUtf8());

  QHttpPart author_name_part;
  author_name_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"author_name\""));
  author_name_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
  author_name_part.setBody(author_name.toUtf8());

  QHttpPart author_email_part;
  author_email_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"author_email\""));
  author_email_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
  author_email_part.setBody(author_email.toUtf8());

  QHttpPart application_name_part;
  application_name_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"application_name\""));
  application_name_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
  application_name_part.setBody(application_name.toUtf8());

  QHttpPart file_part;
  file_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\""));
  file_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/xml"));
  file_part.setBody(bundle_data.toUtf8());

  multi_part->append(key_part);
  multi_part->append(author_name_part);
  multi_part->append(author_email_part);
  multi_part->append(application_name_part);
  multi_part->append(file_part);

  QNetworkRequest request;

  request.setUrl(url);
  runPostRequest(request, multi_part);
}

void Downloader::finished(QNetworkReply *reply) {
  m_timer->stop();

  // In this phase, some part of downloading process is completed.
  QUrl redirection_url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

  if (redirection_url.isValid()) {
    // Communication indicates that HTTP redirection is needed.
    // Setup redirection URL and download again.
    QNetworkRequest request = reply->request();
    request.setUrl(redirection_url);

    m_activeReply->deleteLater();
    m_activeReply = NULL;

    runGetRequest(request);
  }
  else {
    // No redirection is indicated. Final file is obtained
    // in our "reply" object.

    // Read the data into output buffer.
    QByteArray output = reply->readAll();
    QNetworkReply::NetworkError reply_error = reply->error();

    m_activeReply->deleteLater();
    m_activeReply = NULL;

    emit completed(reply_error, output);
  }
}

void Downloader::progressInternal(qint64 bytes_received, qint64 bytes_total) {
  if (m_timer->interval() > 0) {
    m_timer->start();
  }

  emit progress(bytes_received, bytes_total);
}

void Downloader::timeout() {
  if (m_activeReply != NULL) {
    m_activeReply->abort();
  }
}

void Downloader::runGetRequest(const QNetworkRequest &request) {
  m_timer->start();
  m_activeReply = m_downloadManager->get(request);

  connect(m_activeReply, SIGNAL(downloadProgress(qint64,qint64)),
          this, SLOT(progressInternal(qint64,qint64)));
}

void Downloader::runPostRequest(const QNetworkRequest &request, QHttpMultiPart *multi_part) {
  m_timer->start();
  m_activeReply = m_downloadManager->post(request, multi_part);
  multi_part->setParent(m_activeReply);

  connect(m_activeReply, SIGNAL(uploadProgress(qint64,qint64)),
          this, SLOT(progressInternal(qint64,qint64)));
}


