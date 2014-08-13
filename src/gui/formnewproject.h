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

#ifndef FORMNEWPROJECT_H
#define FORMNEWPROJECT_H

#include <QDialog>

#include "ui_formnewproject.h"


namespace Ui {
  class FormNewProject;
}

class TemplateFactory;
class TemplateEntryPoint;

/// \brief Dialog for creating new projects.
class FormNewProject : public QDialog {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit FormNewProject(TemplateFactory *template_manager, QWidget *parent = 0);
    virtual ~FormNewProject();

  public slots:
    /// \brief Displays the dialog and returns entry point of desired
    /// template which user wants to create new project from. If "Cancel"
    /// is hit, then NULL is returned.
    TemplateEntryPoint *startNewTemplate();

  protected:
    void showEvent(QShowEvent *e);

  private slots:
    void templateSelected(int index);

  private:
    // Loads templates into the dialog.
    void loadTemplates(const QList<TemplateEntryPoint*> &entry_points);

    Ui::FormNewProject *m_ui;
    bool m_adjusted;
};

#endif // FORMNEWPROJECT_H
