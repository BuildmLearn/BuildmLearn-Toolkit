########################################################################################
#
# Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# 
# * Neither the name of the BuildmLearn nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
########################################################################################
#
# BuildmLearn Toolkit compilation script for CMake.
#
# Build process (navigate to root source folder first):
#   a) Windows RELEASE build.
#     mkdir build && cd build
#     cmake ../ -DCMAKE_BUILD_TYPE="release" -DCMAKE_INSTALL_PREFIX="C:\Program Files\BuildmLearn Toolkit" -DUSE_QT_5="ON"
#     nmake (or mingw32-make if you use MinGW compiler)
#     nmake install (or mingw32-make if you use MinGW compiler)
#
#   b) Linux RELEASE build.
#     mkdir build && cd build
#     cmake ../ -DCMAKE_BUILD_TYPE="release" -DCMAKE_INSTALL_PREFIX=/usr -DUSE_QT_5="ON"
#     make
#     make install
#
#   c) Mac OS X RELEASE build.
#     mkdir build && cd build
#     cmake ../ -DCMAKE_BUILD_TYPE="release" -DCMAKE_INSTALL_PREFIX="./install -DCMAKE_INSTALL_PREFIX=/usr -DUSE_QT_5="ON"
#     make
#     make install
#     cd install
#     macdeployqt "buildmlearn-toolkit.app" -dmg
#
#   d) Windows DEBUG build.
#     mkdir build && cd build
#     cmake ../ -DCMAKE_BUILD_TYPE="debug" -DCMAKE_INSTALL_PREFIX="./install" -DUSE_QT_5="ON"
#     nmake (or mingw32-make if you use MinGW compiler)
#     nmake install (or mingw32-make if you use MinGW compiler)
#     
#     Now it is done. You now need to copy all files contained in "build\install" subfolder and copy it into "build" folder.
#   
#
# Refreshing translations:
#   make lupdate
#
# Generating source tarballs:
#   make dist or make package_source
#
# Generating binary tarballs (or NSIS packages):
#   make package (For more see -DUSE_NSIS argument description.)
#   cpack -G PACKAGE_TYPE (for example cpack -G NSIS or cpack -G ZIP)
#
# Arguments:
#   "-DCMAKE_INSTALL_PREFIX"
#     Installation path, replace with something like "C:\buildmlearn-toolkit" on Windows.
#
#   "-DUSE_QT_5"
#     Specifies which major Qt version to use. Qt 4 and Qt 5 are supported.
#     If "OFF" is passed as an argument, then Qt 4 is used. Default is "OFF".
#
#   "-DBUNDLE_ICON_THEMES"
#     If "ON", then custom icons theme(s) will be bundled with application
#     installation. If "OFF", then no icon theme(s) will be available for
#     the application and application will run in iconless mode.
#     Default and recommended value is "ON".
#
#   "-DINSTALL_ALL_LANGUAGES"
#     If "ON", then all available localizations are installed.
#     If "OFF", then only basic set of localizations is installed.
#
#   "-DUSE_NSIS"
#     If "ON", then NSIS generator is used instead of ZIP generator.
#     If "OFF", then default ZIP generator is used.
#
#   "-DDISABLE_STORE"
#     Enables or disables BuildmLearn Store.
#
#   "-DDISABLE_APK_GENERATION"
#     Enables or disables APK generation.
#
# Tip for developers: When you COMPILE BuildmLearn Toolkit, you also need to run "make install" ("mingw32-make install" if you use MinGW) to "install
# the software to some folder. Then you need to take installed files (without root folder) and copy it to your build directory. Detailed steps are these:
#   a) Compile the program and use this CMake call 
#
# Other information:
#   - supports Windows, Linux, OS/2 (eComStation),
#   - Qt 4.7.3 and higher is required,
#   - resource compiler (windres.exe) is needed on MinGW,
#   - only Qt 5.x.x is supported on Mac OS X,
#   - resource compiler (rc.exe) is needed on OS/2.
#
# Authors and contributors:
#   - BuildmLearn Contributors listed at http://buildmlearn.org/people/,
#   - Petr Vaněk (for Mac OS X-related stuff).
#
########################################################################################

# Setup basic variables.
project(buildmlearn-toolkit)

set(APP_NAME "BuildmLearn Toolkit")
set(APP_LOW_NAME "buildmlearn-toolkit")
set(APP_VERSION "2.0.4")
set(FILE_VERSION "2,0,4,0")
set(APP_COMPANY "BuildmLearn")
set(APP_AUTHOR "BuildmLearn Contributors")
set(APP_URL "http://buildmlearn.org/")
set(APP_URL_ISSUES "https://github.com/BuildmLearn/BuildmLearn-Toolkit/issues")
set(APP_URL_ISSUES_NEW "https://github.com/BuildmLearn/BuildmLearn-Toolkit/issues/new")
set(APP_URL_DOWNLOADS "http://buildmlearn.org/download")
set(APP_EMAIL "buildmlearn@gmail.com")
set(APP_BRIEF "BuildmLearn Toolkit is an easy-to-use program that helps users make mobile apps without any knowledge of application development.")
set(MINIMUM_QT_VERSION 4.7.3)
set(EXE_NAME ${APP_LOW_NAME})

if(APPLE)
  set(APP_URL_BACKWARDS "org.buildmlearn.toolkit")
endif(APPLE)

# Options declaration.
option(USE_QT_5 "Use Qt 5 for building" OFF)
option(BUNDLE_ICON_THEMES "Equip installation with custom icon themes" ON)
option(INSTALL_ALL_LANGUAGES "Install all available localizations" ON)
option(DISABLE_STORE "Disable BuildmLearn Store features" OFF)
option(DISABLE_APK_GENERATION "Disable APK generation" OFF)

if(DISABLE_STORE)
  add_definitions(-DDISABLE_STORE)
endif(DISABLE_STORE)

if(DISABLE_STORE)
  add_definitions(-DDISABLE_APK_GENERATION)
endif(DISABLE_STORE)

if(WIN32)
  option(USE_NSIS "Use NSIS generator to produce installer" OFF)
endif(WIN32)

if(APPLE AND NOT USE_QT_5)
  message(FATAL_ERROR "[${APP_LOW_NAME}] Only Qt 5.x.x is supported on Mac OS X")
endif(APPLE AND NOT USE_QT_5)

message(STATUS "")
message(STATUS "[${APP_LOW_NAME}] ==== Options summary ====")
message(STATUS "[${APP_LOW_NAME}] Use Qt 5 for building -> ${USE_QT_5}")
message(STATUS "[${APP_LOW_NAME}] Equip installation with custom icon themes -> ${BUNDLE_ICON_THEMES}")
message(STATUS "[${APP_LOW_NAME}] Install all available localizations -> ${INSTALL_ALL_LANGUAGES}")
message(STATUS "[${APP_LOW_NAME}] Disable BuildmLearn Store features -> ${DISABLE_STORE}")
message(STATUS "[${APP_LOW_NAME}] Disable APK generation -> ${DISABLE_APK_GENERATION}")

if(WIN32)
  message(STATUS "[${APP_LOW_NAME}] Use NSIS generator to produce installer -> ${USE_NSIS}")
endif(WIN32)

message(STATUS "[${APP_LOW_NAME}] ==== Options summary ====")
message(STATUS "")

if(POLICY CMP0012)
  cmake_policy(SET CMP0012 NEW)
endif()

if(${USE_QT_5})
  cmake_minimum_required(VERSION 2.8.10)
else(${USE_QT_5})
  cmake_minimum_required(VERSION 2.8.0)
endif(${USE_QT_5})

message(STATUS "[${APP_LOW_NAME}] Welcome to ${APP_NAME} compilation process.")
message(STATUS "[${APP_LOW_NAME}] Compilation process begins right now.")

if(BUNDLE_ICON_THEMES)
  message(STATUS "[${APP_LOW_NAME}] Custom icon themes will be installed.")
else(BUNDLE_ICON_THEMES)
  message(STATUS "[${APP_LOW_NAME}] Custom icon themes will NOT be installed.")
endif(BUNDLE_ICON_THEMES)

# Setup misc options.
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/resources/nsis
  ${CMAKE_MODULE_PATH})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Eliminate a warning when building in Windows that relates
# to static linking of Qt executables to qtmain.lib.
# This policy was introduced in CMake version 2.8.11.
# CMake version 2.8.11.2 warns when the policy is not set
# and uses OLD behavior.
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

# Select which Qt version to use.
if(${USE_QT_5})
  message(STATUS "[${APP_LOW_NAME}] Using Qt 5 library for building.")
  
  # Instruct CMake to run moc automatically when needed.
  set(CMAKE_AUTOMOC ON)
else(${USE_QT_5})
  message(STATUS "[${APP_LOW_NAME}] Using Qt 4 library for building.")
endif(${USE_QT_5})

# Obtain revision number if available.
message(STATUS "[${APP_LOW_NAME}] Obtaining revision number.")

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
  find_package(Git)
  if(GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_REVISION
    )
    string(REGEX REPLACE "\n" "" GIT_REVISION "${GIT_REVISION}")
    set(APP_REVISION ${GIT_REVISION})
  else(GIT_FOUND)
    set(APP_REVISION -)
  endif(GIT_FOUND)
else(EXISTS "${PROJECT_SOURCE_DIR}/.git")
  set(APP_REVISION -)
endif(EXISTS "${PROJECT_SOURCE_DIR}/.git")

message(STATUS "[${APP_LOW_NAME}] Resolved revision number: " ${APP_REVISION} ".")

# Configure desktop entry for Linux.
if(UNIX)
  message(STATUS "[${APP_LOW_NAME}] Generating desktop entry for Linux.")
  configure_file (
    ${PROJECT_SOURCE_DIR}/resources/desktop/${APP_LOW_NAME}.desktop.in
    ${CMAKE_CURRENT_BINARY_DIR}/resources/desktop/${APP_LOW_NAME}.desktop
  )
  set(DESKTOP_ENTRY_PATH ${CMAKE_INSTALL_PREFIX}/share/applications)
endif(UNIX)

# Configure internal C++ defines.
configure_file (
  ${PROJECT_SOURCE_DIR}/src/definitions/definitions.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/definitions/definitions.h
)

# Configure Doxygen documentation file.
configure_file (
  ${PROJECT_SOURCE_DIR}/resources/documentation/Doxyfile.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources/documentation/Doxyfile
)

# Define some useful DEBUG for, ehrm, debug build.
if(CMAKE_BUILD_TYPE STREQUAL "release" OR CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  message(STATUS "[${APP_LOW_NAME}] A release build (non-debug) is chosen. Debugging outputs are silently ignored.")
  set(CMAKE_BUILD_TYPE MinSizeRel)
  message(STATUS "[${APP_LOW_NAME}] Output executable file is optimized for minimum size.")
else(CMAKE_BUILD_TYPE STREQUAL "release" OR CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  message(STATUS "[${APP_LOW_NAME}] A debug build is chosen.")
  add_definitions(-DDEBUG)
  set(CMAKE_BUILD_TYPE Debug)

# Enable compiler warnings.
# See http://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
message(STATUS "[${APP_LOW_NAME}] Enabling verbose makefile and full warning reports.")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-pedantic -Wall -Wextra)
elseif(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
  #add_definitions(/W3)
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

# Verbose compiling outputs.
set(CMAKE_VERBOSE_MAKEFILE ON)

endif(CMAKE_BUILD_TYPE STREQUAL "release" OR CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RELEASE")

# Force Qt to use string builders.
add_definitions(-DQT_USE_QSTRINGBUILDER)

# Unicode settings.
add_definitions(-DUNICODE -D_UNICODE)

if(${USE_QT_5})
  # Check for C++ 11 features availability.
  # See http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
  if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(
      COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION
    )

    if(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
      message(FATAL_ERROR "[${APP_LOW_NAME}] Your C++ compiler does not support C++ 11.")
    else(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
      add_definitions(-std=c++11)
    endif(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))

  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    add_definitions(-std=c++11 -stdlib=libc++)
  elseif(${MSVC_VERSION} VERSION_LESS 1600)
    message(FATAL_ERROR "[${APP_LOW_NAME}] Your C++ compiler does not support C++ 11.")
  endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
endif(${USE_QT_5})

# Setup libraries.
if(${USE_QT_5})
  find_package(Qt5 REQUIRED Sql Widgets Xml XmlPatterns Network LinguistTools Multimedia)
else(${USE_QT_5})
  set(QT_MIN_VERSION ${MINIMUM_QT_VERSION})
  set(QT_USE_PHONON TRUE)
  if(OS2)
    find_package(Qt4 REQUIRED QtCore QtGui QtSql QtNetwork QtXml QtXmlPatterns)
  else(OS2)
    find_package(Qt4 REQUIRED QtCore QtGui QtSql QtNetwork QtXml QtXmlPatterns Phonon)
  endif(OS2)
  include(${QT_USE_FILE})
endif(${USE_QT_5})

# Configure QStringBuilder behavior.
if(${USE_QT_5})
  message(STATUS "[${APP_LOW_NAME}] Enabling fast QString concatenation.")

  add_definitions(-DQT_USE_FAST_CONCATENATION)
  add_definitions(-DQT_USE_FAST_OPERATOR_PLUS)
elseif(NOT ${QTVERSION} VERSION_LESS 4.8.0)
  message(STATUS "[${APP_LOW_NAME}] Enabling fast QString concatenation.")

  add_definitions(-DQT_USE_FAST_CONCATENATION)
  add_definitions(-DQT_USE_FAST_OPERATOR_PLUS)
else(NOT ${QTVERSION} VERSION_LESS 4.8.0)
  message(STATUS "[${APP_LOW_NAME}] Disabling fast QString concatenation.")
endif(${USE_QT_5})

# Configure executable "properties" for Windows or OS2.
if(WIN32)
  message(STATUS "[${APP_LOW_NAME}] Generating executable file properties for Windows.")
  configure_file (
    ${PROJECT_SOURCE_DIR}/resources/executable_properties/${APP_LOW_NAME}_win.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/resources/executable_properties/${APP_LOW_NAME}_win.rc
  )
elseif(OS2)
  message(STATUS "[${APP_LOW_NAME}] Generating executable file properties for OS2.")
  configure_file (
    ${PROJECT_SOURCE_DIR}/resources/executable_properties/${APP_LOW_NAME}_os2.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/resources/executable_properties/${APP_LOW_NAME}_os2.rc
  )
endif(WIN32)

# Compile application icon if compiling with MinGW on WIN32 or with OS2.
if(MINGW AND WIN32)
  enable_language(RC)
  set(CMAKE_RC_COMPILER_INIT windres)
  message(STATUS "[${APP_LOW_NAME}] Icon file binary will be builded for Windows.")
  message(STATUS "[${APP_LOW_NAME}] Used tool is: ${CMAKE_RC_COMPILER}")
  set(CMAKE_RC_COMPILE_OBJECT
      "<CMAKE_RC_COMPILER> -i <SOURCE> -o <OBJECT>")

  set(APP_SOURCES
      ${APP_SOURCES}
      ${CMAKE_CURRENT_BINARY_DIR}/resources/executable_properties/${APP_LOW_NAME}_win.rc)
elseif(WIN32 AND MSVC)
  # MSVC takes care of this automatically - no need to use windres.exe
  # for MSVC compilers.
  set(APP_SOURCES ${APP_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/resources/executable_properties/${APP_LOW_NAME}_win.rc)
endif(MINGW AND WIN32)

# APP source files.
set(APP_SOURCES
  ${APP_SOURCES}
  
  src/gui/formmain.cpp
  src/gui/formnewproject.cpp
  src/gui/formupdate.cpp
  src/gui/widgetwithstatus.cpp
  src/gui/labelwithstatus.cpp
  src/gui/plaintoolbutton.cpp
  src/gui/systemtrayicon.cpp
  src/gui/custommessagebox.cpp
  src/gui/formabout.cpp
  src/gui/formsettings.cpp
  src/gui/formhelp.cpp
  src/gui/lineeditwithstatus.cpp
  src/gui/formsimulator.cpp
  src/gui/formuploadbundle.cpp

  src/dynamic-shortcuts/shortcutcatcher.cpp
  src/dynamic-shortcuts/shortcutbutton.cpp
  src/dynamic-shortcuts/dynamicshortcutswidget.cpp
  src/dynamic-shortcuts/dynamicshortcuts.cpp

  src/miscellaneous/application.cpp
  src/miscellaneous/settings.cpp
  src/miscellaneous/debugging.cpp
  src/miscellaneous/iconfactory.cpp
  src/miscellaneous/systemfactory.cpp
  src/miscellaneous/textfactory.cpp
  src/miscellaneous/localization.cpp
  src/miscellaneous/skinfactory.cpp
  src/miscellaneous/iofactory.cpp
  src/miscellaneous/storefactory.cpp

  src/network-web/webfactory.cpp
  src/network-web/basenetworkaccessmanager.cpp
  src/network-web/silentnetworkaccessmanager.cpp
  src/network-web/downloader.cpp
  src/network-web/networkfactory.cpp

  src/core/templatefactory.cpp
  src/core/templateentrypoint.cpp
  src/core/templatecore.cpp
  src/core/templateeditor.cpp
  src/core/templatesimulator.cpp
  src/core/templategenerator.cpp

  src/templates/quiz/quizentrypoint.cpp
  src/templates/quiz/quizcore.cpp
  src/templates/quiz/quizeditor.cpp
  src/templates/quiz/quizsimulator.cpp
  src/templates/quiz/quizquestion.cpp
  src/templates/quiz/quizitem.cpp

  src/templates/flashcard/flashcardentrypoint.cpp
  src/templates/flashcard/flashcardcore.cpp
  src/templates/flashcard/flashcardeditor.cpp
  src/templates/flashcard/flashcardsimulator.cpp
  src/templates/flashcard/flashcardquestion.cpp
  src/templates/flashcard/flashcarditem.cpp

  src/templates/mlearning/basicmlearningentrypoint.cpp
  src/templates/mlearning/basicmlearningcore.cpp
  src/templates/mlearning/basicmlearningeditor.cpp
  src/templates/mlearning/basicmlearningsimulator.cpp
  src/templates/mlearning/basicmlearningitem.cpp

  src/templates/learnspellings/learnspellingsentrypoint.cpp
  src/templates/learnspellings/learnspellingscore.cpp
  src/templates/learnspellings/learnspellingseditor.cpp
  src/templates/learnspellings/learnspellingssimulator.cpp
  src/templates/learnspellings/learnspellingsitem.cpp

  src/main.cpp
)

# APP headers.
set(APP_HEADERS
  ${APP_HEADERS}
  
  src/gui/formmain.h
  src/gui/formnewproject.h
  src/gui/formupdate.h
  src/gui/widgetwithstatus.h
  src/gui/labelwithstatus.h
  src/gui/plaintoolbutton.h
  src/gui/custommessagebox.h
  src/gui/systemtrayicon.h
  src/gui/formabout.h
  src/gui/formsettings.h
  src/gui/formhelp.h
  src/gui/lineeditwithstatus.h
  src/gui/formsimulator.h
  src/gui/formuploadbundle.h

  src/dynamic-shortcuts/dynamicshortcutswidget.h
  src/dynamic-shortcuts/shortcutcatcher.h
  src/dynamic-shortcuts/shortcutbutton.h

  src/miscellaneous/application.h
  src/miscellaneous/settings.h
  src/miscellaneous/iconfactory.h
  src/miscellaneous/localization.h
  src/miscellaneous/skinfactory.h
  src/miscellaneous/iofactory.h
  src/miscellaneous/storefactory.h

  src/network-web/webfactory.h
  src/network-web/basenetworkaccessmanager.h
  src/network-web/silentnetworkaccessmanager.h
  src/network-web/downloader.h

  src/core/templatefactory.h
  src/core/templateentrypoint.h
  src/core/templatecore.h
  src/core/templateeditor.h
  src/core/templatesimulator.h
  src/core/templategenerator.h

  src/templates/quiz/quizentrypoint.h
  src/templates/quiz/quizcore.h
  src/templates/quiz/quizeditor.h
  src/templates/quiz/quizsimulator.h
  src/templates/quiz/quizitem.h

  src/templates/flashcard/flashcardentrypoint.h
  src/templates/flashcard/flashcardcore.h
  src/templates/flashcard/flashcardeditor.h
  src/templates/flashcard/flashcardsimulator.h
  src/templates/flashcard/flashcarditem.h

  src/templates/mlearning/basicmlearningentrypoint.h
  src/templates/mlearning/basicmlearningcore.h
  src/templates/mlearning/basicmlearningeditor.h
  src/templates/mlearning/basicmlearningsimulator.h

  src/templates/learnspellings/learnspellingsentrypoint.h
  src/templates/learnspellings/learnspellingscore.h
  src/templates/learnspellings/learnspellingseditor.h
  src/templates/learnspellings/learnspellingssimulator.h
)

# APP form files.
set(APP_FORMS
  src/gui/formmain.ui
  src/gui/formupdate.ui
  src/gui/formabout.ui
  src/gui/formsettings.ui
  src/gui/formhelp.ui
  src/gui/formsimulator.ui
  src/gui/formnewproject.ui
  src/gui/formuploadbundle.ui

  src/templates/quiz/quizeditor.ui
  src/templates/quiz/quizsimulator.ui
  src/templates/quiz/quizitem.ui

  src/templates/flashcard/flashcardeditor.ui
  src/templates/flashcard/flashcardsimulator.ui
  src/templates/flashcard/flashcarditem.ui

  src/templates/mlearning/basicmlearningsimulator.ui
  src/templates/mlearning/basicmlearningeditor.ui

  src/templates/learnspellings/learnspellingseditor.ui
  src/templates/learnspellings/learnspellingssimulator.ui
)

# APP translations.
set(APP_TRANSLATIONS
  localization/${APP_LOW_NAME}-en_GB.ts
  localization/${APP_LOW_NAME}-hi_IN.ts
)

set(APP_TRANSLATIONS_WO_QT
  localization/${APP_LOW_NAME}-en_GB.ts
  localization/${APP_LOW_NAME}-hi_IN.ts
)

if(INSTALL_ALL_LANGUAGES)
  # Add remaining languages to the basic set.
endif(INSTALL_ALL_LANGUAGES)

set(APP_TEXT
  resources/text/CHANGELOG
  resources/text/LICENSE
)

if(WIN32)
  set(APP_DLLS_QT4_MSVC2010
    resources/binaries/windows/deployment/qt4-msvc2010/libeay32.dll
    resources/binaries/windows/deployment/qt4-msvc2010/msvcp100.dll
    resources/binaries/windows/deployment/qt4-msvc2010/msvcr100.dll
    resources/binaries/windows/deployment/qt4-msvc2010/QtCore4.dll
    resources/binaries/windows/deployment/qt4-msvc2010/QtGui4.dll
    resources/binaries/windows/deployment/qt4-msvc2010/QtNetwork4.dll
    resources/binaries/windows/deployment/qt4-msvc2010/QtSql4.dll
    resources/binaries/windows/deployment/qt4-msvc2010/QtWebKit4.dll
    resources/binaries/windows/deployment/qt4-msvc2010/QtXml4.dll
    resources/binaries/windows/deployment/qt4-msvc2010/ssleay32.dll
    resources/binaries/windows/deployment/qt4-msvc2010/phonon4.dll
  )

  set(APP_DLLS_QT4_MSVC2010_PHONON
    resources/binaries/windows/deployment/qt4-msvc2010/phonon_backend/phonon_ds94.dll
  )
endif(WIN32)

# Add custom icon on Mac OS X.
if(APPLE)
  SET (APP_SOURCES ${APP_SOURCES} resources/macosx/${APP_LOW_NAME}.icns)
endif(APPLE)

# Wrap files, create moc files.
if(${USE_QT_5})
  qt5_wrap_ui(APP_UI ${APP_FORMS})
  
  # Load translations.
  if(Qt5LinguistTools_FOUND)
    message(STATUS "[${APP_LOW_NAME}] Qt Linguist Tools found. Translations will get compiled.")
    qt5_add_translation(APP_QM ${APP_TRANSLATIONS})
  else(Qt5LinguistTools_FOUND)
    message(STATUS "[${APP_LOW_NAME}] Qt Linguist Tools NOT found. No compilation for translations.")
  endif(Qt5LinguistTools_FOUND)
else(${USE_QT_5})
  qt4_wrap_cpp(APP_MOC ${APP_HEADERS})
  qt4_wrap_ui(APP_UI ${APP_FORMS})
  
  # Load translations.
  qt4_add_translation(APP_QM ${APP_TRANSLATIONS})
endif(${USE_QT_5})

# Include additional directory paths.
include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/core
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
  ${CMAKE_CURRENT_SOURCE_DIR}/src/miscellaneous
  ${CMAKE_CURRENT_SOURCE_DIR}/src/network-web
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dynamic-shortcuts
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/src
)

# Compile the toolkit.
if(${USE_QT_5})
  add_executable(${EXE_NAME} WIN32 MACOSX_BUNDLE
    ${APP_SOURCES}
    ${APP_FORMS}
    ${APP_QM}
  )

  if(WIN32)
    target_link_libraries(${EXE_NAME} Qt5::WinMain)
  endif(WIN32)
  
  # Use modules from Qt.
  qt5_use_modules(${EXE_NAME}
    Core
    Widgets
    Sql
    Network
    Xml
    Multimedia
  )
# Setup compilation for Qt 4.
else(${USE_QT_5})
  add_executable(${EXE_NAME} WIN32 MACOSX_BUNDLE
    ${APP_SOURCES}
    ${APP_FORMS}
    ${APP_MOC}
    ${APP_QM}
  )

  if(OS2)
    # Link modules from Qt.
    target_link_libraries(${EXE_NAME}
      ${QT_QTCORE_LIBRARY}
      ${QT_QTGUI_LIBRARY}
      ${QT_QTNETWORK_LIBRARY}
      ${QT_QTSQL_LIBRARY}
      ${QT_QTXML_LIBRARY}
      ${QT_QTMAIN_LIBRARY}
    )
  else(OS2)
    # Link modules from Qt.
    target_link_libraries(${EXE_NAME}
      ${QT_QTCORE_LIBRARY}
      ${QT_QTGUI_LIBRARY}
      ${QT_QTNETWORK_LIBRARY}
      ${QT_QTSQL_LIBRARY}
      ${QT_QTXML_LIBRARY}
      ${QT_QTMAIN_LIBRARY}
      ${QT_PHONON_LIBRARY}
    )
  endif(OS2)
endif(${USE_QT_5})

# Installation stage.
if(WIN32 OR OS2)
  message(STATUS "[${APP_LOW_NAME}] You will probably install on Windows or OS/2.")
  install(TARGETS ${EXE_NAME}
          RUNTIME DESTINATION ./)

  if(BUNDLE_ICON_THEMES)
    install(DIRECTORY resources/graphics/icons/mini-kfaenza
            DESTINATION ./icons)
  endif(BUNDLE_ICON_THEMES)

  if(WIN32)
    # Install custom binary files for windows, dlls, exes.
    install(FILES ${APP_DLLS_QT4_MSVC2010}
            DESTINATION ./)
    install(FILES ${APP_DLLS_QT4_MSVC2010_PHONON}
            DESTINATION ./phonon_backend)
    install(DIRECTORY resources/binaries/windows/zip
            DESTINATION ./binaries)
  else(WIN32)
    install(DIRECTORY resources/binaries/os2/zip
            DESTINATION ./binaries)
  endif(WIN32)

  install(DIRECTORY resources/templates
          DESTINATION ./)
  install(DIRECTORY resources/skins
          DESTINATION ./)
  install(DIRECTORY resources/binaries/independent/certificates
          DESTINATION ./)
  install(DIRECTORY resources/binaries/independent/signapk
          DESTINATION ./binaries)
  install(FILES resources/graphics/${APP_LOW_NAME}_128.png
          DESTINATION ./
          RENAME ${APP_LOW_NAME}.png)
  install(FILES resources/graphics/${APP_LOW_NAME}.ico
          DESTINATION ./)
  install(FILES ${APP_QM}
          DESTINATION ./l10n)
  install(FILES ${APP_TEXT}
          DESTINATION ./)
elseif(APPLE)
  message(STATUS "[${APP_LOW_NAME}] You will probably install on Mac OS X.")

  set_target_properties(${EXE_NAME}
                        PROPERTIES
                        MACOSX_BUNDLE_INFO_PLIST
                        "${CMAKE_SOURCE_DIR}/resources/macosx/Info.plist.in")

  set_source_files_properties(${CMAKE_SOURCE_DIR}/resources/macosx/${APP_LOW_NAME}.icns
                              PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  set(MACOSX_BUNDLE_ICON_FILE ${APP_LOW_NAME}.icns)
  set(MACOSX_BUNDLE_INFO_STRING "${EXE_NAME} ${APP_VERSION}")
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "${APP_URL_BACKWARDS}")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "${APP_VERSION}")
  set(MACOSX_BUNDLE_BUNDLE_NAME "${EXE_NAME}")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${APP_VERSION}")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "${APP_VERSION}")
  set(MACOSX_BUNDLE_COPYRIGHT "(c) ${APP_AUTHOR}")

  install(TARGETS ${EXE_NAME}
          BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX})

  # Setup custom "bundle" prefix.
  set(APPLE_PREFIX ${CMAKE_INSTALL_PREFIX}/${EXE_NAME}.app/Contents/Resources)

  if(BUNDLE_ICON_THEMES)
    install(DIRECTORY resources/graphics/icons/mini-kfaenza
            DESTINATION ${APPLE_PREFIX}/icons)
  endif(BUNDLE_ICON_THEMES)

  install(DIRECTORY resources/templates
          DESTINATION ${APPLE_PREFIX})
  install(DIRECTORY resources/skins
          DESTINATION ${APPLE_PREFIX})
  install(DIRECTORY resources/binaries/independent/certificates
          DESTINATION ${APPLE_PREFIX})
  install(DIRECTORY resources/binaries/independent/signapk
          DESTINATION ${APPLE_PREFIX}/binaries)
  install(FILES resources/graphics/${APP_LOW_NAME}_128.png
          DESTINATION ${APPLE_PREFIX}
          RENAME ${APP_LOW_NAME}.png)
  install(FILES ${APP_QM}
          DESTINATION ${APPLE_PREFIX}/l10n)
  install(FILES ${APP_TEXT}
          DESTINATION ${APPLE_PREFIX}/information)

  # Create a "transportable" bundle - all libs into the bundle.
  #configure_file(
  #  ${CMAKE_SOURCE_DIR}/resources/macosx/bundle.cmake.in
  #  ${CMAKE_CURRENT_BINARY_DIR}/bundle.cmake @ONLY
  #)
  #
  #add_custom_target(bundle
  #  ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/bundle.cmake)
elseif(UNIX)
  message(STATUS "[${APP_LOW_NAME}] You will probably install on Linux.")
  install(TARGETS ${EXE_NAME}
          RUNTIME DESTINATION bin)

  if(BUNDLE_ICON_THEMES)
    install(DIRECTORY resources/graphics/icons/mini-kfaenza
            DESTINATION share/${APP_LOW_NAME}/icons)
  endif(BUNDLE_ICON_THEMES)

  install(DIRECTORY resources/templates
          DESTINATION share/${APP_LOW_NAME})
  install(DIRECTORY resources/skins
          DESTINATION share/${APP_LOW_NAME})
  install(DIRECTORY resources/binaries/independent/certificates
          DESTINATION share/${APP_LOW_NAME})
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/resources/desktop/${APP_LOW_NAME}.desktop
          DESTINATION share/applications)
  install(DIRECTORY resources/binaries/independent/signapk
          DESTINATION share/${APP_LOW_NAME}/binaries)
  install(FILES resources/graphics/${APP_LOW_NAME}_128.png
          DESTINATION share/pixmaps
          RENAME ${APP_LOW_NAME}.png)
  install(FILES ${APP_QM}
          DESTINATION share/${APP_LOW_NAME}/l10n)
  install(FILES ${APP_TEXT}
          DESTINATION share/${APP_LOW_NAME}/information)
endif(WIN32 OR OS2)

# Custom target for packaging.
if(WIN32)
  if(USE_NSIS)
    set(CPACK_GENERATOR "NSIS")
  else(USE_NSIS)
    set(CPACK_GENERATOR "ZIP")
  endif(USE_NSIS)
else(WIN32)
  set(CPACK_GENERATOR "ZIP")
endif(WIN32)

set(CPACK_PACKAGE_NAME ${APP_LOW_NAME})
set(CPACK_PACKAGE_VERSION ${APP_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VENDOR ${APP_COMPANY})
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${APP_NAME})
set(CPACK_IGNORE_FILES "\\\\.psd$;/CVS/;/\\\\.svn/;/\\\\.git/;\\\\.swp$;/CMakeLists.txt.user;\\\\.#;/#;\\\\.tar.gz$;/CMakeFiles/;CMakeCache.txt;\\\\.qm$;/build/;\\\\.diff$;.DS_Store'")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})

set(CPACK_NSIS_INSTALLED_ICON_NAME "${APP_LOW_NAME}.ico")
set(CPACK_NSIS_HELP_LINK ${APP_URL})
set(CPACK_NSIS_URL_INFO_ABOUT ${APP_URL})
set(CPACK_NSIS_CONTACT ${APP_EMAIL})

# Load packaging facilities.
include(CPack)

# Configure file with custom definitions for NSIS.
configure_file(
  ${PROJECT_SOURCE_DIR}/resources/nsis/NSIS.definitions.nsh.in
  ${CMAKE_CURRENT_BINARY_DIR}/resources/nsis/NSIS.definitions.nsh
)

# make dist implementation.
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

# make lupdate implementation.
if(${USE_QT_5})
  add_custom_target(lupdate
    ${Qt5Core_QMAKE_EXECUTABLE} -project -o ${CMAKE_CURRENT_BINARY_DIR}/${APP_LOW_NAME}.pro
      COMMAND ${Qt5_LUPDATE_EXECUTABLE} -no-obsolete -ts ${APP_TRANSLATIONS_WO_QT} -pro ${CMAKE_CURRENT_BINARY_DIR}/${APP_LOW_NAME}.pro
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
else(${USE_QT_5})
  add_custom_target(lupdate
    ${QT_QMAKE_EXECUTABLE} -project -o ${CMAKE_CURRENT_BINARY_DIR}/${APP_LOW_NAME}.pro
      COMMAND ${QT_LUPDATE_EXECUTABLE} -no-obsolete -ts ${APP_TRANSLATIONS_WO_QT} -pro ${CMAKE_CURRENT_BINARY_DIR}/${APP_LOW_NAME}.pro
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
endif(${USE_QT_5})
