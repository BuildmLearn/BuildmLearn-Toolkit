#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle("BuildmLearn Toolkit");
    showMaximized();
    iNewProjectWidget = new NewProjectWidget(this);
    iNewProjectWidget->show();

    iStackedWidget = new QStackedWidget(this);
    iBlankWidget = new QWidget(this);
    iInfoTemplateWidget = new InfoTemplate(this);
    iQuizTemplateWidget = new QuizTemplate(this);

    iStackedWidget->addWidget(iBlankWidget);
    iStackedWidget->addWidget(iInfoTemplateWidget);
    iStackedWidget->addWidget(iQuizTemplateWidget);

    iStackedWidget->setCurrentIndex(0);

    setCentralWidget(iStackedWidget);

    // Menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    projectMenu = menuBar()->addMenu(tr("&Project"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    newAct = new QAction(tr("&New"), this);
    exitAct = new QAction(tr("&Exit"), this);
    buildAct = new QAction(tr("&Generate application"), this);
    howitworksAct = new QAction(tr("&How it works"), this);
    aboutAct = new QAction(tr("&About"), this);

    fileMenu->addAction(newAct);
    fileMenu->addAction(exitAct);

    projectMenu->addAction(buildAct);

    helpMenu->addAction(howitworksAct);
    helpMenu->addAction(aboutAct);

    connect(iNewProjectWidget, SIGNAL(startProject(int)), this, SLOT(startProject(int)));
    connect(aboutAct, SIGNAL(triggered()), this ,SLOT(aboutClicked()));
    connect(newAct, SIGNAL(triggered()), this ,SLOT(newClicked()));
    connect(howitworksAct, SIGNAL(triggered()), this ,SLOT(helpClicked()));
    connect(buildAct, SIGNAL(triggered()), this ,SLOT(generateClicked()));
    connect(exitAct, SIGNAL(triggered()), this ,SLOT(close()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::newClicked()
{
    if (iStackedWidget->currentIndex() !=0)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, "Discard current project?", "Choosing a new project would discard your current project. Are you sure to continue?", QMessageBox::Yes|QMessageBox::No))
        {
            iStackedWidget->setCurrentIndex(0);
            iNewProjectWidget->show();

            // reseting other widgets
            iStackedWidget->removeWidget(iQuizTemplateWidget);
            iStackedWidget->removeWidget(iInfoTemplateWidget);

            iInfoTemplateWidget = new InfoTemplate(this);
            iQuizTemplateWidget = new QuizTemplate(this);

            iStackedWidget->addWidget(iInfoTemplateWidget);
            iStackedWidget->addWidget(iQuizTemplateWidget);

        }
    }



}

void MainWindow::aboutClicked()
{

QMessageBox::information(this,"About" , "BuildmLearn Toolkit\nVersion 0.9\n\nBuildmLearn Toolkit is an easy-to-use program that helps the users make mobile apps without any knowledge of application development. The toolkit helps creating mobile application with various functionality and allows teachers to input their custom content. Targeted at teachers, this toolkit helps them make learning fun and engaging through mobile apps.\n\nFor more information visit: http://buildmlearn.wordpress.com \n\nContact the developer at croozeus@gmail.com for any other information or suggestions.");
}

void MainWindow::helpClicked()
{
 QDesktopServices::openUrl(QString(HELP_URL));
}

void MainWindow::generateClicked()
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
}

void MainWindow::startProject(int index)
{
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
}
