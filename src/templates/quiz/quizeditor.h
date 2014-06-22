#ifndef QUIZEDITOR_H
#define QUIZEDITOR_H

#include "core/templateeditor.h"

#include "ui_quizeditor.h"
#include "templates/quiz/quizquestion.h"

#include <QIcon>


namespace Ui {
  class QuizEditor;
}

class QuizEditor : public TemplateEditor {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit QuizEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~QuizEditor();

    bool canGenerateApplications();
    void launch();

    /// \brief Access to list of added questions.
    /// \return Returns list of added questions.
    QList<QuizQuestion> activeQuestions() const;

  private slots:
    void addQuestion();
    void loadQuestion(int index);
    void removeQuestion();
    void saveQuestion();
    void moveQuestionUp();
    void moveQuestionDown();

    void configureUpDown();
    void setEditorsEnabled(bool enabled);

    void updateNameStatus();
    void updateAuthorStatus();

  private:
    QuizQuestion m_activeQuestion;
    Ui::QuizEditor *m_ui;
    QIcon m_iconYes;
    QIcon m_iconNo;
};

#endif // QUIZEDITOR_H
