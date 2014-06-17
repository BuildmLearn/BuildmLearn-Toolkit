#ifndef QUIZEDITOR_H
#define QUIZEDITOR_H

#include "core/templateeditor.h"

#include "ui_quizeditor.h"


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
    Ui::QuizEditor *m_ui;
};

#endif // QUIZEDITOR_H
