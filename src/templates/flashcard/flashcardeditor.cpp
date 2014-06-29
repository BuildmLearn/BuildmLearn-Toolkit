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


#include <QFileDialog>


FlashCardEditor::FlashCardEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::FlashCardEditor) {
  m_ui->setupUi(this);

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
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));
  connect(m_ui->m_txtAnswer->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAnswerChanged(QString)));
  connect(m_ui->m_txtHint->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onHintChanged(QString)));
  connect(m_ui->m_btnQuestionAdd, SIGNAL(clicked()), this, SLOT(addQuestion()));
  connect(m_ui->m_btnQuestionRemove, SIGNAL(clicked()), this, SLOT(removeQuestion()));
  connect(m_ui->m_listQuestions, SIGNAL(currentRowChanged(int)), this, SLOT(loadQuestion(int)));

  setEditorsEnabled(false);
  updateQuestionCount();

  m_ui->m_txtAuthor->lineEdit()->setText(tr("John Doe"));
  m_ui->m_txtName->lineEdit()->setText(tr("Greatest collection"));

  qRegisterMetaType<FlashCardQuestion>("FlashCardQuestion");
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

void FlashCardEditor::launch() {
  if (canGenerateApplications()) {
    emit canGenerateChanged(true);
  }
  else {
    emit canGenerateChanged(false, tr("Simulation or mobile application generation of flash card template cannot be started \n"
                                      "because there is no question added or quiz does not have name."));
  }
}

QList<FlashCardQuestion> FlashCardEditor::activeQuestions() const {
  QList<FlashCardQuestion> questions;

  for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
    questions.append(m_ui->m_listQuestions->item(i)->data(Qt::UserRole).value<FlashCardQuestion>());
  }

  return questions;
}

void FlashCardEditor::loadPicture(const QString& picture_path) {
  if (!picture_path.isEmpty()) {
    m_ui->m_lblPictureView->setPixmap(QPixmap(picture_path).scaled(m_ui->m_lblPictureView->size(),
                                                                   Qt::KeepAspectRatio));
    m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Ok,
                                      QDir::toNativeSeparators(picture_path),
                                      tr("Picture is selected."));
  }
  else {
    m_ui->m_lblPictureView->setPixmap(QPixmap());
    m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Error,
                                      QString(),
                                      tr("No picture is selected."));
  }
}

void FlashCardEditor::addQuestion() {
  int marked_question = m_ui->m_listQuestions->currentRow();
  FlashCardQuestion new_question;
  QListWidgetItem *new_item = new QListWidgetItem();

  new_question.setQuestion(tr("What animal do you see on the picture?"));
  new_question.setHint(tr("This animal is hated by dog."));
  new_question.setAnswer("cat");
  new_question.setPicturePath(APP_TEMPLATES_PATH + QDir::separator() +
                              core()->entryPoint()->baseFolder() + QDir::separator() +
                              "cat.png");

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
  launch();
  emit changed();
}

void FlashCardEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupQuestionEditor->setEnabled(enabled);
}

void FlashCardEditor::loadQuestion(int index) {
  m_ui->m_txtQuestion->blockSignals(true);
  m_ui->m_txtAnswer->lineEdit()->blockSignals(true);
  m_ui->m_txtHint->lineEdit()->blockSignals(true);
  m_ui->m_lblPictureFile->label()->blockSignals(true);

  if (index >= 0) {
    FlashCardQuestion question = m_ui->m_listQuestions->item(index)->data(Qt::UserRole).value<FlashCardQuestion>();

    m_ui->m_txtQuestion->setText(question.question());
    m_ui->m_txtAnswer->lineEdit()->setText(question.answer());
    m_ui->m_txtHint->lineEdit()->setText(question.hint());
    loadPicture(question.picturePath());
  }
  else {
    m_ui->m_txtQuestion->setText(QString());
    m_ui->m_txtAnswer->lineEdit()->setText(QString());
    m_ui->m_txtHint->lineEdit()->setText(QString());
    loadPicture(QString());
  }

  m_ui->m_txtQuestion->blockSignals(false);
  m_ui->m_txtAnswer->lineEdit()->blockSignals(false);
  m_ui->m_txtHint->lineEdit()->blockSignals(false);
  m_ui->m_lblPictureFile->label()->blockSignals(false);
}

void FlashCardEditor::removeQuestion() {

}

void FlashCardEditor::onAnswerChanged(const QString& new_answer) {
  if (new_answer.isEmpty()) {
    m_ui->m_txtAnswer->setStatus(WidgetWithStatus::Error,
                                 tr("Answer is not specified."));
  }
  else {
    m_ui->m_txtAnswer->setStatus(WidgetWithStatus::Ok,
                                 tr("Answer is specified."));
  }
}

void FlashCardEditor::onHintChanged(const QString& new_hint) {
  if (new_hint.isEmpty()) {
    m_ui->m_txtHint->setStatus(WidgetWithStatus::Warning,
                               tr("Hint is not specified."));
  }
  else {
    m_ui->m_txtHint->setStatus(WidgetWithStatus::Ok,
                               tr("Hint is specified."));
  }
}

void FlashCardEditor::onAuthorChanged(const QString& new_author) {
  if (new_author.isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void FlashCardEditor::onNameChanged(const QString& new_name) {
  if (new_name.isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection name is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection name is specified."));
  }
}

void FlashCardEditor::selectPicture() {
  QString selected_picture = QFileDialog::getOpenFileName(this, tr("Select picture for question"),
                                                          m_ui->m_lblPictureFile->label()->text(),
                                                          tr("Images (*.gif *.jpg *.png)"),
                                                          0,
                                                          QFileDialog::DontUseNativeDialog);

  loadPicture(selected_picture);
}
