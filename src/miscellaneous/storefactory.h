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

#ifndef STOREFACTORY_H
#define STOREFACTORY_H

#include <QObject>

#include <QNetworkReply>


/// \brief Main BuildmLearn Store functionality.
class StoreFactory : public QObject {
    Q_OBJECT

  public:
    /// \brief Possible states of application upload process.
    enum UploadStatus {
      Success,
      NetworkError,
      MissingParameters,
      InvalidKey,
      FileTooBig,
      OtherError
    };

    virtual ~StoreFactory();

    /// \brief Converts UploadStatus enumeration to textual representation.
    /// \param status Upload result.
    /// \return Returns textual representation of application upload process status.
    static QString uploadStatusToString(UploadStatus status);

    /// \brief Parses received XML from BuildmLearn Store server.
    /// \param error_status Network status of connection to BuildmLearn Store server.
    /// \param response XML received from BuildmLearn Store server.
    /// \return Returns appropriate UploadStatus for given service response XML.
    static UploadStatus parseResponseXml(QNetworkReply::NetworkError error_status,
                                         const QByteArray &response);

  private:
    explicit StoreFactory(QObject *parent = 0);
};

#endif // STOREFACTORY_H
