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

  public:
    // Constructors and destructors.
    explicit FormSimulator(FormMain *parent = 0);
    virtual ~FormSimulator();

    void saveState();

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

  private:
    void setupPhoneWidget();
    void setupIcons();

  private:
    Ui::FormSimulator *m_ui;
    FormMain *m_mainWindow;
    bool m_isVisibleOnStartup;
    bool m_isSticked;
    bool m_isActive;
    // TODO: Tady možná dát TemplateCore a z něj ten simulator tahat
    // skrz volani startSimulation(...), nebo dat do TemplateSimulator
    // pointer na TemplateCore.
    TemplateSimulator *m_activeSimulation;
};

#endif // FORMSIMULATOR_H
