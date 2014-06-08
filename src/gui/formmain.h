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

#ifndef FORMMAIN_H
#define FORMMAIN_H

#include "ui_formmain.h"

#include "gui/formnewproject.h"

#include "InfoTemplate.h"
#include "QuizTemplate.h"
#include "FlashcardTemplate.h"

#include <QMainWindow>
#include <QHash>
#include <QtGui>


namespace Ui {
 class FormMain;
}

class FormSimulator;

/// \brief Main application window.
class FormMain : public QMainWindow {
    Q_OBJECT
    
  public:
    /// \brief Constructor.
    /// \param parent Parent widget.
    explicit FormMain(QWidget *parent = 0);
    virtual ~FormMain();

    /// \brief Access to tray menu.
    /// \see SystemTrayIcon
    inline QMenu *trayMenu() const {
      return m_trayMenu;
    }

    /// \brief Access to simulator window.
    /// \see FormSimulator
    inline FormSimulator *simulatorWindow() const {
      return m_simulatorWindow;
    }

    /// \brief Access to all actions provided by this window.
    /// \see DynamicShortcuts
    QHash<QString, QAction*> allActions();

  private:
    void createConnections();
    void setupSimulatorWindow();
    void setupActionShortcuts();
    void setupIcons();
    void setupToolbar();
    void setupTrayMenu();

    void loadSizeAndPosition();
    void saveSizeAndPosition();

  private slots:
    void onAboutToQuit();
    void onSimulatorWindowClosed();
    void switchSimulatorWindow(bool show);

    void showSettings();
    void showAbout();
    void showUpdates();
    void showHelp(bool enable_do_not_show_again_option = false);
    void showUpdatesAfterBubbleClick();

  public slots:
    /// \brief Switches visibility of main window.
    /// \param force_hide If true, then window is not switched but hidden.
    void switchVisibility(bool force_hide = false);

    /// \brief Displays window.
    /// \see display(), switchVisibility()
    void show();

    /// \brief Displays the window.
    /// \see show()
    void display();

    void startProject(int);
    void generateClicked();
    void newClicked();
    void saveClicked();
    void openClicked();
    void loadOpenFile();
    void resetWidgets();

  protected:
    /// \brief Executed when main application window is closed.
    /// \param e Event message.
    void closeEvent(QCloseEvent *e);

    /// \brief Executed when window is moved.
    /// \param e Event message.
    void moveEvent(QMoveEvent *e);

  private:
    bool m_firstTimeShow;
    Ui::FormMain *m_ui;
    QMenu *m_trayMenu;

    FormSimulator *m_simulatorWindow;

    // Other widgets
    QStackedWidget* iStackedWidget;

    // Create NewProject Widget
    FormNewProject *iNewProjectWidget;

    //  Blank widget
    QWidget* iBlankWidget;
    // Create InfoTemplate Widget
    InfoTemplate* iInfoTemplateWidget;
    // Create QuizTemplate Widget
    QuizTemplate* iQuizTemplateWidget;
    // Create Flashcards Widget
    FlashcardTemplate* iFlashCardsWidget;
};

#endif // FORMMAIN_H
