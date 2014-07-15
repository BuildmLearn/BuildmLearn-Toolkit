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

#ifndef DYNAMICSHORTCUTSWIDGET_H
#define DYNAMICSHORTCUTSWIDGET_H

#include <QWidget>


class QGridLayout;
class ShortcutCatcher;

typedef QPair<QAction*, ShortcutCatcher*> ActionBinding;

/// \brief Widget for displaying and editing shortcuts.
/// \ingroup keyboard-shortcuts
class DynamicShortcutsWidget : public QWidget {
    Q_OBJECT
    
  public:
    /// \brief Constructor.
    /// \param parent Pointer to parent object.
    explicit DynamicShortcutsWidget(QWidget *parent = 0);

    /// \brief Destructor.
    virtual ~DynamicShortcutsWidget();

    /// \brief Updates shortcuts of all actions according to changes.
    ///
    /// No access to settings is done here.
    /// Shortcuts are fetched from settings when applications starts
    /// and stored back to settings when application quits.
    void updateShortcuts();

    /// \brief Checks whether set shortcuts are unique.
    /// \returns Returns true if all shortcuts are unique,
    /// otherwise false.
    bool areShortcutsUnique();

    /// \brief Populates this widget with shortcut widgets for given actions.
    ///
    /// This gets initial shortcut for each action from its properties, NOT from
    /// the application settings, so shortcuts from settings need to be
    /// assigned to actions before calling this method.
    void populate(const QList<QAction*> actions);

  private:
    QGridLayout *m_layout;
    QList<ActionBinding> m_actionBindings;
};

#endif // DYNAMICSHORTCUTSOVERVIEW_H
