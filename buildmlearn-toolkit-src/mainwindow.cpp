/* Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GlobalData.h"

#include <QMessageBox>
#include<QFileDialog>
#include<QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("BuildmLearn Toolkit");
    showMaximized();
    iNewProjectWidget = new NewProjectWidget(this);
    iNewProjectWidget->setWindowModality(Qt::ApplicationModal);
    iNewProjectWidget->show();

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

    // Menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    projectMenu = menuBar()->addMenu(tr("&Project"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    newAct = new QAction(QIcon(":/images/new_project.png"),tr("&New Application"), this);
    saveAct = new QAction(QIcon(":/images/save.png"),tr("&Save"), this);
    openAct = new QAction(QIcon(":/images/open.png"),tr("&Open"), this);
    exitAct = new QAction(tr("&Exit BuildmLearn Toolkit"), this);
    buildAct = new QAction(QIcon(":/images/generate.png"),tr("&Generate Application"), this);
    howitworksAct = new QAction(QIcon(":/images/help.png"),tr("&How it works"), this);
    aboutAct = new QAction(QIcon(":/images/about.png"),tr("&About"), this);

    fileMenu->addAction(newAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(exitAct);

    projectMenu->addAction(buildAct);

    helpMenu->addAction(howitworksAct);
    helpMenu->addAction(aboutAct);


    // Toolbar
    toolBar = addToolBar(tr("toolbar"));
    toolBar->setMovable(false);
    toolBar->addAction(newAct);
    toolBar->addSeparator();
    toolBar->addAction(openAct);
    toolBar->addSeparator();
    toolBar->addAction(saveAct);
    toolBar->addSeparator();
    toolBar->addAction(buildAct);
    toolBar->addSeparator();
    toolBar->addAction(howitworksAct);
    toolBar->addSeparator();
    toolBar->addAction(aboutAct);

    connect(iNewProjectWidget, SIGNAL(startProject(int)), this, SLOT(startProject(int)));
    connect(aboutAct, SIGNAL(triggered()), this ,SLOT(aboutClicked()));
    connect(newAct, SIGNAL(triggered()), this ,SLOT(newClicked()));
    connect(saveAct, SIGNAL(triggered()), this ,SLOT(saveClicked()));
    connect(openAct, SIGNAL(triggered()), this ,SLOT(openClicked()));
    connect(howitworksAct, SIGNAL(triggered()), this ,SLOT(helpClicked()));
    connect(buildAct, SIGNAL(triggered()), this ,SLOT(generateClicked()));
    connect(exitAct, SIGNAL(triggered()), this ,SLOT(close()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::saveClicked()
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

void MainWindow::openClicked()
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

void MainWindow::loadOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",tr("*.buildmlearn"));
    QFile indexFile(fileName);
    indexFile.open(QIODevice::ReadOnly);

    QString data = indexFile.readAll();
    indexFile.close();
    QStringList dataList = data.split(GlobalData::IO_LD);
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

void MainWindow::newClicked()
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

void MainWindow::aboutClicked()
{

    QMessageBox::information(this,"About" , "BuildmLearn Toolkit\nVersion 2.0.0\n\nBuildmLearn Toolkit is an easy-to-use program that helps the users make mobile apps without any knowledge of application development. The toolkit helps creating mobile application with various functionality and allows teachers to input their custom content. Targeted at teachers, this toolkit helps them make learning fun and engaging through mobile apps.\n\nFor more information visit: http://buildmlearn.org \n\nContact the developers at BuildmLearn Google Group (https://groups.google.com/forum/#!forum/buildmlearn) for any other information or suggestions. Alternatively, you can email the core developers at croozeus@gmail.com. ");
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
    else if (iStackedWidget->currentIndex()==3)
    {
        ((FlashcardTemplate*)iStackedWidget->currentWidget())->on_generateButton_clicked();
    }
}

void MainWindow::startProject(int index)
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
void MainWindow::resetWidgets()
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
