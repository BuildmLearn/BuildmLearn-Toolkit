#ifndef LEARNSPELLINGSSIMULATOR_H
#define LEARNSPELLINGSSIMULATOR_H

#include "core/templatesimulator.h"

#include "ui_learnspellingssimulator.h"


namespace Ui {
  class LearnSpellingsSimulator;
}

class LearnSpellingsSimulator : public TemplateSimulator {
    Q_OBJECT

  public:
    explicit LearnSpellingsSimulator(TemplateCore *core, QWidget *parent = 0);
    virtual ~LearnSpellingsSimulator();

  public slots:
    bool startSimulation();
    bool stopSimulation();
    bool goBack();
    void launch();

  private slots:
    void start();
    void restart();
    void exit();
    void playWord();
    void nextWord();

  private:
    Ui::LearnSpellingsSimulator *m_ui;
};

#endif // LEARNSPELLINGSSIMULATOR_H
