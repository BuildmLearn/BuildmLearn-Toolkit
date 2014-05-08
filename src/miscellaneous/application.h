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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "miscellaneous/settings.h"
#include "miscellaneous/systemfactory.h"

#include <QNetworkReply>
#include <QSessionManager>
#include <QHash>

#if defined(qApp)
#undef qApp
#endif

// Define new qApp macro. Yeaaaaah.
#define qApp (Application::instance())


typedef QPair<UpdateInfo, QNetworkReply::NetworkError> UpdateCheck;

class FormMain;
class SystemTrayIcon;
class SkinFactory;
class QAction;
class QMutex;

/// \brief Key application class containing all critical
/// elements of the application.
/// \see Settings, FormMain, UpdateInfo, SystemTrayIcon
class Application : public QApplication {
    Q_OBJECT

  public:
    /// \brief Constructor.
    /// \param argc Count of arguments passed to the executable file.
    /// \param argv Array of strings of arguments.
    explicit Application(int &argc, char **argv);
    virtual ~Application();

    /// \brief Tries to download list with new updates.
    /// \return Returns pair of information: metadata of update and
    /// network status of update.
    UpdateCheck checkForUpdates();

    /// \brief Access to application-wide settings.
    /// \return
    inline Settings *settings() {
      if (m_settings == NULL) {
        m_settings = Settings::setupSettings(this);
      }

      return m_settings;
    }

    /// \brief Access to application-wide close lock.
    /// \return Returns pointer to application-wide close lock.
    /// \remarks Application-wide close lock is used to determine if
    /// application can be closed securely.
    inline QMutex *closeLock() const {
      return m_closeLock;
    }

    /// \brief Access to application-wide skin facilities.
    /// \return Returns pointer to skin facilities.
    SkinFactory *skinFactory();

    /// \brief Access to main application form.
    /// \return Returns pointer to main application form.
    inline FormMain *mainForm() {
      return m_mainForm;
    }

    /// \brief Setter for main application form.
    /// \param main_form Pointer to main application form.
    void setMainForm(FormMain *main_form) {
      m_mainForm = main_form;
    }

    /// \brief Access to all application-wide useable actions.
    /// \return Return list of user actions.
    QHash<QString, QAction*> availableActions();

    /// \brief Access to application tray icon.
    /// \return Returns pointer to application tray icon.
    /// \warning Always use this in cooperation with
    /// SystemTrayIcon::isSystemTrayActivated().
    SystemTrayIcon *trayIcon();

    /// \brief Main static getter of global Application instance.
    /// \return Returns singleton for Application.
    inline static Application *instance() {
      return static_cast<Application*>(QCoreApplication::instance());
    }

  public slots:
    /// \brief Schedules check for updates.
    ///
    /// Check for updates is executed in separate thread. Result is announced
    /// via tray icon balloon tip. If tray icon is not available, then
    /// result is not announced and is suppressed.
    void checkForUpdatesOnBackground();

  private slots:
    void onAboutToQuit();
    void onCommitData(QSessionManager &manager);
    void onSaveState(QSessionManager &manager);

    void handleBackgroundUpdatesCheck();

  private:
    QMutex *m_closeLock;
    QHash<QString, QAction*> m_availableActions;
    Settings *m_settings;
    SkinFactory *m_skinFactory;
    SystemTrayIcon *m_trayIcon;
    FormMain *m_mainForm;
};

#endif // APPLICATION_H
