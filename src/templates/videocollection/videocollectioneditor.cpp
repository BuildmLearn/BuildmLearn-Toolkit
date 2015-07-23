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

#include "templates/videocollection/videocollectioneditor.h"

#include "templates/videocollection/videocollectionvideo.h"
#include "templates/videocollection/videocollectioncore.h"
#include "templates/videocollection/videocollectionentrypoint.h"
#include "miscellaneous/iconfactory.h"
#include "miscellaneous/iofactory.h"
#include "core/templatefactory.h"

#include <QTimer>
#include <QFileDialog>


VideoCollectionEditor::VideoCollectionEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::VideoCollectionEditor) {
  m_ui->setupUi(this);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));

  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);

  // Set validators.
  QRegExpValidator *video_validator = new QRegExpValidator(this);
  QRegExpValidator *hint_validator = new QRegExpValidator(this);

  video_validator->setRegExp(QRegExp(".{,100}"));
  hint_validator->setRegExp(QRegExp(".{,30}"));

  m_ui->m_txtVideo->lineEdit()->setValidator(video_validator);
  m_ui->m_txtHint->lineEdit()->setValidator(hint_validator);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtVideo->lineEdit() << m_ui->m_btnPictureSelect  <<
                       m_ui->m_txtAnswer->lineEdit() << m_ui->m_txtHint->lineEdit() <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_listVideos << m_ui->m_btnVideoAdd << m_ui->m_btnVideoRemove <<
                       m_ui->m_btnVideoUp << m_ui->m_btnVideoDown;

  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfVideos->lineEdit()->setEnabled(false);

  m_ui->m_lblPictureFile->label()->setWordWrap(true);
  m_ui->m_txtAnswer->lineEdit()->setPlaceholderText(tr("Answer for the answer"));
  m_ui->m_txtHint->lineEdit()->setPlaceholderText(tr("Hint for the answer"));

  m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Error, QString(), tr("No picture selected"));
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Author of this quiz"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("Name of this quiz"));

  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnVideoAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnVideoRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnVideoUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnVideoDown->setIcon(factory->fromTheme("move-down"));

  connect(m_ui->m_btnPictureSelect, SIGNAL(clicked()), this, SLOT(selectPicture()));
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onAuthorChanged(QString)));
  connect(m_ui->m_txtVideo->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(saveVideo()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));
  connect(m_ui->m_txtAnswer->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(onAnswerChanged(QString)));
  connect(m_ui->m_txtHint->lineEdit(), SIGNAL(textEdited(QString)), this, SLOT(onHintChanged(QString)));
  connect(m_ui->m_btnVideoAdd, SIGNAL(clicked()), this, SLOT(addVideo()));
  connect(m_ui->m_btnVideoRemove, SIGNAL(clicked()), this, SLOT(removeVideo()));
  connect(m_ui->m_listVideos, SIGNAL(currentRowChanged(int)), this, SLOT(loadVideo(int)));
  connect(m_ui->m_btnVideoUp, SIGNAL(clicked()), this, SLOT(moveVideoUp()));
  connect(m_ui->m_btnVideoDown, SIGNAL(clicked()), this, SLOT(moveVideoDown()));

  setEditorsEnabled(false);
  updateVideoCount();

  qRegisterMetaType<VideoCollectionVideo>("VideoCollectionVideo");

  checkAuthor();
  checkName();
  loadVideo(-1);
}

VideoCollectionEditor::~VideoCollectionEditor() {
  qDebug("Destroying VideoCollectionEditor instance.");

  delete m_ui;
}

void VideoCollectionEditor::updateVideoCount() {
  m_ui->m_txtNumberOfVideos->lineEdit()->setText(QString::number(m_ui->m_listVideos->count()));

  if (m_ui->m_listVideos->count() > 0) {
    m_ui->m_txtNumberOfVideos->setStatus(WidgetWithStatus::Ok, tr("Collection contains at least one video."));
  }
  else {
    m_ui->m_txtNumberOfVideos->setStatus(WidgetWithStatus::Error, tr("Collection does not contain any videos."));
  }
}

bool VideoCollectionEditor::canGenerateApplications() {
  return
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !activeVideos().isEmpty();
}

QString VideoCollectionEditor::generateBundleData() {
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

  foreach (const VideoCollectionVideo &video, activeVideos()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about video.
    QDomElement video_element = source_document.createElement("video");
    QDomElement answer_element = source_document.createElement("answer");
    QDomElement hint_element = source_document.createElement("hint");
    QDomElement image_element = source_document.createElement("image");

    video_element.appendChild(source_document.createTextNode(video.video()));
    answer_element.appendChild(source_document.createTextNode(video.answer()));
    hint_element.appendChild(source_document.createTextNode(video.hint()));

    // Read file with image, convert it to base64 and insert into XML bundle.
    QByteArray picture_encoded = IOFactory::fileToBase64(video.picturePath());

    if (picture_encoded.isEmpty() || picture_encoded.isNull()) {
      return QString();
    }

    image_element.appendChild(source_document.createTextNode(QString::fromUtf8(picture_encoded)));
    item_element.appendChild(video_element);
    item_element.appendChild(answer_element);
    item_element.appendChild(hint_element);
    item_element.appendChild(image_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

bool VideoCollectionEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString video = item.namedItem("video").toElement().text();
      QString answer = item.namedItem("answer").toElement().text();
      QString hint = item.namedItem("hint").toElement().text();
      QString image_data = item.namedItem("image").toElement().text();

      if (video.isEmpty() || answer.isEmpty() || image_data.isEmpty()) {
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
          addVideo(video, answer, hint, target_image_file);
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

QList<VideoCollectionVideo> VideoCollectionEditor::activeVideos() const {
  QList<VideoCollectionVideo> videos;

  for (int i = 0; i < m_ui->m_listVideos->count(); i++) {
    videos.append(m_ui->m_listVideos->item(i)->data(Qt::UserRole).value<VideoCollectionVideo>());
  }

  return videos;
}

QString VideoCollectionEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

QString VideoCollectionEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

void VideoCollectionEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error,
                                 tr("No author is specified."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok,
                                 tr("Author is specified."));
  }
}

void VideoCollectionEditor::checkHint() {
  if (m_ui->m_txtHint->lineEdit()->text().isEmpty()) {
    m_ui->m_txtHint->setStatus(WidgetWithStatus::Warning,
                               tr("Hint is not specified."));
  }
  else {
    m_ui->m_txtHint->setStatus(WidgetWithStatus::Ok,
                               tr("Hint is specified."));
  }
}

void VideoCollectionEditor::checkVideo() {
  if (m_ui->m_txtVideo->lineEdit()->text().isEmpty()) {
    m_ui->m_txtVideo->setStatus(WidgetWithStatus::Warning,
                               tr("Video is not specified."));
  }
  else {
    m_ui->m_txtVideo->setStatus(WidgetWithStatus::Ok,
                               tr("Video is specified."));
  }
}

void VideoCollectionEditor::checkAnswer() {
  if (m_ui->m_txtAnswer->lineEdit()->text().isEmpty()) {
    m_ui->m_txtAnswer->setStatus(WidgetWithStatus::Error,
                                 tr("Answer is not specified."));
  }
  else {
    m_ui->m_txtAnswer->setStatus(WidgetWithStatus::Ok,
                                 tr("Answer is specified."));
  }
}

void VideoCollectionEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error,
                               tr("No collection name is specified."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok,
                               tr("Collection name is specified."));
  }
}

void VideoCollectionEditor::configureUpDown() {
  if (m_ui->m_listVideos->count() > 1) {
    int index = m_ui->m_listVideos->currentRow();

    if (index == 0) {
      m_ui->m_btnVideoUp->setEnabled(false);
      m_ui->m_btnVideoDown->setEnabled(true);
    }
    else if (index == m_ui->m_listVideos->count() - 1) {
      m_ui->m_btnVideoUp->setEnabled(true);
      m_ui->m_btnVideoDown->setEnabled(false);
    }
    else {
      m_ui->m_btnVideoUp->setEnabled(true);
      m_ui->m_btnVideoDown->setEnabled(true);
    }
  }
  else {
    m_ui->m_btnVideoUp->setEnabled(false);
    m_ui->m_btnVideoDown->setEnabled(false);
  }
}

void VideoCollectionEditor::moveVideoUp() {
  int index = m_ui->m_listVideos->currentRow();

  m_ui->m_listVideos->insertItem(index - 1, m_ui->m_listVideos->takeItem(index));
  m_ui->m_listVideos->setCurrentRow(index - 1);

  emit changed();
}

void VideoCollectionEditor::moveVideoDown() {
  int index = m_ui->m_listVideos->currentRow();

  m_ui->m_listVideos->insertItem(index + 1, m_ui->m_listVideos->takeItem(index));
  m_ui->m_listVideos->setCurrentRow(index + 1);

  emit changed();
}

void VideoCollectionEditor::loadPicture(const QString& picture_path) {
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

void VideoCollectionEditor::addVideo(const QString &video,
                                  const QString &answer,
                                  const QString &hint,
                                  const QString &picture_path) {
  int marked_video = m_ui->m_listVideos->currentRow();
  VideoCollectionVideo new_video;
  QListWidgetItem *new_item = new QListWidgetItem();

  new_video.setVideo(video);
  new_video.setHint(hint);
  new_video.setAnswer(answer);
  new_video.setPicturePath(picture_path);

  new_item->setText(new_video.video());
  new_item->setData(Qt::UserRole, QVariant::fromValue(new_video));

  if (m_ui->m_listVideos->count() == 0) {
    // We are adding first video.
    setEditorsEnabled(true);

    m_ui->m_btnVideoRemove->setEnabled(true);

    m_ui->m_listVideos->insertItem(0, new_item);
    m_ui->m_listVideos->setCurrentRow(0);
  }
  else {
    m_ui->m_listVideos->insertItem(marked_video + 1, new_item);
    m_ui->m_listVideos->setCurrentRow(marked_video + 1);
  }

  updateVideoCount();
}

void VideoCollectionEditor::addVideo() {
  addVideo(tr("What animal do you see on the picture?"),
              tr("cat"),
              tr("This animal is hated by dog."),
              APP_TEMPLATES_PATH + QDir::separator() +
              core()->entryPoint()->baseFolder() + QDir::separator() +
              "cat.png");
  launch();
  emit changed();
}

void VideoCollectionEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupVideoEditor->setEnabled(enabled);
}

void VideoCollectionEditor::loadVideo(int index) {
  m_ui->m_txtVideo->blockSignals(true);
  m_ui->m_lblPictureFile->label()->blockSignals(true);

  if (index >= 0) {
    VideoCollectionVideo video = m_ui->m_listVideos->item(index)->data(Qt::UserRole).value<VideoCollectionVideo>();

    m_ui->m_txtVideo->lineEdit()->setText(video.video());
    m_ui->m_txtAnswer->lineEdit()->setText(video.answer());
    m_ui->m_txtHint->lineEdit()->setText(video.hint());
    loadPicture(video.picturePath());

    m_activeVideo = video;
  }
  else {
    m_ui->m_txtVideo->lineEdit()->setText(QString());
    m_ui->m_txtAnswer->lineEdit()->setText(QString());
    m_ui->m_txtHint->lineEdit()->setText(QString());
    loadPicture(QString());
  }

  m_ui->m_txtVideo->blockSignals(false);
  m_ui->m_lblPictureFile->label()->blockSignals(false);

  checkAnswer();
  checkHint();

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

void VideoCollectionEditor::saveVideo() {
  m_activeVideo.setVideo(m_ui->m_txtVideo->lineEdit()->text());
  m_activeVideo.setAnswer(m_ui->m_txtAnswer->lineEdit()->text());
  m_activeVideo.setHint(m_ui->m_txtHint->lineEdit()->text());
  m_activeVideo.setPicturePath(m_ui->m_lblPictureFile->label()->toolTip());

  m_ui->m_listVideos->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeVideo));
  m_ui->m_listVideos->currentItem()->setText(m_activeVideo.video());

  emit changed();
}

void VideoCollectionEditor::removeVideo() {
  int current_row = m_ui->m_listVideos->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listVideos->count() == 1) {
      // We are removing last visible video.
      setEditorsEnabled(false);

      m_ui->m_btnVideoRemove->setEnabled(false);
    }

    delete m_ui->m_listVideos->takeItem(current_row);
  }

  updateVideoCount();
  launch();
  emit changed();
}

void VideoCollectionEditor::onAnswerChanged(const QString& new_answer) {
  Q_UNUSED(new_answer)

  checkAnswer();
  saveVideo();
}

void VideoCollectionEditor::onHintChanged(const QString& new_hint) {
  Q_UNUSED(new_hint)

  checkHint();
  saveVideo();
}

void VideoCollectionEditor::onAuthorChanged(const QString& new_author) {
  Q_UNUSED(new_author)

  checkAuthor();

  launch();
  emit changed();
}

void VideoCollectionEditor::onNameChanged(const QString& new_name) {
  Q_UNUSED(new_name)

  checkName();

  launch();
  emit changed();
}

void VideoCollectionEditor::selectPicture() {
  QString selected_picture = QFileDialog::getOpenFileName(this, tr("Select picture for video"),
                                                          m_ui->m_lblPictureFile->label()->toolTip(),
                                                          tr("Images (*.gif *.jpg *.png)"),
                                                          0);

  if (!selected_picture.isEmpty()) {
    loadPicture(selected_picture);
    saveVideo();
  }
}
