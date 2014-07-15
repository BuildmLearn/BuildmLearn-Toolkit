#ifndef FORMSIMULATOR_H
#define FORMSIMULATOR_H

#include <QDialog>

#include "ui_formsimulator.h"


namespace Ui {
  class FormSimulator;
}

class FormMain;
class TemplateSimulator;
class QCloseEvent;

/// \brief Separate window which contains active simulator.
/// \remarks This window can be sticked to main window.
class FormSimulator : public QDialog {
    Q_OBJECT

    friend class FormMain;

  public:
    // Constructors and destructors.
    explicit FormSimulator(FormMain *parent = 0);
    virtual ~FormSimulator();

    /// \brief Saves size & position for the window into settings.
    void saveState();

    /// \brief Loads size & position for the window from settings.
    void loadState();

    /// \brief Indicates whether simulator window is sticked to
    /// main window or not.
    /// \return Returns true if window is sticked
    /// or false when it is not.
    inline bool isSticked() const {
      return m_isSticked;
    }

    /// \brief Indicates whether simulator window should be shown
    /// when application launches.
    inline bool isVisibleOnStartup() const {
      return m_isVisibleOnStartup;
    }

    /// \brief Sets new active simulation widget.
    /// \param simulation New active simulation widget.
    /// \remarks This instance of FormSimulator takes ownership
    /// of added simulation editors. When this method is called
    /// and there is already some editor set, then this editor
    /// is deleted.
    void setActiveSimulation(TemplateSimulator *simulation);

  public slots:
    /// \brief Takes active simulation one step back.
    ///
    /// This simply calls TemplateSimulator::goBack().
    void goBack();

    /// \brief Starts active simulation.
    ///
    /// This simply calls TemplateSimulator::startSimulation().
    void startSimulation();

    /// \brief Stops active simulation.
    ///
    /// This simply calls TemplateSimulator::stopSimulation().
    void stopSimulation();

    /// \brief Conditionally sticks simulator window to its parent.
    /// \remarks Depends on settings.
    void conditionallyAttachToParent();

    /// \brief Forces this window to align itself next to its parent window.
    void attachToParent();

    /// \brief Allows window to be unattached and allows vertical resize policy.
    void unAttachFromParent();

    /// \brief Sticks or unsticks window.
    /// \param is_sticked Do we want to stick window?
    void setIsSticked(bool is_sticked);

    /// \brief Displays simulator window.
    void show();

  protected:
    /// \brief Executed when simulator window is closed.
    /// \param e Event argument.
    void closeEvent(QCloseEvent *e);

  signals:
    /// \brief Emitted when simulator window is closed.
    void closed();

    /// \brief Emitted if "stop" feature for active simulation is changed, in other
    /// words, if simulation is started/stopped.
    void stopEnableChanged(bool enabled);

  private:
    void setupPhoneWidget();
    void setupIcons();

  private:
    Ui::FormSimulator *m_ui;
    FormMain *m_mainWindow;
    bool m_isVisibleOnStartup;
    bool m_isSticked;
    bool m_isActive;
    TemplateSimulator *m_activeSimulation;
};

#endif // FORMSIMULATOR_H
