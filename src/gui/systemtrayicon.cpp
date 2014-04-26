// This file is part of RSS Guard.
//
// Copyright (C) 2011-2014 by Martin Rotter <rotter.martinos@gmail.com>
//
// RSS Guard is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RSS Guard is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RSS Guard. If not, see <http://www.gnu.org/licenses/>.

#include "gui/systemtrayicon.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/application.h"

#include <QPainter>
#include <QTimer>


#if defined(Q_OS_WIN)
TrayIconMenu::TrayIconMenu(const QString &title, QWidget *parent)
  : QMenu(title, parent) {
}

TrayIconMenu::~TrayIconMenu() {
}

bool TrayIconMenu::event(QEvent *event) {
  if (Application::activeModalWidget() != NULL &&
      event->type() == QEvent::Show) {
    QTimer::singleShot(0, this, SLOT(hide()));
    SystemTrayIcon::instance()->showMessage(APP_LONG_NAME,
                                            tr("Close opened modal dialogs first."),
                                            QSystemTrayIcon::Warning);
  }

  return QMenu::event(event);
}
#endif

QPointer<SystemTrayIcon> SystemTrayIcon::s_trayIcon;

SystemTrayIcon::SystemTrayIcon(const QString &icon, QObject *parent)
  : QSystemTrayIcon(parent)  {
  qDebug("Creating SystemTrayIcon instance.");

  setIcon(QIcon(icon));

  // Create necessary connections.
  connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
}

SystemTrayIcon::~SystemTrayIcon() {
  qDebug("Destroying SystemTrayIcon instance.");
  hide();
}

void SystemTrayIcon::onActivated(const QSystemTrayIcon::ActivationReason &reason) {
  switch (reason) {
    case SystemTrayIcon::Trigger:
    case SystemTrayIcon::DoubleClick:
    case SystemTrayIcon::MiddleClick:
      break;

    default:
      break;
  }
}

bool SystemTrayIcon::isSystemTrayAvailable() {
  return QSystemTrayIcon::isSystemTrayAvailable() && QSystemTrayIcon::supportsMessages();
}

bool SystemTrayIcon::isSystemTrayActivated() {
  return SystemTrayIcon::isSystemTrayAvailable() && qApp->settings()->value(APP_CFG_GUI,
                                                                            "use_tray_icon",
                                                                            true).toBool();
}

SystemTrayIcon *SystemTrayIcon::instance() {
  if (s_trayIcon.isNull()) {
    s_trayIcon = new SystemTrayIcon(APP_ICON_PATH, qApp);
  }

  return s_trayIcon;
}

void SystemTrayIcon::showPrivate() {
  // Make sure that application does not exit some window (for example
  // the settings window) gets closed. Behavior for main window
  // is handled explicitly by FormMain::closeEvent() method.
  qApp->setQuitOnLastWindowClosed(false);

  // Display the tray icon.
  QSystemTrayIcon::show();
  qDebug("Tray icon displayed.");
}

void SystemTrayIcon::show() {
#if defined(Q_OS_WIN)
  // Show immediately.
  qDebug("Showing tray icon immediately.");
  showPrivate();
#else
  // Delay avoids race conditions and tray icon is properly displayed.
  qDebug("Showing tray icon with 1000 ms delay.");
  QTimer::singleShot(1000, this, SLOT(showPrivate()));
#endif
}
