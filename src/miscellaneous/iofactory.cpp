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

#include "miscellaneous/iofactory.h"

#include <QDir>
#include <QFile>


IOFactory::IOFactory() {
}

bool IOFactory::removeDirectory(const QString& directory_name,
                                const QStringList& exception_file_list,
                                const QStringList& exception_folder_list) {
  bool result = true;
  QDir dir(directory_name);

  if (dir.exists(directory_name)) {
    foreach (QFileInfo info,
             dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System |
                               QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
      if (info.isDir()) {
        if (!exception_folder_list.contains(info.fileName())) {
          result &= removeDirectory(info.absoluteFilePath(), exception_file_list);
        }
      }
      else if (!exception_file_list.contains(info.fileName())) {
        result &= QFile::remove(info.absoluteFilePath());
      }
    }

    result &= dir.rmdir(directory_name);
  }

  return result;
}

bool IOFactory::copyDirectory(QString source, QString destination) {
  QDir dir(source);

  if (! dir.exists()) {
    return false;
  }

  foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
    QString dst_path = destination + QDir::separator() + d;
    dir.mkpath(dst_path);
    copyDirectory(source + QDir::separator() + d, dst_path);
  }

  foreach (QString f, dir.entryList(QDir::Files)) {
    QString original_file = source + QDir::separator() + f;
    QString destination_file = destination + QDir::separator() + f;

    if (!QFile::exists(destination_file) || QFile::remove(destination_file)) {
      if (QFile::copy(original_file, destination_file)) {
        qDebug("Copied file '%1'.", QDir::toNativeSeparators(original_file));
      }
      else {
        qDebug("Failed to copy file '%1'.", QDir::toNativeSeparators(original_file));
      }
    }
    else {
      qDebug("Failed to remove file '%1'.", QDir::toNativeSeparators(original_file));
    }
  }

  return true;
}
