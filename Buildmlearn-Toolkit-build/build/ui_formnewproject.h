/********************************************************************************
** Form generated from reading UI file 'formnewproject.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMNEWPROJECT_H
#define UI_FORMNEWPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FormNewProject
{
public:
    QGridLayout *gridLayout_2;
    QDialogButtonBox *m_buttonBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *m_lblThumbnail;
    QLabel *m_lblDescription;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *m_listTemplates;

    void setupUi(QDialog *FormNewProject)
    {
        if (FormNewProject->objectName().isEmpty())
            FormNewProject->setObjectName(QStringLiteral("FormNewProject"));
        FormNewProject->resize(664, 458);
        gridLayout_2 = new QGridLayout(FormNewProject);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_buttonBox = new QDialogButtonBox(FormNewProject);
        m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
        m_buttonBox->setOrientation(Qt::Horizontal);
        m_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(m_buttonBox, 2, 0, 1, 2);

        groupBox = new QGroupBox(FormNewProject);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_lblThumbnail = new QLabel(groupBox);
        m_lblThumbnail->setObjectName(QStringLiteral("m_lblThumbnail"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_lblThumbnail->sizePolicy().hasHeightForWidth());
        m_lblThumbnail->setSizePolicy(sizePolicy);
        m_lblThumbnail->setMinimumSize(QSize(200, 213));
        m_lblThumbnail->setMaximumSize(QSize(200, 213));
        m_lblThumbnail->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblThumbnail);

        m_lblDescription = new QLabel(groupBox);
        m_lblDescription->setObjectName(QStringLiteral("m_lblDescription"));
        m_lblDescription->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        m_lblDescription->setWordWrap(true);

        verticalLayout->addWidget(m_lblDescription);


        gridLayout_2->addWidget(groupBox, 0, 1, 2, 1);

        groupBox_2 = new QGroupBox(FormNewProject);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_listTemplates = new QListWidget(groupBox_2);
        m_listTemplates->setObjectName(QStringLiteral("m_listTemplates"));

        horizontalLayout_2->addWidget(m_listTemplates);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 2, 1);

        QWidget::setTabOrder(m_listTemplates, m_buttonBox);

        retranslateUi(FormNewProject);
        QObject::connect(m_buttonBox, SIGNAL(accepted()), FormNewProject, SLOT(accept()));
        QObject::connect(m_buttonBox, SIGNAL(rejected()), FormNewProject, SLOT(reject()));

        QMetaObject::connectSlotsByName(FormNewProject);
    } // setupUi

    void retranslateUi(QDialog *FormNewProject)
    {
        FormNewProject->setWindowTitle(QApplication::translate("FormNewProject", "Create new project", 0));
        groupBox->setTitle(QApplication::translate("FormNewProject", "Description of selected template", 0));
        m_lblThumbnail->setText(QString());
        m_lblDescription->setText(QApplication::translate("FormNewProject", "aaa", 0));
        groupBox_2->setTitle(QApplication::translate("FormNewProject", "Available templates", 0));
    } // retranslateUi

};

namespace Ui {
    class FormNewProject: public Ui_FormNewProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMNEWPROJECT_H
