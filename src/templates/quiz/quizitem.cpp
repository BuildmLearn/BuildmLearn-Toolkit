#include "templates/quiz/quizitem.h"


QuizItem::QuizItem(QWidget *parent) : QWidget(parent), m_ui(new Ui::QuizItem), m_state(Unanswered) {
  m_ui->setupUi(this);

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

void QuizItem::setQuestion(const QuizQuestion &question, int question_number) {
  m_question = question;

  m_ui->m_rbAnswerOne->setText(question.answerOne());
  m_ui->m_rbAnswerTwo->setText(question.answerTwo());
  m_ui->m_rbAnswerThree->setText(question.answerThree());
  m_ui->m_rbAnswerFour->setText(question.answerFour());

  m_ui->m_rbAnswerOne->setVisible(question.correctAnswer() == 1 || !question.answerOne().simplified().isEmpty());
  m_ui->m_rbAnswerTwo->setVisible(question.correctAnswer() == 2 || !question.answerTwo().simplified().isEmpty());
  m_ui->m_rbAnswerThree->setVisible(question.correctAnswer() == 3 || !question.answerThree().simplified().isEmpty());
  m_ui->m_rbAnswerFour->setVisible(question.correctAnswer() == 4 || !question.answerFour().simplified().isEmpty());

  m_ui->m_lblQuestionNumber->setText(tr("Question number %1").arg(question_number));
  m_ui->m_lblQuestionText->setText(question.question());
}

QuizItem::State QuizItem::state() const {
  return m_state;
}

void QuizItem::reset() {
  clearStylesheets();

  foreach (QRadioButton *answer_button, m_answerButtons) {
    answer_button->setEnabled(true);
    answer_button->setChecked(false);
  }

  m_ui->m_lblWarning->setVisible(false);
  m_ui->m_btnConfirm->setEnabled(true);
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
        selected_answer = i + 1;
      }
    }

    if (selected_answer == m_question.correctAnswer()) {
      m_ui->m_lblWarning->setText("That is correct answer.");
      m_answerButtons.at(selected_answer - 1)->setStyleSheet("background-color: green;");
      m_state = AnsweredCorrectly;
    }
    else {
      m_ui->m_lblWarning->setText("That is wrong answer.");
      m_answerButtons.at(selected_answer - 1)->setStyleSheet("background-color: red;");
      m_answerButtons.at(m_question.correctAnswer() - 1)->setStyleSheet("background-color: green;");
      m_state = AnsweredWrongly;
    }

    foreach (QRadioButton *button, m_answerButtons) {
      button->setEnabled(false);
    }

    m_ui->m_btnConfirm->setEnabled(false);
    m_ui->m_lblWarning->setVisible(true);
  }
}
