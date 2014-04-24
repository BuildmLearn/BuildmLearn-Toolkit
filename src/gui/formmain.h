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

#ifndef FORMMAIN_H
#define FORMMAIN_H

#include "ui_formmain.h"

#include "gui/formnewproject.h"

#include "InfoTemplate.h"
#include "QuizTemplate.h"
#include "FlashcardTemplate.h"

#include <QMainWindow>
#include <QtGui>

#define HELP_URL "http://buildmlearn.wordpress.com/download/"


namespace Ui {
  class FormMain;
}

class FormMain : public QMainWindow {
    Q_OBJECT
    
  public:
    // Constructors and destructors.
    explicit FormMain(QWidget *parent = 0);
    virtual ~FormMain();

  public slots:
    void startProject(int);
    void aboutClicked();
    void helpClicked();
    void generateClicked();
    void newClicked();
    void saveClicked();
    void openClicked();
    void loadOpenFile();
    void resetWidgets();

  private:
    Ui::FormMain *m_ui;

    // Menus
    QMenu *fileMenu;
    QMenu *projectMenu;

    // Action
    QAction *newAct;
    QAction *saveAct;
    QAction *openAct;
    QAction *exitAct;
    QAction *buildAct;

    // Toolbar
    QToolBar* toolBar;

    // Other widgets
    QStackedWidget* iStackedWidget;

    // Create NewProject Widget
    FormNewProject *iNewProjectWidget;

    //  Blank widget
    QWidget* iBlankWidget;
    // Create InfoTemplate Widget
    InfoTemplate* iInfoTemplateWidget;
    // Create QuizTemplate Widget
    QuizTemplate* iQuizTemplateWidget;
    // Create Flashcards Widget
    FlashcardTemplate* iFlashCardsWidget;
};

#endif // FORMMAIN_H
