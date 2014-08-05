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

#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include <QObject>

#include "definitions/definitions.h"
#include "application.h"

#include <QString>
#include <QIcon>
#include <QPointer>
#include <QHash>
#include <QDir>


/// \brief Icon theme manipulator and provider.
class IconFactory : public QObject {
    Q_OBJECT

  public:
    // Destructor.
    virtual ~IconFactory();

    /// \brief Returns icon from active theme.
    /// \param name Name of the icon.
    /// \return Returns icon from active theme or invalid icon if
    /// "no icon theme" is set.
    inline QIcon fromTheme(const QString &name) {
      if (m_currentIconTheme == APP_NO_THEME) {
        return QIcon();
      }

      if (!m_cachedIcons.contains(name)) {
        // Icon is not cached yet.
        m_cachedIcons.insert(name, QIcon(APP_THEME_PATH + QDir::separator() +
                                         m_currentIconTheme + QDir::separator() +
                                         name + APP_THEME_SUFFIX));
      }

      return m_cachedIcons.value(name);
    }

    /// \brief Adds custom application path to be search for icons.
    void setupSearchPaths();

    /// \brief Access to list of icon themes.
    /// \return Returns list of installed themes, including "default" theme.
    QStringList installedIconThemes() const;

    /// \brief Loads name of selected icon theme (from settings) for the application and
    /// activates it.
    /// \note If that particular theme is not installed, then "default" theme is loaded.
    void loadCurrentIconTheme();

    /// \brief Gets name of current theme.
    /// \return Returns name of currently activated theme for the application.
    inline QString currentIconTheme() const {
      return m_currentIconTheme;
    }

    ///
    /// \brief Sets icon theme with given name as the active one and loads it.
    /// \param theme_name New theme name.
    void setCurrentIconTheme(const QString &theme_name);

    ///
    /// \brief Singleton getter.
    /// \return Returns pointer to singleton.
    static IconFactory *instance();

  private:
    // Constructor.
    explicit IconFactory(QObject *parent = 0);

    QHash<QString, QIcon> m_cachedIcons;
    QString m_currentIconTheme;

    // Singleton.
    static QPointer<IconFactory> s_instance;
};

#endif // ICONFACTORY_H
