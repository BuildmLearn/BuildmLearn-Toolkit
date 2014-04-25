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


#include "network-web/basenetworkaccessmanager.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/application.h"

#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>


BaseNetworkAccessManager::BaseNetworkAccessManager(QObject *parent)
  : QNetworkAccessManager(parent) {
  connect(this, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
          this, SLOT(onSslErrors(QNetworkReply*,QList<QSslError>)));

  loadSettings();
}

BaseNetworkAccessManager::~BaseNetworkAccessManager() {
}

void BaseNetworkAccessManager::loadSettings() {
  QNetworkProxy new_proxy;
  QNetworkProxy::ProxyType selected_proxy_type = static_cast<QNetworkProxy::ProxyType>(qApp->settings()->value(APP_CFG_PROXY,
                                                                                                               "proxy_type",
                                                                                                               QNetworkProxy::NoProxy).toInt());

  if (selected_proxy_type == QNetworkProxy::NoProxy) {
    // No extra setting is needed, set new proxy and exit this method.
    setProxy(QNetworkProxy::NoProxy);
    return;
  }
  else if (selected_proxy_type == QNetworkProxy::DefaultProxy) {
    setProxy(QNetworkProxy::applicationProxy());
    return;
  }

  Settings *settings = qApp->settings();

  // Custom proxy is selected, set it up.
  new_proxy.setType(selected_proxy_type);
  new_proxy.setHostName(settings->value(APP_CFG_PROXY,
                                        "host").toString());
  new_proxy.setPort(settings->value(APP_CFG_PROXY,
                                    "port", 80).toInt());
  new_proxy.setUser(settings->value(APP_CFG_PROXY,
                                    "username").toString());
  new_proxy.setPassword(settings->value(APP_CFG_PROXY,
                                        "password").toString());
  setProxy(new_proxy);

  qDebug("Settings of BaseNetworkAccessManager loaded.");
}

void BaseNetworkAccessManager::onSslErrors(QNetworkReply *reply,
                                           const QList<QSslError> &error) {
  qDebug("SSL errors for '%s': '%s' (code %d).",
         qPrintable(reply->url().toString()),
         qPrintable(reply->errorString()),
         (int) reply->error());

  reply->ignoreSslErrors(error);
}

QNetworkReply *BaseNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op,
                                                       const QNetworkRequest &request,
                                                       QIODevice *outgoingData) {
  QNetworkRequest new_request = request;

  // This rapidly speeds up loading of web sites.
  // NOTE: https://en.wikipedia.org/wiki/HTTP_pipelining
  new_request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute,
                           true);

  // Setup custom user-agent.
  new_request.setRawHeader(USER_AGENT_HTTP_HEADER,
                           QString(APP_USERAGENT).toLocal8Bit());

  return QNetworkAccessManager::createRequest(op, new_request, outgoingData);
}
