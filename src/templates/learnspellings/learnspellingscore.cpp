#include "templates/learnspellings/learnspellingscore.h"

#include "templates/learnspellings/learnspellingseditor.h"
#include "templates/learnspellings/learnspellingssimulator.h"


LearnSpellingsCore::LearnSpellingsCore(TemplateEntryPoint *entry_point, QObject *parent)
  : TemplateCore(entry_point, parent) {
  m_editor = new LearnSpellingsEditor(this);
  m_simulator = new LearnSpellingsSimulator(this);
}

LearnSpellingsCore::~LearnSpellingsCore() {
}

TemplateCore::GenerationResult LearnSpellingsCore::generateMobileApplication(QString &output_file) {
  return Success;
}

void LearnSpellingsCore::launch() {
  learnSpellingsEditor()->launch();
  //learnSpellingsSimulator()->launch();
}

LearnSpellingsEditor *LearnSpellingsCore::learnSpellingsEditor() {
  return static_cast<LearnSpellingsEditor*>(editor());
}

LearnSpellingsSimulator *LearnSpellingsCore::learnSpellingsSimulator() {
  return static_cast<LearnSpellingsSimulator*>(simulator());
}
