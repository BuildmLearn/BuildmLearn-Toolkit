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
    enum State {
      Unanswered,
      AnsweredCorrectly,
      AnsweredWrongly
    };

    // Contructors and destructors.
    explicit QuizItem(QWidget *parent = 0);
    virtual ~QuizItem();

    /// \brief Sets new question for this widget.
    /// \param question Question object.
    /// \param question_number Number of the question.
    void setQuestion(const QuizQuestion &question, int question_number);

    /// \brief Access to state of quiz question widget.
    /// \return Returns the state of quiz question widget.
    State state() const;

    void reset();

  signals:
    /// \brief Emitted if users clicks "Next" or "Submit"
    void questionSubmitted();

  private slots:
    void onNextClicked();
    void onSubmitClicked();

  private:
    void setupButtons();
    void createConnections();
    void clearStylesheets();

  private:
    State m_state;
    Ui::QuizItem *m_ui;
    QuizQuestion m_question;
    QList<QRadioButton*> m_answerButtons;
};

#endif // QUIZITEM_H
