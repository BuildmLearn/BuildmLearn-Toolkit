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

#ifndef IOFACTORY_H
#define IOFACTORY_H

#include <QString>
#include <QStringList>


/// \brief IO/files processing methods.
class IOFactory {
  private:
    explicit IOFactory();

  public:
    /// \brief Plays selected file with default audio output.
    /// \param file_path Path to file to play, it should be WAVE file.
    static void playWaveFile(const QString &file_path);

    /// \brief Copies source file into destination path.
    /// \param source Path to source file.
    /// \param destination Path to destination path.
    /// \return Returns true if copy operation was successfull.
    /// \warning If destination exists, then it is overwritten.
    static bool copyFile(const QString &source, const QString &destination);

    /// \brief Copies source directory into destination path.
    /// \param source Path to source directory.
    /// \param destination Path to destination directory.
    /// \return Returns true if copy operation was successfull.
    /// \note If destination exists, then it is overwritten.
    static bool copyDirectory(QString source, QString destination);

    /// \brief Removes given directory and all its contents if not exceptions are given.
    /// \param directory_name Path to directory.
    /// \param exception_file_list List of file names which should be skipped.
    /// \param exception_folder_list List of folder names which should be skipped.
    /// \return Returns true if delete operation was successfull.
    static bool removeDirectory(const QString & directory_name,
                                const QStringList &exception_file_list = QStringList(),
                                const QStringList &exception_folder_list = QStringList());

    /// \brief Takes input file and reads it into base64 byte array.
    /// \param file_name Path to file.
    /// \return Returns base64 byte array on success or empty array on failure.
    static QByteArray fileToBase64(const QString &file_name);

    /// \brief Takes base64 byte array and saves it into file.
    /// \param source_data Source base64 string.
    /// \param target_file Path to target file.
    /// \return Returns true if data was saved to file, false otherwise.
    static bool base64ToFile(const QString &source_data, const QString &target_file);
};

#endif // IOFACTORY_H
