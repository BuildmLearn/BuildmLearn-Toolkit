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

#include "gui/formmain.h"

#include "definitions/definitions.h"
#include "gui/formupdate.h"
#include "gui/formabout.h"
#include "gui/formsettings.h"
#include "gui/systemtrayicon.h"
#include "gui/formhelp.h"
#include "miscellaneous/iconfactory.h"

#include <QStackedWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>


FormMain::FormMain(QWidget *parent) :
  QMainWindow(parent),
  m_firstTimeShow(true),
  m_ui(new Ui::FormMain) {
  m_ui->setupUi(this);

  setupActionShortcuts();
  setupIcons();
  setupTrayMenu();
  setupToolbar();

  createConnections();

  iNewProjectWidget = new FormNewProject(this);
  iNewProjectWidget->setWindowModality(Qt::ApplicationModal);

  iStackedWidget = new QStackedWidget(this);
  iBlankWidget = new QWidget(this);
  iInfoTemplateWidget = new InfoTemplate(this);
  iQuizTemplateWidget = new QuizTemplate(this);
  iFlashCardsWidget = new FlashcardTemplate(this);


  iBlankWidget->setStyleSheet("background-image: url(:/images/banner.png)");


  iStackedWidget->addWidget(iBlankWidget);
  iStackedWidget->addWidget(iInfoTemplateWidget);
  iStackedWidget->addWidget(iQuizTemplateWidget);
  iStackedWidget->addWidget(iFlashCardsWidget);

  iStackedWidget->setCurrentIndex(0);

  setCentralWidget(iStackedWidget);

  connect(iNewProjectWidget, SIGNAL(startProject(int)),
          this, SLOT(startProject(int)));
}

FormMain::~FormMain() {
  delete m_ui;

  qDebug("Destroying FormMain instance.");
}

QHash<QString, QAction *> FormMain::allActions() {
  QHash<QString, QAction*> actions;

  actions.insert(m_ui->m_actionCheckForUpdates->objectName(), m_ui->m_actionCheckForUpdates);
  actions.insert(m_ui->m_actionGenerateApkFile->objectName(), m_ui->m_actionGenerateApkFile);
  actions.insert(m_ui->m_actionLoadProject->objectName(), m_ui->m_actionLoadProject);
  actions.insert(m_ui->m_actionNewProject->objectName(), m_ui->m_actionNewProject);
  actions.insert(m_ui->m_actionSaveProject->objectName(), m_ui->m_actionSaveProject);
  actions.insert(m_ui->m_actionSaveProjectAs->objectName(), m_ui->m_actionSaveProjectAs);
  actions.insert(m_ui->m_actionQuit->objectName(), m_ui->m_actionQuit);
  actions.insert(m_ui->m_actionSettings->objectName(), m_ui->m_actionSettings);
  actions.insert(m_ui->m_actionHelp->objectName(), m_ui->m_actionHelp);

  return actions;
}

void FormMain::createConnections() {
  // General connections.
  connect(m_ui->m_actionQuit, SIGNAL(triggered()),
          qApp, SLOT(quit()));
  connect(m_ui->m_actionCheckForUpdates, SIGNAL(triggered()),
          this, SLOT(showUpdates()));
  connect(m_ui->m_actionAboutToolkit, SIGNAL(triggered()),
          this, SLOT(showAbout()));
  connect(m_ui->m_actionSettings, SIGNAL(triggered()),
          this, SLOT(showSettings()));
  connect(m_ui->m_actionHelp, SIGNAL(triggered()),
          this, SLOT(showHelp()));

  // Project connections.
  connect(m_ui->m_actionNewProject, SIGNAL(triggered()),
          this ,SLOT(newClicked()));
  connect(m_ui->m_actionSaveProject, SIGNAL(triggered()),
          this ,SLOT(saveClicked()));
  connect(m_ui->m_actionLoadProject, SIGNAL(triggered()),
          this ,SLOT(openClicked()));
  connect(m_ui->m_actionGenerateApkFile, SIGNAL(triggered()),
          this ,SLOT(generateClicked()));
}

void FormMain::setupActionShortcuts() {
#if defined(Q_OS_OSX)
  // TODO: Finalize Mac OS X default shortcuts.
  m_ui->m_actionCheckForUpdates->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionGenerateApkFile->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionLoadProject->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionNewProject->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionSaveProject->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionSaveProjectAs->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionQuit->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionSettings->setShortcut(QKeySequence("", QKeySequence::PortableText));
  m_ui->m_actionHelp->setShortcut(QKeySequence("", QKeySequence::PortableText));
#else
  m_ui->m_actionGenerateApkFile->setShortcut(QKeySequence("Ctrl+G", QKeySequence::PortableText));
  m_ui->m_actionLoadProject->setShortcut(QKeySequence("Ctrl+L", QKeySequence::PortableText));
  m_ui->m_actionNewProject->setShortcut(QKeySequence("Ctrl+N", QKeySequence::PortableText));
  m_ui->m_actionSaveProject->setShortcut(QKeySequence("Ctrl+S", QKeySequence::PortableText));
  m_ui->m_actionSaveProjectAs->setShortcut(QKeySequence("Ctrl+Shift+S", QKeySequence::PortableText));
  m_ui->m_actionQuit->setShortcut(QKeySequence("Ctrl+Q", QKeySequence::PortableText));
  m_ui->m_actionSettings->setShortcut(QKeySequence("Ctrl+T", QKeySequence::PortableText));
  m_ui->m_actionHelp->setShortcut(QKeySequence("F1", QKeySequence::PortableText));
#endif
}

void FormMain::setupIcons() {
  IconFactory *factory = IconFactory::instance();

  m_ui->m_actionSettings->setIcon(factory->fromTheme("application-settings"));
  m_ui->m_actionQuit->setIcon(factory->fromTheme("application-exit"));
  m_ui->m_actionAboutToolkit->setIcon(factory->fromTheme("application-about"));
  m_ui->m_actionCheckForUpdates->setIcon(factory->fromTheme("check-for-updates"));
  m_ui->m_actionHelp->setIcon(factory->fromTheme("dialog-question"));
  m_ui->m_actionNewProject->setIcon(factory->fromTheme("project-new"));
  m_ui->m_actionSaveProject->setIcon(factory->fromTheme("project-save"));
  m_ui->m_actionSaveProjectAs->setIcon(factory->fromTheme("project-save-as"));
  m_ui->m_actionLoadProject->setIcon(factory->fromTheme("project-load"));
  m_ui->m_actionGenerateApkFile->setIcon(factory->fromTheme("project-generate"));
}

void FormMain::setupToolbar() {
  m_ui->m_toolBar->addAction(m_ui->m_actionNewProject);
  m_ui->m_toolBar->addAction(m_ui->m_actionLoadProject);
  m_ui->m_toolBar->addAction(m_ui->m_actionSaveProject);
  m_ui->m_toolBar->addAction(m_ui->m_actionSaveProjectAs);
  m_ui->m_toolBar->addSeparator();
  m_ui->m_toolBar->addAction(m_ui->m_actionGenerateApkFile);
  m_ui->m_toolBar->addAction(m_ui->m_actionHelp);
}

void FormMain::setupTrayMenu() {
  if (SystemTrayIcon::isSystemTrayActivated()) {
#if defined(Q_OS_WIN)
    m_trayMenu = new TrayIconMenu(APP_NAME, this);
#else
    m_trayMenu = new QMenu(APP_NAME, this);
#endif

    // Add needed items to the menu.
    m_trayMenu->addAction(m_ui->m_actionCheckForUpdates);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(m_ui->m_actionQuit);

    qDebug("Creating tray icon menu.");
  }
}

void FormMain::showSettings() {
  QPointer<FormSettings> form_pointer = new FormSettings(this);
  form_pointer.data()->exec();
  delete form_pointer.data();
}

void FormMain::showAbout() {
  QPointer<FormAbout> form_about = new FormAbout(this);
  form_about.data()->exec();
  delete form_about.data();
}

void FormMain::showUpdates() {
  QPointer<FormUpdate> form_update = new FormUpdate(this);
  form_update.data()->exec();
  delete form_update.data();
}

void FormMain::showHelp(bool enable_do_not_show_again_option) {
  QPointer<FormHelp> form_help = new FormHelp(enable_do_not_show_again_option, this);
  form_help.data()->exec();
  delete form_help.data();
}

void FormMain::showUpdatesAfterBubbleClick() {
  display();
  showUpdates();
}

void FormMain::switchVisibility(bool force_hide) {
  if (force_hide || isVisible()) {
    if (SystemTrayIcon::isSystemTrayActivated()) {
      hide();
    }
    else {
      // Window gets minimized in single-window mode.
      showMinimized();
    }
  }
  else {
    display();
  }
}

void FormMain::show() {
  QMainWindow::show();

  if (m_firstTimeShow) {
    m_firstTimeShow = false;

    if (qApp->settings()->value(APP_CFG_GUI, "show_help_startup", true).toBool()) {
      showHelp(true);
    }
  }
}

void FormMain::display() {
  // Make sure window is not minimized.
  setWindowState(windowState() & ~Qt::WindowMinimized);

  // Display the window and make sure it is raised on top.
  show();
  activateWindow();
  raise();

  // Raise alert event. Check the documentation for more info on this.
  Application::alert(this);
}

void FormMain::saveClicked()
{
  if (iStackedWidget->currentIndex()==0)
  {
    QMessageBox::information(this,"Generate application" , "Please create an application first!");
  }
  else if (iStackedWidget->currentIndex()==1)
  {
    ((InfoTemplate*)iStackedWidget->currentWidget())->on_save_clicked();
  }
  else if (iStackedWidget->currentIndex()==2)
  {
    ((QuizTemplate*)iStackedWidget->currentWidget())->on_save_clicked();
  }
  else if (iStackedWidget->currentIndex()==3)
  {
    ((FlashcardTemplate*)iStackedWidget->currentWidget())->on_save_clicked();
  }
}

void FormMain::openClicked()
{
  if (iStackedWidget->currentIndex() !=0)
  {
    if (QMessageBox::Yes == QMessageBox::question(this, "Discard current project?", "Choosing a new project would discard your current project. Are you sure to continue?", QMessageBox::Yes|QMessageBox::No))
    {
      // reseting other widgets
      resetWidgets();
      loadOpenFile();
    }
  }
  else{
    resetWidgets();
    loadOpenFile();
  }
  iNewProjectWidget->hide();


}

void FormMain::loadOpenFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "",tr("*.buildmlearn"));
  QFile indexFile(fileName);
  indexFile.open(QIODevice::ReadOnly);

  QString data = indexFile.readAll();
  indexFile.close();
  QStringList dataList = data.split(DELIMITER_LINE);
  qDebug()<<dataList;

  QString selectedTemplate = dataList.first();
  dataList.removeFirst();

  qDebug()<<selectedTemplate.compare("QuizTemplate");

  if (selectedTemplate.compare("InfoTemplate")==0)
  {
    iInfoTemplateWidget->on_open_clicked(dataList);
    iStackedWidget->setCurrentIndex(1);
  }
  else if (selectedTemplate.compare("QuizTemplate")==0)
  {
    iQuizTemplateWidget->on_open_clicked(dataList);
    iStackedWidget->setCurrentIndex(2);
  }
  else if (selectedTemplate.compare("FlashCardsTemplate")==0)
  {
    iFlashCardsWidget->on_open_clicked(dataList);
    iStackedWidget->setCurrentIndex(3);
  }

}

void FormMain::newClicked()
{
  if (iStackedWidget->currentIndex() !=0)
  {
    if (QMessageBox::Yes == QMessageBox::question(this, "Discard current project?", "Choosing a new project would discard your current project. Are you sure to continue?", QMessageBox::Yes|QMessageBox::No))
    {
      iStackedWidget->setCurrentIndex(0);
      iNewProjectWidget->show();

      // reseting other widgets
      resetWidgets();
    }
  }
  else if (!iNewProjectWidget->isVisible())
  {
    iNewProjectWidget->show();
  }
}

void FormMain::generateClicked()
{
  if (iStackedWidget->currentIndex()==0)
  {
    QMessageBox::information(this,"Generate application" , "Please create a project first!");
  }
  else if (iStackedWidget->currentIndex()==1)
  {
    ((InfoTemplate*)iStackedWidget->currentWidget())->on_generateButton_clicked();
  }
  else if (iStackedWidget->currentIndex()==2)
  {
    ((QuizTemplate*)iStackedWidget->currentWidget())->on_generateButton_clicked();
  }
  else if (iStackedWidget->currentIndex()==3)
  {
    ((FlashcardTemplate*)iStackedWidget->currentWidget())->on_generateButton_clicked();
  }
}

void FormMain::startProject(int index)
{
  if (index == -1)
  {
    // if Open clicked from the New project dialog
    openClicked();
    return;
  }

  //qDebug()<<"Project number selected: " + index;
  iStackedWidget->setCurrentIndex(index+1);
  if (index==1)
  {
    // if Quiz template is selected
    bool ok;
    iQuizTemplateWidget->quizName = QInputDialog::getText(this, "Enter quiz name",
                                                          "Quiz Name:", QLineEdit::Normal,
                                                          "", &ok);
    if (!ok || iQuizTemplateWidget->quizName.isEmpty())
    {
      return;
    }

    ok = false;
    iQuizTemplateWidget->authorName = QInputDialog::getText(this, "Enter author name",
                                                            "Quiz author:", QLineEdit::Normal,
                                                            "", &ok);
    if (!ok || iQuizTemplateWidget->authorName.isEmpty())
    {
      return;
    }

    iQuizTemplateWidget->updateStartPage_phone();
  }
  else if (index==2)
  {
    // if Flashcards template is selected
    bool ok;
    iFlashCardsWidget->quizName = QInputDialog::getText(this, "Enter the name of the Flashcards collection",
                                                        "Colllection's' Name:", QLineEdit::Normal,
                                                        "", &ok);
    if (!ok || iFlashCardsWidget->quizName.isEmpty())
    {
      return;
    }

    ok = false;
    iFlashCardsWidget->authorName = QInputDialog::getText(this, "Enter author name",
                                                          "Flashcards author:", QLineEdit::Normal,
                                                          "", &ok);
    if (!ok || iFlashCardsWidget->authorName.isEmpty())
    {
      return;
    }

    iFlashCardsWidget->updateStartPage_phone();
  }
}
void FormMain::resetWidgets()
{
  iStackedWidget->removeWidget(iFlashCardsWidget);
  iStackedWidget->removeWidget(iQuizTemplateWidget);
  iStackedWidget->removeWidget(iInfoTemplateWidget);

  iInfoTemplateWidget = new InfoTemplate(this);
  iQuizTemplateWidget = new QuizTemplate(this);
  iFlashCardsWidget = new FlashcardTemplate(this);

  iStackedWidget->addWidget(iInfoTemplateWidget);
  iStackedWidget->addWidget(iQuizTemplateWidget);
  iStackedWidget->addWidget(iFlashCardsWidget);
}

void FormMain::closeEvent(QCloseEvent *event) {
  if (SystemTrayIcon::isSystemTrayActivated()) {
    qApp->trayIcon()->hide();
  }

  event->accept();
  qApp->quit();
}
