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

#include "templates/matchthefollowing/matchfollowingsimulator.h"

#include "core/templatecore.h"
#include "templates/matchthefollowing/matchfollowingeditor.h"
#include "definitions/definitions.h"
#include "miscellaneous/iconfactory.h"
#include <algorithm>


MatchFollowingSimulator::MatchFollowingSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent),
    m_ui(new Ui::MatchFollowingSimulator) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);
  m_ui->m_lblTemplateTitle->setFont(caption_font);
  m_ui->m_lblScore->setFont(caption_font);

  // Setup icons for buttons.
  IconFactory *factory = IconFactory::instance();

  m_ui->m_btnFirstItemUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnFirstItemDown->setIcon(factory->fromTheme("move-down"));
  m_ui->m_btnSecondItemUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnSecondItemDown->setIcon(factory->fromTheme("move-down"));

  // Setup signals and slots.
  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnFirstItemUp, SIGNAL(clicked()), this, SLOT(moveFirstListTopicUp()));
  connect(m_ui->m_btnFirstItemDown, SIGNAL(clicked()), this, SLOT(moveFirstListTopicDown()));
  connect(m_ui->m_btnSecondItemUp, SIGNAL(clicked()), this, SLOT(moveSecondListTopicUp()));
  connect(m_ui->m_btnSecondItemDown, SIGNAL(clicked()), this, SLOT(moveSecondListTopicDown()));
  connect(m_ui->m_btnAnswer, SIGNAL(clicked()), this, SLOT(checkAnswer()));
  connect(m_ui->m_btnTryAgain, SIGNAL(clicked()), this, SLOT(startSimulation()));

  // Setup labels.
  m_ui->m_lblTemplateTitle->setWordWrap(true);
  m_ui->m_lblFirstListTitle->setWordWrap(true);
  m_ui->m_lblSecondListTitle->setWordWrap(true);

}

MatchFollowingSimulator::~MatchFollowingSimulator() {
  qDebug("Destroying MatchFollowingSimulator instance.");

  delete m_ui;
}

bool MatchFollowingSimulator::startSimulation() {
  MatchFollowingEditor *editor = static_cast<MatchFollowingEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active topics or Collection does not
    // contain its name or author name.
    return false;
  }

  // Remove previous data.
  m_ui->m_listFirst->clear();
  m_ui->m_listSecond->clear();

  // Setup the collection and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());
  m_ui->m_flipperTitle->setCurrentIndex(0);
  m_ui->m_flipperAnswer->setCurrentIndex(0);

  // Setup the labels.
  m_ui->m_lblTemplateTitle->setText(editor->m_ui->m_txtTemplateTitle->lineEdit()->text());
  m_ui->m_lblFirstListTitle->setText(editor->m_ui->m_txtFirstListTitle->lineEdit()->text());
  m_ui->m_lblSecondListTitle->setText(editor->m_ui->m_txtSecondListTitle->lineEdit()->text());

  // Enable the user interface.
  m_ui->m_listFirst->setEnabled(true);
  m_ui->m_listSecond->setEnabled(true);
  m_ui->m_btnFirstItemUp->setEnabled(true);
  m_ui->m_btnFirstItemDown->setEnabled(true);
  m_ui->m_btnSecondItemUp->setEnabled(true);
  m_ui->m_btnSecondItemDown->setEnabled(true);

  // Randomize the lists.
  QList<MatchFollowingTopic> topics = editor->activeTopics();
  int max_topics = editor->activeTopics().count();
  QList<int> first_topics_position, second_topics_position;

  for (int i = 0; i < max_topics; ++i) {
  first_topics_position.append(i);
  second_topics_position.append(i);
  }

  std::random_shuffle(first_topics_position.begin(), first_topics_position.end());
  std::random_shuffle(second_topics_position.begin(), second_topics_position.end());

  int i = 0;

  // Load the topics.
  foreach (const MatchFollowingTopic &topic, topics) {
    QListWidgetItem *new_first_topic = new QListWidgetItem();
    new_first_topic->setText(topic.firstListTopic());
    new_first_topic->setData(Qt::UserRole, topic.secondListTopic());
    m_ui->m_listFirst->insertItem(first_topics_position.at(i), new_first_topic);

    QListWidgetItem *new_second_topic = new QListWidgetItem();
    new_second_topic->setText(topic.secondListTopic());
    new_second_topic->setData(Qt::UserRole, topic.secondListTopic());
    m_ui->m_listSecond->insertItem(second_topics_position.at(i), new_second_topic);

    i++;
  }

  // Go to "start" page and begin.
  m_ui->m_phoneWidget->setCurrentIndex(1);
  return true;
}

bool MatchFollowingSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

void MatchFollowingSimulator::start() {
  m_ui->m_phoneWidget->slideInNext();
}

bool MatchFollowingSimulator::goBack() {
  return false;
}

void MatchFollowingSimulator::moveFirstListTopicUp() {
  int index = m_ui->m_listFirst->currentRow();
  if (index == 0) {
    m_ui->m_listFirst->insertItem(m_ui->m_listFirst->count(), m_ui->m_listFirst->takeItem(index));
    m_ui->m_listFirst->insertItem(0, m_ui->m_listFirst->takeItem(m_ui->m_listFirst->count() - 2));
    m_ui->m_listFirst->setCurrentRow(m_ui->m_listFirst->count() - 1);
  }
  else {
    m_ui->m_listFirst->insertItem(index - 1, m_ui->m_listFirst->takeItem(index));
    m_ui->m_listFirst->setCurrentRow(index - 1);
  }
}

void MatchFollowingSimulator::moveFirstListTopicDown() {
  int index = m_ui->m_listFirst->currentRow();
  if (index == m_ui->m_listFirst->count() - 1) {
    m_ui->m_listFirst->insertItem(0, m_ui->m_listFirst->takeItem(index));
    m_ui->m_listFirst->insertItem(m_ui->m_listFirst->count(), m_ui->m_listFirst->takeItem(1));
    m_ui->m_listFirst->setCurrentRow(0);
  }
  else {
    m_ui->m_listFirst->insertItem(index + 1, m_ui->m_listFirst->takeItem(index));
    m_ui->m_listFirst->setCurrentRow(index + 1);
  }
}

void MatchFollowingSimulator::moveSecondListTopicUp() {
  int index = m_ui->m_listSecond->currentRow();
  if (index == 0) {
    m_ui->m_listSecond->insertItem(m_ui->m_listSecond->count(), m_ui->m_listSecond->takeItem(index));
    m_ui->m_listSecond->insertItem(0, m_ui->m_listSecond->takeItem(m_ui->m_listSecond->count() - 2));
    m_ui->m_listSecond->setCurrentRow(m_ui->m_listSecond->count() - 1);
  }
  else {
    m_ui->m_listSecond->insertItem(index - 1, m_ui->m_listSecond->takeItem(index));
    m_ui->m_listSecond->setCurrentRow(index - 1);
  }
}

void MatchFollowingSimulator::moveSecondListTopicDown() {
  int index = m_ui->m_listSecond->currentRow();
  if (index == m_ui->m_listSecond->count() - 1) {
    m_ui->m_listSecond->insertItem(0, m_ui->m_listSecond->takeItem(index));
    m_ui->m_listSecond->insertItem(m_ui->m_listSecond->count(), m_ui->m_listSecond->takeItem(1));
    m_ui->m_listSecond->setCurrentRow(0);
  }
  else {
    m_ui->m_listSecond->insertItem(index + 1, m_ui->m_listSecond->takeItem(index));
    m_ui->m_listSecond->setCurrentRow(index + 1);
  }
}

void MatchFollowingSimulator::checkAnswer() {
  MatchFollowingEditor *editor = static_cast<MatchFollowingEditor*>(core()->editor());
  int max_topics = editor->activeTopics().count(), score = 0;

  for (int i = 0; i < max_topics; ++i) {
  qDebug()<<m_ui->m_listFirst->item(i)->data(Qt::UserRole).toString()<<" , "<<m_ui->m_listSecond->item(i)->data(Qt::UserRole).toString();
    if (m_ui->m_listFirst->item(i)->data(Qt::UserRole).toString() == 
    m_ui->m_listSecond->item(i)->data(Qt::UserRole).toString()) {
      
      score++;
      m_ui->m_listFirst->item(i)->setBackground(QBrush("green"));
      m_ui->m_listSecond->item(i)->setBackground(QBrush("green"));
    }
    else {
      m_ui->m_listFirst->item(i)->setBackground(QBrush("red"));
      m_ui->m_listSecond->item(i)->setBackground(QBrush("red"));
    }
    m_ui->m_flipperTitle->setCurrentIndex(1);
    m_ui->m_lblScore->setText(tr("Score - %1 of %2").arg(QString::number(score),
                                                         QString::number(max_topics)));
    m_ui->m_flipperAnswer->setCurrentIndex(1);
  }
  m_ui->m_listFirst->clearSelection();
  m_ui->m_listSecond->clearSelection();
  m_ui->m_listFirst->setEnabled(false);
  m_ui->m_listSecond->setEnabled(false);
  m_ui->m_btnFirstItemUp->setEnabled(false);
  m_ui->m_btnFirstItemDown->setEnabled(false);
  m_ui->m_btnSecondItemUp->setEnabled(false);
  m_ui->m_btnSecondItemDown->setEnabled(false);
}
