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

  private slots:
    void addQuestion();
    void loadQuestion(int index);
    void removeQuestion();
    void saveQuestion();

    void setEditorsEnabled(bool enabled);

  private:
    QuizQuestion m_activeQuestion;
    Ui::QuizEditor *m_ui;
    QIcon m_iconYes;
    QIcon m_iconNo;
};

#endif // QUIZEDITOR_H
