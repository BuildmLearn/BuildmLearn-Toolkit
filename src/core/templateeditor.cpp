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

#include "core/templateeditor.h"

#include "core/templatecore.h"


TemplateEditor::TemplateEditor(TemplateCore *core, QWidget *parent)
  : QWidget(parent), m_canGenerate(false), m_generateMessage(QString()), m_isDirty(false), m_core(core) {
  connect(this, SIGNAL(changed()), this, SLOT(dirtify()));
}

TemplateEditor::~TemplateEditor() {
  qDebug("Destroying TemplateEditor instance.");
}

void TemplateEditor::launch() {
  if (canGenerateApplications()) {
    issueNewGenereationStatus(true);
  }
  else {
    issueNewGenereationStatus(false,
                              tr("Simulation or mobile application generation cannot be started \n"
                                 "because editor does not contain enough data."));
  }
}

TemplateCore *TemplateEditor::core() const {
  return m_core;
}

bool TemplateEditor::isDirty() const {
  return m_isDirty;
}

void TemplateEditor::setIsDirty(bool is_dirty) {
  m_isDirty = is_dirty;
}

void TemplateEditor::issueNewGenereationStatus(bool can_generate, const QString &message) {
  m_canGenerate = can_generate;
  m_generateMessage = message;

  emit canGenerateChanged(can_generate, message);
}
