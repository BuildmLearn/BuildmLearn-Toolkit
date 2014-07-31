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

#ifndef LEARNSPELLINGSEDITOR_H
#define LEARNSPELLINGSEDITOR_H

#include "core/templateeditor.h"

#include "ui_learnspellingseditor.h"
#include "templates/learnspellings/learnspellingsitem.h"


namespace Ui {
  class LearnSpellingsEditor;
}

/// \brief Editor widget of Learn Spellings template.
/// \ingroup template-learnspellings
class LearnSpellingsEditor : public TemplateEditor {
    Q_OBJECT

    friend class LearnSpellingsSimulator;
    friend class LearnSpellingsCore;

  public:
    explicit LearnSpellingsEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~LearnSpellingsEditor();

    QList<LearnSpellingsItem> activeWords() const;

    QString generateBundleData();
    bool loadBundleData(const QString &bundle_data);
    bool canGenerateApplications();

    QString projectName();
    QString authorName();

  private slots:
    void addSampleWord(const QString &title, const QString &description);
    void addSampleWord();
    void removeSelectedWord();
    void saveWord();
    void displayWord(int index);
    void checkTitle(const QString &title);
    void checkDescription(const QString &description);
    void moveWordUp();
    void moveWordDown();
    void configureUpDown();
    void updateItemCount();
    void checkAuthor();
    void checkName();
    void onAuthorChanged(const QString &new_author);
    void onNameChanged(const QString &new_name);

  private:
    void setEditorsEnabled(bool enabled);

  private:
    Ui::LearnSpellingsEditor *m_ui;
    LearnSpellingsItem m_activeItem;
};



#endif // LEARNSPELLINGSEDITOR_H
