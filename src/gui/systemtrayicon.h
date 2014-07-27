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

#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>

#include "definitions/definitions.h"

#if defined(Q_OS_WIN)
#include <QMenu>
#endif


class QEvent;

#if defined(Q_OS_WIN)
/// \brief Tray icon Windows-specific menu.
class TrayIconMenu : public QMenu {
    Q_OBJECT

  public:
    /// \brief Constructor.
    /// \param title Title of the tray icon.
    /// \param parent Parent for the tray icon.
    explicit TrayIconMenu(const QString &title, QWidget *parent);
    virtual ~TrayIconMenu();

  protected:
    /// \brief Custom event handler.
    /// \param event Information about the event which just occurred.
    /// \return Returns true if event was handler, otherwise returns false.
    bool event(QEvent *event);
};
#endif

/// \brief Application-wide tray icon.
class SystemTrayIcon : public QSystemTrayIcon {
    Q_OBJECT

  public:
    /// \brief Constructor.
    /// \param icon Icon for tray icon.
    /// \param parent Parent of tray icon.
    explicit SystemTrayIcon(const QString &icon, QObject *parent = 0);
    virtual ~SystemTrayIcon();

    /// \brief Displays new balloon tip with message.
    /// \param title Title of message.
    /// \param message Content of message.
    /// \param icon Icon of message.
    /// \param milliseconds_timeout_hint Number of miliseconds for message to being visible.
    /// \param click_target Target object for balloon tip click.
    /// \param click_slot Target object method for balloon tip click.
    /// \warning Use this in cooperation with isSystemTrayActivated() method.
    void showMessage(const QString &title,
                     const QString &message,
                     MessageIcon icon = Information,
                     int milliseconds_timeout_hint = TRAY_ICON_BUBBLE_TIMEOUT,
                     QObject *click_target = NULL,
                     const char *click_slot = NULL);

    /// \brief Indicates whether tray icon is supported.
    /// \return Returns true if tray icon is supported.
    /// \see isSystemTrayActivated()
    static bool isSystemTrayAvailable();
    
  public slots:
    /// \brief Displays tray icon.
    void show();

  private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void showPrivate();

  signals:
    /// \brief Emitted if user clicks tray icon with left mouse button.
    void leftMouseClicked();

  private:
    QObject *m_bubbleClickTarget;
    char *m_bubbleClickSlot;
};

#endif // SYSTEMTRAYICON_H
