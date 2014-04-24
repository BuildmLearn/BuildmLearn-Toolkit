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

#include "gui/widgetwithstatus.h"

#include "gui/plaintoolbutton.h"
#include "miscellaneous/iconfactory.h"

#include <QHBoxLayout>


WidgetWithStatus::WidgetWithStatus(QWidget *parent)
  : QWidget(parent), m_wdgInput(NULL) {
  m_layout = new QHBoxLayout(this);
  m_btnStatus = new PlainToolButton(this);
  m_btnStatus->setFocusPolicy(Qt::NoFocus);

  m_iconInformation = IconFactory::instance()->fromTheme("dialog-information");
  m_iconWarning = IconFactory::instance()->fromTheme("dialog-warning");
  m_iconError = IconFactory::instance()->fromTheme("dialog-error");
  m_iconOk = IconFactory::instance()->fromTheme("dialog-yes");

  // Set layout properties.
  m_layout->setMargin(0);

  setLayout(m_layout);
  setStatus(Information, QString());
}

WidgetWithStatus::~WidgetWithStatus() {
}

void WidgetWithStatus::setStatus(WidgetWithStatus::StatusType status,
                                 const QString &tooltip_text) {
  m_status = status;

  switch (status) {
    case Information:
      m_btnStatus->setIcon(m_iconInformation);
      break;

    case Warning:
      m_btnStatus->setIcon(m_iconWarning);
      break;

    case Error:
      m_btnStatus->setIcon(m_iconError);
      break;

    case Ok:
      m_btnStatus->setIcon(m_iconOk);
      break;

    default:
      break;
  }

  // Setup the tooltip text.
  m_btnStatus->setToolTip(tooltip_text);
}
