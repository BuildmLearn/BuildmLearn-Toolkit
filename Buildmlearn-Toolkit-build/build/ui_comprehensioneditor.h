/********************************************************************************
** Form generated from reading UI file 'comprehensioneditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPREHENSIONEDITOR_H
#define UI_COMPREHENSIONEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "lineeditwithstatus.h"
#include "maxlengthtextedit.h"
#include "plaintoolbutton.h"

QT_BEGIN_NAMESPACE

class Ui_ComprehensionEditor
{
public:
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    LineEditWithStatus *m_txtAuthor;
    QLabel *label_4;
    LineEditWithStatus *m_txtName;
    QLabel *label_5;
    LineEditWithStatus *m_txtNumberOfQuestions;
    QGroupBox *groupBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *m_groupPassageEditor;
    QGridLayout *gridLayout1;
    QLabel *label_7;
    MaxLengthTextEdit *m_txtPassage;
    QWidget *tab_2;
    QGroupBox *m_groupQuestionEditor;
    QGridLayout *gridLayout2;
    QLabel *label_2;
    MaxLengthTextEdit *m_txtQuestion;
    QLabel *label_6;
    QHBoxLayout *hboxLayout;
    PlainToolButton *m_btnAnswerOne;
    QLineEdit *m_txtAnswerOne;
    QHBoxLayout *hboxLayout1;
    PlainToolButton *m_btnAnswerTwo;
    QLineEdit *m_txtAnswerTwo;
    QHBoxLayout *hboxLayout2;
    PlainToolButton *m_btnAnswerThree;
    QLineEdit *m_txtAnswerThree;
    QHBoxLayout *hboxLayout3;
    PlainToolButton *m_btnAnswerFour;
    QLineEdit *m_txtAnswerFour;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_4;
    QListWidget *m_listPassage;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout4;
    QToolButton *m_btnPassageAdd;
    QToolButton *m_btnPassageRemove;
    QSpacerItem *spacerItem;
    QGroupBox *groupBox_5;
    QListWidget *m_listQuestions;
    QWidget *layoutWidget1;
    QHBoxLayout *hboxLayout5;
    QToolButton *m_btnQuestionAdd;
    QToolButton *m_btnQuestionRemove;
    QToolButton *m_btnQuestionUp;
    QToolButton *m_btnQuestionDown;
    QSpacerItem *spacerItem1;

    void setupUi(QWidget *ComprehensionEditor)
    {
        if (ComprehensionEditor->objectName().isEmpty())
            ComprehensionEditor->setObjectName(QStringLiteral("ComprehensionEditor"));
        ComprehensionEditor->resize(742, 570);
        groupBox_3 = new QGroupBox(ComprehensionEditor);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 470, 361, 88));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        m_txtAuthor = new LineEditWithStatus(groupBox_3);
        m_txtAuthor->setObjectName(QStringLiteral("m_txtAuthor"));

        gridLayout->addWidget(m_txtAuthor, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        m_txtName = new LineEditWithStatus(groupBox_3);
        m_txtName->setObjectName(QStringLiteral("m_txtName"));

        gridLayout->addWidget(m_txtName, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        m_txtNumberOfQuestions = new LineEditWithStatus(groupBox_3);
        m_txtNumberOfQuestions->setObjectName(QStringLiteral("m_txtNumberOfQuestions"));
        m_txtNumberOfQuestions->setEnabled(true);

        gridLayout->addWidget(m_txtNumberOfQuestions, 2, 1, 1, 1);

        groupBox = new QGroupBox(ComprehensionEditor);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 361, 421));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 341, 381));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        m_groupPassageEditor = new QGroupBox(tab);
        m_groupPassageEditor->setObjectName(QStringLiteral("m_groupPassageEditor"));
        m_groupPassageEditor->setGeometry(QRect(10, 10, 315, 331));
        gridLayout1 = new QGridLayout(m_groupPassageEditor);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        label_7 = new QLabel(m_groupPassageEditor);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout1->addWidget(label_7, 0, 0, 1, 1);

        m_txtPassage = new MaxLengthTextEdit(m_groupPassageEditor);
        m_txtPassage->setObjectName(QStringLiteral("m_txtPassage"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(m_txtPassage->sizePolicy().hasHeightForWidth());
        m_txtPassage->setSizePolicy(sizePolicy);
        m_txtPassage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_txtPassage->setTabChangesFocus(true);
        m_txtPassage->setAcceptRichText(false);

        gridLayout1->addWidget(m_txtPassage, 0, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        m_groupQuestionEditor = new QGroupBox(tab_2);
        m_groupQuestionEditor->setObjectName(QStringLiteral("m_groupQuestionEditor"));
        m_groupQuestionEditor->setGeometry(QRect(10, 10, 315, 334));
        gridLayout2 = new QGridLayout(m_groupQuestionEditor);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        label_2 = new QLabel(m_groupQuestionEditor);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout2->addWidget(label_2, 0, 0, 1, 1);

        m_txtQuestion = new MaxLengthTextEdit(m_groupQuestionEditor);
        m_txtQuestion->setObjectName(QStringLiteral("m_txtQuestion"));
        sizePolicy.setHeightForWidth(m_txtQuestion->sizePolicy().hasHeightForWidth());
        m_txtQuestion->setSizePolicy(sizePolicy);
        m_txtQuestion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_txtQuestion->setTabChangesFocus(true);
        m_txtQuestion->setAcceptRichText(false);

        gridLayout2->addWidget(m_txtQuestion, 0, 1, 1, 1);

        label_6 = new QLabel(m_groupQuestionEditor);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout2->addWidget(label_6, 1, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        m_btnAnswerOne = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerOne->setObjectName(QStringLiteral("m_btnAnswerOne"));

        hboxLayout->addWidget(m_btnAnswerOne);

        m_txtAnswerOne = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerOne->setObjectName(QStringLiteral("m_txtAnswerOne"));

        hboxLayout->addWidget(m_txtAnswerOne);


        gridLayout2->addLayout(hboxLayout, 1, 1, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        m_btnAnswerTwo = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerTwo->setObjectName(QStringLiteral("m_btnAnswerTwo"));

        hboxLayout1->addWidget(m_btnAnswerTwo);

        m_txtAnswerTwo = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerTwo->setObjectName(QStringLiteral("m_txtAnswerTwo"));

        hboxLayout1->addWidget(m_txtAnswerTwo);


        gridLayout2->addLayout(hboxLayout1, 2, 1, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        m_btnAnswerThree = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerThree->setObjectName(QStringLiteral("m_btnAnswerThree"));

        hboxLayout2->addWidget(m_btnAnswerThree);

        m_txtAnswerThree = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerThree->setObjectName(QStringLiteral("m_txtAnswerThree"));

        hboxLayout2->addWidget(m_txtAnswerThree);


        gridLayout2->addLayout(hboxLayout2, 3, 1, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        m_btnAnswerFour = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerFour->setObjectName(QStringLiteral("m_btnAnswerFour"));

        hboxLayout3->addWidget(m_btnAnswerFour);

        m_txtAnswerFour = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerFour->setObjectName(QStringLiteral("m_txtAnswerFour"));

        hboxLayout3->addWidget(m_txtAnswerFour);


        gridLayout2->addLayout(hboxLayout3, 4, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        groupBox_2 = new QGroupBox(ComprehensionEditor);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(400, 10, 331, 531));
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 0, 301, 251));
        m_listPassage = new QListWidget(groupBox_4);
        m_listPassage->setObjectName(QStringLiteral("m_listPassage"));
        m_listPassage->setGeometry(QRect(10, 20, 281, 192));
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 220, 227, 22));
        hboxLayout4 = new QHBoxLayout(layoutWidget);
        hboxLayout4->setObjectName(QStringLiteral("hboxLayout4"));
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        m_btnPassageAdd = new QToolButton(layoutWidget);
        m_btnPassageAdd->setObjectName(QStringLiteral("m_btnPassageAdd"));

        hboxLayout4->addWidget(m_btnPassageAdd);

        m_btnPassageRemove = new QToolButton(layoutWidget);
        m_btnPassageRemove->setObjectName(QStringLiteral("m_btnPassageRemove"));

        hboxLayout4->addWidget(m_btnPassageRemove);

        spacerItem = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacerItem);

        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 260, 301, 251));
        m_listQuestions = new QListWidget(groupBox_5);
        m_listQuestions->setObjectName(QStringLiteral("m_listQuestions"));
        m_listQuestions->setGeometry(QRect(10, 20, 281, 192));
        layoutWidget1 = new QWidget(groupBox_5);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 220, 227, 22));
        hboxLayout5 = new QHBoxLayout(layoutWidget1);
        hboxLayout5->setObjectName(QStringLiteral("hboxLayout5"));
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        m_btnQuestionAdd = new QToolButton(layoutWidget1);
        m_btnQuestionAdd->setObjectName(QStringLiteral("m_btnQuestionAdd"));

        hboxLayout5->addWidget(m_btnQuestionAdd);

        m_btnQuestionRemove = new QToolButton(layoutWidget1);
        m_btnQuestionRemove->setObjectName(QStringLiteral("m_btnQuestionRemove"));

        hboxLayout5->addWidget(m_btnQuestionRemove);

        m_btnQuestionUp = new QToolButton(layoutWidget1);
        m_btnQuestionUp->setObjectName(QStringLiteral("m_btnQuestionUp"));

        hboxLayout5->addWidget(m_btnQuestionUp);

        m_btnQuestionDown = new QToolButton(layoutWidget1);
        m_btnQuestionDown->setObjectName(QStringLiteral("m_btnQuestionDown"));

        hboxLayout5->addWidget(m_btnQuestionDown);

        spacerItem1 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacerItem1);


        retranslateUi(ComprehensionEditor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ComprehensionEditor);
    } // setupUi

    void retranslateUi(QWidget *ComprehensionEditor)
    {
        ComprehensionEditor->setWindowTitle(QApplication::translate("ComprehensionEditor", "Dialog", 0));
        groupBox_3->setTitle(QApplication::translate("ComprehensionEditor", "Quiz metadata", 0));
        label_3->setText(QApplication::translate("ComprehensionEditor", "Author", 0));
        label_4->setText(QApplication::translate("ComprehensionEditor", "Quiz name", 0));
        label_5->setText(QApplication::translate("ComprehensionEditor", "Number of questions", 0));
        groupBox->setTitle(QString());
        m_groupPassageEditor->setTitle(QApplication::translate("ComprehensionEditor", "Passage editor", 0));
        label_7->setText(QApplication::translate("ComprehensionEditor", "Passage", 0));
        m_txtPassage->setHtml(QApplication::translate("ComprehensionEditor", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ComprehensionEditor", "Passage", 0));
        m_groupQuestionEditor->setTitle(QApplication::translate("ComprehensionEditor", "Question editor", 0));
        label_2->setText(QApplication::translate("ComprehensionEditor", "Question", 0));
        m_txtQuestion->setHtml(QApplication::translate("ComprehensionEditor", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        label_6->setText(QApplication::translate("ComprehensionEditor", "Answers", 0));
        m_btnAnswerOne->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_txtAnswerOne->setProperty("placeholderText", QVariant(QApplication::translate("ComprehensionEditor", "Answer one", 0)));
        m_btnAnswerTwo->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_txtAnswerTwo->setProperty("placeholderText", QVariant(QApplication::translate("ComprehensionEditor", "Answer two", 0)));
        m_btnAnswerThree->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_txtAnswerThree->setProperty("placeholderText", QVariant(QApplication::translate("ComprehensionEditor", "Answer three", 0)));
        m_btnAnswerFour->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_txtAnswerFour->setProperty("placeholderText", QVariant(QApplication::translate("ComprehensionEditor", "Answer four", 0)));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ComprehensionEditor", "Questions", 0));
        groupBox_2->setTitle(QString());
        groupBox_4->setTitle(QApplication::translate("ComprehensionEditor", "Passage", 0));
        m_btnPassageAdd->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_btnPassageRemove->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        groupBox_5->setTitle(QApplication::translate("ComprehensionEditor", "Active questions", 0));
        m_btnQuestionAdd->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_btnQuestionRemove->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_btnQuestionUp->setText(QApplication::translate("ComprehensionEditor", "...", 0));
        m_btnQuestionDown->setText(QApplication::translate("ComprehensionEditor", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class ComprehensionEditor: public Ui_ComprehensionEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPREHENSIONEDITOR_H
