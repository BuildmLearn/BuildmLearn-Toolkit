/********************************************************************************
** Form generated from reading UI file 'formsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSETTINGS_H
#define UI_FORMSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "dynamicshortcutswidget.h"
#include "labelwithstatus.h"

QT_BEGIN_NAMESPACE

class Ui_FormSettings
{
public:
    QGridLayout *gridLayout;
    QListWidget *m_listSettings;
    QDialogButtonBox *m_buttonBox;
    QStackedWidget *m_stackedSettings;
    QWidget *m_pageGeneral;
    QFormLayout *formLayout_2;
    QCheckBox *m_checkCheckForUpdatesOnStartup;
    QWidget *m_pageUi;
    QHBoxLayout *horizontalLayout;
    QTabWidget *m_tabUi;
    QWidget *m_tabIconSkin;
    QHBoxLayout *horizontalLayout_8;
    QScrollArea *m_scrollIconSkins;
    QWidget *scrollAreaWidgetContents_2;
    QFormLayout *formLayout;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_9;
    QTreeWidget *m_treeSkins;
    QLabel *m_lblActiveCaption;
    QLabel *m_lblActiveContents;
    QLabel *m_lblSelectedCaption;
    QLabel *m_lblSelectedContents;
    QGroupBox *groupBox;
    QFormLayout *formLayout_8;
    QLabel *m_lblIconTheme;
    QComboBox *m_cmbIconTheme;
    QWidget *m_pageShortcuts;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *m_scrollShortcuts;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_4;
    DynamicShortcutsWidget *m_shortcutsEditor;
    QWidget *m_pageLanguages;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *m_treeLanguages;
    QWidget *m_pageProxy;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *m_tabBrowserProxy;
    QWidget *m_tabExternalBrowser;
    QFormLayout *formLayout_17;
    QGroupBox *m_grpCustomExternalBrowser;
    QFormLayout *formLayout_12;
    QLabel *m_lblExternalBrowserExecutable;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *m_txtExternalBrowserExecutable;
    QToolButton *m_btnExternalBrowserExecutable;
    QLabel *m_lblExternalBrowserArguments;
    QLineEdit *m_txtExternalBrowserArguments;
    QLabel *m_lblExternalBrowserPreset;
    QComboBox *m_cmbExternalBrowserPreset;
    QLabel *label;
    QWidget *m_tabProxy;
    QFormLayout *formLayout_6;
    QLabel *m_lblProxyType;
    QComboBox *m_cmbProxyType;
    QLabel *m_lblProxyHost;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *m_txtProxyHost;
    QLabel *m_lblProxyPort;
    QSpinBox *m_spinProxyPort;
    QLabel *m_lblProxyUsername;
    QLineEdit *m_txtProxyUsername;
    QLabel *m_lblProxyPassword;
    QLineEdit *m_txtProxyPassword;
    QCheckBox *m_checkShowPassword;
    QLabel *m_lblProxyInfo;
    QWidget *m_pageExternalApplications;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *m_btnSelectSignapk;
    LabelWithStatus *m_lblExternalSignapk;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *m_btnSelectZip;
    LabelWithStatus *m_lblExternalZip;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *m_btnSelectJava;
    LabelWithStatus *m_lblExternalJava;
    QWidget *m_pageApkGeneration;
    QFormLayout *formLayout_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *m_btnGenerationTempSelect;
    QLabel *m_lblGenerationTemp;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *m_btnGenerationOutputSelect;
    QLabel *m_lblGenerationOutput;
    QLabel *label_3;
    QLineEdit *m_txtGenerationOutputFilePattern;
    QLabel *m_lblGenerationInfo;

    void setupUi(QDialog *FormSettings)
    {
        if (FormSettings->objectName().isEmpty())
            FormSettings->setObjectName(QStringLiteral("FormSettings"));
        FormSettings->resize(820, 427);
        gridLayout = new QGridLayout(FormSettings);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_listSettings = new QListWidget(FormSettings);
        new QListWidgetItem(m_listSettings);
        new QListWidgetItem(m_listSettings);
        new QListWidgetItem(m_listSettings);
        new QListWidgetItem(m_listSettings);
        new QListWidgetItem(m_listSettings);
        new QListWidgetItem(m_listSettings);
        new QListWidgetItem(m_listSettings);
        m_listSettings->setObjectName(QStringLiteral("m_listSettings"));
        m_listSettings->setMinimumSize(QSize(220, 0));
        m_listSettings->setMaximumSize(QSize(220, 16777215));
        m_listSettings->setProperty("showDropIndicator", QVariant(false));
        m_listSettings->setAlternatingRowColors(false);
        m_listSettings->setMovement(QListView::Static);
        m_listSettings->setSelectionRectVisible(false);

        gridLayout->addWidget(m_listSettings, 0, 0, 1, 1);

        m_buttonBox = new QDialogButtonBox(FormSettings);
        m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
        m_buttonBox->setOrientation(Qt::Horizontal);
        m_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(m_buttonBox, 1, 0, 1, 2);

        m_stackedSettings = new QStackedWidget(FormSettings);
        m_stackedSettings->setObjectName(QStringLiteral("m_stackedSettings"));
        m_pageGeneral = new QWidget();
        m_pageGeneral->setObjectName(QStringLiteral("m_pageGeneral"));
        formLayout_2 = new QFormLayout(m_pageGeneral);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        m_checkCheckForUpdatesOnStartup = new QCheckBox(m_pageGeneral);
        m_checkCheckForUpdatesOnStartup->setObjectName(QStringLiteral("m_checkCheckForUpdatesOnStartup"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, m_checkCheckForUpdatesOnStartup);

        m_stackedSettings->addWidget(m_pageGeneral);
        m_pageUi = new QWidget();
        m_pageUi->setObjectName(QStringLiteral("m_pageUi"));
        horizontalLayout = new QHBoxLayout(m_pageUi);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_tabUi = new QTabWidget(m_pageUi);
        m_tabUi->setObjectName(QStringLiteral("m_tabUi"));
        m_tabUi->setTabPosition(QTabWidget::North);
        m_tabIconSkin = new QWidget();
        m_tabIconSkin->setObjectName(QStringLiteral("m_tabIconSkin"));
        horizontalLayout_8 = new QHBoxLayout(m_tabIconSkin);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        m_scrollIconSkins = new QScrollArea(m_tabIconSkin);
        m_scrollIconSkins->setObjectName(QStringLiteral("m_scrollIconSkins"));
        m_scrollIconSkins->setFrameShape(QFrame::NoFrame);
        m_scrollIconSkins->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 570, 354));
        formLayout = new QFormLayout(scrollAreaWidgetContents_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout_9 = new QFormLayout(groupBox_2);
        formLayout_9->setObjectName(QStringLiteral("formLayout_9"));
        m_treeSkins = new QTreeWidget(groupBox_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        m_treeSkins->setHeaderItem(__qtreewidgetitem);
        m_treeSkins->setObjectName(QStringLiteral("m_treeSkins"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_treeSkins->sizePolicy().hasHeightForWidth());
        m_treeSkins->setSizePolicy(sizePolicy);
        m_treeSkins->setAlternatingRowColors(false);
        m_treeSkins->setIndentation(0);
        m_treeSkins->setRootIsDecorated(false);
        m_treeSkins->setItemsExpandable(false);
        m_treeSkins->setExpandsOnDoubleClick(false);

        formLayout_9->setWidget(0, QFormLayout::SpanningRole, m_treeSkins);

        m_lblActiveCaption = new QLabel(groupBox_2);
        m_lblActiveCaption->setObjectName(QStringLiteral("m_lblActiveCaption"));

        formLayout_9->setWidget(1, QFormLayout::LabelRole, m_lblActiveCaption);

        m_lblActiveContents = new QLabel(groupBox_2);
        m_lblActiveContents->setObjectName(QStringLiteral("m_lblActiveContents"));

        formLayout_9->setWidget(1, QFormLayout::FieldRole, m_lblActiveContents);

        m_lblSelectedCaption = new QLabel(groupBox_2);
        m_lblSelectedCaption->setObjectName(QStringLiteral("m_lblSelectedCaption"));

        formLayout_9->setWidget(2, QFormLayout::LabelRole, m_lblSelectedCaption);

        m_lblSelectedContents = new QLabel(groupBox_2);
        m_lblSelectedContents->setObjectName(QStringLiteral("m_lblSelectedContents"));

        formLayout_9->setWidget(2, QFormLayout::FieldRole, m_lblSelectedContents);


        formLayout->setWidget(1, QFormLayout::FieldRole, groupBox_2);

        groupBox = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout_8 = new QFormLayout(groupBox);
        formLayout_8->setObjectName(QStringLiteral("formLayout_8"));
        formLayout_8->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_lblIconTheme = new QLabel(groupBox);
        m_lblIconTheme->setObjectName(QStringLiteral("m_lblIconTheme"));

        formLayout_8->setWidget(0, QFormLayout::LabelRole, m_lblIconTheme);

        m_cmbIconTheme = new QComboBox(groupBox);
        m_cmbIconTheme->setObjectName(QStringLiteral("m_cmbIconTheme"));

        formLayout_8->setWidget(0, QFormLayout::FieldRole, m_cmbIconTheme);


        formLayout->setWidget(0, QFormLayout::SpanningRole, groupBox);

        m_scrollIconSkins->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_8->addWidget(m_scrollIconSkins);

        m_tabUi->addTab(m_tabIconSkin, QString());

        horizontalLayout->addWidget(m_tabUi);

        m_stackedSettings->addWidget(m_pageUi);
        m_pageShortcuts = new QWidget();
        m_pageShortcuts->setObjectName(QStringLiteral("m_pageShortcuts"));
        horizontalLayout_3 = new QHBoxLayout(m_pageShortcuts);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        m_scrollShortcuts = new QScrollArea(m_pageShortcuts);
        m_scrollShortcuts->setObjectName(QStringLiteral("m_scrollShortcuts"));
        m_scrollShortcuts->setFrameShape(QFrame::NoFrame);
        m_scrollShortcuts->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 576, 380));
        horizontalLayout_4 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        m_shortcutsEditor = new DynamicShortcutsWidget(scrollAreaWidgetContents);
        m_shortcutsEditor->setObjectName(QStringLiteral("m_shortcutsEditor"));

        horizontalLayout_4->addWidget(m_shortcutsEditor);

        m_scrollShortcuts->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(m_scrollShortcuts);

        m_stackedSettings->addWidget(m_pageShortcuts);
        m_pageLanguages = new QWidget();
        m_pageLanguages->setObjectName(QStringLiteral("m_pageLanguages"));
        horizontalLayout_2 = new QHBoxLayout(m_pageLanguages);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_treeLanguages = new QTreeWidget(m_pageLanguages);
        m_treeLanguages->setObjectName(QStringLiteral("m_treeLanguages"));
        m_treeLanguages->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_treeLanguages->setIndentation(0);
        m_treeLanguages->setItemsExpandable(false);
        m_treeLanguages->setAllColumnsShowFocus(true);
        m_treeLanguages->setExpandsOnDoubleClick(false);
        m_treeLanguages->setColumnCount(0);

        horizontalLayout_2->addWidget(m_treeLanguages);

        m_stackedSettings->addWidget(m_pageLanguages);
        m_pageProxy = new QWidget();
        m_pageProxy->setObjectName(QStringLiteral("m_pageProxy"));
        horizontalLayout_5 = new QHBoxLayout(m_pageProxy);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        m_tabBrowserProxy = new QTabWidget(m_pageProxy);
        m_tabBrowserProxy->setObjectName(QStringLiteral("m_tabBrowserProxy"));
        m_tabExternalBrowser = new QWidget();
        m_tabExternalBrowser->setObjectName(QStringLiteral("m_tabExternalBrowser"));
        formLayout_17 = new QFormLayout(m_tabExternalBrowser);
        formLayout_17->setObjectName(QStringLiteral("formLayout_17"));
        m_grpCustomExternalBrowser = new QGroupBox(m_tabExternalBrowser);
        m_grpCustomExternalBrowser->setObjectName(QStringLiteral("m_grpCustomExternalBrowser"));
        m_grpCustomExternalBrowser->setFlat(false);
        m_grpCustomExternalBrowser->setCheckable(true);
        formLayout_12 = new QFormLayout(m_grpCustomExternalBrowser);
        formLayout_12->setObjectName(QStringLiteral("formLayout_12"));
        m_lblExternalBrowserExecutable = new QLabel(m_grpCustomExternalBrowser);
        m_lblExternalBrowserExecutable->setObjectName(QStringLiteral("m_lblExternalBrowserExecutable"));

        formLayout_12->setWidget(0, QFormLayout::LabelRole, m_lblExternalBrowserExecutable);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        m_txtExternalBrowserExecutable = new QLineEdit(m_grpCustomExternalBrowser);
        m_txtExternalBrowserExecutable->setObjectName(QStringLiteral("m_txtExternalBrowserExecutable"));

        horizontalLayout_10->addWidget(m_txtExternalBrowserExecutable);

        m_btnExternalBrowserExecutable = new QToolButton(m_grpCustomExternalBrowser);
        m_btnExternalBrowserExecutable->setObjectName(QStringLiteral("m_btnExternalBrowserExecutable"));

        horizontalLayout_10->addWidget(m_btnExternalBrowserExecutable);


        formLayout_12->setLayout(0, QFormLayout::FieldRole, horizontalLayout_10);

        m_lblExternalBrowserArguments = new QLabel(m_grpCustomExternalBrowser);
        m_lblExternalBrowserArguments->setObjectName(QStringLiteral("m_lblExternalBrowserArguments"));

        formLayout_12->setWidget(1, QFormLayout::LabelRole, m_lblExternalBrowserArguments);

        m_txtExternalBrowserArguments = new QLineEdit(m_grpCustomExternalBrowser);
        m_txtExternalBrowserArguments->setObjectName(QStringLiteral("m_txtExternalBrowserArguments"));

        formLayout_12->setWidget(1, QFormLayout::FieldRole, m_txtExternalBrowserArguments);

        m_lblExternalBrowserPreset = new QLabel(m_grpCustomExternalBrowser);
        m_lblExternalBrowserPreset->setObjectName(QStringLiteral("m_lblExternalBrowserPreset"));

        formLayout_12->setWidget(2, QFormLayout::LabelRole, m_lblExternalBrowserPreset);

        m_cmbExternalBrowserPreset = new QComboBox(m_grpCustomExternalBrowser);
        m_cmbExternalBrowserPreset->setObjectName(QStringLiteral("m_cmbExternalBrowserPreset"));
        m_cmbExternalBrowserPreset->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        formLayout_12->setWidget(2, QFormLayout::FieldRole, m_cmbExternalBrowserPreset);

        label = new QLabel(m_grpCustomExternalBrowser);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label->setWordWrap(true);
        label->setMargin(10);

        formLayout_12->setWidget(3, QFormLayout::SpanningRole, label);


        formLayout_17->setWidget(0, QFormLayout::SpanningRole, m_grpCustomExternalBrowser);

        m_tabBrowserProxy->addTab(m_tabExternalBrowser, QString());
        m_tabProxy = new QWidget();
        m_tabProxy->setObjectName(QStringLiteral("m_tabProxy"));
        formLayout_6 = new QFormLayout(m_tabProxy);
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        m_lblProxyType = new QLabel(m_tabProxy);
        m_lblProxyType->setObjectName(QStringLiteral("m_lblProxyType"));
        m_lblProxyType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(0, QFormLayout::LabelRole, m_lblProxyType);

        m_cmbProxyType = new QComboBox(m_tabProxy);
        m_cmbProxyType->setObjectName(QStringLiteral("m_cmbProxyType"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, m_cmbProxyType);

        m_lblProxyHost = new QLabel(m_tabProxy);
        m_lblProxyHost->setObjectName(QStringLiteral("m_lblProxyHost"));
        m_lblProxyHost->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(1, QFormLayout::LabelRole, m_lblProxyHost);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        m_txtProxyHost = new QLineEdit(m_tabProxy);
        m_txtProxyHost->setObjectName(QStringLiteral("m_txtProxyHost"));
        m_txtProxyHost->setEnabled(true);

        horizontalLayout_7->addWidget(m_txtProxyHost);

        m_lblProxyPort = new QLabel(m_tabProxy);
        m_lblProxyPort->setObjectName(QStringLiteral("m_lblProxyPort"));
        m_lblProxyPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(m_lblProxyPort);

        m_spinProxyPort = new QSpinBox(m_tabProxy);
        m_spinProxyPort->setObjectName(QStringLiteral("m_spinProxyPort"));
        m_spinProxyPort->setEnabled(true);
        m_spinProxyPort->setMaximum(65535);
        m_spinProxyPort->setValue(80);

        horizontalLayout_7->addWidget(m_spinProxyPort);


        formLayout_6->setLayout(1, QFormLayout::FieldRole, horizontalLayout_7);

        m_lblProxyUsername = new QLabel(m_tabProxy);
        m_lblProxyUsername->setObjectName(QStringLiteral("m_lblProxyUsername"));
        m_lblProxyUsername->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(2, QFormLayout::LabelRole, m_lblProxyUsername);

        m_txtProxyUsername = new QLineEdit(m_tabProxy);
        m_txtProxyUsername->setObjectName(QStringLiteral("m_txtProxyUsername"));
        m_txtProxyUsername->setEnabled(true);

        formLayout_6->setWidget(2, QFormLayout::FieldRole, m_txtProxyUsername);

        m_lblProxyPassword = new QLabel(m_tabProxy);
        m_lblProxyPassword->setObjectName(QStringLiteral("m_lblProxyPassword"));
        m_lblProxyPassword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(3, QFormLayout::LabelRole, m_lblProxyPassword);

        m_txtProxyPassword = new QLineEdit(m_tabProxy);
        m_txtProxyPassword->setObjectName(QStringLiteral("m_txtProxyPassword"));
        m_txtProxyPassword->setEnabled(true);
        m_txtProxyPassword->setEchoMode(QLineEdit::Password);

        formLayout_6->setWidget(3, QFormLayout::FieldRole, m_txtProxyPassword);

        m_checkShowPassword = new QCheckBox(m_tabProxy);
        m_checkShowPassword->setObjectName(QStringLiteral("m_checkShowPassword"));
        m_checkShowPassword->setEnabled(true);

        formLayout_6->setWidget(4, QFormLayout::FieldRole, m_checkShowPassword);

        m_lblProxyInfo = new QLabel(m_tabProxy);
        m_lblProxyInfo->setObjectName(QStringLiteral("m_lblProxyInfo"));
        m_lblProxyInfo->setAlignment(Qt::AlignCenter);
        m_lblProxyInfo->setWordWrap(true);

        formLayout_6->setWidget(5, QFormLayout::SpanningRole, m_lblProxyInfo);

        m_tabBrowserProxy->addTab(m_tabProxy, QString());

        horizontalLayout_5->addWidget(m_tabBrowserProxy);

        m_stackedSettings->addWidget(m_pageProxy);
        m_pageExternalApplications = new QWidget();
        m_pageExternalApplications->setObjectName(QStringLiteral("m_pageExternalApplications"));
        formLayout_3 = new QFormLayout(m_pageExternalApplications);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(m_pageExternalApplications);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_btnSelectSignapk = new QPushButton(m_pageExternalApplications);
        m_btnSelectSignapk->setObjectName(QStringLiteral("m_btnSelectSignapk"));

        horizontalLayout_6->addWidget(m_btnSelectSignapk);

        m_lblExternalSignapk = new LabelWithStatus(m_pageExternalApplications);
        m_lblExternalSignapk->setObjectName(QStringLiteral("m_lblExternalSignapk"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_lblExternalSignapk->sizePolicy().hasHeightForWidth());
        m_lblExternalSignapk->setSizePolicy(sizePolicy1);
        m_lblExternalSignapk->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_6->addWidget(m_lblExternalSignapk);


        formLayout_3->setLayout(0, QFormLayout::FieldRole, horizontalLayout_6);

        label_8 = new QLabel(m_pageExternalApplications);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        m_btnSelectZip = new QPushButton(m_pageExternalApplications);
        m_btnSelectZip->setObjectName(QStringLiteral("m_btnSelectZip"));

        horizontalLayout_9->addWidget(m_btnSelectZip);

        m_lblExternalZip = new LabelWithStatus(m_pageExternalApplications);
        m_lblExternalZip->setObjectName(QStringLiteral("m_lblExternalZip"));
        sizePolicy1.setHeightForWidth(m_lblExternalZip->sizePolicy().hasHeightForWidth());
        m_lblExternalZip->setSizePolicy(sizePolicy1);
        m_lblExternalZip->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_9->addWidget(m_lblExternalZip);


        formLayout_3->setLayout(1, QFormLayout::FieldRole, horizontalLayout_9);

        label_9 = new QLabel(m_pageExternalApplications);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        m_btnSelectJava = new QPushButton(m_pageExternalApplications);
        m_btnSelectJava->setObjectName(QStringLiteral("m_btnSelectJava"));

        horizontalLayout_11->addWidget(m_btnSelectJava);

        m_lblExternalJava = new LabelWithStatus(m_pageExternalApplications);
        m_lblExternalJava->setObjectName(QStringLiteral("m_lblExternalJava"));
        sizePolicy1.setHeightForWidth(m_lblExternalJava->sizePolicy().hasHeightForWidth());
        m_lblExternalJava->setSizePolicy(sizePolicy1);
        m_lblExternalJava->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_11->addWidget(m_lblExternalJava);


        formLayout_3->setLayout(2, QFormLayout::FieldRole, horizontalLayout_11);

        m_stackedSettings->addWidget(m_pageExternalApplications);
        m_pageApkGeneration = new QWidget();
        m_pageApkGeneration->setObjectName(QStringLiteral("m_pageApkGeneration"));
        formLayout_4 = new QFormLayout(m_pageApkGeneration);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(m_pageApkGeneration);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        m_btnGenerationTempSelect = new QPushButton(m_pageApkGeneration);
        m_btnGenerationTempSelect->setObjectName(QStringLiteral("m_btnGenerationTempSelect"));

        horizontalLayout_12->addWidget(m_btnGenerationTempSelect);

        m_lblGenerationTemp = new QLabel(m_pageApkGeneration);
        m_lblGenerationTemp->setObjectName(QStringLiteral("m_lblGenerationTemp"));
        sizePolicy1.setHeightForWidth(m_lblGenerationTemp->sizePolicy().hasHeightForWidth());
        m_lblGenerationTemp->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(m_lblGenerationTemp);


        formLayout_4->setLayout(0, QFormLayout::FieldRole, horizontalLayout_12);

        label_5 = new QLabel(m_pageApkGeneration);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        m_btnGenerationOutputSelect = new QPushButton(m_pageApkGeneration);
        m_btnGenerationOutputSelect->setObjectName(QStringLiteral("m_btnGenerationOutputSelect"));

        horizontalLayout_13->addWidget(m_btnGenerationOutputSelect);

        m_lblGenerationOutput = new QLabel(m_pageApkGeneration);
        m_lblGenerationOutput->setObjectName(QStringLiteral("m_lblGenerationOutput"));
        sizePolicy1.setHeightForWidth(m_lblGenerationOutput->sizePolicy().hasHeightForWidth());
        m_lblGenerationOutput->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(m_lblGenerationOutput);


        formLayout_4->setLayout(1, QFormLayout::FieldRole, horizontalLayout_13);

        label_3 = new QLabel(m_pageApkGeneration);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_3);

        m_txtGenerationOutputFilePattern = new QLineEdit(m_pageApkGeneration);
        m_txtGenerationOutputFilePattern->setObjectName(QStringLiteral("m_txtGenerationOutputFilePattern"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, m_txtGenerationOutputFilePattern);

        m_lblGenerationInfo = new QLabel(m_pageApkGeneration);
        m_lblGenerationInfo->setObjectName(QStringLiteral("m_lblGenerationInfo"));
        m_lblGenerationInfo->setTextFormat(Qt::RichText);
        m_lblGenerationInfo->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        m_lblGenerationInfo->setWordWrap(true);
        m_lblGenerationInfo->setMargin(10);

        formLayout_4->setWidget(3, QFormLayout::SpanningRole, m_lblGenerationInfo);

        m_stackedSettings->addWidget(m_pageApkGeneration);

        gridLayout->addWidget(m_stackedSettings, 0, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        m_lblIconTheme->setBuddy(m_cmbIconTheme);
        m_lblProxyType->setBuddy(m_cmbProxyType);
        m_lblProxyHost->setBuddy(m_txtProxyHost);
        m_lblProxyPort->setBuddy(m_spinProxyPort);
        m_lblProxyUsername->setBuddy(m_txtProxyUsername);
        m_lblProxyPassword->setBuddy(m_txtProxyPassword);
#endif // QT_NO_SHORTCUT

        retranslateUi(FormSettings);
        QObject::connect(m_buttonBox, SIGNAL(rejected()), FormSettings, SLOT(reject()));
        QObject::connect(m_listSettings, SIGNAL(currentRowChanged(int)), m_stackedSettings, SLOT(setCurrentIndex(int)));

        m_listSettings->setCurrentRow(-1);
        m_stackedSettings->setCurrentIndex(0);
        m_tabUi->setCurrentIndex(0);
        m_tabBrowserProxy->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormSettings);
    } // setupUi

    void retranslateUi(QDialog *FormSettings)
    {
        FormSettings->setWindowTitle(QApplication::translate("FormSettings", "Settings", 0));

        const bool __sortingEnabled = m_listSettings->isSortingEnabled();
        m_listSettings->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = m_listSettings->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("FormSettings", "General", 0));
        QListWidgetItem *___qlistwidgetitem1 = m_listSettings->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("FormSettings", "User interface", 0));
        QListWidgetItem *___qlistwidgetitem2 = m_listSettings->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("FormSettings", "Keyboard shortcuts", 0));
        QListWidgetItem *___qlistwidgetitem3 = m_listSettings->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("FormSettings", "Language", 0));
        QListWidgetItem *___qlistwidgetitem4 = m_listSettings->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("FormSettings", "Web browser & proxy", 0));
        QListWidgetItem *___qlistwidgetitem5 = m_listSettings->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("FormSettings", "External applications", 0));
        QListWidgetItem *___qlistwidgetitem6 = m_listSettings->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("FormSettings", "Project .apk file generation", 0));
        m_listSettings->setSortingEnabled(__sortingEnabled);

        m_checkCheckForUpdatesOnStartup->setText(QApplication::translate("FormSettings", "Check for updates when application starts (update is triggered with time delay.)", 0));
        groupBox_2->setTitle(QApplication::translate("FormSettings", "Skins", 0));
        m_lblActiveCaption->setText(QApplication::translate("FormSettings", "Active skin:", 0));
        m_lblActiveContents->setText(QString());
        m_lblSelectedCaption->setText(QApplication::translate("FormSettings", "Selected skin:", 0));
        m_lblSelectedContents->setText(QString());
        groupBox->setTitle(QApplication::translate("FormSettings", "Icons", 0));
        m_lblIconTheme->setText(QApplication::translate("FormSettings", "Icon theme", 0));
        m_tabUi->setTabText(m_tabUi->indexOf(m_tabIconSkin), QApplication::translate("FormSettings", "Icons && skins", 0));
#ifndef QT_NO_TOOLTIP
        m_grpCustomExternalBrowser->setToolTip(QApplication::translate("FormSettings", "<html><head/><body><p>If unchecked, then default system-wide web browser is used.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        m_grpCustomExternalBrowser->setTitle(QApplication::translate("FormSettings", "Use custom external web browser", 0));
        m_lblExternalBrowserExecutable->setText(QApplication::translate("FormSettings", "Web browser executable", 0));
        m_txtExternalBrowserExecutable->setPlaceholderText(QApplication::translate("FormSettings", "Executable file of web browser", 0));
        m_btnExternalBrowserExecutable->setText(QApplication::translate("FormSettings", "...", 0));
        m_lblExternalBrowserArguments->setText(QApplication::translate("FormSettings", "Executable parameters", 0));
        m_txtExternalBrowserArguments->setPlaceholderText(QApplication::translate("FormSettings", "Parameters to executable", 0));
        m_lblExternalBrowserPreset->setText(QApplication::translate("FormSettings", "Use sample arguments for", 0));
        m_cmbExternalBrowserPreset->clear();
        m_cmbExternalBrowserPreset->insertItems(0, QStringList()
         << QApplication::translate("FormSettings", "Select browser", 0)
        );
        label->setText(QApplication::translate("FormSettings", "Note that \"%1\" (without quotation marks) is placeholder for URL of selected message. If you don't know what to put in \"Executable parameters\" field, then use simply \"%1\".\n"
"\n"
"External web browser set on this page is used application-wide. For example, it is used for opening new update files for the application. If no specific external web browser is set, then application tries to use system default web browser.", 0));
        m_tabBrowserProxy->setTabText(m_tabBrowserProxy->indexOf(m_tabExternalBrowser), QApplication::translate("FormSettings", "External web browser", 0));
        m_lblProxyType->setText(QApplication::translate("FormSettings", "Type", 0));
        m_lblProxyHost->setText(QApplication::translate("FormSettings", "Host", 0));
        m_txtProxyHost->setPlaceholderText(QApplication::translate("FormSettings", "Hostname or IP of your proxy server", 0));
        m_lblProxyPort->setText(QApplication::translate("FormSettings", "Port", 0));
        m_lblProxyUsername->setText(QApplication::translate("FormSettings", "Username", 0));
        m_txtProxyUsername->setPlaceholderText(QApplication::translate("FormSettings", "Your username for proxy server authentication", 0));
        m_lblProxyPassword->setText(QApplication::translate("FormSettings", "Password", 0));
        m_txtProxyPassword->setPlaceholderText(QApplication::translate("FormSettings", "Your password for proxy server authentication", 0));
        m_checkShowPassword->setText(QApplication::translate("FormSettings", "Display password", 0));
        m_lblProxyInfo->setText(QApplication::translate("FormSettings", "Note that these settings are applied only on newly established connections.", 0));
        m_tabBrowserProxy->setTabText(m_tabBrowserProxy->indexOf(m_tabProxy), QApplication::translate("FormSettings", "Proxy", 0));
        label_7->setText(QApplication::translate("FormSettings", "SIGNAPK application signer", 0));
        m_btnSelectSignapk->setText(QApplication::translate("FormSettings", "&Select file...", 0));
        label_8->setText(QApplication::translate("FormSettings", "ZIP extractor", 0));
        m_btnSelectZip->setText(QApplication::translate("FormSettings", "&Select file...", 0));
        label_9->setText(QApplication::translate("FormSettings", "JAVA interpreter", 0));
        m_btnSelectJava->setText(QApplication::translate("FormSettings", "&Select file...", 0));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("FormSettings", "This is directory which is used for temporary files which are created during the application file generation process.", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("FormSettings", "TEMP directory", 0));
        m_btnGenerationTempSelect->setText(QApplication::translate("FormSettings", "&Select directory...", 0));
        m_lblGenerationTemp->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("FormSettings", "This is the directory, which will contain final generated application.", 0));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("FormSettings", "Output directory", 0));
        m_btnGenerationOutputSelect->setText(QApplication::translate("FormSettings", "Select &directory...", 0));
        m_lblGenerationOutput->setText(QString());
        label_3->setText(QApplication::translate("FormSettings", "Application filename pattern", 0));
        m_lblGenerationInfo->setText(QApplication::translate("FormSettings", "<html>\n"
"<body>\n"
"You can use these placeholders:\n"
"<ul>\n"
"<li>\"%1\" - name of used template,</li>\n"
"<li>\"%2\" - name of the project,</li>\n"
"<li>\"%3\" - timestamp of current date and time.</li>\n"
"</ul>\n"
"For example, typical application filename pattern can look like this: \"application-%1-%2-%3.apk\". This pattern is escaped during the generation process. For example, if you use \"flashcard\" template, then filename of result will look like this: \"application-flashcard-myflashcardproject-20140523T082205.apk\".\n"
"<br><br>\n"
"Note that not all templates support \"name of the project part\", for example Basic mLearning template ignores %2 placeholder.\n"
"</body>\n"
"</html>", 0));
    } // retranslateUi

};

namespace Ui {
    class FormSettings: public Ui_FormSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSETTINGS_H
