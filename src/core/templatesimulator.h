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

#ifndef TEMPLATESIMULATOR_H
#define TEMPLATESIMULATOR_H

#include <QWidget>


class TemplateCore;

/// \brief Base widget which represents simulator of the template.
/// \ingroup template-interfaces
class TemplateSimulator : public QWidget {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit TemplateSimulator(TemplateCore *core, QWidget *parent = 0);
    virtual ~TemplateSimulator();

    /// \brief Hint for default and fixed size for all
    /// simulator contents.
    QSize sizeHint() const;

    /// \brief Called when core with this simulator widget is fully loaded from XML
    /// bundle or newly created.
    virtual void launch();

    /// \brief Access to associated template core.
    /// \return Returns associated template core.
    /// \see TemplateCore
    TemplateCore *core() const;

  public slots:
    /// \brief (Re)starts the simulation.
    /// \return Returns true if simulation was (re)started, false otherwise.
    virtual bool startSimulation() = 0;

    /// \brief Stops simulation and resets its to initial state, all user
    /// data from simulation are cleared.
    /// \return Returns true if simulation was stopped, false otherwise.
    virtual bool stopSimulation() = 0;

    /// \brief Gets simulation one step back.
    /// \return Returns true if simulation was rolled one step back, false otherwise.
    virtual bool goBack() = 0;

  signals:
    /// \brief Emitted if "can go back" status of simulator changes.
    /// \param can_go_back True if simulation can be rolled back one step, false otherwise.
    /// \warning This signal MUST be emitted explicitly by simulator when its stopSimulator() slot
    /// is called.
    void canGoBackChanged(bool can_go_back);

    /// \brief Emitted if simulation is stopped from template itself.
    void simulationStopRequested();

  protected:
    TemplateCore *m_core;
};

#endif // TEMPLATESIMULATOR_H
