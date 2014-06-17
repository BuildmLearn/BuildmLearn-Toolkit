#include "templates/quiz/quizquestion.h"


QuizQuestion::QuizQuestion() {
}

QuizQuestion::~QuizQuestion() {
}

int QuizQuestion::correctAnswer() const {
  return m_correctAnswer;
}

void QuizQuestion::setCorrectAnswer(int correctAnswer) {
  m_correctAnswer = correctAnswer;
}

QString QuizQuestion::answerOne() const {
  return m_answerOne;
}

void QuizQuestion::setAnswerOne(const QString &answerOne) {
  m_answerOne = answerOne;
}

QString QuizQuestion::answerTwo() const {
  return m_answerTwo;
}

void QuizQuestion::setAnswerTwo(const QString &answerTwo) {
  m_answerTwo = answerTwo;
}

QString QuizQuestion::answerThree() const {
  return m_answerThree;
}

void QuizQuestion::setAnswerThree(const QString &answerThree) {
  m_answerThree = answerThree;
}

QString QuizQuestion::answerFour() const {
  return m_answerFour;
}

void QuizQuestion::setAnswerFour(const QString &answerFour) {
  m_answerFour = answerFour;
}

QString QuizQuestion::question() const {
  return m_question;
}

void QuizQuestion::setQuestion(const QString &question) {
  m_question = question;
}

