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

class TemplateEntryPoint : public QObject {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateEntryPoint(TemplateFactory *parent);
    virtual ~TemplateEntryPoint();

    virtual TemplateCore *createNewCore() = 0;
    virtual TemplateCore *loadCoreFromRawData(const QString &raw_data) = 0;

    /// \brief Name of template.
    virtual QString name() const;

    /// \brief Human-readable name of template.
    virtual QString humanName() const;

    /// \brief Author of template.
    virtual QString author() const;

    /// \brief Version of template.
    virtual QString version() const;

    /// \brief Copyright of template.
    virtual QString copyright() const;

    /// \brief Base folder of template.
    virtual QString baseFolder() const;

    /// \brief Description of template.
    virtual QString description() const;

    /// \brief Relative path to thumbnail image.
    /// \remarks This path is relative to APP_TEMPLATES_PATH macro combined
    /// with base folder of template.
    virtual QString thumbnailImage() const;

  protected:
    QString m_name;
    QString m_humanName;
    QString m_author;
    QString m_version;
    QString m_copyright;
    QString m_baseFolder;
    QString m_description;
    QString m_thumbnailImage;

};

#endif // TEMPLATEENTRYPOINT_H
