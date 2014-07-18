#include "templates/learnspellings/learnspellingssimulator.h"


LearnSpellingsSimulator::LearnSpellingsSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::LearnSpellingsSimulator) {
  m_ui->setupUi(this);
}

LearnSpellingsSimulator::~LearnSpellingsSimulator() {
  delete m_ui;
}

bool LearnSpellingsSimulator::startSimulation() {
  return false;
}

bool LearnSpellingsSimulator::stopSimulation() {
  return false;
}

bool LearnSpellingsSimulator::goBack() {
  return false;
}
