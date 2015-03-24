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

#include "templates/flashcard/flashcardeditor.h"

#include "templates/flashcard/flashcardquestion.h"
#include "templates/flashcard/flashcardcore.h"
#include "templates/flashcard/flashcardentrypoint.h"
#include "miscellaneous/iconfactory.h"
#include "miscellaneous/iofactory.h"
#include "core/templatefactory.h"

#include <QTimer>
#include <QFileDialog>


FlashCardEditor::FlashCardEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::FlashCardEditor) {
  m_ui->setupUi(this);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));

  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);

  // Set validators.
  QRegExpValidator *question_validator = new QRegExpValidator(this);
  QRegExpValidator *hint_validator = new QRegExpValidator(this);

  question_validator->setRegExp(QRegExp(".{,100}"));
  hint_validator->setRegExp(QRegExp(".{,30}"));

  m_ui->m_txtQuestion->lineEdit()->setValidator(question_validator);
  m_ui->m_txtHint->lineEdit()->setValidator(hint_validator);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtQuestion->lineEdit() << m_ui->m_btnPictureSelect  <<
                       m_ui->m_txtAnswer->lineEdit() << m_ui->m_txtHint->lineEdit() <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_listQuestions << m_ui->m_btnQuestionAdd << m_ui->m_btnQuestionRemove <<
                       m_ui->m_btnQuestionUp << m_ui->m_btnQuestionDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfQuestions->lineEdit()->setEnabled(false);

  m_ui->m_lblPictureFile->label()->setWordWrap(true);
  m_ui->m_txtAnswer->lineEdit()->setPlaceholderText(tr("Answer for the answer"));
  m_ui->m_txtHint->lineEdit()->setPlaceholderText(tr("Hint for the answer"));

  m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Error, QString(), tr("No picture selected"));
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this quiz"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this quiz"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnQuestionAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnQuestionRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnQuestionUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnQuestionDown->setIcon(factory->fromTheme("move-down"));

  connect(m_ui->m_btnPictureSelect, SIGNAL(clicked()), this, SLOT(selectPicture()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAuthorChanged(QString)));
  connect(m_ui->m_txtQuestion, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));
  connect(m_ui->m_txtAnswer->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(onAnswerChanged(QString)));
  connect(m_ui->m_txtHint->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(onHintChanged(QString)));
  connect(m_ui->m_btnQuestionAdd, SIGNAL(clicked()), this, SLOT(addQuestion()));
  connect(m_ui->m_btnQuestionRemove, SIGNAL(clicked()), this, SLOT(removeQuestion()));
  connect(m_ui->m_listQuestions, SIGNAL(currentRowChanged(int)), this, SLOT(loadQuestion(int)));
  connect(m_ui->m_btnQuestionUp, SIGNAL(clicked()), this, SLOT(moveQuestionUp()));
  connect(m_ui->m_btnQuestionDown, SIGNAL(clicked()), this, SLOT(moveQuestionDown()));

  setEditorsEnabled(false);
  updateQuestionCount();

  qRegisterMetaType<FlashCardQuestion>("FlashCardQuestion");

  checkAuthor();
  checkName();
  loadQuestion(-1);
}

FlashCardEditor::~FlashCardEditor() {
  qDebug("Destroying FlashCardEditor instance.");

  delete m_ui;
}

void FlashCardEditor::updateQuestionCount() {
  m_ui->m_txtNumberOfQuestions->lineEdit()->setText(QString::number(m_ui->m_listQuestions->count()));

  if (m_ui->m_listQuestions->count() > 0) {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Ok, tr("Collection contains at least one question."));
  }
  else {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Error, tr("Collection does not contain any questions."));
  }
}

bool FlashCardEditor::canGenerateApplications() {
  return
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !activeQuestions().isEmpty();
}

QString FlashCardEditor::generateBundleData() {
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

  foreach (const FlashCardQuestion &question, activeQuestions()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about question.
    QDomElement question_element = source_document.createElement("question");
    QDomElement answer_element = source_document.createElement("answer");
    QDomElement hint_element = source_document.createElement("hint");
    QDomElement image_element = source_document.createElement("image");

    question_element.appendChild(source_document.createTextNode(question.question()));
    answer_element.appendChild(source_document.createTextNode(question.answer()));
    hint_element.appendChild(source_document.createTextNode(question.hint()));

    // Read file with image, convert it to base64 and insert into XML bundle.
    QByteArray picture_encoded = IOFactory::fileToBase64(question.picturePath());

    if (picture_encoded.isEmpty() || picture_encoded.isNull()) {
      return QString();
    }

    image_element.appendChild(source_document.createTextNode(QString::fromUtf8(picture_encoded)));
    item_element.appendChild(question_element);
    item_element.appendChild(answer_element);
    item_element.appendChild(hint_element);
    item_element.appendChild(image_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

bool FlashCardEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString question = item.namedItem("question").toElement().text();
      QString answer = item.namedItem("answer").toElement().text();
      QString hint = item.namedItem("hint").toElement().text();
      QString image_data = item.namedItem("image").toElement().text();

      if (question.isEmpty() || answer.isEmpty() || image_data.isEmpty()) {
        // TODO: error
        continue;
      }
      else {
        // TODO: POKRACOVAT TADY, prevadeni z base64 do souboru blbne.
        // https://www.google.cz/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=qt%20base64%20to%20file
        QString output_directory = qApp->templateManager()->tempDirectory();
        QString target_image_file = output_directory +
                                    QString("/image_%1.png").arg(i);

        if (IOFactory::base64ToFile(image_data, target_image_file)) {
          // Picture from the item was saved to disk.
          addQuestion(question, answer, hint, target_image_file);
        }
        else {
          // TODO: errro
        }
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

QList<FlashCardQuestion> FlashCardEditor::activeQuestions() const {
  QList<FlashCardQuestion> questions;

  for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
    questions.append(m_ui->m_listQuestions->item(i)->data(Qt::UserRole).value<FlashCardQuestion>());
  }

  return questions;
}

QString FlashCardEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString FlashCardEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

void FlashCardEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void FlashCardEditor::checkHint() {
  if (m_ui->m_txtHint->lineEdit()->text().isEmpty()) {
    m_ui->m_txtHint->setStatus(WidgetWithStatus::Warning,
                               tr("Hint is not specified."));
  }
  else {
    m_ui->m_txtHint->setStatus(WidgetWithStatus::Ok,
                               tr("Hint is specified."));
  }
}

void FlashCardEditor::checkQuestion() {
  if (m_ui->m_txtQuestion->lineEdit()->text().isEmpty()) {
    m_ui->m_txtQuestion->setStatus(WidgetWithStatus::Warning,
                               tr("Question is not specified."));
  }
  else {
    m_ui->m_txtQuestion->setStatus(WidgetWithStatus::Ok,
                               tr("Question is specified."));
  }
}

void FlashCardEditor::checkAnswer() {
  if (m_ui->m_txtAnswer->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAnswer->setStatus(WidgetWithStatus::Error,
                                 tr("Answer is not specified."));
  }
  else {
    m_ui->m_txtAnswer->setStatus(WidgetWithStatus::Ok,
                                 tr("Answer is specified."));
  }
}

void FlashCardEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection name is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection name is specified."));
  }
}

void FlashCardEditor::configureUpDown() {
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

void FlashCardEditor::moveQuestionUp() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index - 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index - 1);

  emit changed();
}

void FlashCardEditor::moveQuestionDown() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index + 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index + 1);

  emit changed();
}

void FlashCardEditor::loadPicture(const QString& picture_path) {
  if (!picture_path.isEmpty()) {
    m_ui->m_lblPictureView->setPixmap(QPixmap(picture_path).scaled(m_ui->m_lblPictureView->size(),
                                                                   Qt::KeepAspectRatio));
    m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Ok,
                                      tr("Picture is selected."),
                                      tr("Picture is selected."));
  }
  else {
    m_ui->m_lblPictureView->setPixmap(QPixmap());
    m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Error,
                                      tr("Picture is not selected."),
                                      tr("No picture is selected."));
  }

  m_ui->m_lblPictureFile->label()->setToolTip(QDir::toNativeSeparators(picture_path));
}

void FlashCardEditor::addQuestion(const QString &question,
                                  const QString &answer,
                                  const QString &hint,
                                  const QString &picture_path) {
  int marked_question = m_ui->m_listQuestions->currentRow();
  FlashCardQuestion new_question;
  QListWidgetItem *new_item = new QListWidgetItem();

  new_question.setQuestion(question);
  new_question.setHint(hint);
  new_question.setAnswer(answer);
  new_question.setPicturePath(picture_path);

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

void FlashCardEditor::addQuestion() {
  addQuestion(tr("What animal do you see on the picture?"),
              tr("cat"),
              tr("This animal is hated by dog."),
              APP_TEMPLATES_PATH + QDir::separator() +
              core()->entryPoint()->baseFolder() + QDir::separator() +
              "cat.png");
  launch();
  emit changed();
}

void FlashCardEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupQuestionEditor->setEnabled(enabled);
}

void FlashCardEditor::loadQuestion(int index) {
  m_ui->m_txtQuestion->blockSignals(true);
  m_ui->m_lblPictureFile->label()->blockSignals(true);

  if (index >= 0) {
    FlashCardQuestion question = m_ui->m_listQuestions->item(index)->data(Qt::UserRole).value<FlashCardQuestion>();

    m_ui->m_txtQuestion->lineEdit()->setText(question.question());
    m_ui->m_txtAnswer->lineEdit()->setText(question.answer());
    m_ui->m_txtHint->lineEdit()->setText(question.hint());
    loadPicture(question.picturePath());

    m_activeQuestion = question;
  }
  else {
    m_ui->m_txtQuestion->lineEdit()->setText(QString());
    m_ui->m_txtAnswer->lineEdit()->setText(QString());
    m_ui->m_txtHint->lineEdit()->setText(QString());
    loadPicture(QString());
  }

  m_ui->m_txtQuestion->blockSignals(false);
  m_ui->m_lblPictureFile->label()->blockSignals(false);

  checkAnswer();
  checkHint();

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

void FlashCardEditor::saveQuestion() {
  m_activeQuestion.setQuestion(m_ui->m_txtQuestion->lineEdit()->text());
  m_activeQuestion.setAnswer(m_ui->m_txtAnswer->lineEdit()->text());
  m_activeQuestion.setHint(m_ui->m_txtHint->lineEdit()->text());
  m_activeQuestion.setPicturePath(m_ui->m_lblPictureFile->label()->toolTip());

  m_ui->m_listQuestions->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeQuestion));
  m_ui->m_listQuestions->currentItem()->setText(m_activeQuestion.question());

  emit changed();
}

void FlashCardEditor::removeQuestion() {
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

void FlashCardEditor::onAnswerChanged(const QString& new_answer) {
  Q_UNUSED(new_answer)

  checkAnswer();
  saveQuestion();
}

void FlashCardEditor::onHintChanged(const QString& new_hint) {
  Q_UNUSED(new_hint)

  checkHint();
  saveQuestion();
}

void FlashCardEditor::onAuthorChanged(const QString& new_author) {
  Q_UNUSED(new_author)

  checkAuthor();

  launch();
  emit changed();
}

void FlashCardEditor::onNameChanged(const QString& new_name) {
  Q_UNUSED(new_name)

  checkName();

  launch();
  emit changed();
}

void FlashCardEditor::selectPicture() {
  QString selected_picture = QFileDialog::getOpenFileName(this, tr("Select picture for question"),
                                                          m_ui->m_lblPictureFile->label()->toolTip(),
                                                          tr("Images (*.gif *.jpg *.png)"),
                                                          0);

  if (!selected_picture.isEmpty()) {
    loadPicture(selected_picture);
    saveQuestion();
  }
}
