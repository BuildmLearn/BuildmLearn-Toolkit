/*
  Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "templates/comprehension/comprehensionpassageitem.h"
#include "templates/comprehension/comprehensioneditor .h"

#include "definitions/definitions.h"


ComprehensionPassageItem::ComprehensionPassageItem(QWidget *parent) : QWidget(parent), m_ui(new Ui::ComprehensionPassageItem) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblQuizName->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADER_SIZE_INCREASE);
  m_ui->m_lblQuizName->setFont(caption_font);

  createConnections();
}

ComprehensionPassageItem::~ComprehensionPassageItem() {
  delete m_ui;
}


void ComprehensionPassageItem::createConnections() {

connect(m_ui->m_exitquiz, SIGNAL(clicked()), this, SLOT(onExitClicked()));
connect(m_ui->m_startquiz, SIGNAL(clicked()),SLOT(onQuestionsClicked()));
}


void  ComprehensionPassageItem::setComprehensionPassage(const  ComprehensionPassage &passage) {
  m_passage = passage;  
  m_ui->m_lblPassageText->setText(passage.passage());
}


void  ComprehensionPassageItem::onQuestionsClicked() { ////
  // Just signal that user is done with passage.
  emit passageReaded();
}


void  ComprehensionPassageItem::onExitClicked() {  ///
//Just signal that user aborted passage or quiz 
emit passageAborted();
}  
