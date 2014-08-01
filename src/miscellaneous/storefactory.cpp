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

#include "miscellaneous/storefactory.h"

#include "definitions/definitions.h"

#include <QDomDocument>
#include <QDomElement>


StoreFactory::StoreFactory(QObject *parent) : QObject(parent) {
}

StoreFactory::~StoreFactory() {
}

QString StoreFactory::uploadStatusToString(StoreFactory::UploadStatus status) {
  switch (status) {
    case Success:
      return tr("Application uploaded successfully.");

    case NetworkError:
      return tr("Network error occurred.");

    case MissingParameters:
      return tr("Error - some parameters are missing.");

    case FileTooBig:
      return tr("Application file is too big.");

    default:
      return tr("Unknown status.");
  }
}

StoreFactory::UploadStatus StoreFactory::parseResponseXml(QNetworkReply::NetworkError error_status,
                                                          const QByteArray &response) {
  // TODO: finalize this.
  switch (error_status) {
    case QNetworkReply::NoError: {
      QDomDocument xml_response;
      xml_response.setContent(QString(response));

      QString status = xml_response.documentElement().namedItem("status").toElement().text();

      if (status == STORE_ANSWER_SUCCESS) {
        return Success;
      }
      else if (status == STORE_ANSWER_INVALID_KEY) {
        return InvalidKey;
      }
      else if (status == STORE_ANSWER_NO_PARAMETERS) {
        return MissingParameters;
      }
      else {
        return OtherError;
      }
    }

    default:
      return NetworkError;
  }
}
