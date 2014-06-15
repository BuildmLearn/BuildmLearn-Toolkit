#include "templates/quiz/quizsimulator.h"

#include "core/templatecore.h"


QuizSimulator::QuizSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::QuizSimulator) {
  m_ui->setupUi(this);
}

QuizSimulator::~QuizSimulator() {
  delete m_ui;
}

bool QuizSimulator::startSimulation() {
  return true;
}

bool QuizSimulator::stopSimulation() {
  return true;
}

bool QuizSimulator::canGoBack() {
  return true;
}

bool QuizSimulator::goBack() {
  return true;
}
