#ifndef QUIZSIMULATOR_H
#define QUIZSIMULATOR_H

#include "core/templatesimulator.h"

#include "ui_quizsimulator.h"


namespace Ui {
  class QuizSimulator;
}

class TemplateCore;

class QuizSimulator : public TemplateSimulator {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit QuizSimulator(TemplateCore *core, QWidget *parent = 0);
    virtual ~QuizSimulator();

    bool startSimulation();
    bool stopSimulation();
    bool canGoBack();
    bool goBack();

  private:
    Ui::QuizSimulator *m_ui;
};

#endif // QUIZSIMULATOR_H
