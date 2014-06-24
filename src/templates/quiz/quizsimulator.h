#ifndef QUIZSIMULATOR_H
#define QUIZSIMULATOR_H

#include "core/templatesimulator.h"

#include "ui_quizsimulator.h"


namespace Ui {
  class QuizSimulator;
}

class TemplateCore;
class QLabel;
class QPushButton;
class QRadioButton;

class QuizSimulator : public TemplateSimulator {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit QuizSimulator(TemplateCore *core, QWidget *parent = 0);
    virtual ~QuizSimulator();

    bool startSimulation();
    bool stopSimulation();
    void launch();

    /// \brief Indicates whether user can go back in simulation.
    /// \warning This template does not support going back.
    /// \return Returns always false.
    bool canGoBack();
    bool goBack();

  private slots:
    void start();
    void prepareSummary();
    void questionSubmitted();
    void restart();

  private:
    Ui::QuizSimulator *m_ui;
};

#endif // QUIZSIMULATOR_H
