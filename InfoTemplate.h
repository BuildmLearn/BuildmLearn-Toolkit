#ifndef INFOTEMPLATE_H
#define INFOTEMPLATE_H

#include <QtGui>



class InfoTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit InfoTemplate(QWidget *parent = 0);

public slots:
    void on_addButton_cicked();
    void on_removedButton_cicked();
    void on_itemList_selected();

    void on_textEdit_textChanged();

    void on_itemList_phone_selected();
    void on_backButton_clicked();
    void on_generateButton_clicked();

    void execWindowsCommand(QString);
    void execWindowsCommandDetached(QString);

private:
    QWidget* widget1;
    QWidget* widget2;
    QWidget* widget3;
    QWidget* mainWidget;

    // for widget 1
    QListWidget* itemList;
    QPushButton* addButton;
    QPushButton* removeButton;
    QLineEdit* lineEdit;

    // for widget 2
    QPlainTextEdit* textEdit;

    // for widget 3
    QStackedWidget* phoneWidget;
    QWidget* screen1;
    QWidget* screen2;
    QListWidget* itemList_phone;
    QLabel* textLabel_phone;
    QPushButton* backButton;
    QPushButton* generateButton;

    QLabel* phoneBody;
    QLabel* phoneHeader;
    QLabel* phoneFooter;
    QLabel* phoneLeft;
    QLabel* phoneRight;


    QProcess* iProcess;

    // Menus
    QMenu *fileMenu;
    QMenu *projectMenu;
    QMenu *helpMenu;

    // Action
    QAction *newAct;
    QAction *exitAct;
    QAction *buildAct;
    QAction *howitworksAct;
    QAction *aboutAct;

    // Other widgets
//    NewProjectWidget *newProject;

    // Engine
    QStringList iTitleList;
    QStringList iDescriptionList;


};

#endif // INFOTEMPLATE_H
