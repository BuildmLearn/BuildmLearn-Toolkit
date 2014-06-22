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
    m_ui->m_phoneWidget->removeWidget(m_ui->m_phoneWidget->widget(1));
  }

  // TODO: Load the questions, setup the quiz and start it.
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

  int question_number = 1;

  foreach (const QuizQuestion &question, editor->activeQuestions()) {
    QuizItem *item = new QuizItem(m_ui->m_phoneWidget);

    item->setQuestion(question, question_number++);
    m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, item);
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);

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

void QuizSimulator::launch() {
  emit canGoBackChanged(false);
}
