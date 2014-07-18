#ifndef LEARNSPELLINGSITEM_H
#define LEARNSPELLINGSITEM_H

#include <QString>
#include <QMetaType>


class LearnSpellingsItem {
  public:
    explicit LearnSpellingsItem();
    virtual ~LearnSpellingsItem();

    QString word() const;
    void setWord(const QString &word);

    QString meaning() const;
    void setMeaning(const QString &meaning);

  private:
    QString m_word;
    QString m_meaning;
};

Q_DECLARE_METATYPE(LearnSpellingsItem)

#endif // LEARNSPELLINGSITEM_H
