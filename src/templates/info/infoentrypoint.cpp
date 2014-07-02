#include "templates/info/infoentrypoint.h"

#include "core/templatefactory.h"


InfoEntryPoint::InfoEntryPoint(TemplateFactory *parent) : TemplateEntryPoint(parent) {
}


InfoEntryPoint::~InfoEntryPoint() {

}


TemplateCore *InfoEntryPoint::createNewCore() {
  return NULL;
}

TemplateCore *InfoEntryPoint::loadCoreFromRawData(const QString &raw_data) {
  return NULL;
}
