#ifndef TEMPLATEGENERATOR_H
#define TEMPLATEGENERATOR_H

#include <QObject>

#include "core/templatecore.h"


class TemplateGenerator : public QObject {
    Q_OBJECT

  public:
    explicit TemplateGenerator(QObject *parent = 0);
    virtual ~TemplateGenerator();

  public slots:
    void generateMobileApplication(TemplateCore *core);

  signals:
    void generationStarted();
    void generationFinished(TemplateCore::GenerationResult result_code, const QString &output_file = QString());
    void generationProgress(int progress, const QString &message);
};

#endif // TEMPLATEGENERATOR_H
