#include "templates/learnspellings/learnspellingseditor.h"

#include "miscellaneous/iconfactory.h"

#include <QTimer>


LearnSpellingsEditor::LearnSpellingsEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::LearnSpellingsEditor) {
  m_ui->setupUi(this);

  m_ui->m_txtTitle->lineEdit()->setPlaceholderText(tr("Word to spell"));
  m_ui->m_txtDescription->lineEdit()->setPlaceholderText(tr("Meaning of the word"));
  m_ui->m_txtNumberOfItems->lineEdit()->setReadOnly(true);
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this collection"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this collection"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnItemAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnItemRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnItemUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnItemDown->setIcon(factory->fromTheme("move-down"));

  m_ui->m_txtAuthor->lineEdit()->setText(tr("John Doe"));
  m_ui->m_txtName->lineEdit()->setText(tr("Greatest collection"));

  connect(m_ui->m_txtDescription->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkDescription(QString)));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(checkTitle(QString)));
  connect(m_ui->m_btnItemAdd, SIGNAL(clicked()), this, SLOT(addNewItem()));
  connect(m_ui->m_btnItemRemove, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
  connect(m_ui->m_txtDescription->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveItem()));
  connect(m_ui->m_txtTitle->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveItem()));
  connect(m_ui->m_listItems, SIGNAL(currentRowChanged(int)), this, SLOT(displayItem(int)));
  connect(m_ui->m_btnItemUp, SIGNAL(clicked()), this, SLOT(moveItemUp()));
  connect(m_ui->m_btnItemDown, SIGNAL(clicked()), this, SLOT(moveItemDown()));
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
  return QString();
}

bool LearnSpellingsEditor::loadBundleData(const QString &bundle_data) {
  return false;
}

void LearnSpellingsEditor::launch() {
  if (canGenerateApplications()) {
    issueNewGenereationStatus(true);
  }
  else {
    issueNewGenereationStatus(false,
                              tr("Simulation or mobile application generation cannot be started \n"
                                 "because there is no word added or collection does not have name."));
  }
}

void LearnSpellingsEditor::addNewItem(const QString &title, const QString &description) {
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

void LearnSpellingsEditor::addNewItem() {
  addNewItem(tr("cat"), tr("Cats are animals which are hated by dogs."));
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
  checkAuthor();

  launch();
  emit changed();
}

void LearnSpellingsEditor::onNameChanged(const QString& new_name) {
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
  return !activeWords().isEmpty();
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

void LearnSpellingsEditor::removeSelectedItem() {
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

void LearnSpellingsEditor::saveItem() {
  m_activeItem.setWord(m_ui->m_txtTitle->lineEdit()->text());
  m_activeItem.setMeaning(m_ui->m_txtDescription->lineEdit()->text());

  m_ui->m_listItems->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeItem));
  m_ui->m_listItems->currentItem()->setText(m_activeItem.word());

  emit changed();
}

void LearnSpellingsEditor::displayItem(int index) {
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

void LearnSpellingsEditor::moveItemUp() {
  int index = m_ui->m_listItems->currentRow();

  m_ui->m_listItems->insertItem(index - 1, m_ui->m_listItems->takeItem(index));
  m_ui->m_listItems->setCurrentRow(index - 1);

  emit changed();
}

void LearnSpellingsEditor::moveItemDown() {
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
