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

#include "miscellaneous/iconfactory.h"

#include <QTimer>


BasicmLearningEditor::BasicmLearningEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::BasicmLearningEditor) {
  m_ui->setupUi(this);

  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Title of the item"));
  m_ui->m_txtDescription->lineEdit()->setPlaceholderText(tr("Description of the item"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnItemAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnItemRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnItemUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnItemDown->setIcon(factory->fromTheme("move-down"));

  connect(m_ui->m_txtDescription->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkDescription(QString)));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkTitle(QString)));
  connect(m_ui->m_btnItemAdd, SIGNAL(clicked()), this, SLOT(addNewItem()));
  connect(m_ui->m_btnItemRemove, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
  connect(m_ui->m_txtDescription->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveItem()));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveItem()));
  connect(m_ui->m_listItems, SIGNAL(currentRowChanged(int)), this, SLOT(displayItem(int)));
  connect(m_ui->m_btnItemUp, SIGNAL(clicked()), this, SLOT(moveItemUp()));
  connect(m_ui->m_btnItemDown, SIGNAL(clicked()), this, SLOT(moveItemDown()));

  checkDescription(m_ui->m_txtDescription->lineEdit()->text());
  checkTitle(m_ui->m_txtTitle->lineEdit()->text());
  setEditorsEnabled(false);
}

BasicmLearningEditor::~BasicmLearningEditor() {
  delete m_ui;
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
  return !activeItems().isEmpty();
}

void BasicmLearningEditor::launch() {
  if (canGenerateApplications()) {
    emit canGenerateChanged(true);
  }
  else {
    emit canGenerateChanged(false, tr("Simulation or mobile application generation cannot be started \n"
                                      "because there is no question added or quiz does not have name."));
  }
}

void BasicmLearningEditor::addNewItem() {
  int marked_item = m_ui->m_listItems->currentRow();
  BasicmLearningItem new_item;
  QListWidgetItem *new_item_view = new QListWidgetItem();

  new_item.setTitle(tr("Prague"));
  new_item.setDescription(tr("Prague is the city which lies in the heart of Europe."));

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

  launch();
  emit changed();
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

  launch();
  emit changed();
}

void BasicmLearningEditor::saveItem() {
  m_activeItem.setTitle(m_ui->m_txtTitle->lineEdit()->text());
  m_activeItem.setDescription(m_ui->m_txtDescription->lineEdit()->text());

  m_ui->m_listItems->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeItem));
  m_ui->m_listItems->currentItem()->setText(m_activeItem.title());

  emit changed();
}

void BasicmLearningEditor::displayItem(int index) {
  if (index >= 0) {
    BasicmLearningItem item = m_ui->m_listItems->item(index)->data(Qt::UserRole).value<BasicmLearningItem>();

    m_ui->m_txtTitle->lineEdit()->setText(item.title());
    m_ui->m_txtDescription->lineEdit()->setText(item.description());
    m_activeItem = item;
  }
  else {
    m_ui->m_txtTitle->lineEdit()->clear();
    m_ui->m_txtDescription->lineEdit()->clear();
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

void BasicmLearningEditor::checkDescription(const QString &description) {
  if (description.simplified().isEmpty()) {
    m_ui->m_txtDescription->setStatus(WidgetWithStatus::Error, tr("Please, enter some description."));
  }
  else {
    m_ui->m_txtDescription->setStatus(WidgetWithStatus::Ok, tr("Description seems to be okay."));
  }
}

void BasicmLearningEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupItemEditor->setEnabled(enabled);
}
