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

#include "templates/comprehension/comprehensionsimulator.h"

#include "core/templatecore.h"
#include "templates/comprehension/comprehensioncore.h"
#include "templates/comprehension/comprehensioneditor .h"
#include "definitions/definitions.h"
#include "templates/comprehension/comprehensionquestionitem.h"
#include "templates/comprehension/comprehensionpassageitem.h"
#include "templates/comprehension/comprehensionpassage.h"
#include "templates/comprehension/comprehensionquestion.h"

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


ComprehensionSimulator::ComprehensionSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::ComprehensionSimulator) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(exit()));
}

ComprehensionSimulator::~ComprehensionSimulator() {
  qDebug("Destroying ComprehensionSimulator instance.");

  delete m_ui;
}

bool ComprehensionSimulator::startSimulation() {
  ComprehensionEditor *editor = static_cast<ComprehensionEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active questions or quiz does not passage
    // containt its name or author name.
    return false;
  }

  // Remove existing passage and questions.
  while (m_ui->m_phoneWidget->count() > 4) {
    QWidget *passage_widget = m_ui->m_phoneWidget->widget(2);
    QWidget *question_widget = m_ui->m_phoneWidget->widget(3);
    m_ui->m_phoneWidget->removeWidget(passage_widget);
    m_ui->m_phoneWidget->removeWidget(question_widget);
	passage_widget->deleteLater();
    question_widget->deleteLater();
  }

  // Load the questions, setup the quiz and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

   ComprehensionPassage passage = editor->activePassage();
   ComprehensionPassageItem *passageitem = new ComprehensionPassageItem(m_ui->m_phoneWidget);
   connect(passageitem, SIGNAL(passageReaded()), this, SLOT(passageReaded()));
   connect(passageitem, SIGNAL(passageAborted()), this, SLOT(passageAborted()));
   passageitem->setComprehensionPassage(passage);
   m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, passageitem);
   
  int question_number = 1;
  QList<ComprehensionQuestion> questions = editor->activeQuestions();

  foreach (const ComprehensionQuestion &question, questions) {

    ComprehensionQuestionItem *item = new ComprehensionQuestionItem(m_ui->m_phoneWidget);
    connect(item, SIGNAL(questionSubmitted()), this, SLOT(questionSubmitted()));

    item->setQuestion(question, question_number++, questions.size());
    m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, item);
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);
  return true;
}

bool  ComprehensionSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool  ComprehensionSimulator::goBack() {
  return false;
}


void  ComprehensionSimulator::start() {
  m_ui->m_phoneWidget->setCurrentIndex(2);
}


void  ComprehensionSimulator::prepareSummary() {
  int answered_correctly = 0;
  int answered_wrongly = 0;
  int unanswered = 0;

  for (int i = 2; i < m_ui->m_phoneWidget->count() - 1; i++) {
    ComprehensionQuestionItem *widget = static_cast< ComprehensionQuestionItem*>(m_ui->m_phoneWidget->widget(i));

    switch (widget->state()) {
      case ComprehensionQuestionItem::AnsweredCorrectly:
        answered_correctly++;
        break;

      case ComprehensionQuestionItem::AnsweredWrongly:
        answered_wrongly++;
        break;

      case ComprehensionQuestionItem::Unanswered:
      default:
        unanswered++;
        break;
    }
  }

  m_ui->m_lblTotalCorrect->setText(tr("Total correct %1").arg(answered_correctly));
  m_ui->m_lblTotalWrong->setText(tr("Total wrong %1").arg(answered_wrongly));
  m_ui->m_lblTotalUnanswered->setText(tr("Total unanswered %1").arg(unanswered));
}


void ComprehensionSimulator::questionSubmitted() {
  int current_index = m_ui->m_phoneWidget->currentIndex();

  if (current_index == m_ui->m_phoneWidget->count() - 2) {
    // This is the last confirmed question. Go to "summary".
    prepareSummary();
  }

  m_ui->m_phoneWidget->setCurrentIndex(current_index + 1);
}


void ComprehensionSimulator::passageReaded() {
  int current_index = m_ui->m_phoneWidget->currentIndex();

  if (current_index == 2) {
  // This  user had read the passge now ready to face questions
  m_ui->m_phoneWidget->setCurrentIndex(current_index + 1);
  }
}


void ComprehensionSimulator::passageAborted() {
  int current_index = m_ui->m_phoneWidget->currentIndex();
  
  if (current_index == 2) {
  // User aborted quiz during passage read time 
  m_ui->m_phoneWidget->setCurrentIndex(0);
  }

}


void ComprehensionSimulator::restart() {
  // Reset all the questions. Passage require no reset 
  for (int i = 3; i < m_ui->m_phoneWidget->count() - 1; i++) {
    static_cast<ComprehensionQuestionItem*> (m_ui->m_phoneWidget->widget(i))->reset();
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);
}

void ComprehensionSimulator::exit() {
  stopSimulation();
  emit simulationStopRequested();
}
