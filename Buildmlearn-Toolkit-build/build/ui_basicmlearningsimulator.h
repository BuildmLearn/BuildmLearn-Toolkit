/********************************************************************************
** Form generated from reading UI file 'basicmlearningsimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICMLEARNINGSIMULATOR_H
#define UI_BASICMLEARNINGSIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicmLearningSimulator
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *m_phoneWidget;
    QWidget *m_pageStopped;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_lblHeading_2;
    QWidget *m_pageList;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *m_listItems;
    QWidget *m_pageDetails;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_lblDetails;

    void setupUi(QWidget *BasicmLearningSimulator)
    {
        if (BasicmLearningSimulator->objectName().isEmpty())
            BasicmLearningSimulator->setObjectName(QStringLiteral("BasicmLearningSimulator"));
        BasicmLearningSimulator->resize(400, 300);
        horizontalLayout = new QHBoxLayout(BasicmLearningSimulator);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_phoneWidget = new QStackedWidget(BasicmLearningSimulator);
        m_phoneWidget->setObjectName(QStringLiteral("m_phoneWidget"));
        m_pageStopped = new QWidget();
        m_pageStopped->setObjectName(QStringLiteral("m_pageStopped"));
        horizontalLayout_3 = new QHBoxLayout(m_pageStopped);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        m_lblHeading_2 = new QLabel(m_pageStopped);
        m_lblHeading_2->setObjectName(QStringLiteral("m_lblHeading_2"));
        m_lblHeading_2->setText(QStringLiteral("<span style=\" font-size:18pt;\">Basic mLearning</span>"));
        m_lblHeading_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_lblHeading_2);

        m_phoneWidget->addWidget(m_pageStopped);
        m_pageList = new QWidget();
        m_pageList->setObjectName(QStringLiteral("m_pageList"));
        horizontalLayout_2 = new QHBoxLayout(m_pageList);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_listItems = new QListWidget(m_pageList);
        m_listItems->setObjectName(QStringLiteral("m_listItems"));

        horizontalLayout_2->addWidget(m_listItems);

        m_phoneWidget->addWidget(m_pageList);
        m_pageDetails = new QWidget();
        m_pageDetails->setObjectName(QStringLiteral("m_pageDetails"));
        horizontalLayout_4 = new QHBoxLayout(m_pageDetails);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        m_lblDetails = new QLabel(m_pageDetails);
        m_lblDetails->setObjectName(QStringLiteral("m_lblDetails"));
        m_lblDetails->setAlignment(Qt::AlignCenter);
        m_lblDetails->setWordWrap(true);

        horizontalLayout_4->addWidget(m_lblDetails);

        m_phoneWidget->addWidget(m_pageDetails);

        horizontalLayout->addWidget(m_phoneWidget);


        retranslateUi(BasicmLearningSimulator);

        m_phoneWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BasicmLearningSimulator);
    } // setupUi

    void retranslateUi(QWidget *BasicmLearningSimulator)
    {
        BasicmLearningSimulator->setWindowTitle(QApplication::translate("BasicmLearningSimulator", "Form", 0));
        m_lblDetails->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BasicmLearningSimulator: public Ui_BasicmLearningSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICMLEARNINGSIMULATOR_H
