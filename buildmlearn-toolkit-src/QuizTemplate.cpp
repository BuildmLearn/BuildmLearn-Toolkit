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

#include "QuizTemplate.h"
#include "GlobalData.h"

#include<QLineEdit>
#include<QMessageBox>
#include<QFileDialog>

QuizTemplate::QuizTemplate(QWidget *parent) :
    QWidget(parent)
{
    questionCounter = 0;
    noOfQues = 0;

    widget1 = new QWidget();
    widget2 = new QWidget();
    widget3 = new QWidget();

    iScrollArea = new QScrollArea();
    iScrollArea->setWidgetResizable(true);
    iScrollArea->setWidget(widget2);

    QVBoxLayout* widget1_vlayout=  new QVBoxLayout(widget1);

    widget1_vlayout->setSpacing(0);
    widget1_vlayout->setMargin(10);
    questionEdit =  new QTextEdit(widget1);
    option1Edit =  new QLineEdit(widget1);
    option2Edit =  new QLineEdit(widget1);
    option3Edit =  new QLineEdit(widget1);
    option4Edit =  new QLineEdit(widget1);
    addButton = new QPushButton("Add Question", widget1);
    questionLabel = new QLabel("Enter your question:", widget1);
    optionsLabel = new QLabel("Enter options", widget1);
    correctAnserLabel = new QLabel("Choose the correct answer", widget1);
    comboBox = new QComboBox(widget1);
    questionEdit->setFixedHeight(100);
    questionLabel->setFixedHeight(40);
    optionsLabel->setFixedHeight(40);


    option1Edit->setPlaceholderText("Option 1");
    option2Edit->setPlaceholderText("Option 2");
    option3Edit->setPlaceholderText("Option 3");
    option4Edit->setPlaceholderText("Option 4");

    connect(option1Edit, SIGNAL(editingFinished()), this, SLOT(optionAdded()));
    connect(option2Edit, SIGNAL(editingFinished()), this, SLOT(optionAdded()));
    connect(option3Edit, SIGNAL(editingFinished()), this, SLOT(optionAdded()));
    connect(option4Edit, SIGNAL(editingFinished()), this, SLOT(optionAdded()));

    questionLabel->setStyleSheet("font-size:24px;");
    optionsLabel->setStyleSheet("font-size:22px;");
    correctAnserLabel->setStyleSheet("font-size:22px;");

    widget1_vlayout->addWidget(questionLabel);
    widget1_vlayout->addWidget(questionEdit);
    widget1_vlayout->addWidget(optionsLabel);
    widget1_vlayout->addWidget(option1Edit);
    widget1_vlayout->addWidget(option2Edit);
    widget1_vlayout->addWidget(option3Edit);
    widget1_vlayout->addWidget(option4Edit);
    widget1_vlayout->addWidget(correctAnserLabel);
    widget1_vlayout->addWidget(comboBox);
    widget1_vlayout->addWidget(addButton);



    // widget 2 initialization

    widget2_vlayout=  new QVBoxLayout(widget2);
    widget2_vlayout->setMargin(1);
    widget2->setStyleSheet("background-color:grey");
    widget2_vlayout->update();

    startSimulation = new QPushButton("Start Simulation", widget3);
//    startSimulation->setGeometry(120,20,100,30);
    connect(startSimulation, SIGNAL(clicked()), this, SLOT(startSimulaton_clicked()));


    phoneBody = new QLabel(widget3);
    QVBoxLayout* widget3_vlayout=  new QVBoxLayout(widget3);

    phoneBody->setFixedSize(327,639);
    phoneBody->setStyleSheet("background-image: url(:/images/phone.png)");

    phoneWidget = new QStackedWidget(phoneBody);
    phoneWidget->setStyleSheet("background: #255593; color: white;");
    phoneWidget->setGeometry(30,95,270,447);

    backButton = new QPushButton("<-");
    backButton->setFixedWidth(phoneWidget->width());

    generateButton = new QPushButton("Generate Application");
    generateButton->setFixedWidth(phoneWidget->width());

    widget3_vlayout->addWidget(phoneBody);
    widget3_vlayout->addWidget(backButton);
    widget3_vlayout->addWidget(generateButton);

    screen1 = new QWidget();
    screen2 = new QWidget();
    screen3 = new QWidget();
    phoneWidget->addWidget(screen1);
    phoneWidget->addWidget(screen2);
    phoneWidget->addWidget(screen3);

    // screen 1
    QVBoxLayout* screen1_vlayout = new QVBoxLayout(screen1);
    screen1_vlayout->setSpacing(5);


    quizNameLabel_phone = new QLabel("Quiz Name");
    quizNameLabel_phone->setStyleSheet("background: transparent; color: white; font-size: 20px;padding:10px;");
    quizNameLabel_phone->setAlignment(Qt::AlignBottom|Qt::AlignCenter);
    quizAuthorLabel_phone= new QLabel("Author Name");
    quizAuthorLabel_phone->setStyleSheet("background: transparent; color: white; font-size: 20px;padding:10px;");
    quizAuthorLabel_phone->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

    QLabel* line_screen1 = new QLabel(screen1);
    line_screen1->setFixedWidth(screen1->width()-20);
    line_screen1->setFixedHeight(1);
    line_screen1->setStyleSheet("background-color: white;");

    startQuiz_phone = new QPushButton("Start",screen1);
    startQuiz_phone->setStyleSheet("background-color: lightgrey; color: black;font-size:18px;");
    connect(startQuiz_phone, SIGNAL(clicked()), this, SLOT(startQuiz()));

    screen1_vlayout->addWidget(quizNameLabel_phone);
    screen1_vlayout->addWidget(line_screen1);
    screen1_vlayout->addWidget(quizAuthorLabel_phone);
    screen1_vlayout->addWidget(startQuiz_phone, 0, Qt::AlignCenter);

    screen1->setVisible(false);

    // screen 2
    QVBoxLayout* screen2_vlayout = new QVBoxLayout(screen2);
    screen2_vlayout->setSpacing(5);

    questionLabel_phone= new QLabel(screen2);
    //    textLabel_phone->setFixedSize(phoneWidget->size());
    questionLabel_phone->setAlignment(Qt::AlignTop);
    //    textLabel_phone->setStyleSheet("background: yellow");
    //    textLabel_phone->setFixedSize(phoneWidget->size());
    questionLabel_phone->setStyleSheet("background: transparent; color: white; font-size: 20px;");
    //    textLabel_phone->setWordWrap(true);
    questionLabel_phone->setFixedHeight(30);

    QLabel* line_screen2 = new QLabel(screen2);
    line_screen2->setFixedWidth(screen2->width()-10);
    line_screen2->setFixedHeight(1);
    line_screen2->setStyleSheet("background-color: white;");

    questionText_phone = new QLabel(screen2);
    questionText_phone->setAlignment(Qt::AlignTop);
    questionText_phone->setStyleSheet("background: transparent; color: white; font-size: 20px;");
    questionText_phone->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

    option1_phone = new QRadioButton(screen2);
    option2_phone = new QRadioButton(screen2);
    option3_phone = new QRadioButton(screen2);
    option4_phone = new QRadioButton(screen2);

    optionsList_phone.append(option1_phone);
    optionsList_phone.append(option2_phone);
    optionsList_phone.append(option3_phone);
    optionsList_phone.append(option4_phone);

    option1_phone->setStyleSheet("background: transparent; color: white; font-size: 18px;");
    option2_phone->setStyleSheet("background: transparent; color: white; font-size: 18px;");
    option3_phone->setStyleSheet("background: transparent; color: white; font-size: 18px;");
    option4_phone->setStyleSheet("background: transparent; color: white; font-size: 18px;");

    submitButton_phone = new QPushButton("Submit", screen2);
    submitButton_phone->setStyleSheet("background-color: lightgrey; color: black;font-size:18px;");
    connect(submitButton_phone, SIGNAL(clicked()), this, SLOT(submitButton_phone_clicked()));

    screen2_vlayout->addWidget(questionLabel_phone);
    screen2_vlayout->addWidget(line_screen2);
    screen2_vlayout->addWidget(questionText_phone);
    screen2_vlayout->addWidget(option1_phone);
    screen2_vlayout->addWidget(option2_phone);
    screen2_vlayout->addWidget(option3_phone);
    screen2_vlayout->addWidget(option4_phone);
    screen2_vlayout->addWidget(submitButton_phone, 0, Qt::AlignCenter|Qt::AlignBottom);

    //screen3
    QVBoxLayout* screen3_vlayout = new QVBoxLayout(screen3);
    screen3_vlayout->setGeometry(widget3->geometry());
    quizComplete_Label_phone = new QLabel( "Quiz completed!", screen3);
    quizComplete_Label_phone->setStyleSheet("font-size:24px;");
    restartQuiz_phone = new QPushButton("Start again", screen3);
    restartQuiz_phone->setStyleSheet("background-color: lightgrey; color: black;font-size:18px;");
    screen3_vlayout->addWidget(quizComplete_Label_phone, 0, Qt::AlignTop);
    screen3_vlayout->addWidget(restartQuiz_phone, Qt::AlignBottom);
    connect(restartQuiz_phone, SIGNAL(clicked()), this, SLOT(restartQuiz_phone_clicked()));

    phoneWidget->setCurrentIndex(0);
//phoneWidget->setEnabled(false);

    ///
    QHBoxLayout* hlayout = new QHBoxLayout(this);

    hlayout->addWidget(widget1);
    hlayout->addWidget(iScrollArea);
    hlayout->addWidget(widget3);

    widget1->setFixedHeight(600);
    hlayout->setAlignment(widget1, Qt::AlignTop);

    iProcess = new QProcess(this);

    // Signal and slots

    connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButton_cicked()));
    connect(generateButton, SIGNAL(clicked()), this, SLOT(on_generateButton_clicked()));
}

void QuizTemplate::on_addButton_cicked()
{
    if (questionEdit->toPlainText().isEmpty())
    {
        QMessageBox::information(this,"Add question" , "Please add the question text first.");
        return;
    }
    else if (option1Edit->text().isEmpty() && option2Edit->text().isEmpty() &&
             option3Edit->text().isEmpty() && option4Edit->text().isEmpty())
    {
        QMessageBox::information(this,"Add options" , "Please add some options for your question first.");
        return;
    }

    QString qText = questionEdit->toPlainText().replace("\n", " ");
    QString quesText = "<br><br>" +qText+" <br><br>";
    QString optionsText;
    if (!option1Edit->text().isEmpty())
    {
        quesText.append("- " + option1Edit->text() + "<br>");
        optionsText.append(option1Edit->text());
    }
    if (!option2Edit->text().isEmpty())
    {
        optionsText.append("==");
        quesText.append("- " + option2Edit->text() + "<br>");
        optionsText.append(option2Edit->text());

    }
    if (!option3Edit->text().isEmpty())
    {
        optionsText.append("==");
        quesText.append("- " + option3Edit->text() + "<br>");
        optionsText.append(option3Edit->text());

    }
    if (!option4Edit->text().isEmpty())
    {
        optionsText.append("==");
        quesText.append("- " + option4Edit->text() + "<br>");
        optionsText.append(option4Edit->text());

    }
    iQuestionItemList.append(new QuestionItem(noOfQues,quesText));
    widget2_vlayout->addWidget(iQuestionItemList.at(noOfQues));
    connect(iQuestionItemList.at(noOfQues), SIGNAL(removeClicked(int)), this, SLOT(removeQuestion(int)));
    noOfQues++;

    iQuestionTextList.append(qText);
    iOptionsList.append(optionsText);
    iAnsList.append(comboBox->currentIndex());

    qDebug()<<iQuestionTextList;
    qDebug()<<iOptionsList;
    qDebug()<<iAnsList;
    qDebug()<<"===============";

    questionEdit->clear();
    option1Edit->clear();
    option2Edit->clear();
    option3Edit->clear();
    option4Edit->clear();

    comboBox->clear();

}

void QuizTemplate::on_generateButton_clicked()
{
    if (iQuestionTextList.count()==0)
    {
          QMessageBox::information(this,"No questions added!" , "Please add some questions before generating the application!");
          return;
    }

    QDir dir;
    dir.mkdir("assets");
    QFile indexFile("assets/quiz_content.txt");
    indexFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&indexFile);

    out << quizName;
    out << "\n";
    out << authorName;
    out << "\n";

    for (int i=0; i<iQuestionTextList.count(); i++)
    {
        out << iQuestionTextList.at(i) + "==" + iOptionsList.at(i)+"=="+QString::number(iAnsList.at(i));
        out << "\n";
    }
    indexFile.close();



    execWindowsCommand("copy config\\templates\\BuildmLearnQuiz.apk config\\BuildmLearnQuiz_in_use.zip");
    execWindowsCommand("config\\templates\\7za.exe a config\\BuildmLearnQuiz_in_use.zip assets");
    execWindowsCommand("config\\templates\\signapk.jar config\\templates\\certificate.pem config\\templates\\key.pk8 config\\BuildmLearnQuiz_in_use.zip applications\\BuildmLearnQuiz_signed.apk");
    execWindowsCommand("del config\\BuildmLearnQuiz_in_use.zip");

    indexFile.remove();
    dir.rmdir("assets");
    QMessageBox::information(this,"Application generated" , "Your application has been generated. For the installation file, please check /applications folder. ");
}

void QuizTemplate::execWindowsCommand(QString command)
{
    qDebug()<<"cmd: "+command;
    QStringList args;
    args<<"/C"<<command;
    iProcess->start("cmd.exe",args);
    iProcess->waitForFinished(-1);
}


void QuizTemplate::execWindowsCommandDetached(QString command)
{
    qDebug()<<"detached cmd: "+command;
    QStringList args;
    args<<"/C"<<command;
    iProcess->startDetached("cmd.exe",args);
}

void QuizTemplate::removeQuestion(int index)
{
    qDebug()<<"removeQuestionssss: "+QString::number(index);
    delete iQuestionItemList.takeAt(index);

    for (int i=index; i<iQuestionItemList.length(); i++)
    {
        iQuestionItemList.at(i)->setIndex(iQuestionItemList.at(i)->getIndex()-1);

    }

    iQuestionTextList.removeAt(index);
    iOptionsList.removeAt(index);
    iAnsList.removeAt(index);

    qDebug()<<iQuestionTextList;
    qDebug()<<iOptionsList;
    qDebug()<<iAnsList;
    qDebug()<<"===============";

    noOfQues--;
}

void QuizTemplate::optionAdded()
{
    comboBox->clear();
    if (option1Edit->text()!="")
    {
        comboBox->addItem(option1Edit->text());
    }
    if (option2Edit->text()!="")
    {
        comboBox->addItem(option2Edit->text());
    }
    if (option3Edit->text()!="")
    {
        comboBox->addItem(option3Edit->text());
    }
    if (option4Edit->text()!="")
    {
        comboBox->addItem(option4Edit->text());
    }
}

void QuizTemplate::startSimulaton_clicked()
{

    qDebug()<<iQuestionTextList;
    if (iQuestionTextList.length()>0)
    {
        // If there are questions added

        if (startSimulation->text()=="Start Simulation")
        {
            widget1->setEnabled(false);
            widget2->setEnabled(false);
            startSimulation->setText("Stop Simulation");
            screen1->setVisible(true);
            phoneWidget->setCurrentIndex(0);
//            phoneWidget->setEnabled(true);
            return;
        }
    }
    else{
        // Add questions first MessageBox
        qDebug()<<"Add questions first";
        QMessageBox::information(this,"Simulation" , "Please add some questions first");
    }




    if (startSimulation->text()=="Stop Simulation"){
        widget1->setEnabled(true);
        widget2->setEnabled(true);
        startSimulation->setText("Start Simulation");
//        phoneWidget->setEnabled(false);
    }

}

void QuizTemplate::startQuiz()
{
    qDebug()<<"Start clicked";
    phoneWidget->setCurrentIndex(1);
    populateQuiz(questionCounter);
}

void QuizTemplate::populateQuiz(int index)
{
    if (index<iQuestionTextList.length())
    {
        // Load new question
        questionLabel_phone->setText("Question "+ QString::number(index+1));
        questionText_phone->setText(iQuestionTextList.at(index));


        for (int i=0; i<4; i++)
        {
            optionsList_phone.at(i)->setVisible(false);
        }

        QStringList options = iOptionsList.at(index).split("==");
        qDebug()<<options;
        for (int i=0; i<options.length(); i++)
        {

            optionsList_phone.at(i)->setText(options.at(i));
            optionsList_phone.at(i)->setVisible(true);

            // reset options to not selected
            optionsList_phone.at(i)->setAutoExclusive(false);
            optionsList_phone.at(i)->setChecked(false);
            optionsList_phone.at(i)->setAutoExclusive(true);
            optionsList_phone.at(i)->setStyleSheet("background: transparent; color: white; font-size: 18px;");
        }

        rightAnswer =iAnsList.at(index);
        submitButton_phone->setText("Submit");


    }

}

void QuizTemplate::submitButton_phone_clicked()
{
    if (submitButton_phone->text()=="Submit")
    {
        // If submit is clicked
        int selectedOption = getSelectedOption();
        if (selectedOption != -1)
        {
            if (selectedOption == rightAnswer)
            {
                // correct answer
                optionsList_phone.at(selectedOption)->setStyleSheet("background: green; color: white; font-size: 18px;");
            }
            else
            {
                optionsList_phone.at(selectedOption)->setStyleSheet("background: red; color: white; font-size: 18px;");
                optionsList_phone.at(rightAnswer)->setStyleSheet("background: green; color: white; font-size: 18px;");
            }
            submitButton_phone->setText("Next");
            questionCounter++;
        }
        else{
            // ask to select an option
        }
    }
    else{
        // If next is clicked
        if (questionCounter<iQuestionTextList.length())
        {

            // if more questions are there
            populateQuiz(questionCounter);
        }
        else
        {
        // if no more questions
            qDebug()<<"Over to screen3";
            phoneWidget->setCurrentIndex(2);
            questionCounter=0;
        }


    }

}

void QuizTemplate::restartQuiz_phone_clicked()
{
    phoneWidget->setCurrentIndex(0);
}

int QuizTemplate::getSelectedOption()
{
    int selected = -1;
    for (int i=0; i<optionsList_phone.length(); i++)
    {
        if (optionsList_phone.at(i)->isChecked())
        {
            selected = i;
            return selected;
        }
    }
    return selected;
}

void QuizTemplate::updateStartPage_phone()
{
    quizNameLabel_phone->setText(quizName);
    quizAuthorLabel_phone->setText(authorName);
}

void QuizTemplate::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "MyQuizApp.buildmlearn",
                                tr("*.buildmlearn"));


    QFile indexFile(fileName);
    indexFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&indexFile);
    QString headers = QString("QuizTemplate") + GlobalData::IO_LD + quizName + GlobalData::IO_LD + authorName;
    out << headers;
    qDebug()<<headers;

    for (int i=0; i<iQuestionTextList.count(); i++)
    {
        out <<GlobalData::IO_LD;
        out << iQuestionTextList.at(i) + "==" + iOptionsList.at(i)+"=="+QString::number(iAnsList.at(i));
    }
    indexFile.close();

}
void QuizTemplate::on_open_clicked(QStringList dataList)
{
    qDebug()<<dataList;
    iQuestionItemList.clear();
    iQuestionTextList.clear();
    iOptionsList.clear();
    iAnsList.clear();

    quizName = dataList.at(0);
    authorName = dataList.at(1);
    qDebug()<<quizName<<quizName.count()<<QString(quizName.right(1));
    dataList.removeFirst();
    dataList.removeFirst();

    updateStartPage_phone();

    questionCounter=0;
    noOfQues = 0;

    for (int i=0; i<dataList.length();i++)
    {
//        if (dataList.at(i).isEmpty())
//        {
//            continue;
//        }
        QStringList data = dataList.at(i).split("==");
        iQuestionTextList.append(data.first());
        data.removeFirst();
        iAnsList.append(data.last().toInt());
        data.removeLast();


        QString quesText = "<br><br>" +iQuestionTextList.at(i)+" <br><br>";

        QString options;
        for (int j=0; j<data.count();j++)
        {
            options.append(data.at(j));
            if (j!=data.count()-1)
            {
                options.append("==");
            }

            quesText.append("- " + data.at(j) + "<br>");
        }
        iOptionsList.append(options);

        iQuestionItemList.append(new QuestionItem(noOfQues,quesText));
        widget2_vlayout->addWidget(iQuestionItemList.at(noOfQues));
        connect(iQuestionItemList.at(noOfQues), SIGNAL(removeClicked(int)), this, SLOT(removeQuestion(int)));
        noOfQues++;
    }
    qDebug()<<"===============";
    qDebug()<<quizName<<authorName;
    qDebug()<<iQuestionTextList;
    qDebug()<<iOptionsList;
    qDebug()<<iAnsList;
    qDebug()<<"===============";
}
