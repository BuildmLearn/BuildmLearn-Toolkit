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

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/systemfactory.h"
#include "gui/systemtrayicon.h"

#include <QNetworkReply>
#include <QSessionManager>
#include <QHash>

#if defined(qApp)
#undef qApp
#endif

// Define new qApp macro. Yeaaaaah.
#define qApp (Application::instance())

typedef QPair<UpdateInfo, QNetworkReply::NetworkError> UpdateCheck;

class TemplateFactory;
class FormMain;
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

    /// \brief Access to "zip" utility path.
    /// \return Returns path to "zip" utlity.
    inline QString zipUtilityPath() {
      return settings()->value(APP_CFG_GEN,
                               "zip_path",
                               QString(APP_ZIP_PATH)).toString();
    }

    /// \brief Sets new path to "zip".
    /// \param zip_path Path to "zip".
    void setZipUtilityPath(const QString &zip_path);

    /// \brief Access to path to "signapk" utility.
    /// \return Return path to "signapk".
    inline QString signApkUtlityPath() {
      return settings()->value(APP_CFG_GEN,
                               "signapk_path",
                               QString(APP_SIGNAPK_PATH)).toString();
    }

    /// \brief Sets new path to "signapk".
    /// \param signapk_path New path to "signapk".
    void setSignApkUtilityPath(const QString &signapk_path);

    /// \brief Access to path to "java" interpreter.
    /// \return Returns path to "java" interpreter.
    inline QString javaInterpreterPath() {
      return settings()->value(APP_CFG_GEN, "java_path", QString(APP_JAVA_PATH)).toString();
    }

    /// \brief Sets new "java" interpreter path.
    /// \param java_path New path to "java".
    void setJavaInterpreterPath(const QString &java_path) {
      settings()->setValue(APP_CFG_GEN, "java_path", java_path);
    }

    /// \brief Tests if binary in new_path is correct JAVA executable.
    /// \param new_path Path to JAVA executable.
    /// \return Returns specific return code of JAVA executable.
    int checkJava(const QString &new_path = QString());

    /// \brief Tests if binary in new_path is correct SIGNAPK executable.
    /// \param new_path Path to SIGNAPK executable.
    /// \param java_path Path to JAVA executable.
    /// \return Returns specific return code of SIGNAPK executable.
    int checkSignApk(const QString &new_path = QString(), const QString &java_path = QString());

    /// \brief Tests if binary in new_path is correct ZIP executable.
    /// \param new_path Path to ZIP executable.
    /// \return Returns specific return code of ZIP executable.
    int checkZip(const QString &new_path = QString());

    void recheckExternalApplications(bool emit_signals);

    QString interpretJava(int return_code);
    QString interpretZip(int return_code);
    QString interpretSignApk(int return_code);

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
    QList<QAction*> availableActions();

    /// \brief Access to application tray icon.
    /// \return Returns pointer to application tray icon.
    /// \warning Always use this in cooperation with
    /// SystemTrayIcon::isSystemTrayActivated().
    SystemTrayIcon *trayIcon();

    /// \brief Access to template high level manager.
    /// \see TemplateFactory
    TemplateFactory *templateManager();

    /// \brief Main static getter of global Application instance.
    /// \return Returns singleton for Application.
    inline static Application *instance() {
      return static_cast<Application*>(QCoreApplication::instance());
    }

    bool externalApplicationsReady() const;
    QString externalApplicationsStatus() const;
    bool externalApplicationChecked() const;

    /// \brief Application closing indication.
    /// \return Returns true, if application is closing, otherwise returns false.
    bool isClosing() const;

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

  signals:
    /// \brief Emitted if external applications are rechecked which happens
    /// usually if path to some of external application changes.
    void externalApplicationsRechecked();

  private:
    bool m_externalApplicationChecked;
    bool m_externalApplicationsReady;
    QString m_externalApplicationsStatus;
    QMutex *m_closeLock;
    QList<QAction*> m_availableActions;
    Settings *m_settings;
    SkinFactory *m_skinFactory;
    SystemTrayIcon *m_trayIcon;
    FormMain *m_mainForm;
    TemplateFactory *m_templateManager;
    bool m_closing;
};

#endif // APPLICATION_H
