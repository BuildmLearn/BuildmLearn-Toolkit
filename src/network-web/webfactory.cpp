#include "network-web/webfactory.h"

#include "definitions/definitions.h"
#include "miscellaneous/settings.h"
#include "miscellaneous/application.h"

#include <QRegExp>
#include <QProcess>
#include <QUrl>
#include <QDesktopServices>


QPointer<WebFactory> WebFactory::s_instance;

WebFactory::WebFactory(QObject *parent)
  : QObject(parent) {
}

WebFactory::~WebFactory() {
  qDebug("Destroying WebFactory instance.");
}

bool WebFactory::openUrlInExternalBrowser(const QString &url) {
  if (qApp->settings()->value(APP_CFG_BROWSER,
                              "custom_external_browser",
                              false).toBool()) {
    QString browser = qApp->settings()->value(APP_CFG_BROWSER,
                                              "external_browser_executable").toString();
    QString arguments = qApp->settings()->value(APP_CFG_BROWSER,
                                                "external_browser_arguments",
                                                "%1").toString();

    return QProcess::startDetached(browser, QStringList() << arguments.arg(url));
  }
  else {
    return QDesktopServices::openUrl(url);
  }
}

WebFactory *WebFactory::instance() {
  if (s_instance.isNull()) {
    s_instance = new WebFactory(qApp);
  }

  return s_instance;
}
