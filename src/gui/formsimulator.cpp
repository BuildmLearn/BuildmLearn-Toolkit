#include "gui/formsimulator.h"

#include "gui/formmain.h"
#include "definitions/definitions.h"
#include "miscellaneous/iconfactory.h"
#include "miscellaneous/application.h"
#include "miscellaneous/skinfactory.h"
#include "core/templatesimulator.h"
#include "core/templatecore.h"
#include "core/templateeditor.h"

#include <QWidget>
#include <QCloseEvent>


FormSimulator::FormSimulator(FormMain* parent)
  : QDialog(parent), m_ui(new Ui::FormSimulator), m_mainWindow(parent), m_isActive(false), m_activeSimulation(NULL) {
  m_ui->setupUi(this);

  // Load some needed settings.
  m_isVisibleOnStartup = qApp->settings()->value(APP_CFG_SIMULATOR, "visible_on_startup", false).toBool();
  m_isSticked = qApp->settings()->value(APP_CFG_SIMULATOR, "is_sticked", false).toBool();

  // Do necessary initializations.
  setupIcons();
  setupPhoneWidget();

  connect(parent, SIGNAL(moved()), this, SLOT(conditionallyAttachToParent()));
  connect(parent, SIGNAL(resized()), this, SLOT(conditionallyAttachToParent()));
  connect(m_ui->m_btnRunSimulation, SIGNAL(clicked()), this, SLOT(startSimulation()));
  connect(m_ui->m_btnStopSimulation, SIGNAL(clicked()), this, SLOT(stopSimulation()));
  connect(m_ui->m_btnGoBack, SIGNAL(clicked()), this, SLOT(goBack()));
  connect(this, SIGNAL(stopEnableChanged(bool)), m_ui->m_btnStopSimulation, SLOT(setEnabled(bool)));

  // This window mustn't be deleted when closed by user.
  setAttribute(Qt::WA_DeleteOnClose, false);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

FormSimulator::~FormSimulator() {
  delete m_ui;
}

void FormSimulator::saveState() {
  qApp->settings()->setValue(APP_CFG_SIMULATOR, "visible_on_startup", m_isActive);

  if (!m_isSticked) {
    qApp->settings()->setValue(APP_CFG_SIMULATOR, "position", pos());
    qApp->settings()->setValue(APP_CFG_SIMULATOR, "height", height());
  }
}

void FormSimulator::loadState() {
  if (!m_isSticked) {
    move(qApp->settings()->value(APP_CFG_SIMULATOR, "position", pos()).toPoint());
    resize(width(), qApp->settings()->value(APP_CFG_SIMULATOR, "height", height()).toInt());
  }
}

void FormSimulator::setActiveSimulation(TemplateSimulator *simulation) {
  if (m_activeSimulation != NULL) {
    // There is existing simulator widget, remove it.
    m_activeSimulation->close();
    m_activeSimulation->deleteLater();
    m_activeSimulation = NULL;
  }

  // Assign new simulation and display its initial state.
  m_activeSimulation = simulation;
  m_activeSimulation->setParent(m_ui->m_phoneWidget);
  m_activeSimulation->setGeometry(SIMULATOR_CONTENTS_OFFSET_X, SIMULATOR_CONTENTS_OFFSET_Y,
                                  SIMULATOR_CONTENTS_WIDTH, SIMULATOR_CONTENTS_HEIGHT);
  m_activeSimulation->show();

  // Make necessary connections which are meant for simulator window.
  connect(m_activeSimulation, SIGNAL(canGoBackChanged(bool)), m_ui->m_btnGoBack, SLOT(setEnabled(bool)));
  connect(m_activeSimulation, SIGNAL(simulationStopRequested()), m_ui->m_btnStopSimulation, SLOT(click()));
  connect(m_activeSimulation->core()->editor(), SIGNAL(canGenerateChanged(bool)), m_ui->m_btnRunSimulation, SLOT(setEnabled(bool)));

  emit stopEnableChanged(false);
}

void FormSimulator::goBack() {
  if (m_activeSimulation != NULL) {
    m_activeSimulation->goBack();
  }
}

void FormSimulator::startSimulation() {
  if (m_activeSimulation != NULL) {
    if (m_activeSimulation->startSimulation()) {
      emit stopEnableChanged(true);
    }
  }
}

void FormSimulator::stopSimulation() {
  if (m_activeSimulation != NULL) {
    if (m_activeSimulation->stopSimulation()) {
      emit stopEnableChanged(false);
    }
  }
}

void FormSimulator::conditionallyAttachToParent() {
  if (m_isSticked) {
    attachToParent();
  }
}

void FormSimulator::setIsSticked(bool is_sticked) {
  if (is_sticked && !m_isSticked) {
    attachToParent();
  }
  else if (!is_sticked && m_isSticked) {
    unAttachFromParent();
  }

  m_isSticked = is_sticked;

  qApp->settings()->setValue(APP_CFG_SIMULATOR, "is_sticked", is_sticked);
}

void FormSimulator::show() {
  m_isActive = true;

  conditionallyAttachToParent();
  QDialog::show();
}

void FormSimulator::attachToParent() {
  QPoint main_window_position = m_mainWindow->pos();
  QSize main_window_size = m_mainWindow->size();

  setFixedHeight(main_window_size.height());
  //resize(size().width(), main_window_size.height());

  move(main_window_position.x() + main_window_size.width() + SIMULATOR_OFFSET,
       main_window_position.y());
}

void FormSimulator::unAttachFromParent() {
  QPoint main_window_position = m_mainWindow->pos();
  QSize main_window_size = m_mainWindow->size();

  setMinimumHeight(SIMULATOR_HEIGHT_MIN);
  setMaximumHeight(SIMULATOR_HEIGHT_MAX);

  move(main_window_position.x() + main_window_size.width() + SIMULATOR_WIDTH_OFFSET,
       main_window_position.y());
}

void FormSimulator::setupPhoneWidget() {
  m_ui->m_phoneWidget->setFixedSize(SIMULATOR_WIDTH, SIMULATOR_HEIGHT_DEFAULT);
  m_ui->m_phoneWidget->setPixmap(QPixmap(qApp->skinFactory()->currentSkin().m_simulatorBackgroundMain));

  setFixedWidth(SIMULATOR_WIDTH + SIMULATOR_WIDTH_OFFSET);
}

void FormSimulator::closeEvent(QCloseEvent *e) {
  m_isActive = false;

  emit closed();
  e->accept();
}

void FormSimulator::setupIcons() {
  IconFactory *factory = IconFactory::instance();

  setWindowIcon(factory->fromTheme("view-simulator"));
  m_ui->m_btnStopSimulation->setIcon(factory->fromTheme("simulation-stop"));
  m_ui->m_btnGoBack->setIcon(factory->fromTheme("simulation-back"));
  m_ui->m_btnRunSimulation->setIcon(factory->fromTheme("simulation-run"));
}
