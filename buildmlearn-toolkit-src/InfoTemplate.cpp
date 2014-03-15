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

#include<QVBoxLayout>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QMessageBox>
#include<QFileDialog>

#include "InfoTemplate.h"
#include "GlobalData.h"

InfoTemplate::InfoTemplate(QWidget *parent) :
    QWidget(parent)
{
    widget1 = new QWidget();
    widget2 = new QWidget();
    widget3 = new QWidget();

    // widget 1 initialization

    QVBoxLayout* widget1_vlayout=  new QVBoxLayout(widget1);
    QHBoxLayout* widget1_vlayout_hlayout = new QHBoxLayout();
    qDebug()<<"2";

    addButton = new QPushButton("Add");
    lineEdit = new QLineEdit();
    removeButton = new QPushButton("Remove");

    widget1_vlayout_hlayout->addWidget(lineEdit);
    widget1_vlayout_hlayout->addWidget(addButton);

    itemList = new QListWidget();

    widget1_vlayout->addLayout(widget1_vlayout_hlayout);
    widget1_vlayout->addWidget(itemList);
    widget1_vlayout->addWidget(removeButton);

    // widget 2 initialization

    QVBoxLayout* widget2_vlayout=  new QVBoxLayout(widget2);
    textEdit = new QPlainTextEdit();


    qDebug()<<"3";
    widget2_vlayout->addWidget(textEdit);

    // widget 3 initialization
    phoneBody = new QLabel(widget3);
    QVBoxLayout* widget3_vlayout=  new QVBoxLayout(widget3);


    phoneBody->setFixedSize(327,639);
    phoneBody->setStyleSheet("background-image: url(:/images/phone.png)");

    phoneWidget = new QStackedWidget(phoneBody);
    phoneWidget->setStyleSheet("background: black; color: white; font-size: 30px");
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
    phoneWidget->addWidget(screen1);
    phoneWidget->addWidget(screen2);

    itemList_phone = new QListWidget(screen1);
    itemList_phone->setStyleSheet( "QListWidget::item { color: white; border-bottom: 0.5px solid #333333; }") ;
    itemList_phone->setFixedSize(phoneWidget->size());


    textLabel_phone= new QLabel(screen2);
    textLabel_phone->setFixedSize(phoneWidget->size());
    textLabel_phone->setAlignment(Qt::AlignTop);
//    textLabel_phone->setStyleSheet("background: yellow");
    textLabel_phone->setFixedSize(phoneWidget->size());
    textLabel_phone->setStyleSheet("background: black; color: white; font-size: 20px");
    textLabel_phone->setWordWrap(true);

    phoneWidget->setCurrentIndex(0);

    ///
    QHBoxLayout* hlayout = new QHBoxLayout(this);

    hlayout->addWidget(widget1);
    hlayout->addWidget(widget2);
    hlayout->addWidget(widget3);




    iProcess = new QProcess(this);

    // Signal and slots

    connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButton_cicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(on_removedButton_cicked()));
    connect(itemList, SIGNAL(currentRowChanged(int)), this, SLOT(on_itemList_selected()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(on_textEdit_textChanged()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()));
    connect(itemList_phone, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_itemList_phone_selected()));
    connect(generateButton, SIGNAL(clicked()), this, SLOT(on_generateButton_clicked()));
}

void InfoTemplate::on_addButton_cicked()
{
    if (lineEdit->text().length()>0)
    {
        iTitleList.append(lineEdit->text());
        iDescriptionList.append("");
        itemList->addItem(lineEdit->text());
        itemList_phone->addItem(lineEdit->text());
        lineEdit->clear();
    }
}

void InfoTemplate::on_removedButton_cicked()
{
    itemList->takeItem(itemList->currentRow());
    itemList_phone->takeItem(itemList->currentRow());
    iTitleList.removeAt(itemList->currentRow());
    iDescriptionList.removeAt(itemList->currentRow());
}

void InfoTemplate::on_itemList_selected()
{
    textEdit->setPlainText(iDescriptionList.at(itemList->currentRow()));
}

void InfoTemplate::on_textEdit_textChanged()
{
    qDebug()<<"Start:";
    qDebug()<<iDescriptionList;
    iDescriptionList.removeAt((itemList->currentRow()));
    iDescriptionList.insert(itemList->currentRow(), textEdit->toPlainText());
    qDebug()<<"End:";
    qDebug()<<iDescriptionList;
}

void InfoTemplate::on_itemList_phone_selected()
{
    textLabel_phone->setText(iDescriptionList.at(itemList_phone->currentRow()));
    phoneWidget->setCurrentIndex(1);
}

void InfoTemplate::on_backButton_clicked()
{
    if (phoneWidget->currentIndex() == 0)
    {
        phoneWidget->setCurrentIndex(1);
    }
    else
    {
        phoneWidget->setCurrentIndex(0);
    }
}

void InfoTemplate::on_generateButton_clicked()
{
    if (iTitleList.count()==0)
    {
      QMessageBox::information(this,"No topics added!" , "Please add some topics, and content before generating the application!");
      return;
    }

    QDir dir;
    dir.mkdir("assets");
    QFile indexFile("assets/index.txt");
    indexFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&indexFile);

    for (int i=0; i<iTitleList.count(); i++)
    {
        out << iTitleList.at(i);
        out << "\n";
    }
    indexFile.close();


//    qDebug()<<iDescriptionList;

    for (int i=0;i<iDescriptionList.count(); i++)
    {
        QFile file("assets/"+ iTitleList.at(i)+".txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        out << iDescriptionList.at(i);

        file.close();
    }

    execWindowsCommand("copy config\\templates\\BuildmLearnInfo.apk config\\BuildmLearnInfo_in_use.zip");
    execWindowsCommand("config\\templates\\7za.exe a config\\BuildmLearnInfo_in_use.zip assets");
    execWindowsCommand("config\\templates\\signapk.jar config\\templates\\certificate.pem config\\templates\\key.pk8 config\\BuildmLearnInfo_in_use.zip applications\\BuildmLearnInfo_signed.apk");
    execWindowsCommand("del config\\BuildmLearnInfo_in_use.zip");

    // delete temp files

    for (int i=0;i<iDescriptionList.count(); i++)
    {
        QFile file("assets/"+ iTitleList.at(i)+".txt");
            file.remove();
    }
    indexFile.remove();
    dir.rmdir("assets");

    QMessageBox::information(this,"Application generated" , "Your application has been generated. For the installation file, please check /applications folder. ");
}

void InfoTemplate::execWindowsCommand(QString command)
{
    qDebug()<<"cmd: "+command;
    QStringList args;
    args<<"/C"<<command;
    iProcess->start("cmd.exe",args);
    iProcess->waitForFinished(-1);
}


void InfoTemplate::execWindowsCommandDetached(QString command)
{
    qDebug()<<"detached cmd: "+command;
    QStringList args;
    args<<"/C"<<command;
    iProcess->startDetached("cmd.exe",args);
}

void InfoTemplate::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "MyInfoApp.buildmlearn",
                                tr("*.buildmlearn"));
    QFile indexFile(fileName);
    indexFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&indexFile);

    out<<"InfoTemplate";

    for (int i=0; i<iTitleList.count(); i++)
    {
        out << GlobalData::IO_LD;
        out << iTitleList.at(i);
        out << GlobalData::IO_ILD;
        out << iDescriptionList.at(i);
    }
    indexFile.close();
}

void InfoTemplate::on_open_clicked(QStringList dataList)
{
    iTitleList.clear();
    iDescriptionList.clear();
    for (int i=0; i<dataList.length();i++)
    {
        QStringList data = dataList.at(i).split(GlobalData::IO_ILD);
        iTitleList.append(data.at(0));
        iDescriptionList.append(data.at(1));
    }

    itemList->addItems(iTitleList);
    itemList_phone->addItems(iTitleList);
}
