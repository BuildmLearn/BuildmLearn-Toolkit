#include "templates/quiz/quizeditor.h"

#include "miscellaneous/iconfactory.h"


QuizEditor::QuizEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::QuizEditor) {
  m_ui->setupUi(this);


  m_ui->m_btnAnswerOne->setIcon(IconFactory::instance()->fromTheme("dialog-no"));
  m_ui->m_btnAnswerTwo->setIcon(IconFactory::instance()->fromTheme("dialog-no"));
}

QuizEditor::~QuizEditor() {
  delete m_ui;
}
