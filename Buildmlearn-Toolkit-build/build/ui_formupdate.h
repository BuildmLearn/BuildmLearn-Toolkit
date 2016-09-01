/********************************************************************************
** Form generated from reading UI file 'formupdate.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUPDATE_H
#define UI_FORMUPDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include "labelwithstatus.h"

QT_BEGIN_NAMESPACE

class Ui_FormUpdate
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *m_lblCurrentRelease;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *m_txtChanges;
    QLabel *m_lblAvailableRelease;
    QLabel *label_2;
    LabelWithStatus *m_lblStatus;
    QDialogButtonBox *m_buttonBox;

    void setupUi(QDialog *FormUpdate)
    {
        if (FormUpdate->objectName().isEmpty())
            FormUpdate->setObjectName(QStringLiteral("FormUpdate"));
        FormUpdate->resize(488, 328);
        verticalLayout = new QVBoxLayout(FormUpdate);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(FormUpdate);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        m_lblCurrentRelease = new QLabel(FormUpdate);
        m_lblCurrentRelease->setObjectName(QStringLiteral("m_lblCurrentRelease"));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_lblCurrentRelease);

        label_3 = new QLabel(FormUpdate);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(FormUpdate);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        m_txtChanges = new QTextEdit(FormUpdate);
        m_txtChanges->setObjectName(QStringLiteral("m_txtChanges"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(m_txtChanges->sizePolicy().hasHeightForWidth());
        m_txtChanges->setSizePolicy(sizePolicy);
        m_txtChanges->setUndoRedoEnabled(false);
        m_txtChanges->setLineWrapMode(QTextEdit::WidgetWidth);
        m_txtChanges->setReadOnly(true);
        m_txtChanges->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>"));
        m_txtChanges->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        formLayout->setWidget(3, QFormLayout::FieldRole, m_txtChanges);

        m_lblAvailableRelease = new QLabel(FormUpdate);
        m_lblAvailableRelease->setObjectName(QStringLiteral("m_lblAvailableRelease"));

        formLayout->setWidget(1, QFormLayout::FieldRole, m_lblAvailableRelease);

        label_2 = new QLabel(FormUpdate);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        m_lblStatus = new LabelWithStatus(FormUpdate);
        m_lblStatus->setObjectName(QStringLiteral("m_lblStatus"));
        m_lblStatus->setLayoutDirection(Qt::RightToLeft);

        formLayout->setWidget(2, QFormLayout::FieldRole, m_lblStatus);


        verticalLayout->addLayout(formLayout);

        m_buttonBox = new QDialogButtonBox(FormUpdate);
        m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
        m_buttonBox->setOrientation(Qt::Horizontal);
        m_buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(m_buttonBox);

#ifndef QT_NO_SHORTCUT
        label_4->setBuddy(m_txtChanges);
        label_2->setBuddy(m_lblStatus);
#endif // QT_NO_SHORTCUT

        retranslateUi(FormUpdate);
        QObject::connect(m_buttonBox, SIGNAL(accepted()), FormUpdate, SLOT(accept()));
        QObject::connect(m_buttonBox, SIGNAL(rejected()), FormUpdate, SLOT(reject()));

        QMetaObject::connectSlotsByName(FormUpdate);
    } // setupUi

    void retranslateUi(QDialog *FormUpdate)
    {
        FormUpdate->setWindowTitle(QApplication::translate("FormUpdate", "Check for updates", 0));
        label->setText(QApplication::translate("FormUpdate", "Current release", 0));
        m_lblCurrentRelease->setText(QString());
        label_3->setText(QApplication::translate("FormUpdate", "Available release", 0));
        label_4->setText(QApplication::translate("FormUpdate", "Changes", 0));
        m_lblAvailableRelease->setText(QString());
        label_2->setText(QApplication::translate("FormUpdate", "Status", 0));
    } // retranslateUi

};

namespace Ui {
    class FormUpdate: public Ui_FormUpdate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUPDATE_H
