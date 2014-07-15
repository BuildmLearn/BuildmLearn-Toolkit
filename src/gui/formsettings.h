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

#ifndef FORMSETTINGS_H
#define FORMSETTINGS_H

#include "ui_formsettings.h"

#include <QDialog>


namespace Ui {
  class FormSettings;
}

/// \brief Structure holding some initial values.
struct TemporarySettings {

  public:
    TemporarySettings() {
    }
};

/// \brief Form for displaying and editting settings.
class FormSettings : public QDialog {
    Q_OBJECT
    
  public:
    /// \brief Constructor.
    /// \param parent Parent widget.
    explicit FormSettings(QWidget *parent = 0);
    virtual ~FormSettings();

  private:
    void createConnections();

    // Does check of controls before dialog can be submitted.
    bool doSaveCheck();

  private slots:
    // Displays "restart" dialog if some critical settings changed.
    void promptForRestart();

    // Saves settings into global configuration.
    void saveSettings();

    void loadGeneral();
    void saveGeneral();

    void loadGenerationStuff();
    void saveGenerationStuff();

    void selectTempDirectory();
    void selectOutputDirectory();

    void loadExternalUtilites();
    void saveExternalUtilites();

    void checkJava(const QString& new_path);
    void checkZip(const QString& new_path);
    void checkSignApk(const QString& new_path);

    void selectJava();
    void selectZip();
    void selectSignApk();

    void loadInterface();
    void saveInterface();
    void onSkinSelected(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void loadShortcuts();
    void saveShortcuts();

    void loadLanguage();
    void saveLanguage();

    void loadBrowser();
    void saveBrowser();
    void changeDefaultBrowserArguments(int index);
    void selectBrowserExecutable();

    void loadProxy();
    void saveProxy();
    void displayProxyPassword(int state);
    void onProxyTypeChanged(int index);

  private:
    Ui::FormSettings *m_ui;
    TemporarySettings m_initialSettings;
    QStringList m_changedDataTexts;
};

#endif // FORMSETTINGS_H
