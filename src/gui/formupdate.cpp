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

#include "gui/formupdate.h"

#include "definitions/definitions.h"
#include "miscellaneous/systemfactory.h"
#include "miscellaneous/iconfactory.h"
#include "network-web/webfactory.h"
#include "network-web/downloader.h"
#include "network-web/networkfactory.h"
#include "gui/custommessagebox.h"
#include "gui/systemtrayicon.h"

#include <QNetworkReply>
#include <QDesktopServices>
#include <QProcess>


FormUpdate::FormUpdate(QWidget *parent)
  : QDialog(parent), m_downloader(NULL), m_readyToInstall(false), m_ui(new Ui::FormUpdate) {
  m_ui->setupUi(this);

  // Set flags and attributes.
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  setWindowIcon(IconFactory::instance()->fromTheme("application-about"));

  m_btnUpdate = m_ui->m_buttonBox->addButton(tr("Update"), QDialogButtonBox::ActionRole);
  m_btnUpdate->setToolTip(tr("Download new installation files."));

  connect(m_btnUpdate, SIGNAL(clicked()), this, SLOT(startUpdate()));


  m_ui->m_lblCurrentRelease->setText(APP_VERSION);
  checkForUpdates();
}

FormUpdate::~FormUpdate() {
  delete m_ui;
}

bool FormUpdate::isUpdateForThisSystem() const {
  return m_updateInfo.m_urls.keys().contains(OS_ID);
}

bool FormUpdate::isSelfUpdateSupported() const {
  // DO NOT allow self-updating for now.
#if defined(Q_OS_WIN) || defined(Q_OS_OS2)
  return false;
#else
  return false;
#endif
}

void FormUpdate::checkForUpdates() {
  UpdateCheck update = qApp->checkForUpdates();

  m_updateInfo = update.first;

  if (update.second != QNetworkReply::NoError) {
    //: Unknown release.
    m_ui->m_lblAvailableRelease->setText(tr("unknown"));
    m_ui->m_txtChanges->clear();
    m_ui->m_lblStatus->setStatus(WidgetWithStatus::Error,
                                 tr("Error: '%1'.").arg(NetworkFactory::networkErrorText(update.second)),
                                 tr("List with updates was "
                                    "not\ndownloaded successfully."));
    m_btnUpdate->setEnabled(false);
    m_btnUpdate->setToolTip(tr("Checking for updates failed."));
  }
  else {
    m_ui->m_lblAvailableRelease->setText(update.first.m_availableVersion);
    m_ui->m_txtChanges->setText(update.first.m_changes);

    if (update.first.m_availableVersion > APP_VERSION) {
      m_ui->m_lblStatus->setStatus(WidgetWithStatus::Ok,
                                   tr("New release available."),
                                   tr("This is new version which can be\ndownloaded and installed."));
      m_btnUpdate->setEnabled(true);
      m_btnUpdate->setToolTip(isUpdateForThisSystem() ?
                                tr("Download installation file for your OS.") :
                                tr("Installation file is not available directly.\n"
                                   "Go to application website to obtain it manually."));

      if (isUpdateForThisSystem() /* && isSelfUpdateSupported() */ ) {
        m_btnUpdate->setText(tr("Download update"));
      }
    }
    else {
      m_ui->m_lblStatus->setStatus(WidgetWithStatus::Warning,
                                   tr("No new release available."),
                                   tr("This release is not newer than\ncurrently installed one."));
      m_btnUpdate->setEnabled(false);
      m_btnUpdate->setToolTip(tr("No new update available."));
    }
  }
}

void FormUpdate::updateProgress(qint64 bytes_received, qint64 bytes_total) {
  qApp->processEvents();
  m_ui->m_lblStatus->setStatus(WidgetWithStatus::Information,
                               tr("Downloaded %1% (update size is %2 kB).").arg(QString::number((bytes_received * 100.0) / bytes_total,
                                                                                                'f',
                                                                                                2),
                                                                                QString::number(bytes_total / 1000,
                                                                                                'f',
                                                                                                2)),
                               tr("Downloading update..."));
}

void FormUpdate::saveUpdateFile(const QByteArray &file_contents) {
  QString url_file = m_updateInfo.m_urls.value(OS_ID).m_fileUrl;;

#if QT_VERSION >= 0x050000
  QString temp_directory = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
#else
  QString temp_directory = QDesktopServices::storageLocation(QDesktopServices::TempLocation);
#endif

  if (!temp_directory.isEmpty()) {
    QString output_file_name = url_file.mid(url_file.lastIndexOf('/') + 1);
    QFile output_file(temp_directory + QDir::separator() + output_file_name);

    if (output_file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
      qDebug("Storing update file to temporary location '%s'.",
             qPrintable(output_file.fileName()));

      output_file.write(file_contents);
      output_file.flush();
      output_file.close();

      qDebug("Update file contents was successfuly saved.");

      m_updateFilePath = output_file.fileName();
      m_readyToInstall = true;
    }
    else {
      qDebug("Cannot save downloaded update file because target temporary file '%s' cannot be "
             "opened for writing.", qPrintable(output_file_name));
    }
  }
  else {
    qDebug("Cannot save downloaded update file because no TEMP folder is available.");
  }
}

void FormUpdate::updateCompleted(QNetworkReply::NetworkError status, QByteArray contents) {
  qDebug("Download of application update file was completed with code '%d'.",
         status);

  switch (status) {
    case QNetworkReply::NoError:
      saveUpdateFile(contents);

      m_ui->m_lblStatus->setStatus(WidgetWithStatus::Ok,
                                   tr("Downloaded successfully, stored in file '%1'.").arg(m_updateFilePath),
                                   tr("Package was downloaded successfully."));
      m_btnUpdate->setText(tr("Open update file"));
      m_btnUpdate->setEnabled(true);
      break;

    default:
      m_ui->m_lblStatus->setStatus(WidgetWithStatus::Error,
                                   tr("Error occured."),
                                   tr("Error occured during downloading of the package."));
      m_btnUpdate->setText(tr("Error occured"));
      break;
  }
}

void FormUpdate::startUpdate() {
  QString url_file;
  bool update_for_this_system = isUpdateForThisSystem();

  if (update_for_this_system) {
    url_file = m_updateInfo.m_urls.value(OS_ID).m_fileUrl;
  }
  else {
    url_file = APP_URL_DOWNLOADS;
  }

  if (!WebFactory::instance()->openUrlInExternalBrowser(url_file)) {
    if (SystemTrayIcon::isSystemTrayAvailable()) {
      qApp->trayIcon()->showMessage(tr("Cannot update application"),
                                    tr("Cannot navigate to installation file. Check new installation downloads "
                                       "manually on project website."),
                                    QSystemTrayIcon::Warning);
    }
    else {
      CustomMessageBox::show(this,
                             QMessageBox::Warning,
                             tr("Cannot update application"),
                             tr("Cannot navigate to installation file. Check new installation downloads "
                                "manually on project website."));
    }
  }
}
