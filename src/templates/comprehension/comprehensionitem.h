/*
  Copyright (c) 2015, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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

#ifndef COMPREHENSIONITEM_H
#define COMPREHENSIONITEM_H

//#include <QWidget>

#include "ui_comprehensionitem.h"

#include "templates/comprehension/comprehensionquestion.h"


namespace Ui {
  class ComprehensionItem;
}

/// \brief Widget which represents single question in Comprehension.
/// \ingroup template-comprehension
class ComprehensionItem : public QWidget {
    Q_OBJECT

  public:
    /// \brief Enum containing possible states for widget for the question.
    enum State {
      Unanswered,
      AnsweredCorrectly,
      AnsweredWrongly
    };

    // Contructors and destructors.
    explicit ComprehensionItem(QWidget *parent = 0);
    virtual ~ComprehensionItem();

    /// \brief Sets new question for this widget.
    /// \param question Question object.
    /// \param question_number Number of the question.
    void setQuestion(const ComprehensionQuestion &question, int question_number, int total_questions);

    /// \brief Access to state of comprehension question widget.
    /// \return Returns the state of comprehension question widget.
    State state() const;

  public slots:
    /// \brief Resets widget for the question to its original/default state.
    void reset();

  signals:
    /// \brief Emitted if users clicks "Next" or "Submit"
    void questionSubmitted();

  private slots:
    void onNextClicked();
    void onSubmitClicked();

  private:
    void setupButtons();
    void createConnections();
    void clearStylesheets();

  private:
    State m_state;
    Ui::ComprehensionItem *m_ui;
    ComprehensionQuestion m_question;
    QList<QRadioButton*> m_answerButtons;
};

#endif // COMPREHENSIONITEM_H
