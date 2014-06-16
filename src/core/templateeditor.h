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


#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QWidget>


class TemplateCore;

/// \brief Represents the editor of the template.
///
/// Editor is the place where user can edit contents of the template,
/// for example questions for Quiz template.
class TemplateEditor : public QWidget {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~TemplateEditor();

    /// \brief Specifies if template can generate applications
    /// or not.
    /// \return Returns true if editor contains enough data
    /// for generating of applications.
    /// \warning This is used in cooperation with canGenerateStatusChanged(bool can_generate).
    bool canGenerateApplications() const;

    /// \brief Access to associated template core.
    /// \return Returns associated template core.
    /// \see TemplateCore
    TemplateCore *core() const;

  signals:
    /// \brief Emitted everytime any child widget of editor
    /// changes its contents.
    /// \remarks This signal is used to check if contents of
    /// editor are saved or not. If editor notifies that its contents
    /// are changed, then it is marked by toolkit as "unsaved".
    void changed();

    /// \brief Emitted if status, which specifies if mobile application
    /// can be generated from the template, changes.
    /// \param can_generate True if editor contains enough
    /// data so that mobile application can be generated, false
    /// otherwise.
    /// \remarks This is for example emitted if user ads first
    /// question item to Quiz template editor.
    void canGenerateChanged(bool can_generate);

  protected:
    TemplateCore *m_core;
    bool m_canGenerateApplications;
};

#endif // TEMPLATEEDITOR_H
