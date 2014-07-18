#ifndef LEARNSPELLINGSENTRYPOINT_H
#define LEARNSPELLINGSENTRYPOINT_H

#include "core/templateentrypoint.h"


class TemplateFactory;
class TemplateCore;

class LearnSpellingsEntryPoint : public TemplateEntryPoint {
    Q_OBJECT

  public:
    explicit LearnSpellingsEntryPoint(TemplateFactory *parent);
    virtual ~LearnSpellingsEntryPoint();

    TemplateCore *createNewCore();
    TemplateCore *loadCoreFromBundleData(const QString &raw_data);
};

#endif // LEARNSPELLINGSENTRYPOINT_H
