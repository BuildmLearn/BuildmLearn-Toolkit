#include "QuestionItem.h"

QuestionItem::QuestionItem(int index, QString ques_text,QWidget *parent) :
    QWidget(parent)
{
//    <b>Question 1</b><br><br>This is a question, it can be long? <br><br>- Hello<br>- Hello<br>
//    setStyleSheet("background-color:blue");
//    setFixedSize(300, 300);
//    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    iListIndex= index;

    if (iListIndex%2==0)
    {
        setStyleSheet("background-color:white");
    }
    else{
        setStyleSheet("background-color:lightgrey");
    }

//    iGroupBox = new QGroupBox("Question",this);
    iText=ques_text;
    iQuestionLabel = new QLabel("<b><u>Question "+QString::number(index+1)+"</u></b>" + iText);
    iRemoveButton = new QPushButton("Remove");

    iQuestionLabel->setStyleSheet("padding:10px");
    iRemoveButton->setStyleSheet("border-color:grey;border-width:1px;");

    QVBoxLayout* v_layout = new QVBoxLayout;
    v_layout->setSpacing(0);
    v_layout->setMargin(0);
    v_layout->addWidget(iQuestionLabel);
    v_layout->addWidget(iRemoveButton);
    setLayout(v_layout);
//    v_layout->setSizeConstraint( QLayout::SetMinimumSize );
//    iGroupBox->setLayout(v_layout);
//    iGroupBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    connect(iRemoveButton, SIGNAL(clicked()), this, SLOT(iRemoveButton_clicked()));
}

int QuestionItem::getIndex()
{
    return iListIndex;
}

void QuestionItem::setIndex(int index)
{
    iListIndex = index;
    iQuestionLabel->setText("<b><u>Question "+QString::number(index+1)+"</u></b>" + iText);
    if (iListIndex%2==0)
    {
        setStyleSheet("background-color:white");
    }
    else{
        setStyleSheet("background-color:lightgrey");
    }
}

void QuestionItem::iRemoveButton_clicked()
{
    removeClicked(iListIndex);
}

