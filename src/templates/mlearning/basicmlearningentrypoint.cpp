#include "templates/mlearning/basicmlearningentrypoint.h"

#include "core/templatefactory.h"


BasicmLearningEntryPoint::BasicmLearningEntryPoint(TemplateFactory *parent) : TemplateEntryPoint(parent) {
  m_baseFolder = "mlearning";
  m_description = "This is simple template for displaying clickable lists of textual information.";
  m_humanName = "Basic mLearning";
  m_name = "mlearning";
  m_thumbnailImage = "thumbnail.png";
  m_typeIndentifier = "InfoTemplate";
}

BasicmLearningEntryPoint::~BasicmLearningEntryPoint() {
}

TemplateCore *BasicmLearningEntryPoint::createNewCore() {
  return NULL;
}

TemplateCore *BasicmLearningEntryPoint::loadCoreFromRawData(const QString &raw_data) {
  return NULL;
}
