/********************************************************************************
** Form generated from reading UI file 'flashcardeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHCARDEDITOR_H
#define UI_FLASHCARDEDITOR_H

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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "labelwithstatus.h"
#include "lineeditwithstatus.h"
#include "plaintoolbutton.h"

QT_BEGIN_NAMESPACE

class Ui_FlashCardEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    LineEditWithStatus *m_txtAuthor;
    QLabel *label_4;
    LineEditWithStatus *m_txtName;
    QLabel *label_6;
    LineEditWithStatus *m_txtNumberOfQuestions;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    PlainToolButton *m_btnQuestionAdd;
    PlainToolButton *m_btnQuestionDown;
    PlainToolButton *m_btnQuestionRemove;
    PlainToolButton *m_btnQuestionUp;
    QSpacerItem *horizontalSpacer;
    QListWidget *m_listQuestions;
    QGroupBox *m_groupQuestionEditor;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *m_btnPictureSelect;
    LabelWithStatus *m_lblPictureFile;
    QLabel *m_lblPictureView;
    QLabel *label_2;
    LineEditWithStatus *m_txtAnswer;
    QLabel *label_7;
    LineEditWithStatus *m_txtHint;
    LineEditWithStatus *m_txtQuestion;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FlashCardEditor)
    {
        if (FlashCardEditor->objectName().isEmpty())
            FlashCardEditor->setObjectName(QStringLiteral("FlashCardEditor"));
        FlashCardEditor->resize(585, 382);
        horizontalLayout = new QHBoxLayout(FlashCardEditor);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(FlashCardEditor);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 585, 382));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
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

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_6);

        m_txtNumberOfQuestions = new LineEditWithStatus(groupBox_3);
        m_txtNumberOfQuestions->setObjectName(QStringLiteral("m_txtNumberOfQuestions"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, m_txtNumberOfQuestions);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_btnQuestionAdd = new PlainToolButton(groupBox_2);
        m_btnQuestionAdd->setObjectName(QStringLiteral("m_btnQuestionAdd"));
        m_btnQuestionAdd->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionAdd, 1, 0, 1, 1);

        m_btnQuestionDown = new PlainToolButton(groupBox_2);
        m_btnQuestionDown->setObjectName(QStringLiteral("m_btnQuestionDown"));
        m_btnQuestionDown->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionDown, 1, 3, 1, 1);

        m_btnQuestionRemove = new PlainToolButton(groupBox_2);
        m_btnQuestionRemove->setObjectName(QStringLiteral("m_btnQuestionRemove"));
        m_btnQuestionRemove->setEnabled(false);
        m_btnQuestionRemove->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionRemove, 1, 1, 1, 1);

        m_btnQuestionUp = new PlainToolButton(groupBox_2);
        m_btnQuestionUp->setObjectName(QStringLiteral("m_btnQuestionUp"));
        m_btnQuestionUp->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(m_btnQuestionUp, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 4, 1, 1);

        m_listQuestions = new QListWidget(groupBox_2);
        m_listQuestions->setObjectName(QStringLiteral("m_listQuestions"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_listQuestions->sizePolicy().hasHeightForWidth());
        m_listQuestions->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_listQuestions, 0, 0, 1, 5);


        gridLayout->addWidget(groupBox_2, 0, 1, 4, 1);

        m_groupQuestionEditor = new QGroupBox(scrollAreaWidgetContents);
        m_groupQuestionEditor->setObjectName(QStringLiteral("m_groupQuestionEditor"));
        formLayout = new QFormLayout(m_groupQuestionEditor);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(m_groupQuestionEditor);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_5 = new QLabel(m_groupQuestionEditor);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        m_btnPictureSelect = new QPushButton(m_groupQuestionEditor);
        m_btnPictureSelect->setObjectName(QStringLiteral("m_btnPictureSelect"));

        horizontalLayout_12->addWidget(m_btnPictureSelect);

        m_lblPictureFile = new LabelWithStatus(m_groupQuestionEditor);
        m_lblPictureFile->setObjectName(QStringLiteral("m_lblPictureFile"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_lblPictureFile->sizePolicy().hasHeightForWidth());
        m_lblPictureFile->setSizePolicy(sizePolicy1);
        m_lblPictureFile->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_12->addWidget(m_lblPictureFile);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_12);

        m_lblPictureView = new QLabel(m_groupQuestionEditor);
        m_lblPictureView->setObjectName(QStringLiteral("m_lblPictureView"));
        m_lblPictureView->setMinimumSize(QSize(0, 130));
        m_lblPictureView->setMaximumSize(QSize(16777215, 130));
        m_lblPictureView->setFrameShape(QFrame::NoFrame);
        m_lblPictureView->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        formLayout->setWidget(2, QFormLayout::FieldRole, m_lblPictureView);

        label_2 = new QLabel(m_groupQuestionEditor);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        m_txtAnswer = new LineEditWithStatus(m_groupQuestionEditor);
        m_txtAnswer->setObjectName(QStringLiteral("m_txtAnswer"));

        formLayout->setWidget(4, QFormLayout::FieldRole, m_txtAnswer);

        label_7 = new QLabel(m_groupQuestionEditor);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);

        m_txtHint = new LineEditWithStatus(m_groupQuestionEditor);
        m_txtHint->setObjectName(QStringLiteral("m_txtHint"));

        formLayout->setWidget(5, QFormLayout::FieldRole, m_txtHint);

        m_txtQuestion = new LineEditWithStatus(m_groupQuestionEditor);
        m_txtQuestion->setObjectName(QStringLiteral("m_txtQuestion"));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_txtQuestion);


        gridLayout->addWidget(m_groupQuestionEditor, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        retranslateUi(FlashCardEditor);

        QMetaObject::connectSlotsByName(FlashCardEditor);
    } // setupUi

    void retranslateUi(QWidget *FlashCardEditor)
    {
        FlashCardEditor->setWindowTitle(QApplication::translate("FlashCardEditor", "Form", 0));
        groupBox_3->setTitle(QApplication::translate("FlashCardEditor", "Flashcards metadata", 0));
        label_3->setText(QApplication::translate("FlashCardEditor", "Author", 0));
        label_4->setText(QApplication::translate("FlashCardEditor", "Collection name", 0));
        label_6->setText(QApplication::translate("FlashCardEditor", "Number of questions", 0));
        groupBox_2->setTitle(QApplication::translate("FlashCardEditor", "Active questions", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionAdd->setToolTip(QApplication::translate("FlashCardEditor", "Add new question.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionAdd->setText(QApplication::translate("FlashCardEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionDown->setToolTip(QApplication::translate("FlashCardEditor", "Move question down.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionDown->setText(QApplication::translate("FlashCardEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionRemove->setToolTip(QApplication::translate("FlashCardEditor", "Remove selected question.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionRemove->setText(QApplication::translate("FlashCardEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnQuestionUp->setToolTip(QApplication::translate("FlashCardEditor", "Move question up.", 0));
#endif // QT_NO_TOOLTIP
        m_btnQuestionUp->setText(QApplication::translate("FlashCardEditor", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_listQuestions->setToolTip(QApplication::translate("FlashCardEditor", "This list contains already added questions.", 0));
#endif // QT_NO_TOOLTIP
        m_groupQuestionEditor->setTitle(QApplication::translate("FlashCardEditor", "Question editor", 0));
        label->setText(QApplication::translate("FlashCardEditor", "Question", 0));
        label_5->setText(QApplication::translate("FlashCardEditor", "Picture", 0));
        m_btnPictureSelect->setText(QApplication::translate("FlashCardEditor", "&Select", 0));
        m_lblPictureView->setText(QString());
        label_2->setText(QApplication::translate("FlashCardEditor", "Answer", 0));
        label_7->setText(QApplication::translate("FlashCardEditor", "Hint", 0));
    } // retranslateUi

};

namespace Ui {
    class FlashCardEditor: public Ui_FlashCardEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHCARDEDITOR_H
