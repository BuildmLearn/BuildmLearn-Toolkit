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

#include "templates/dictation/dictationeditor.h"

#include "miscellaneous/iconfactory.h"
#include "templates/dictation/dictationpassage.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"

#include <QToolTip>
#include <QShowEvent>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QFileDialog>


DictationEditor::DictationEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::DictationEditor) {
  m_ui->setupUi(this);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);
  
  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));
  
  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);
  m_ui->m_txtTitle->lineEdit()->setValidator(title_validator);
  m_ui->m_txtPassage->setMaxLength(300);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtTitle->lineEdit() <<  m_ui->m_btnPassageSelect <<
					   m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_txtPassage << m_ui->m_listPassages << 
                       m_ui->m_btnPassageAdd << m_ui->m_btnPassageRemove <<
                       m_ui->m_btnPassageUp << m_ui->m_btnPassageDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfPassage->lineEdit()->setEnabled(false);
  m_ui->m_lblPassageStatus->label()->setWordWrap(true);

  IconFactory *factory = IconFactory::instance();

  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this dictation"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this dictation"));
  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Title"));
  m_ui->m_txtPassage->document()->clear();

  m_ui->m_btnPassageAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnPassageRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnPassageUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnPassageDown->setIcon(factory->fromTheme("move-down"));

  connect(m_ui->m_btnPassageSelect, SIGNAL(clicked()), this, SLOT(selectPassage()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateAuthorStatus()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateNameStatus()));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateTitleStatus()));
  connect(m_ui->m_txtPassage, SIGNAL(textChanged()), this, SLOT(onPassageChanged()));
  
  connect(m_ui->m_btnPassageAdd, SIGNAL(clicked()), this, SLOT(addPassage()));
  connect(m_ui->m_btnPassageRemove, SIGNAL(clicked()), this, SLOT(removePassage()));
  connect(m_ui->m_listPassages, SIGNAL(currentRowChanged(int)), this, SLOT(loadPassage(int)));

  connect(m_ui->m_btnPassageUp, SIGNAL(clicked()), this, SLOT(movePassageUp()));
  connect(m_ui->m_btnPassageDown, SIGNAL(clicked()), this, SLOT(movePassageDown()));

  setEditorsEnabled(false);
  updatePassageCount();
  checkTitle();
  checkPassage();
  checkName();
  checkAuthor();
  qRegisterMetaType<DictationPassage>("DictationPassage");
}

DictationEditor::~DictationEditor() {
  qDebug("Destroying DictationEditor instance.");

  delete m_ui;
}

QList<DictationPassage> DictationEditor::activePassages() const {
  QList<DictationPassage> passages;

  for (int i = 0; i < m_ui->m_listPassages->count(); i++) {
    passages.append(m_ui->m_listPassages->item(i)->data(Qt::UserRole).value<DictationPassage>());
  }

  return passages;
}

QString DictationEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString DictationEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

void DictationEditor::updatePassageCount() {
  m_ui->m_txtNumberOfPassage->lineEdit()->setText(QString::number(m_ui->m_listPassages->count()));

  if (m_ui->m_listPassages->count() > 0) {
    m_ui->m_txtNumberOfPassage->setStatus(WidgetWithStatus::Ok, tr("Dictation contains at least one passage."));
  }
  else {
    m_ui->m_txtNumberOfPassage->setStatus(WidgetWithStatus::Error, tr("Dictation does not contain minimum one passage."));
  }
}

void DictationEditor::addPassage(const QString &title) {
  DictationPassage new_passage;

  new_passage.setTitle(title);

  int marked_passage = m_ui->m_listPassages->currentRow();
  QListWidgetItem *new_item = new QListWidgetItem();
  new_item->setText(new_passage.title());
  new_item->setData(Qt::UserRole, QVariant::fromValue(new_passage));

  if (m_ui->m_listPassages->count() == 0) {
    // We are adding first passage.
    setEditorsEnabled(true);

    m_ui->m_btnPassageRemove->setEnabled(true);

    m_ui->m_listPassages->insertItem(0, new_item);
    m_ui->m_listPassages->setCurrentRow(0);
  }
  else {
    m_ui->m_listPassages->insertItem(marked_passage + 1, new_item);
    m_ui->m_listPassages->setCurrentRow(marked_passage + 1);
  }

  updatePassageCount();
}

void DictationEditor::addPassage() {
  addPassage(tr("Passage"),
              QStringList() << tr("Option 1") << tr("Option 2") <<
              tr("Option 3") << tr("Option 4"),
              1);

  launch();
  emit changed();
}

void DictationEditor::loadPassage(int index) {
  m_ui->m_txtPassage->blockSignals(true);
  m_ui->m_txtTitle->blockSignals(true);
  if (index >= 0) {
    DictationPassage passage = m_ui->m_listPassages->item(index)->data(Qt::UserRole).value<DictationPassage>();

    m_ui->m_txtPassage->setText(passage.passage());
    m_ui->m_txtTitle->lineEdit()->setText(passage.title());
    
    m_activePassage = passage;
  }
  else {
    m_ui->m_txtPassage->setText(QString());
    m_ui->m_txtTitle->lineEdit()->setText(QString());
  }

  m_ui->m_txtPassage->blockSignals(false);
  m_ui->m_txtTitle->blockSignals(false);
}

void DictationEditor::removePassage() {
  int current_row = m_ui->m_listPassages->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listPassages->count() == 1) {
      // We are removing last visible passage.
      setEditorsEnabled(false);

      m_ui->m_btnPassageRemove->setEnabled(false);
    }

    delete m_ui->m_listPassages->takeItem(current_row);
  }

  updatePassageCount();
  launch();
  emit changed();
}
