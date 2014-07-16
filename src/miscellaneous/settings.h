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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#include <QPointer>


/// \brief Application-wide settings mechanism.
class Settings : public QSettings {
    Q_OBJECT

  public:
    /// \brief Describes possible types of loaded settings.
    enum Type {
      Portable,
      NonPortable
    };

    // Destructor.
    virtual ~Settings();

    /// \brief Type of used settings.
    /// \return Returns type of used settings.
    inline Type type() const {
      return m_initializationStatus;
    }

    /// \brief Getter/setter for settings values.
    /// \param section Section in the settings.
    /// \param key Key of setting.
    /// \param default_value Default value to be used if no value exists for given key.
    /// \return Returns found value, default value or empty variant value.
    inline QVariant value(const QString &section,
                          const QString &key,
                          const QVariant &default_value = QVariant()) {
      return QSettings::value(QString("%1/%2").arg(section, key), default_value);
    }

    /// \brief Sets new value into settings.
    /// \param section Section in the settings.
    /// \param key Key.
    /// \param value New value.
    inline void setValue(const QString &section,
                         const QString &key,
                         const QVariant &value) {
      QSettings::setValue(QString("%1/%2").arg(section, key), value);
    }

    /// \brief Synchronizes settings.
    /// \return Returns state of settings.
    QSettings::Status checkSettings();

    /// \brief Creates settings file in correct location.
    /// \param parent Parent object.
    /// \return Returns pointer to new settings.
    static Settings *setupSettings(QObject *parent);

  private:
    // Constructor.
    Settings(const QString & file_name, Format format,
             const Type &type, QObject * parent = 0);

    Type m_initializationStatus;
};

#endif // SETTINGS_H
