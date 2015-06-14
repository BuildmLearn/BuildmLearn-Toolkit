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

#include "templates/comprehension/comprehensionsimulator.h"

#include "core/templatecore.h"
#include "templates/comprehension/comprehensioncore.h"
#include "templates/comprehension/comprehensioneditor.h"
#include "templates/comprehension/comprehensionitem.h"
#include "definitions/definitions.h"

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


ComprehensionSimulator::ComprehensionSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::ComprehensionSimulator) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(exit()));
  
}

ComprehensionSimulator::~ComprehensionSimulator() {
  qDebug("Destroying ComprehensionSimulator instance.");

  delete m_ui;
}

bool ComprehensionSimulator::startSimulation() {
  
  return true;
}

bool ComprehensionSimulator::stopSimulation() {
  m_ui->m_phoneWidget->slideInIdx(0);

  emit canGoBackChanged(false);

  return true;
}

bool ComprehensionSimulator::goBack() {
  return false;
}

void ComprehensionSimulator::start() {
  m_ui->m_phoneWidget->slideInIdx(2);
}

void ComprehensionSimulator::prepareSummary() {
  
}

void ComprehensionSimulator::questionSubmitted() {
  int current_index = m_ui->m_phoneWidget->currentIndex();

  if (current_index == m_ui->m_phoneWidget->count() - 2) {
    // This is the last confirmed question. Go to "summary".
    prepareSummary();
  }

  m_ui->m_phoneWidget->slideInIdx(current_index + 1);
}

void ComprehensionSimulator::restart() {
  // Reset all the questions.
  for (int i = 3; i < m_ui->m_phoneWidget->count() - 1; i++) {
    static_cast<ComprehensionItem*>(m_ui->m_phoneWidget->widget(i))->reset();
  }

  m_ui->m_phoneWidget->slideInIdx(1);
}

void ComprehensionSimulator::exit() {
  stopSimulation();
  emit simulationStopRequested();
}

void ComprehensionSimulator::questionStart() {
  m_ui->m_phoneWidget->slideInNext();
}
