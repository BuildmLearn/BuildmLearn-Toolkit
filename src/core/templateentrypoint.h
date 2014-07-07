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

#ifndef TEMPLATEENTRYPOINT_H
#define TEMPLATEENTRYPOINT_H

#include <QObject>


class TemplateCore;
class TemplateFactory;

/// \brief The entry point for a template.
///
/// Entry points acts as a thin and light wrapper for template core.
/// It is primarily used to represent the template in "new project" dialog
/// and in some other places throughout the toolkit.
/// \see FormNewProject, TemplateCore
/// \ingroup template-interfaces
class TemplateEntryPoint : public QObject {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateEntryPoint(TemplateFactory *parent);
    virtual ~TemplateEntryPoint();

    /// \brief Creates new instance of template core.
    /// \return Returns pointer to new instance or NULL if no
    /// such instance could be created.
    virtual TemplateCore *createNewCore() = 0;

    /// \brief Creates new instance and fills it template-specific
    /// data ("load project" functionality).
    /// \param raw_data Template-specific data.
    /// \return Returns pointer to new instance or NULL if no
    /// such instance could be created.
    virtual TemplateCore *loadCoreFromBundleData(const QString &raw_data) = 0;

    /// \brief Name of template.
    virtual QString name() const;

    /// \brief Human-readable name of template.
    virtual QString humanName() const;

    /// \brief Base folder of template.
    virtual QString baseFolder() const;

    /// \brief Description of template.
    virtual QString description() const;

    /// \brief Relative path to thumbnail image.
    /// \remarks This path is relative to APP_TEMPLATES_PATH macro combined
    /// with base folder of template.
    virtual QString thumbnailImage() const;

    /// \brief Identifier of the template.
    ///
    /// Identifier is used to determine which template belongs XML bundle file to.
    /// \return Returns identifier of the template.
    QString typeIndentifier() const;

    /// \brief Access to name of template APK file.
    /// \return Returns name of APK template.
    QString mobileApplicationApkFile() const;

  protected:
    QString m_name;
    QString m_humanName;
    QString m_baseFolder;
    QString m_description;
    QString m_thumbnailImage;
    QString m_typeIndentifier;
    QString m_mobileApplicationApkFile;
};

#endif // TEMPLATEENTRYPOINT_H
