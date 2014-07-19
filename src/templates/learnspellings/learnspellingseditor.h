#ifndef LEARNSPELLINGSEDITOR_H
#define LEARNSPELLINGSEDITOR_H

#include "core/templateeditor.h"

#include "ui_learnspellingseditor.h"
#include "templates/learnspellings/learnspellingsitem.h"


namespace Ui {
  class LearnSpellingsEditor;
}

class LearnSpellingsEditor : public TemplateEditor {
    Q_OBJECT

    friend class LearnSpellingsSimulator;

  public:
    explicit LearnSpellingsEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~LearnSpellingsEditor();

    QList<LearnSpellingsItem> activeItems() const;

    QString generateBundleData();
    bool loadBundleData(const QString &bundle_data);
    bool canGenerateApplications();
    void launch();

  private slots:
    void addNewItem(const QString &title, const QString &description);
    void addNewItem();
    void removeSelectedItem();
    void saveItem();
    void displayItem(int index);
    void checkTitle(const QString &title);
    void checkDescription(const QString &description);
    void moveItemUp();
    void moveItemDown();
    void configureUpDown();
    void updateItemCount();
    void checkAuthor();
    void checkName();
    void onAuthorChanged(const QString &new_author);
    void onNameChanged(const QString &new_name);

  private:
    void setEditorsEnabled(bool enabled);

  private:
    Ui::LearnSpellingsEditor *m_ui;
    LearnSpellingsItem m_activeItem;
};



#endif // LEARNSPELLINGSEDITOR_H
