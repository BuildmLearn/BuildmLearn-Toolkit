/********************************************************************************
** Form generated from reading UI file 'comprehensionpassageitem.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPREHENSIONPASSAGEITEM_H
#define UI_COMPREHENSIONPASSAGEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComprehensionPassageItem
{
public:
    QLabel *m_lblPassageText;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *m_exitquiz;
    QPushButton *m_startquiz;
    QFrame *line;
    QLabel *m_lblQuizName;

    void setupUi(QWidget *ComprehensionPassageItem)
    {
        if (ComprehensionPassageItem->objectName().isEmpty())
            ComprehensionPassageItem->setObjectName(QStringLiteral("ComprehensionPassageItem"));
        ComprehensionPassageItem->resize(299, 323);
        m_lblPassageText = new QLabel(ComprehensionPassageItem);
        m_lblPassageText->setObjectName(QStringLiteral("m_lblPassageText"));
        m_lblPassageText->setGeometry(QRect(10, 50, 265, 61));
        layoutWidget = new QWidget(ComprehensionPassageItem);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 290, 251, 25));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        m_exitquiz = new QPushButton(layoutWidget);
        m_exitquiz->setObjectName(QStringLiteral("m_exitquiz"));

        hboxLayout->addWidget(m_exitquiz);

        m_startquiz = new QPushButton(layoutWidget);
        m_startquiz->setObjectName(QStringLiteral("m_startquiz"));

        hboxLayout->addWidget(m_startquiz);

        line = new QFrame(ComprehensionPassageItem);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 40, 265, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_lblQuizName = new QLabel(ComprehensionPassageItem);
        m_lblQuizName->setObjectName(QStringLiteral("m_lblQuizName"));
        m_lblQuizName->setGeometry(QRect(10, 20, 265, 14));

        retranslateUi(ComprehensionPassageItem);

        QMetaObject::connectSlotsByName(ComprehensionPassageItem);
    } // setupUi

    void retranslateUi(QWidget *ComprehensionPassageItem)
    {
        ComprehensionPassageItem->setWindowTitle(QApplication::translate("ComprehensionPassageItem", "Form", 0));
        m_lblPassageText->setText(QApplication::translate("ComprehensionPassageItem", "Passage", 0));
        m_exitquiz->setText(QApplication::translate("ComprehensionPassageItem", "Exit ", 0));
        m_startquiz->setText(QApplication::translate("ComprehensionPassageItem", "Questions", 0));
        m_lblQuizName->setText(QApplication::translate("ComprehensionPassageItem", "Quiz name ", 0));
    } // retranslateUi

};

namespace Ui {
    class ComprehensionPassageItem: public Ui_ComprehensionPassageItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPREHENSIONPASSAGEITEM_H
