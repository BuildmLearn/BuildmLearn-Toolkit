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
#include "miscellaneous/skinfactory.h"
#include "miscellaneous/localization.h"
#include "dynamic-shortcuts/dynamicshortcuts.h"


#include <QThread>
#include <QTranslator>
#include <QDebug>
#include <QTimer>


/// \mainpage Welcome to documentation!
/// The BuildmLearn Toolkit is an easy-to-use
/// program that helps users make mobile apps
/// without any knowledge of application development.
/// The toolkit helps creating mobile application with
/// various functionality and allows teachers to input
/// their custom content. Targeted at teachers, this program
/// helps them make learning fun and engaging through mobile apps.
///
///
/// Links
/// -----
/// * [www.buildmlearn.org](http://buildmlearn.org/)  ~homepage,
/// * [www.buildmlearn.github.io/BuildmLearn-Toolkit/docs/](http://buildmlearn.github.io/BuildmLearn-Toolkit/docs/)  ~API documentation,
/// * [www.martin-rotter.8u.cz](http://www.martin-rotter.8u.cz/)  ~author's homepage,
/// * [www.transifex.com/projects/p/buildmlearn-toolkit](https://www.transifex.com/projects/p/buildmlearn-toolkit/)  ~translations,
/// * [www.build.opensuse.org/project/show/home:skunkos:buildmlearn] (https://build.opensuse.org/project/show/home:skunkos:buildmlearn)  ~OBS homepage,
/// * [www.cmake.org](http://www.cmake.org/)  ~build system,
/// * [www.qt-project.org](http://qt-project.org/)  ~Qt libraries.
///
/// Packages
/// --------
/// You can use source code tarball available direct from here to build the software. Precompiled binary packages are available for some other platforms:
///
/// * [OBS (Git version)](http://software.opensuse.org/download.html?project=home%3Askunkos%3Abuildmlearn&package=buildmlearn-toolkit-git)  ~Archlinux, openSUSE, Fedora, *Ubuntu, Debian,
/// * [OBS (Stable version)](http://software.opensuse.org/download.html?project=home%3Askunkos%3Abuildmlearn&package=buildmlearn-toolkit)  ~Archlinux, openSUSE, Fedora, *Ubuntu, Debian,
/// * [testing NSIS installers](https://drive.google.com/folderview?id=0B8XNkQ-jUoBYYjMzd3laRHROMnM&usp=drive_web)  ~Windows (XP or newer),
/// * TBA  ~OS/2 (eComStation),
/// * TBA  ~OSX (Mac OS X).
///
/// How to build
/// ------------
/// Information regarding build process can be found in CMakeLists.txt file.
///
/// License for use and distribution
/// ---------------------------------
/// All the code in this repository (unless specified otherwise) is governed by the BSD (3-Clause) License quoted below.
///
/// Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
/// * Redistributions of source code must retain the above copyright notice, this
///   list of conditions and the following disclaimer.
///
/// * Redistributions in binary form must reproduce the above copyright notice,
///   this list of conditions and the following disclaimer in the documentation
///   and/or other materials provided with the distribution.
///
/// * Neither the name of the BuildmLearn nor the names of its
///   contributors may be used to endorse or promote products derived from
///   this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
/// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
/// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/// \defgroup template-interfaces Template interfaces
/// \brief Base template interface classes.
///
/// Template interfaces module contains all base classes which are
/// inherited by concrete templates.
///
/// \defgroup keyboard-shortcuts Dynamic keyboard shortcuts
/// \brief Dynamic keyboard shortcuts classes.
///
/// Dynamic keyboard shortcuts module contains classes related to
/// application-wide dynamic keyboard shortcuts facilities.
///
/// \defgroup template-quiz Quiz template
/// \brief Quiz template classes.
///
/// This module contains all classes related to Quiz template.
///
/// \defgroup template-flashcards Flashcards template
/// \brief Flashcards template classes.
///
/// This module contains all classes related to Flashcards template.
///
/// \defgroup template-basicmlearn Basic m-learning template
/// \brief Basic m-learning template classes.
///
/// This module contains all classes related to Basic m-learning template.
///
/// \defgroup template-learnspellings Learn Spellings template
/// \brief Learn Spellings template classes.
///
/// This module contains all classes related to Learn Spellings template.
/// Learn Spellings template helps its users to learn to pronunciate particular
/// words or phrases.

/// \brief main Main entry point to the application.
///
/// Main function is the "main" entry point to toolkit.
///
/// \param argc Number of arguments passed to the program.
/// \param argv Array of strings passed to the program.
/// \return Function returns EXIT_SUCCESS when it succeedes
/// or another integer value when it fails.
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

  // Load current skin.
  application.skinFactory()->loadCurrentSkin();

  // Load localization and setup locale before any widget is constructed.
  Localization::instance()->load();

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

  // Load keyboard shortcuts.
  DynamicShortcuts::load(application.availableActions());

  main_form.show();

  if (SystemTrayIcon::isSystemTrayAvailable()) {
    QObject::connect(application.trayIcon(), SIGNAL(leftMouseClicked()),
                     &main_form, SLOT(switchVisibility()));
    application.trayIcon()->setContextMenu(main_form.trayMenu());
    application.trayIcon()->show();

    QTimer::singleShot(STARTUP_UPDATE_DELAY, &application,
                       SLOT(checkForUpdatesOnBackground()));
  }
  else {
    qDebug("System tray icon is not available, quitting.");
    return EXIT_FAILURE;
  }

  // Check for availability of external generators.
  application.recheckExternalApplications(true);

  return Application::exec();
}
