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

#include <QDomDocument>


class TemplateCore;

/// \brief Represents the editor of the template.
///
/// Editor is the place where user can edit contents of the template,
/// for example questions for Quiz template.
/// \ingroup template-interfaces
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
    virtual bool canGenerateApplications() {
      return m_canGenerate;
    }

    /// \brief Access to description of current state.
    /// \return Returns active description of generating state.
    virtual QString generationStatusDescription() {
      return m_generateMessage;
    }

    /// \brief Generates RAW data which represent data of this template.
    /// \remarks Generated data are stored in XML bundle file.
    /// \warning Generated data of this method must be compatible
    /// with custom implementation of TemplateEntryPoint::loadCoreFromBundleData(const QString &raw_data)
    /// method!!!
    /// \return Returns string with generated data.
    virtual QString generateBundleData() = 0;

    /// \brief Loads editor state from XML bundle.
    /// \param bundle_data Raw XML bundle data.
    /// \return Returns true if editor loaded bundle data, otherwise
    /// returns false.
    virtual bool loadBundleData(const QString &bundle_data) = 0;

    /// \brief Executed when given template with this editor is launched.
    /// \note Editor is "launched" when its core is newly created or loaded
    /// from XML bundle file. Durin "launch" usually only check if data contained
    /// in editor is done.
    virtual void launch();

    /// \brief Access to associated template core.
    /// \return Returns associated template core.
    /// \see TemplateCore
    TemplateCore *core() const;

    /// \brief Check if editor contains unsaved contents.
    /// \return Returns true, if editor contains unsaved contents, otherwise
    /// returns false.
    bool isDirty() const;

    /// \brief Sets new dirtiness status.
    /// \param is_dirty New dirtiness status.
    void setIsDirty(bool is_dirty);

    /// \brief Access to project name of current editor.
    /// \return Returns string of project name of current editor.
    /// This is usually text in some text box in the editor.
    virtual QString projectName() = 0;

    /// \brief Access to author name of current editor.
    /// \return Returns string of author name. This is usually text in some text box in the editor.
    virtual QString authorName() = 0;

  public slots:
    /// \brief Dirtifies (sets m_isDirty to true) the editor.
    void dirtify() {
      setIsDirty(true);
    }

  protected:
    /// \brief Emits new signal notifying other components about state
    /// of creating of APK application.
    /// \param can_generate True if editor contains enough data
    /// to generate APK application or not.
    /// \param message New message to be delivered to application
    /// about current status of creating of APK application.
    void issueNewGenereationStatus(bool can_generate, const QString &message = QString());

  signals:
    /// \brief Emitted everytime any child widget of editor
    /// changes its contents.
    /// \remarks This signal is used to check if contents of
    /// editor are saved or not. If editor notifies that its contents
    /// are changed, then it is marked by toolkit as "unsaved".
    void changed();

    /// \brief Emitted if status, which specifies if mobile application
    /// can be generated from the template, changes.
    /// \warning This signal also specifies if new simulation can be started.
    /// \param can_generate True if editor contains enough
    /// data so that mobile application can be generated, false
    /// otherwise.
    /// \remarks This is for example emitted if user ads first
    /// question item to Quiz template editor.
    void canGenerateChanged(bool can_generate, const QString &message = QString());

  protected:
    bool m_canGenerate;
    QString m_generateMessage;
    bool m_isDirty;
    TemplateCore *m_core;
};

#endif // TEMPLATEEDITOR_H
