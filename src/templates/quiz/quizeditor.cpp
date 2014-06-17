#include "templates/quiz/quizeditor.h"

#include "miscellaneous/iconfactory.h"
#include "templates/quiz/quizquestion.h"


QuizEditor::QuizEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::QuizEditor) {
  m_ui->setupUi(this);

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnQuestionAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnQuestionRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnQuestionUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnQuestionDown->setIcon(factory->fromTheme("move-down"));
  m_ui->m_btnAnswerOne->setIcon(factory->fromTheme("dialog-no"));
  m_ui->m_btnAnswerTwo->setIcon(factory->fromTheme("dialog-no"));

  connect(m_ui->m_btnQuestionAdd, SIGNAL(clicked()), this, SLOT(addQuestion()));
  connect(m_ui->m_btnQuestionRemove, SIGNAL(clicked()), this, SLOT(removeQuestion()));
  connect(m_ui->m_listQuestions, SIGNAL(currentRowChanged(int)), this, SLOT(loadQuestion(int)));

  connect(m_ui->m_btnAnswerOne, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerTwo, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerThree, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerFour, SIGNAL(clicked()), this, SLOT(saveQuestion()));

  connect(m_ui->m_txtAnswerOne, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerTwo, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerThree, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerFour, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtQuestion, SIGNAL(textChanged()), this, SLOT(saveQuestion()));

  setEditorsEnabled(false);

  qRegisterMetaType<QuizQuestion>("QuizQuestion");
}

QuizEditor::~QuizEditor() {
  delete m_ui;
}

void QuizEditor::addQuestion() {
  int marked_question = m_ui->m_listQuestions->currentRow();
  QuizQuestion new_question;
  QListWidgetItem *new_item = new QListWidgetItem();

  new_question.setQuestion(tr("How many cats do you have?"));
  new_item->setText(new_question.question());
  new_item->setData(Qt::UserRole, QVariant::fromValue(new_question));

  if (m_ui->m_listQuestions->count() == 0) {
    // We are adding first question.
    setEditorsEnabled(true);

    m_ui->m_btnQuestionRemove->setEnabled(true);

    m_ui->m_listQuestions->insertItem(0, new_item);
    m_ui->m_listQuestions->setCurrentRow(0);
  }
  else {
    m_ui->m_listQuestions->insertItem(marked_question + 1, new_item);
    m_ui->m_listQuestions->setCurrentRow(marked_question + 1);
  }
}

void QuizEditor::loadQuestion(int index) {

}

void QuizEditor::removeQuestion() {
  int current_row = m_ui->m_listQuestions->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listQuestions->count() == 1) {
      // We are removing last question.
      setEditorsEnabled(false);

      m_ui->m_btnQuestionRemove->setEnabled(false);
    }

    delete m_ui->m_listQuestions->takeItem(current_row);
  }
}

void QuizEditor::saveQuestion() {

}

void QuizEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_txtAnswerOne->setEnabled(enabled);
  m_ui->m_txtAnswerTwo->setEnabled(enabled);
  m_ui->m_txtAnswerThree->setEnabled(enabled);
  m_ui->m_txtAnswerFour->setEnabled(enabled);
  m_ui->m_txtQuestion->setEnabled(enabled);

  m_ui->m_btnAnswerOne->setEnabled(enabled);
  m_ui->m_btnAnswerTwo->setEnabled(enabled);
  m_ui->m_btnAnswerThree->setEnabled(enabled);
  m_ui->m_btnAnswerFour->setEnabled(enabled);
}
