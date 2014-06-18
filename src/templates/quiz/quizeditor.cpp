#include "templates/quiz/quizeditor.h"

#include "miscellaneous/iconfactory.h"
#include "templates/quiz/quizquestion.h"


QuizEditor::QuizEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::QuizEditor) {
  m_ui->setupUi(this);

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnAnswerOne->setProperty("id", 1);
  m_ui->m_btnAnswerTwo->setProperty("id", 2);
  m_ui->m_btnAnswerThree->setProperty("id", 3);
  m_ui->m_btnAnswerFour->setProperty("id", 4);

  m_ui->m_btnQuestionAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnQuestionRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnQuestionUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnQuestionDown->setIcon(factory->fromTheme("move-down"));

  m_iconNo = factory->fromTheme("dialog-no");
  m_iconYes = factory->fromTheme("dialog-yes");

  m_ui->m_btnAnswerOne->setIcon(m_iconNo);
  m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
  m_ui->m_btnAnswerThree->setIcon(m_iconNo);
  m_ui->m_btnAnswerFour->setIcon(m_iconNo);

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

  connect(m_ui->m_btnQuestionUp, SIGNAL(clicked()), this, SLOT(moveQuestionUp()));
  connect(m_ui->m_btnQuestionDown, SIGNAL(clicked()), this, SLOT(moveQuestionDown()));

  setEditorsEnabled(false);

  qRegisterMetaType<QuizQuestion>("QuizQuestion");
}

QuizEditor::~QuizEditor() {
  delete m_ui;
}

QList<QuizQuestion> QuizEditor::activeQuestions() const {
  QList<QuizQuestion> questions;

  for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
    questions.append(m_ui->m_listQuestions->item(i)->data(Qt::UserRole).value<QuizQuestion>());
  }

  return questions;
}

void QuizEditor::addQuestion() {
  int marked_question = m_ui->m_listQuestions->currentRow();
  QuizQuestion new_question;
  QListWidgetItem *new_item = new QListWidgetItem();

  new_question.setQuestion(tr("How many cats do you have?"));
  new_question.setCorrectAnswer(3);
  new_question.setAnswerOne(tr("I hate cats!"));
  new_question.setAnswerTwo(tr("I have two nice kittens."));
  new_question.setAnswerThree(tr("I have seven beasts."));
  new_question.setAnswerFour(tr("Cats? Well, we own eleven dogs."));

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
  m_ui->m_txtQuestion->blockSignals(true);
  m_ui->m_txtAnswerOne->blockSignals(true);
  m_ui->m_txtAnswerTwo->blockSignals(true);
  m_ui->m_txtAnswerThree->blockSignals(true);
  m_ui->m_txtAnswerFour->blockSignals(true);
  m_ui->m_btnAnswerOne->blockSignals(true);
  m_ui->m_btnAnswerTwo->blockSignals(true);
  m_ui->m_btnAnswerThree->blockSignals(true);
  m_ui->m_btnAnswerFour->blockSignals(true);

  if (index >= 0) {
    QuizQuestion question = m_ui->m_listQuestions->item(index)->data(Qt::UserRole).value<QuizQuestion>();

    m_ui->m_txtQuestion->setText(question.question());
    m_ui->m_txtAnswerOne->setText(question.answerOne());
    m_ui->m_txtAnswerTwo->setText(question.answerTwo());
    m_ui->m_txtAnswerThree->setText(question.answerThree());
    m_ui->m_txtAnswerFour->setText(question.answerFour());
    m_ui->m_btnAnswerOne->setIcon(question.correctAnswer() == 1 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerTwo->setIcon(question.correctAnswer() == 2 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerThree->setIcon(question.correctAnswer() == 3 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerFour->setIcon(question.correctAnswer() == 4 ? m_iconYes : m_iconNo);

    m_activeQuestion = question;
  }
  else {
    m_ui->m_txtQuestion->setText(QString());
    m_ui->m_txtAnswerOne->setText(QString());
    m_ui->m_txtAnswerTwo->setText(QString());
    m_ui->m_txtAnswerThree->setText(QString());
    m_ui->m_txtAnswerFour->setText(QString());
    m_ui->m_btnAnswerOne->setIcon(m_iconNo);
    m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
    m_ui->m_btnAnswerThree->setIcon(m_iconNo);
    m_ui->m_btnAnswerFour->setIcon(m_iconNo);
  }

  m_ui->m_txtQuestion->blockSignals(false);
  m_ui->m_txtAnswerOne->blockSignals(false);
  m_ui->m_txtAnswerTwo->blockSignals(false);
  m_ui->m_txtAnswerThree->blockSignals(false);
  m_ui->m_txtAnswerFour->blockSignals(false);
  m_ui->m_btnAnswerOne->blockSignals(false);
  m_ui->m_btnAnswerTwo->blockSignals(false);
  m_ui->m_btnAnswerThree->blockSignals(false);
  m_ui->m_btnAnswerFour->blockSignals(false);
}

void QuizEditor::removeQuestion() {
  int current_row = m_ui->m_listQuestions->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listQuestions->count() == 1) {
      // We are removing last visible question.
      setEditorsEnabled(false);

      m_ui->m_btnQuestionRemove->setEnabled(false);
    }

    delete m_ui->m_listQuestions->takeItem(current_row);
  }
}

void QuizEditor::saveQuestion() {
  PlainToolButton *button_sender = dynamic_cast<PlainToolButton*>(sender());

  if (button_sender != NULL) {
    // User clicked some of the "answer" buttons.
    m_activeQuestion.setCorrectAnswer(button_sender->property("id").toInt());

    // Change icons.
    switch (m_activeQuestion.correctAnswer()) {
      case 1:
        m_ui->m_btnAnswerOne->setIcon(m_iconYes);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        m_ui->m_btnAnswerThree->setIcon(m_iconNo);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;

      case 2:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconYes);
        m_ui->m_btnAnswerThree->setIcon(m_iconNo);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;

      case 3:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        m_ui->m_btnAnswerThree->setIcon(m_iconYes);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;

      case 4:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        m_ui->m_btnAnswerThree->setIcon(m_iconNo);
        m_ui->m_btnAnswerFour->setIcon(m_iconYes);
        break;

      default:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        m_ui->m_btnAnswerThree->setIcon(m_iconNo);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;
    }
  }

  m_activeQuestion.setQuestion(m_ui->m_txtQuestion->toPlainText());
  m_activeQuestion.setAnswerOne(m_ui->m_txtAnswerOne->text());
  m_activeQuestion.setAnswerTwo(m_ui->m_txtAnswerTwo->text());
  m_activeQuestion.setAnswerThree(m_ui->m_txtAnswerThree->text());
  m_activeQuestion.setAnswerFour(m_ui->m_txtAnswerFour->text());

  m_ui->m_listQuestions->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeQuestion));
  m_ui->m_listQuestions->currentItem()->setText(m_activeQuestion.question());
}

void QuizEditor::moveQuestionUp() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index - 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index - 1);
}

void QuizEditor::moveQuestionDown() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index + 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index + 1);
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
