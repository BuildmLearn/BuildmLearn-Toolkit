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

#include "gui/formabout.h"

#include "miscellaneous/iconfactory.h"
#include "miscellaneous/textfactory.h"

#include <QFile>
#include <QTextStream>


FormAbout::FormAbout(QWidget *parent) : QDialog(parent), m_ui(new Ui::FormAbout) {
  m_ui->setupUi(this);

  // Set flags and attributes.
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  setWindowIcon(IconFactory::instance()->fromTheme("application-about"));

  //: About toolkit dialog title.
  setWindowTitle(tr("About %1").arg(APP_NAME));

  m_ui->m_lblIcon->setPixmap(QPixmap(APP_ICON_PATH));

  // Load information from embedded text files.
  QTextStream text_stream;
  QFile file;
  text_stream.setDevice(&file);

  file.setFileName(APP_INFO_PATH + "/CHANGELOG");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    m_ui->m_txtChangelog->setText(text_stream.readAll());
    file.close();
  }
  else {
    m_ui->m_txtChangelog->setText(tr("Changelog not found."));
  }

  file.setFileName(APP_INFO_PATH + "/LICENSE");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    m_ui->m_txtLicense->setText(text_stream.readAll());
    file.close();
  }
  else {
    m_ui->m_txtLicense->setText(tr("License not found."));
  }

  // Set other informative texts.
  m_ui->m_lblDesc->setText(tr("<b>%8</b><br>"
                              "<b>Version:</b> %1 (build on %2 with CMake %3)<br>"
                              "<b>Revision:</b> %4<br>"
                              "<b>Build date:</b> %5<br>"
                              "<b>Qt:</b> %6 (compiled against %7)<br>").arg(qApp->applicationVersion(),
                                                                             CMAKE_SYSTEM,
                                                                             CMAKE_VERSION,
                                                                             APP_REVISION,
                                                                             TextFactory::parseDateTime(QString("%1 %2").arg(__DATE__,
                                                                                                                             __TIME__)).toString(Qt::DefaultLocaleShortDate),
                                                                             qVersion(),
                                                                             QT_VERSION_STR,
                                                                             APP_NAME));

  m_ui->m_txtInfo->setText(tr("<body>%4 is an easy-to-use program that helps users make mobile apps without any knowledge of application development."
                              "<br><br>Visit us at <a href=\"%2\">%2</a>."
                              "<br><br>Any feedback or suggestions related to %4 are always welcome. Please write to us at <a href=\"mailto:%1\">%1</a>."
                              "<br><br>Copyright (C) 2012 %3</body>").arg(APP_EMAIL,
                                                                          APP_URL,
                                                                          APP_AUTHOR,
                                                                          APP_NAME));
}

FormAbout::~FormAbout() {
  qDebug("Destroying FormAbout instance.");
  delete m_ui;
}
