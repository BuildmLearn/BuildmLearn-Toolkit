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
#include "miscellaneous/application.h"
#include "miscellaneous/skinfactory.h"


MatchFollowingSimulator::MatchFollowingSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent),
    m_ui(new Ui::MatchFollowingSimulator) {
  m_ui->setupUi(this);

  QString style = "QPushButton{min-height:1.5em; font:1em; margin:0 1px 0 1px; color: white;\
					   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff3232, stop: 1 #e50000);\
					   border-style: outset;border-radius: 3px; border-width: 1px; border-color: #ff0000;}\
					   QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e50000, stop: 1 #ff3232);}";
  
  m_ui->m_btnStart->setStyleSheet(style);
  //connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
}

MatchFollowingSimulator::~MatchFollowingSimulator() {
  qDebug("Destroying MatchFollowingSimulator instance.");

  delete m_ui;
}

bool MatchFollowingSimulator::startSimulation() {
  MatchFollowingEditor *editor = static_cast<MatchFollowingEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active topics or Collection does not
    // containt its name or author name.
    return false;
  }

  return true;
}

bool MatchFollowingSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool MatchFollowingSimulator::goBack() {
  return false;
}
