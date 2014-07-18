#include "templates/learnspellings/learnspellingsitem.h"


LearnSpellingsItem::LearnSpellingsItem() {
}

LearnSpellingsItem::~LearnSpellingsItem() {
}

QString LearnSpellingsItem::word() const {
  return m_word;
}

void LearnSpellingsItem::setWord(const QString &word) {
  m_word = word;
}

QString LearnSpellingsItem::meaning() const {
  return m_meaning;
}

void LearnSpellingsItem::setMeaning(const QString &meaning) {
  m_meaning = meaning;
}
