/********************************************************************************
** Form generated from reading UI file 'formuploadbundle.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUPLOADBUNDLE_H
#define UI_FORMUPLOADBUNDLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "labelwithstatus.h"
#include "lineeditwithstatus.h"

QT_BEGIN_NAMESPACE

class Ui_FormUploadBundle
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label_4;
    LineEditWithStatus *m_txtApplicationName;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *m_btnSelectIcon;
    LabelWithStatus *m_lblIcon;
    QLabel *label_5;
    QTextEdit *m_txtApplicationDescription;
    QLabel *label_2;
    LineEditWithStatus *m_txtAuthorName;
    QLabel *label_3;
    LineEditWithStatus *m_txtAuthorEmail;
    QLabel *label;
    QComboBox *m_cmbCategory;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QProgressBar *m_progressUpload;
    LabelWithStatus *m_lblProgress;
    QDialogButtonBox *m_buttonBox;

    void setupUi(QDialog *FormUploadBundle)
    {
        if (FormUploadBundle->objectName().isEmpty())
            FormUploadBundle->setObjectName(QStringLiteral("FormUploadBundle"));
        FormUploadBundle->resize(562, 382);
        verticalLayout = new QVBoxLayout(FormUploadBundle);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(FormUploadBundle);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        m_txtApplicationName = new LineEditWithStatus(groupBox);
        m_txtApplicationName->setObjectName(QStringLiteral("m_txtApplicationName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_txtApplicationName);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_btnSelectIcon = new QToolButton(groupBox);
        m_btnSelectIcon->setObjectName(QStringLiteral("m_btnSelectIcon"));

        horizontalLayout_2->addWidget(m_btnSelectIcon);

        m_lblIcon = new LabelWithStatus(groupBox);
        m_lblIcon->setObjectName(QStringLiteral("m_lblIcon"));
        m_lblIcon->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(m_lblIcon);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_2);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        m_txtApplicationDescription = new QTextEdit(groupBox);
        m_txtApplicationDescription->setObjectName(QStringLiteral("m_txtApplicationDescription"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(m_txtApplicationDescription->sizePolicy().hasHeightForWidth());
        m_txtApplicationDescription->setSizePolicy(sizePolicy1);
        m_txtApplicationDescription->setTabChangesFocus(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, m_txtApplicationDescription);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        m_txtAuthorName = new LineEditWithStatus(groupBox);
        m_txtAuthorName->setObjectName(QStringLiteral("m_txtAuthorName"));

        formLayout->setWidget(3, QFormLayout::FieldRole, m_txtAuthorName);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        m_txtAuthorEmail = new LineEditWithStatus(groupBox);
        m_txtAuthorEmail->setObjectName(QStringLiteral("m_txtAuthorEmail"));

        formLayout->setWidget(4, QFormLayout::FieldRole, m_txtAuthorEmail);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label);

        m_cmbCategory = new QComboBox(groupBox);
        m_cmbCategory->setObjectName(QStringLiteral("m_cmbCategory"));

        formLayout->setWidget(5, QFormLayout::FieldRole, m_cmbCategory);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(FormUploadBundle);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_progressUpload = new QProgressBar(groupBox_2);
        m_progressUpload->setObjectName(QStringLiteral("m_progressUpload"));
        m_progressUpload->setLayoutDirection(Qt::RightToLeft);
        m_progressUpload->setValue(0);
        m_progressUpload->setInvertedAppearance(false);

        horizontalLayout->addWidget(m_progressUpload);

        m_lblProgress = new LabelWithStatus(groupBox_2);
        m_lblProgress->setObjectName(QStringLiteral("m_lblProgress"));
        m_lblProgress->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout->addWidget(m_lblProgress);


        verticalLayout->addWidget(groupBox_2);

        m_buttonBox = new QDialogButtonBox(FormUploadBundle);
        m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
        m_buttonBox->setOrientation(Qt::Horizontal);
        m_buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(m_buttonBox);

        QWidget::setTabOrder(m_cmbCategory, m_buttonBox);
        QWidget::setTabOrder(m_buttonBox, m_txtApplicationDescription);

        retranslateUi(FormUploadBundle);
        QObject::connect(m_buttonBox, SIGNAL(accepted()), FormUploadBundle, SLOT(accept()));
        QObject::connect(m_buttonBox, SIGNAL(rejected()), FormUploadBundle, SLOT(reject()));

        QMetaObject::connectSlotsByName(FormUploadBundle);
    } // setupUi

    void retranslateUi(QDialog *FormUploadBundle)
    {
        FormUploadBundle->setWindowTitle(QApplication::translate("FormUploadBundle", "Submit application to BuildmLearn Store", 0));
        groupBox->setTitle(QApplication::translate("FormUploadBundle", "Application metadata", 0));
        label_4->setText(QApplication::translate("FormUploadBundle", "Application name", 0));
        label_6->setText(QApplication::translate("FormUploadBundle", "Application icon", 0));
        m_btnSelectIcon->setText(QApplication::translate("FormUploadBundle", "...", 0));
        label_5->setText(QApplication::translate("FormUploadBundle", "Application description", 0));
        label_2->setText(QApplication::translate("FormUploadBundle", "Author name", 0));
        label_3->setText(QApplication::translate("FormUploadBundle", "Author e-mail", 0));
        label->setText(QApplication::translate("FormUploadBundle", "Category", 0));
        groupBox_2->setTitle(QApplication::translate("FormUploadBundle", "Progress of uploading", 0));
    } // retranslateUi

};

namespace Ui {
    class FormUploadBundle: public Ui_FormUploadBundle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUPLOADBUNDLE_H
