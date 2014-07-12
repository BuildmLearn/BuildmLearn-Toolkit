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
#include <QDomDocument>

/// \brief Finds root data element in basic XML bundle header
/// and exports it as target_name argument.
#define FIND_DATA_ELEMENT(target_name, source_document)                               \
  QStringList way_to_data_element = QString(XML_BUNDLE_ROOT_DATA_ELEMENT).split('/'); \
  QDomElement target_name = source_document.documentElement();                        \
  \
  while (!way_to_data_element.isEmpty()) {                                            \
  QDomNode child_item = data_element.namedItem(way_to_data_element.at(0));          \
  \
  if (!child_item.isNull() && child_item.isElement()) {                             \
  target_name = child_item.toElement();                                           \
  way_to_data_element.removeFirst();                                              \
  }                                                                                 \
  else {                                                                            \
  return QString();                                                               \
  }                                                                                 \
  }                                                                                   \


class TemplateEntryPoint;
class TemplateCore;
class TemplateGenerator;

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

    /// \brief Generates file name for output APK file.
    /// \param project_name Name of source project.
    /// \return Access to output APK application file name pattern.
    QString applicationFileName(const QString &project_name);

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

    /// \brief Generates common XML bundle.
    /// \return Returns XML bundle structure.
    QDomDocument generateBundleHeader(const QString &template_type,
                                      const QString &author_name,
                                      const QString &author_email,
                                      const QString &project_title,
                                      const QString &project_description,
                                      const QString &template_version);

    /// \brief Access to component which supervises generating of APK files.
    /// \return Returns pointer to generator.
    TemplateGenerator *generator() const;

    /// \brief Decides which entry point raw XML bundle data belong to.
    /// \param bundle_data Raw XML bundle data.
    /// \return Returns pointer to appropriate entry point or NULL
    /// if no correct entry point exists.
    TemplateEntryPoint *entryPointForBundle(const QString &bundle_data);

    /// \brief Performs lexicographical comparison of two entry points.
    /// \note This is used for sorting entry points in FormNewProject class.
    /// \param s1 First entry point.
    /// \param s2 Second entry point.
    /// \return Returns true if s1 is less than s2, otherwise
    /// returns false.
    static bool entryPointIsLessThan(TemplateEntryPoint *s1, TemplateEntryPoint &s2);

  public slots:
    /// \brief Quits running actions of template manager.
    void quit();

    /// \brief Starts new project core from given entry point.
    /// \param entry_point Entry point to be started.
    bool startNewProject(TemplateEntryPoint *entry_point);

    /// \brief Loads stored project and initializes new core according to it.
    /// \param bundle_file_name XML bundle file name of saved project.
    bool loadProject(const QString &bundle_file_name);

    /// \brief Saves current project to given file.
    /// \param bundle_file_name File to save project XML bundle to.
    /// \return Returns true if project was saved, otherwise returns false.
    bool saveCurrentProjectAs(const QString &bundle_file_name);

    /// \brief Saves current project to assigned file if there is any.
    /// \return Returns true if project was saved, otherwise returns false.
    bool saveCurrentProject();

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
    TemplateGenerator *m_generator;
};

#endif // TEMPLATEFACTORY_H
