#include "gui/formsimulator.h"

#include "gui/formmain.h"
#include "definitions/definitions.h"
#include "miscellaneous/iconfactory.h"
#include "miscellaneous/application.h"
#include "miscellaneous/skinfactory.h"

#include <QCloseEvent>


FormSimulator::FormSimulator(FormMain* parent)
  : QDialog(parent), m_ui(new Ui::FormSimulator), m_mainWindow(parent) {
  m_ui->setupUi(this);

  // Do necessary initializations.
  setupIcons();
  setupPhoneWidget();

  // This window mustn't be deleted when closed by user.
  setAttribute(Qt::WA_DeleteOnClose, false);
}

FormSimulator::~FormSimulator() {
  delete m_ui;
}

void FormSimulator::setIsSticked(bool is_sticked) {
  m_isSticked = is_sticked;

  // Stick or unstick the window to main application window.
}

void FormSimulator::attachToParent() {
  QPoint main_window_position = m_mainWindow->pos();
  QSize main_window_size = m_mainWindow->size();

  resize(size().width(), main_window_size.height());
  move(main_window_position.x() + main_window_size.width() + 10,
       main_window_position.y());
}

void FormSimulator::setupPhoneWidget() {
  m_ui->m_phoneWidget->setFixedSize(SIMULATOR_WIDTH, SIMULATOR_HEIGHT);
  m_ui->m_phoneWidget->setStyleSheet(QString("background-image: url(%1)").arg(qApp->skinFactory()->currentSkin().m_simulatorBackgroundMain));

  setFixedWidth(SIMULATOR_WIDTH + 50);
}

void FormSimulator::closeEvent(QCloseEvent *e) {
  emit closed();
  e->accept();
}

void FormSimulator::setupIcons() {
  IconFactory *factory = IconFactory::instance();

  setWindowIcon(factory->fromTheme("view-simulator"));
  m_ui->m_btnGoBack->setIcon(factory->fromTheme("simulation-back"));
  m_ui->m_btnRunSimulation->setIcon(factory->fromTheme("simulation-run"));
}
