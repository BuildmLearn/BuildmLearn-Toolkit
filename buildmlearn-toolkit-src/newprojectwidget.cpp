#include "newprojectwidget.h"

int WIDGET_WIDTH = 560;
int WIDGET_HEIGHT = 480;
int TEMPLATE_WIDTH = 200;
int TEMPLATE_HEIGHT = 400;
int RIGHT_WIDGET_WIDTH = 300;
int INFO_WIDGET_HEIGHT = 50;


NewProjectWidget::NewProjectWidget(QWidget *parent) :
    QMainWindow(parent)
{
    // Initializing lists
    iTemplateInfoList <<"Choose this template if you wish to create an Informative app. The template presents a list and a detail view."
    << "Choose this template if you wish to create a test or quiz application."
     << "Choose this template if you wish to create a flashcard collection.";

    iTemplateImageList <<"background-image: url(:/images/InfoTemplate.png)" << "background-image: url(:/images/QuizTemplate.png)"
                         << "background-image: url(:/images/FlashCardsTemplate.png)";

    setFixedSize(560,480);
    setWindowTitle("New Application");

    iWidget = new QWidget(this);
    iWidget->setFixedSize(size());
//    iWidget->setStyleSheet("background: white");

    QVBoxLayout* v_layout= new QVBoxLayout(iWidget);
    QHBoxLayout* h_layout1=  new QHBoxLayout();
    QHBoxLayout* h_layout2=  new QHBoxLayout();


    iChooseTemplateLabel = new QLabel(this);
    iChooseTemplateLabel->setText("Choose a template:");
    v_layout->addWidget(iChooseTemplateLabel);

    iTemplateList = new QListWidget(this);

    iTemplateList->setFixedSize(TEMPLATE_WIDTH,TEMPLATE_HEIGHT- iChooseTemplateLabel->height());
    iTemplateList->setStyleSheet("font-size: 20px;");

    iTemplateList->addItem("Informative");
    iTemplateList->addItem("Quiz / Test");
    iTemplateList->addItem("Flashcards");

    h_layout1->addWidget(iTemplateList);


    // Right Widget starts
    iRightWidget = new QWidget(this);
    iRightWidget->setFixedSize(RIGHT_WIDGET_WIDTH, iTemplateList->height());
//    iRightWidget->setStyleSheet("background: white");

    iRightImageWidget = new QLabel(iRightWidget);
    iRightInfoWidget = new QLabel(iRightWidget);


    iRightInfoWidget->setStyleSheet("background-color: white; padding: 5px;");


    iRightInfoWidget->setAlignment(Qt::AlignLeft);
    iRightInfoWidget->setWordWrap(true);
    iRightImageWidget->setStyleSheet(iTemplateImageList.at(0));
    iRightInfoWidget->setText(iTemplateInfoList.at(0));


    int height_image_widget = iRightWidget->height()-INFO_WIDGET_HEIGHT;

    iRightImageWidget->setGeometry(0,0,iRightWidget->width(), height_image_widget);
    iRightInfoWidget->setGeometry(0,height_image_widget, iRightWidget->width(), iRightWidget->height());


    h_layout1->addWidget(iRightWidget);

    // Right Widget ends


//    h_layout1->addLayout(v_layout1);
//    h_layout1->addWidget(iRightWidget);

    v_layout->addLayout(h_layout1);


    iOpenButton = new QPushButton("Open Existing Application", this);

    iChooseButton = new QPushButton("Choose",this);
    iChooseButton->setFixedWidth(100);
//    iCancelButton= new QPushButton("Cancel",this);
//    iCancelButton->setFixedWidth(100);
    h_layout2->addWidget(iOpenButton,0, Qt::AlignLeft);
    h_layout2->addWidget(iChooseButton,0, Qt::AlignRight);

    v_layout->addLayout(h_layout2);


    connect(iTemplateList, SIGNAL(currentRowChanged(int)), this, SLOT(TemplateSelectionChanged(int)));
    connect(iChooseButton, SIGNAL(clicked()), this, SLOT(iChooseButton_clicked()));
    connect(iOpenButton, SIGNAL(clicked()), this, SLOT(iOpenButton_clicked()));

    iTemplateList->setCurrentRow(1);

}


void NewProjectWidget::TemplateSelectionChanged(int index)
{
    iRightImageWidget->setStyleSheet(iTemplateImageList.at(index));
    iRightInfoWidget->setText(iTemplateInfoList.at(index));
}

void NewProjectWidget::iChooseButton_clicked()
{
    this->hide();
    startProject(iTemplateList->currentRow());
}

void NewProjectWidget::iOpenButton_clicked()
{
    this->hide();
    startProject(-1);
}
