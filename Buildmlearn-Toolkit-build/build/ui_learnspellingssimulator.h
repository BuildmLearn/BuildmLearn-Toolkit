/********************************************************************************
** Form generated from reading UI file 'learnspellingssimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNSPELLINGSSIMULATOR_H
#define UI_LEARNSPELLINGSSIMULATOR_H

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

class Ui_LearnSpellingsSimulator
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *m_phoneWidget;
    QWidget *m_pageStopped;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_lblTitle;
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
    QWidget *m_pageListening;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_lblQuestionNumber;
    QFrame *line_3;
    QStackedWidget *m_listener;
    QWidget *m_pageQuestion;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *m_btnPlayWord;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_btnSpellIt;
    QPushButton *m_btnSkip;
    QWidget *m_pageResult;
    QVBoxLayout *verticalLayout_5;
    QLabel *m_lblResultCaption;
    QFrame *line_4;
    QLabel *m_lblEnteredWord;
    QSpacerItem *verticalSpacer_7;
    QLabel *m_lblCorrectWordDescription;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *m_btnGoToNextWord;
    QSpacerItem *horizontalSpacer_7;
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

    void setupUi(QWidget *LearnSpellingsSimulator)
    {
        if (LearnSpellingsSimulator->objectName().isEmpty())
            LearnSpellingsSimulator->setObjectName(QStringLiteral("LearnSpellingsSimulator"));
        LearnSpellingsSimulator->resize(400, 300);
        horizontalLayout = new QHBoxLayout(LearnSpellingsSimulator);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_phoneWidget = new QStackedWidget(LearnSpellingsSimulator);
        m_phoneWidget->setObjectName(QStringLiteral("m_phoneWidget"));
        m_pageStopped = new QWidget();
        m_pageStopped->setObjectName(QStringLiteral("m_pageStopped"));
        horizontalLayout_3 = new QHBoxLayout(m_pageStopped);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_lblTitle = new QLabel(m_pageStopped);
        m_lblTitle->setObjectName(QStringLiteral("m_lblTitle"));
        m_lblTitle->setText(QStringLiteral("<span style=\" font-size:18pt;\">Learn Spellings</span>"));
        m_lblTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_lblTitle);

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
        m_pageListening = new QWidget();
        m_pageListening->setObjectName(QStringLiteral("m_pageListening"));
        verticalLayout_3 = new QVBoxLayout(m_pageListening);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        m_lblQuestionNumber = new QLabel(m_pageListening);
        m_lblQuestionNumber->setObjectName(QStringLiteral("m_lblQuestionNumber"));
        m_lblQuestionNumber->setText(QStringLiteral("Question number"));

        verticalLayout_3->addWidget(m_lblQuestionNumber);

        line_3 = new QFrame(m_pageListening);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_3);

        m_listener = new QStackedWidget(m_pageListening);
        m_listener->setObjectName(QStringLiteral("m_listener"));
        m_pageQuestion = new QWidget();
        m_pageQuestion->setObjectName(QStringLiteral("m_pageQuestion"));
        verticalLayout_4 = new QVBoxLayout(m_pageQuestion);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(m_pageQuestion);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setWordWrap(true);

        verticalLayout_4->addWidget(label_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        m_btnPlayWord = new QPushButton(m_pageQuestion);
        m_btnPlayWord->setObjectName(QStringLiteral("m_btnPlayWord"));

        horizontalLayout_5->addWidget(m_btnPlayWord);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 133, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_btnSpellIt = new QPushButton(m_pageQuestion);
        m_btnSpellIt->setObjectName(QStringLiteral("m_btnSpellIt"));
        m_btnSpellIt->setEnabled(false);

        horizontalLayout_4->addWidget(m_btnSpellIt);

        m_btnSkip = new QPushButton(m_pageQuestion);
        m_btnSkip->setObjectName(QStringLiteral("m_btnSkip"));
        m_btnSkip->setEnabled(false);
        m_btnSkip->setStyleSheet(QLatin1String("QPushButton {\n"
"	color: red;\n"
"}"));

        horizontalLayout_4->addWidget(m_btnSkip);


        verticalLayout_4->addLayout(horizontalLayout_4);

        m_listener->addWidget(m_pageQuestion);
        m_pageResult = new QWidget();
        m_pageResult->setObjectName(QStringLiteral("m_pageResult"));
        verticalLayout_5 = new QVBoxLayout(m_pageResult);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        m_lblResultCaption = new QLabel(m_pageResult);
        m_lblResultCaption->setObjectName(QStringLiteral("m_lblResultCaption"));
        m_lblResultCaption->setText(QStringLiteral("This is correct spelling"));
        m_lblResultCaption->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(m_lblResultCaption);

        line_4 = new QFrame(m_pageResult);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_4);

        m_lblEnteredWord = new QLabel(m_pageResult);
        m_lblEnteredWord->setObjectName(QStringLiteral("m_lblEnteredWord"));
        m_lblEnteredWord->setText(QStringLiteral("You entered %1"));
        m_lblEnteredWord->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(m_lblEnteredWord);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_7);

        m_lblCorrectWordDescription = new QLabel(m_pageResult);
        m_lblCorrectWordDescription->setObjectName(QStringLiteral("m_lblCorrectWordDescription"));
        m_lblCorrectWordDescription->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(m_lblCorrectWordDescription);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        m_btnGoToNextWord = new QPushButton(m_pageResult);
        m_btnGoToNextWord->setObjectName(QStringLiteral("m_btnGoToNextWord"));

        horizontalLayout_6->addWidget(m_btnGoToNextWord);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_5->addLayout(horizontalLayout_6);

        m_listener->addWidget(m_pageResult);

        verticalLayout_3->addWidget(m_listener);

        m_phoneWidget->addWidget(m_pageListening);
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
        m_lblTotalCorrect->setText(QStringLiteral(""));
        m_lblTotalCorrect->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblTotalCorrect);

        m_lblTotalWrong = new QLabel(m_pageFinish);
        m_lblTotalWrong->setObjectName(QStringLiteral("m_lblTotalWrong"));
        m_lblTotalWrong->setText(QStringLiteral(""));
        m_lblTotalWrong->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblTotalWrong);

        m_lblTotalUnanswered = new QLabel(m_pageFinish);
        m_lblTotalUnanswered->setObjectName(QStringLiteral("m_lblTotalUnanswered"));
        m_lblTotalUnanswered->setText(QStringLiteral(""));
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


        retranslateUi(LearnSpellingsSimulator);

        m_phoneWidget->setCurrentIndex(0);
        m_listener->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LearnSpellingsSimulator);
    } // setupUi

    void retranslateUi(QWidget *LearnSpellingsSimulator)
    {
        LearnSpellingsSimulator->setWindowTitle(QApplication::translate("LearnSpellingsSimulator", "Form", 0));
        m_btnStart->setText(QApplication::translate("LearnSpellingsSimulator", "&Start", 0));
        label_2->setText(QApplication::translate("LearnSpellingsSimulator", "Press \"Listen\" button when you are ready. Listen to the word as many times as you want before answering. If you are not sure, you can skip the word.", 0));
        m_btnPlayWord->setText(QApplication::translate("LearnSpellingsSimulator", "Listen", 0));
        m_btnSpellIt->setText(QApplication::translate("LearnSpellingsSimulator", "&Spell it!", 0));
        m_btnSkip->setText(QApplication::translate("LearnSpellingsSimulator", "S&kip", 0));
        m_lblCorrectWordDescription->setText(QString());
        m_btnGoToNextWord->setText(QApplication::translate("LearnSpellingsSimulator", "&Next word", 0));
        label->setText(QApplication::translate("LearnSpellingsSimulator", "This was the last word", 0));
        m_btnExit->setText(QApplication::translate("LearnSpellingsSimulator", "&Exit", 0));
        m_btnRestart->setText(QApplication::translate("LearnSpellingsSimulator", "&Restart", 0));
    } // retranslateUi

};

namespace Ui {
    class LearnSpellingsSimulator: public Ui_LearnSpellingsSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNSPELLINGSSIMULATOR_H
