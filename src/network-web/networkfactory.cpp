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


#include "network-web/networkfactory.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "network-web/silentnetworkaccessmanager.h"

#include <QEventLoop>
#include <QTimer>
#include <QIcon>
#include <QPixmap>
#include <QTextDocument>


NetworkFactory::NetworkFactory() {
}

QString NetworkFactory::networkErrorText(QNetworkReply::NetworkError error_code) {
  switch (error_code) {
    case QNetworkReply::ProtocolUnknownError:
    case QNetworkReply::ProtocolFailure:
      //: Network status.
      return tr("protocol error");

    case QNetworkReply::HostNotFoundError:
      //: Network status.
      return tr("host not found");

    case QNetworkReply::RemoteHostClosedError:
    case QNetworkReply::ConnectionRefusedError:
      //: Network status.
      return tr("connection refused");

    case QNetworkReply::TimeoutError:
    case QNetworkReply::ProxyTimeoutError:
      //: Network status.
      return tr("connection timed out");

    case QNetworkReply::SslHandshakeFailedError:
      //: Network status.
      return tr("SSL handshake failed");

    case QNetworkReply::ProxyConnectionClosedError:
    case QNetworkReply::ProxyConnectionRefusedError:
      //: Network status.
      return tr("proxy server connection refused");

    case QNetworkReply::TemporaryNetworkFailureError:
      //: Network status.
      return tr("temporary failure");

    case QNetworkReply::AuthenticationRequiredError:
      //: Network status.
      return tr("authentication failed");

    case QNetworkReply::ProxyAuthenticationRequiredError:
      //: Network status.
      return tr("proxy authentication required");

    case QNetworkReply::ProxyNotFoundError:
      //: Network status.
      return tr("proxy server not found");

    case QNetworkReply::NoError:
      //: Network status.
      return tr("success");

    case QNetworkReply::UnknownContentError:
      //: Network status.
      return tr("uknown content");

    case QNetworkReply::ContentNotFoundError:
      //: Network status.
      return tr("content not found");

    default:
      //: Network status.
      return tr("unknown error");
  }
}

QNetworkReply::NetworkError NetworkFactory::downloadFile(const QString &url,
                                                             int timeout,
                                                             QByteArray &output,
                                                             bool protected_contents,
                                                             const QString &username,
                                                             const QString &password) {
  // Original asynchronous behavior of QNetworkAccessManager
  // is replaced by synchronous behavior in order to make
  // process of downloading of a file easier to understand.

  // Make necessary variables.
  SilentNetworkAccessManager manager;
  QEventLoop loop;
  QTimer timer;
  QNetworkRequest request;
  QNetworkReply *reply;
  QObject originatingObject;

  // Set credential information as originating object.
  originatingObject.setProperty("protected", protected_contents);
  originatingObject.setProperty("username", username);
  originatingObject.setProperty("password", password);
  request.setOriginatingObject(&originatingObject);

  // Set url for this reques.
  request.setUrl(url);

  // Create necessary connections.
  // TODO: Edited, maybe remove this line.
  QObject::connect(qApp, SIGNAL(aboutToQuit()), &loop, SLOT(quit()));
  QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
  QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

  forever {
    // This timer fires just ONCE.
    timer.setSingleShot(true);

    // Try to open communication channel.
    reply = manager.get(request);

    // Start the timeout timer.
    timer.start(timeout);

    // Enter the event loop.
    loop.exec();

    // At this point one of two things happened:
    //  a) file download was completed,
    //  b) communication timed-out.

    if (timer.isActive()) {
      // Download is complete because timer is still running.
      timer.stop();
    }
    else {
      if (reply != NULL) {
        delete reply;
        reply = NULL;
      }

      // Timer already fired. Download is NOT successful.
      return QNetworkReply::TimeoutError;
    }

    // In this phase, some part of downloading process is completed.
    QUrl redirection_url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

    if (redirection_url.isValid()) {
      // Communication indicates that HTTP redirection is needed.
      // Setup redirection URL and download again.
      request.setUrl(redirection_url);

      delete reply;
      reply = NULL;
    }
    else {
      // No redirection is indicated. Final file is obtained
      // in our "reply" object.
      break;
    }
  }

  // Read the data into output buffer.
  output = reply->readAll();

  QNetworkReply::NetworkError reply_error = reply->error();

  qDebug("File '%s' fetched with status '%s' (code %d).",
         qPrintable(url),
         qPrintable(networkErrorText(reply_error)),
         reply_error);

  // Delete needed stuff and exit.
  if (reply != NULL) {
    delete reply;
    reply = NULL;
  }

  return reply_error;
}
