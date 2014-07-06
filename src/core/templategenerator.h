#ifndef TEMPLATEGENERATOR_H
#define TEMPLATEGENERATOR_H

#include <QObject>


class TemplateCore;

class TemplateGenerator : public QObject {
    Q_OBJECT

  public:
    explicit TemplateGenerator(QObject *parent = 0);
    virtual ~TemplateGenerator();

  public slots:
    bool generateMobileApplication(TemplateCore *core);

  signals:
    void generationStarted();
    void generationFinished(int result_code, const QString &output_file = QString());
    void generationProgress(int result_code, const QString &message);
};

#endif // TEMPLATEGENERATOR_H
