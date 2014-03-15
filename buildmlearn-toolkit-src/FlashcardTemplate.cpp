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

#include "FlashcardTemplate.h"
#include "GlobalData.h"

FlashcardTemplate::FlashcardTemplate(QWidget *parent) :
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
    widget1_vlayout->setAlignment(Qt::AlignTop);
    questionEdit =  new QTextEdit(widget1);
    fcAnswerEdit =  new QLineEdit(widget1);
    fcHintEdit  =  new QLineEdit(widget1);

    chooseImageButton = new QPushButton("Browse to choose image", widget1);
    chooseImageButton->setFixedWidth(150);
    addButton = new QPushButton("Add Flashcard", widget1);

    questionLabel = new QLabel("Enter your question:", widget1);
    fcImageLabel = new QLabel("Add image (for front side of the flashcard):", widget1);
    hintLabel = new QLabel("Enter hint or any text to be shown with the flashcard image:", widget1);
    correctAnserLabel = new QLabel("Enter answer to the question:", widget1);

    fcHintEdit->setPlaceholderText("Hint/text - This would be displayed on front side of flashcard");
    fcAnswerEdit->setPlaceholderText("Answer - This would be displayed on reverse side of flashcard");

    fcImagePathLabel = new QLabel("No image selected", widget1);

    questionEdit->setFixedHeight(100);
    questionLabel->setFixedHeight(40);
    hintLabel->setFixedHeight(40);
    fcImageLabel->setFixedHeight(40);

    questionLabel->setStyleSheet("font-size:24px;");
    fcImageLabel->setStyleSheet("font-size:18px;");
    hintLabel->setStyleSheet("font-size:14px;");
    correctAnserLabel->setStyleSheet("font-size:18px;");

    widget1_vlayout->addWidget(questionLabel);
    widget1_vlayout->addWidget(questionEdit);

    widget1_vlayout->addWidget(fcImageLabel);
    widget1_vlayout->addWidget(fcImagePathLabel);
    widget1_vlayout->addWidget(chooseImageButton);

    widget1_vlayout->addWidget(hintLabel);
    widget1_vlayout->addWidget(fcHintEdit);

    widget1_vlayout->addWidget(correctAnserLabel);
    widget1_vlayout->addWidget(fcAnswerEdit);

    widget1_vlayout->addWidget(addButton);

widget1_vlayout->setAlignment(Qt::AlignTop);

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


    QVBoxLayout* flash_card_layout = new QVBoxLayout(screen2);
    flash_card_layout->setSpacing(5);

    fcImage_phone = new QLabel(screen2);
    fcHintLabel_phone = new QLabel(screen2);
    fcAnswerLabel_phone = new QLabel(screen2);

    fcImage_phone->setFixedSize(210,210);
    fcImage_phone->setMargin(20);
    fcImage_phone->setStyleSheet("background: red;");
    fcHintLabel_phone->setStyleSheet("font-size:24px;");
    fcAnswerLabel_phone->setStyleSheet("font-size:24px;");


    flash_card_layout->addSpacing(20);
    flash_card_layout->addWidget(fcImage_phone,0, Qt::AlignCenter);
    flash_card_layout->addWidget(fcHintLabel_phone,0, Qt::AlignCenter);
    flash_card_layout->addWidget(fcAnswerLabel_phone,0, Qt::AlignCenter);


    prevButton_phone = new QPushButton("Previous", screen2);
    prevButton_phone->setStyleSheet("background-color: lightgrey; color: black;font-size:18px;");
    connect(prevButton_phone, SIGNAL(clicked()), this, SLOT(prevButton_phone_clicked()));

    nextButton_phone = new QPushButton("Next", screen2);
    nextButton_phone->setStyleSheet("background-color: lightgrey; color: black;font-size:18px;");
    connect(nextButton_phone, SIGNAL(clicked()), this, SLOT(nextButton_phone_clicked()));

    flipButton_phone = new QPushButton("Flip", screen2);
    flipButton_phone->setStyleSheet("background-color: lightgrey; color: black;font-size:18px;");
    connect(flipButton_phone, SIGNAL(clicked()), this, SLOT(flipButton_phone_clicked()));

    QHBoxLayout *screen2_hlayout = new QHBoxLayout(screen2);
    screen2_hlayout->setSpacing(5);
    screen2_hlayout->addWidget(prevButton_phone);
    screen2_hlayout->addWidget(flipButton_phone);
    screen2_hlayout->addWidget(nextButton_phone);

    screen2_vlayout->addWidget(questionLabel_phone);
    screen2_vlayout->addWidget(line_screen2);
    screen2_vlayout->addWidget(questionText_phone);
    screen2_vlayout->addLayout(flash_card_layout);
    screen2_vlayout->addLayout(screen2_hlayout);



    //screen3
    QVBoxLayout* screen3_vlayout = new QVBoxLayout(screen3);
    screen3_vlayout->setGeometry(widget3->geometry());
    quizComplete_Label_phone = new QLabel( "That was the last card!", screen3);
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
    connect(chooseImageButton, SIGNAL(clicked()), SLOT(on_chooseImageButton_clicked()));

}

void FlashcardTemplate::on_chooseImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Images (*.png)"));

    fcImagePathLabel->setText(fileName);
}

void FlashcardTemplate::on_addButton_cicked()
{
    QString quesText = "<br><br>" +questionEdit->toPlainText()+" <br><br>";
    QString optionsText;

    if ((fcImagePathLabel->text().compare("No image selected")==0 && fcHintEdit->text().isEmpty() ) ||
            questionEdit->toPlainText().isEmpty() || fcAnswerEdit->text().isEmpty())
    {
        QMessageBox::information(this,"Insufficient Information" , "Flash card needs to have an image or text on the front side, and an answer on the reverse side. Seems like you didn't fill them all.");
        return;
    }
    else{
        optionsText.append("<b>Front side</b>");
        optionsText.append("<br>");

        if (fcImageLabel->text().length() > 0)
        {
            QString fileName = fcImagePathLabel->text().split("/").last();
            optionsText.append("<b>Image:</b> " + fileName + "<br>");
        }
        if  (fcHintEdit->text().length() > 0)
        {
            optionsText.append("<b>Hint/Text:</b> "+ fcHintEdit->text() + "<br>");
        }

        optionsText.append("<br><b>Reverse side</b>");
        optionsText.append("<br>");
        optionsText.append("<b>Answer: </b>");
        optionsText.append(fcAnswerEdit->text());
    }

    iQuestionTextList.append(questionEdit->toPlainText());
    iHintList.append(fcHintEdit->text());
    qDebug()<<"Hint is "+ fcHintEdit->text() +".";
    qDebug()<<fcImagePathLabel->text();
    if (fcImagePathLabel->text() != "No image selected")
    {
    iImageList.append(fcImagePathLabel->text());
    }
    else
    {
     iImageList.append("");
    }
    iAnsList.append(fcAnswerEdit->text());

    iQuestionItemList.append(new QuestionItem(noOfQues,quesText + optionsText));
    widget2_vlayout->addWidget(iQuestionItemList.at(noOfQues));
    connect(iQuestionItemList.at(noOfQues), SIGNAL(removeClicked(int)), this, SLOT(removeQuestion(int)));
    noOfQues++;

    questionEdit->clear();
    fcImagePathLabel->setText("No image selected");
    fcHintEdit->clear();
    fcAnswerEdit->clear();
}

void FlashcardTemplate::on_generateButton_clicked()
{
    if (iQuestionTextList.count()==0)
    {
          QMessageBox::information(this,"No flashcards added!" , "Please add some flashcards before generating the application!");
          return;
    }

    QDir dir;
    dir.mkdir("assets");
    dir.mkdir("res");
    dir.mkdir("res/drawable-hdpi");
    QFile indexFile("assets/flashcard_content.txt");
    indexFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&indexFile);

    out << quizName;
    out << "\n";
    out << authorName;
    out << "\n";

    for (int i=0; i<iQuestionTextList.count(); i++)
    {
        QString str_to_write =  "";
        qDebug()<< "W" + iImageList.at(i) +"EOM";
        if (iImageList.at(i) == "")
        {
        str_to_write = "NOIMAGE__" + iQuestionTextList.at(i) + "==" + iAnsList.at(i);
        }
        else{
            str_to_write = "IMAGE__" + iQuestionTextList.at(i) + "==" + iAnsList.at(i);
        }

        if (iHintList.at(i) != "")
        {
            str_to_write.append("=="+ iHintList.at(i));
        }
        out << str_to_write;
        out << "\n";
    }
    indexFile.close();

    qDebug()<<iImageList;

    for (int i=0; i<iImageList.length();i++)
    {
        QString image = iImageList.at(i);
        qDebug()<<image;
        if (image != "")
        {
            QString fileExt = image.split(".").last();
            qDebug()<<fileExt;
            QFile::copy(image, "res/drawable-hdpi/image"+QString::number(i) + "."+ fileExt);
        }
    }

    QString zipBin = "7za";
    #if defined(WIN32) ||  defined(_WIN32) ||  defined(__WIN32)
        zipBin += ".exe";
        QDir::setCurrent(QCoreApplication::applicationDirPath());
    #endif

    QFile::copy("config/templates/BuildmLearnFlashCards.apk", "config/BuildmLearnFlashCards_in_use.zip");
    //execWindowsCommand("copy config/templates/BuildmLearnFlashCards.apk config/BuildmLearnFlashCards_in_use.zip");

    execWindowsCommand("config/templates/" +  zipBin + " a config/BuildmLearnFlashCards_in_use.zip assets");
    execWindowsCommand("config/templates/" +  zipBin + " a config/BuildmLearnFlashCards_in_use.zip res");
    execWindowsCommand("java -jar config/templates/signapk.jar config/templates/certificate.pem config/templates/key.pk8 config/BuildmLearnFlashCards_in_use.zip applications/BuildmLearnFlashCards_signed.apk");
    //execWindowsCommand("java -jar templates/signapk.jar config/templates/certificate.pem config/templates/key.pk8 config/BuildmLearnFlashCards_in_use.zip BuildmLearnFlashCards_signed.apk");

    QFile::remove("config/BuildmLearnFlashCards_in_use.zip");
    //execWindowsCommand("del config/BuildmLearnFlashCards_in_use.zip");

    for (int i=0; i<iImageList.length();i++)
    {
        QString image = iImageList.at(i);
        qDebug()<<image;
        if (image != "")
        {
            QString fileExt = image.split(".").last();
            qDebug()<<fileExt;
            QFile::remove("res/drawable-hdpi/image"+QString::number(i) + "."+ fileExt);
        }
    }

    indexFile.remove();
    dir.rmdir("assets");
    dir.rmdir("res/drawable-hdpi");
    dir.rmdir("res");
    QMessageBox::information(this,"Application generated" , "Your application has been generated. For the installation file, please check /applications folder. ");

}


void FlashcardTemplate::execWindowsCommand(QString command)
{
    QTime time;
    qDebug()<<time.currentTime().toString();
    qDebug()<<"cmd: "+command;
    //QStringList args;
    //args<<"/C"<<command;
    iProcess->start(command);
    iProcess->waitForFinished(-1);
    qDebug()<<iProcess->readAll()<<time.currentTime().toString();

}


void FlashcardTemplate::execWindowsCommandDetached(QString command)
{
    qDebug()<<"detached cmd: "+command;
    QStringList args;
    args<<"/C"<<command;
    iProcess->startDetached("cmd.exe",args);
}

void FlashcardTemplate::removeQuestion(int index)
{
    qDebug()<<"removeQuestionssss: "+QString::number(index);
    delete iQuestionItemList.takeAt(index);

    for (int i=index; i<iQuestionItemList.length(); i++)
    {
        iQuestionItemList.at(i)->setIndex(iQuestionItemList.at(i)->getIndex()-1);

    }

    iQuestionTextList.removeAt(index);
    iHintList.removeAt(index);
    iImageList.removeAt(index);
    iAnsList.removeAt(index);

    qDebug()<<iQuestionTextList;
    qDebug()<<iAnsList;
    qDebug()<<"===============";

    noOfQues--;
}

void FlashcardTemplate::optionAdded()
{
}

void FlashcardTemplate::startSimulaton_clicked()
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

void FlashcardTemplate::startQuiz()
{
    qDebug()<<"Start clicked";
    phoneWidget->setCurrentIndex(1);
    populateQuiz(questionCounter);
}

void FlashcardTemplate::populateQuiz(int index)
{
    if (index<iQuestionTextList.length())
    {
        // Load new question
        questionLabel_phone->setText("Question "+ QString::number(index+1));
        questionText_phone->setText(iQuestionTextList.at(index));

        fcImage_phone->setVisible(false);
        if (iImageList.at(index)!="")
        {
            qDebug()<<"Image: " + iImageList.at(index);
            fcImage_phone->setStyleSheet("border-image: url("+iImageList.at(index)+");");
            fcImage_phone->setVisible(true);
        }


        fcHintLabel_phone->setVisible(false);
        if (iHintList.at(index)!="")
        {
            qDebug()<<"Hint: " + iHintList.at(index);
            fcHintLabel_phone->setText(iHintList.at(index));
            fcHintLabel_phone->setVisible(true);
        }


        fcAnswerLabel_phone->setVisible(false);
        if (iAnsList.at(index)!="")
        {
            qDebug()<<"Answer: " + iAnsList.at(index);
            fcAnswerLabel_phone->setText(iAnsList.at(index));
        }

    }

}

void FlashcardTemplate::flipButton_phone_clicked()
{
    if (fcAnswerLabel_phone->isVisible())
    {
        fcAnswerLabel_phone->setVisible(false);
        if(fcHintLabel_phone->text()!="")
        {
            fcHintLabel_phone->setVisible(true);
        }
        qDebug()<<"stylesheet: "+ fcImage_phone->styleSheet();
        if (fcImage_phone->styleSheet().contains("border-image"))
        {
            fcImage_phone->setVisible(true);
        }

    }
    else{
        fcAnswerLabel_phone->setVisible(true);
        fcHintLabel_phone->setVisible(false);
        fcImage_phone->setVisible(false);
    }
}

void FlashcardTemplate::prevButton_phone_clicked()
{
    if (questionCounter!=0)
    {
        questionCounter--;
        populateQuiz(questionCounter);
    }
}

void FlashcardTemplate::restartQuiz_phone_clicked()
{
    phoneWidget->setCurrentIndex(0);
}


void FlashcardTemplate::nextButton_phone_clicked()
{
    qDebug()<<iQuestionTextList.count();
    if (questionCounter<iQuestionTextList.count()-1)
    {
        questionCounter++;
        populateQuiz(questionCounter);
    }
    else if (questionCounter==iQuestionTextList.count()-1)
    {
        // if no more questions
            qDebug()<<"Over to screen3";
            phoneWidget->setCurrentIndex(2);
            questionCounter=0;
    }
}


void FlashcardTemplate::updateStartPage_phone()
{
    quizNameLabel_phone->setText(quizName);
    quizAuthorLabel_phone->setText(authorName);
}

void FlashcardTemplate::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "MyFlashCardsApp.buildmlearn",
                                tr("*.buildmlearn"));
    QFile indexFile(fileName);
    indexFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&indexFile);

    out << "FlashCardsTemplate" + GlobalData::IO_LD + quizName + GlobalData::IO_LD + authorName;

    for (int i=0; i<iQuestionTextList.count(); i++)
    {
        out << GlobalData::IO_LD;
        QString str_to_write =  "";

        if (iImageList.at(i) == "")
        {
        str_to_write = "NOIMAGE__" + iQuestionTextList.at(i) + "==" + iAnsList.at(i);
        }
        else{
            str_to_write = "IMAGE__" + iQuestionTextList.at(i) + "==" + iAnsList.at(i);
        }

        if (iHintList.at(i) != "")
        {
            str_to_write.append("=="+ iHintList.at(i));
        }

        if (iImageList.at(i) != "")
        {
            str_to_write.append("=="+ iImageList.at(i));
        }

        out << str_to_write;
    }
    indexFile.close();

}
void FlashcardTemplate::on_open_clicked(QStringList dataList)
{
    qDebug()<<dataList;
    iQuestionItemList.clear();
    iQuestionTextList.clear();
    iHintList.clear();
    iImageList.clear();
    iAnsList.clear();

    quizName = dataList.at(0);
    authorName = dataList.at(1);
    dataList.removeFirst();
    dataList.removeFirst();

    updateStartPage_phone();

    noOfQues =0;

    for (int i=0; i<dataList.length();i++)
    {
        QStringList data = dataList.at(i).split("__");
        qDebug()<<data;

        QString quesText;
        qDebug()<<"N"<<data.at(0).compare("NOIMAGE");
        qDebug()<<data.at(0).compare("IMAGE");
        if (data.at(0).compare("NOIMAGE")==0)
        {
            qDebug()<<"NoImage";
            QStringList qData = data.at(1).split("==");

            iQuestionTextList.append(qData.at(0)); //q
            iAnsList.append(qData.at(1)); //a
            iHintList.append(qData.at(2)); //h
            iImageList.append(""); //append a placeholder for the list


            quesText = "<br><br>" +iQuestionTextList.at(i)+" <br><br>";
            quesText.append("<b>Front side</b>");
            quesText.append("<br>");
            quesText.append("<b>Hint/Text:</b> "+ iHintList.at(i) + "<br>");
            quesText.append("<br><b>Reverse side</b>");
            quesText.append("<br>");
            quesText.append("<b>Answer: </b>");
            quesText.append(iAnsList.at(i));



        }
        if (data.at(0).compare("IMAGE")==0)
        {
            qDebug()<<"Image";
            QStringList qData = data.at(1).split("==");
            iQuestionTextList.append(qData.at(0)); //q
            iAnsList.append(qData.at(1)); //a


            if (qData.count()>3)
            {
                // has hint and image both
                iHintList.append(qData.at(2)); //h
                iImageList.append(qData.at(3)); //i
            }
            else{
                iHintList.append(""); //append a placeholder
                iImageList.append(qData.at(2)); //i
            }


            quesText = "<br><br>" +iQuestionTextList.at(i)+" <br><br>";
            quesText.append("<b>Front side</b>");
            quesText.append("<br>");
            quesText.append("<b>Image:</b> " + iImageList.at(i) + "<br>");

            if (qData.count()>3)
            {
                // if hint is not present
                quesText.append("<b>Hint/Text:</b> "+ iHintList.at(i) + "<br>");
            }

            quesText.append("<br><b>Reverse side</b>");
            quesText.append("<br>");
            quesText.append("<b>Answer: </b>");
            quesText.append(iAnsList.at(i));
        }

        iQuestionItemList.append(new QuestionItem(noOfQues,quesText));
        widget2_vlayout->addWidget(iQuestionItemList.at(noOfQues));
        connect(iQuestionItemList.at(noOfQues), SIGNAL(removeClicked(int)), this, SLOT(removeQuestion(int)));
        noOfQues++;

    }

}
