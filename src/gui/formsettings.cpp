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

#include "gui/formsettings.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/localization.h"
#include "miscellaneous/systemfactory.h"
#include "miscellaneous/iconfactory.h"
#include "network-web/webfactory.h"
#include "network-web/silentnetworkaccessmanager.h"
#include "gui/systemtrayicon.h"
#include "gui/formmain.h"
#include "gui/custommessagebox.h"
#include "miscellaneous/application.h"
#include "miscellaneous/skinfactory.h"
#include "dynamic-shortcuts/dynamicshortcutswidget.h"
#include "dynamic-shortcuts/dynamicshortcuts.h"
#include "core/templatefactory.h"

#include <QProcess>
#include <QNetworkProxy>
#include <QColorDialog>
#include <QFileDialog>


FormSettings::FormSettings(QWidget *parent)
  : QDialog(parent), m_ui(new Ui::FormSettings) {
  m_ui->setupUi(this);

  // Set flags and attributes.
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  setWindowIcon(IconFactory::instance()->fromTheme("application-settings"));

  // Setup behavior.
  m_ui->m_listSettings->setCurrentRow(0);
  m_ui->m_treeLanguages->setColumnCount(4);
  m_ui->m_treeLanguages->setHeaderHidden(false);
  m_ui->m_treeLanguages->setHeaderLabels(QStringList()
                                         << /*: Language column of language list. */ tr("Language")
                                         << /*: Lang. code column of language list. */ tr("Code")
                                         << tr("Author")
                                         << tr("Email"));

  m_ui->m_treeSkins->setColumnCount(4);
  m_ui->m_treeSkins->setHeaderHidden(false);
  m_ui->m_treeSkins->setHeaderLabels(QStringList()
                                     << /*: Skin list name column. */ tr("Name")
                                     << /*: Version column of skin list. */ tr("Version")
                                     << tr("Author")
                                     << tr("Email"));

#if QT_VERSION >= 0x050000
  // Setup languages.
  m_ui->m_treeLanguages->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  m_ui->m_treeLanguages->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
  m_ui->m_treeLanguages->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
  m_ui->m_treeLanguages->header()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

  // Setup skins.
  m_ui->m_treeSkins->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  m_ui->m_treeSkins->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
  m_ui->m_treeSkins->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
  m_ui->m_treeSkins->header()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
#else
  // Setup languages.
  m_ui->m_treeLanguages->header()->setResizeMode(0, QHeaderView::ResizeToContents);
  m_ui->m_treeLanguages->header()->setResizeMode(1, QHeaderView::ResizeToContents);
  m_ui->m_treeLanguages->header()->setResizeMode(2, QHeaderView::ResizeToContents);
  m_ui->m_treeLanguages->header()->setResizeMode(3, QHeaderView::ResizeToContents);

  // Setup skins.
  m_ui->m_treeSkins->header()->setResizeMode(0, QHeaderView::ResizeToContents);
  m_ui->m_treeSkins->header()->setResizeMode(1, QHeaderView::ResizeToContents);
  m_ui->m_treeSkins->header()->setResizeMode(2, QHeaderView::ResizeToContents);
  m_ui->m_treeSkins->header()->setResizeMode(3, QHeaderView::ResizeToContents);
#endif

  // Establish needed connections.
  createConnections();

  // Load all settings.
  loadGeneral();
  loadExternalUtilites();
  loadInterface();
  loadShortcuts();
  loadProxy();
  loadBrowser();
  loadLanguage();
  loadGenerationStuff();
}

FormSettings::~FormSettings() {
  qDebug("Destroying FormSettings distance.");
  delete m_ui;
}

void FormSettings::changeDefaultBrowserArguments(int index) {
  if (index != 0) {
    m_ui->m_txtExternalBrowserArguments->setText(m_ui->m_cmbExternalBrowserPreset->itemData(index).toString());
  }
}

void FormSettings::createConnections() {
  connect(m_ui->m_buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
  connect(m_ui->m_cmbProxyType, SIGNAL(currentIndexChanged(int)), this, SLOT(onProxyTypeChanged(int)));
  connect(m_ui->m_checkShowPassword, SIGNAL(stateChanged(int)), this, SLOT(displayProxyPassword(int)));
  connect(m_ui->m_cmbExternalBrowserPreset, SIGNAL(currentIndexChanged(int)), this, SLOT(changeDefaultBrowserArguments(int)));
  connect(m_ui->m_btnExternalBrowserExecutable, SIGNAL(clicked()), this, SLOT(selectBrowserExecutable()));
  connect(m_ui->m_btnSelectZip, SIGNAL(clicked()), this, SLOT(selectZip()));
  connect(m_ui->m_btnSelectJava, SIGNAL(clicked()), this, SLOT(selectJava()));
  connect(m_ui->m_btnSelectSignapk, SIGNAL(clicked()), this, SLOT(selectSignApk()));
  connect(m_ui->m_btnGenerationOutputSelect, SIGNAL(clicked()), this, SLOT(selectOutputDirectory()));
  connect(m_ui->m_btnGenerationTempSelect, SIGNAL(clicked()), this, SLOT(selectTempDirectory()));
  connect(m_ui->m_treeSkins, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
          this, SLOT(onSkinSelected(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void FormSettings::onSkinSelected(QTreeWidgetItem *current,
                                  QTreeWidgetItem *previous) {
  Q_UNUSED(previous)

  if (current != NULL) {
    Skin skin = current->data(0, Qt::UserRole).value<Skin>();
    m_ui->m_lblSelectedContents->setText(skin.m_visibleName);
  }
}

void FormSettings::selectBrowserExecutable() {
  QString executable_file = QFileDialog::getOpenFileName(this,
                                                         tr("Select web browser executable"),
                                                         QDir::homePath(),
                                                         //: File filter for external browser selection dialog.
                                                         tr("Executables (*.*)"));

  if (!executable_file.isEmpty()) {
    m_ui->m_txtExternalBrowserExecutable->setText(QDir::toNativeSeparators(executable_file));
  }
}

void FormSettings::displayProxyPassword(int state) {
  if (state == Qt::Checked) {
    m_ui->m_txtProxyPassword->setEchoMode(QLineEdit::Normal);
  }
  else {
    m_ui->m_txtProxyPassword->setEchoMode(QLineEdit::Password);
  }
}

bool FormSettings::doSaveCheck() {
  bool everything_ok = true;
  QStringList resulting_information;

  // Setup indication of settings consistence.
  if (!m_ui->m_shortcutsEditor->areShortcutsUnique()) {
    everything_ok = false;
    resulting_information.append(tr("some keyboard shortcuts are not unique"));
  }

  // User selected custom external browser but did not set its
  // properties.
  if (m_ui->m_grpCustomExternalBrowser->isChecked() &&
      (m_ui->m_txtExternalBrowserExecutable->text().simplified().isEmpty() ||
       !m_ui->m_txtExternalBrowserArguments->text().simplified().contains("%1"))) {
    everything_ok = false;
    resulting_information.append(tr("custom external browser is not set correctly"));
  }

  if (!everything_ok) {
    resulting_information.replaceInStrings(QRegExp("^"),
                                           QString::fromUtf8(" • "));

    CustomMessageBox::show(this,
                           QMessageBox::Critical,
                           tr("Cannot save settings"),
                           tr("Some critical settings are not set. You must fix these settings in order confirm new settings."),
                           QString(),
                           tr("List of errors:\n%1.").arg(resulting_information.join(",\n")));
  }

  return everything_ok;
}

void FormSettings::promptForRestart() {
  if (m_changedDataTexts.count() > 0) {
    QStringList changed_data_texts = m_changedDataTexts;

    changed_data_texts.replaceInStrings(QRegExp("^"),
                                        QString::fromUtf8(" • "));

    int question_result = CustomMessageBox::show(this,
                                                 QMessageBox::Question,
                                                 tr("Critical settings were changed"),
                                                 tr("Some critical settings were changed and will be applied after the application gets restarted."),
                                                 tr("Do you want to restart now?"),
                                                 tr("List of changes:\n%1.").arg(changed_data_texts.join(",\n")),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes);

    if (question_result == QMessageBox::Yes) {
      if (!QProcess::startDetached(qApp->applicationFilePath())) {
        if (SystemTrayIcon::isSystemTrayAvailable()) {
          qApp->trayIcon()->showMessage(tr("Problem with application restart"),
                                        tr("Application couldn't be restarted. "
                                           "Please, restart it manually for changes to take effect."),
                                        QSystemTrayIcon::Warning);
        }
        else {
          CustomMessageBox::show(this,
                                 QMessageBox::Warning,
                                 tr("Problem with application restart"),
                                 tr("Application couldn't be restarted. "
                                    "Please, restart it manually for changes to take effect."));
        }
      }
      else {
        qApp->quit();
      }
    }
  }
}

void FormSettings::saveSettings() {
  // Make sure everything is saveable.
  if (!doSaveCheck()) {
    return;
  }

  // Save all settings.
  saveGeneral();
  saveExternalUtilites();
  saveInterface();
  saveShortcuts();
  saveProxy();
  saveBrowser();
  saveLanguage();
  saveGenerationStuff();

  qApp->settings()->checkSettings();
  promptForRestart();

  accept();
}

void FormSettings::loadGeneral() {
  m_ui->m_checkCheckForUpdatesOnStartup->setChecked(qApp->settings()->value(APP_CFG_GEN,
                                                                            "check_for_updates_startup",
                                                                            true).toBool());
}

void FormSettings::saveGeneral() {
  qApp->settings()->setValue(APP_CFG_GEN,
                             "check_for_updates_startup",
                             m_ui->m_checkCheckForUpdatesOnStartup->isChecked());
}

void FormSettings::loadExternalUtilites() {
  checkZip(QDir::toNativeSeparators(qApp->zipUtilityPath()));
  checkJava(QDir::toNativeSeparators(qApp->javaInterpreterPath()));
  checkSignApk(QDir::toNativeSeparators(qApp->signApkUtlityPath()));
}

void FormSettings::saveExternalUtilites() {
  qApp->setZipUtilityPath(m_ui->m_lblExternalZip->label()->text());
  qApp->setJavaInterpreterPath(m_ui->m_lblExternalJava->label()->text());
  qApp->setSignApkUtilityPath(m_ui->m_lblExternalSignapk->label()->text());
  qApp->recheckExternalApplications(true);
}

void FormSettings::checkZip(const QString &new_path) {
  int zip_output = qApp->checkZip(new_path);
  QString textual_info = qApp->interpretZip(zip_output);

  switch (zip_output) {
    case EXIT_STATUS_NOT_STARTED:
      m_ui->m_lblExternalZip->setStatus(WidgetWithStatus::Error,
                                        new_path,
                                        textual_info);
      break;

    case EXIT_STATUS_ZIP_NORMAL:
      m_ui->m_lblExternalZip->setStatus(WidgetWithStatus::Ok,
                                        new_path,
                                        textual_info);
      break;

    case EXIT_STATUS_CRASH:
    default:
      m_ui->m_lblExternalZip->setStatus(WidgetWithStatus::Warning,
                                        new_path,
                                        textual_info);
      break;
  }
}

void FormSettings::checkJava(const QString &new_path) {
  int java_output = qApp->checkJava(new_path);
  QString textual_info = qApp->interpretJava(java_output);

  switch (java_output) {
    case EXIT_STATUS_NOT_STARTED:
      m_ui->m_lblExternalJava->setStatus(WidgetWithStatus::Error,
                                         new_path,
                                         textual_info);
      break;

    case EXIT_STATUS_JAVA_NORMAL:
      m_ui->m_lblExternalJava->setStatus(WidgetWithStatus::Ok,
                                         new_path,
                                         textual_info);
      break;

    case EXIT_STATUS_CRASH:
    default:
      m_ui->m_lblExternalJava->setStatus(WidgetWithStatus::Warning,
                                         new_path,
                                         textual_info);
      break;
  }
}

void FormSettings::checkSignApk(const QString &new_path) {
  int signapk_output = qApp->checkSignApk(new_path, m_ui->m_lblExternalJava->label()->text());
  QString textual_info = qApp->interpretSignApk(signapk_output);

  switch (signapk_output) {
    case EXIT_STATUS_SIGNAPK_NOT_FOUND:
    case EXIT_STATUS_NOT_STARTED:
      m_ui->m_lblExternalSignapk->setStatus(WidgetWithStatus::Error,
                                            new_path,
                                            textual_info);
      break;

    case EXIT_STATUS_SIGNAPK_NORMAL:
      m_ui->m_lblExternalSignapk->setStatus(WidgetWithStatus::Ok,
                                            new_path,
                                            textual_info);
      break;

    case EXIT_STATUS_CRASH:
    case EXIT_STATUS_SIGNAPK_WORKING:
    default:
      m_ui->m_lblExternalSignapk->setStatus(WidgetWithStatus::Warning,
                                            new_path,
                                            textual_info);
      break;
  }
}

void FormSettings::selectJava() {
  QString executable_file = QFileDialog::getOpenFileName(this,
                                                         tr("Select JAVA executable"),
                                                         m_ui->m_lblExternalJava->label()->text(),
                                                         //: File filter for external browser selection dialog.
                                                         tr("Executables (java*)"),
                                                         0);

  if (!executable_file.isEmpty()) {
    checkJava(QDir::toNativeSeparators(executable_file));
    checkSignApk(m_ui->m_lblExternalSignapk->label()->text());
  }
}

void FormSettings::selectZip() {
  QString executable_file = QFileDialog::getOpenFileName(this,
                                                         tr("Select ZIP executable"),
                                                         m_ui->m_lblExternalZip->label()->text(),
                                                         //: File filter for external browser selection dialog.
                                                         tr("Executables (zip*)"),
                                                         0);

  if (!executable_file.isEmpty()) {
    checkZip(QDir::toNativeSeparators(executable_file));
  }
}

void FormSettings::selectSignApk() {
  QString executable_file = QFileDialog::getOpenFileName(this,
                                                         tr("Select SIGNAPK executable"),
                                                         m_ui->m_lblExternalSignapk->label()->text(),
                                                         //: File filter for external browser selection dialog.
                                                         tr("Executables (signapk.jar)"),
                                                         0);

  if (!executable_file.isEmpty()) {
    checkSignApk(QDir::toNativeSeparators(executable_file));
  }
}

void FormSettings::onProxyTypeChanged(int index) {
  QNetworkProxy::ProxyType selected_type = static_cast<QNetworkProxy::ProxyType>(m_ui->m_cmbProxyType->itemData(index).toInt());
  bool is_proxy_selected = selected_type != QNetworkProxy::NoProxy && selected_type != QNetworkProxy::DefaultProxy;

  m_ui->m_txtProxyHost->setEnabled(is_proxy_selected);
  m_ui->m_txtProxyPassword->setEnabled(is_proxy_selected);
  m_ui->m_txtProxyUsername->setEnabled(is_proxy_selected);
  m_ui->m_spinProxyPort->setEnabled(is_proxy_selected);
  m_ui->m_checkShowPassword->setEnabled(is_proxy_selected);
  m_ui->m_lblProxyHost->setEnabled(is_proxy_selected);
  m_ui->m_lblProxyInfo->setEnabled(is_proxy_selected);
  m_ui->m_lblProxyPassword->setEnabled(is_proxy_selected);
  m_ui->m_lblProxyPort->setEnabled(is_proxy_selected);
  m_ui->m_lblProxyUsername->setEnabled(is_proxy_selected);
}

void FormSettings::loadBrowser() {
  Settings *settings = qApp->settings();

  // Load settings of web browser GUI.
  m_ui->m_cmbExternalBrowserPreset->addItem(tr("Opera 12 or older"), "-nosession %1");
  m_ui->m_txtExternalBrowserExecutable->setText(QDir::toNativeSeparators(settings->value(APP_CFG_BROWSER,
                                                                                         "external_browser_executable").toString()));
  m_ui->m_txtExternalBrowserArguments->setText(settings->value(APP_CFG_BROWSER,
                                                               "external_browser_arguments",
                                                               "%1").toString());
  m_ui->m_grpCustomExternalBrowser->setChecked(settings->value(APP_CFG_BROWSER,
                                                               "custom_external_browser",
                                                               false).toBool());
}

void FormSettings::saveBrowser() {
  Settings *settings = qApp->settings();

  // Save settings of GUI of web browser.
  settings->setValue(APP_CFG_BROWSER,
                     "custom_external_browser",
                     m_ui->m_grpCustomExternalBrowser->isChecked());
  settings->setValue(APP_CFG_BROWSER,
                     "external_browser_executable",
                     m_ui->m_txtExternalBrowserExecutable->text());
  settings->setValue(APP_CFG_BROWSER,
                     "external_browser_arguments",
                     m_ui->m_txtExternalBrowserArguments->text());
}

void FormSettings::loadProxy() {
  m_ui->m_cmbProxyType->addItem(tr("No proxy"), QNetworkProxy::NoProxy);
  m_ui->m_cmbProxyType->addItem(tr("System proxy"), QNetworkProxy::DefaultProxy);
  m_ui->m_cmbProxyType->addItem(tr("Socks5"), QNetworkProxy::Socks5Proxy);
  m_ui->m_cmbProxyType->addItem(tr("Http"), QNetworkProxy::HttpProxy);

  // Load the settings.
  Settings *settings = qApp->settings();

  QNetworkProxy::ProxyType selected_proxy_type = static_cast<QNetworkProxy::ProxyType>(settings->value(APP_CFG_PROXY,
                                                                                                       "proxy_type",
                                                                                                       QNetworkProxy::NoProxy).toInt());

  m_ui->m_cmbProxyType->setCurrentIndex(m_ui->m_cmbProxyType->findData(selected_proxy_type));
  m_ui->m_txtProxyHost->setText(settings->value(APP_CFG_PROXY,
                                                "host").toString());
  m_ui->m_txtProxyUsername->setText(settings->value(APP_CFG_PROXY,
                                                    "username").toString());
  m_ui->m_txtProxyPassword->setText(settings->value(APP_CFG_PROXY,
                                                    "password").toString());
  m_ui->m_spinProxyPort->setValue(settings->value(APP_CFG_PROXY,
                                                  "port", 80).toInt());
}

void FormSettings::saveProxy() {
  Settings *settings = qApp->settings();

  settings->setValue(APP_CFG_PROXY, "proxy_type",
                     m_ui->m_cmbProxyType->itemData(m_ui->m_cmbProxyType->currentIndex()));
  settings->setValue(APP_CFG_PROXY, "host",
                     m_ui->m_txtProxyHost->text());
  settings->setValue(APP_CFG_PROXY, "username",
                     m_ui->m_txtProxyUsername->text());
  settings->setValue(APP_CFG_PROXY, "password",
                     m_ui->m_txtProxyPassword->text());
  settings->setValue(APP_CFG_PROXY, "port",
                     m_ui->m_spinProxyPort->value());
}

void FormSettings::loadLanguage() {
  foreach (const Language &language, Localization::instance()->installedLanguages()) {
    QTreeWidgetItem *item = new QTreeWidgetItem(m_ui->m_treeLanguages);
    item->setText(0, language.m_name);
    item->setText(1, language.m_code);
    item->setText(2, language.m_author);
    item->setText(3, language.m_email);
    item->setIcon(0, IconFactory::instance()->fromTheme(language.m_code));
  }

  QList<QTreeWidgetItem*> matching_items = m_ui->m_treeLanguages->findItems(Localization::instance()->loadedLanguage(),
                                                                            Qt::MatchContains,
                                                                            1);
  if (!matching_items.isEmpty()) {
    m_ui->m_treeLanguages->setCurrentItem(matching_items[0]);
  }
}

void FormSettings::saveLanguage() {
  if (m_ui->m_treeLanguages->currentItem() == NULL) {
    qDebug("No localizations loaded in settings dialog, so no saving for them.");
    return;
  }

  Settings *settings = qApp->settings();
  QString actual_lang = Localization::instance()->loadedLanguage();
  QString new_lang = m_ui->m_treeLanguages->currentItem()->text(1);

  // Save prompt for restart if language has changed.
  if (new_lang != actual_lang) {
    m_changedDataTexts.append(tr("language changed"));
    settings->setValue(APP_CFG_GEN, "language", new_lang);
  }
}

void FormSettings::loadInterface() {
  // Load settings of icon theme.
  QString current_theme = IconFactory::instance()->currentIconTheme();

  foreach (const QString &icon_theme_name, IconFactory::instance()->installedIconThemes()) {
    if (icon_theme_name == APP_NO_THEME) {
      // Add just "no theme" on other systems.
      //: Label for disabling icon theme.
      m_ui->m_cmbIconTheme->addItem(tr("no icon theme"),
                                    APP_NO_THEME);
    }
    else {
      m_ui->m_cmbIconTheme->addItem(icon_theme_name,
                                    icon_theme_name);
    }
  }

  // Mark active theme.
  if (current_theme == APP_NO_THEME) {
    // Because "no icon theme" lies at the index 0.
    m_ui->m_cmbIconTheme->setCurrentIndex(0);
  }
  else {
#if QT_VERSION >= 0x050000
    m_ui->m_cmbIconTheme->setCurrentText(current_theme);
#else
    int theme_index = m_ui->m_cmbIconTheme->findText(current_theme);
    if (theme_index >= 0) {
      m_ui->m_cmbIconTheme->setCurrentIndex(theme_index);
    }
#endif
  }

  // Load skin.
  QString selected_skin = qApp->skinFactory()->selectedSkinName();

  foreach (const Skin &skin, qApp->skinFactory()->installedSkins()) {
    QTreeWidgetItem *new_item = new QTreeWidgetItem(QStringList() <<
                                                    skin.m_visibleName <<
                                                    skin.m_version <<
                                                    skin.m_author <<
                                                    skin.m_email);
    new_item->setData(0, Qt::UserRole, QVariant::fromValue(skin));

    // Add this skin and mark it as active if its active now.
    m_ui->m_treeSkins->addTopLevelItem(new_item);

    if (skin.m_baseName == selected_skin) {
      m_ui->m_treeSkins->setCurrentItem(new_item);
      m_ui->m_lblActiveContents->setText(skin.m_visibleName);
    }
  }

  if (m_ui->m_treeSkins->currentItem() == NULL &&
      m_ui->m_treeSkins->topLevelItemCount() > 0) {
    // Currently active skin is NOT available, select another one as selected
    // if possible.
    m_ui->m_treeSkins->setCurrentItem(m_ui->m_treeSkins->topLevelItem(0));
  }
}

void FormSettings::saveInterface() {
  // Save selected icon theme.
  QString selected_icon_theme = m_ui->m_cmbIconTheme->itemData(m_ui->m_cmbIconTheme->currentIndex()).toString();
  QString original_icon_theme = IconFactory::instance()->currentIconTheme();
  IconFactory::instance()->setCurrentIconTheme(selected_icon_theme);

  // Check if icon theme was changed.
  if (selected_icon_theme != original_icon_theme) {
    m_changedDataTexts.append(tr("icon theme changed"));
  }

  // Save and activate new skin.
  if (m_ui->m_treeSkins->selectedItems().size() > 0) {
    Skin active_skin = m_ui->m_treeSkins->currentItem()->data(0, Qt::UserRole).value<Skin>();

    if (qApp->skinFactory()->selectedSkinName() != active_skin.m_baseName) {
      qApp->skinFactory()->setCurrentSkinName(active_skin.m_baseName);
      m_changedDataTexts.append(tr("skin changed"));
    }
  }
}

void FormSettings::loadShortcuts() {
  m_ui->m_shortcutsEditor->populate(qApp->availableActions());
}

void FormSettings::saveShortcuts() {
  // Update the actual shortcuts of some actions.
  m_ui->m_shortcutsEditor->updateShortcuts();

  // Save new shortcuts to the settings.
  DynamicShortcuts::save(qApp->availableActions());
}

void FormSettings::loadGenerationStuff() {
  m_ui->m_lblGenerationTemp->setText(QDir::toNativeSeparators(qApp->templateManager()->tempDirectory()));
  m_ui->m_lblGenerationOutput->setText(QDir::toNativeSeparators(qApp->templateManager()->outputDirectory()));
  m_ui->m_txtGenerationOutputFilePattern->setText(QDir::toNativeSeparators(qApp->templateManager()->applicationFileNamePattern()));
}

void FormSettings::saveGenerationStuff() {
  qApp->templateManager()->setOutputDirectory(m_ui->m_lblGenerationOutput->text());
  qApp->templateManager()->setTempDirectory(m_ui->m_lblGenerationTemp->text());
  qApp->templateManager()->setApplicationFileNamePattern(m_ui->m_txtGenerationOutputFilePattern->text());
}

void FormSettings::selectTempDirectory() {
  QString temp_directory = QFileDialog::getExistingDirectory(this,
                                                             tr("Select temporary directory"),
                                                             m_ui->m_lblGenerationTemp->text());

  if (!temp_directory.isEmpty()) {
    m_ui->m_lblGenerationTemp->setText(QDir::toNativeSeparators(temp_directory));
  }
}

void FormSettings::selectOutputDirectory() {
  QString output_directory = QFileDialog::getExistingDirectory(this,
                                                               tr("Select output directory"),
                                                               m_ui->m_lblGenerationOutput->text());

  if (!output_directory.isEmpty()) {
    m_ui->m_lblGenerationOutput->setText(QDir::toNativeSeparators(output_directory));
  }
}
