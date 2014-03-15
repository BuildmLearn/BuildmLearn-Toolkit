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

#ifndef FlashcardTemplate_H
#define FlashcardTemplate_H

#include<QVBoxLayout>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QMessageBox>
#include<QFileDialog>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QScrollArea>
#include <QStackedWidget>
#include <QComboBox>

#include <QtGui>
#include "QuestionItem.h"

class FlashcardTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit FlashcardTemplate(QWidget *parent = 0);

public slots:
    void on_addButton_cicked();
//    void on_removedButton_cicked();
//    void on_itemList_selected();

//    void on_textEdit_textChanged();

//    void on_itemList_phone_selected();
//    void on_backButton_clicked();
    void on_generateButton_clicked();
    void on_chooseImageButton_clicked();

    void execWindowsCommand(QString);
    void execWindowsCommandDetached(QString);

    void removeQuestion(int);
    void optionAdded();
    void startSimulaton_clicked();

    void startQuiz();
    void populateQuiz(int);

    void flipButton_phone_clicked();
    void prevButton_phone_clicked();
    void nextButton_phone_clicked();


    void updateStartPage_phone();
    void restartQuiz_phone_clicked();
    void on_save_clicked();
    void on_open_clicked(QStringList dataList);

private:
    QWidget* widget1;
    QWidget* widget2;
    QWidget* widget3;
    QWidget* mainWidget;

    // for widget 1
    QPushButton* addButton;
    QTextEdit* questionEdit;
    QLineEdit* fcAnswerEdit;
    QLineEdit* fcHintEdit;

    QLabel* questionLabel;
    QLabel* fcImageLabel;
    QLabel* fcImagePathLabel;
    QLabel* correctAnserLabel;
    QLabel* hintLabel;

    QComboBox* comboBox;
    QPushButton* chooseImageButton;


    // for widget 2
    QPlainTextEdit* textEdit;
    QListWidget* iQuestionList;
    QScrollArea* iScrollArea;
    QVBoxLayout* widget2_vlayout;

    // for widget 3
    QStackedWidget* phoneWidget;
    QWidget* screen1;
    QWidget* screen2;
    QWidget* screen3;

    QLabel* quizNameLabel_phone;
    QLabel* quizAuthorLabel_phone;
    QPushButton* startQuiz_phone;

    QLabel* questionLabel_phone;
    QLabel* questionText_phone;
//    QRadioButton* option1_phone;
//    QRadioButton* option2_phone;
//    QRadioButton* option3_phone;
//    QRadioButton* option4_phone;
//    QList<QRadioButton*> optionsList_phone;
    QLabel* fcImage_phone;
    QLabel* fcHintLabel_phone;
    QLabel* fcAnswerLabel_phone;
    QPushButton* prevButton_phone;
    QPushButton* nextButton_phone;
    QPushButton* flipButton_phone;
    QLabel* quizComplete_Label_phone;
    QPushButton* restartQuiz_phone;
    QPushButton* backButton;
    QPushButton* generateButton;


    QLabel* phoneBody;
    QLabel* phoneHeader;
    QLabel* phoneFooter;
    QLabel* phoneLeft;
    QLabel* phoneRight;
    QPushButton* startSimulation;

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

    int noOfQues;


    int questionCounter;
    int rightAnswer;

    // Engine
    QStringList iQuestionTextList;
    QStringList iImageList;
    QStringList iHintList;
    QList<QString> iAnsList;
    QList<QuestionItem*> iQuestionItemList;

public:
    QString quizName;
    QString authorName;
};

#endif // FlashcardTemplate_H
