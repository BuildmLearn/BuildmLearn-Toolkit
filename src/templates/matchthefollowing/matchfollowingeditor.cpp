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

#include "templates/matchthefollowing/matchfollowingeditor.h"
#include "templates/matchthefollowing/listdelegate.h"
#include "templates/matchthefollowing/matchfollowingcore.h"
#include "templates/matchthefollowing/matchfollowingentrypoint.h"
#include "miscellaneous/iconfactory.h"
#include "miscellaneous/iofactory.h"
#include "core/templatefactory.h"

#include <QTimer>
#include <QFileDialog>


MatchFollowingEditor::MatchFollowingEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::MatchFollowingEditor) {
  m_ui->setupUi(this);

  // Set initial delegate.
  m_ui->m_listTopics->setItemDelegate(NULL);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));

  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);

  // Set validators.
  QRegExpValidator *first_list_topic_validator = new QRegExpValidator(this);
  QRegExpValidator *second_list_topic_validator = new QRegExpValidator(this);

  first_list_topic_validator->setRegExp(QRegExp(".{,100}"));
  second_list_topic_validator->setRegExp(QRegExp(".{,100}"));

  m_ui->m_txtFirstListTopic->lineEdit()->setValidator(first_list_topic_validator);
  m_ui->m_txtSecondListTopic->lineEdit()->setValidator(second_list_topic_validator);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtFirstListTopic->lineEdit() << m_ui->m_txtSecondListTopic <<
                       m_ui->m_txtTemplateTitle->lineEdit() << m_ui->m_txtFirstListTitle <<
                       m_ui->m_txtSecondListTitle->lineEdit() << m_ui->m_txtAuthor->lineEdit() <<
                       m_ui->m_txtName->lineEdit() << m_ui->m_listTopics <<
                       m_ui->m_btnTopicAdd << m_ui->m_btnTopicRemove <<
                       m_ui->m_btnTopicUp << m_ui->m_btnTopicDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfTopics->lineEdit()->setEnabled(false);

  // Set Default Text.
  m_ui->m_txtFirstListTopic->lineEdit()->setPlaceholderText(tr("First Set Topic"));
  m_ui->m_txtSecondListTopic->lineEdit()->setPlaceholderText(tr("Matching Topic"));
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this Collection"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this Collection"));
  m_ui->m_txtTemplateTitle->lineEdit()->setText("Match the following");
  m_ui->m_txtFirstListTitle->lineEdit()->setText("A");
  m_ui->m_txtSecondListTitle->lineEdit()->setText("B");
  

  // Set Icons for the buttons.
  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnTopicAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnTopicRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnTopicUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnTopicDown->setIcon(factory->fromTheme("move-down"));

  // Set Signals and Slots.
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAuthorChanged(QString)));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));
  connect(m_ui->m_txtFirstListTopic->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(onFirstListTopicChanged(QString)));
  connect(m_ui->m_txtSecondListTopic->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onSecondListTopicChanged(QString)));
  connect(m_ui->m_txtTemplateTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onTemplateTitleChanged(QString)));
  connect(m_ui->m_txtFirstListTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onFirstListTitleChanged(QString)));
  connect(m_ui->m_txtSecondListTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onSecondListTitleChanged(QString)));
  connect(m_ui->m_btnTopicAdd, SIGNAL(clicked()), this, SLOT(addTopic()));
  connect(m_ui->m_btnTopicRemove, SIGNAL(clicked()), this, SLOT(removeTopic()));
  connect(m_ui->m_listTopics, SIGNAL(currentRowChanged(int)), this, SLOT(loadTopic(int)));
  connect(m_ui->m_btnTopicUp, SIGNAL(clicked()), this, SLOT(moveTopicUp()));
  connect(m_ui->m_btnTopicDown, SIGNAL(clicked()), this, SLOT(moveTopicDown()));

  setEditorsEnabled(false);
  updateTopicCount();

  qRegisterMetaType<MatchFollowingTopic>("MatchFollowingTopic");

  // Start the validation.
  checkFirstListTopic();
  checkSecondListTopic();
  checkTemplateTitle();
  checkFirstListTitle();
  checkSecondListTitle();
  checkAuthor();
  checkName();

  loadTopic(-1);
}

MatchFollowingEditor::~MatchFollowingEditor() {
  qDebug("Destroying MatchFollowingEditor instance.");

  delete m_ui;
}

// For Updating the number of topics present in the List.
void MatchFollowingEditor::updateTopicCount() {
  m_ui->m_txtNumberOfTopics->lineEdit()->setText(QString::number(m_ui->m_listTopics->count()));

  if (m_ui->m_listTopics->count() > 1) {
    m_ui->m_txtNumberOfTopics->setStatus(WidgetWithStatus::Ok, tr("Collection contains at least two topics."));
  }
  else {
    m_ui->m_txtNumberOfTopics->setStatus(WidgetWithStatus::Error, tr("Collection does not contain minimum two topics."));
  }
}

bool MatchFollowingEditor::canGenerateApplications() {
  return
    !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
    !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
    !m_ui->m_txtTemplateTitle->lineEdit()->text().simplified().isEmpty() &&
    !m_ui->m_txtFirstListTitle->lineEdit()->text().simplified().isEmpty() &&
    !m_ui->m_txtSecondListTitle->lineEdit()->text().simplified().isEmpty() &&
    activeTopics().count() > 1;
}

// For Generating Bundle Data.
QString MatchFollowingEditor::generateBundleData() {
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
  
  QDomElement template_title_element = source_document.createElement("templateTitle");
  QDomElement first_list_title_element = source_document.createElement("firstListTitle");
  QDomElement second_list_title_element = source_document.createElement("secondListTitle");

  template_title_element.appendChild(source_document.createTextNode(m_ui->m_txtTemplateTitle->lineEdit()->text()));
  first_list_title_element.appendChild(source_document.createTextNode(m_ui->m_txtFirstListTitle->lineEdit()->text()));
  second_list_title_element.appendChild(source_document.createTextNode(m_ui->m_txtSecondListTitle->lineEdit()->text()));

  data_element.appendChild(template_title_element);
  data_element.appendChild(first_list_title_element);
  data_element.appendChild(second_list_title_element);

  foreach (const MatchFollowingTopic &topic, activeTopics()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about topic.
    QDomElement first_list_topic_element = source_document.createElement("firstListTopic");
    QDomElement second_list_topic_element = source_document.createElement("secondListTopic");

    first_list_topic_element.appendChild(source_document.createTextNode(topic.firstListTopic()));
    second_list_topic_element.appendChild(source_document.createTextNode(topic.secondListTopic()));

    item_element.appendChild(first_list_topic_element);
    item_element.appendChild(second_list_topic_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

// For Loading bundle data.
bool MatchFollowingEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString first_list_topic = item.namedItem("firstListTopic").toElement().text();
      QString second_list_topic = item.namedItem("secondListTopic").toElement().text();
      
      if (first_list_topic.isEmpty() || second_list_topic.isEmpty()) {
        // TODO: error
        continue;
      }
      else {
        addTopic(first_list_topic, second_list_topic);
      }
    }
  }

  // Load author & name.
  m_ui->m_txtAuthor->lineEdit()->setText(bundle_document.documentElement().namedItem("author").namedItem("name").toElement().text());
  m_ui->m_txtName->lineEdit()->setText(bundle_document.documentElement().namedItem("title").toElement().text());
  
  // Load template details
  m_ui->m_txtTemplateTitle->lineEdit()->setText(bundle_document.documentElement().namedItem("data").namedItem("templateTitle").toElement().text());
  m_ui->m_txtFirstListTitle->lineEdit()->setText(bundle_document.documentElement().namedItem("data").namedItem("firstListTitle").toElement().text());
  m_ui->m_txtSecondListTitle->lineEdit()->setText(bundle_document.documentElement().namedItem("data").namedItem("secondListTitle").toElement().text());

  return true;
}

// Storing the topics in a list.
QList<MatchFollowingTopic> MatchFollowingEditor::activeTopics() const {
  QList<MatchFollowingTopic> topics;

  for (int i = 0; i < m_ui->m_listTopics->count(); i++) {
    topics.append(m_ui->m_listTopics->item(i)->data(Qt::UserRole).value<MatchFollowingTopic>());
  }

  return topics;
}

QString MatchFollowingEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString MatchFollowingEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

void MatchFollowingEditor::checkFirstListTopic() {
  if (m_ui->m_txtFirstListTopic->lineEdit()->text().isEmpty()) {
    m_ui->m_txtFirstListTopic->setStatus(WidgetWithStatus::Error,
                                         tr("Topic is not specified."));
  }
  else {
    m_ui->m_txtFirstListTopic->setStatus(WidgetWithStatus::Ok,
                                         tr("Topic is specified."));
  }
}

void MatchFollowingEditor::checkSecondListTopic() {
  if (m_ui->m_txtSecondListTopic->lineEdit()->text().isEmpty()) {
    m_ui->m_txtSecondListTopic->setStatus(WidgetWithStatus::Error,
                                          tr("Topic is not specified."));
  }
  else {
    m_ui->m_txtSecondListTopic->setStatus(WidgetWithStatus::Ok,
                                          tr("Topic is specified."));
  }
}

void MatchFollowingEditor::checkTemplateTitle() {
  if (m_ui->m_txtTemplateTitle->lineEdit()->text().isEmpty()) {
    m_ui->m_txtTemplateTitle->setStatus(WidgetWithStatus::Error,
                                        tr("Title is not specified."));
  }
  else {
    m_ui->m_txtTemplateTitle->setStatus(WidgetWithStatus::Ok,
                                        tr("Title is specified."));
  }
}

void MatchFollowingEditor::checkFirstListTitle() {
  if (m_ui->m_txtFirstListTitle->lineEdit()->text().isEmpty()) {
    m_ui->m_txtFirstListTitle->setStatus(WidgetWithStatus::Error,
                                         tr("Title is not specified."));
  }
  else {
    m_ui->m_txtFirstListTitle->setStatus(WidgetWithStatus::Ok,
                                         tr("Title is specified."));
  }
}

void MatchFollowingEditor::checkSecondListTitle() {
  if (m_ui->m_txtSecondListTitle->lineEdit()->text().isEmpty()) {
    m_ui->m_txtSecondListTitle->setStatus(WidgetWithStatus::Error,
                                          tr("Title is not specified."));
  }
  else {
    m_ui->m_txtSecondListTitle->setStatus(WidgetWithStatus::Ok,
                                          tr("Title is specified."));
  }
}

void MatchFollowingEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void MatchFollowingEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection name is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection name is specified."));
  }
}

// Configuring up/down button for QListWidget.
void MatchFollowingEditor::configureUpDown() {
  if (m_ui->m_listTopics->count() > 1) {
    int index = m_ui->m_listTopics->currentRow();

    if (index == 0) {
      m_ui->m_btnTopicUp->setEnabled(false);
      m_ui->m_btnTopicDown->setEnabled(true);
    }
    else if (index == m_ui->m_listTopics->count() - 1) {
      m_ui->m_btnTopicUp->setEnabled(true);
      m_ui->m_btnTopicDown->setEnabled(false);
    }
    else {
      m_ui->m_btnTopicUp->setEnabled(true);
      m_ui->m_btnTopicDown->setEnabled(true);
    }
  }
  else {
    m_ui->m_btnTopicUp->setEnabled(false);
    m_ui->m_btnTopicDown->setEnabled(false);
  }
}

void MatchFollowingEditor::moveTopicUp() {
  int index = m_ui->m_listTopics->currentRow();

  m_ui->m_listTopics->insertItem(index - 1, m_ui->m_listTopics->takeItem(index));
  m_ui->m_listTopics->setCurrentRow(index - 1);

  emit changed();
}

void MatchFollowingEditor::moveTopicDown() {
  int index = m_ui->m_listTopics->currentRow();

  m_ui->m_listTopics->insertItem(index + 1, m_ui->m_listTopics->takeItem(index));
  m_ui->m_listTopics->setCurrentRow(index + 1);

  emit changed();
}

// For adding a new topic in the list.
void MatchFollowingEditor::addTopic(const QString &firstListTopic,
                                    const QString &secondListTopic) {

  // Set Delegate.
  bool nullDelegate = false;
  if (m_ui->m_listTopics->itemDelegate() == NULL) {
    nullDelegate = true;
    m_ui->m_listTopics->setItemDelegate(new ListDelegate());
  }

  int marked_topic = m_ui->m_listTopics->currentRow();
  MatchFollowingTopic new_topic;
  new_topic.setFirstListTopic(firstListTopic);
  new_topic.setSecondListTopic(secondListTopic);

  QListWidgetItem *new_item = new QListWidgetItem();
  new_item->setData(Qt::UserRole, QVariant::fromValue(new_topic));
  new_item->setData(Qt::UserRole + 1, firstListTopic);
  new_item->setData(Qt::UserRole + 2, secondListTopic);
  new_item->setData(Qt::UserRole + 3, m_ui->m_txtFirstListTitle->lineEdit()->text());
  new_item->setData(Qt::UserRole + 4, m_ui->m_txtSecondListTitle->lineEdit()->text());

  if (m_ui->m_listTopics->count() == 0) {
    // We are adding first topic.
    setEditorsEnabled(true);
    m_ui->m_btnTopicRemove->setEnabled(true);

    m_ui->m_listTopics->insertItem(0, new_item);
    m_ui->m_listTopics->setCurrentRow(0);
  }
  else {
    m_ui->m_listTopics->insertItem(marked_topic + 1, new_item);
    m_ui->m_listTopics->setCurrentRow(marked_topic + 1);
    if (nullDelegate) {
      delete m_ui->m_listTopics->takeItem(0);
      setEditorsEnabled(true);
      m_ui->m_btnTopicRemove->setEnabled(true);
    }
  }

  updateTopicCount();
}

void MatchFollowingEditor::addTopic() {
  addTopic(tr("Topic 1"),
           tr("Topic 2"));
  launch();
  emit changed();
}

void MatchFollowingEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupTopicEditor->setEnabled(enabled);
}

// For selecting a topic from the list.
void MatchFollowingEditor::loadTopic(int index) {
  m_ui->m_txtFirstListTopic->blockSignals(true);
  m_ui->m_txtSecondListTopic->blockSignals(true);

  if (index >= 0) {
    MatchFollowingTopic topic = m_ui->m_listTopics->item(index)->data(Qt::UserRole).value<MatchFollowingTopic>();

    m_ui->m_txtFirstListTopic->lineEdit()->setText(topic.firstListTopic());
    m_ui->m_txtSecondListTopic->lineEdit()->setText(topic.secondListTopic());

    m_activeTopic = topic;
  }
  else {
    m_ui->m_txtFirstListTopic->lineEdit()->setText(QString());
    m_ui->m_txtSecondListTopic->lineEdit()->setText(QString());
  }

  m_ui->m_txtFirstListTopic->blockSignals(false);
  m_ui->m_txtSecondListTopic->blockSignals(false);

  checkFirstListTopic();
  checkSecondListTopic();

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

// For saving the data of individual topic present in the list.
void MatchFollowingEditor::saveTopic() {
  m_activeTopic.setFirstListTopic(m_ui->m_txtFirstListTopic->lineEdit()->text());
  m_activeTopic.setSecondListTopic(m_ui->m_txtSecondListTopic->lineEdit()->text());

  m_ui->m_listTopics->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeTopic));
  m_ui->m_listTopics->currentItem()->setData(Qt::UserRole + 1, m_activeTopic.firstListTopic());
  m_ui->m_listTopics->currentItem()->setData(Qt::UserRole + 2, m_activeTopic.secondListTopic());

  emit changed();
}

// For removing the topic from the list.
void MatchFollowingEditor::removeTopic() {
  int current_row = m_ui->m_listTopics->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listTopics->count() == 1) {
      // We are removing last visible topic.
      m_ui->m_listTopics->setItemDelegate(NULL);
      setEditorsEnabled(false);
      m_ui->m_btnTopicRemove->setEnabled(false);
      m_ui->m_txtNumberOfTopics->lineEdit()->setText("0");
      m_ui->m_txtFirstListTopic->lineEdit()->setText(QString::null);
      m_ui->m_txtSecondListTopic->lineEdit()->setText(QString::null);
      m_ui->m_txtFirstListTopic->setStatus(WidgetWithStatus::Error,
                                           tr("Topic is not specified."));
    }
    else {
      delete m_ui->m_listTopics->takeItem(current_row);
      updateTopicCount();
    }
  }

  launch();
  emit changed();
}

// For saving the various titles, will be completed with simulator part.
void MatchFollowingEditor::saveTitle() {
  for (int i = 0; i < m_ui->m_listTopics->count(); ++i) {
    m_ui->m_listTopics->item(i)->setData(Qt::UserRole + 3, m_ui->m_txtFirstListTitle->lineEdit()->text());
    m_ui->m_listTopics->item(i)->setData(Qt::UserRole + 4, m_ui->m_txtSecondListTitle->lineEdit()->text());
  }
}

void MatchFollowingEditor::onFirstListTopicChanged(const QString& new_title) {
  Q_UNUSED(new_title);

  checkFirstListTopic();
  saveTopic();
}

void MatchFollowingEditor::onSecondListTopicChanged(const QString& new_secondListTopic) {
  Q_UNUSED(new_secondListTopic);

  checkSecondListTopic();
  saveTopic();
}

void MatchFollowingEditor::onTemplateTitleChanged(const QString& new_title) {
  Q_UNUSED(new_title);

  checkTemplateTitle();

  launch();
  emit changed();
}

void MatchFollowingEditor::onFirstListTitleChanged(const QString& new_title) {
  Q_UNUSED(new_title);

  checkFirstListTitle();
  saveTitle();

  launch();
  emit changed();
}

void MatchFollowingEditor::onSecondListTitleChanged(const QString& new_title) {
  Q_UNUSED(new_title);

  checkSecondListTitle();
  saveTitle();

  launch();
  emit changed();
}

void MatchFollowingEditor::onAuthorChanged(const QString& new_author) {
  Q_UNUSED(new_author);

  checkAuthor();

  launch();
  emit changed();
}

void MatchFollowingEditor::onNameChanged(const QString& new_name) {
  Q_UNUSED(new_name);

  checkName();

  launch();
  emit changed();
}
