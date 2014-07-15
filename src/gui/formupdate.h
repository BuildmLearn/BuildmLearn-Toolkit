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

#ifndef FORMUPDATE_H
#define FORMUPDATE_H

#include "ui_formupdate.h"

#include "miscellaneous/systemfactory.h"

#include <QDialog>
#include <QPushButton>
#include <QNetworkReply>


namespace Ui {
  class FormUpdate;
}

class Downloader;

/// \brief Dialog for showing update details.
/// \see UpdateInfo, UpdateUrl, SystemFactory::checkForUpdates()
class FormUpdate : public QDialog {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit FormUpdate(QWidget *parent = 0);
    virtual ~FormUpdate();

    /// \brief Indication of update/platform suitability.
    /// \return Returns true if current update provides
    /// installation file for current platform.
    bool isUpdateForThisSystem() const;

    /// \brief Indication of presence of self-update feature.
    /// \return Returns true if application can self-update
    /// on current platform.
    /// \note This returns false for all platforms.
    bool isSelfUpdateSupported() const;

  protected slots:
    /// \brief Check for updates and interprets the results.
    void checkForUpdates();

    void startUpdate();

    void updateProgress(qint64 bytes_received, qint64 bytes_total);
    void updateCompleted(QNetworkReply::NetworkError status, QByteArray contents);
    void saveUpdateFile(const QByteArray &file_contents);

  private:
    Downloader *m_downloader;
    bool m_readyToInstall;
    QString m_updateFilePath;
    Ui::FormUpdate *m_ui;
    UpdateInfo m_updateInfo;
    QPushButton *m_btnUpdate;
};

#endif // FORMUPDATE_H
