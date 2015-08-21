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

#include "templates/dictation/dictationsimulator.h"

#include "core/templatecore.h"
#include "core/templatefactory.h"
#include "templates/dictation/dictationeditor.h"
#include "definitions/definitions.h"


DictationSimulator::DictationSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent),
    m_ui(new Ui::DictationSimulator) {
  m_ui->setupUi(this);
  
  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);
  m_ui->m_lblPassage->setFont(caption_font);
  m_ui->m_lblTitle->setFont(caption_font);
  m_ui->m_lblScore->setFont(caption_font);
  m_ui->m_lblDescription->setWordWrap(true);
  m_ui->m_txtCorrectPassage->setReadOnly(true);

  // Connecting signals and slots.
  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_listItems, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(select()));
  connect(m_ui->m_btnBack, SIGNAL(clicked()), this, SLOT(goBack()));
  connect(m_ui->m_btnSubmit, SIGNAL(clicked()), this, SLOT(submit()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_webRead, SIGNAL(loadProgress(int)), this, SLOT(loading(int)));
  connect(m_ui->m_webRead, SIGNAL(loadFinished(bool)), this, SLOT(loadingFinished(bool)));
  connect(m_ui->m_txtPassage, SIGNAL(textChanged()), this, SLOT(onEnterPassageChanged()));
}

DictationSimulator::~DictationSimulator() {
  qDebug("Destroying DictationSimulator instance.");

  delete m_ui;
}

bool DictationSimulator::startSimulation() {
  DictationEditor *editor = static_cast<DictationEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active passages or dictation does not
    // containt its name or author name.
    return false;
  }

  // Remove existing items.
  m_ui->m_listItems->clear();
  m_ui->m_txtCorrectPassage->document()->clear();
  m_ui->m_txtPassage->document()->clear();
  
  m_passages = editor->activePassages();
  
  // Add new items.
  foreach (const DictationPassage &passage, editor->activePassages()) {
    QListWidgetItem *list_item = new QListWidgetItem(passage.title(), m_ui->m_listItems);
    list_item->setData(Qt::UserRole, QVariant::fromValue(passage));
  }

  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());
  
  // Go to "start" page and begin.
  m_ui->m_phoneWidget->setCurrentIndex(1);
  return true;
}

bool DictationSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool DictationSimulator::goBack() {
  if (m_ui->m_phoneWidget->currentIndex() == 3) {
    m_ui->m_phoneWidget->setCurrentIndex(2);
    m_ui->m_listItems->setCurrentRow(-1);

    emit canGoBackChanged(false);

    return true;
  }
  else {
    return false;
  }
}

void DictationSimulator::start() {
  m_ui->m_phoneWidget->setCurrentIndex(2);
}

void DictationSimulator::restart() {
  m_ui->m_phoneWidget->setCurrentIndex(1);
  m_ui->m_txtCorrectPassage->document()->clear();
  m_ui->m_txtPassage->document()->clear();
}

// Set initial things after user has chosen the passage.
void DictationSimulator::select() {
  m_activePassage = m_ui->m_listItems->currentRow();
  m_ui->m_lblTitle->setText(m_passages.at(m_activePassage).title());
  m_ui->m_phoneWidget->setCurrentIndex(3);
  m_ui->m_readWidget->setCurrentIndex(0);
  m_ui->m_btnSubmit->setEnabled(false);
  playPassage();
  
  emit canGoBackChanged(true);
}

// Play passage by using QWebView.
void DictationSimulator::playPassage() {
  QString passage = m_passages.at(m_activePassage).passage();
  QString url = QString("http://tts-api.com/tts.mp3?q=%1").arg(passage);
  m_ui->m_progressLoading->setValue(0);
  m_ui->m_webRead->load(QUrl(url));
}

void DictationSimulator::loading(int progress) {
  m_ui->m_progressLoading->setValue(progress);
}

void DictationSimulator::loadingFinished(bool success) {
  Q_UNUSED(success);
  m_ui->m_readWidget->setCurrentIndex(1);
}

// For enabling submit button after user start writing something. 
void DictationSimulator::onEnterPassageChanged() {
  QString passage_entered = m_ui->m_txtPassage->toPlainText().simplified();
  
  if (passage_entered.isEmpty() || passage_entered.isNull())
    m_ui->m_btnSubmit->setEnabled(false);
  else
    m_ui->m_btnSubmit->setEnabled(true);
}

// For calculating the score and displaying the result
void DictationSimulator::submit() {
  
  QString passage_entered = m_ui->m_txtPassage->toPlainText().simplified();
  QString correct_passage = m_passages.at(m_activePassage).passage().simplified();
  QStringList entered_words = passage_entered.split(" ");
  QStringList correct_words = correct_passage.split(" ");
  
  m_ui->m_txtCorrectPassage->insertPlainText(correct_passage);
  
  QList<int> position;
  int word_position = correct_passage.indexOf(" ");
  position << 0;
  
  // Insert the starting position of each word in the passage in 'position' QList.
  while(word_position != -1) {
    position << word_position + 1;
    word_position = correct_passage.indexOf(" ", word_position + 1);
  }
  
  // 'begin' stores the beginning position of the wrong word and 'end' stores the ending position of the wrong word.
  QList<int> begin;
  QList<int> end;
  QStringList store_entered_words;
  QStringList store_correct_words;
  bool correct = true;
  int j = 0, start, score = 0;
  
  // Start checking the entered passage with the correct passage.
  for (int i = 0; i < correct_words.size(); i++) {
    if (j >= entered_words.size()) {
      if (correct) {
        begin << position.at(i);
      }
      correct = false;        
      break; 
    }
    
    if(correct_words.at(i) != entered_words.at(j) || !correct) {
      if (correct) {
        begin << position.at(i);
        start = i;
        correct = false;
      }
      store_entered_words << entered_words.at(j);
      for (int k = 0; k < store_entered_words.size(); ++k) {
        if(store_entered_words.at(k) == correct_words.at(i)) {
          j = start + k;
          end << position.at(i);
          store_entered_words.clear();
          correct = true;
          score++;
          break;
        }
      }
    }
    else {
      score++;
    }
    j++;
  }
  
  // If last word is incorrect, then insert the ending position of passage in 'end' QList.
  if (!correct)
    end << correct_passage.size() + 1;
  
  // Set the background color of wrong words as red.
  QTextCharFormat fmt;
  fmt.setBackground(Qt::red);

  QList< QTextCursor > cursor;
  
  // Mark the wrong words with red color.
  for(int i = 0; i < begin.size(); i++) {
    cursor << QTextCursor(m_ui->m_txtCorrectPassage->document());
    cursor[i].setPosition(begin.at(i), QTextCursor::MoveAnchor);
    cursor[i].setPosition(end.at(i) - 1, QTextCursor::KeepAnchor);
    cursor[i].setCharFormat(fmt);
  }
  
  // Display the score.
  m_ui->m_lblScore->setText(tr("Score - %1 of %2").arg(QString::number(score),
                                                       QString::number(correct_words.size())));
  
  m_ui->m_phoneWidget->setCurrentIndex(4);
}

void DictationSimulator::exit() {
  stopSimulation();
  emit simulationStopRequested();
}
