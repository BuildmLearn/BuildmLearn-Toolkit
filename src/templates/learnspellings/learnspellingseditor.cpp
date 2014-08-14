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

#include "templates/learnspellings/learnspellingseditor.h"

#include "miscellaneous/iconfactory.h"
#include "miscellaneous/application.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"

#include <QTimer>


LearnSpellingsEditor::LearnSpellingsEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::LearnSpellingsEditor) {
  m_ui->setupUi(this);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));

  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtTitle->lineEdit() << m_ui->m_txtDescription->lineEdit()  <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_listItems << m_ui->m_btnItemAdd << m_ui->m_btnItemRemove <<
                       m_ui->m_btnItemUp << m_ui->m_btnItemDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Word to spell"));
  m_ui->m_txtDescription->lineEdit()->setPlaceholderText(tr("Meaning of the word"));
  m_ui->m_txtNumberOfItems->lineEdit()->setEnabled(false);
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this collection"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this collection"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnItemAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnItemRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnItemUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnItemDown->setIcon(factory->fromTheme("move-down"));

  connect(m_ui->m_txtDescription->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkDescription(QString)));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkTitle(QString)));
  connect(m_ui->m_btnItemAdd, SIGNAL(clicked()), this, SLOT(addSampleWord()));
  connect(m_ui->m_btnItemRemove, SIGNAL(clicked()), this, SLOT(removeSelectedWord()));
  connect(m_ui->m_txtDescription->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveWord()));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveWord()));
  connect(m_ui->m_listItems, SIGNAL(currentRowChanged(int)), this, SLOT(displayWord(int)));
  connect(m_ui->m_btnItemUp, SIGNAL(clicked()), this, SLOT(moveWordUp()));
  connect(m_ui->m_btnItemDown, SIGNAL(clicked()), this, SLOT(moveWordDown()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAuthorChanged(QString)));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));

  checkDescription(m_ui->m_txtDescription->lineEdit()->text());
  checkTitle(m_ui->m_txtTitle->lineEdit()->text());
  checkAuthor();
  checkName();
  setEditorsEnabled(false);
  updateItemCount();
}

LearnSpellingsEditor::~LearnSpellingsEditor() {
  delete m_ui;
}

QString LearnSpellingsEditor::generateBundleData() {
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

  foreach (const LearnSpellingsItem &item, activeWords()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about question.
    QDomElement word_element = source_document.createElement("word");
    QDomElement meaning_element = source_document.createElement("meaning");

    word_element.appendChild(source_document.createTextNode(item.word()));
    meaning_element.appendChild(source_document.createTextNode(item.meaning()));

    item_element.appendChild(word_element);
    item_element.appendChild(meaning_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

bool LearnSpellingsEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString word = item.namedItem("word").toElement().text();
      QString meaning = item.namedItem("meaning").toElement().text();

      if (word.isEmpty()) {
        // TODO: error
        continue;
      }
      else {
        addSampleWord(word, meaning);
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

void LearnSpellingsEditor::addSampleWord(const QString &title, const QString &description) {
  int marked_item = m_ui->m_listItems->currentRow();
  LearnSpellingsItem new_item;
  QListWidgetItem *new_item_view = new QListWidgetItem();

  new_item.setWord(title);
  new_item.setMeaning(description);

  new_item_view->setText(new_item.word());
  new_item_view->setData(Qt::UserRole, QVariant::fromValue(new_item));

  if (m_ui->m_listItems->count() == 0) {
    // We are adding first item.
    setEditorsEnabled(true);

    m_ui->m_btnItemRemove->setEnabled(true);

    m_ui->m_listItems->insertItem(0, new_item_view);
    m_ui->m_listItems->setCurrentRow(0);
  }
  else {
    m_ui->m_listItems->insertItem(marked_item + 1, new_item_view);
    m_ui->m_listItems->setCurrentRow(marked_item + 1);
  }

  updateItemCount();
}

void LearnSpellingsEditor::addSampleWord() {
  addSampleWord(tr("cat"), tr("Cats are animals which are hated by dogs."));
  launch();
  emit changed();
}

void LearnSpellingsEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void LearnSpellingsEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection title is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection title is specified."));
  }
}

void LearnSpellingsEditor::onAuthorChanged(const QString& new_author) {
  Q_UNUSED(new_author)

  checkAuthor();

  launch();
  emit changed();
}

void LearnSpellingsEditor::onNameChanged(const QString& new_name) {
  Q_UNUSED(new_name)

  checkName();

  launch();
  emit changed();
}

void LearnSpellingsEditor::configureUpDown() {
  if (m_ui->m_listItems->count() > 1) {
    int index = m_ui->m_listItems->currentRow();

    if (index == 0) {
      m_ui->m_btnItemUp->setEnabled(false);
      m_ui->m_btnItemDown->setEnabled(true);
    }
    else if (index == m_ui->m_listItems->count() - 1) {
      m_ui->m_btnItemUp->setEnabled(true);
      m_ui->m_btnItemDown->setEnabled(false);
    }
    else {
      m_ui->m_btnItemUp->setEnabled(true);
      m_ui->m_btnItemDown->setEnabled(true);
    }
  }
  else {
    m_ui->m_btnItemUp->setEnabled(false);
    m_ui->m_btnItemDown->setEnabled(false);
  }
}

QList<LearnSpellingsItem> LearnSpellingsEditor::activeWords() const {
  QList<LearnSpellingsItem> questions;

  for (int i = 0; i < m_ui->m_listItems->count(); i++) {
    questions.append(m_ui->m_listItems->item(i)->data(Qt::UserRole).value<LearnSpellingsItem>());
  }

  return questions;
}

bool LearnSpellingsEditor::canGenerateApplications() {
  return
      !activeWords().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty();
}

QString LearnSpellingsEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString LearnSpellingsEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

void LearnSpellingsEditor::updateItemCount() {
  m_ui->m_txtNumberOfItems->lineEdit()->setText(QString::number(m_ui->m_listItems->count()));

  if (m_ui->m_listItems->count() > 0) {
    m_ui->m_txtNumberOfItems->setStatus(WidgetWithStatus::Ok, tr("Collection contains at least one word."));
  }
  else {
    m_ui->m_txtNumberOfItems->setStatus(WidgetWithStatus::Error, tr("Collection does not contain any words."));
  }
}

void LearnSpellingsEditor::removeSelectedWord() {
  int current_row = m_ui->m_listItems->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listItems->count() == 1) {
      // We are removing last visible question.
      setEditorsEnabled(false);

      m_ui->m_btnItemRemove->setEnabled(false);
    }

    delete m_ui->m_listItems->takeItem(current_row);
  }

  updateItemCount();
  launch();
  emit changed();
}

void LearnSpellingsEditor::saveWord() {
  m_activeItem.setWord(m_ui->m_txtTitle->lineEdit()->text());
  m_activeItem.setMeaning(m_ui->m_txtDescription->lineEdit()->text());

  m_ui->m_listItems->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeItem));
  m_ui->m_listItems->currentItem()->setText(m_activeItem.word());

  emit changed();
}

void LearnSpellingsEditor::displayWord(int index) {
  if (index >= 0) {
    LearnSpellingsItem item = m_ui->m_listItems->item(index)->data(Qt::UserRole).value<LearnSpellingsItem>();

    m_ui->m_txtTitle->lineEdit()->setText(item.word());
    m_ui->m_txtDescription->lineEdit()->setText(item.meaning());
    m_activeItem = item;
  }
  else {
    m_ui->m_txtTitle->lineEdit()->clear();
    m_ui->m_txtDescription->lineEdit()->clear();
  }

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

void LearnSpellingsEditor::checkTitle(const QString &title) {
  if (title.simplified().isEmpty()) {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Error, tr("Please, enter some word."));
  }
  else {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Ok, tr("Word seems to be okay."));
  }
}

void LearnSpellingsEditor::moveWordUp() {
  int index = m_ui->m_listItems->currentRow();

  m_ui->m_listItems->insertItem(index - 1, m_ui->m_listItems->takeItem(index));
  m_ui->m_listItems->setCurrentRow(index - 1);

  emit changed();
}

void LearnSpellingsEditor::moveWordDown() {
  int index = m_ui->m_listItems->currentRow();

  m_ui->m_listItems->insertItem(index + 1, m_ui->m_listItems->takeItem(index));
  m_ui->m_listItems->setCurrentRow(index + 1);

  emit changed();
}

void LearnSpellingsEditor::checkDescription(const QString &description) {
  if (description.simplified().isEmpty()) {
    m_ui->m_txtDescription->setStatus(WidgetWithStatus::Error, tr("Please, enter some meaning."));
  }
  else {
    m_ui->m_txtDescription->setStatus(WidgetWithStatus::Ok, tr("Meaning seems to be okay."));
  }
}

void LearnSpellingsEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupItemEditor->setEnabled(enabled);
}
