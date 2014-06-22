#ifndef QUIZITEM_H
#define QUIZITEM_H

#include <QWidget>

#include "ui_quizitem.h"

#include "templates/quiz/quizquestion.h"


namespace Ui {
  class QuizItem;
}

class QuizItem : public QWidget {
    Q_OBJECT

  public:
    // Contructors and destructors.
    explicit QuizItem(QWidget *parent = 0);
    virtual ~QuizItem();

    void setQuestion(const QuizQuestion &question, int question_number);

  private:
    Ui::QuizItem *m_ui;
    QuizQuestion m_question;
    QList<QRadioButton*> m_answerButtons;
};

#endif // QUIZITEM_H
