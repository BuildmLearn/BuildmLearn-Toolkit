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

#include "miscellaneous/application.h"

#include "definitions/definitions.h"
#include "miscellaneous/systemfactory.h"
#include "network-web/networkfactory.h"
#include "gui/systemtrayicon.h"
#include "gui/formmain.h"


Application::Application(int &argc, char **argv)
  : QApplication(argc, argv),
    m_settings(NULL),
    m_systemFactory(NULL),
    m_trayIcon(NULL) {
  connect(this, SIGNAL(aboutToQuit()),
          this, SLOT(onAboutToQuit()));
  connect(this, SIGNAL(commitDataRequest(QSessionManager&)),
          this, SLOT(onCommitData(QSessionManager&)));
  connect(this, SIGNAL(saveStateRequest(QSessionManager&)),
          this, SLOT(onSaveState(QSessionManager&)));
}

Application::~Application() {
}

QPair<UpdateInfo, QNetworkReply::NetworkError> Application::checkForUpdates() {
  if (m_systemFactory == NULL) {
    m_systemFactory = new SystemFactory(this);
  }

  return m_systemFactory->checkForUpdates();
}

SystemTrayIcon *Application::trayIcon() {
  if (m_trayIcon == NULL) {
    m_trayIcon = new SystemTrayIcon(APP_ICON_PATH, m_mainForm);
    m_trayIcon->setToolTip(APP_LONG_NAME);
  }

  return m_trayIcon;
}

void Application::checkForUpdatesOnBackground() {
  if (!settings()->value(APP_CFG_GEN,
                         "check_for_updates_startup",
                         true).toBool()) {
    qDebug("Checking for updates after application startup is not allowed.");
  }
  else {
    qDebug("Checking for updates after application has started.");

    QPair<UpdateInfo, QNetworkReply::NetworkError> updates = checkForUpdates();

    switch (updates.second) {
      case QNetworkReply::NoError:
        if (updates.first.m_availableVersion > APP_VERSION) {
          trayIcon()->showMessage(tr("Update available"),
                                  tr("New application update is available."),
                                  QSystemTrayIcon::Information);
        }
        else {
          trayIcon()->showMessage(tr("No updates available"),
                                  tr("No new updates are available."),
                                  QSystemTrayIcon::Information);
        }
        break;

      default:
        trayIcon()->showMessage(tr("Update check error"),
                                tr("Could not check for updates: %1.").arg(NetworkFactory::networkErrorText(updates.second)),
                                QSystemTrayIcon::Warning);
        break;
    }
  }
}

void Application::onAboutToQuit() {
  qDebug("Quitting the application.");
}

void Application::onCommitData(QSessionManager &manager) {
  qDebug("OS asked application to commit its data.");

  manager.setRestartHint(QSessionManager::RestartNever);
  manager.release();
}

void Application::onSaveState(QSessionManager &manager) {
  qDebug("OS asked application to save its state.");

  manager.setRestartHint(QSessionManager::RestartNever);
  manager.release();
}
