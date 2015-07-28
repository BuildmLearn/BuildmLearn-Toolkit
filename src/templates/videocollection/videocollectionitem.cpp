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

#include "templates/videocollection/videocollectionitem.h"

#include "definitions/definitions.h"


VideoCollectionItem::VideoCollectionItem(QWidget *parent) : QWidget(parent), m_ui(new Ui::VideoCollectionItem) {
  m_ui->setupUi(this);
  
  QFont caption_font = m_ui->m_lblTitle->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADER_SIZE_INCREASE);
  m_ui->m_lblTitle->setFont(caption_font);

  connect(m_ui->m_btnPrevious, SIGNAL(clicked()), this, SIGNAL(previousVideoRequested()));
  connect(m_ui->m_btnList, SIGNAL(clicked()), this, SIGNAL(goToList()));
  connect(m_ui->m_btnNext, SIGNAL(clicked()), this, SIGNAL(nextVideRequested()));
}

VideoCollectionItem::~VideoCollectionItem() {
  delete m_ui;
}

void VideoCollectionItem::setVideo(const VideoCollectionVideo &video, int video_number, int total_videos) {
  m_ui->m_btnPrevious->setEnabled(video_number != 1);
  m_ui->m_lblTitle->setText(video.title());
  //m_ui->m_lblVideoNumber->setText(tr("Video number %1 of %2").arg(QString::number(video_number), QString::number(total_videos)));
}
