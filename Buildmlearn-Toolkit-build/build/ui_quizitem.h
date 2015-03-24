/********************************************************************************
** Form generated from reading UI file 'quizitem.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZITEM_H
#define UI_QUIZITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuizItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *m_lblQuestionNumber;
    QFrame *line;
    QLabel *m_lblQuestionText;
    QRadioButton *m_rbAnswerOne;
    QRadioButton *m_rbAnswerTwo;
    QRadioButton *m_rbAnswerThree;
    QRadioButton *m_rbAnswerFour;
    QSpacerItem *verticalSpacer;
    QLabel *m_lblWarning;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnNext;
    QPushButton *m_btnConfirm;

    void setupUi(QWidget *QuizItem)
    {
        if (QuizItem->objectName().isEmpty())
            QuizItem->setObjectName(QStringLiteral("QuizItem"));
        QuizItem->resize(283, 329);
        verticalLayout = new QVBoxLayout(QuizItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_lblQuestionNumber = new QLabel(QuizItem);
        m_lblQuestionNumber->setObjectName(QStringLiteral("m_lblQuestionNumber"));

        verticalLayout->addWidget(m_lblQuestionNumber);

        line = new QFrame(QuizItem);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        m_lblQuestionText = new QLabel(QuizItem);
        m_lblQuestionText->setObjectName(QStringLiteral("m_lblQuestionText"));

        verticalLayout->addWidget(m_lblQuestionText);

        m_rbAnswerOne = new QRadioButton(QuizItem);
        m_rbAnswerOne->setObjectName(QStringLiteral("m_rbAnswerOne"));

        verticalLayout->addWidget(m_rbAnswerOne);

        m_rbAnswerTwo = new QRadioButton(QuizItem);
        m_rbAnswerTwo->setObjectName(QStringLiteral("m_rbAnswerTwo"));

        verticalLayout->addWidget(m_rbAnswerTwo);

        m_rbAnswerThree = new QRadioButton(QuizItem);
        m_rbAnswerThree->setObjectName(QStringLiteral("m_rbAnswerThree"));

        verticalLayout->addWidget(m_rbAnswerThree);

        m_rbAnswerFour = new QRadioButton(QuizItem);
        m_rbAnswerFour->setObjectName(QStringLiteral("m_rbAnswerFour"));

        verticalLayout->addWidget(m_rbAnswerFour);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_lblWarning = new QLabel(QuizItem);
        m_lblWarning->setObjectName(QStringLiteral("m_lblWarning"));
        m_lblWarning->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblWarning);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_btnNext = new QPushButton(QuizItem);
        m_btnNext->setObjectName(QStringLiteral("m_btnNext"));

        horizontalLayout->addWidget(m_btnNext);

        m_btnConfirm = new QPushButton(QuizItem);
        m_btnConfirm->setObjectName(QStringLiteral("m_btnConfirm"));

        horizontalLayout->addWidget(m_btnConfirm);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QuizItem);

        QMetaObject::connectSlotsByName(QuizItem);
    } // setupUi

    void retranslateUi(QWidget *QuizItem)
    {
        QuizItem->setWindowTitle(QApplication::translate("QuizItem", "Form", 0));
        m_lblQuestionNumber->setText(QApplication::translate("QuizItem", "Question number", 0));
        m_lblQuestionText->setText(QApplication::translate("QuizItem", "Question text", 0));
        m_rbAnswerOne->setText(QApplication::translate("QuizItem", "Answer one", 0));
        m_rbAnswerTwo->setText(QApplication::translate("QuizItem", "Answer two", 0));
        m_rbAnswerThree->setText(QApplication::translate("QuizItem", "Answer three", 0));
        m_rbAnswerFour->setText(QApplication::translate("QuizItem", "Answer four", 0));
        m_lblWarning->setText(QString());
        m_btnNext->setText(QApplication::translate("QuizItem", "&Next", 0));
        m_btnConfirm->setText(QApplication::translate("QuizItem", "&Submit", 0));
    } // retranslateUi

};

namespace Ui {
    class QuizItem: public Ui_QuizItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZITEM_H
