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

#include "gui/custommessagebox.h"

#include "miscellaneous/iconfactory.h"
#include "miscellaneous/application.h"

#include <QtGlobal>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QStyle>


CustomMessageBox::CustomMessageBox(QWidget *parent) : QMessageBox(parent) {
}

CustomMessageBox::~CustomMessageBox() {
}

void CustomMessageBox::setIcon(QMessageBox::Icon icon) {
  // Determine correct status icon size.
  int icon_size = qApp->style()->pixelMetric(QStyle::PM_MessageBoxIconSize, 0, this);
  // Setup status icon.
  setIconPixmap(iconForStatus(icon).pixmap(icon_size, icon_size));
}

void CustomMessageBox::iconify(QDialogButtonBox *button_box) {
  foreach (QAbstractButton *button, button_box->buttons()) {
    button->setIcon(iconForRole(button_box->standardButton(button)));
  }
}

QIcon CustomMessageBox::iconForRole(QDialogButtonBox::StandardButton button) {
  switch (button) {
    case QMessageBox::Ok:
      return IconFactory::instance()->fromTheme("dialog-ok");

    case QMessageBox::Cancel:
    case QMessageBox::Close:
      return IconFactory::instance()->fromTheme("dialog-cancel");

    case QMessageBox::Yes:
    case QMessageBox::YesToAll:
      return IconFactory::instance()->fromTheme("dialog-yes");

    case QMessageBox::No:
    case QMessageBox::NoToAll:
      return IconFactory::instance()->fromTheme("dialog-no");

    case QMessageBox::Help:
      return IconFactory::instance()->fromTheme("dialog-question");

    default:
      return QIcon();
  }
}

QIcon CustomMessageBox::iconForStatus(QMessageBox::Icon status) {
  switch (status) {
    case QMessageBox::Information:
      return IconFactory::instance()->fromTheme("dialog-information");

    case QMessageBox::Warning:
      return IconFactory::instance()->fromTheme("dialog-warning");

    case QMessageBox::Critical:
      return IconFactory::instance()->fromTheme("dialog-error");

    case QMessageBox::Question:
      return IconFactory::instance()->fromTheme("dialog-question");

    case QMessageBox::NoIcon:
    default:
      return QIcon();
  }
}

QMessageBox::StandardButton CustomMessageBox::show(QWidget *parent,
                                             QMessageBox::Icon icon,
                                             const QString &title,
                                             const QString &text,
                                             const QString &informative_text,
                                             const QString &detailed_text,
                                             QMessageBox::StandardButtons buttons,
                                             QMessageBox::StandardButton default_button) {
  // Create and find needed components.
  CustomMessageBox msg_box(parent);

  // Initialize message box properties.
  msg_box.setWindowTitle(title);
  msg_box.setText(text);
  msg_box.setInformativeText(informative_text);
  msg_box.setDetailedText(detailed_text);
  msg_box.setIcon(icon);
  msg_box.setStandardButtons(buttons);
  msg_box.setDefaultButton(default_button);

  // Setup button box icons.
#if defined(Q_OS_OS2)
  QDialogButtonBox *button_box = msg_box.findChild<QDialogButtonBox*>();
  iconify(button_box);
#endif

  // Display it.
  if (msg_box.exec() == -1) {
    return QMessageBox::Cancel;
  }
  else {
    return msg_box.standardButton(msg_box.clickedButton());
  }
}
