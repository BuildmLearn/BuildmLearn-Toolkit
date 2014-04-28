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
#include "miscellaneous/localization.h"


#include <QThread>
#include <QTranslator>
#include <QDebug>
#include <QTimer>

// TODO: Napad jak na rozhrani s templatama
// kazdej template bude mit dve hlavni vstupni tridy
//
// mejme treba template Flashcard
// da bude mit teda dve hlavni tridy FlashCardEntryPoint (dedi
// z predka TemplateEntryPoint)
// a FlashCardCore (dedi z predka TemplateCore)
// predek TemplateEntryPoint bude mit rohzrani
/*
TemplateEntryPoint {

public
  TemplateCore *getPlainCore(Application *application);
  TemplateCore *loadCoreFromFile(const QString &file_contents,
                                 Application *application);

  QString name(); //treba "template.flashcard"
  QString humanName(); // treba "FlashCard";
  QString author(); // John Doe
  QString version(); // 1.0.1
  QString copyright() // (c) Martin Rotter 2013
  QPixmap thumbnailImage(); // obrazek pro prehled sablon
}
  */
// tedy predek TemplateEntryPoint bude specifikovat
// metadata templatu a navic bude nabizet metodu
// TemplateCore *plainCore(Application *application); ktera
// bude vytvaret skutecny objekt "jadra" sablony -
// ten bude prave obsahovat ty dva widgety (jeden je samotna
// sablona a druhy je widget pro simulator
// - navic TemplateEntryPoint bude definovat metodu
// pro nacteni sablony z projektoveho souboru a ta metoda
// tedy bude taky vracet ukazatel na "jadro", tedy metoda to bude
// loadCoreFromFile (viz vyse)
//
// metody plainCore a loadCoreFromFile berou taky ukazatel
// na aplikaci, aby mely treba pristup do nastaveni atp
//
// trida template core by mohla vypadat takhle
/*
TemplateCore {
public:
  QWidget *editor();
  QWidget *simulator()

  void startSimulator();
  void stopSimulator()

  void saveToProject(const QString &file_name);
  void generateApkFile(const QString &file_name);
  }
*/
// a todle kazda templata reimplementuje
// takze templata si musi zajistit nejspis navazani udalosti
// mezi widgetem editoru a widgetem simulatoru.
//
// co se tyce rozliseni simulatoru, tak to muze bejt problem
// ale mozna to udelat tak ze k simulatoru
// dat combobox s polozkama small, medium, big, tedy
// definovat tri rozliseni simulatoru mozna
// sablona by mohla specifikovat ktera rozliseni (big, medium, small)
// podporuje a podle toho by se odvijel zbytek
// takze by treba TemplateCore mohla mit metodu
//
// QWidget *simulator(Resolution resolution), kde Resuolution
// bude vycet Small, Medium, Large atd atd.

// TODO: cmake uz mam nastavenej module path
// do module path pridat dva soubory
// podle http://www.cmake.org/Wiki/CMake:CPackNSISAdvancedTips
// nejdriv nastavit cpack_generator na nsis a dat make package
// v buildovacim adresari (viz odkaz)
// to vygeneruje Project.nsi a ten dat do resources/cmake
// adresare (prejmenovat na NSIS.template.in)
// spolu s NSIS.InstallOptions.ini.in a nahradit
// ---> LEPSI vzit soubor originalni z cmake, viz nize
//
// vsecko makrama a proměnnejma cmakeovskejma
// dalsi zajimavy soubory
//   c:\CMake\share\cmake-2.8\Modules\CPackNSIS.cmake
//   c:\CMake\share\cmake-2.8\Modules\NSIS.InstallOptions.ini.in
//   c:\CMake\share\cmake-2.8\Modules\NSIS.template.in



/// \mainpage Welcome to documentation!!!
/// The BuildmLearn Toolkit is an easy-to-use
/// program that helps users make mobile apps
/// without any knowledge of application development.
/// The toolkit helps creating mobile application with
/// various functionality and allows teachers to input
/// their custom content. Targeted at teachers, this program
/// helps them make learning fun and engaging through mobile apps.

/// \brief main Main entry point to the application
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

  // Set correct information for main window and show it.
  main_form.setWindowTitle(APP_LONG_NAME);
  main_form.show();

  if (SystemTrayIcon::isSystemTrayActivated()) {
    QObject::connect(application.trayIcon(), SIGNAL(leftMouseClicked()),
                     &main_form, SLOT(switchVisibility()));
    application.trayIcon()->setContextMenu(main_form.trayMenu());
    application.trayIcon()->show();

    QTimer::singleShot(STARTUP_UPDATE_DELAY,
                       &application,
                       SLOT(checkForUpdatesOnBackground()));
  }

  return Application::exec();
}
