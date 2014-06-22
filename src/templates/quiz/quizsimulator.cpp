#include "templates/quiz/quizsimulator.h"

#include "core/templatecore.h"
#include "templates/quiz/quizcore.h"
#include "templates/quiz/quizeditor.h"

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


QuizSimulator::QuizSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::QuizSimulator) {
  m_ui->setupUi(this);

  m_ui->phoneWidget->setStyleSheet("background: #255593; color: white;");
  m_ui->phoneWidget->setFixedSize(270, 447);
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

  // TODO: Load the questions, setup the quiz and start it.



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
