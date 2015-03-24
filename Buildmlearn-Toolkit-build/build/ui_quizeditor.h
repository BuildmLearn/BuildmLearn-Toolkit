/********************************************************************************
** Form generated from reading UI file 'quizeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZEDITOR_H
#define UI_QUIZEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "lineeditwithstatus.h"
#include "maxlengthtextedit.h"
#include "plaintoolbutton.h"

QT_BEGIN_NAMESPACE

class Ui_QuizEditor
{
public:
    QGridLayout *gridLayout;
    QGroupBox *m_groupQuestionEditor;
    QFormLayout *formLayout;
    QLabel *label;
    MaxLengthTextEdit *m_txtQuestion;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    PlainToolButton *m_btnAnswerOne;
    QLineEdit *m_txtAnswerOne;
    QHBoxLayout *horizontalLayout_2;
    PlainToolButton *m_btnAnswerTwo;
    QLineEdit *m_txtAnswerTwo;
    QHBoxLayout *horizontalLayout_3;
    PlainToolButton *m_btnAnswerThree;
    QLineEdit *m_txtAnswerThree;
    QHBoxLayout *horizontalLayout_4;
    PlainToolButton *m_btnAnswerFour;
    QLineEdit *m_txtAnswerFour;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    PlainToolButton *m_btnQuestionAdd;
    PlainToolButton *m_btnQuestionDown;
    PlainToolButton *m_btnQuestionRemove;
    PlainToolButton *m_btnQuestionUp;
    QSpacerItem *horizontalSpacer;
    QListWidget *m_listQuestions;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    LineEditWithStatus *m_txtAuthor;
    QLabel *label_4;
    LineEditWithStatus *m_txtName;
    QLabel *label_5;
    LineEditWithStatus *m_txtNumberOfQuestions;

    void setupUi(QWidget *QuizEditor)
    {
        if (QuizEditor->objectName().isEmpty())
            QuizEditor->setObjectName(QStringLiteral("QuizEditor"));
        QuizEditor->resize(588, 428);
        gridLayout = new QGridLayout(QuizEditor);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        m_groupQuestionEditor = new QGroupBox(QuizEditor);
        m_groupQuestionEditor->setObjectName(QStringLiteral("m_groupQuestionEditor"));
        formLayout = new QFormLayout(m_groupQuestionEditor);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(m_groupQuestionEditor);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        m_txtQuestion = new MaxLengthTextEdit(m_groupQuestionEditor);
        m_txtQuestion->setObjectName(QStringLiteral("m_txtQuestion"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(m_txtQuestion->sizePolicy().hasHeightForWidth());
        m_txtQuestion->setSizePolicy(sizePolicy);
        m_txtQuestion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_txtQuestion->setTabChangesFocus(true);
        m_txtQuestion->setAcceptRichText(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, m_txtQuestion);

        label_2 = new QLabel(m_groupQuestionEditor);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_btnAnswerOne = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerOne->setObjectName(QStringLiteral("m_btnAnswerOne"));

        horizontalLayout->addWidget(m_btnAnswerOne);

        m_txtAnswerOne = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerOne->setObjectName(QStringLiteral("m_txtAnswerOne"));

        horizontalLayout->addWidget(m_txtAnswerOne);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_btnAnswerTwo = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerTwo->setObjectName(QStringLiteral("m_btnAnswerTwo"));

        horizontalLayout_2->addWidget(m_btnAnswerTwo);

        m_txtAnswerTwo = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerTwo->setObjectName(QStringLiteral("m_txtAnswerTwo"));

        horizontalLayout_2->addWidget(m_txtAnswerTwo);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_btnAnswerThree = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerThree->setObjectName(QStringLiteral("m_btnAnswerThree"));

        horizontalLayout_3->addWidget(m_btnAnswerThree);

        m_txtAnswerThree = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerThree->setObjectName(QStringLiteral("m_txtAnswerThree"));

        horizontalLayout_3->addWidget(m_txtAnswerThree);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_btnAnswerFour = new PlainToolButton(m_groupQuestionEditor);
        m_btnAnswerFour->setObjectName(QStringLiteral("m_btnAnswerFour"));

        horizontalLayout_4->addWidget(m_btnAnswerFour);

        m_txtAnswerFour = new QLineEdit(m_groupQuestionEditor);
        m_txtAnswerFour->setObjectName(QStringLiteral("m_txtAnswerFour"));

        horizontalLayout_4->addWidget(m_txtAnswerFour);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_4);


        gridLayout->addWidget(m_groupQuestionEditor, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(QuizEditor);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_btnQuestionAdd = new PlainToolButton(groupBox_2);
        m_btnQuestionAdd->setObjectName(QStringLiteral("m_btnQuestionAdd"));
        m_btnQuestionAdd->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionAdd, 1, 0, 1, 1);

        m_btnQuestionDown = new PlainToolButton(groupBox_2);
        m_btnQuestionDown->setObjectName(QStringLiteral("m_btnQuestionDown"));
        m_btnQuestionDown->setEnabled(false);
        m_btnQuestionDown->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionDown, 1, 3, 1, 1);

        m_btnQuestionRemove = new PlainToolButton(groupBox_2);
        m_btnQuestionRemove->setObjectName(QStringLiteral("m_btnQuestionRemove"));
        m_btnQuestionRemove->setEnabled(false);
        m_btnQuestionRemove->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionRemove, 1, 1, 1, 1);

        m_btnQuestionUp = new PlainToolButton(groupBox_2);
        m_btnQuestionUp->setObjectName(QStringLiteral("m_btnQuestionUp"));
        m_btnQuestionUp->setEnabled(false);
        m_btnQuestionUp->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionUp, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 4, 1, 1);

        m_listQuestions = new QListWidget(groupBox_2);
        m_listQuestions->setObjectName(QStringLiteral("m_listQuestions"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_listQuestions->sizePolicy().hasHeightForWidth());
        m_listQuestions->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_listQuestions, 0, 0, 1, 5);


        gridLayout->addWidget(groupBox_2, 0, 1, 2, 1);

        groupBox_3 = new QGroupBox(QuizEditor);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        m_txtAuthor = new LineEditWithStatus(groupBox_3);
        m_txtAuthor->setObjectName(QStringLiteral("m_txtAuthor"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, m_txtAuthor);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        m_txtName = new LineEditWithStatus(groupBox_3);
        m_txtName->setObjectName(QStringLiteral("m_txtName"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_txtName);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        m_txtNumberOfQuestions = new LineEditWithStatus(groupBox_3);
        m_txtNumberOfQuestions->setObjectName(QStringLiteral("m_txtNumberOfQuestions"));
        m_txtNumberOfQuestions->setEnabled(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, m_txtNumberOfQuestions);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);


        retranslateUi(QuizEditor);

        QMetaObject::connectSlotsByName(QuizEditor);
    } // setupUi

    void retranslateUi(QWidget *QuizEditor)
    {
        QuizEditor->setWindowTitle(QApplication::translate("QuizEditor", "Form", 0));
        m_groupQuestionEditor->setTitle(QApplication::translate("QuizEditor", "Question editor", 0));
        label->setText(QApplication::translate("QuizEditor", "Question", 0));
        m_txtQuestion->setHtml(QApplication::translate("QuizEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        label_2->setText(QApplication::translate("QuizEditor", "Answers", 0));
        m_btnAnswerOne->setText(QApplication::translate("QuizEditor", "...", 0));
        m_txtAnswerOne->setPlaceholderText(QApplication::translate("QuizEditor", "Answer one", 0));
        m_btnAnswerTwo->setText(QApplication::translate("QuizEditor", "...", 0));
        m_txtAnswerTwo->setPlaceholderText(QApplication::translate("QuizEditor", "Answer two", 0));
        m_btnAnswerThree->setText(QApplication::translate("QuizEditor", "...", 0));
        m_txtAnswerThree->setPlaceholderText(QApplication::translate("QuizEditor", "Answer three", 0));
        m_btnAnswerFour->setText(QApplication::translate("QuizEditor", "...", 0));
        m_txtAnswerFour->setPlaceholderText(QApplication::translate("QuizEditor", "Answer four", 0));
        groupBox_2->setTitle(QApplication::translate("QuizEditor", "Active questions", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionAdd->setToolTip(QApplication::translate("QuizEditor", "Add new question.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionAdd->setText(QApplication::translate("QuizEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionDown->setToolTip(QApplication::translate("QuizEditor", "Move question down.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionDown->setText(QApplication::translate("QuizEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionRemove->setToolTip(QApplication::translate("QuizEditor", "Remove selected question.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionRemove->setText(QApplication::translate("QuizEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionUp->setToolTip(QApplication::translate("QuizEditor", "Move question up.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionUp->setText(QApplication::translate("QuizEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_listQuestions->setToolTip(QApplication::translate("QuizEditor", "This list contains already added questions.", 0));
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QApplication::translate("QuizEditor", "Quiz metadata", 0));
        label_3->setText(QApplication::translate("QuizEditor", "Author", 0));
        label_4->setText(QApplication::translate("QuizEditor", "Quiz name", 0));
        label_5->setText(QApplication::translate("QuizEditor", "Number of questions", 0));
    } // retranslateUi

};

namespace Ui {
    class QuizEditor: public Ui_QuizEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZEDITOR_H
