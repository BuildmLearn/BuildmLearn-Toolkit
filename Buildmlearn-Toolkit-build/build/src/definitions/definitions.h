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


#ifndef DEFS_H
#define DEFS_H

#include <QtGlobal>

// General constants.
#define CMAKE_VERSION       "2.8.12.2"
#define CMAKE_SYSTEM        "Windows-6.2"

#define APP_NAME            "BuildmLearn Toolkit"
#define APP_LOW_NAME        "buildmlearn-toolkit"
#define APP_LOW_H_NAME      ".buildmlearn-toolkit"
#define APP_LONG_NAME       "BuildmLearn Toolkit 2.0.4 pre-alpha"
#define APP_AUTHOR          "BuildmLearn Contributors"
#define APP_EMAIL           "buildmlearn@gmail.com"
#define APP_URL             "http://buildmlearn.org/"
#define APP_URL_ISSUES      "https://github.com/BuildmLearn/BuildmLearn-Toolkit/issues"
#define APP_URL_ISSUES_NEW  "https://github.com/BuildmLearn/BuildmLearn-Toolkit/issues/new"
#define APP_URL_DOWNLOADS   "http://buildmlearn.org/download"
#define APP_VERSION         "2.0.4"
#define APP_REVISION        "79bcdb4"
#define APP_USERAGENT       QString("BuildmLearn Toolkit/2.0.4 (http://buildmlearn.org/) on Windows-6.2")

#define EXIT_STATUS_NOT_STARTED         -2
#define EXIT_STATUS_CRASH               -1
#define EXIT_STATUS_ZIP_NORMAL          0
#define EXIT_STATUS_JAVA_NORMAL         0
#define EXIT_STATUS_SIGNAPK_NORMAL      2
#define EXIT_STATUS_SIGNAPK_NOT_FOUND   1
#define EXIT_STATUS_SIGNAPK_WORKING     0

#define RELEASES_LIST                   "https://raw.githubusercontent.com/BuildmLearn/BuildmLearn-Toolkit/portage/resources/text/UPDATES"
#define DEFAULT_LOCALE                  "en_GB"
#define USER_AGENT_HTTP_HEADER          "User-Agent"
#define ICON_SIZE_SETTINGS              16
#define TRAY_ICON_BUBBLE_TIMEOUT        30000
#define CLOSE_LOCK_TIMEOUT              3000
#define DOWNLOAD_TIMEOUT                5000
#define ELLIPSIS_LENGTH                 3
#define STARTUP_UPDATE_DELAY            40000
#define TRAY_ICON_DELAY                 1000
#define CERTIFICATE_PATH                "certificate.pem"
#define KEY_PATH                        "key.pk8"
//#define TTS_SERVICE_URL                 "http://translate.google.com/translate_tts?tl=en&q=%1"
#define TTS_SERVICE_URL                 "http://mary.dfki.de:59125/process?INPUT_TEXT=%1&INPUT_TYPE=TEXT&OUTPUT_TYPE=AUDIO&AUDIO=WAVE_FILE&LOCALE=en_US"

#define STORE_API_KEY                   "BuildmLearnToolkit"
#define STORE_ENDPOINT                  "http://croozeus.com/buildmlearn/api/v1/storeAPI.php"
#define STORE_ANSWER_SUCCESS            "success"
#define STORE_ANSWER_NO_PARAMETERS      "missing_parameters"
#define STORE_ANSWER_INVALID_KEY        "invalid_key"

#define XML_BUNDLE_ROOT_DATA_ELEMENT    "data"
#define XML_BUNDLE_INDENTATION          2

// Line delimiters.
#define DELIMITER_LINE                  "##L##"
#define DELIMITER_INLINE                "##IL##"

// Simulator dimensions -> it supports single fixed size.
#define SIMULATOR_WIDTH           327
#define SIMULATOR_HEIGHT_MAX      10000
#define SIMULATOR_HEIGHT_MIN      150
#define SIMULATOR_HEIGHT_DEFAULT  639
#define SIMULATOR_WIDTH_OFFSET    50
#define SIMULATOR_OFFSET          16

#define SIMULATOR_CONTENTS_OFFSET_X   30
#define SIMULATOR_CONTENTS_OFFSET_Y   95
#define SIMULATOR_CONTENTS_WIDTH      270
#define SIMULATOR_CONTENTS_HEIGHT     447

#define SIMULATOR_HEADER_SIZE_INCREASE    2
#define SIMULATOR_HEADING_SIZE_INCREASE   2

// Config constants.
#define APP_CFG_PATH        "config"
#define APP_CFG_FILE        "config.ini"
#define APP_CFG_GUI         "gui"
#define APP_CFG_GEN         "main"
#define APP_CFG_PROXY       "proxy"
#define APP_CFG_SHORTCUTS   "keyboard"
#define APP_CFG_BROWSER     "browser"
#define APP_CFG_APK_GEN     "apk_generation"
#define APP_CFG_SIMULATOR   "simulator"
#define APP_CFG_TEMPLATES   "templates"

#if defined(Q_OS_OSX) || defined(Q_WS_MAC)
#define APP_PREFIX  QApplication::applicationDirPath() + "/../Resources"
#else
#define APP_PREFIX  "C:/Program Files (x86)/buildmlearn-toolkit"
#endif

// Themes & signalling constants.
#define APP_QUIT_INSTANCE   "app_quit"
#define APP_IS_RUNNING      "app_is_running"
#define APP_SKIN_DEFAULT    "base/greeen.xml"
#define APP_THEME_DEFAULT   "mini-kfaenza"
#define APP_NO_THEME        "-"
#define APP_THEME_SUFFIX    ".png"

#if defined(Q_OS_LINUX)
#define OS_ID   "Linux"
#elif defined(Q_OS_OSX) || defined(Q_WS_MAC)
#define OS_ID   "Mac OS X"
#elif defined(Q_OS_WIN)
#define OS_ID   "Windows"
#elif defined(Q_OS_OS2)
#define OS_ID   "OS2"
#else
#define OS_ID   ""
#endif

// System-dependent constants.
#if defined(Q_OS_LINUX)
#define APP_LANG_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/l10n")
#define APP_SKIN_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/skins")
#define APP_INFO_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/information")
#define APP_APK_ICON_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/app_icons")
#define APP_THEME_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/icons")
#define APP_MISC_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/misc")
#define APP_TEMPLATES_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/templates")
#define APP_ICON_PATH APP_PREFIX + QString("/share/pixmaps/buildmlearn-toolkit.png")
#define APP_SIGNAPK_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/binaries/signapk/signapk.jar")
#define APP_CERT_PATH APP_PREFIX + QString("/share/buildmlearn-toolkit/certificates")
#define APP_ZIP_PATH "/usr/bin/zip"
#define APP_JAVA_PATH "/usr/bin/java"
#elif defined(Q_OS_OSX) || defined(Q_WS_MAC)
#define APP_LANG_PATH APP_PREFIX + QString("/l10n")
#define APP_SKIN_PATH APP_PREFIX + QString("/skins")
#define APP_INFO_PATH APP_PREFIX + QString("/information")
#define APP_APK_ICON_PATH APP_PREFIX + QString("/app_icons")
#define APP_THEME_PATH APP_PREFIX + QString("/icons")
#define APP_MISC_PATH APP_PREFIX + QString("/misc")
#define APP_TEMPLATES_PATH APP_PREFIX + QString("/templates")
#define APP_ICON_PATH APP_PREFIX + QString("/buildmlearn-toolkit.png")
#define APP_SIGNAPK_PATH APP_PREFIX + QString("/binaries/signapk/signapk.jar")
#define APP_CERT_PATH APP_PREFIX + QString("/certificates")
#define APP_ZIP_PATH "/usr/bin/zip"
#define APP_JAVA_PATH "/usr/bin/java"
#elif defined(Q_OS_WIN) || defined(Q_OS_OS2)
#define APP_LANG_PATH QApplication::applicationDirPath() + QString("/l10n")
#define APP_SKIN_PATH QApplication::applicationDirPath() + QString("/skins")
#define APP_INFO_PATH QApplication::applicationDirPath()
#define APP_APK_ICON_PATH QApplication::applicationDirPath() + QString("/app_icons")
#define APP_THEME_PATH QApplication::applicationDirPath() + QString("/icons")
#define APP_MISC_PATH QApplication::applicationDirPath() + QString("/misc")
#define APP_TEMPLATES_PATH QApplication::applicationDirPath() + QString("/templates")
#define APP_ICON_PATH QApplication::applicationDirPath() + QString("/buildmlearn-toolkit.png")
#define APP_SIGNAPK_PATH QApplication::applicationDirPath() + QString("/binaries/signapk/signapk.jar")
#define APP_CERT_PATH QApplication::applicationDirPath() + QString("/certificates")
#define APP_ZIP_PATH QApplication::applicationDirPath() + QString("/binaries/zip/zip.exe")
#define APP_JAVA_PATH "java.exe"
#endif

#endif // DEFS_H
