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

#ifndef COMPREHENSIONPASSAGEITEM_H
#define COMPREHENSIONPASSAGEITEM_H

#include <QWidget>

#include "ui_comprehensionpassageitem.h"

#include "templates/comprehension/comprehensioneditor .h"
#include "templates/comprehension/comprehensionpassage.h"


namespace Ui {
  class ComprehensionPassageItem;
}

/// \brief Widget which represents the passage in Comprehension.
/// 
class ComprehensionPassageItem : public QWidget {
    Q_OBJECT

  public:
    
    // Contructors and destructors.
    explicit  ComprehensionPassageItem(QWidget *parent = 0);
    virtual ~ ComprehensionPassageItem();	
    void setComprehensionPassage(const ComprehensionPassage &passage);
	
  signals:
    /// \brief Emitted if users clicks "Questions" i.e user is ready to do questions
    void passageReaded();
	void passageAborted();

  private slots:
    void onQuestionsClicked();
    void onExitClicked();

  private:
    void createConnections();

  private:
    Ui::ComprehensionPassageItem *m_ui;
    ComprehensionPassage m_passage;

};

#endif // COMPREHENSIONPASSAGEITEM_H
