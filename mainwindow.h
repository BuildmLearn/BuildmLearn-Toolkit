#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "newprojectwidget.h"
#include "InfoTemplate.h"
#include "QuizTemplate.h"

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
private:
    // Menus
    QMenu *fileMenu;
    QMenu *projectMenu;
    QMenu *helpMenu;

    // Action
    QAction *newAct;
    QAction *exitAct;
    QAction *buildAct;
    QAction *howitworksAct;
    QAction *aboutAct;

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
};

#endif // MAINWINDOW_H
