#include "templates/quiz/quizeditor.h"


QuizEditor::QuizEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::QuizEditor) {
  m_ui->setupUi(this);
}

QuizEditor::~QuizEditor() {
  delete m_ui;
}
