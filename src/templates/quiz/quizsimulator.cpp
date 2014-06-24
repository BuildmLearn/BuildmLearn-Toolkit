#include "templates/quiz/quizsimulator.h"

#include "core/templatecore.h"
#include "templates/quiz/quizcore.h"
#include "templates/quiz/quizeditor.h"
#include "templates/quiz/quizitem.h"

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


QuizSimulator::QuizSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::QuizSimulator) {
  m_ui->setupUi(this);

  m_ui->m_phoneWidget->setStyleSheet("background: #255593; color: white;");
  m_ui->m_phoneWidget->setFixedSize(270, 447);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
}

QuizSimulator::~QuizSimulator() {
  delete m_ui;
}

bool QuizSimulator::startSimulation() {
  QuizEditor *editor = static_cast<QuizEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active questions or quiz does not
    // containt its name or author name.
    return false;
  }

  // Remove existing questions.
  while (m_ui->m_phoneWidget->count() > 2) {
    QWidget *question_widget = m_ui->m_phoneWidget->widget(1);

    m_ui->m_phoneWidget->removeWidget(question_widget);
    question_widget->deleteLater();
  }

  // Load the questions, setup the quiz and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

  int question_number = 1;

  foreach (const QuizQuestion &question, editor->activeQuestions()) {
    QuizItem *item = new QuizItem(m_ui->m_phoneWidget);

    connect(item, SIGNAL(questionSubmitted()), this, SLOT(questionSubmitted()));

    item->setQuestion(question, question_number++);
    m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, item);
  }

  m_ui->m_phoneWidget->setCurrentIndex(0);

  return true;
}

bool QuizSimulator::stopSimulation() {
  return true;
}

bool QuizSimulator::canGoBack() {
  return false;
}

bool QuizSimulator::goBack() {
  return false;
}

void QuizSimulator::start() {
  m_ui->m_phoneWidget->setCurrentIndex(1);
}

void QuizSimulator::prepareSummary() {
  int answered_correctly = 0;
  int answered_wrongly = 0;
  int unanswered = 0;

  for (int i = 1; i < m_ui->m_phoneWidget->count() - 1; i++) {
    QuizItem *widget = static_cast<QuizItem*>(m_ui->m_phoneWidget->widget(i));

    switch (widget->state()) {
      case QuizItem::AnsweredCorrectly:
        answered_correctly++;
        break;

      case QuizItem::AnsweredWrongly:
        answered_wrongly++;
        break;

      case QuizItem::Unanswered:
      default:
        unanswered++;
        break;
    }
  }

  m_ui->m_lblTotalCorrect->setText(tr("Total correct %1").arg(answered_correctly));
  m_ui->m_lblTotalWrong->setText(tr("Total wrong %1").arg(answered_wrongly));
  m_ui->m_lblTotalUnanswered->setText(tr("Total unanswered %1").arg(unanswered));
}

void QuizSimulator::questionSubmitted() {
  int current_index = m_ui->m_phoneWidget->currentIndex();

  if (current_index == m_ui->m_phoneWidget->count() - 2) {
    // This is the last confirmed question. Go to "summary".
    prepareSummary();
  }

  m_ui->m_phoneWidget->setCurrentIndex(current_index + 1);
}

void QuizSimulator::restart() {

}

void QuizSimulator::launch() {
  emit canGoBackChanged(false);
}
