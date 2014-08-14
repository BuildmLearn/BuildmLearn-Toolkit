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

#ifndef FORMUPLOADBUNDLE_H
#define FORMUPLOADBUNDLE_H

#include <QDialog>

#include "ui_formuploadbundle.h"
#include "miscellaneous/storefactory.h"

#include <QNetworkReply>


namespace Ui {
  class FormUploadBundle;
}

class Downloader;

/// \brief Form for uploading applications to BuildmLearn Store.
/// \see Downloader, StoreFactory
class FormUploadBundle : public QDialog {
    Q_OBJECT

  public:
    explicit FormUploadBundle(QWidget *parent = 0);
    virtual ~FormUploadBundle();

    StoreFactory::UploadStatus uploadStatus() const;

  private slots:
    void checkAuthorName(const QString &author_name);
    void checkAuthorEmail(const QString &author_email);
    void checkApplicationName(const QString &application_name);
    void checkMetadata();

    void selectApplicationIcon();
    void checkApplicationIcon(const QString &icon_path);

    void startUpload();

    void uploadProgress(qint64 bytes_sent, qint64 bytes_total);
    void uploadCompleted(QNetworkReply::NetworkError error, QByteArray output);

  signals:
    void metadataChanged();

  private:
    Ui::FormUploadBundle *m_ui;
    QPushButton *m_btnUpload;
    QPushButton *m_btnClose;
    Downloader *m_uploader;

    StoreFactory::UploadStatus m_uploadStatus;
};

#endif // FORMUPLOADBUNDLE_H
