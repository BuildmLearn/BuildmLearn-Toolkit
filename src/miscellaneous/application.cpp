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

#include "miscellaneous/systemfactory.h"
#include "miscellaneous/skinfactory.h"
#include "network-web/networkfactory.h"
#include "gui/systemtrayicon.h"
#include "gui/formmain.h"
#include "core/templatefactory.h"

#include <QMutex>
#include <QFuture>
#include <QFutureWatcher>

#if QT_VERSION >= 0x050000
#include <QtConcurrent/QtConcurrentRun>
#else
#include <QtConcurrentRun>
#endif


Application::Application(int &argc, char **argv)
  : QApplication(argc, argv),
    m_externalApplicationChecked(false),
    m_closeLock(new QMutex()),
    m_availableActions(QList<QAction*>()),
    m_settings(NULL),
    m_skinFactory(NULL),
    m_trayIcon(NULL),
    m_templateManager(NULL),
    m_closing(false) {
  connect(this, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
  connect(this, SIGNAL(commitDataRequest(QSessionManager&)), this, SLOT(onCommitData(QSessionManager&)));
  connect(this, SIGNAL(saveStateRequest(QSessionManager&)), this, SLOT(onSaveState(QSessionManager&)));
}

Application::~Application() {
  delete m_closeLock;
}

UpdateCheck Application::checkForUpdates() {
  return SystemFactory::checkForUpdates();
}

SkinFactory *Application::skinFactory() {
  if (m_skinFactory == NULL) {
    m_skinFactory = new SkinFactory(this);
  }

  return m_skinFactory;
}

void Application::setZipUtilityPath(const QString& zip_path) {
  settings()->setValue(APP_CFG_GEN, "zip_path", zip_path);
}

void Application::setSignApkUtilityPath(const QString& signapk_path) {
  settings()->value(APP_CFG_GEN, "signapk_path", signapk_path);
}

int Application::checkJava(const QString &new_path) {
  QString java_path = new_path.isEmpty() ? javaInterpreterPath() : new_path;

  if (java_path.isEmpty()) {
    return EXIT_STATUS_NOT_STARTED;
  }
  else {
    QProcess process;

    process.setReadChannelMode(QProcess::MergedChannels);
    process.start(QDir::toNativeSeparators(java_path), QStringList() << "-version");
    process.waitForFinished(-1);

    return process.exitCode();
  }
}

int Application::checkSignApk(const QString &new_path, const QString &java_path) {
  QString real_java_path = java_path.isEmpty() ? javaInterpreterPath() : java_path;
  QString signapk_path = new_path.isEmpty() ? signApkUtlityPath() : new_path;

  if (signapk_path.isEmpty()) {
    return EXIT_STATUS_NOT_STARTED;
  }
  else {
    QProcess process;

    process.setReadChannelMode(QProcess::MergedChannels);
    process.start(QDir::toNativeSeparators(real_java_path),
                  QStringList() << "-jar" << QDir::toNativeSeparators(signapk_path));
    process.waitForFinished(-1);

    return process.exitCode();
  }
}

int Application::checkZip(const QString &new_path) {
  QString zip_path = new_path.isEmpty() ? zipUtilityPath() : new_path;

  if (zip_path.isEmpty()) {
    return EXIT_STATUS_NOT_STARTED;
  }
  else {
    QProcess process;

    process.setReadChannelMode(QProcess::MergedChannels);
    process.start(QDir::toNativeSeparators(zip_path), QStringList() << "--version");
    process.waitForFinished(-1);

    return process.exitCode();
  }
}

void Application::recheckExternalApplications(bool emit_signals) {
  int java_ready = checkJava();
  int zip_ready = checkZip();
  int signapk_ready = checkSignApk();

  if (signapk_ready != EXIT_STATUS_SIGNAPK_NORMAL ||
      java_ready != EXIT_STATUS_JAVA_NORMAL ||
      zip_ready != EXIT_STATUS_ZIP_NORMAL) {
    m_externalApplicationsStatus = QString();

    if (signapk_ready != EXIT_STATUS_SIGNAPK_NORMAL) {
      m_externalApplicationsStatus += qApp->interpretSignApk(signapk_ready) + '\n';
    }

    if (java_ready != EXIT_STATUS_JAVA_NORMAL) {
      m_externalApplicationsStatus += qApp->interpretJava(java_ready) + '\n';
    }

    if (zip_ready != EXIT_STATUS_ZIP_NORMAL) {
      m_externalApplicationsStatus += qApp->interpretZip(zip_ready) + '\n';
    }

    m_externalApplicationsStatus.chop(1);
    m_externalApplicationsReady = false;
  }
  else {
    m_externalApplicationsReady = true;
  }

  m_externalApplicationChecked = true;

  if (emit_signals) {
    emit externalApplicationsRechecked();
  }
}

QString Application::interpretJava(int return_code) {
  switch (return_code) {
    case EXIT_STATUS_NOT_STARTED:
      return tr("JAVA was not found at given location.");

    case EXIT_STATUS_CRASH:
      return tr("JAVA found but is crashy.");

    case EXIT_STATUS_JAVA_NORMAL:
      return tr("JAVA found and probably working.");

    default:
      return tr("JAVA returned uknown code.");
  }
}

QString Application::interpretZip(int return_code) {
  switch (return_code) {
    case EXIT_STATUS_NOT_STARTED:
      return tr("ZIP was not found at given location.");

    case EXIT_STATUS_CRASH:
      return tr("ZIP found but is crashy.");

    case EXIT_STATUS_ZIP_NORMAL:
      return tr("ZIP found and probably working.");

    default:
      return tr("ZIP returned uknown code.");
  }
}

QString Application::interpretSignApk(int return_code) {
  switch (return_code) {
    case EXIT_STATUS_NOT_STARTED:
      return tr("SIGNAPK was not found because JAVA was not found.");

    case EXIT_STATUS_CRASH:
      return tr("SIGNAPK found but is crashy.");

    case EXIT_STATUS_SIGNAPK_NOT_FOUND:
      return tr("SIGNAPK not found.");

    case EXIT_STATUS_SIGNAPK_NORMAL:
      return tr("SIGNAPK found and probably working.");

    case EXIT_STATUS_SIGNAPK_WORKING:
      return tr("SIGNAPK found and but there is high risk it is invalid.");

    default:
      return tr("SIGNAPK returned uknown code.");
  }
}

QList<QAction*> Application::availableActions() {
  if (m_mainForm == NULL) {
    return QList<QAction*>();
  }
  else {
    if (m_availableActions.isEmpty()) {
      m_availableActions = m_mainForm->allActions();
    }

    return m_availableActions;
  }
}

SystemTrayIcon *Application::trayIcon() {
  if (m_trayIcon == NULL) {
    m_trayIcon = new SystemTrayIcon(APP_ICON_PATH, m_mainForm);
    m_trayIcon->setToolTip(APP_LONG_NAME);
  }

  return m_trayIcon;
}

TemplateFactory *Application::templateManager() {
  if (m_templateManager == NULL) {
    m_templateManager = new TemplateFactory(this);
  }

  return m_templateManager;
}

void Application::handleBackgroundUpdatesCheck() {
  QFutureWatcher<UpdateCheck> *future_watcher = static_cast<QFutureWatcher<UpdateCheck>*>(sender());
  UpdateCheck updates = future_watcher->result();

  switch (updates.second) {
    case QNetworkReply::NoError:
      if (updates.first.m_availableVersion > APP_VERSION) {
        if (SystemTrayIcon::isSystemTrayAvailable()) {
          trayIcon()->showMessage(tr("Update available"),
                                  tr("New application update is available."),
                                  QSystemTrayIcon::Information,
                                  TRAY_ICON_BUBBLE_TIMEOUT,
                                  qApp->mainForm(),
                                  SLOT(showUpdatesAfterBubbleClick()));
        }
      }
      else {
        if (SystemTrayIcon::isSystemTrayAvailable()) {
          trayIcon()->showMessage(tr("No updates available"),
                                  tr("No new updates are available."),
                                  QSystemTrayIcon::Information);
        }
      }

      break;

    default:
      if (SystemTrayIcon::isSystemTrayAvailable()) {
        trayIcon()->showMessage(tr("Update check error"),
                                tr("Could not check for updates: %1.").arg(NetworkFactory::networkErrorText(updates.second)),
                                QSystemTrayIcon::Warning);
      }

      break;
  }
}

bool Application::isClosing() const {
  return m_closing;
}

bool Application::externalApplicationChecked() const {
  return m_externalApplicationChecked;
}

QString Application::externalApplicationsStatus() const {
  return m_externalApplicationsStatus;
}

bool Application::externalApplicationsReady() const {
  return m_externalApplicationsReady;
}

void Application::checkForUpdatesOnBackground() {
  if (!settings()->value(APP_CFG_GEN,
                         "check_for_updates_startup",
                         true).toBool()) {
    qDebug("Checking for updates after application startup is not allowed.");
  }
  else {
    qDebug("Checking for updates after application has started.");

    QFutureWatcher<UpdateCheck> *watcher_for_future = new QFutureWatcher<UpdateCheck>(this);

    connect(watcher_for_future, SIGNAL(finished()), this, SLOT(handleBackgroundUpdatesCheck()));
    watcher_for_future->setFuture(QtConcurrent::run(this, &Application::checkForUpdates));
  }
}

void Application::onAboutToQuit() {
  qDebug("Quitting the application.");
  qDebug("Cleaning up resources and saving application state.");

  if (closeLock()->tryLock(CLOSE_LOCK_TIMEOUT)) {
    // Application obtained permission to close
    // in a safety way.
    qDebug("Close lock was obtained safely.");

    templateManager()->quit();

    // We locked the lock to exit peacefully, unlock it to avoid warnings.
    closeLock()->unlock();
  }
  else {
    // Request for write lock timed-out. This means
    // that some critical action can be processed right now.
    qDebug("Close lock timed-out.");
  }
}

void Application::onCommitData(QSessionManager &manager) {
  qDebug("OS asked application to commit its data.");

  m_closing = true;

  manager.setRestartHint(QSessionManager::RestartNever);
  manager.release();
}

void Application::onSaveState(QSessionManager &manager) {
  qDebug("OS asked application to save its state.");

  manager.setRestartHint(QSessionManager::RestartNever);
  manager.release();
}
