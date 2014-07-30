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

#include "gui/formuploadbundle.h"

#include "gui/lineeditwithstatus.h"
#include "miscellaneous/application.h"
#include "network-web/downloader.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateeditor.h"
#include "definitions/definitions.h"

#include <QPushButton>


FormUploadBundle::FormUploadBundle(QWidget *parent)
  : QDialog(parent), m_ui(new Ui::FormUploadBundle), m_uploader(NULL) {
  m_ui->setupUi(this);

  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);

  // Obtain buttons.
  m_btnClose = m_ui->m_buttonBox->button(QDialogButtonBox::Close);
  m_btnUpload = m_ui->m_buttonBox->addButton(tr("&Upload application"),
                                             QDialogButtonBox::ActionRole);

  m_ui->m_txtApiKey->lineEdit()->setPlaceholderText(tr("Your store API key"));
  m_ui->m_txtApplicationName->lineEdit()->setPlaceholderText(tr("Name of your application"));
  m_ui->m_txtAuthorEmail->lineEdit()->setPlaceholderText(tr("Your e-mail"));
  m_ui->m_txtAuthorName->lineEdit()->setPlaceholderText(tr("Your name"));

  connect(m_ui->m_txtApiKey->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkApiKey(QString)));
  connect(m_ui->m_txtApplicationName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkApplicationName(QString)));
  connect(m_ui->m_txtAuthorEmail->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkAuthorEmail(QString)));
  connect(m_ui->m_txtAuthorName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkAuthorName(QString)));
  connect(this, SIGNAL(metadataChanged()), this, SLOT(checkMetadata()));
  connect(m_btnUpload, SIGNAL(clicked()), this, SLOT(startUpload()));

  checkApiKey(m_ui->m_txtApiKey->lineEdit()->text());
  checkApplicationName(m_ui->m_txtApplicationName->lineEdit()->text());
  checkAuthorEmail(m_ui->m_txtAuthorEmail->lineEdit()->text());
  checkAuthorName(m_ui->m_txtAuthorName->lineEdit()->text());
}

FormUploadBundle::~FormUploadBundle() {
  delete m_ui;
}

void FormUploadBundle::checkAuthorName(const QString &author_name) {
  bool input_ok = !author_name.simplified().isEmpty();
  m_ui->m_txtAuthorName->setStatus(input_ok ?
                                     WidgetWithStatus::Ok :
                                     WidgetWithStatus::Error,
                                   input_ok ?
                                     tr("Your name is okay.") :
                                     tr("Enter valid name."));

  emit metadataChanged();
}

void FormUploadBundle::checkAuthorEmail(const QString &author_email) {
  bool input_ok = !author_email.simplified().isEmpty();
  m_ui->m_txtAuthorEmail->setStatus(input_ok ?
                                      WidgetWithStatus::Ok :
                                      WidgetWithStatus::Error,
                                    input_ok ?
                                      tr("Your e-mail is okay.") :
                                      tr("Enter valid e-mail."));

  emit metadataChanged();
}

void FormUploadBundle::checkApplicationName(const QString &application_name) {
  bool input_ok = !application_name.simplified().isEmpty();
  m_ui->m_txtApplicationName->setStatus(input_ok ?
                                          WidgetWithStatus::Ok :
                                          WidgetWithStatus::Error,
                                        input_ok ?
                                          tr("Your application name is okay.") :
                                          tr("Enter valid application name."));

  emit metadataChanged();
}

void FormUploadBundle::checkApiKey(const QString &api_key) {
  bool input_ok = !api_key.simplified().isEmpty();
  m_ui->m_txtApiKey->setStatus(input_ok ?
                                 WidgetWithStatus::Ok :
                                 WidgetWithStatus::Error,
                               input_ok ?
                                 tr("Your store API key is okay.") :
                                 tr("Enter valid store API key."));

  emit metadataChanged();
}

void FormUploadBundle::checkMetadata() {
  m_btnUpload->setEnabled(m_ui->m_txtApiKey->status() == WidgetWithStatus::Ok &&
                          m_ui->m_txtApplicationName->status() == WidgetWithStatus::Ok &&
                          m_ui->m_txtAuthorEmail->status() == WidgetWithStatus::Ok &&
                          m_ui->m_txtAuthorName->status() == WidgetWithStatus::Ok);

  if (m_btnUpload->isEnabled()) {
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Ok,
                                   tr("Ready to upload."),
                                   tr("Ready to upload."));
  }
  else {
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Error,
                                   tr("Fill-in missing metadata."),
                                   tr("In order to continue, fill-in missing metadata."));
  }
}

void FormUploadBundle::startUpload() {
  if (m_uploader == NULL) {
    m_uploader = new Downloader(this);

    connect(m_uploader, SIGNAL(progress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
    connect(m_uploader, SIGNAL(completed(QNetworkReply::NetworkError,QByteArray)), this,
            SLOT(uploadCompleted(QNetworkReply::NetworkError,QByteArray)));
  }

  // Prepare parameters and data.
  QString xml_bundle_data = qApp->templateManager()->activeCore()->editor()->generateBundleData();

  if (xml_bundle_data.isEmpty()) {
    // TODO: error
  }

  // Finally, start file upload.
  m_btnClose->setEnabled(false);
  m_btnUpload->setEnabled(false);
  m_uploader->uploadBundleFile(STORE_ENDPOINT, xml_bundle_data, m_ui->m_txtApiKey->lineEdit()->text(),
                               m_ui->m_txtAuthorName->lineEdit()->text(), m_ui->m_txtAuthorEmail->lineEdit()->text(),
                               m_ui->m_txtApplicationName->lineEdit()->text());
  m_ui->m_lblProgress->setStatus(WidgetWithStatus::Information,
                                 tr("Uploading application..."),
                                 tr("Uploading application..."));
}

void FormUploadBundle::uploadProgress(qint64 bytes_sent, qint64 bytes_total) {
  m_ui->m_progressUpload->setValue(bytes_sent * 100.0 / bytes_total);
}

void FormUploadBundle::uploadCompleted(QNetworkReply::NetworkError error, QByteArray output) {
  qDebug(qPrintable(output));

  if (error == QNetworkReply::NoError) {
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Ok,
                                   tr("Uploading finished successfully."),
                                   tr("Uploading finished successfully."));
  }
  else {
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Error,
                                   tr("Error occured during upload process."),
                                   tr("Error occured during upload process."));
  }

  m_btnClose->setEnabled(true);
  m_btnUpload->setEnabled(true);
}
