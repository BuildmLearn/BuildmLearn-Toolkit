#include "templates/learnspellings/learnspellingssimulator.h"

#include "core/templatecore.h"
#include "templates/learnspellings/learnspellingseditor.h"


LearnSpellingsSimulator::LearnSpellingsSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::LearnSpellingsSimulator) {
  m_ui->setupUi(this);
  m_ui->m_phoneWidget->setStyleSheet("background: #255593; color: white;");

  connect(m_ui->m_btnPlayWord, SIGNAL(clicked()), this, SLOT(playWord()));
  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(exit()));
  connect(m_ui->m_btnSkip, SIGNAL(clicked()), this, SLOT(nextWord()));
}

LearnSpellingsSimulator::~LearnSpellingsSimulator() {
  delete m_ui;
}

bool LearnSpellingsSimulator::startSimulation() {
  LearnSpellingsEditor *editor = static_cast<LearnSpellingsEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active questions or quiz does not
    // containt its name or author name.
    return false;
  }

  // Load the questions, setup the quiz and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

  m_ui->m_phoneWidget->setCurrentIndex(1);
  return false;
}

bool LearnSpellingsSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool LearnSpellingsSimulator::goBack() {
  return false;
}

void LearnSpellingsSimulator::launch() {
  emit canGoBackChanged(false);
}

void LearnSpellingsSimulator::start() {

}

void LearnSpellingsSimulator::restart() {

}

void LearnSpellingsSimulator::exit() {

}

void LearnSpellingsSimulator::playWord() {
  m_ui->m_btnSkip->setEnabled(true);
  m_ui->m_btnSpellIt->setEnabled(true);
}

void LearnSpellingsSimulator::nextWord() {

}
