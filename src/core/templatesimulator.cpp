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

#include "core/templatesimulator.h"

#include "definitions/definitions.h"
#include "miscellaneous/application.h"
#include "miscellaneous/skinfactory.h"

#include <QTextEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QLayout>


TemplateSimulator::TemplateSimulator(TemplateCore *core, QWidget *parent)
  : QWidget(parent, 0), m_core(core) {
  setStyleSheet(qApp->skinFactory()->currentSkin().m_simulatorStyle);
}

TemplateSimulator::~TemplateSimulator() {
  qDebug("Destroying TemplateSimulator instance.");
}

QSize TemplateSimulator::sizeHint() const {
  return QSize(SIMULATOR_CONTENTS_WIDTH, SIMULATOR_CONTENTS_HEIGHT);
}

void TemplateSimulator::launch() {
  emit canGoBackChanged(false);
}

TemplateCore *TemplateSimulator::core() const {
  return m_core;
}
