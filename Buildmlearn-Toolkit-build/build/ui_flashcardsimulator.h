/********************************************************************************
** Form generated from reading UI file 'flashcardsimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHCARDSIMULATOR_H
#define UI_FLASHCARDSIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlashCardSimulator
{
public:
    QVBoxLayout *verticalLayout_3;
    QStackedWidget *m_phoneWidget;
    QWidget *m_pageStopped;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_lblHeading_2;
    QWidget *m_pageWelcome;
    QGridLayout *gridLayout_2;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnStart;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_lblAuthor;
    QLabel *m_lblHeading;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QWidget *m_pageFinish;
    QGridLayout *gridLayout;
    QLabel *m_lblHeading_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnRestart;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *FlashCardSimulator)
    {
        if (FlashCardSimulator->objectName().isEmpty())
            FlashCardSimulator->setObjectName(QStringLiteral("FlashCardSimulator"));
        FlashCardSimulator->resize(381, 434);
        verticalLayout_3 = new QVBoxLayout(FlashCardSimulator);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        m_phoneWidget = new QStackedWidget(FlashCardSimulator);
        m_phoneWidget->setObjectName(QStringLiteral("m_phoneWidget"));
        m_pageStopped = new QWidget();
        m_pageStopped->setObjectName(QStringLiteral("m_pageStopped"));
        horizontalLayout_3 = new QHBoxLayout(m_pageStopped);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_lblHeading_2 = new QLabel(m_pageStopped);
        m_lblHeading_2->setObjectName(QStringLiteral("m_lblHeading_2"));
        m_lblHeading_2->setText(QStringLiteral("<span style=\" font-size:18pt;\">Flash cards</span>"));
        m_lblHeading_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_lblHeading_2);

        m_phoneWidget->addWidget(m_pageStopped);
        m_pageWelcome = new QWidget();
        m_pageWelcome->setObjectName(QStringLiteral("m_pageWelcome"));
        gridLayout_2 = new QGridLayout(m_pageWelcome);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        line_2 = new QFrame(m_pageWelcome);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 2, 0, 1, 3);

        horizontalSpacer_3 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 5, 0, 1, 1);

        m_btnStart = new QPushButton(m_pageWelcome);
        m_btnStart->setObjectName(QStringLiteral("m_btnStart"));
        m_btnStart->setEnabled(false);

        gridLayout_2->addWidget(m_btnStart, 5, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 5, 2, 1, 1);

        m_lblAuthor = new QLabel(m_pageWelcome);
        m_lblAuthor->setObjectName(QStringLiteral("m_lblAuthor"));
        m_lblAuthor->setText(QStringLiteral("Author"));
        m_lblAuthor->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lblAuthor, 3, 0, 1, 3);

        m_lblHeading = new QLabel(m_pageWelcome);
        m_lblHeading->setObjectName(QStringLiteral("m_lblHeading"));
        m_lblHeading->setText(QStringLiteral("Heading"));
        m_lblHeading->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lblHeading, 1, 0, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 116, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 0, 1, 3);

        verticalSpacer_3 = new QSpacerItem(20, 115, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 0, 1, 3);

        m_phoneWidget->addWidget(m_pageWelcome);
        m_pageFinish = new QWidget();
        m_pageFinish->setObjectName(QStringLiteral("m_pageFinish"));
        gridLayout = new QGridLayout(m_pageFinish);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_lblHeading_3 = new QLabel(m_pageFinish);
        m_lblHeading_3->setObjectName(QStringLiteral("m_lblHeading_3"));
        m_lblHeading_3->setText(QStringLiteral("<span style=\" font-size:18pt;\">That was the last card!</span>"));
        m_lblHeading_3->setAlignment(Qt::AlignCenter);
        m_lblHeading_3->setWordWrap(true);

        gridLayout->addWidget(m_lblHeading_3, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        m_btnRestart = new QPushButton(m_pageFinish);
        m_btnRestart->setObjectName(QStringLiteral("m_btnRestart"));

        gridLayout->addWidget(m_btnRestart, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        m_phoneWidget->addWidget(m_pageFinish);

        verticalLayout_3->addWidget(m_phoneWidget);


        retranslateUi(FlashCardSimulator);

        m_phoneWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FlashCardSimulator);
    } // setupUi

    void retranslateUi(QWidget *FlashCardSimulator)
    {
        FlashCardSimulator->setWindowTitle(QApplication::translate("FlashCardSimulator", "Form", 0));
        m_btnStart->setText(QApplication::translate("FlashCardSimulator", "&Start", 0));
        m_btnRestart->setText(QApplication::translate("FlashCardSimulator", "&Restart", 0));
    } // retranslateUi

};

namespace Ui {
    class FlashCardSimulator: public Ui_FlashCardSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHCARDSIMULATOR_H
