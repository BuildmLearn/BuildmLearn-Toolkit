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

#ifndef TEMPLATECORE_H
#define TEMPLATECORE_H

#include <QObject>


class TemplateEditor;
class TemplateSimulator;
class TemplateEntryPoint;

/// \brief The core class container for single template.
/// \ingroup template-interfaces
class TemplateCore : public QObject {
    Q_OBJECT

  public:
    /// \brief Possible results of generation of bundle data.
    enum GenerationResult {
      Success,
      ZipProblem,
      SignApkProblem,
      JavaProblem,
      BundleProblem,
      CopyProblem,
      Aborted,
      OtherProblem
    };

    // Constructors and destructors.
    explicit TemplateCore(TemplateEntryPoint *entry_point, QObject *parent = 0);
    virtual ~TemplateCore();

    /// \brief Generates APK file from current project with active settings
    /// \return Returns true on success, otherwise returns false.
    /// \warning This is used only if template can actually
    /// generate mobile application, so that editor of the template
    /// must contain sufficient data for doing so.
    virtual GenerationResult generateMobileApplication(const QString &input_apk_file, QString &output_file) = 0;

    /// \brief Called after this template is fully loaded in toolkit.
    /// \note Template is fully loaded only and only if its editor is set as
    /// active and its simulator is set as active. During "launching" usually
    /// some common signals are emitted and input data of editor are checked.
    virtual void launch();

    /// \brief Access to entry point of the template.
    /// \return Returns entry point pointer.
    virtual TemplateEntryPoint *entryPoint() const {
      return m_entryPoint;
    }

    /// \brief Access to editor widget of the template.
    /// \return Returns editor widget pointer.
    virtual TemplateEditor *editor() const {
      return m_editor;
    }

    /// \brief Access to simulator widget of the template.
    /// \return Returns simulator widget pointer.
    virtual TemplateSimulator *simulator() const {
      return m_simulator;
    }

    /// \brief Access to assigned XML "bundle" file.
    /// \return Returns full path to assigned XML "bundle" file.
    ///
    /// Template core gets assigned path to XML "bundle" file,
    /// when it is loaded from that XML bundle file or when it is saved
    /// into some XML bundle file.
    ///
    /// \note This is used when using "Save" functionality, it asks
    /// if currently active core has assigned some file and if it does,
    /// then "Save" feature saves unsaved work into that file, otherwise
    /// it transfers the flow to "Save as" feature.
    QString assignedFile() const;

    /// \brief Sets new assigned file.
    /// \param assigned_file New assigned file.
    void setAssignedFile(const QString &assigned_file);

  signals:
    /// \brief Emitted when there is something new concerning generating of
    /// mobile APK application.
    /// \param percent_completed Percent of mobile application generating
    /// completed.
    /// \param progress_info Description text of status of current
    /// generating process.
    void generationProgress(int percent_completed, const QString &progress_info);

  protected:
    TemplateEntryPoint *m_entryPoint;
    TemplateEditor *m_editor;
    TemplateSimulator *m_simulator;
    QString m_assignedFile;
};

#endif // TEMPLATECORE_H
