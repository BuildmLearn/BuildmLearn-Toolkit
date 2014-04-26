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


#ifndef BASENETWORKACCESSMANAGER_H
#define BASENETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>


/// \brief Base class for all network access managers.
class BaseNetworkAccessManager : public QNetworkAccessManager {
    Q_OBJECT

  public:
    /// \brief Constructor.
    explicit BaseNetworkAccessManager(QObject *parent = 0);
    virtual ~BaseNetworkAccessManager();

  public slots:
    /// \brief Loads network settings for this instance.
    /// \remarks This sets up proxy settings.
    virtual void loadSettings();

  protected slots:
    /// \brief Catches and processes SSL errors.
    /// \param reply Network reply for which error came up.
    /// \param error Error description.
    void onSslErrors(QNetworkReply *reply,
                     const QList<QSslError> &error);

  protected:
    /// \brief Creates custom request.
    /// \param op Requested operation.
    /// \param request The request object itself.
    /// \param outgoingData Buffer for writting output data.
    /// \return Returns newly created reply for given request.
    QNetworkReply *createRequest(Operation op,
                                 const QNetworkRequest &request,
                                 QIODevice *outgoingData);
};

#endif // BASENETWORKACCESSMANAGER_H
