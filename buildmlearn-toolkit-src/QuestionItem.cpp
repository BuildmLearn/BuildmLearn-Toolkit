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


#include "QuestionItem.h"

#include<QVBoxLayout>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QMessageBox>
#include<QFileDialog>

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

