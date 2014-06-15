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

class TemplateCore : public QObject {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateCore(TemplateEntryPoint *entry_point, QObject *parent = 0);
    virtual ~TemplateCore();

    /// \brief Generates RAW data which represent data of this template.
    /// \remarks Generated data are stored in XML bundle file.
    /// \warning Generated data of this method must be compatible
    /// with custom implementation of TemplateEntryPoint::loadCoreFromRawData(const QString &raw_data)
    /// method!!!
    /// \return Returns string with generated data.
    virtual QString generateRawData() = 0;

    /// \brief Generates APK file from current project with active settings
    /// \return Returns true on success, otherwise returns false.
    virtual bool generateApkFile() = 0;

    virtual bool startSimulation() = 0;
    virtual bool stopSimulation() = 0;

    virtual TemplateEntryPoint *entryPoint() const {
      return m_entryPoint;
    }

    virtual TemplateEditor *editor() const {
      return m_editor;
    }

    virtual TemplateSimulator *simulator() const {
      return m_simulator;
    }

  protected:
    TemplateEntryPoint *m_entryPoint;
    TemplateEditor *m_editor;
    TemplateSimulator *m_simulator;
};

#endif // TEMPLATECORE_H
