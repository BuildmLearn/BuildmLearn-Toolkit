#ifndef INFOENTRYPOINT_H
#define INFOENTRYPOINT_H

#include "core/templateentrypoint.h"


class TemplateFactory;

class InfoEntryPoint : public TemplateEntryPoint {
    Q_OBJECT

  public:
    explicit InfoEntryPoint(TemplateFactory *parent);
    virtual ~InfoEntryPoint();

    TemplateCore *createNewCore();
    TemplateCore *loadCoreFromRawData(const QString &raw_data);
};

#endif // INFOENTRYPOINT_H
