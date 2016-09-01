/********************************************************************************
** Form generated from reading UI file 'flashcarditem.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHCARDITEM_H
#define UI_FLASHCARDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlashCardItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *m_lblQuestionNumber;
    QFrame *line;
    QLabel *m_lblQuestionText;
    QLabel *m_lblDummy;
    QStackedWidget *m_flipper;
    QWidget *m_pagePicture;
    QVBoxLayout *verticalLayout_2;
    QLabel *m_lblPicture;
    QWidget *m_pageAnswer;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_lblAnswer;
    QSpacerItem *verticalSpacer;
    QLabel *m_lblHint;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_btnPrevious;
    QPushButton *m_btnFlip;
    QPushButton *m_btnNext;

    void setupUi(QWidget *FlashCardItem)
    {
        if (FlashCardItem->objectName().isEmpty())
            FlashCardItem->setObjectName(QStringLiteral("FlashCardItem"));
        FlashCardItem->resize(351, 431);
        verticalLayout = new QVBoxLayout(FlashCardItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_lblQuestionNumber = new QLabel(FlashCardItem);
        m_lblQuestionNumber->setObjectName(QStringLiteral("m_lblQuestionNumber"));

        verticalLayout->addWidget(m_lblQuestionNumber);

        line = new QFrame(FlashCardItem);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        m_lblQuestionText = new QLabel(FlashCardItem);
        m_lblQuestionText->setObjectName(QStringLiteral("m_lblQuestionText"));
        m_lblQuestionText->setWordWrap(true);

        verticalLayout->addWidget(m_lblQuestionText);

        m_lblDummy = new QLabel(FlashCardItem);
        m_lblDummy->setObjectName(QStringLiteral("m_lblDummy"));
        m_lblDummy->setEnabled(true);

        verticalLayout->addWidget(m_lblDummy);

        m_flipper = new QStackedWidget(FlashCardItem);
        m_flipper->setObjectName(QStringLiteral("m_flipper"));
        m_pagePicture = new QWidget();
        m_pagePicture->setObjectName(QStringLiteral("m_pagePicture"));
        verticalLayout_2 = new QVBoxLayout(m_pagePicture);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_lblPicture = new QLabel(m_pagePicture);
        m_lblPicture->setObjectName(QStringLiteral("m_lblPicture"));
        m_lblPicture->setFrameShape(QFrame::Box);
        m_lblPicture->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(m_lblPicture);

        m_flipper->addWidget(m_pagePicture);
        m_pageAnswer = new QWidget();
        m_pageAnswer->setObjectName(QStringLiteral("m_pageAnswer"));
        verticalLayout_3 = new QVBoxLayout(m_pageAnswer);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        m_lblAnswer = new QLabel(m_pageAnswer);
        m_lblAnswer->setObjectName(QStringLiteral("m_lblAnswer"));
        m_lblAnswer->setFrameShape(QFrame::Box);
        m_lblAnswer->setAlignment(Qt::AlignCenter);
        m_lblAnswer->setWordWrap(true);

        verticalLayout_3->addWidget(m_lblAnswer);

        m_flipper->addWidget(m_pageAnswer);

        verticalLayout->addWidget(m_flipper);

        verticalSpacer = new QSpacerItem(17, 152, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_lblHint = new QLabel(FlashCardItem);
        m_lblHint->setObjectName(QStringLiteral("m_lblHint"));
        m_lblHint->setAlignment(Qt::AlignCenter);
        m_lblHint->setWordWrap(true);

        verticalLayout->addWidget(m_lblHint);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_btnPrevious = new QPushButton(FlashCardItem);
        m_btnPrevious->setObjectName(QStringLiteral("m_btnPrevious"));

        horizontalLayout_3->addWidget(m_btnPrevious);

        m_btnFlip = new QPushButton(FlashCardItem);
        m_btnFlip->setObjectName(QStringLiteral("m_btnFlip"));

        horizontalLayout_3->addWidget(m_btnFlip);

        m_btnNext = new QPushButton(FlashCardItem);
        m_btnNext->setObjectName(QStringLiteral("m_btnNext"));

        horizontalLayout_3->addWidget(m_btnNext);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(FlashCardItem);

        m_flipper->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FlashCardItem);
    } // setupUi

    void retranslateUi(QWidget *FlashCardItem)
    {
        FlashCardItem->setWindowTitle(QApplication::translate("FlashCardItem", "Form", 0));
        m_lblQuestionNumber->setText(QApplication::translate("FlashCardItem", "Question number", 0));
        m_lblQuestionText->setText(QApplication::translate("FlashCardItem", "Question text", 0));
        m_lblDummy->setText(QString());
        m_lblPicture->setText(QString());
        m_lblAnswer->setText(QString());
        m_lblHint->setText(QString());
        m_btnPrevious->setText(QApplication::translate("FlashCardItem", "&Previous", 0));
        m_btnFlip->setText(QApplication::translate("FlashCardItem", "&Flip", 0));
        m_btnNext->setText(QApplication::translate("FlashCardItem", "&Next", 0));
    } // retranslateUi

};

namespace Ui {
    class FlashCardItem: public Ui_FlashCardItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHCARDITEM_H
