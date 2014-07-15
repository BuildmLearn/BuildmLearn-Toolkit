/******************************************************************************
Copyright (c) 2010, Artem Galichkin <doomer3d@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef SHORTCUTCATCHER_H
#define SHORTCUTCATCHER_H

#include <QWidget>


class QHBoxLayout;
class QToolButton;
class ShortcutButton;

/// \brief Represents extra widget for changing single keyboard shortcut.
/// \ingroup keyboard-shortcuts
class ShortcutCatcher : public QWidget {
    Q_OBJECT

    friend class ShortcutButton;
    friend class DynamicShortcutsWidget;

  public:
    /// \brief Constructor.
    /// \param parent Pointer to parent widget.
    explicit ShortcutCatcher(QWidget *parent = 0);
    virtual ~ShortcutCatcher();

    /// \brief Performs time-dependent check of current shortcut check and stops
    /// the recording if time is up.
    void controlModifierlessTimeout();

    /// \brief Updates text displayed in catcher according to active shortcut.
    void updateDisplayShortcut();

    /// \brief Access to active shortcut.
    /// \return Returns active shortcut.
    inline QKeySequence shortcut() const {
      return m_currentSequence;
    }

    /// \brief Sets default shortcut for the widget.
    /// \param key Shortcut to set.
    inline void setDefaultShortcut(const QKeySequence &key) {
      m_defaultSequence = key;
      setShortcut(key);
    }

    /// \brief Sets active shortcut for the widget.
    /// \param key Shortcut to set.
    inline void setShortcut(const QKeySequence &key) {
      m_currentSequence = key;
      doneRecording();
    }

  public slots:
    /// \brief Resets active shortcut to default shortcut.
    inline void resetShortcut() {
      setShortcut(m_defaultSequence);
    }

    /// \brief Clears current active shortcut.
    inline void clearShortcut() {
      setShortcut(QKeySequence());
    }

  protected slots:
    void startRecording();
    void doneRecording();

  signals:
    void shortcutChanged(const QKeySequence &seguence);

  private:
    QToolButton *m_btnReset;
    QToolButton *m_btnClear;
    ShortcutButton *m_btnChange;
    QHBoxLayout *m_layout;

    QKeySequence m_currentSequence;
    QKeySequence m_defaultSequence;

    bool m_isRecording;
    int m_numKey;
    uint m_modifierKeys;
};

#endif // KEYSEQUENCECATCHER_H
