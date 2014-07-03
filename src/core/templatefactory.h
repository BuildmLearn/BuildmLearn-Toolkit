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

#ifndef TEMPLATEFACTORY_H
#define TEMPLATEFACTORY_H

#include <QObject>

#include <QHash>


class TemplateEntryPoint;
class TemplateCore;

/// \brief The top-level manager of templates.
///
/// This class is used in a singleton-like fashion from main Application
/// object via Application::templateManager(). It contains all available
/// template entry points.
/// \see TemplateEntryPoint, TemplateCore, Application
/// \ingroup template-interfaces
class TemplateFactory : public QObject {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateFactory(QObject *parent = 0);
    virtual ~TemplateFactory();

    /// \brief Access to available templates.
    /// \see TemplateEntryPoint
    /// \return Method returns list of available templates. Templates
    /// are not sorted in any particular order.
    QList<TemplateEntryPoint*> availableTemplates();

    /// \brief Access to temporary directory used throughout APK generation process.
    /// \return Returns temporary directory used throughout APK generation process.
    QString tempDirectory() const;
    void setTempDirectory(const QString &temp_directory);

    /// \brief Access to directory used throughout APK generation process.
    /// \return Returns output directory used throughout APK generation process.
    QString outputDirectory() const;
    void setOutputDirectory(const QString &output_directory);

    /// \brief Access to pattern used for name of output APK file.
    /// \return Returns pattern used for name of output APK file.
    QString applicationFileNamePattern() const;
    void setApplicationFileNamePattern(const QString &file_name_pattern);

    /// \brief Access to active entry point.
    /// \return Returns pointer to active entry point or NULL if no entry
    /// point is active.
    TemplateEntryPoint *activeEntryPoint() const {
      return m_activeEntryPoint;
    }

    /// \brief Access to active core.
    /// \return Returns pointer to active core or NULL if not core is active.
    TemplateCore *activeCore() const {
      return m_activeCore;
    }

  public slots:
    /// \brief Starts new project core from given entry point.
    /// \param entry_point Entry point to be started.
    void startNewProject(TemplateEntryPoint *entry_point);

    /// \brief Loads stored project and initializes new core according to it.
    /// \param bundle_file_name XML bundle file name of saved project.
    void loadProject(const QString &bundle_file_name);

  signals:
    /// \brief Emitted if new project using some template core is started.
    /// \param core Core object pointer.
    void newTemplateCoreCreated(TemplateCore *core);

  private:
    void clearEntryAndCore();
    void setupTemplates();

    QHash<QString, TemplateEntryPoint*> m_availableTemplates;
    TemplateEntryPoint *m_activeEntryPoint;
    TemplateCore *m_activeCore;
};

#endif // TEMPLATEFACTORY_H
