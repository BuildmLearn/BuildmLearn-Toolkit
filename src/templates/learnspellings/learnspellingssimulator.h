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

#ifndef LEARNSPELLINGSSIMULATOR_H
#define LEARNSPELLINGSSIMULATOR_H

#include "core/templatesimulator.h"

#include "ui_learnspellingssimulator.h"
#include "templates/learnspellings/learnspellingsitem.h"


namespace Ui {
  class LearnSpellingsSimulator;
}

/// \brief Simulator widget for Learn Spellings template.
/// \ingroup template-learnspellings
class LearnSpellingsSimulator : public TemplateSimulator {
    Q_OBJECT

  public:
    explicit LearnSpellingsSimulator(TemplateCore *core, QWidget *parent = 0);
    virtual ~LearnSpellingsSimulator();

  public slots:
    bool startSimulation();
    bool stopSimulation();
    bool goBack();

  private slots:
    void start();
    void restart();
    void exit();
    void playWord();
    void skipThisWord();
    void spellThisWord();
    void loadNextWord();

  private:
    Ui::LearnSpellingsSimulator *m_ui;
    QList<LearnSpellingsItem> m_words;
    int m_activeWord;
    int m_resultCorrect;
    int m_resultIncorrect;
    int m_resultSkipped;
};

#endif // LEARNSPELLINGSSIMULATOR_H
