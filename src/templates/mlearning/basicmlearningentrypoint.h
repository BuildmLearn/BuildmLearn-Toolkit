#ifndef INFOENTRYPOINT_H
#define INFOENTRYPOINT_H

#include "core/templateentrypoint.h"


class TemplateFactory;

class BasicmLearningEntryPoint : public TemplateEntryPoint {
    Q_OBJECT

  public:
    explicit BasicmLearningEntryPoint(TemplateFactory *parent);
    virtual ~BasicmLearningEntryPoint();

    TemplateCore *createNewCore();
    TemplateCore *loadCoreFromRawData(const QString &raw_data);
};

#endif // INFOENTRYPOINT_H
