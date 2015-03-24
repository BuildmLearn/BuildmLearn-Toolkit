/********************************************************************************
** Form generated from reading UI file 'formhelp.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMHELP_H
#define UI_FORMHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FormHelp
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *m_txtHelp;
    QCheckBox *m_cmbDoNotShowAgain;
    QDialogButtonBox *m_buttonBox;

    void setupUi(QDialog *FormHelp)
    {
        if (FormHelp->objectName().isEmpty())
            FormHelp->setObjectName(QStringLiteral("FormHelp"));
        FormHelp->resize(621, 348);
        verticalLayout = new QVBoxLayout(FormHelp);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_txtHelp = new QTextBrowser(FormHelp);
        m_txtHelp->setObjectName(QStringLiteral("m_txtHelp"));
        m_txtHelp->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>"));
        m_txtHelp->setTextInteractionFlags(Qt::TextBrowserInteraction);
        m_txtHelp->setOpenExternalLinks(true);

        verticalLayout->addWidget(m_txtHelp);

        m_cmbDoNotShowAgain = new QCheckBox(FormHelp);
        m_cmbDoNotShowAgain->setObjectName(QStringLiteral("m_cmbDoNotShowAgain"));

        verticalLayout->addWidget(m_cmbDoNotShowAgain);

        m_buttonBox = new QDialogButtonBox(FormHelp);
        m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
        m_buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(m_buttonBox);


        retranslateUi(FormHelp);
        QObject::connect(m_buttonBox, SIGNAL(accepted()), FormHelp, SLOT(accept()));

        QMetaObject::connectSlotsByName(FormHelp);
    } // setupUi

    void retranslateUi(QDialog *FormHelp)
    {
        FormHelp->setWindowTitle(QApplication::translate("FormHelp", "Help", 0));
        m_cmbDoNotShowAgain->setText(QApplication::translate("FormHelp", "Do not show this dialog again.", 0));
    } // retranslateUi

};

namespace Ui {
    class FormHelp: public Ui_FormHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMHELP_H
