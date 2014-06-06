#include "gui/formsimulator.h"

#include "gui/formmain.h"


FormSimulator::FormSimulator(FormMain* parent)
  : QDialog(parent), m_ui(new Ui::FormSimulator), m_mainWindow(parent) {
  m_ui->setupUi(this);
}

FormSimulator::~FormSimulator() {
  delete m_ui;
}

void FormSimulator::setIsSticked(bool is_sticked) {
  m_isSticked = is_sticked;

  // Stick the window to main application window.
}

