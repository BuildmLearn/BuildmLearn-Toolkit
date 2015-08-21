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

#include "templates/videocollection/videocollectionsimulator.h"

#include "core/templatecore.h"
#include "templates/videocollection/videocollectioneditor.h"
#include "templates/videocollection/videocollectionitem.h"
#include "definitions/definitions.h"


VideoCollectionSimulator::VideoCollectionSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent),
  m_ui(new Ui::VideoCollectionSimulator) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);
  m_ui->m_lblSelect->setFont(caption_font);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_listVideos, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(loadVideo()));
}

VideoCollectionSimulator::~VideoCollectionSimulator() {
  qDebug("Destroying VideoCollectionSimulator instance.");

  delete m_ui;
}

bool VideoCollectionSimulator::startSimulation() {
  VideoCollectionEditor *editor = static_cast<VideoCollectionEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active videos or collection does not
    // containt its name or author name.
    return false;
  }

  // Remove existing videos.
  m_ui->m_listVideos->clear();
  while (m_ui->m_phoneWidget->count() > 4) {
    QWidget *video_widget = m_ui->m_phoneWidget->widget(3);

    m_ui->m_phoneWidget->removeWidget(video_widget);
    video_widget->deleteLater();
  }

  // Load the videos, setup the collection and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

  int video_number = 1;
  QList<VideoCollectionVideo> videos = editor->activeVideos();
  
  foreach (const VideoCollectionVideo &video, videos) {
    VideoCollectionItem *item = new VideoCollectionItem(m_ui->m_phoneWidget);

    connect(item, SIGNAL(nextVideoRequested()), this, SLOT(moveToNextVideo()));
    connect(item, SIGNAL(goToList()), this, SLOT(goToList()));
    connect(item, SIGNAL(previousVideoRequested()), this, SLOT(moveToPreviousVideo()));

    item->setVideo(video, video_number);
    m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, item);
    
    QListWidgetItem *new_item = new QListWidgetItem();
    new_item->setText(video.title() + "\n" + video.description());
    new_item->setIcon(QIcon(video.thumbnailPath()));
    m_ui->m_listVideos->insertItem(video_number-1, new_item);
  
    video_number++;
  }

  // Go to "start" page and begin.
  m_ui->m_phoneWidget->setCurrentIndex(1);
  return true;
}

bool VideoCollectionSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool VideoCollectionSimulator::goBack() {
  return false;
}

void VideoCollectionSimulator::start() {
  moveToNextVideo();
}

void VideoCollectionSimulator::restart() {
  m_ui->m_phoneWidget->setCurrentIndex(1);
}

void VideoCollectionSimulator::loadVideo() {
  int index = m_ui->m_listVideos->currentRow();
  m_ui->m_phoneWidget->setCurrentIndex(m_ui->m_phoneWidget->currentIndex() + index + 1);
}

void VideoCollectionSimulator::moveToNextVideo() {
  m_ui->m_phoneWidget->setCurrentIndex(m_ui->m_phoneWidget->currentIndex() + 1);
}

void VideoCollectionSimulator::moveToPreviousVideo() {
  m_ui->m_phoneWidget->setCurrentIndex(m_ui->m_phoneWidget->currentIndex() - 1);
}

void VideoCollectionSimulator::goToList() {
  m_ui->m_phoneWidget->setCurrentIndex(2);
}
