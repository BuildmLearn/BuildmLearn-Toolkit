/*
  Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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

#include "templates/comprehension/comprehensioneditor .h"
#include "miscellaneous/iconfactory.h"
#include "templates/comprehension/comprehensionquestion.h"
#include "templates/comprehension/comprehensionpassage.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"


#include <QToolTip>
#include <QTimer>
#include <QShowEvent>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>


ComprehensionEditor::ComprehensionEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::ComprehensionEditor) {
  m_ui->setupUi(this);


  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);
  QRegExpValidator *option_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));
  option_validator->setRegExp(QRegExp(".{,60}"));

  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);
  m_ui->m_txtAnswerOne->setValidator(option_validator);
  m_ui->m_txtAnswerTwo->setValidator(option_validator);
  m_ui->m_txtAnswerThree->setValidator(option_validator);
  m_ui->m_txtAnswerFour->setValidator(option_validator);
  m_ui->m_txtQuestion->setMaxLength(160);
  
  //Set max size of  passage as 2500 words 
  m_ui->m_txtPassage->setMaxLength(2500);

  // Set tab order for question tab
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtQuestion << m_ui->m_btnAnswerOne << m_ui->m_txtAnswerOne <<
                       m_ui->m_btnAnswerTwo << m_ui->m_txtAnswerTwo <<
                       m_ui->m_btnAnswerThree << m_ui->m_txtAnswerThree <<
                       m_ui->m_btnAnswerFour << m_ui->m_txtAnswerFour <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_listQuestions << m_ui->m_btnQuestionAdd << m_ui->m_btnQuestionRemove <<
                       m_ui->m_btnQuestionUp << m_ui->m_btnQuestionDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfQuestions->lineEdit()->setEnabled(false);

  IconFactory *factory = IconFactory::instance();

  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this quiz"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this quiz"));

  m_ui->m_btnAnswerOne->setProperty("id", 0);
  m_ui->m_btnAnswerTwo->setProperty("id", 1);
  m_ui->m_btnAnswerThree->setProperty("id", 2);
  m_ui->m_btnAnswerFour->setProperty("id", 3);

  m_ui->m_btnQuestionAdd->setIcon(factory->fromTheme("item-add"));   
  m_ui->m_btnQuestionRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnQuestionUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnQuestionDown->setIcon(factory->fromTheme("move-down"));
  m_ui->m_btnPassageAdd->setIcon(factory->fromTheme("item-add")); ///
  m_ui->m_btnPassageRemove->setIcon(factory->fromTheme("item-remove"));

  m_iconNo = factory->fromTheme("dialog-no");
  m_iconYes = factory->fromTheme("dialog-yes");

  m_ui->m_btnAnswerOne->setIcon(m_iconNo);
  m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
  m_ui->m_btnAnswerThree->setIcon(m_iconNo);
  m_ui->m_btnAnswerFour->setIcon(m_iconNo);

  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateAuthorStatus()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateNameStatus()));

  connect(m_ui->m_btnQuestionAdd, SIGNAL(clicked()), this, SLOT(addQuestion()));
  connect(m_ui->m_btnQuestionRemove, SIGNAL(clicked()), this, SLOT(removeQuestion()));
  connect(m_ui->m_listQuestions, SIGNAL(currentRowChanged(int)), this, SLOT(loadQuestion(int)));
  
  connect(m_ui->m_btnPassageAdd, SIGNAL(clicked()), this, SLOT(addPassage()));  ////
  connect(m_ui->m_btnPassageRemove, SIGNAL(clicked()), this, SLOT(removePassage()));  ////
  
  connect(m_ui->m_btnAnswerOne, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerTwo, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerThree, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerFour, SIGNAL(clicked()), this, SLOT(saveQuestion()));

  connect(m_ui->m_txtAnswerOne, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerTwo, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerThree, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerFour, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtQuestion, SIGNAL(textChanged()), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtPassage, SIGNAL(textChanged()), this, SLOT(savePassage()));  ////

  connect(m_ui->m_btnQuestionUp, SIGNAL(clicked()), this, SLOT(moveQuestionUp()));
  connect(m_ui->m_btnQuestionDown, SIGNAL(clicked()), this, SLOT(moveQuestionDown()));

  
  
  // initially only passage tab is enabled that force teacher to first provide passage for questions
  setQuestionEditorEnabled(false);
  setPassageEditorEnabled(true);
  updateQuestionCount();
  checkName();
  checkAuthor();
  qRegisterMetaType<ComprehensionQuestion>("ComprehensionQuestion");
}

ComprehensionEditor::~ComprehensionEditor() {

    qDebug("Destroying ComprehensionEditor instance.");
  delete m_ui;
}



// function that give list of active questions
QList<ComprehensionQuestion> ComprehensionEditor::activeQuestions() const {
  QList<ComprehensionQuestion> questions;

  for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
    questions.append(m_ui->m_listQuestions->item(i)->data(Qt::UserRole).value<ComprehensionQuestion>());
  }

  return questions;
}


// function that give one and only active passage 
ComprehensionPassage ComprehensionEditor::activePassage() const {     
return (m_ui->m_listPassage->item(0)->data(Qt::UserRole).value<ComprehensionPassage>()); ////
}


QString ComprehensionEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString ComprehensionEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

// function that update Questions count after add and remove of questions 
void ComprehensionEditor::updateQuestionCount() {
  m_ui->m_txtNumberOfQuestions->lineEdit()->setText(QString::number(m_ui->m_listQuestions->count()));

  if (m_ui->m_listQuestions->count() > 0) {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Ok, tr("Quiz contains at least one question."));
  }
  else {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Error, tr("Quiz does not contain any questions."));
  }
}


// function to add new passage to quiz
void ComprehensionEditor::addPassage(const QString &passage){  
ComprehensionPassage new_passage;
new_passage.setPassage(passage);
QListWidgetItem *new_item = new QListWidgetItem();
new_item->setText(new_passage.passage());
///new_item->setData(Qt::UserRole, QVariant::fromValue(new_passage));
    
	// As we add passage so enabling teacher to add questions  
	setQuestionEditorEnabled(true);
    m_ui->m_btnPassageRemove->setEnabled(true);
	m_ui->m_btnPassageAdd->setEnabled(false);
	m_ui->m_btnQuestionAdd->setEnabled(true);
    m_ui->m_listPassage->insertItem(0, new_item);
    m_ui->m_listPassage->setCurrentRow(0);
  }

  
  
 // adding questions  to quiz  
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
    ///setEditorsEnabled(true);

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

void ComprehensionEditor::addQuestion() {
  addQuestion(tr("How many cats do you have?"),
              QStringList() << tr("I hate cats!") << tr("I have two nice kittens.") <<
              tr("I have seven beasts.") << tr("Cats? Well, we own eleven dogs."),
              2);

  launch();
  emit changed();
}

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


// function for removing active pssage 
void ComprehensionEditor::removePassage() {    
  int current_row  = m_ui->m_listPassage->currentRow();
      setQuestionEditorEnabled(false);
      m_ui->m_btnPassageAdd->setEnabled(true);
      m_ui->m_btnPassageRemove->setEnabled(false);
    delete m_ui->m_listPassage->takeItem(current_row);
	  //clearing question list of this passage 
	  clearQuestionList();
	  launch();
      emit changed();
  }

  
void ComprehensionEditor::removeQuestion() {
  int current_row = m_ui->m_listQuestions->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listQuestions->count() == 1) {
      // We are removing last visible question.
      m_ui->m_btnQuestionRemove->setEnabled(false);
    }

    delete m_ui->m_listQuestions->takeItem(current_row);
  }

  updateQuestionCount();
  launch();
  emit changed();
}



//function for clearing activeQuestions as their passage is removed
void ComprehensionEditor::clearQuestionList(){
 int current_row = m_ui->m_listQuestions->currentRow();
  if(current_row >=0){
    for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
      delete m_ui->m_listQuestions->takeItem(i);
    }

  }
  
 // setting question tab bisabled as active passsage is removed
  setQuestionEditorEnabled(false);
  m_ui->m_btnQuestionRemove->setEnabled(false);
  m_ui->m_btnQuestionAdd->setEnabled(false);
  m_ui->m_btnQuestionUp->setEnabled(false);
  m_ui->m_btnQuestionDown->setEnabled(false);
  updateQuestionCount();
  launch();
  emit changed();
}


void ComprehensionEditor::savePassage() {
m_activePassage.setPassage(m_ui->m_txtPassage->toPlainText());
m_ui->m_listPassage->currentItem()->setText(m_activePassage.passage());
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

//setting passage editor enabled or bisabled
void ComprehensionEditor::setPassageEditorEnabled(bool enabled) {
  m_ui->m_groupPassageEditor->setEnabled(enabled);
}

// setting question editor enabled or disabled
void ComprehensionEditor::setQuestionEditorEnabled(bool enabled){
m_ui->m_groupQuestionEditor->setEnabled(enabled);
} 


void ComprehensionEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error, tr("Enter the name of the quiz."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok, tr("Name is okay."));
  }
}

void ComprehensionEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error, tr("Enter the name of the author of the quiz."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok, tr("Enter the name of the author of the quiz."));
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

bool ComprehensionEditor::canGenerateApplications() {
  return
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      ///!activePassage().isEmpty()&&
      !activeQuestions().isEmpty();
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
  FIND_DATA_ELEMENT(data_element,source_document);

  foreach(const ComprehensionQuestion &question,activeQuestions()) {
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

