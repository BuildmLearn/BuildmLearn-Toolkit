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
#include "gui/formsimulator.h"
#include "gui/formnewproject.h"
#include "gui/custommessagebox.h"
#include "gui/formuploadbundle.h"
#include "miscellaneous/iconfactory.h"
#include "core/templatesimulator.h"
#include "core/templatefactory.h"
#include "core/templateentrypoint.h"
#include "core/templateeditor.h"
#include "core/templategenerator.h"
#include "templates/quiz/quizentrypoint.h"

#include <QStackedWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QLayoutItem>
#include <QProgressBar>
#include <QScrollArea>


FormMain::FormMain(QWidget *parent)
  : QMainWindow(parent),
    m_statusProgress(new QProgressBar(this)),
    m_statusLabel(new QLabel(this)),
    m_centralArea(new QScrollArea(this)),
    m_centralLayout(new QVBoxLayout(m_centralArea)),
    m_firstTimeShow(true),
    m_ui(new Ui::FormMain),
    m_simulatorWindow(NULL) {
  m_ui->setupUi(this);

  m_normalTitle = APP_LONG_NAME;
  m_unsavedTitle = m_normalTitle + " *";

  m_statusProgress->setFixedHeight(m_ui->m_statusBar->sizeHint().height());

  // Addd necessary widgets to status.
  m_ui->m_statusBar->addWidget(m_statusProgress);
  m_ui->m_statusBar->addWidget(m_statusLabel, 1);
  m_statusLabel->setVisible(false);
  m_statusProgress->setVisible(false);

  setWindowTitle(m_normalTitle);

  // Disable "maximize" button.
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

  m_centralArea->setFrameStyle(QFrame::NoFrame);

  setCentralWidget(m_centralArea);
  setupSimulatorWindow();
  setupActionShortcuts();
  setupIcons();
  setupTrayMenu();
  setupToolbar();
  loadSizeAndPosition();

  createConnections();

  // Make sure simulator window is displayed.
  m_ui->m_actionViewSimulatorWindow->setChecked(m_simulatorWindow->isVisibleOnStartup());
  m_ui->m_actionStickSimulatorWindow->setChecked(m_simulatorWindow->isSticked());
}

FormMain::~FormMain() {
  delete m_ui;

  qDebug("Destroying FormMain instance.");
}

QList<QAction*> FormMain::allActions() {
  QList<QAction*> actions;

  actions.append(m_ui->m_actionCheckForUpdates);
  actions.append(m_ui->m_actionGenerateMobileApplication);
  actions.append(m_ui->m_actionUploadApplicationToStore);
  actions.append(m_ui->m_actionLoadProject);
  actions.append(m_ui->m_actionNewProject);
  actions.append(m_ui->m_actionSaveProject);
  actions.append(m_ui->m_actionSaveProjectAs);
  actions.append(m_ui->m_actionSimulatorRun);
  actions.append(m_ui->m_actionSimulatorStop);
  actions.append(m_ui->m_actionSimulatorGoBack);
  actions.append(m_ui->m_actionViewSimulatorWindow);
  actions.append(m_ui->m_actionStickSimulatorWindow);
  actions.append(m_ui->m_actionQuit);
  actions.append( m_ui->m_actionSettings);
  actions.append(m_ui->m_actionHelp);

  return actions;
}

void FormMain::setupSimulatorWindow() {
  m_simulatorWindow = new FormSimulator(this);
}

void FormMain::createConnections() {
  // General connections.
  connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
  connect(m_ui->m_actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(m_ui->m_actionCheckForUpdates, SIGNAL(triggered()), this, SLOT(showUpdates()));
  connect(m_ui->m_actionAboutToolkit, SIGNAL(triggered()), this, SLOT(showAbout()));
  connect(m_ui->m_actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
  connect(m_ui->m_actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));

  // View connections.
  connect(m_ui->m_actionViewSimulatorWindow, SIGNAL(toggled(bool)), this, SLOT(switchSimulatorWindow(bool)));
  connect(m_ui->m_actionStickSimulatorWindow, SIGNAL(toggled(bool)), m_simulatorWindow, SLOT(setIsSticked(bool)));

  // Extra simulator connections.
  connect(m_simulatorWindow, SIGNAL(closed()), this, SLOT(onSimulatorWindowClosed()));
  connect(m_simulatorWindow, SIGNAL(stopEnableChanged(bool)), m_ui->m_actionSimulatorStop, SLOT(setEnabled(bool)));
  connect(m_ui->m_actionSimulatorStop, SIGNAL(triggered()), m_simulatorWindow->m_ui->m_btnStopSimulation, SLOT(click()));
  connect(m_ui->m_actionSimulatorRun, SIGNAL(triggered()), this, SLOT(startSimulation()));
  connect(m_ui->m_actionSimulatorGoBack, SIGNAL(triggered()), this, SLOT(takeSimulationOneStepBack()));

  // Project connections.
  connect(m_ui->m_actionNewProject, SIGNAL(triggered()), this ,SLOT(openNewProjectDialog()));
  connect(m_ui->m_actionSaveProject, SIGNAL(triggered()), this ,SLOT(openSaveProjectDialog()));
  connect(m_ui->m_actionSaveProjectAs, SIGNAL(triggered()), this, SLOT(openSaveProjectAsDialog()));
  connect(m_ui->m_actionLoadProject, SIGNAL(triggered()), this ,SLOT(openLoadProjectDialog()));
  connect(m_ui->m_actionOpenOutputDirectory, SIGNAL(triggered()), this, SLOT(openOutputDirectory()));

  // Template system connections.
  connect(qApp->templateManager(), SIGNAL(newTemplateCoreCreated(TemplateCore*)), this, SLOT(setTemplateCore(TemplateCore*)));
  connect(qApp, SIGNAL(externalApplicationsRechecked()), this, SLOT(onExternalApplicationsChanged()));
  connect(m_ui->m_actionGenerateMobileApplication, SIGNAL(triggered()), this, SLOT(generateMobileApplication()));
  connect(m_ui->m_actionUploadApplicationToStore, SIGNAL(triggered()), this, SLOT(uploadMobileApplicationToStore()));
  connect(qApp->templateManager()->generator(), SIGNAL(generationStarted()), this, SLOT(onGenerationStarted()));
  connect(qApp->templateManager()->generator(), SIGNAL(generationFinished(TemplateCore::GenerationResult,QString)),
          this, SLOT(onGenerationDone(TemplateCore::GenerationResult,QString)));
  connect(qApp->templateManager()->generator(), SIGNAL(generationProgress(int,QString)), this, SLOT(onGenerationProgress(int,QString)));
}

void FormMain::setupActionShortcuts() {
  m_ui->m_actionGenerateMobileApplication->setShortcut(QKeySequence("Ctrl+G", QKeySequence::PortableText));
  m_ui->m_actionLoadProject->setShortcut(QKeySequence("Ctrl+L", QKeySequence::PortableText));
  m_ui->m_actionNewProject->setShortcut(QKeySequence("Ctrl+N", QKeySequence::PortableText));
  m_ui->m_actionSaveProject->setShortcut(QKeySequence("Ctrl+S", QKeySequence::PortableText));
  m_ui->m_actionSaveProjectAs->setShortcut(QKeySequence("Ctrl+Shift+S", QKeySequence::PortableText));
  m_ui->m_actionQuit->setShortcut(QKeySequence("Ctrl+Q", QKeySequence::PortableText));
  m_ui->m_actionSettings->setShortcut(QKeySequence("Ctrl+T", QKeySequence::PortableText));
  m_ui->m_actionHelp->setShortcut(QKeySequence("F1", QKeySequence::PortableText));
  m_ui->m_actionOpenOutputDirectory->setShortcut(QKeySequence("Ctrl+D", QKeySequence::PortableText));
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
  m_ui->m_actionGenerateMobileApplication->setIcon(factory->fromTheme("project-generate"));
  m_ui->m_menuSimulatorWindow->setIcon(factory->fromTheme("view-simulator"));
  m_ui->m_actionStickSimulatorWindow->setIcon(factory->fromTheme("simulation-stick"));
  m_ui->m_actionViewSimulatorWindow->setIcon(factory->fromTheme("view-simulator"));
  m_ui->m_actionSimulatorRun->setIcon(factory->fromTheme("simulation-run"));
  m_ui->m_actionSimulatorStop->setIcon(factory->fromTheme("simulation-stop"));
  m_ui->m_actionSimulatorGoBack->setIcon(factory->fromTheme("simulation-back"));
  m_ui->m_actionOpenOutputDirectory->setIcon(factory->fromTheme("view-output"));
}

void FormMain::setupToolbar() {
  m_ui->m_toolBar->setWindowTitle(tr("Main toolbar"));

  m_ui->m_toolBar->addAction(m_ui->m_actionNewProject);
  m_ui->m_toolBar->addAction(m_ui->m_actionLoadProject);
  m_ui->m_toolBar->addAction(m_ui->m_actionSaveProject);
  m_ui->m_toolBar->addAction(m_ui->m_actionSaveProjectAs);
  m_ui->m_toolBar->addSeparator();
  m_ui->m_toolBar->addAction(m_ui->m_actionSimulatorRun);
  m_ui->m_toolBar->addAction(m_ui->m_actionSimulatorStop);
  m_ui->m_toolBar->addAction(m_ui->m_actionSimulatorGoBack);
  m_ui->m_toolBar->addAction(m_ui->m_actionGenerateMobileApplication);
  m_ui->m_toolBar->addAction(m_ui->m_actionUploadApplicationToStore);
  m_ui->m_toolBar->addAction(m_ui->m_actionHelp);
}

void FormMain::setupTrayMenu() {
  if (SystemTrayIcon::isSystemTrayAvailable()) {
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

void FormMain::loadSizeAndPosition() {
  QRect screen = qApp->desktop()->screenGeometry();
  QRect windows = rect();
  Settings *settings = qApp->settings();

  windows.setWidth(windows.width() + m_simulatorWindow->width());

  // Reload main window size & position.
  resize(settings->value(APP_CFG_GUI, "window_size", size()).toSize());
  move(settings->value(APP_CFG_GUI, "window_position", screen.center() - windows.center()).toPoint());

  // Load visual state of simulator window.
  m_simulatorWindow->loadState();
}

void FormMain::saveSizeAndPosition() {
  Settings *settings = qApp->settings();

  settings->setValue(APP_CFG_GUI, "window_position", pos());
  settings->setValue(APP_CFG_GUI, "window_size", size());

  // Save visual state of simulator window.
  m_simulatorWindow->saveState();
}

void FormMain::quit()
{

}

void FormMain::startSimulation() {
  showSimulator();
  QTimer::singleShot(0, m_simulatorWindow, SLOT(startSimulation()));
}

void FormMain::takeSimulationOneStepBack() {
  showSimulator();
  QTimer::singleShot(0, m_simulatorWindow, SLOT(goBack()));
}

void FormMain::onCanGenerateChanged(bool can_generate, const QString &informative_text) {
  if (can_generate) {
    // Editor of active template can generate applications.
    if (!qApp->externalApplicationChecked()) {
      qApp->recheckExternalApplications(false);
    }

    if (!qApp->externalApplicationsReady()) {
      m_ui->m_actionGenerateMobileApplication->setEnabled(false);
      m_ui->m_actionGenerateMobileApplication->setToolTip(qApp->externalApplicationsStatus());
    }
    else {
      // All external generators are set, template is ready, we can generate.
      m_ui->m_actionGenerateMobileApplication->setEnabled(true);
      m_ui->m_actionGenerateMobileApplication->setToolTip(tr("Generate mobile application"));
    }

    m_ui->m_actionUploadApplicationToStore->setEnabled(true);
    m_ui->m_actionUploadApplicationToStore->setToolTip(tr("Upload mobile application to store"));
    m_ui->m_actionSimulatorRun->setEnabled(true);
    m_ui->m_actionSimulatorRun->setToolTip(tr("Start new simulation"));
  }
  else {
    // Editor of active template cannot generate applications.
    m_ui->m_actionUploadApplicationToStore->setEnabled(false);
    m_ui->m_actionUploadApplicationToStore->setToolTip(informative_text);
    m_ui->m_actionGenerateMobileApplication->setEnabled(can_generate);
    m_ui->m_actionGenerateMobileApplication->setToolTip(qApp->externalApplicationsStatus());
    m_ui->m_actionSimulatorRun->setEnabled(can_generate);
    m_ui->m_actionSimulatorRun->setToolTip(informative_text);
  }
}

void FormMain::onExternalApplicationsChanged() {
  if (qApp->templateManager()->activeCore() != NULL) {
    TemplateEditor *active_editor = qApp->templateManager()->activeCore()->editor();

    onCanGenerateChanged(active_editor->canGenerateApplications(),
                         active_editor->generationStatusDescription());
  }
  else {
    // There is no active template, thus no simulations can be started
    // but still update generator buttons.
    onCanGenerateChanged(false, QString());
  }
}

void FormMain::onEditorChanged() {
  setWindowTitle(m_unsavedTitle);

  TemplateCore *current_core = static_cast<TemplateEditor*>(sender())->core();

  if (current_core->assignedFile().isEmpty()) {
    // Template which was already saved or is loaded
    // from XML bundle file has changed its state
    // and is now unsaved.
    m_ui->m_actionSaveProjectAs->setEnabled(true);
    m_ui->m_actionSaveProject->setEnabled(true);
  }
  else {
    // Template from new project has changed.
    m_ui->m_actionSaveProjectAs->setEnabled(true);
    m_ui->m_actionSaveProject->setEnabled(true);
  }
}

void FormMain::onGenerationProgress(int percentage_completed, const QString &message) {
  qApp->processEvents();

  m_statusLabel->setText(message);
  m_statusLabel->setVisible(true);
  m_statusProgress->setValue(percentage_completed);
  m_statusProgress->setVisible(true);
}

void FormMain::onGenerationStarted() {
  qApp->processEvents();

  m_ui->m_actionGenerateMobileApplication->setEnabled(false);
}

void FormMain::onGenerationDone(TemplateCore::GenerationResult result_code, const QString &output_file) {
  qApp->processEvents();

  m_generatedApplicationPath = output_file;

  if (qApp->templateManager()->activeCore() != NULL) {
    m_ui->m_actionGenerateMobileApplication->setEnabled(qApp->templateManager()->activeCore()->editor()->canGenerateApplications());
  }
  else {
    m_ui->m_actionGenerateMobileApplication->setEnabled(false);
  }

  m_statusLabel->clear();
  m_statusLabel->setVisible(false);
  m_statusProgress->setValue(0);
  m_statusProgress->setVisible(false);

  // TODO: Print information about result.
  switch (result_code) {
    case TemplateCore::Success:
      qApp->trayIcon()->showMessage(tr("Mobile application generated"),
                              #if defined(Q_OS_WIN32)
                                    tr("Click here to open its location."),
                              #else
                                    tr("Click here to copy output path to clipboard."),
                              #endif
                                    QSystemTrayIcon::Information,
                                    20000,
                                    this,
                                    SLOT(openOutputApplication()));
      break;

    case TemplateCore::Aborted:
      // Supress abortion state because this is not critical state.
      break;

    default:
      qApp->trayIcon()->showMessage(tr("Mobile application not generated"),
                                    tr("Application was NOT generated successfully."),
                                    QSystemTrayIcon::Critical);
      break;
  }
}

void FormMain::openOutputApplication() {
#if defined(Q_OS_WIN32)
  // Open explorer window with target path.
  QProcess::startDetached("explorer", QStringList() << "/select,"  << QDir::toNativeSeparators(m_generatedApplicationPath));
#else
  // Copy target path to clipboard.
  QApplication::clipboard()->setText(m_generatedApplicationPath);
#endif

  m_generatedApplicationPath = QString();
}

void FormMain::openOutputDirectory() {
#if defined(Q_OS_WIN32)
  // Open explorer window with target path.
  QProcess::startDetached("explorer", QStringList() << "/root,"  << QDir::toNativeSeparators(qApp->templateManager()->outputDirectory()));
#else
  // Copy target path to clipboard.
  // TODO: Better handling here and add action icon.
  QMessageBox::information(this, tr("Cannot open directory"), tr("Directory was copied into your clipboard."));
  QApplication::clipboard()->setText(qApp->templateManager()->outputDirectory());
#endif
}

void FormMain::setTemplateCore(TemplateCore *core) {
  setWindowTitle(m_normalTitle);

  // Set editor widget as central widget of main window
  // and setup simulator stuff.
  TemplateEditor *editor = core->editor();
  TemplateSimulator *simulator = core->simulator();

  // Clear previous editor if any.
  while (m_centralLayout->count() > 0) {
    QLayoutItem *item = m_centralLayout->itemAt(0);

    item->widget()->deleteLater();
    m_centralLayout->removeItem(item);

    delete item;
  }

  // Set editor part.
  m_centralLayout->layout()->addWidget(editor);
  editor->setParent(m_centralArea);

  connect(editor, SIGNAL(changed()), this, SLOT(onEditorChanged()));
  connect(editor, SIGNAL(canGenerateChanged(bool,QString)), this, SLOT(onCanGenerateChanged(bool,QString)));
  connect(simulator, SIGNAL(canGoBackChanged(bool)), m_ui->m_actionSimulatorGoBack, SLOT(setEnabled(bool)));

  // Set simulator part.
  m_simulatorWindow->setActiveSimulation(simulator);

  // Now, new template editor is set and simulator is set. Launch the template.
  core->launch();
}

void FormMain::onAboutToQuit() { 
  // Save all necessary things before application exits.
  saveSizeAndPosition();
}

void FormMain::onSimulatorWindowClosed() {
  m_ui->m_actionViewSimulatorWindow->setChecked(false);
}

void FormMain::switchSimulatorWindow(bool show) {
  if (show) {
    m_simulatorWindow->show();
  }
  else {
    m_simulatorWindow->close();
  }
}

void FormMain::showSimulator() {
  if (!m_ui->m_actionViewSimulatorWindow->isChecked()) {
    m_ui->m_actionViewSimulatorWindow->setChecked(true);
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
    if (SystemTrayIcon::isSystemTrayAvailable()) {
      hide();
      m_simulatorWindow->hide();
    }
    else {
      // Window gets minimized in single-window mode.
      showMinimized();
    }
  }
  else {
    display();

    if (SystemTrayIcon::isSystemTrayAvailable()) {
      m_simulatorWindow->show();
    }
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

void FormMain::openSaveProjectDialog() {
  if (qApp->templateManager()->activeCore()->assignedFile().isEmpty()) {
    // This project was not saved/loaded before, se we need to use "Save as..."
    // feature.
    openSaveProjectAsDialog();
  }
  else {
    if (qApp->templateManager()->saveCurrentProject()) {
      // Everything saved OK.
      m_ui->m_actionSaveProject->setEnabled(false);
      setWindowTitle(m_normalTitle);
    }
    else {
      // TODO:
    }
  }
}

void FormMain::openSaveProjectAsDialog() {
  QString selected_file = QFileDialog::getSaveFileName(this,
                                                       tr("Select destination file for the project"),
                                                       qApp->templateManager()->activeCore()->assignedFile(),
                                                       tr("BuildmLearn Toolkit projects (*.buildmlearn)"),
                                                       0);

  if (!selected_file.isEmpty()) {
    if (qApp->templateManager()->saveCurrentProjectAs(selected_file)) {
      // Everything saved OK.
      m_ui->m_actionSaveProject->setEnabled(false);
      setWindowTitle(m_normalTitle);
    }
    else {
      // TODO:
    }
  }
}

void FormMain::openLoadProjectDialog() {
  if (!saveUnsavedProject()) {
    return;
  }

  QString selected_file = QFileDialog::getOpenFileName(this,
                                                       tr("Select destination file for the project"),
                                                       QDir::homePath(),
                                                       tr("BuildmLearn Toolkit projects (*.buildmlearn)"),
                                                       0);

  if (selected_file.isEmpty()) {
    return;
  }

  if (qApp->templateManager()->loadProject(selected_file)) {
    m_ui->m_actionSaveProjectAs->setEnabled(true);
    m_ui->m_actionSaveProject->setEnabled(false);
  }
}

void FormMain::openNewProjectDialog() {
  if (!saveUnsavedProject()) {
    return;
  }

  QPointer<FormNewProject> form_new_project = new FormNewProject(qApp->templateManager(), this);
  TemplateEntryPoint *entry_point = form_new_project.data()->startNewTemplate();

  delete form_new_project.data();

  if (entry_point != NULL) {
    // User selected proper template to start with.
    // Load the template.
    qApp->templateManager()->startNewProject(entry_point);
  }
}

void FormMain::generateMobileApplication() {
  if (qApp->templateManager()->activeCore() != NULL) {
    qApp->templateManager()->generator()->generateMobileApplication(qApp->templateManager()->activeCore());
  }
  else {
    QMessageBox::warning(this,
                         tr("Cannot generate application"),
                         tr("No project is opened, thus, cannot generate application."));
  }
}

void FormMain::uploadMobileApplicationToStore() {
  QPointer<FormUploadBundle> form_pointer = new FormUploadBundle(this);
  form_pointer.data()->exec();
  delete form_pointer.data();
}

bool FormMain::saveUnsavedProject() {
  if (qApp->templateManager()->activeCore() != NULL) {
    if (qApp->templateManager()->activeCore()->editor()->isDirty()) {
      QMessageBox::StandardButton decision = CustomMessageBox::show(this,
                                                                    QMessageBox::Warning,
                                                                    tr("Unsaved work"),
                                                                    tr("There is unsaved project. You might want to save your current project, unless you do not mind losing your unsaved work."),
                                                                    tr("Do you want to save your unsaved project before proceeding?"), QString(),
                                                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                                                    QMessageBox::Yes);

      switch (decision) {
        case QMessageBox::Yes:
          openSaveProjectDialog();
          return true;

        case QMessageBox::No:
          return true;

        case QMessageBox::Cancel:
        default:
          return false;
      }
    }
  }

  return true;
}

void FormMain::closeEvent(QCloseEvent *e) {
  if (!qApp->isClosing()) {
    if (!saveUnsavedProject()) {
      e->ignore();
      return;
    }
  }

  if (SystemTrayIcon::isSystemTrayAvailable()) {
    qApp->trayIcon()->hide();
  }

  e->accept();
  qApp->quit();
}

void FormMain::moveEvent(QMoveEvent *e) {
  e->accept();
  emit moved();
}

void FormMain::resizeEvent(QResizeEvent *e) {
  e->accept();
  emit resized();
}
