#ifndef LEARNSPELLINGSCORE_H
#define LEARNSPELLINGSCORE_H

#include "core/templatecore.h"


class TemplateEntryPoint;
class LearnSpellingsEditor;
class LearnSpellingsSimulator;

class LearnSpellingsCore : public TemplateCore {
    Q_OBJECT

  public:
    explicit LearnSpellingsCore(TemplateEntryPoint *entry_point, QObject *parent = 0);
    virtual ~LearnSpellingsCore();

    GenerationResult generateMobileApplication(QString &output_file);
    void launch();

  private:
    LearnSpellingsEditor *learnSpellingsEditor();
    LearnSpellingsSimulator *learnSpellingsSimulator();
};

#endif // LEARNSPELLINGSCORE_H
