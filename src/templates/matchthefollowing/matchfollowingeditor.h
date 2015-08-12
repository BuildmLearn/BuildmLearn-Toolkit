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

#ifndef MATCHFOLLOWINGEDITOR_H
#define MATCHFOLLOWINGEDITOR_H

#include "core/templateeditor.h"

#include "ui_matchfollowingeditor.h"
#include "templates/matchthefollowing/matchfollowingtopic.h"


namespace Ui {
  class MatchFollowingEditor;
}

/// \brief Editor for Match the following.
/// \ingroup template-matchthefollowing
class MatchFollowingEditor : public TemplateEditor {
    Q_OBJECT

    friend class MatchFollowingSimulator;
    friend class MatchFollowingCore;

  public:
    explicit MatchFollowingEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~MatchFollowingEditor();

    bool canGenerateApplications();
    QString generateBundleData();
    bool loadBundleData(const QString &bundle_data);

    /// \brief Access to list of added topics.
    /// \return Returns list of added topics.
    QList<MatchFollowingTopic> activeTopics() const;

    QString projectName();
    QString authorName();

  private:
    void checkAuthor();
    void checkName();
    void checkFirstListTopic();
    void checkSecondListTopic();
    void checkTemplateTitle();
    void checkFirstListTitle();
    void checkSecondListTitle();

  private slots:
    void setEditorsEnabled(bool enabled);
    void updateTopicCount();
    void addTopic();
    void loadTopic(int index);
    void saveTopic();
    void removeTopic();
    void saveTitle();
    void onAuthorChanged(const QString &new_author);
    void onNameChanged(const QString &new_name);
    void onFirstListTopicChanged(const QString &new_firstListTopic);
    void onSecondListTopicChanged(const QString &new_secondListTopic);
    void onTemplateTitleChanged(const QString &new_title);
    void onFirstListTitleChanged(const QString &new_title);
    void onSecondListTitleChanged(const QString &new_title);
    void configureUpDown();
    void moveTopicUp();
    void moveTopicDown();
    void addTopic(const QString& firstListTopic, const QString& secondListTopic);

  private:
    Ui::MatchFollowingEditor *m_ui;
    MatchFollowingTopic m_activeTopic;
};

#endif // MATCHFOLLOWINGEDITOR_H
