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

#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <QString>
#include <QObject>
#include <QPointer>


/// \brief Representation of single localization.
struct Language {
    QString m_name;
    QString m_code;
    QString m_author;
    QString m_email;
};

/// \brief Localization facilities.
class Localization : public QObject {
    Q_OBJECT

  private:
    // Constructor.
    explicit Localization(QObject *parent = 0);

  public:
    // Destructor.
    virtual ~Localization();

    /// \brief Singleton getter.
    /// \return Returns singleton.
    static Localization *instance();

    /// \brief Access to code of language that should
    /// be loaded according to settings.
    /// \return Returns code of language that should
    /// be loaded according to settings.
    QString desiredLanguage();

    /// \brief Loads currently active language.
    void load();

    /// \brief Gets list of installed languages.
    /// \return Returns list of installed application localizations.
    /// This list is used ie. in settings dialog.
    QList<Language> installedLanguages();

    /// \brief Access to code of loaded language.
    /// \return Returns empty string or loaded language
    /// name if it is really loaded.
    inline QString loadedLanguage() const {
      return m_loadedLanguage;
    }

  private:
    // Code of loaded language.
    QString m_loadedLanguage;

    // Singleton.
    static QPointer<Localization> s_instance;
};

#endif // LOCALIZATION_H
