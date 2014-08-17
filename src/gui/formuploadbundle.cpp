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
#include "miscellaneous/iconfactory.h"
#include "network-web/downloader.h"
#include "network-web/networkfactory.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateeditor.h"
#include "definitions/definitions.h"

#include <QPushButton>
#include "QFileDialog"


FormUploadBundle::FormUploadBundle(QWidget *parent)
  : QDialog(parent), m_ui(new Ui::FormUploadBundle), m_uploader(NULL), m_uploadStatus(StoreFactory::OtherError) {
  m_ui->setupUi(this);

  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  setWindowIcon(IconFactory::instance()->fromTheme("project-upload"));

  // Obtain buttons.
  m_btnClose = m_ui->m_buttonBox->button(QDialogButtonBox::Close);
  m_btnUpload = m_ui->m_buttonBox->addButton(tr("&Upload application"),
                                             QDialogButtonBox::ActionRole);

  m_ui->m_txtApplicationName->lineEdit()->setPlaceholderText(tr("Name of your application"));
  m_ui->m_txtAuthorEmail->lineEdit()->setPlaceholderText(tr("Your e-mail"));
  m_ui->m_txtAuthorName->lineEdit()->setPlaceholderText(tr("Your name"));

  // Add categories.
  m_ui->m_cmbCategory->addItem(tr("Science"), "Science");
  m_ui->m_cmbCategory->addItem(tr("Math"), "Math");
  m_ui->m_cmbCategory->addItem(tr("Physics"), "Physics");
  m_ui->m_cmbCategory->addItem(tr("Literature"), "Literature");
  m_ui->m_cmbCategory->addItem(tr("English"), "English");
  m_ui->m_cmbCategory->addItem(tr("Geography"), "Geography");
  m_ui->m_cmbCategory->addItem(tr("Social Studies"), "Social Studies");
  m_ui->m_cmbCategory->addItem(tr("Language"), "Language");
  m_ui->m_cmbCategory->addItem(tr("History"), "History");
  m_ui->m_cmbCategory->addItem(tr("Chemistry"), "Chemistry");

  connect(m_ui->m_txtApplicationName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkApplicationName(QString)));
  connect(m_ui->m_txtAuthorEmail->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkAuthorEmail(QString)));
  connect(m_ui->m_txtAuthorName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkAuthorName(QString)));
  connect(this, SIGNAL(metadataChanged()), this, SLOT(checkMetadata()));
  connect(m_btnUpload, SIGNAL(clicked()), this, SLOT(startUpload()));
  connect(m_ui->m_btnSelectIcon, SIGNAL(clicked()), this, SLOT(selectApplicationIcon()));

  setTabOrder(m_ui->m_txtApplicationName->lineEdit(), m_ui->m_txtApplicationDescription);
  setTabOrder(m_ui->m_txtApplicationDescription, m_ui->m_txtAuthorName->lineEdit());
  setTabOrder(m_ui->m_txtAuthorName->lineEdit(), m_ui->m_txtAuthorEmail->lineEdit());
  setTabOrder(m_ui->m_txtAuthorEmail->lineEdit(), m_ui->m_cmbCategory);
  /*setTabOrder(m_ui->m_cmbCategory, m_btnUpload);
  setTabOrder(m_btnUpload, m_ui->m_buttonBox->);
  */
  checkApplicationName(QString());
  checkAuthorName(QString());
  checkAuthorEmail(QString());
  checkApplicationIcon(QString());
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
  bool input_ok = QRegExp("^\\S+@\\S+\\.\\S{2,3}$").exactMatch(author_email);
  m_ui->m_txtAuthorEmail->setStatus(input_ok ?
                                      WidgetWithStatus::Ok :
                                      WidgetWithStatus::Error,
                                    input_ok ?
                                      tr("Your e-mail is okay.") :
                                      tr("Enter valid e-mail in the form \"john@doe.com\"."));

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

void FormUploadBundle::checkMetadata() {
  m_btnUpload->setEnabled(m_ui->m_txtApplicationName->status() == WidgetWithStatus::Ok &&
                          m_ui->m_txtAuthorEmail->status() == WidgetWithStatus::Ok &&
                          m_ui->m_txtAuthorName->status() == WidgetWithStatus::Ok &&
                          m_ui->m_lblIcon->status() == WidgetWithStatus::Ok);

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

void FormUploadBundle::selectApplicationIcon() {
  QString selected_picture = QFileDialog::getOpenFileName(this, tr("Select icon for application"),
                                                          m_ui->m_lblIcon->label()->toolTip().isEmpty() ?
                                                            APP_APK_ICON_PATH :
                                                            m_ui->m_lblIcon->label()->toolTip(),
                                                          tr("Icons (*.jpg *.png)"));

  checkApplicationIcon(selected_picture);
}

void FormUploadBundle::checkApplicationIcon(const QString &icon_path) {
  if (!icon_path.isEmpty()) {
    m_ui->m_lblIcon->setStatus(WidgetWithStatus::Ok,
                               tr("Correct icon is selected."),
                               QDir::toNativeSeparators(icon_path));
  }
  else {
    m_ui->m_lblIcon->setStatus(WidgetWithStatus::Error,
                               tr("No valid icon is selected."),
                               QDir::toNativeSeparators(icon_path));
  }

  emit metadataChanged();
}

void FormUploadBundle::startUpload() {
  // Prepare parameters and data.
  QString xml_bundle_data = qApp->templateManager()->activeCore()->editor()->generateBundleData();

  if (xml_bundle_data.isEmpty()) {
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Error,
                                   tr("Cannot upload application."),
                                   tr("Application cannot be uploaded because template return error.\nContact application developers to fix this issue."));
    return;
  }

  if (m_uploader == NULL) {
    m_uploader = new Downloader(this);

    connect(m_uploader, SIGNAL(progress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
    connect(m_uploader, SIGNAL(completed(QNetworkReply::NetworkError,QByteArray)), this,
            SLOT(uploadCompleted(QNetworkReply::NetworkError,QByteArray)));
  }

  // Finally, start file upload.
  m_btnClose->setEnabled(false);
  m_btnUpload->setEnabled(false);

  // Obtain real endpoint.

  QByteArray endpoint;
  QNetworkReply::NetworkError endpoint_status = NetworkFactory::downloadFile(STORE_ENDPOINT, 5000,
                                                                             endpoint);

  if (endpoint_status != QNetworkReply::NoError) {
    // Endpoint was not obtained.
    m_btnClose->setEnabled(true);
    m_btnUpload->setEnabled(true);
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Error,
                                   tr("Endpoint was not obtained."),
                                   tr("Endpoint was not obtained."));

    return;
  }

  m_uploader->uploadBundleFile(QString(endpoint), xml_bundle_data, STORE_API_KEY,
                               m_ui->m_txtAuthorName->lineEdit()->text(),
                               m_ui->m_txtAuthorEmail->lineEdit()->text(),
                               m_ui->m_txtApplicationName->lineEdit()->text(),
                               m_ui->m_lblIcon->label()->toolTip());
  m_ui->m_lblProgress->setStatus(WidgetWithStatus::Information,
                                 tr("Uploading application..."),
                                 tr("Uploading application..."));
}

void FormUploadBundle::uploadProgress(qint64 bytes_sent, qint64 bytes_total) {
  m_ui->m_progressUpload->setValue(bytes_sent * 100.0 / bytes_total);
  qApp->processEvents();
}

void FormUploadBundle::uploadCompleted(QNetworkReply::NetworkError error, QByteArray output) {
  qDebug(qPrintable(QString(output)));

  m_uploadStatus = StoreFactory::parseResponseXml(error, output);
  QString string_status = StoreFactory::uploadStatusToString(m_uploadStatus);

  if (m_uploadStatus == StoreFactory::Success) {
    close();
  }
  else {
    m_ui->m_lblProgress->setStatus(WidgetWithStatus::Error,
                                   string_status,
                                   string_status);
  }

  m_btnClose->setEnabled(true);
  m_btnUpload->setEnabled(true);
}

StoreFactory::UploadStatus FormUploadBundle::uploadStatus() const {
  return m_uploadStatus;
}
