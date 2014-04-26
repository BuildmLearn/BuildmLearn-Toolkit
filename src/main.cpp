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

#include "gui/formmain.h"
#include "definitions/definitions.h"
#include "gui/systemtrayicon.h"
#include "miscellaneous/application.h"
#include "miscellaneous/debugging.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/iconfactory.h"


#include <QThread>
#include <QTranslator>
#include <QDebug>


int main(int argc, char *argv[]) {
  //: Name of language, e.g. English.
  QObject::tr("LANG_NAME");
  //: Abbreviation of language.
  //: Use ISO 639-1 code here combined with ISO 3166-1 (alpha-2) code.
  //: Examples: "cs_CZ", "en_GB", "en_US".
  QObject::tr("LANG_ABBREV");
  //: Name of translator - optional.
  QObject::tr("LANG_AUTHOR");
  //: Email of translator - optional.
  QObject::tr("LANG_EMAIL");

  // Ensure that ini format is used as application settings storage on Mac OS.
#ifdef Q_OS_MAC
  QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

  // Setup debug output system.
#if QT_VERSION >= 0x050000
  qInstallMessageHandler(Debugging::debugHandler);
#else
  qInstallMsgHandler(Debugging::debugHandler);
#endif

  Application application(argc, argv);

  // Add an extra path for non-system icon themes and set current icon theme
  // and skin.
  IconFactory::instance()->setupSearchPaths();
  IconFactory::instance()->loadCurrentIconTheme();

  // These settings needs to be set before any QSettings object.
  Application::setApplicationName(APP_NAME);
  Application::setApplicationVersion(APP_VERSION);
  Application::setOrganizationName(APP_AUTHOR);
  Application::setOrganizationDomain(APP_URL);
  Application::setWindowIcon(QIcon(APP_ICON_PATH));

  qDebug().nospace() << "Creating main application form in thread: \'" <<
                        QThread::currentThreadId() << "\'.";

  FormMain main_form;

  application.setMainForm(&main_form);

  // Set correct information for main window.
  main_form.setWindowTitle(APP_LONG_NAME);

  main_form.show();

  if (SystemTrayIcon::isSystemTrayActivated()) {
    QObject::connect(application.trayIcon(), SIGNAL(triggered(QSystemTrayIcon::ActivationReason)),
                     &main_form, SLOT(switchVisibility()));
    application.trayIcon()->show();
  }

  return Application::exec();
}
