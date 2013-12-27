#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "newprojectwidget.h"
#include "InfoTemplate.h"
#include "QuizTemplate.h"
#include "FlashcardTemplate.h"

#define HELP_URL "http://buildmlearn.wordpress.com/download/"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

public slots:
    void startProject(int);
    void aboutClicked();
    void helpClicked();
    void generateClicked();
    void newClicked();
    void saveClicked();
    void openClicked();
    void loadOpenFile();
    void resetWidgets();
private:
    // Menus
    QMenu *fileMenu;
    QMenu *projectMenu;
    QMenu *helpMenu;

    // Action
    QAction *newAct;
    QAction *saveAct;
    QAction *openAct;
    QAction *exitAct;
    QAction *buildAct;
    QAction *howitworksAct;
    QAction *aboutAct;

    // Toolbar
    QToolBar* toolBar;

    // Other widgets
    QStackedWidget* iStackedWidget;

    // Create NewProject Widget
    NewProjectWidget *iNewProjectWidget;

    //  Blank widget
    QWidget* iBlankWidget;
    // Create InfoTemplate Widget
    InfoTemplate* iInfoTemplateWidget;
    // Create QuizTemplate Widget
    QuizTemplate* iQuizTemplateWidget;
    // Create Flashcards Widget
    FlashcardTemplate* iFlashCardsWidget;
};

#endif // MAINWINDOW_H
