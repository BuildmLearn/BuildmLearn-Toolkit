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

#include "templates/mlearning/basicmlearningsimulator.h"

#include "templates/mlearning/basicmlearningeditor.h"
#include "core/templatecore.h"


BasicmLearningSimulator::BasicmLearningSimulator(TemplateCore *core, QWidget *parent) :
  TemplateSimulator(core, parent), m_ui(new Ui::BasicmLearningSimulator) {
  m_ui->setupUi(this);

  connect(m_ui->m_listItems, SIGNAL(itemClicked(QListWidgetItem*)),
          this, SLOT(displayDescription(QListWidgetItem*)));
}

BasicmLearningSimulator::~BasicmLearningSimulator() {
  delete m_ui;
}

bool BasicmLearningSimulator::startSimulation() {
  BasicmLearningEditor *editor = static_cast<BasicmLearningEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active questions or quiz does not
    // containt its name or author name.
    return false;
  }

  // Remove existing items.
  m_ui->m_listItems->clear();

  // Add new items.
  foreach (const BasicmLearningItem &item, editor->activeItems()) {
    QListWidgetItem *list_item = new QListWidgetItem(item.title(), m_ui->m_listItems);
    list_item->setData(Qt::UserRole, QVariant::fromValue(item));
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);

  return true;
}

bool BasicmLearningSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool BasicmLearningSimulator::goBack() {
  if (m_ui->m_phoneWidget->currentIndex() == 2) {
    m_ui->m_phoneWidget->setCurrentIndex(1);
    m_ui->m_listItems->setCurrentRow(-1);

    emit canGoBackChanged(false);

    return true;
  }
  else {
    return false;
  }
}

void BasicmLearningSimulator::displayDescription(QListWidgetItem *list_item) {
  m_ui->m_lblDetails->setText(list_item->data(Qt::UserRole).value<BasicmLearningItem>().description());
  m_ui->m_phoneWidget->setCurrentIndex(2);

  emit canGoBackChanged(true);
}
