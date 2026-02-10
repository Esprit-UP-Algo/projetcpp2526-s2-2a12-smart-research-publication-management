/********************************************************************************
** Form generated from reading UI file 'smartresearchpublicationmanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMARTRESEARCHPUBLICATIONMANAGEMENT_H
#define UI_SMARTRESEARCHPUBLICATIONMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmartResearchPublicationManagement
{
public:
    QWidget *AppRoot;
    QHBoxLayout *rootLayout;
    QFrame *Sidebar;
    QVBoxLayout *sidebarLayout;
    QLabel *AppLogo;
    QPushButton *BtnEmployee;
    QPushButton *BtnFinance;
    QPushButton *BtnPublication;
    QPushButton *BtnLabs;
    QPushButton *BtnInventory;
    QPushButton *BtnPlans;
    QSpacerItem *sideSpacer;
    QToolButton *BtnTheme;
    QPushButton *BtnLogout;
    QFrame *MainArea;
    QVBoxLayout *mainAreaLayout;
    QFrame *Topbar;
    QHBoxLayout *topbarLayout;
    QLabel *PageTitle;
    QSpacerItem *topSpacer;
    QFrame *UserChip;
    QHBoxLayout *userChipLayout;
    QLabel *UserRole;
    QLabel *UserName;
    QSpacerItem *userSpacer;
    QHBoxLayout *bodyLayout;
    QStackedWidget *Pages;
    QWidget *PageFinance;
    QVBoxLayout *financeLayout;
    QWidget *PageEmployee;
    QVBoxLayout *empLayout;
    QWidget *PagePublication;
    QVBoxLayout *pubLayout;
    QWidget *PageLabs;
    QVBoxLayout *pageLabsLayout;
    QStackedWidget *LabsStack;
    QWidget *LabsContent;
    QVBoxLayout *labsLayout;
    QFrame *LabsCardFilter;
    QGridLayout *labsFilterGrid;
    QLabel *LblLabsSearch;
    QLabel *LblLabsSpec;
    QLabel *LblLabsCap;
    QLineEdit *LabsSearch;
    QComboBox *LabsSpec;
    QComboBox *LabsCap;
    QPushButton *BtnLabsApply;
    QFrame *LabsCardTable;
    QVBoxLayout *labsTableLayout;
    QLabel *LabsTitle;
    QTableWidget *TableLabs;
    QHBoxLayout *labsActions;
    QPushButton *BtnLabAdd;
    QPushButton *BtnLabEdit;
    QPushButton *BtnLabDelete;
    QSpacerItem *labsSpacer;
    QPushButton *BtnLabExport;
    QWidget *LabsPopup;
    QVBoxLayout *labsPopupLayout;
    QFrame *LabsOverlay;
    QVBoxLayout *labsOverlayLayout;
    QSpacerItem *labsOverlayTop;
    QHBoxLayout *labsCenterRow;
    QSpacerItem *labsOverlayLeft;
    QFrame *PopupLabsCard;
    QVBoxLayout *popupLabsLayout;
    QHBoxLayout *popupLabsHeader;
    QLabel *PopupTitleLabs;
    QSpacerItem *popupLabsHeaderSpacer;
    QToolButton *BtnPopupCancelLabs;
    QFrame *PopupLabsForm;
    QGridLayout *labsFormGrid;
    QLineEdit *LabLocation;
    QLineEdit *LabResponsible;
    QComboBox *LabSpec;
    QLabel *LblLabCap;
    QLabel *LblLabLoc;
    QLabel *LblLabName;
    QLabel *LblLabNum;
    QLineEdit *LabName;
    QLineEdit *LabNumber;
    QLabel *LblLabResp;
    QLabel *LblLabSpec;
    QComboBox *LabCap;
    QHBoxLayout *popupLabsActions;
    QSpacerItem *popupLabsActionsLeft;
    QPushButton *BtnPopupSaveLabs;
    QPushButton *BtnPopupResetLabs;
    QSpacerItem *labsOverlayRight;
    QSpacerItem *labsOverlayBottom;
    QWidget *PageInventory;
    QVBoxLayout *invRootLayout;
    QWidget *PagePlans;
    QVBoxLayout *plansLayout;
    QFrame *RightPanel;
    QVBoxLayout *rightPanelLayout;
    QFrame *CardStats;
    QVBoxLayout *statsCardLayout;
    QLabel *StatsTitle;
    QFrame *ChartPlaceholder;
    QSpacerItem *rightSpacer;

    void setupUi(QMainWindow *SmartResearchPublicationManagement)
    {
        if (SmartResearchPublicationManagement->objectName().isEmpty())
            SmartResearchPublicationManagement->setObjectName("SmartResearchPublicationManagement");
        SmartResearchPublicationManagement->resize(1366, 768);
        AppRoot = new QWidget(SmartResearchPublicationManagement);
        AppRoot->setObjectName("AppRoot");
        rootLayout = new QHBoxLayout(AppRoot);
        rootLayout->setSpacing(0);
        rootLayout->setObjectName("rootLayout");
        rootLayout->setContentsMargins(0, 0, 0, 0);
        Sidebar = new QFrame(AppRoot);
        Sidebar->setObjectName("Sidebar");
        Sidebar->setMinimumSize(QSize(250, 0));
        Sidebar->setMaximumSize(QSize(260, 16777215));
        Sidebar->setFrameShape(QFrame::Shape::NoFrame);
        sidebarLayout = new QVBoxLayout(Sidebar);
        sidebarLayout->setSpacing(12);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(18, 18, 18, 18);
        AppLogo = new QLabel(Sidebar);
        AppLogo->setObjectName("AppLogo");

        sidebarLayout->addWidget(AppLogo);

        BtnEmployee = new QPushButton(Sidebar);
        BtnEmployee->setObjectName("BtnEmployee");

        sidebarLayout->addWidget(BtnEmployee);

        BtnFinance = new QPushButton(Sidebar);
        BtnFinance->setObjectName("BtnFinance");

        sidebarLayout->addWidget(BtnFinance);

        BtnPublication = new QPushButton(Sidebar);
        BtnPublication->setObjectName("BtnPublication");

        sidebarLayout->addWidget(BtnPublication);

        BtnLabs = new QPushButton(Sidebar);
        BtnLabs->setObjectName("BtnLabs");

        sidebarLayout->addWidget(BtnLabs);

        BtnInventory = new QPushButton(Sidebar);
        BtnInventory->setObjectName("BtnInventory");

        sidebarLayout->addWidget(BtnInventory);

        BtnPlans = new QPushButton(Sidebar);
        BtnPlans->setObjectName("BtnPlans");

        sidebarLayout->addWidget(BtnPlans);

        sideSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(sideSpacer);

        BtnTheme = new QToolButton(Sidebar);
        BtnTheme->setObjectName("BtnTheme");

        sidebarLayout->addWidget(BtnTheme);

        BtnLogout = new QPushButton(Sidebar);
        BtnLogout->setObjectName("BtnLogout");

        sidebarLayout->addWidget(BtnLogout);


        rootLayout->addWidget(Sidebar);

        MainArea = new QFrame(AppRoot);
        MainArea->setObjectName("MainArea");
        MainArea->setFrameShape(QFrame::Shape::NoFrame);
        mainAreaLayout = new QVBoxLayout(MainArea);
        mainAreaLayout->setSpacing(14);
        mainAreaLayout->setObjectName("mainAreaLayout");
        mainAreaLayout->setContentsMargins(18, 18, 18, 18);
        Topbar = new QFrame(MainArea);
        Topbar->setObjectName("Topbar");
        Topbar->setMinimumSize(QSize(0, 64));
        Topbar->setMaximumSize(QSize(16777215, 64));
        Topbar->setFrameShape(QFrame::Shape::NoFrame);
        topbarLayout = new QHBoxLayout(Topbar);
        topbarLayout->setObjectName("topbarLayout");
        topbarLayout->setContentsMargins(16, 10, 16, 10);
        PageTitle = new QLabel(Topbar);
        PageTitle->setObjectName("PageTitle");

        topbarLayout->addWidget(PageTitle);

        topSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topbarLayout->addItem(topSpacer);

        UserChip = new QFrame(Topbar);
        UserChip->setObjectName("UserChip");
        UserChip->setFrameShape(QFrame::Shape::NoFrame);
        userChipLayout = new QHBoxLayout(UserChip);
        userChipLayout->setObjectName("userChipLayout");
        userChipLayout->setContentsMargins(12, 8, 12, 8);
        UserRole = new QLabel(UserChip);
        UserRole->setObjectName("UserRole");

        userChipLayout->addWidget(UserRole);

        UserName = new QLabel(UserChip);
        UserName->setObjectName("UserName");

        userChipLayout->addWidget(UserName);

        userSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        userChipLayout->addItem(userSpacer);


        topbarLayout->addWidget(UserChip);


        mainAreaLayout->addWidget(Topbar);

        bodyLayout = new QHBoxLayout();
        bodyLayout->setSpacing(14);
        bodyLayout->setObjectName("bodyLayout");
        Pages = new QStackedWidget(MainArea);
        Pages->setObjectName("Pages");
        PageFinance = new QWidget();
        PageFinance->setObjectName("PageFinance");
        financeLayout = new QVBoxLayout(PageFinance);
        financeLayout->setSpacing(14);
        financeLayout->setObjectName("financeLayout");
        financeLayout->setContentsMargins(0, 0, 0, 0);
        Pages->addWidget(PageFinance);
        PageEmployee = new QWidget();
        PageEmployee->setObjectName("PageEmployee");
        empLayout = new QVBoxLayout(PageEmployee);
        empLayout->setObjectName("empLayout");
        Pages->addWidget(PageEmployee);
        PagePublication = new QWidget();
        PagePublication->setObjectName("PagePublication");
        pubLayout = new QVBoxLayout(PagePublication);
        pubLayout->setObjectName("pubLayout");
        Pages->addWidget(PagePublication);
        PageLabs = new QWidget();
        PageLabs->setObjectName("PageLabs");
        pageLabsLayout = new QVBoxLayout(PageLabs);
        pageLabsLayout->setObjectName("pageLabsLayout");
        pageLabsLayout->setContentsMargins(0, 0, 0, 0);
        LabsStack = new QStackedWidget(PageLabs);
        LabsStack->setObjectName("LabsStack");
        LabsContent = new QWidget();
        LabsContent->setObjectName("LabsContent");
        labsLayout = new QVBoxLayout(LabsContent);
        labsLayout->setSpacing(14);
        labsLayout->setObjectName("labsLayout");
        labsLayout->setContentsMargins(0, 0, 0, 0);
        LabsCardFilter = new QFrame(LabsContent);
        LabsCardFilter->setObjectName("LabsCardFilter");
        LabsCardFilter->setFrameShape(QFrame::Shape::NoFrame);
        labsFilterGrid = new QGridLayout(LabsCardFilter);
        labsFilterGrid->setObjectName("labsFilterGrid");
        labsFilterGrid->setHorizontalSpacing(12);
        labsFilterGrid->setVerticalSpacing(10);
        labsFilterGrid->setContentsMargins(16, 16, 16, 16);
        LblLabsSearch = new QLabel(LabsCardFilter);
        LblLabsSearch->setObjectName("LblLabsSearch");

        labsFilterGrid->addWidget(LblLabsSearch, 0, 0, 1, 1);

        LblLabsSpec = new QLabel(LabsCardFilter);
        LblLabsSpec->setObjectName("LblLabsSpec");

        labsFilterGrid->addWidget(LblLabsSpec, 0, 1, 1, 1);

        LblLabsCap = new QLabel(LabsCardFilter);
        LblLabsCap->setObjectName("LblLabsCap");

        labsFilterGrid->addWidget(LblLabsCap, 0, 2, 1, 1);

        LabsSearch = new QLineEdit(LabsCardFilter);
        LabsSearch->setObjectName("LabsSearch");

        labsFilterGrid->addWidget(LabsSearch, 1, 0, 1, 1);

        LabsSpec = new QComboBox(LabsCardFilter);
        LabsSpec->setObjectName("LabsSpec");

        labsFilterGrid->addWidget(LabsSpec, 1, 1, 1, 1);

        LabsCap = new QComboBox(LabsCardFilter);
        LabsCap->setObjectName("LabsCap");

        labsFilterGrid->addWidget(LabsCap, 1, 2, 1, 1);

        BtnLabsApply = new QPushButton(LabsCardFilter);
        BtnLabsApply->setObjectName("BtnLabsApply");

        labsFilterGrid->addWidget(BtnLabsApply, 1, 3, 1, 1);


        labsLayout->addWidget(LabsCardFilter);

        LabsCardTable = new QFrame(LabsContent);
        LabsCardTable->setObjectName("LabsCardTable");
        LabsCardTable->setFrameShape(QFrame::Shape::NoFrame);
        labsTableLayout = new QVBoxLayout(LabsCardTable);
        labsTableLayout->setSpacing(10);
        labsTableLayout->setObjectName("labsTableLayout");
        labsTableLayout->setContentsMargins(16, 16, 16, 16);
        LabsTitle = new QLabel(LabsCardTable);
        LabsTitle->setObjectName("LabsTitle");

        labsTableLayout->addWidget(LabsTitle);

        TableLabs = new QTableWidget(LabsCardTable);
        if (TableLabs->columnCount() < 7)
            TableLabs->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TableLabs->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        TableLabs->setObjectName("TableLabs");
        TableLabs->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableLabs->setAlternatingRowColors(true);
        TableLabs->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableLabs->setShowGrid(false);
        TableLabs->setSortingEnabled(true);
        TableLabs->setCornerButtonEnabled(false);

        labsTableLayout->addWidget(TableLabs);

        labsActions = new QHBoxLayout();
        labsActions->setSpacing(10);
        labsActions->setObjectName("labsActions");
        BtnLabAdd = new QPushButton(LabsCardTable);
        BtnLabAdd->setObjectName("BtnLabAdd");

        labsActions->addWidget(BtnLabAdd);

        BtnLabEdit = new QPushButton(LabsCardTable);
        BtnLabEdit->setObjectName("BtnLabEdit");

        labsActions->addWidget(BtnLabEdit);

        BtnLabDelete = new QPushButton(LabsCardTable);
        BtnLabDelete->setObjectName("BtnLabDelete");

        labsActions->addWidget(BtnLabDelete);

        labsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsActions->addItem(labsSpacer);

        BtnLabExport = new QPushButton(LabsCardTable);
        BtnLabExport->setObjectName("BtnLabExport");

        labsActions->addWidget(BtnLabExport);


        labsTableLayout->addLayout(labsActions);


        labsLayout->addWidget(LabsCardTable);

        LabsStack->addWidget(LabsContent);
        LabsPopup = new QWidget();
        LabsPopup->setObjectName("LabsPopup");
        labsPopupLayout = new QVBoxLayout(LabsPopup);
        labsPopupLayout->setObjectName("labsPopupLayout");
        labsPopupLayout->setContentsMargins(0, 0, 0, 0);
        LabsOverlay = new QFrame(LabsPopup);
        LabsOverlay->setObjectName("LabsOverlay");
        LabsOverlay->setFrameShape(QFrame::Shape::NoFrame);
        labsOverlayLayout = new QVBoxLayout(LabsOverlay);
        labsOverlayLayout->setObjectName("labsOverlayLayout");
        labsOverlayLayout->setContentsMargins(0, 0, 0, 0);
        labsOverlayTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        labsOverlayLayout->addItem(labsOverlayTop);

        labsCenterRow = new QHBoxLayout();
        labsCenterRow->setObjectName("labsCenterRow");
        labsOverlayLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsCenterRow->addItem(labsOverlayLeft);

        PopupLabsCard = new QFrame(LabsOverlay);
        PopupLabsCard->setObjectName("PopupLabsCard");
        PopupLabsCard->setMinimumSize(QSize(760, 0));
        PopupLabsCard->setFrameShape(QFrame::Shape::NoFrame);
        popupLabsLayout = new QVBoxLayout(PopupLabsCard);
        popupLabsLayout->setSpacing(12);
        popupLabsLayout->setObjectName("popupLabsLayout");
        popupLabsLayout->setContentsMargins(18, 18, 18, 18);
        popupLabsHeader = new QHBoxLayout();
        popupLabsHeader->setObjectName("popupLabsHeader");
        PopupTitleLabs = new QLabel(PopupLabsCard);
        PopupTitleLabs->setObjectName("PopupTitleLabs");

        popupLabsHeader->addWidget(PopupTitleLabs);

        popupLabsHeaderSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupLabsHeader->addItem(popupLabsHeaderSpacer);

        BtnPopupCancelLabs = new QToolButton(PopupLabsCard);
        BtnPopupCancelLabs->setObjectName("BtnPopupCancelLabs");

        popupLabsHeader->addWidget(BtnPopupCancelLabs);


        popupLabsLayout->addLayout(popupLabsHeader);

        PopupLabsForm = new QFrame(PopupLabsCard);
        PopupLabsForm->setObjectName("PopupLabsForm");
        PopupLabsForm->setFrameShape(QFrame::Shape::NoFrame);
        labsFormGrid = new QGridLayout(PopupLabsForm);
        labsFormGrid->setObjectName("labsFormGrid");
        labsFormGrid->setHorizontalSpacing(12);
        labsFormGrid->setVerticalSpacing(10);
        LabLocation = new QLineEdit(PopupLabsForm);
        LabLocation->setObjectName("LabLocation");

        labsFormGrid->addWidget(LabLocation, 1, 1, 1, 1);

        LabResponsible = new QLineEdit(PopupLabsForm);
        LabResponsible->setObjectName("LabResponsible");

        labsFormGrid->addWidget(LabResponsible, 0, 3, 1, 1);

        LabSpec = new QComboBox(PopupLabsForm);
        LabSpec->setObjectName("LabSpec");

        labsFormGrid->addWidget(LabSpec, 2, 1, 1, 1);

        LblLabCap = new QLabel(PopupLabsForm);
        LblLabCap->setObjectName("LblLabCap");

        labsFormGrid->addWidget(LblLabCap, 2, 2, 1, 1);

        LblLabLoc = new QLabel(PopupLabsForm);
        LblLabLoc->setObjectName("LblLabLoc");

        labsFormGrid->addWidget(LblLabLoc, 1, 0, 1, 1);

        LblLabName = new QLabel(PopupLabsForm);
        LblLabName->setObjectName("LblLabName");

        labsFormGrid->addWidget(LblLabName, 0, 0, 1, 1);

        LblLabNum = new QLabel(PopupLabsForm);
        LblLabNum->setObjectName("LblLabNum");

        labsFormGrid->addWidget(LblLabNum, 1, 2, 1, 1);

        LabName = new QLineEdit(PopupLabsForm);
        LabName->setObjectName("LabName");

        labsFormGrid->addWidget(LabName, 0, 1, 1, 1);

        LabNumber = new QLineEdit(PopupLabsForm);
        LabNumber->setObjectName("LabNumber");

        labsFormGrid->addWidget(LabNumber, 1, 3, 1, 1);

        LblLabResp = new QLabel(PopupLabsForm);
        LblLabResp->setObjectName("LblLabResp");

        labsFormGrid->addWidget(LblLabResp, 0, 2, 1, 1);

        LblLabSpec = new QLabel(PopupLabsForm);
        LblLabSpec->setObjectName("LblLabSpec");

        labsFormGrid->addWidget(LblLabSpec, 2, 0, 1, 1);

        LabCap = new QComboBox(PopupLabsForm);
        LabCap->setObjectName("LabCap");

        labsFormGrid->addWidget(LabCap, 2, 3, 1, 1);


        popupLabsLayout->addWidget(PopupLabsForm);

        popupLabsActions = new QHBoxLayout();
        popupLabsActions->setObjectName("popupLabsActions");
        popupLabsActionsLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupLabsActions->addItem(popupLabsActionsLeft);

        BtnPopupSaveLabs = new QPushButton(PopupLabsCard);
        BtnPopupSaveLabs->setObjectName("BtnPopupSaveLabs");

        popupLabsActions->addWidget(BtnPopupSaveLabs);

        BtnPopupResetLabs = new QPushButton(PopupLabsCard);
        BtnPopupResetLabs->setObjectName("BtnPopupResetLabs");

        popupLabsActions->addWidget(BtnPopupResetLabs);


        popupLabsLayout->addLayout(popupLabsActions);


        labsCenterRow->addWidget(PopupLabsCard);

        labsOverlayRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsCenterRow->addItem(labsOverlayRight);


        labsOverlayLayout->addLayout(labsCenterRow);

        labsOverlayBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        labsOverlayLayout->addItem(labsOverlayBottom);


        labsPopupLayout->addWidget(LabsOverlay);

        LabsStack->addWidget(LabsPopup);

        pageLabsLayout->addWidget(LabsStack);

        Pages->addWidget(PageLabs);
        PageInventory = new QWidget();
        PageInventory->setObjectName("PageInventory");
        invRootLayout = new QVBoxLayout(PageInventory);
        invRootLayout->setSpacing(14);
        invRootLayout->setObjectName("invRootLayout");
        invRootLayout->setContentsMargins(0, 0, 0, 0);
        Pages->addWidget(PageInventory);
        PagePlans = new QWidget();
        PagePlans->setObjectName("PagePlans");
        plansLayout = new QVBoxLayout(PagePlans);
        plansLayout->setObjectName("plansLayout");
        Pages->addWidget(PagePlans);

        bodyLayout->addWidget(Pages);

        RightPanel = new QFrame(MainArea);
        RightPanel->setObjectName("RightPanel");
        RightPanel->setMinimumSize(QSize(280, 0));
        RightPanel->setMaximumSize(QSize(320, 16777215));
        RightPanel->setFrameShape(QFrame::Shape::NoFrame);
        rightPanelLayout = new QVBoxLayout(RightPanel);
        rightPanelLayout->setSpacing(14);
        rightPanelLayout->setObjectName("rightPanelLayout");
        rightPanelLayout->setContentsMargins(0, 0, 0, 0);
        CardStats = new QFrame(RightPanel);
        CardStats->setObjectName("CardStats");
        CardStats->setFrameShape(QFrame::Shape::NoFrame);
        statsCardLayout = new QVBoxLayout(CardStats);
        statsCardLayout->setSpacing(10);
        statsCardLayout->setObjectName("statsCardLayout");
        statsCardLayout->setContentsMargins(16, 16, 16, 16);
        StatsTitle = new QLabel(CardStats);
        StatsTitle->setObjectName("StatsTitle");

        statsCardLayout->addWidget(StatsTitle);

        ChartPlaceholder = new QFrame(CardStats);
        ChartPlaceholder->setObjectName("ChartPlaceholder");
        ChartPlaceholder->setMinimumSize(QSize(0, 260));
        ChartPlaceholder->setFrameShape(QFrame::Shape::NoFrame);

        statsCardLayout->addWidget(ChartPlaceholder);


        rightPanelLayout->addWidget(CardStats);

        rightSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightPanelLayout->addItem(rightSpacer);


        bodyLayout->addWidget(RightPanel);


        mainAreaLayout->addLayout(bodyLayout);


        rootLayout->addWidget(MainArea);

        SmartResearchPublicationManagement->setCentralWidget(AppRoot);

        retranslateUi(SmartResearchPublicationManagement);

        LabsStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SmartResearchPublicationManagement);
    } // setupUi

    void retranslateUi(QMainWindow *SmartResearchPublicationManagement)
    {
        SmartResearchPublicationManagement->setWindowTitle(QCoreApplication::translate("SmartResearchPublicationManagement", "Smart Research Lab", nullptr));
        AppLogo->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "VORTEX", nullptr));
        BtnEmployee->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "EMPLOYEE", nullptr));
        BtnFinance->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "FINANCE", nullptr));
        BtnPublication->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "PUBLICATION", nullptr));
        BtnLabs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "LABS", nullptr));
        BtnInventory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "INVENTORY", nullptr));
        BtnPlans->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "PLANS", nullptr));
#if QT_CONFIG(tooltip)
        BtnTheme->setToolTip(QCoreApplication::translate("SmartResearchPublicationManagement", "Changer le th\303\250me (Jour/Nuit)", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnTheme->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "MODE", nullptr));
        BtnLogout->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "LOG OUT", nullptr));
        PageTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Smart Research", nullptr));
        UserRole->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Admin", nullptr));
        UserName->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Azer", nullptr));
        LblLabsSearch->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Recherche", nullptr));
        LblLabsSpec->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Sp\303\251cialit\303\251", nullptr));
        LblLabsCap->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Capacit\303\251", nullptr));
        LabsSearch->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "nom, responsable, localisation, num\303\251ro\342\200\246", nullptr));
        BtnLabsApply->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Appliquer", nullptr));
        BtnLabsApply->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "primary", nullptr)));
        LabsTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Laboratoires", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableLabs->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableLabs->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableLabs->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Responsable", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableLabs->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Localisation", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TableLabs->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Num\303\251ro", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TableLabs->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Sp\303\251cialit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = TableLabs->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Capacit\303\251", nullptr));
        BtnLabAdd->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Ajouter", nullptr));
        BtnLabAdd->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "primary", nullptr)));
        BtnLabEdit->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Modifier", nullptr));
        BtnLabEdit->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "ghost", nullptr)));
        BtnLabDelete->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Supprimer", nullptr));
        BtnLabDelete->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "danger", nullptr)));
        BtnLabExport->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Exporter PDF", nullptr));
        BtnLabExport->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "chip", nullptr)));
        PopupTitleLabs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Ajouter un laboratoire", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs->setToolTip(QCoreApplication::translate("SmartResearchPublicationManagement", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "\342\234\225", nullptr));
        LabLocation->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "Bloc B, Salle 204", nullptr));
        LabResponsible->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "Nom responsable", nullptr));
        LblLabCap->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Capacit\303\251", nullptr));
        LblLabLoc->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Localisation", nullptr));
        LblLabName->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Nom labo", nullptr));
        LblLabNum->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Num\303\251ro", nullptr));
        LabName->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "Laboratoire IA", nullptr));
        LabNumber->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "204", nullptr));
        LblLabResp->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Responsable", nullptr));
        LblLabSpec->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Sp\303\251cialit\303\251", nullptr));
        BtnPopupSaveLabs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Enregistrer", nullptr));
        BtnPopupSaveLabs->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "primary", nullptr)));
        BtnPopupResetLabs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Vider", nullptr));
        BtnPopupResetLabs->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "ghost", nullptr)));
        StatsTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "D\303\251penses vs Revenus / mois", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmartResearchPublicationManagement: public Ui_SmartResearchPublicationManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMARTRESEARCHPUBLICATIONMANAGEMENT_H
