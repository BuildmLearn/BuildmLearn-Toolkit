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

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QDialogButtonBox>


/// \brief Custom message boxes.
class CustomMessageBox : public QMessageBox {
    Q_OBJECT

  public:
    /// \brief Constructor.
    explicit CustomMessageBox(QWidget *parent = 0);
    virtual ~CustomMessageBox();

    /// \brief Custom icon setting.
    /// \param icon Icon to set.
    void setIcon(Icon icon);

    /// \brief Performs icon replacements for given button box.
    /// \param button_box Button box to work with.
    static void iconify(QDialogButtonBox *button_box);

    /// \brief Displays custom message box.
    /// \param parent Parent object.
    /// \param icon Icon of message box.
    /// \param title Title of message box.
    /// \param text Text of message box.
    /// \param informative_text Informative text of message box.
    /// \param detailed_text Detailed text of message box.
    /// \param buttons Which buttons to display?
    /// \param default_button Which button highlight as default one?
    /// \return Returns the status of message box (e.g. which button was pressed.
    static QMessageBox::StandardButton show(QWidget *parent,
                                            QMessageBox::Icon icon,
                                            const QString &title,
                                            const QString &text,
                                            const QString &informative_text = QString(),
                                            const QString &detailed_text = QString(),
                                            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                            QMessageBox::StandardButton default_button = QMessageBox::Ok);

  private:
    // Returns icons for standard roles/statuses.
    static QIcon iconForRole(QDialogButtonBox::StandardButton button);
    static QIcon iconForStatus(QMessageBox::Icon status);
};

#endif // MESSAGEBOX_H
