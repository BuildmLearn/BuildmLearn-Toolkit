/********************************************************************************
** Form generated from reading UI file 'formsimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSIMULATOR_H
#define UI_FORMSIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "plaintoolbutton.h"

QT_BEGIN_NAMESPACE

class Ui_FormSimulator
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *m_simulatorScrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *m_phoneWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    PlainToolButton *m_btnGoBack;
    PlainToolButton *m_btnStopSimulation;
    PlainToolButton *m_btnRunSimulation;

    void setupUi(QDialog *FormSimulator)
    {
        if (FormSimulator->objectName().isEmpty())
            FormSimulator->setObjectName(QStringLiteral("FormSimulator"));
        FormSimulator->resize(390, 417);
        verticalLayout = new QVBoxLayout(FormSimulator);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_simulatorScrollArea = new QScrollArea(FormSimulator);
        m_simulatorScrollArea->setObjectName(QStringLiteral("m_simulatorScrollArea"));
        m_simulatorScrollArea->setWidgetResizable(true);
        m_simulatorScrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 370, 369));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        m_phoneWidget = new QLabel(scrollAreaWidgetContents);
        m_phoneWidget->setObjectName(QStringLiteral("m_phoneWidget"));
        m_phoneWidget->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_phoneWidget, 1, 1, 1, 1);

        m_simulatorScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(m_simulatorScrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnGoBack = new PlainToolButton(FormSimulator);
        m_btnGoBack->setObjectName(QStringLiteral("m_btnGoBack"));
        m_btnGoBack->setEnabled(false);

        horizontalLayout->addWidget(m_btnGoBack);

        m_btnStopSimulation = new PlainToolButton(FormSimulator);
        m_btnStopSimulation->setObjectName(QStringLiteral("m_btnStopSimulation"));
        m_btnStopSimulation->setEnabled(false);

        horizontalLayout->addWidget(m_btnStopSimulation);

        m_btnRunSimulation = new PlainToolButton(FormSimulator);
        m_btnRunSimulation->setObjectName(QStringLiteral("m_btnRunSimulation"));
        m_btnRunSimulation->setEnabled(false);

        horizontalLayout->addWidget(m_btnRunSimulation);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FormSimulator);

        QMetaObject::connectSlotsByName(FormSimulator);
    } // setupUi

    void retranslateUi(QDialog *FormSimulator)
    {
        FormSimulator->setWindowTitle(QApplication::translate("FormSimulator", "Simulator", 0));
        m_phoneWidget->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnGoBack->setToolTip(QApplication::translate("FormSimulator", "Goes one step backwards in running simulation.", 0));
#endif // QT_NO_TOOLTIP
        m_btnGoBack->setText(QApplication::translate("FormSimulator", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnStopSimulation->setToolTip(QApplication::translate("FormSimulator", "Stops running simulation.", 0));
#endif // QT_NO_TOOLTIP
        m_btnStopSimulation->setText(QApplication::translate("FormSimulator", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_btnRunSimulation->setToolTip(QApplication::translate("FormSimulator", "Starts new simulation.", 0));
#endif // QT_NO_TOOLTIP
        m_btnRunSimulation->setText(QApplication::translate("FormSimulator", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class FormSimulator: public Ui_FormSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSIMULATOR_H
