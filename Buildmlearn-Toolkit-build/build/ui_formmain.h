/********************************************************************************
** Form generated from reading UI file 'formmain.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMAIN_H
#define UI_FORMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormMain
{
public:
    QAction *m_actionCheckForUpdates;
    QAction *m_actionAboutToolkit;
    QAction *m_actionQuit;
    QAction *m_actionGenerateMobileApplication;
    QAction *m_actionNewProject;
    QAction *m_actionSaveProject;
    QAction *m_actionSaveProjectAs;
    QAction *m_actionLoadProject;
    QAction *m_actionSettings;
    QAction *m_actionHelp;
    QAction *m_actionViewSimulatorWindow;
    QAction *m_actionStickSimulatorWindow;
    QAction *m_actionSimulatorRun;
    QAction *m_actionSimulatorGoBack;
    QAction *m_actionSimulatorStop;
    QAction *m_actionOpenOutputDirectory;
    QAction *m_actionUploadApplicationToStore;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *m_menuBar;
    QMenu *m_menuHelp;
    QMenu *m_menuProject;
    QMenu *m_menuTools;
    QMenu *m_menuView;
    QMenu *m_menuSimulatorWindow;
    QMenu *menu_Simulator;
    QToolBar *m_toolBar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *FormMain)
    {
        if (FormMain->objectName().isEmpty())
            FormMain->setObjectName(QStringLiteral("FormMain"));
        FormMain->resize(650, 600);
        FormMain->setUnifiedTitleAndToolBarOnMac(true);
        m_actionCheckForUpdates = new QAction(FormMain);
        m_actionCheckForUpdates->setObjectName(QStringLiteral("m_actionCheckForUpdates"));
        m_actionCheckForUpdates->setShortcutContext(Qt::ApplicationShortcut);
        m_actionAboutToolkit = new QAction(FormMain);
        m_actionAboutToolkit->setObjectName(QStringLiteral("m_actionAboutToolkit"));
        m_actionAboutToolkit->setShortcutContext(Qt::ApplicationShortcut);
        m_actionQuit = new QAction(FormMain);
        m_actionQuit->setObjectName(QStringLiteral("m_actionQuit"));
        m_actionQuit->setShortcut(QStringLiteral(""));
        m_actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        m_actionGenerateMobileApplication = new QAction(FormMain);
        m_actionGenerateMobileApplication->setObjectName(QStringLiteral("m_actionGenerateMobileApplication"));
        m_actionGenerateMobileApplication->setEnabled(false);
        m_actionGenerateMobileApplication->setShortcutContext(Qt::ApplicationShortcut);
        m_actionNewProject = new QAction(FormMain);
        m_actionNewProject->setObjectName(QStringLiteral("m_actionNewProject"));
        m_actionNewProject->setShortcutContext(Qt::ApplicationShortcut);
        m_actionSaveProject = new QAction(FormMain);
        m_actionSaveProject->setObjectName(QStringLiteral("m_actionSaveProject"));
        m_actionSaveProject->setEnabled(false);
        m_actionSaveProject->setShortcut(QStringLiteral(""));
        m_actionSaveProject->setShortcutContext(Qt::ApplicationShortcut);
        m_actionSaveProjectAs = new QAction(FormMain);
        m_actionSaveProjectAs->setObjectName(QStringLiteral("m_actionSaveProjectAs"));
        m_actionSaveProjectAs->setEnabled(false);
        m_actionSaveProjectAs->setShortcutContext(Qt::ApplicationShortcut);
        m_actionLoadProject = new QAction(FormMain);
        m_actionLoadProject->setObjectName(QStringLiteral("m_actionLoadProject"));
        m_actionLoadProject->setShortcut(QStringLiteral(""));
        m_actionLoadProject->setShortcutContext(Qt::ApplicationShortcut);
        m_actionSettings = new QAction(FormMain);
        m_actionSettings->setObjectName(QStringLiteral("m_actionSettings"));
        m_actionSettings->setShortcut(QStringLiteral(""));
        m_actionSettings->setShortcutContext(Qt::ApplicationShortcut);
        m_actionHelp = new QAction(FormMain);
        m_actionHelp->setObjectName(QStringLiteral("m_actionHelp"));
        m_actionHelp->setShortcut(QStringLiteral(""));
        m_actionHelp->setShortcutContext(Qt::ApplicationShortcut);
        m_actionViewSimulatorWindow = new QAction(FormMain);
        m_actionViewSimulatorWindow->setObjectName(QStringLiteral("m_actionViewSimulatorWindow"));
        m_actionViewSimulatorWindow->setCheckable(true);
        m_actionStickSimulatorWindow = new QAction(FormMain);
        m_actionStickSimulatorWindow->setObjectName(QStringLiteral("m_actionStickSimulatorWindow"));
        m_actionStickSimulatorWindow->setCheckable(true);
        m_actionSimulatorRun = new QAction(FormMain);
        m_actionSimulatorRun->setObjectName(QStringLiteral("m_actionSimulatorRun"));
        m_actionSimulatorRun->setEnabled(false);
        m_actionSimulatorGoBack = new QAction(FormMain);
        m_actionSimulatorGoBack->setObjectName(QStringLiteral("m_actionSimulatorGoBack"));
        m_actionSimulatorGoBack->setEnabled(false);
        m_actionSimulatorStop = new QAction(FormMain);
        m_actionSimulatorStop->setObjectName(QStringLiteral("m_actionSimulatorStop"));
        m_actionSimulatorStop->setEnabled(false);
        m_actionOpenOutputDirectory = new QAction(FormMain);
        m_actionOpenOutputDirectory->setObjectName(QStringLiteral("m_actionOpenOutputDirectory"));
        m_actionUploadApplicationToStore = new QAction(FormMain);
        m_actionUploadApplicationToStore->setObjectName(QStringLiteral("m_actionUploadApplicationToStore"));
        m_actionUploadApplicationToStore->setEnabled(false);
        centralWidget = new QWidget(FormMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        FormMain->setCentralWidget(centralWidget);
        m_menuBar = new QMenuBar(FormMain);
        m_menuBar->setObjectName(QStringLiteral("m_menuBar"));
        m_menuBar->setGeometry(QRect(0, 0, 650, 21));
        m_menuHelp = new QMenu(m_menuBar);
        m_menuHelp->setObjectName(QStringLiteral("m_menuHelp"));
        m_menuProject = new QMenu(m_menuBar);
        m_menuProject->setObjectName(QStringLiteral("m_menuProject"));
        m_menuTools = new QMenu(m_menuBar);
        m_menuTools->setObjectName(QStringLiteral("m_menuTools"));
        m_menuView = new QMenu(m_menuBar);
        m_menuView->setObjectName(QStringLiteral("m_menuView"));
        m_menuSimulatorWindow = new QMenu(m_menuView);
        m_menuSimulatorWindow->setObjectName(QStringLiteral("m_menuSimulatorWindow"));
        menu_Simulator = new QMenu(m_menuBar);
        menu_Simulator->setObjectName(QStringLiteral("menu_Simulator"));
        FormMain->setMenuBar(m_menuBar);
        m_toolBar = new QToolBar(FormMain);
        m_toolBar->setObjectName(QStringLiteral("m_toolBar"));
        m_toolBar->setMovable(false);
        m_toolBar->setAllowedAreas(Qt::TopToolBarArea);
        m_toolBar->setFloatable(false);
        FormMain->addToolBar(Qt::TopToolBarArea, m_toolBar);
        m_statusBar = new QStatusBar(FormMain);
        m_statusBar->setObjectName(QStringLiteral("m_statusBar"));
        FormMain->setStatusBar(m_statusBar);

        m_menuBar->addAction(m_menuProject->menuAction());
        m_menuBar->addAction(m_menuView->menuAction());
        m_menuBar->addAction(menu_Simulator->menuAction());
        m_menuBar->addAction(m_menuTools->menuAction());
        m_menuBar->addAction(m_menuHelp->menuAction());
        m_menuHelp->addAction(m_actionCheckForUpdates);
        m_menuHelp->addAction(m_actionHelp);
        m_menuHelp->addAction(m_actionAboutToolkit);
        m_menuProject->addAction(m_actionNewProject);
        m_menuProject->addAction(m_actionSaveProject);
        m_menuProject->addAction(m_actionSaveProjectAs);
        m_menuProject->addAction(m_actionLoadProject);
        m_menuProject->addSeparator();
        m_menuProject->addAction(m_actionGenerateMobileApplication);
        m_menuProject->addAction(m_actionUploadApplicationToStore);
        m_menuProject->addSeparator();
        m_menuProject->addAction(m_actionQuit);
        m_menuTools->addAction(m_actionSettings);
        m_menuTools->addSeparator();
        m_menuTools->addAction(m_actionOpenOutputDirectory);
        m_menuView->addAction(m_menuSimulatorWindow->menuAction());
        m_menuSimulatorWindow->addAction(m_actionViewSimulatorWindow);
        m_menuSimulatorWindow->addAction(m_actionStickSimulatorWindow);
        menu_Simulator->addAction(m_actionSimulatorRun);
        menu_Simulator->addAction(m_actionSimulatorStop);
        menu_Simulator->addAction(m_actionSimulatorGoBack);

        retranslateUi(FormMain);

        QMetaObject::connectSlotsByName(FormMain);
    } // setupUi

    void retranslateUi(QMainWindow *FormMain)
    {
        FormMain->setWindowTitle(QApplication::translate("FormMain", "MainWindow", 0));
        m_actionCheckForUpdates->setText(QApplication::translate("FormMain", "Check for updates", 0));
        m_actionAboutToolkit->setText(QApplication::translate("FormMain", "&About BuildmLearn Toolkit", 0));
        m_actionQuit->setText(QApplication::translate("FormMain", "&Quit", 0));
        m_actionGenerateMobileApplication->setText(QApplication::translate("FormMain", "&Generate mobile application...", 0));
#ifndef QT_NO_TOOLTIP
        m_actionGenerateMobileApplication->setToolTip(QApplication::translate("FormMain", "Generate mobile application...", 0));
#endif // QT_NO_TOOLTIP
        m_actionNewProject->setText(QApplication::translate("FormMain", "&Create new project...", 0));
#ifndef QT_NO_TOOLTIP
        m_actionNewProject->setToolTip(QApplication::translate("FormMain", "Create new project...", 0));
#endif // QT_NO_TOOLTIP
        m_actionSaveProject->setText(QApplication::translate("FormMain", "&Save project", 0));
        m_actionSaveProjectAs->setText(QApplication::translate("FormMain", "Save project &as...", 0));
#ifndef QT_NO_TOOLTIP
        m_actionSaveProjectAs->setToolTip(QApplication::translate("FormMain", "Save project as...", 0));
#endif // QT_NO_TOOLTIP
        m_actionLoadProject->setText(QApplication::translate("FormMain", "&Load project...", 0));
        m_actionSettings->setText(QApplication::translate("FormMain", "&Settings", 0));
        m_actionHelp->setText(QApplication::translate("FormMain", "&Help", 0));
        m_actionViewSimulatorWindow->setText(QApplication::translate("FormMain", "Show simulator &window", 0));
        m_actionStickSimulatorWindow->setText(QApplication::translate("FormMain", "&Stick simulator window to main window", 0));
        m_actionSimulatorRun->setText(QApplication::translate("FormMain", "Run new &simulation", 0));
        m_actionSimulatorGoBack->setText(QApplication::translate("FormMain", "Go &back", 0));
        m_actionSimulatorStop->setText(QApplication::translate("FormMain", "Stop &running simulation", 0));
        m_actionOpenOutputDirectory->setText(QApplication::translate("FormMain", "Open mobile applications &output directory", 0));
        m_actionUploadApplicationToStore->setText(QApplication::translate("FormMain", "&Submit application to BuildmLearn Store...", 0));
#ifndef QT_NO_TOOLTIP
        m_actionUploadApplicationToStore->setToolTip(QApplication::translate("FormMain", "Submit application to BuildmLearn Store...", 0));
#endif // QT_NO_TOOLTIP
        m_menuHelp->setTitle(QApplication::translate("FormMain", "&Help", 0));
        m_menuProject->setTitle(QApplication::translate("FormMain", "&Project", 0));
        m_menuTools->setTitle(QApplication::translate("FormMain", "&Tools", 0));
        m_menuView->setTitle(QApplication::translate("FormMain", "&View", 0));
        m_menuSimulatorWindow->setTitle(QApplication::translate("FormMain", "&Simulator window", 0));
        menu_Simulator->setTitle(QApplication::translate("FormMain", "&Simulator", 0));
    } // retranslateUi

};

namespace Ui {
    class FormMain: public Ui_FormMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMAIN_H
