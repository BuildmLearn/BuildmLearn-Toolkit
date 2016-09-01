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

#include "templates/comprehension/comprehensionquestion.h"

#include <QStringList>


ComprehensionQuestion::ComprehensionQuestion() {
  m_answers = QStringList();
  m_answers << QString() << QString() << QString() << QString();
}

ComprehensionQuestion::~ComprehensionQuestion() {
}

int ComprehensionQuestion::correctAnswer() const {
  return m_correctAnswer;
}

void ComprehensionQuestion::setCorrectAnswer(int correctAnswer) {
  m_correctAnswer = correctAnswer;
}

void ComprehensionQuestion::setAnswer(int index, const QString &answer) {
  if (index >= 0 && index < 4) {
    m_answers.replace(index, answer);
  }
}

QString ComprehensionQuestion::answerOne() const {
  return m_answers.at(0);
}

QString ComprehensionQuestion::answerTwo() const {
  return m_answers.at(1);
}

QString ComprehensionQuestion::answerThree() const {
  return m_answers.at(2);
}

QString ComprehensionQuestion::answerFour() const {
  return m_answers.at(3);
}

QString ComprehensionQuestion::question() const {
  return m_question;
}

void ComprehensionQuestion::setQuestion(const QString &question) {
  m_question = question;
}
