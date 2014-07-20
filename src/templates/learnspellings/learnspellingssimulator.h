#ifndef LEARNSPELLINGSSIMULATOR_H
#define LEARNSPELLINGSSIMULATOR_H

#include "core/templatesimulator.h"

#include "ui_learnspellingssimulator.h"
#include "templates/learnspellings/learnspellingsitem.h"


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
    void skipThisWord();
    void spellThisWord();
    void loadNextWord();

  private:
    Ui::LearnSpellingsSimulator *m_ui;
    QList<LearnSpellingsItem> m_words;
    int m_activeWord;
    int m_resultCorrect;
    int m_resultIncorrect;
    int m_resultSkipped;
};

#endif // LEARNSPELLINGSSIMULATOR_H
