#ifndef WEBFACTORY_H
#define WEBFACTORY_H

#include <QObject>
#include <QPointer>
#include <QMap>


class QWebSettings;

class WebFactory : public QObject {
    Q_OBJECT

  public:
    // Destructor.
    virtual ~WebFactory();

    // Singleton getter.
    static WebFactory *instance();

  public slots:
    // Opens given string URL in external browser.
    bool openUrlInExternalBrowser(const QString &url);

  private:
    // Constructor.
    explicit WebFactory(QObject *parent = 0);

    // Singleton.
    static QPointer<WebFactory> s_instance;
};

#endif // WEBFACTORY_H
