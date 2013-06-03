#include "InfoTemplate.h"

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
    QMessageBox::information(this,"Application generated" , "Your application has been generated. For the installation file, please check /applications folder. ");
}

void InfoTemplate::execWindowsCommand(QString command)
{
}


void InfoTemplate::execWindowsCommandDetached(QString command)
{

}

