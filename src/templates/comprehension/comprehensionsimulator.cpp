/*
  Copyright (c) 2015, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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
#include "templates/comprehension/comprehensioneditor.h"
#include "templates/comprehension/comprehensionitem.h"
#include "definitions/definitions.h"

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QDebug>


ComprehensionSimulator::ComprehensionSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::ComprehensionSimulator) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);
  m_ui->m_lblTitle->setFont(caption_font);
  m_ui->m_lblTimer->setFont(caption_font);
  m_ui->m_lblComplete->setFont(caption_font);
  m_ui->m_lblComplete->setWordWrap(true);
  
  // Set styling.
  QString style = "QPushButton {min-height:1.5em; font:1em; margin:0 1px 0 1px; color: white; \
                   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff3232, \
                   stop: 1 #e50000); border-style: outset;border-radius: 3px; border-width: 1px; \
                   border-color: #ff0000;} QPushButton:pressed {background-color: \
                   qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e50000, stop: 1 #ff3232);}";

  m_ui->m_btnStart->setStyleSheet(style);
  m_ui->m_btnExit->setStyleSheet(style);
  
  style = "QPushButton{min-height:1.5em; font:1em; margin:0 1px 0 1px; color: white; \
           background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #329932, stop: \
           1 #004C00); border-style: outset;border-radius: 3px; border-width: 1px; \
           border-color: #50873a;} QPushButton:pressed {background-color: \
           qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #004C00, stop: 1 #329932);}";
  
  m_ui->m_btnQuestions->setStyleSheet(style);
  m_ui->m_btnRestart->setStyleSheet(style);

  style = "QTextEdit {color: black; background-color: white;} QScrollBar {background-color: grey; border-style: \
           outset;border-radius: 3px; border-width: 1px; border-color: black;}";

  m_ui->m_txtPassage->setStyleSheet(style);
  m_ui->m_txtPassage->setReadOnly(true);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(exit()));

  connect(m_ui->m_btnQuestions, SIGNAL(clicked()), this, SLOT(questionStart()));
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(counter()));

}

ComprehensionSimulator::~ComprehensionSimulator() {
  qDebug("Destroying ComprehensionSimulator instance.");

  delete m_ui;
}

bool ComprehensionSimulator::startSimulation() {
  editor = static_cast<ComprehensionEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active questions or comprehension does not
    // containt its name or author name.
    return false;
  }

  // Remove existing questions.
  while (m_ui->m_phoneWidget->count() > 4) {
    QWidget *question_widget = m_ui->m_phoneWidget->widget(3);

    m_ui->m_phoneWidget->removeWidget(question_widget);
    question_widget->deleteLater();
  }

  // Load the questions, setup the comprehension and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

  m_ui->m_lblTitle->setText(editor->m_ui->m_txtTitle->lineEdit()->text());
  m_ui->m_txtPassage->setDocument(editor->m_ui->m_txtPassage->document());

  int question_number = 1;
  QList<ComprehensionQuestion> questions = editor->activeQuestions();

  foreach (const ComprehensionQuestion &question, questions) {
    ComprehensionItem *item = new ComprehensionItem(m_ui->m_phoneWidget);

    connect(item, SIGNAL(questionSubmitted()), this, SLOT(questionSubmitted()));

    item->setQuestion(question, question_number++, questions.size());
    m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, item);
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);
  return true;
}

bool ComprehensionSimulator::stopSimulation() {
  m_ui->m_phoneWidget->slideInIdx(0);

  emit canGoBackChanged(false);

  return true;
}

bool ComprehensionSimulator::goBack() {
  return false;
}

// Start the simulator.
void ComprehensionSimulator::start() {
  int seconds = editor->m_ui->m_txtTimer->lineEdit()->text().toInt();
  time.setHMS(0, seconds / 60, seconds % 60);
  m_ui->m_lblTimer->setText("- " + time.toString("mm:ss"));
  timer->start(1000);

  m_ui->m_phoneWidget->slideInIdx(2);

}

// Prepare the score card.
void ComprehensionSimulator::prepareSummary() {
  int answered_correctly = 0;
  int answered_wrongly = 0;
  int unanswered = 0;

  for (int i = 3; i < m_ui->m_phoneWidget->count() - 1; i++) {
    ComprehensionItem *widget = static_cast<ComprehensionItem*>(m_ui->m_phoneWidget->widget(i));

    switch (widget->state()) {
      case ComprehensionItem::AnsweredCorrectly:
        answered_correctly++;
        break;

      case ComprehensionItem::AnsweredWrongly:
        answered_wrongly++;
        break;

      case ComprehensionItem::Unanswered:
      default:
        unanswered++;
        break;
    }
  }

  m_ui->m_lblTotalCorrect->setText(tr("Total correct: %1").arg(answered_correctly));
  m_ui->m_lblTotalWrong->setText(tr("Total wrong: %1").arg(answered_wrongly));
  m_ui->m_lblTotalUnanswered->setText(tr("Total unanswered: %1").arg(unanswered));
}

void ComprehensionSimulator::questionSubmitted() {
  int current_index = m_ui->m_phoneWidget->currentIndex();

  if (current_index == m_ui->m_phoneWidget->count() - 2) {
    // This is the last confirmed question. Go to "summary".
    prepareSummary();
  }

  m_ui->m_phoneWidget->slideInIdx(current_index + 1);
}

void ComprehensionSimulator::restart() {
  // Reset all the questions.
  for (int i = 3; i < m_ui->m_phoneWidget->count() - 1; i++) {
    static_cast<ComprehensionItem*>(m_ui->m_phoneWidget->widget(i))->reset();
  }

  m_ui->m_phoneWidget->slideInIdx(1);
}

void ComprehensionSimulator::exit() {
  stopSimulation();
  emit simulationStopRequested();
}

void ComprehensionSimulator::questionStart() {
  timer->stop();
  m_ui->m_phoneWidget->slideInNext();
}

void ComprehensionSimulator::counter() {
  time = time.addSecs(-1);
  m_ui->m_lblTimer->setText("- " + time.toString("mm:ss"));
  if(time == QTime(0,0)) {
    timer->stop();
    questionStart();
  }
}
