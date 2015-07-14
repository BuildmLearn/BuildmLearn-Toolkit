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

#include "templates/dictation/dictationpassage.h"
#include "templates/dictation/dictationcore.h"
#include "templates/dictation/dictationentrypoint.h"
#include "miscellaneous/iconfactory.h"
#include "miscellaneous/iofactory.h"
#include "core/templatefactory.h"

#include <QFileDialog>
#include <QTimer>


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
  
  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtTitle->lineEdit() << m_ui->m_btnPassageSelect  <<
                       m_ui->m_txtPassage << m_ui->m_txtAuthor->lineEdit() << 
                       m_ui->m_txtName->lineEdit() << m_ui->m_listPassages << 
                       m_ui->m_btnPassageAdd << m_ui->m_btnPassageRemove <<
                       m_ui->m_btnPassageUp << m_ui->m_btnPassageDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfPassages->lineEdit()->setEnabled(false);

  m_ui->m_lblPassageStatus->label()->setWordWrap(true);
  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Title for the passage"));
  m_ui->m_txtPassage->document()->clear();

  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this dictation"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this dictation"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnPassageAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnPassageRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnPassageUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnPassageDown->setIcon(factory->fromTheme("move-down"));

  // Connecting signals and slots.
  connect(m_ui->m_btnPassageSelect, SIGNAL(clicked()), this, SLOT(selectPassage()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAuthorChanged(QString)));
  connect(m_ui->m_txtPassage, SIGNAL(textChanged()), this, SLOT(onPassageChanged()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(onTitleChanged(QString)));
  connect(m_ui->m_btnPassageAdd, SIGNAL(clicked()), this, SLOT(addPassage()));
  connect(m_ui->m_btnPassageRemove, SIGNAL(clicked()), this, SLOT(removePassage()));
  connect(m_ui->m_listPassages, SIGNAL(currentRowChanged(int)), this, SLOT(loadPassage(int)));
  connect(m_ui->m_btnPassageUp, SIGNAL(clicked()), this, SLOT(movePassageUp()));
  connect(m_ui->m_btnPassageDown, SIGNAL(clicked()), this, SLOT(movePassageDown()));

  setEditorsEnabled(false);
  updatePassageCount();

  qRegisterMetaType<DictationPassage>("DictationPassage");

  checkAuthor();
  checkName();
  checkTitle();
  checkPassage();
  
  loadPassage(-1);
}

DictationEditor::~DictationEditor() {
  qDebug("Destroying DictationEditor instance.");

  delete m_ui;
}

void DictationEditor::updatePassageCount() {
  m_ui->m_txtNumberOfPassages->lineEdit()->setText(QString::number(m_ui->m_listPassages->count()));

  if (m_ui->m_listPassages->count() > 0) {
    m_ui->m_txtNumberOfPassages->setStatus(WidgetWithStatus::Ok, tr("Collection contains at least one passage."));
  }
  else {
    m_ui->m_txtNumberOfPassages->setStatus(WidgetWithStatus::Error, tr("Collection does not contain any passages."));
  }
}

bool DictationEditor::canGenerateApplications() {
  return
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !activePassages().isEmpty();
}

QString DictationEditor::generateBundleData() {
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

  foreach (const DictationPassage &passage, activePassages()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about passage.
    QDomElement passage_element = source_document.createElement("passage");
    QDomElement title_element = source_document.createElement("title");
    
    passage_element.appendChild(source_document.createTextNode(passage.passage()));
    title_element.appendChild(source_document.createTextNode(passage.title()));

    item_element.appendChild(passage_element);
    item_element.appendChild(title_element);
    
    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

bool DictationEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString passage = item.namedItem("passage").toElement().text();
      QString title = item.namedItem("title").toElement().text();
      
      if (passage.isEmpty()) {
        // TODO: error
        continue;
      }
      else {
        addPassage(title, passage);
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

// Get passage list.
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

void DictationEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void DictationEditor::checkTitle() {
  if (m_ui->m_txtTitle->lineEdit()->text().isEmpty()) {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Error,
                               tr("Title is not specified."));
  }
  else {
    m_ui->m_txtTitle->setStatus(WidgetWithStatus::Ok,
                               tr("Title is specified."));
  }
}

void DictationEditor::checkPassage() {
  if (m_ui->m_txtPassage->document()->isEmpty()) {
    m_ui->m_lblPassageStatus->setStatus(WidgetWithStatus::Error, tr("Passage is empty."), tr("Passage is empty."));
  }
  else {
	QString text = m_ui->m_txtPassage->toPlainText();
	if (text.size() > 300) {
	  text.resize(300);
	  m_ui->m_txtPassage->setText(text);
	}
    m_wordCount = m_ui->m_txtPassage->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"),
															 QString::SkipEmptyParts).count();
	if (m_wordCount < 1) {
	  m_ui->m_lblPassageStatus->setStatus(WidgetWithStatus::Error, tr("Passage has %1 words, min 2 words required")
										  .arg(QString::number(m_wordCount)), tr("Passage has %1 words, min 2 words \
										  required").arg(QString::number(m_wordCount)));
    }
    else {
	  int char_count = m_ui->m_txtPassage->document()->characterCount() - 1;
      m_ui->m_lblPassageStatus->setStatus(WidgetWithStatus::Ok, tr("Words - %1, Char - %2.").arg(
                                          QString::number(m_wordCount), QString::number(char_count)),
                                          tr("Words - %1, Char - %2.").arg(QString::number(m_wordCount),
                                          QString::number(char_count)));
    }
  }
}

void DictationEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection name is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection name is specified."));
  }
}

void DictationEditor::configureUpDown() {
  if (m_ui->m_listPassages->count() > 1) {
    int index = m_ui->m_listPassages->currentRow();

    if (index == 0) {
      m_ui->m_btnPassageUp->setEnabled(false);
      m_ui->m_btnPassageDown->setEnabled(true);
    }
    else if (index == m_ui->m_listPassages->count() - 1) {
      m_ui->m_btnPassageUp->setEnabled(true);
      m_ui->m_btnPassageDown->setEnabled(false);
    }
    else {
      m_ui->m_btnPassageUp->setEnabled(true);
      m_ui->m_btnPassageDown->setEnabled(true);
    }
  }
  else {
    m_ui->m_btnPassageUp->setEnabled(false);
    m_ui->m_btnPassageDown->setEnabled(false);
  }
}

void DictationEditor::movePassageUp() {
  int index = m_ui->m_listPassages->currentRow();

  m_ui->m_listPassages->insertItem(index - 1, m_ui->m_listPassages->takeItem(index));
  m_ui->m_listPassages->setCurrentRow(index - 1);

  emit changed();
}

void DictationEditor::movePassageDown() {
  int index = m_ui->m_listPassages->currentRow();

  m_ui->m_listPassages->insertItem(index + 1, m_ui->m_listPassages->takeItem(index));
  m_ui->m_listPassages->setCurrentRow(index + 1);

  emit changed();
}

void DictationEditor::selectPassage() {
  QString selected_passage = QFileDialog::getOpenFileName(this, tr("Select passage for the comprehension"),
                                                          m_ui->m_lblPassageStatus->label()->toolTip(),
                                                          tr("Text files (*.txt)"),
                                                          0);

  if (!selected_passage.isEmpty()) {
    selectPassage(selected_passage);
  }
}

void DictationEditor::selectPassage(const QString& passage_path) {
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

void DictationEditor::addPassage(const QString &title, const QString &passage) {
  int marked_passage = m_ui->m_listPassages->currentRow();
  DictationPassage new_passage;
  QListWidgetItem *new_item = new QListWidgetItem();

  new_passage.setPassage(passage);
  new_passage.setTitle(title);
  
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
  addPassage(tr("Title of the passage"),
              tr("Write a passage here"));
  launch();
  emit changed();
}

void DictationEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupPassageEditor->setEnabled(enabled);
}

void DictationEditor::loadPassage(int index) {
  m_ui->m_txtPassage->blockSignals(true);
  m_ui->m_lblPassageStatus->label()->blockSignals(true);

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
  m_ui->m_lblPassageStatus->label()->blockSignals(false);

  checkPassage();
  checkTitle();

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

void DictationEditor::savePassage() {
  m_activePassage.setPassage(m_ui->m_txtPassage->toPlainText());
  m_activePassage.setTitle(m_ui->m_txtTitle->lineEdit()->text());
  
  m_ui->m_listPassages->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activePassage));
  m_ui->m_listPassages->currentItem()->setText(m_activePassage.title());

  emit changed();
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

void DictationEditor::onTitleChanged(const QString& new_title) {
  Q_UNUSED(new_title)

  checkTitle();
  savePassage();
}

void DictationEditor::onPassageChanged() {
  checkPassage();
  savePassage();
}

void DictationEditor::onAuthorChanged(const QString& new_author) {
  Q_UNUSED(new_author)

  checkAuthor();

  launch();
  emit changed();
}

void DictationEditor::onNameChanged(const QString& new_name) {
  Q_UNUSED(new_name)

  checkName();

  launch();
  emit changed();
}
