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

#include "templates/quiz/quizitem.h"

#include "definitions/definitions.h"


QuizItem::QuizItem(QWidget *parent) : QWidget(parent), m_state(Unanswered), m_ui(new Ui::QuizItem) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblQuestionNumber->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADER_SIZE_INCREASE);
  m_ui->m_lblQuestionNumber->setFont(caption_font);

  setupButtons();
  createConnections();
}

QuizItem::~QuizItem() {
  delete m_ui;
}

void QuizItem::setupButtons() {
  m_answerButtons = QList<QRadioButton*>();
  m_answerButtons.append(m_ui->m_rbAnswerOne);
  m_answerButtons.append(m_ui->m_rbAnswerTwo);
  m_answerButtons.append(m_ui->m_rbAnswerThree);
  m_answerButtons.append(m_ui->m_rbAnswerFour);
}

void QuizItem::createConnections() {
  connect(m_ui->m_btnNext, SIGNAL(clicked()), this, SLOT(onNextClicked()));
  connect(m_ui->m_btnConfirm, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
  connect(m_ui->m_rbAnswerOne, SIGNAL(toggled(bool)), m_ui->m_lblWarning, SLOT(hide()));
  connect(m_ui->m_rbAnswerTwo, SIGNAL(toggled(bool)), m_ui->m_lblWarning, SLOT(hide()));
  connect(m_ui->m_rbAnswerThree, SIGNAL(toggled(bool)), m_ui->m_lblWarning, SLOT(hide()));
  connect(m_ui->m_rbAnswerFour, SIGNAL(toggled(bool)), m_ui->m_lblWarning, SLOT(hide()));
}

void QuizItem::clearStylesheets() {
  foreach (QRadioButton *answer_button, m_answerButtons) {
    answer_button->setStyleSheet(QString());
  }
}

void QuizItem::setQuestion(const QuizQuestion &question, int question_number, int total_questions) {
  m_question = question;

  m_ui->m_rbAnswerOne->setText(question.answerOne());
  m_ui->m_rbAnswerTwo->setText(question.answerTwo());
  m_ui->m_rbAnswerThree->setText(question.answerThree());
  m_ui->m_rbAnswerFour->setText(question.answerFour());

  m_ui->m_rbAnswerOne->setVisible(question.correctAnswer() == 0 || !question.answerOne().simplified().isEmpty());
  m_ui->m_rbAnswerTwo->setVisible(question.correctAnswer() == 1 || !question.answerTwo().simplified().isEmpty());
  m_ui->m_rbAnswerThree->setVisible(question.correctAnswer() == 2 || !question.answerThree().simplified().isEmpty());
  m_ui->m_rbAnswerFour->setVisible(question.correctAnswer() == 3 || !question.answerFour().simplified().isEmpty());

  m_ui->m_lblQuestionNumber->setText(tr("Question number %1 of %2").arg(QString::number(question_number),
                                                                        QString::number(total_questions)));
  m_ui->m_lblQuestionText->setText(question.question());
}

QuizItem::State QuizItem::state() const {
  return m_state;
}

void QuizItem::reset() {
  clearStylesheets();

  foreach (QRadioButton *answer_button, m_answerButtons) {
    // Hacky way to really force all radio buttons to be unchecked.
    answer_button->setEnabled(false);
    answer_button->setCheckable(false);
    answer_button->setChecked(false);
    answer_button->setEnabled(true);
    answer_button->setCheckable(true);
  }

  m_ui->m_lblWarning->setVisible(false);
  m_ui->m_btnConfirm->setEnabled(true);
  m_state = Unanswered;
}

void QuizItem::onNextClicked() {
  // Just signal that user is done with this question.
  emit questionSubmitted();
}

void QuizItem::onSubmitClicked() {
  // Check if user selected any answer, if he did not, then remind him it.
  if (!m_ui->m_rbAnswerOne->isChecked() && !m_ui->m_rbAnswerTwo->isChecked() &&
      !m_ui->m_rbAnswerThree->isChecked() && !m_ui->m_rbAnswerFour->isChecked()) {
    // No answer seems to be selected.
    m_ui->m_lblWarning->setText("Select some answer, please.");
    m_ui->m_lblWarning->setVisible(true);
  }
  else {
    int selected_answer = 0;

    // User selected some answer, highlight correct and incorrect answer.
    for (int i = 0; i < m_answerButtons.size(); i++) {
      if (m_answerButtons.at(i)->isChecked()) {
        selected_answer = i;
      }
    }

    if (selected_answer == m_question.correctAnswer()) {
      m_ui->m_lblWarning->setText("That is correct answer.");
      m_answerButtons.at(selected_answer)->setStyleSheet("background-color: green;");
      m_state = AnsweredCorrectly;
    }
    else {
      m_ui->m_lblWarning->setText("That is wrong answer.");
      m_answerButtons.at(selected_answer)->setStyleSheet("background-color: red;");
      m_answerButtons.at(m_question.correctAnswer())->setStyleSheet("background-color: green;");
      m_state = AnsweredWrongly;
    }

    foreach (QRadioButton *button, m_answerButtons) {
      button->setEnabled(false);
    }

    m_ui->m_btnConfirm->setEnabled(false);
    m_ui->m_lblWarning->setVisible(true);
  }
}
