#ifndef QuizTemplate_H
#define QuizTemplate_H

#include <QtGui>
#include "QuestionItem.h"

class QuizTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit QuizTemplate(QWidget *parent = 0);

public slots:
    void on_addButton_cicked();
//    void on_removedButton_cicked();
//    void on_itemList_selected();

//    void on_textEdit_textChanged();

//    void on_itemList_phone_selected();
//    void on_backButton_clicked();
    void on_generateButton_clicked();

    void execWindowsCommand(QString);
    void execWindowsCommandDetached(QString);

    void removeQuestion(int);
    void optionAdded();
    void startSimulaton_clicked();

    void startQuiz();
    void populateQuiz(int);

    void submitButton_phone_clicked();
    int getSelectedOption();

    void updateStartPage_phone();
private:
    QWidget* widget1;
    QWidget* widget2;
    QWidget* widget3;
    QWidget* mainWidget;

    // for widget 1
    QPushButton* addButton;
    QTextEdit* questionEdit;
    QLineEdit* option1Edit;
    QLineEdit* option2Edit;
    QLineEdit* option3Edit;
    QLineEdit* option4Edit;
    QLabel* questionLabel;
    QLabel* optionsLabel;
    QLabel* correctAnserLabel;
    QComboBox* comboBox;


    // for widget 2
    QPlainTextEdit* textEdit;
    QListWidget* iQuestionList;
    QScrollArea* iScrollArea;
    QVBoxLayout* widget2_vlayout;

    // for widget 3
    QStackedWidget* phoneWidget;
    QWidget* screen1;
    QWidget* screen2;
    QWidget* screen3;

    QLabel* quizNameLabel_phone;
    QLabel* quizAuthorLabel_phone;
    QPushButton* startQuiz_phone;

    QLabel* questionLabel_phone;
    QLabel* questionText_phone;
    QRadioButton* option1_phone;
    QRadioButton* option2_phone;
    QRadioButton* option3_phone;
    QRadioButton* option4_phone;
    QList<QRadioButton*> optionsList_phone;
    QPushButton* submitButton_phone;
    QPushButton* backButton;
    QPushButton* generateButton;


    QLabel* phoneBody;
    QLabel* phoneHeader;
    QLabel* phoneFooter;
    QLabel* phoneLeft;
    QLabel* phoneRight;
    QPushButton* startSimulation;

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

    int noOfQues;


    int questionCounter;
    int rightAnswer;

    // Engine
    QStringList iQuestionTextList;
    QStringList iOptionsList;
    QList<int> iAnsList;
    QList<QuestionItem*> iQuestionItemList;
public:
    QString quizName;
    QString authorName;
};

#endif // QuizTemplate_H
