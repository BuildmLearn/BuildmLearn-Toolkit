/********************************************************************************
** Form generated from reading UI file 'quizsimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZSIMULATOR_H
#define UI_QUIZSIMULATOR_H

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

class Ui_QuizSimulator
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *m_phoneWidget;
    QWidget *m_pageStopped;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_lblHeading_2;
    QWidget *m_pageWelcome;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *m_lblHeading;
    QFrame *line_2;
    QLabel *m_lblAuthor;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnStart;
    QSpacerItem *horizontalSpacer_4;
    QWidget *m_pageFinish;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QLabel *m_lblTotalCorrect;
    QLabel *m_lblTotalWrong;
    QLabel *m_lblTotalUnanswered;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnExit;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnRestart;

    void setupUi(QWidget *QuizSimulator)
    {
        if (QuizSimulator->objectName().isEmpty())
            QuizSimulator->setObjectName(QStringLiteral("QuizSimulator"));
        QuizSimulator->resize(319, 339);
        horizontalLayout = new QHBoxLayout(QuizSimulator);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_phoneWidget = new QStackedWidget(QuizSimulator);
        m_phoneWidget->setObjectName(QStringLiteral("m_phoneWidget"));
        m_pageStopped = new QWidget();
        m_pageStopped->setObjectName(QStringLiteral("m_pageStopped"));
        horizontalLayout_3 = new QHBoxLayout(m_pageStopped);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_lblHeading_2 = new QLabel(m_pageStopped);
        m_lblHeading_2->setObjectName(QStringLiteral("m_lblHeading_2"));
        m_lblHeading_2->setText(QStringLiteral("<span style=\" font-size:18pt;\">Quiz</span>"));
        m_lblHeading_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_lblHeading_2);

        m_phoneWidget->addWidget(m_pageStopped);
        m_pageWelcome = new QWidget();
        m_pageWelcome->setObjectName(QStringLiteral("m_pageWelcome"));
        verticalLayout_2 = new QVBoxLayout(m_pageWelcome);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 116, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        m_lblHeading = new QLabel(m_pageWelcome);
        m_lblHeading->setObjectName(QStringLiteral("m_lblHeading"));
        m_lblHeading->setText(QStringLiteral("Heading"));
        m_lblHeading->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(m_lblHeading);

        line_2 = new QFrame(m_pageWelcome);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        m_lblAuthor = new QLabel(m_pageWelcome);
        m_lblAuthor->setObjectName(QStringLiteral("m_lblAuthor"));
        m_lblAuthor->setText(QStringLiteral("Author"));
        m_lblAuthor->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(m_lblAuthor);

        verticalSpacer_3 = new QSpacerItem(20, 115, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        m_btnStart = new QPushButton(m_pageWelcome);
        m_btnStart->setObjectName(QStringLiteral("m_btnStart"));
        m_btnStart->setEnabled(false);

        horizontalLayout_2->addWidget(m_btnStart);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        m_phoneWidget->addWidget(m_pageWelcome);
        m_pageFinish = new QWidget();
        m_pageFinish->setObjectName(QStringLiteral("m_pageFinish"));
        verticalLayout = new QVBoxLayout(m_pageFinish);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(m_pageFinish);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(m_pageFinish);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        m_lblTotalCorrect = new QLabel(m_pageFinish);
        m_lblTotalCorrect->setObjectName(QStringLiteral("m_lblTotalCorrect"));
        m_lblTotalCorrect->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblTotalCorrect);

        m_lblTotalWrong = new QLabel(m_pageFinish);
        m_lblTotalWrong->setObjectName(QStringLiteral("m_lblTotalWrong"));
        m_lblTotalWrong->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblTotalWrong);

        m_lblTotalUnanswered = new QLabel(m_pageFinish);
        m_lblTotalUnanswered->setObjectName(QStringLiteral("m_lblTotalUnanswered"));
        m_lblTotalUnanswered->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblTotalUnanswered);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 2, 1);

        m_btnExit = new QPushButton(m_pageFinish);
        m_btnExit->setObjectName(QStringLiteral("m_btnExit"));

        gridLayout->addWidget(m_btnExit, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 2, 1);

        m_btnRestart = new QPushButton(m_pageFinish);
        m_btnRestart->setObjectName(QStringLiteral("m_btnRestart"));

        gridLayout->addWidget(m_btnRestart, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        m_phoneWidget->addWidget(m_pageFinish);

        horizontalLayout->addWidget(m_phoneWidget);


        retranslateUi(QuizSimulator);

        m_phoneWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QuizSimulator);
    } // setupUi

    void retranslateUi(QWidget *QuizSimulator)
    {
        QuizSimulator->setWindowTitle(QApplication::translate("QuizSimulator", "Form", 0));
        m_btnStart->setText(QApplication::translate("QuizSimulator", "&Start", 0));
        label->setText(QApplication::translate("QuizSimulator", "You have completed the quiz", 0));
        m_lblTotalCorrect->setText(QApplication::translate("QuizSimulator", "Total correct: %1", 0));
        m_lblTotalWrong->setText(QApplication::translate("QuizSimulator", "Total wrong: %1", 0));
        m_lblTotalUnanswered->setText(QApplication::translate("QuizSimulator", "Total unanswered: %1", 0));
        m_btnExit->setText(QApplication::translate("QuizSimulator", "&Exit", 0));
        m_btnRestart->setText(QApplication::translate("QuizSimulator", "&Restart", 0));
    } // retranslateUi

};

namespace Ui {
    class QuizSimulator: public Ui_QuizSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZSIMULATOR_H
