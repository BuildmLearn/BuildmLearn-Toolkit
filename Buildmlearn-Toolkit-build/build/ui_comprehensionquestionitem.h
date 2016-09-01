/********************************************************************************
** Form generated from reading UI file 'comprehensionquestionitem.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPREHENSIONQUESTIONITEM_H
#define UI_COMPREHENSIONQUESTIONITEM_H

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

class Ui_ComprehensionQuestionItem
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *m_lblQuestionNumber;
    QFrame *line;
    QLabel *m_lblQuestionText;
    QRadioButton *m_rbAnswerOne;
    QRadioButton *m_rbAnswerTwo;
    QRadioButton *m_rbAnswerThree;
    QRadioButton *m_rbAnswerFour;
    QSpacerItem *spacerItem;
    QLabel *m_lblWarning;
    QHBoxLayout *hboxLayout;
    QPushButton *m_btnNext;
    QPushButton *m_btnConfirm;

    void setupUi(QWidget *ComprehensionQuestionItem)
    {
        if (ComprehensionQuestionItem->objectName().isEmpty())
            ComprehensionQuestionItem->setObjectName(QStringLiteral("ComprehensionQuestionItem"));
        ComprehensionQuestionItem->resize(283, 329);
        vboxLayout = new QVBoxLayout(ComprehensionQuestionItem);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        m_lblQuestionNumber = new QLabel(ComprehensionQuestionItem);
        m_lblQuestionNumber->setObjectName(QStringLiteral("m_lblQuestionNumber"));

        vboxLayout->addWidget(m_lblQuestionNumber);

        line = new QFrame(ComprehensionQuestionItem);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        vboxLayout->addWidget(line);

        m_lblQuestionText = new QLabel(ComprehensionQuestionItem);
        m_lblQuestionText->setObjectName(QStringLiteral("m_lblQuestionText"));

        vboxLayout->addWidget(m_lblQuestionText);

        m_rbAnswerOne = new QRadioButton(ComprehensionQuestionItem);
        m_rbAnswerOne->setObjectName(QStringLiteral("m_rbAnswerOne"));

        vboxLayout->addWidget(m_rbAnswerOne);

        m_rbAnswerTwo = new QRadioButton(ComprehensionQuestionItem);
        m_rbAnswerTwo->setObjectName(QStringLiteral("m_rbAnswerTwo"));

        vboxLayout->addWidget(m_rbAnswerTwo);

        m_rbAnswerThree = new QRadioButton(ComprehensionQuestionItem);
        m_rbAnswerThree->setObjectName(QStringLiteral("m_rbAnswerThree"));

        vboxLayout->addWidget(m_rbAnswerThree);

        m_rbAnswerFour = new QRadioButton(ComprehensionQuestionItem);
        m_rbAnswerFour->setObjectName(QStringLiteral("m_rbAnswerFour"));

        vboxLayout->addWidget(m_rbAnswerFour);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        m_lblWarning = new QLabel(ComprehensionQuestionItem);
        m_lblWarning->setObjectName(QStringLiteral("m_lblWarning"));
        m_lblWarning->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(m_lblWarning);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        m_btnNext = new QPushButton(ComprehensionQuestionItem);
        m_btnNext->setObjectName(QStringLiteral("m_btnNext"));

        hboxLayout->addWidget(m_btnNext);

        m_btnConfirm = new QPushButton(ComprehensionQuestionItem);
        m_btnConfirm->setObjectName(QStringLiteral("m_btnConfirm"));

        hboxLayout->addWidget(m_btnConfirm);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(ComprehensionQuestionItem);

        QMetaObject::connectSlotsByName(ComprehensionQuestionItem);
    } // setupUi

    void retranslateUi(QWidget *ComprehensionQuestionItem)
    {
        ComprehensionQuestionItem->setWindowTitle(QApplication::translate("ComprehensionQuestionItem", "Form", 0));
        m_lblQuestionNumber->setText(QApplication::translate("ComprehensionQuestionItem", "Question number", 0));
        m_lblQuestionText->setText(QApplication::translate("ComprehensionQuestionItem", "Question text", 0));
        m_rbAnswerOne->setText(QApplication::translate("ComprehensionQuestionItem", "Answer one", 0));
        m_rbAnswerTwo->setText(QApplication::translate("ComprehensionQuestionItem", "Answer two", 0));
        m_rbAnswerThree->setText(QApplication::translate("ComprehensionQuestionItem", "Answer three", 0));
        m_rbAnswerFour->setText(QApplication::translate("ComprehensionQuestionItem", "Answer four", 0));
        m_lblWarning->setText(QString());
        m_btnNext->setText(QApplication::translate("ComprehensionQuestionItem", "&Next", 0));
        m_btnConfirm->setText(QApplication::translate("ComprehensionQuestionItem", "&Submit", 0));
    } // retranslateUi

};

namespace Ui {
    class ComprehensionQuestionItem: public Ui_ComprehensionQuestionItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPREHENSIONQUESTIONITEM_H
