/********************************************************************************
** Form generated from reading UI file 'formabout.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMABOUT_H
#define UI_FORMABOUT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAbout
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *m_formLayout;
    QLabel *m_lblIcon;
    QLabel *m_lblDesc;
    QTabWidget *m_tabAbout;
    QWidget *m_tabInfo;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *m_txtInfo;
    QWidget *m_tabChangelog;
    QVBoxLayout *verticalLayout_7;
    QTextBrowser *m_txtChangelog;
    QLabel *m_lblChangelog;
    QWidget *m_tabLicense;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *m_txtLicense;
    QLabel *m_lblLicense;
    QDialogButtonBox *m_buttonBox;

    void setupUi(QDialog *FormAbout)
    {
        if (FormAbout->objectName().isEmpty())
            FormAbout->setObjectName(QStringLiteral("FormAbout"));
        FormAbout->resize(554, 366);
        FormAbout->setWindowTitle(QStringLiteral(""));
        FormAbout->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(FormAbout);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_formLayout = new QFormLayout();
        m_formLayout->setObjectName(QStringLiteral("m_formLayout"));
        m_formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_lblIcon = new QLabel(FormAbout);
        m_lblIcon->setObjectName(QStringLiteral("m_lblIcon"));
        m_lblIcon->setMinimumSize(QSize(90, 90));
        m_lblIcon->setMaximumSize(QSize(90, 90));
        m_lblIcon->setStyleSheet(QStringLiteral(""));
        m_lblIcon->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        m_lblIcon->setTextFormat(Qt::RichText);
        m_lblIcon->setScaledContents(true);
        m_lblIcon->setAlignment(Qt::AlignCenter);

        m_formLayout->setWidget(0, QFormLayout::LabelRole, m_lblIcon);

        m_lblDesc = new QLabel(FormAbout);
        m_lblDesc->setObjectName(QStringLiteral("m_lblDesc"));
        m_lblDesc->setMinimumSize(QSize(0, 60));
        m_lblDesc->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        m_lblDesc->setTextFormat(Qt::RichText);
        m_lblDesc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        m_lblDesc->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        m_formLayout->setWidget(0, QFormLayout::FieldRole, m_lblDesc);


        verticalLayout->addLayout(m_formLayout);

        m_tabAbout = new QTabWidget(FormAbout);
        m_tabAbout->setObjectName(QStringLiteral("m_tabAbout"));
        m_tabAbout->setStyleSheet(QStringLiteral(""));
        m_tabAbout->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        m_tabInfo = new QWidget();
        m_tabInfo->setObjectName(QStringLiteral("m_tabInfo"));
        verticalLayout_2 = new QVBoxLayout(m_tabInfo);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_txtInfo = new QTextBrowser(m_tabInfo);
        m_txtInfo->setObjectName(QStringLiteral("m_txtInfo"));
        m_txtInfo->setContextMenuPolicy(Qt::DefaultContextMenu);
        m_txtInfo->setStyleSheet(QStringLiteral(""));
        m_txtInfo->setFrameShape(QFrame::NoFrame);
        m_txtInfo->setUndoRedoEnabled(false);
        m_txtInfo->setReadOnly(true);
        m_txtInfo->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>"));
        m_txtInfo->setAcceptRichText(false);
        m_txtInfo->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        m_txtInfo->setOpenExternalLinks(true);

        verticalLayout_2->addWidget(m_txtInfo);

        m_tabAbout->addTab(m_tabInfo, QString());
        m_tabChangelog = new QWidget();
        m_tabChangelog->setObjectName(QStringLiteral("m_tabChangelog"));
        verticalLayout_7 = new QVBoxLayout(m_tabChangelog);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        m_txtChangelog = new QTextBrowser(m_tabChangelog);
        m_txtChangelog->setObjectName(QStringLiteral("m_txtChangelog"));
        m_txtChangelog->setFrameShape(QFrame::NoFrame);
        m_txtChangelog->setUndoRedoEnabled(false);
        m_txtChangelog->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>"));
        m_txtChangelog->setAcceptRichText(false);
        m_txtChangelog->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        m_txtChangelog->setOpenExternalLinks(true);

        verticalLayout_7->addWidget(m_txtChangelog);

        m_lblChangelog = new QLabel(m_tabChangelog);
        m_lblChangelog->setObjectName(QStringLiteral("m_lblChangelog"));

        verticalLayout_7->addWidget(m_lblChangelog);

        m_tabAbout->addTab(m_tabChangelog, QString());
        m_tabLicense = new QWidget();
        m_tabLicense->setObjectName(QStringLiteral("m_tabLicense"));
        verticalLayout_3 = new QVBoxLayout(m_tabLicense);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        m_txtLicense = new QTextBrowser(m_tabLicense);
        m_txtLicense->setObjectName(QStringLiteral("m_txtLicense"));
        m_txtLicense->setFrameShape(QFrame::NoFrame);
        m_txtLicense->setUndoRedoEnabled(false);
        m_txtLicense->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>"));
        m_txtLicense->setAcceptRichText(false);
        m_txtLicense->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        m_txtLicense->setOpenExternalLinks(true);

        verticalLayout_3->addWidget(m_txtLicense);

        m_lblLicense = new QLabel(m_tabLicense);
        m_lblLicense->setObjectName(QStringLiteral("m_lblLicense"));

        verticalLayout_3->addWidget(m_lblLicense);

        m_tabAbout->addTab(m_tabLicense, QString());

        verticalLayout->addWidget(m_tabAbout);

        m_buttonBox = new QDialogButtonBox(FormAbout);
        m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
        m_buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(m_buttonBox);


        retranslateUi(FormAbout);
        QObject::connect(m_buttonBox, SIGNAL(accepted()), FormAbout, SLOT(accept()));

        m_tabAbout->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormAbout);
    } // setupUi

    void retranslateUi(QDialog *FormAbout)
    {
        m_lblIcon->setText(QString());
        m_lblDesc->setText(QString());
        m_txtInfo->setSearchPaths(QStringList());
        m_tabAbout->setTabText(m_tabAbout->indexOf(m_tabInfo), QApplication::translate("FormAbout", "Information", 0));
        m_lblChangelog->setText(QApplication::translate("FormAbout", "Changelog page is available only in English language.", 0));
        m_tabAbout->setTabText(m_tabAbout->indexOf(m_tabChangelog), QApplication::translate("FormAbout", "Changelog", 0));
        m_lblLicense->setText(QApplication::translate("FormAbout", "License page is available only in English language.", 0));
        m_tabAbout->setTabText(m_tabAbout->indexOf(m_tabLicense), QApplication::translate("FormAbout", "License", 0));
        Q_UNUSED(FormAbout);
    } // retranslateUi

};

namespace Ui {
    class FormAbout: public Ui_FormAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMABOUT_H
