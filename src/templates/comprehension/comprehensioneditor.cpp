/*
  Copyright (c) 2015, BuildmLearn Contributors listed at http://buildmlearn.org/people/
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the BuildmLearn nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "templates/comprehension/comprehensioneditor.h"

#include "miscellaneous/iconfactory.h"
#include "templates/comprehension/comprehensionquestion.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"

#include <QToolTip>
#include <QTimer>
#include <QShowEvent>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QFileDialog>


ComprehensionEditor::ComprehensionEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::ComprehensionEditor) {
  m_ui->setupUi(this);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);
  QRegExpValidator *option_validator = new QRegExpValidator(this);
  QRegExpValidator *time_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));
  option_validator->setRegExp(QRegExp(".{,60}"));
  time_validator->setRegExp(QRegExp("[1-9]\\d{0,3}"));

  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);
  m_ui->m_txtTitle->lineEdit()->setValidator(title_validator);
  m_ui->m_txtTimer->lineEdit()->setValidator(time_validator);
  m_ui->m_txtAnswerOne->setValidator(option_validator);
  m_ui->m_txtAnswerTwo->setValidator(option_validator);
  m_ui->m_txtAnswerThree->setValidator(option_validator);
  m_ui->m_txtAnswerFour->setValidator(option_validator);
  m_ui->m_txtQuestion->setMaxLength(160);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtQuestion << m_ui->m_btnAnswerOne << m_ui->m_txtAnswerOne <<
                       m_ui->m_btnAnswerTwo << m_ui->m_txtAnswerTwo <<
                       m_ui->m_btnAnswerThree << m_ui->m_txtAnswerThree <<
                       m_ui->m_btnAnswerFour << m_ui->m_txtAnswerFour <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_txtTitle->lineEdit() << m_ui->m_btnPassageSelect <<
                       m_ui->m_txtPassage << m_ui->m_txtTimer->lineEdit()  <<
                       m_ui->m_listQuestions << m_ui->m_btnQuestionAdd << m_ui->m_btnQuestionRemove <<
                       m_ui->m_btnQuestionUp << m_ui->m_btnQuestionDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfQuestions->lineEdit()->setEnabled(false);
  m_ui->m_lblPassageStatus->label()->setWordWrap(true);

  IconFactory *factory = IconFactory::instance();

  // Set placeholders.
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this comprehension"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this comprehension"));
  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Title"));
  m_ui->m_txtTimer->lineEdit()->setPlaceholderText(tr("Time for reading the passage"));
  m_ui->m_txtPassage->document()->clear();

  // Set options for the questions.
  m_ui->m_btnAnswerOne->setProperty("id", 0);
  m_ui->m_btnAnswerTwo->setProperty("id", 1);
  m_ui->m_btnAnswerThree->setProperty("id", 2);
  m_ui->m_btnAnswerFour->setProperty("id", 3);

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

  // Connect signals to their respective slots.
  connect(m_ui->m_btnPassageSelect, SIGNAL(clicked()), this, SLOT(selectPassage()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateAuthorStatus()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateNameStatus()));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateTitleStatus()));
  connect(m_ui->m_txtPassage, SIGNAL(textChanged()), this, SLOT(onPassageChanged()));
  connect(m_ui->m_txtTimer->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateTimerStatus()));

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
  updateQuestionCount();
  checkTitle();
  checkPassage();
  checkTimer();
  checkName();
  checkAuthor();
  qRegisterMetaType<ComprehensionQuestion>("ComprehensionQuestion");
}

ComprehensionEditor::~ComprehensionEditor() {
  qDebug("Destroying ComprehensionEditor instance.");

  delete m_ui;
}

QList<ComprehensionQuestion> ComprehensionEditor::activeQuestions() const {
  QList<ComprehensionQuestion> questions;

  for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
    questions.append(m_ui->m_listQuestions->item(i)->data(Qt::UserRole).value<ComprehensionQuestion>());
  }

  return questions;
}

QString ComprehensionEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString ComprehensionEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

// For updating number of questions.
void ComprehensionEditor::updateQuestionCount() {
  m_ui->m_txtNumberOfQuestions->lineEdit()->setText(QString::number(m_ui->m_listQuestions->count()));

  if (m_ui->m_listQuestions->count() > 2) {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Ok, tr("Passage contains at least three question."));
  }
  else {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Error, tr("Comprehension does not minimum three questions."));
  }
}

// For adding a new question.
void ComprehensionEditor::addQuestion(const QString &question, const QStringList &answers, int correct_answer) {
  ComprehensionQuestion new_question;

  new_question.setQuestion(question);
  new_question.setCorrectAnswer(correct_answer);

  int answer_index = 0;
  foreach (const QString &answer, answers) {
    new_question.setAnswer(answer_index++, answer);
  }

  int marked_question = m_ui->m_listQuestions->currentRow();
  QListWidgetItem *new_item = new QListWidgetItem();
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

  updateQuestionCount();
}

// Add a default question.
void ComprehensionEditor::addQuestion() {
  addQuestion(tr("Question"),
              QStringList() << tr("Option 1") << tr("Option 2") <<
              tr("Option 3") << tr("Option 4"),
              1);

  launch();
  emit changed();
}

// Load the selected question.
void ComprehensionEditor::loadQuestion(int index) {
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
    ComprehensionQuestion question = m_ui->m_listQuestions->item(index)->data(Qt::UserRole).value<ComprehensionQuestion>();

    m_ui->m_txtQuestion->setText(question.question());
    m_ui->m_txtAnswerOne->setText(question.answerOne());
    m_ui->m_txtAnswerTwo->setText(question.answerTwo());
    m_ui->m_txtAnswerThree->setText(question.answerThree());
    m_ui->m_txtAnswerFour->setText(question.answerFour());
    m_ui->m_btnAnswerOne->setIcon(question.correctAnswer() == 0 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerTwo->setIcon(question.correctAnswer() == 1 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerThree->setIcon(question.correctAnswer() == 2 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerFour->setIcon(question.correctAnswer() == 3 ? m_iconYes : m_iconNo);

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

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

// For removing a question.
void ComprehensionEditor::removeQuestion() {
  int current_row = m_ui->m_listQuestions->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listQuestions->count() == 1) {
      // We are removing last visible question.
      setEditorsEnabled(false);

      m_ui->m_btnQuestionRemove->setEnabled(false);
    }

    delete m_ui->m_listQuestions->takeItem(current_row);
  }

  updateQuestionCount();
  launch();
  emit changed();
}

void ComprehensionEditor::saveQuestion() {
  PlainToolButton *button_sender = dynamic_cast<PlainToolButton*>(sender());

  if (button_sender != NULL) {
    // User clicked some of the "answer" buttons.
    m_activeQuestion.setCorrectAnswer(button_sender->property("id").toInt());

    // Change icons.
    switch (m_activeQuestion.correctAnswer()) {
      case 0:
        m_ui->m_btnAnswerOne->setIcon(m_iconYes);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        m_ui->m_btnAnswerThree->setIcon(m_iconNo);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;

      case 1:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconYes);
        m_ui->m_btnAnswerThree->setIcon(m_iconNo);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;

      case 2:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        m_ui->m_btnAnswerThree->setIcon(m_iconYes);
        m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;

      case 3:
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
  m_activeQuestion.setAnswer(0, m_ui->m_txtAnswerOne->text());
  m_activeQuestion.setAnswer(1, m_ui->m_txtAnswerTwo->text());
  m_activeQuestion.setAnswer(2, m_ui->m_txtAnswerThree->text());
  m_activeQuestion.setAnswer(3, m_ui->m_txtAnswerFour->text());

  m_ui->m_listQuestions->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeQuestion));
  m_ui->m_listQuestions->currentItem()->setText(m_activeQuestion.question());

  emit changed();
}

void ComprehensionEditor::moveQuestionUp() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index - 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index - 1);

  emit changed();
}

void ComprehensionEditor::moveQuestionDown() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index + 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index + 1);

  emit changed();
}

void ComprehensionEditor::configureUpDown() {
  if (m_ui->m_listQuestions->count() > 1) {
    int index = m_ui->m_listQuestions->currentRow();

    if (index == 0) {
      m_ui->m_btnQuestionUp->setEnabled(false);
      m_ui->m_btnQuestionDown->setEnabled(true);
    }
    else if (index == m_ui->m_listQuestions->count() - 1) {
      m_ui->m_btnQuestionUp->setEnabled(true);
      m_ui->m_btnQuestionDown->setEnabled(false);
    }
    else {
      m_ui->m_btnQuestionUp->setEnabled(true);
      m_ui->m_btnQuestionDown->setEnabled(true);
    }
  }
  else {
    m_ui->m_btnQuestionUp->setEnabled(false);
    m_ui->m_btnQuestionDown->setEnabled(false);
  }
}

void ComprehensionEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupQuestionEditor->setEnabled(enabled);
}

void ComprehensionEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error, tr("Enter the name of the comprehension."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok, tr("Name is okay."));
  }
}

void ComprehensionEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error, tr("Enter the name of the author of the comprehension."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok, tr("Enter the name of the author of the comprehension."));
  }
}

void ComprehensionEditor::checkTitle() {
  if (m_ui->m_txtTitle->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Error, tr("Enter the title of the passage."));
  }
  else {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Ok, tr("Enter the title of the passage."));
  }
}

void ComprehensionEditor::checkPassage() {
  if (m_ui->m_txtPassage->document()->isEmpty()) {
    m_ui->m_lblPassageStatus->setStatus(WidgetWithStatus::Error, tr("Passage is empty."), tr("Passage is empty."));
  }
  else {
    int word_count = m_ui->m_txtPassage->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"),
                                               QString::SkipEmptyParts).count();
    m_ui->m_lblPassageStatus->setStatus(WidgetWithStatus::Ok, tr("Words - %1, Char - %2.").arg
                                        (QString::number(word_count),
                                         QString::number(m_ui->m_txtPassage->document()->characterCount() - 1)),
                                        tr("Words - %1, Char - %2.").arg
                                        (QString::number(word_count),
                                         QString::number(m_ui->m_txtPassage->document()->characterCount() - 1)));
  }
}

void ComprehensionEditor::checkTimer() {
  if (m_ui->m_txtTimer->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtTimer->setStatus(WidgetWithStatus::Error, tr("Enter the time for reading the passage."));
  }
  else {
    m_ui->m_txtTimer->setStatus(WidgetWithStatus::Ok, tr("Enter the time for reading the passage."));
  }
}

void ComprehensionEditor::updateNameStatus() {
  checkName();
  launch();
  emit changed();
}

void ComprehensionEditor::updateAuthorStatus() {
  checkAuthor();
  launch();
  emit changed();
}

void ComprehensionEditor::updateTitleStatus() {
  checkTitle();
  launch();
  emit changed();
}

void ComprehensionEditor::onPassageChanged() {
  checkPassage();
  launch();
  emit changed();
}

void ComprehensionEditor::updateTimerStatus() {
  checkTimer();
  launch();
  emit changed();
}

bool ComprehensionEditor::canGenerateApplications() {
  return
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtTitle->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtPassage->document()->isEmpty() &&
      !m_ui->m_txtTimer->lineEdit()->text().simplified().isEmpty() &&
      activeQuestions().count() > 2;
}

bool ComprehensionEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString question = item.namedItem("question").toElement().text();
      int correct_answer = item.namedItem("answer").toElement().text().toInt();
      QDomNodeList answer_items = item.toElement().elementsByTagName("option");
      QList<QString> answers;

      for (int j = 0; j < answer_items.size(); j++) {
        answers.append(answer_items.at(j).toElement().text());
      }

      if (question.isEmpty() || answers.size() < 2 || answers.size() > 4) {
        // TODO: error
        continue;
      }
      else {
        addQuestion(question, answers, correct_answer);
      }
    }
    else {
      continue;
    }
  }

  // Load author & name.
  m_ui->m_txtAuthor->lineEdit()->setText(bundle_document.documentElement().namedItem("author").namedItem("name").toElement().text());
  m_ui->m_txtName->lineEdit()->setText(bundle_document.documentElement().namedItem("title").toElement().text());

  return true;
}

QString ComprehensionEditor::generateBundleData() {
  /*if (!canGenerateApplications()) {
    return QString();
  }*/

  QDomDocument source_document = qApp->templateManager()->generateBundleHeader(core()->entryPoint()->typeIndentifier(),
                                                                               m_ui->m_txtAuthor->lineEdit()->text(),
                                                                               QString(),
                                                                               m_ui->m_txtName->lineEdit()->text(),
                                                                               QString(),
                                                                               "1");
  FIND_DATA_ELEMENT(data_element, source_document);

  foreach (const ComprehensionQuestion &question, activeQuestions()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about question.
    QDomElement question_element = source_document.createElement("question");
    QDomElement answer_one_element = source_document.createElement("option");
    QDomElement answer_two_element = source_document.createElement("option");
    QDomElement answer_three_element = source_document.createElement("option");
    QDomElement answer_four_element = source_document.createElement("option");
    QDomElement answer_number_element = source_document.createElement("answer");

    question_element.appendChild(source_document.createTextNode(question.question()));
    answer_one_element.appendChild(source_document.createTextNode(question.answerOne()));
    answer_two_element.appendChild(source_document.createTextNode(question.answerTwo()));
    answer_three_element.appendChild(source_document.createTextNode(question.answerThree()));
    answer_four_element.appendChild(source_document.createTextNode(question.answerFour()));
    answer_number_element.appendChild(source_document.createTextNode(QString::number(question.correctAnswer())));

    item_element.appendChild(question_element);
    item_element.appendChild(answer_one_element);
    item_element.appendChild(answer_two_element);
    item_element.appendChild(answer_three_element);
    item_element.appendChild(answer_four_element);
    item_element.appendChild(answer_number_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

void ComprehensionEditor::selectPassage() {
  QString selected_passage = QFileDialog::getOpenFileName(this, tr("Select passage for the comprehension"),
                                                          m_ui->m_lblPassageStatus->label()->toolTip(),
                                                          tr("Text files (*.txt)"),
                                                          0);

  if (!selected_passage.isEmpty()) {
    loadPassage(selected_passage);
  }
}

// Load and save passage.
void ComprehensionEditor::loadPassage(const QString& passage_path) {
  if (!passage_path.isEmpty()) {
    QFile file(passage_path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QString text = file.readAll();
      QTextDocument *document = new QTextDocument(text);
      m_ui->m_txtPassage->setDocument(document);
    }
    file.close();
  }
  onPassageChanged();
  m_ui->m_lblPassageStatus->label()->setToolTip(QDir::toNativeSeparators(passage_path));
}
