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

#ifndef COMPREHENSIONEDITOR_H
#define COMPREHENSIONEDITOR_H

#include "core/templateeditor.h"

#include "ui_comprehensioneditor.h"
#include "templates/comprehension/comprehensionquestion.h"

#include <QIcon>


namespace Ui {
  class ComprehensionEditor;
}

class ComprehensionSimulator;
class QShowEvent;

/// \brief Editor for Comprehension.
/// \ingroup template-comprehension
class ComprehensionEditor : public TemplateEditor {
    Q_OBJECT

    friend class ComprehensionSimulator;
    friend class ComprehensionCore;

  public:
    // Constructors and destructors.
    explicit ComprehensionEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~ComprehensionEditor();

    QString generateBundleData();
    bool canGenerateApplications();
    bool loadBundleData(const QString &bundle_data);

    /// \brief Access to list of added questions.
    /// \return Returns list of added questions.
    QList<ComprehensionQuestion> activeQuestions() const;

    QString projectName();
    QString authorName();

  private slots:
    void updateQuestionCount();
    void addQuestion(const QString &question, const QStringList &answers, int correct_answer);
    void addQuestion();
    void loadQuestion(int index);
    void removeQuestion();
    void saveQuestion();
    void moveQuestionUp();
    void moveQuestionDown();
	
	void selectPassage();
	void loadPassage(const QString &passage_path);
	
    void configureUpDown();
    void setEditorsEnabled(bool enabled);

    void checkName();
    void checkAuthor();
    void checkTitle();
    void checkPassage();
    void checkTimer();

    void updateNameStatus();
    void updateAuthorStatus();
    void updateTitleStatus();
    void onPassageChanged();
    void updateTimerStatus();

  private:
    ComprehensionQuestion m_activeQuestion;
    Ui::ComprehensionEditor *m_ui;
    QIcon m_iconYes;
    QIcon m_iconNo;
};

#endif // COMPREHENSIONEDITOR_H
