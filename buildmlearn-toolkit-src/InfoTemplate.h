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

#ifndef INFOTEMPLATE_H
#define INFOTEMPLATE_H

#include<QPlainTextEdit>
#include<QStackedWidget>
#include <QWidget>
#include <QtGui>
#include<QListWidget>
#include<QLabel>
#include<QPushButton>
#include<QMainWindow>

#include <QtGui>

class InfoTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit InfoTemplate(QWidget *parent = 0);

public slots:
    void on_addButton_cicked();
    void on_removedButton_cicked();
    void on_itemList_selected();

    void on_textEdit_textChanged();

    void on_itemList_phone_selected();
    void on_backButton_clicked();
    void on_generateButton_clicked();

    void execWindowsCommand(QString);
    void execWindowsCommandDetached(QString);
    void on_save_clicked();
    void on_open_clicked(QStringList dataList);

private:
    QWidget* widget1;
    QWidget* widget2;
    QWidget* widget3;
    QWidget* mainWidget;

    // for widget 1
    QListWidget* itemList;
    QPushButton* addButton;
    QPushButton* removeButton;
    QLineEdit* lineEdit;

    // for widget 2
    QPlainTextEdit* textEdit;

    // for widget 3
    QStackedWidget* phoneWidget;
    QWidget* screen1;
    QWidget* screen2;
    QListWidget* itemList_phone;
    QLabel* textLabel_phone;
    QPushButton* backButton;
    QPushButton* generateButton;

    QLabel* phoneBody;
    QLabel* phoneHeader;
    QLabel* phoneFooter;
    QLabel* phoneLeft;
    QLabel* phoneRight;


    QProcess* iProcess;

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
//    NewProjectWidget *newProject;

    // Engine
    QStringList iTitleList;
    QStringList iDescriptionList;


};

#endif // INFOTEMPLATE_H
