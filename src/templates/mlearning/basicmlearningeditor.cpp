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

#include "templates/mlearning/basicmlearningeditor.h"

#include "miscellaneous/application.h"
#include "miscellaneous/iconfactory.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"

#include <QTimer>


BasicmLearningEditor::BasicmLearningEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::BasicmLearningEditor) {
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
  tab_order_widgets << m_ui->m_txtTitle->lineEdit() << m_ui->m_txtDescription <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_listItems << m_ui->m_btnItemAdd << m_ui->m_btnItemRemove <<
                       m_ui->m_btnItemUp << m_ui->m_btnItemDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }


  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Title of the item"));
  m_ui->m_txtNumberOfItems->lineEdit()->setEnabled(false);
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this collection"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this collection"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnItemAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnItemRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnItemUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnItemDown->setIcon(factory->fromTheme("move-down"));

  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkTitle(QString)));
  connect(m_ui->m_btnItemAdd, SIGNAL(clicked()), this, SLOT(addNewItem()));
  connect(m_ui->m_btnItemRemove, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
  connect(m_ui->m_txtDescription, SIGNAL(textChanged()), this, SLOT(saveItem()));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveItem()));
  connect(m_ui->m_listItems, SIGNAL(currentRowChanged(int)), this, SLOT(displayItem(int)));
  connect(m_ui->m_btnItemUp, SIGNAL(clicked()), this, SLOT(moveItemUp()));
  connect(m_ui->m_btnItemDown, SIGNAL(clicked()), this, SLOT(moveItemDown()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAuthorChanged(QString)));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));

  checkTitle(m_ui->m_txtTitle->lineEdit()->text());
  checkAuthor();
  checkName();
  setEditorsEnabled(false);
  updateItemCount();
}

BasicmLearningEditor::~BasicmLearningEditor() {
  delete m_ui;
}

bool BasicmLearningEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString title = item.namedItem("item_title").toElement().text();
      QString description = item.namedItem("item_description").toElement().text();

      if (title.isEmpty() || description.isEmpty()) {
        // TODO: error
        continue;
      }
      else {
        addNewItem(title, description);
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

QString BasicmLearningEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString BasicmLearningEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

void BasicmLearningEditor::addNewItem(const QString &title, const QString &description) {
  int marked_item = m_ui->m_listItems->currentRow();
  BasicmLearningItem new_item;
  QListWidgetItem *new_item_view = new QListWidgetItem();

  new_item.setTitle(title);
  new_item.setDescription(description);

  new_item_view->setText(new_item.title());
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

void BasicmLearningEditor::addNewItem() {
  addNewItem(tr("Prague"), tr("Prague is the city which lies in the heart of Europe."));
  launch();
  emit changed();
}

void BasicmLearningEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void BasicmLearningEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection title is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection title is specified."));
  }
}

void BasicmLearningEditor::onAuthorChanged(const QString& new_author) {
  Q_UNUSED(new_author)

  checkAuthor();

  launch();
  emit changed();
}

void BasicmLearningEditor::onNameChanged(const QString& new_name) {
  Q_UNUSED(new_name)

  checkName();

  launch();
  emit changed();
}

void BasicmLearningEditor::configureUpDown() {
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

QList<BasicmLearningItem> BasicmLearningEditor::activeItems() const {
  QList<BasicmLearningItem> questions;

  for (int i = 0; i < m_ui->m_listItems->count(); i++) {
    questions.append(m_ui->m_listItems->item(i)->data(Qt::UserRole).value<BasicmLearningItem>());
  }

  return questions;
}

bool BasicmLearningEditor::canGenerateApplications() {
  return
      !activeItems().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty();
}

QString BasicmLearningEditor::generateBundleData() {
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

  foreach (const BasicmLearningItem &item, activeItems()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about question.
    QDomElement title_element = source_document.createElement("item_title");
    QDomElement description_element = source_document.createElement("item_description");

    title_element.appendChild(source_document.createTextNode(item.title()));
    description_element.appendChild(source_document.createTextNode(item.description()));

    item_element.appendChild(title_element);
    item_element.appendChild(description_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

void BasicmLearningEditor::updateItemCount() {
  m_ui->m_txtNumberOfItems->lineEdit()->setText(QString::number(m_ui->m_listItems->count()));

  if (m_ui->m_listItems->count() > 0) {
    m_ui->m_txtNumberOfItems->setStatus(WidgetWithStatus::Ok, tr("Collection contains at least one item."));
  }
  else {
    m_ui->m_txtNumberOfItems->setStatus(WidgetWithStatus::Error, tr("Collection does not contain any items."));
  }
}

void BasicmLearningEditor::removeSelectedItem() {
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

void BasicmLearningEditor::saveItem() {
  m_activeItem.setTitle(m_ui->m_txtTitle->lineEdit()->text());
  m_activeItem.setDescription(m_ui->m_txtDescription->toPlainText());

  if(m_ui->m_listItems->currentItem() != NULL )
  {
    m_ui->m_listItems->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeItem));
    m_ui->m_listItems->currentItem()->setText(m_activeItem.title());
  }

  emit changed();
}

void BasicmLearningEditor::displayItem(int index) {
  if (index >= 0) {
    BasicmLearningItem item = m_ui->m_listItems->item(index)->data(Qt::UserRole).value<BasicmLearningItem>();

    m_ui->m_txtTitle->lineEdit()->setText(item.title());
    m_ui->m_txtDescription->setText(item.description());
    m_activeItem = item;
  }
  else {
    m_ui->m_txtTitle->lineEdit()->clear();
    m_ui->m_txtDescription->clear();
  }

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

void BasicmLearningEditor::checkTitle(const QString &title) {
  if (title.simplified().isEmpty()) {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Error, tr("Please, enter some title."));
  }
  else {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Ok, tr("Title seems to be okay."));
  }
}

void BasicmLearningEditor::moveItemUp() {
  int index = m_ui->m_listItems->currentRow();

  m_ui->m_listItems->insertItem(index - 1, m_ui->m_listItems->takeItem(index));
  m_ui->m_listItems->setCurrentRow(index - 1);

  emit changed();
}

void BasicmLearningEditor::moveItemDown() {
  int index = m_ui->m_listItems->currentRow();

  m_ui->m_listItems->insertItem(index + 1, m_ui->m_listItems->takeItem(index));
  m_ui->m_listItems->setCurrentRow(index + 1);

  emit changed();
}

void BasicmLearningEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupItemEditor->setEnabled(enabled);
}
