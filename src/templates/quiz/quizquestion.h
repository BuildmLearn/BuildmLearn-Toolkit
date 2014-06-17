#ifndef QUIZQUESTION_H
#define QUIZQUESTION_H

#include <QMetaType>


class QuizQuestion {
  public:
    explicit QuizQuestion();
    virtual ~QuizQuestion();

    int correctAnswer() const;
    void setCorrectAnswer(int correctAnswer);

    QString answerOne() const;
    void setAnswerOne(const QString &answerOne);

    QString answerTwo() const;
    void setAnswerTwo(const QString &answerTwo);

    QString answerThree() const;
    void setAnswerThree(const QString &answerThree);

    QString answerFour() const;
    void setAnswerFour(const QString &answerFour);

    QString question() const;
    void setQuestion(const QString &question);

  private:
    QString m_question;
    QString m_answerOne;
    QString m_answerTwo;
    QString m_answerThree;
    QString m_answerFour;
    int m_correctAnswer;
};

Q_DECLARE_METATYPE(QuizQuestion);

#endif // QUIZQUESTION_H
