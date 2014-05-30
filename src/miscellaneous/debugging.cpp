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

#include "miscellaneous/debugging.h"

#include "definitions/definitions.h"
#include "miscellaneous/application.h"

#include <QDir>

#include <cstdio>
#include <cstdlib>

#ifndef QT_NO_DEBUG_OUTPUT
#if QT_VERSION >= 0x050000
#define DEBUG_OUTPUT_WORKER(type_string, file, line, message) \
  fprintf(stderr, "[%s] %s (%s:%d): %s\n", \
  APP_LOW_NAME, \
  type_string, \
  file, \
  line, \
  qPrintable(message));
#else
#define DEBUG_OUTPUT_WORKER(type_string, message) \
  fprintf(stderr, "[%s] %s: %s\n", \
  APP_LOW_NAME, \
  type_string, \
  message);
#endif
#endif


#if QT_VERSION >= 0x050000
void Debugging::debugHandler(QtMsgType type,
                             const QMessageLogContext &placement,
                             const QString &message) {
#ifndef QT_NO_DEBUG_OUTPUT
  const char *file = qPrintable(QString(placement.file).section(QDir::separator(),
                                                                -1));

  switch (type) {
    case QtDebugMsg:
      DEBUG_OUTPUT_WORKER("INFO", file, placement.line, message);
      break;
    case QtWarningMsg:
      DEBUG_OUTPUT_WORKER("WARNING", file, placement.line, message);
      break;
    case QtCriticalMsg:
      DEBUG_OUTPUT_WORKER("CRITICAL", file, placement.line, message);
      break;
    case QtFatalMsg:
      DEBUG_OUTPUT_WORKER("FATAL", file, placement.line, message);
      qApp->exit(EXIT_FAILURE);
    default:
      break;
  }
#else
  Q_UNUSED(type)
  Q_UNUSED(placement)
  Q_UNUSED(message)
#endif
}
#else
void Debugging::debugHandler(QtMsgType type, const char *message) {
  #ifndef QT_NO_DEBUG_OUTPUT
  switch (type) {
    case QtDebugMsg:
      DEBUG_OUTPUT_WORKER("INFO", message);
      break;
    case QtWarningMsg:
      DEBUG_OUTPUT_WORKER("WARNING", message);
      break;
    case QtCriticalMsg:
      DEBUG_OUTPUT_WORKER("CRITICAL", message);
      break;
    case QtFatalMsg:
      DEBUG_OUTPUT_WORKER("FATAL", message);
      qApp->exit(EXIT_FAILURE);
    default:
      break;
  }
#else
  Q_UNUSED(type)
  Q_UNUSED(message)
#endif
}
#endif

Debugging::Debugging() {
}
