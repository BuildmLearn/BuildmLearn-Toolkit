#include "templates/learnspellings/learnspellingsentrypoint.h"

#include "templates/learnspellings/learnspellingscore.h"


LearnSpellingsEntryPoint::LearnSpellingsEntryPoint(TemplateFactory *parent) : TemplateEntryPoint(parent) {
  m_baseFolder = "learnspellings";
  m_description = "This is simple template for learning spelling of words.";
  m_humanName = "Learn Spelling";
  m_name = "learnspellings";
  m_thumbnailImage = "thumbnail.png";
  m_typeIndentifier = "SpellingTemplate";
  m_mobileApplicationApkFile = "LearnSpellingsApp.apk";
}

LearnSpellingsEntryPoint::~LearnSpellingsEntryPoint() {
}

TemplateCore *LearnSpellingsEntryPoint::createNewCore() {
  return new LearnSpellingsCore(this, this);
}

TemplateCore *LearnSpellingsEntryPoint::loadCoreFromBundleData(const QString &raw_data) {
  return NULL;
}
