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
#include "miscellaneous/application.h"
#include "miscellaneous/skinfactory.h"
#include "network-web/networkfactory.h"
#include "gui/custommessagebox.h"

#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>


DictationSimulator::DictationSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent),
    m_ui(new Ui::DictationSimulator) {
  m_ui->setupUi(this);
  m_player = new QMediaPlayer;
  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);
  m_ui->m_lblPassage->setFont(caption_font);
  m_ui->m_lblTitle->setFont(caption_font);
  m_ui->m_lblScore->setFont(caption_font);
  m_ui->m_lblDescription->setWordWrap(true);
  
  QString style = "QPushButton {min-height:1.5em; font:1em; margin:0 1px 0 1px; color: white; \
                   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff3232, \
                   stop: 1 #e50000); border-style: outset;border-radius: 3px; border-width: 1px; \
                   border-color: #ff0000;} QPushButton:pressed {background-color: \
                   qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e50000, stop: 1 #ff3232);}";

  m_ui->m_btnStart->setStyleSheet(style);
  m_ui->m_btnBack->setStyleSheet(style);
  m_ui->m_btnExit->setStyleSheet(style);
  
  style = "QPushButton{min-height:1.5em; font:1em; margin:0 1px 0 1px; color: white; \
           background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #329932, stop: \
           1 #004C00); border-style: outset;border-radius: 3px; border-width: 1px; \
           border-color: #50873a;} QPushButton:pressed {background-color: \
           qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #004C00, stop: 1 #329932);}";
  
  //m_ui->m_btnSelect->setStyleSheet(style);
  m_ui->m_btnSubmit->setStyleSheet(style);
  m_ui->m_btnRestart->setStyleSheet(style);
  
  style = "QTextEdit {color: black; background-color: white;} QScrollBar {background-color: grey; border-style: \
           outset;border-radius: 3px; border-width: 1px; border-color: black;}";
  
  m_ui->m_txtPassage->setStyleSheet(style);
  m_ui->m_txtCorrectPassage->setStyleSheet(style);
  m_ui->m_txtCorrectPassage->setReadOnly(true);

  style = "QListWidget {color: black; background-color: white;} QScrollBar {background-color: grey; border-style: \
           outset;border-radius: 3px; border-width: 1px; border-color: black;}";
           
  m_ui->m_listItems->setStyleSheet(style);

  m_factory = IconFactory::instance();

  m_ui->m_btnPlayPause->setIcon(m_factory->fromTheme("player-pause"));
  m_play = true;
  //m_ui->m_sliderPlay->setMinimum(0);
  //m_ui->m_sliderPlay->setSingleStep(1);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  //connect(m_ui->m_btnSelect, SIGNAL(clicked()), this, SLOT(select()));
  connect(m_ui->m_listItems, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(select()));
  connect(m_ui->m_btnBack, SIGNAL(clicked()), this, SLOT(goBack()));
  connect(m_ui->m_btnPlayPause, SIGNAL(clicked()), this, SLOT(playPause()));
  connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(moveSlider(qint64)));
  connect(m_ui->m_btnSubmit, SIGNAL(clicked()), this, SLOT(submit()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(restart()));
}

DictationSimulator::~DictationSimulator() {
  //qDebug("Destroying DictationSimulator instance.");

  delete m_player;
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

/*void DictationSimulator::selectPassage(QListWidgetItem *passage) {
  selected_passage = passage->data(Qt::UserRole).value<DictationPassage>();
}*/

void DictationSimulator::select() {//QListWidgetItem *passage) {
  //m_ui->m_lblTitle->setText(selected_passage->data(Qt::UserRole).value<DictationPassage>().title());
  m_activePassage = m_ui->m_listItems->currentRow();
  m_ui->m_lblTitle->setText(m_passages.at(m_activePassage).title());
  m_ui->m_phoneWidget->setCurrentIndex(3);
  playPassage();
  
  emit canGoBackChanged(true);
}

/*void DictationSimulator::playPassage() {
  QString url = QString("http://tts-api.com/tts.mp3?q=%1").arg(m_passages.at(m_activePassage).passage());
  m_player->setMedia(QUrl(url));
  m_ui->m_sliderPlay->setMaximum(m_player->duration() / 500);
  m_player->setVolume(100);
  m_player->play();
}*/

void DictationSimulator::playPause() {
  if(m_play) {
    m_ui->m_btnPlayPause->setIcon(m_factory->fromTheme("player-play"));
    m_play = false;
    m_player->pause();
  }
  else {
    m_ui->m_btnPlayPause->setIcon(m_factory->fromTheme("player-pause"));
    m_play = true;
    m_player->play();
  }
}

void DictationSimulator::moveSlider(qint64 position) {
  //qDebug()<<position;
  /*if(position % 500 == 0) {
    m_ui->m_sliderPlay->setValue(position / 500);
  }*/
}

void DictationSimulator::playPassage() {
#if defined(Q_OS_OS2)
  if (SystemTrayIcon::isSystemTrayAvailable()) {
    qApp->trayIcon()->showMessage(tr("Cannot play sound"), tr("Sound cannot play on this platform."),
                                  QSystemTrayIcon::Warning);
  }
  else {
    CustomMessageBox::show(this, QMessageBox::Warning, tr("Cannot play sound"), tr("Sound cannot play on this platform."));
  }
#else
  // Play sound.
  QByteArray output;

  DictationPassage current_passage = m_passages.at(m_activePassage);

  if (current_passage.audioFilePath().isEmpty() || !QFile::exists(current_passage.audioFilePath())) {
    // Current passage does not contain downloaded audio file.
    QString passage = m_passages.at(m_activePassage).passage();//.replace(' ', '+');
    //QString passage = QUrl::toPercentEncoding(m_passages.at(m_activePassage).passage());
    QString url = QString("http://tts-api.com/tts.mp3?q=%1").arg(passage);
    QNetworkReply::NetworkError result_of_download = NetworkFactory::downloadFile(url, 10000, output);

    if (result_of_download != QNetworkReply::NoError) {
      // There was apparently some error.
      if (SystemTrayIcon::isSystemTrayAvailable()) {
        qApp->trayIcon()->showMessage(tr("Cannot play sound"), tr("Sound cannot play on this platform because sound file was not downloaded."),
                                      QSystemTrayIcon::Warning);
      }
      else {
        CustomMessageBox::show(this, QMessageBox::Warning, tr("Cannot play sound"), tr("Sound cannot play on this platform because sound file was not downloaded."));
      }

      return;
    }

    // Store downloaded sound file.
    QString sound_file_name = qApp->templateManager()->tempDirectory() + QDir::separator() +
                              "sound_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hhmmss") + ".mp3";
    QFile sound_file(sound_file_name);
    sound_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered);
    sound_file.write(output);
    sound_file.close();

    // We obtained new sound file for this particular passage.
    // So, store the path.
    // NOTE: Note that this is forgotten when new simulation is started.
    m_passages[m_activePassage].setAudioFilePath(sound_file_name);
  }
    
  m_player->setMedia(QUrl::fromLocalFile(m_passages.at(m_activePassage).audioFilePath()));
  m_player->setVolume(100);
  m_player->play();
  
  //IOFactory::playWaveFile(m_passages.at(m_activePassage).audioFilePath());
#endif
}

void DictationSimulator::submit() {
  
  QString passage_entered = m_ui->m_txtPassage->toPlainText().simplified();
  QString correct_passage = m_passages.at(m_activePassage).passage().simplified();
  QStringList entered_words = passage_entered.split(" ");
  QStringList correct_words = correct_passage.split(" ");
  
  m_ui->m_txtCorrectPassage->insertPlainText(correct_passage);
  
  QList<int> position;
  int pos = correct_passage.indexOf(" ");
  position << 0;
  
  while(pos != -1) {
    position << pos + 1;
    ////qDebug()<<pos+1;
    pos = correct_passage.indexOf(" ", pos + 1);
  }
  
  //position << correct_passage.size();
  
  QList<int> begin;
  QList<int> end;
  QStringList store_words;
  bool correct = true;
  //qDebug()<<"end.at(0) = "<<end.at(0);
  int j = 0, start;
  /*for (int i = 0; i < entered_words.size(); ++i) {
    //qDebug()<<"entered_words.at(i) = "<<entered_words.at(i)<<" correct_words.at(j) = "<<correct_words.at(j) ;
    if(entered_words.at(i) != correct_words.at(j) || !correct) {
      if (correct) {
        begin << position.at(j);
        //qDebug()<<"j="<<j<<" Begin = "<<position.at(j);
        start = j;
        correct = false;
      }
      store_words << correct_words.at(j);
      for (int k = 0; k < store_words.size(); ++k) {
        //qDebug()<<"store_words.at(k) "<<store_words.at(k)<<", entered_words.at(i) "<<entered_words.at(i);
        if(store_words.at(k) == entered_words.at(i)) {
          j = start + k;
          end << position.at(j);
          //qDebug()<<"j="<<j<<" start="<<start<<" end = "<<position.at(j);
          store_words.clear();
          correct = true;
          break;
        }
      }
        //store_words << correct_words.at(j);
    }
    j++;
  }
  */
  
  for (int i = 0; i < correct_words.size(); ++i) {
    if(j == entered_words.size()) {
      begin << position.at(i);
      correct = false;
      break; 
    }
    //qDebug()<<"correct_words.at(i) = "<<correct_words.at(i)<<" entered_words.at(j) = "<<entered_words.at(j) ;
    
    if(correct_words.at(i) != entered_words.at(j) || !correct) {
      if (correct) {
        begin << position.at(i);
        //qDebug()<<"i="<<j<<" Begin = "<<position.at(i);
        start = i;
        correct = false;
      }
      store_words << entered_words.at(j);
      for (int k = 0; k < store_words.size(); ++k) {
        //qDebug()<<"store_words.at(k) "<<store_words.at(k)<<", correct_words.at(i) "<<correct_words.at(i);
        if(store_words.at(k) == correct_words.at(i)) {
          j = start + k;
          end << position.at(i);
          //qDebug()<<"j="<<j<<" start="<<start<<" end = "<<position.at(i);
          store_words.clear();
          correct = true;
          break;
        }
      }
        //store_words << correct_words.at(j);
    }
    j++;
  }
  
  if (!correct)
    end << correct_passage.size() + 1;
  
  QTextCharFormat fmt;
  fmt.setBackground(Qt::red);

  //QVector<QTextCursor> cursor(begin.size(), m_ui->m_correctPassage->document());

  QList< QTextCursor > cursor;
  
  for(int i = 0; i < begin.size(); i++) {
    cursor << QTextCursor(m_ui->m_txtCorrectPassage->document());
    cursor[i].setPosition(begin.at(i), QTextCursor::MoveAnchor);
    cursor[i].setPosition(end.at(i) - 1, QTextCursor::KeepAnchor);
    cursor[i].setCharFormat(fmt);
  }
  
  m_ui->m_lblScore->setText(tr("Score - %1 of %2").arg(QString::number(correct_words.size() - begin.size()),
                                                       QString::number(correct_words.size())));
  
  m_ui->m_phoneWidget->setCurrentIndex(4);
}

void DictationSimulator::exit() {
  stopSimulation();
  emit simulationStopRequested();
}
