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
#include <QtWidgets/QDateEdit>
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
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *sideSpacer;
    QToolButton *BtnTheme;
    QPushButton *BtnLogout;
    QLabel *SideFooter;
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
    QLabel *AppLogo_2;
    QHBoxLayout *bodyLayout;
    QStackedWidget *Pages;
    QWidget *PageFinance;
    QVBoxLayout *financeLayout;
    QStackedWidget *FinanceStack;
    QWidget *FinanceContent;
    QVBoxLayout *financeContentLayout;
    QFrame *CardFilter;
    QGridLayout *filterGrid;
    QLabel *LblType;
    QLabel *LblCategory;
    QLabel *LblFrom;
    QLabel *LblTo;
    QComboBox *CbType;
    QComboBox *CbCategory;
    QDateEdit *DateFrom;
    QDateEdit *DateTo;
    QLineEdit *EdSearch;
    QPushButton *BtnApply;
    QPushButton *BtnReset;
    QFrame *CardTable;
    QVBoxLayout *tableCardLayout;
    QLabel *TableTitle;
    QTableWidget *TableFinance;
    QHBoxLayout *tableActions;
    QPushButton *BtnAdd;
    QPushButton *BtnEdit;
    QPushButton *BtnDelete;
    QSpacerItem *tableActionsSpacer;
    QPushButton *BtnExport;
    QWidget *FinancePopupPage;
    QVBoxLayout *financePopupLayout;
    QFrame *OverlayFinance;
    QVBoxLayout *overlayFinanceLayout;
    QSpacerItem *ovTop;
    QFrame *PopupFinanceCard;
    QVBoxLayout *popupFinanceCardLayout;
    QLabel *PopupTitleFinance;
    QGridLayout *popupFinanceGrid;
    QLabel *LblCode;
    QLineEdit *FormCode;
    QLabel *LblFType;
    QComboBox *FormType;
    QLabel *LblAmount;
    QLineEdit *FormAmount;
    QLabel *LblCat2;
    QComboBox *FormCategory;
    QLabel *LblDesc;
    QLineEdit *FormDesc;
    QLabel *LblDate2;
    QDateEdit *FormDate;
    QLabel *LblPay;
    QComboBox *FormPayMode;
    QLabel *LblCreated;
    QDateEdit *FormCreatedAt;
    QHBoxLayout *popupFinanceButtons;
    QSpacerItem *pfSpacer;
    QPushButton *BtnPopupSaveFinance;
    QPushButton *BtnPopupCancelFinance;
    QSpacerItem *ovBottom;
    QWidget *PageEmployee;
    QVBoxLayout *empLayout;
    QLabel *EmpPlaceholder;
    QWidget *PagePublication;
    QVBoxLayout *pubLayout;
    QLabel *PubPlaceholder;
    QWidget *PageLabs;
    QVBoxLayout *pageLabsLayout;
    QWidget *PageInventory;
    QVBoxLayout *invRootLayout;
    QWidget *PagePlans;
    QVBoxLayout *plansLayout;
    QLabel *PlansPlaceholder;
    QFrame *RightPanel;
    QVBoxLayout *rightPanelLayout;
    QFrame *CardStats;
    QVBoxLayout *statsCardLayout;
    QLabel *StatsTitle;

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
        AppLogo->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

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

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        sidebarLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");

        sidebarLayout->addLayout(verticalLayout_2);

        sideSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(sideSpacer);

        BtnTheme = new QToolButton(Sidebar);
        BtnTheme->setObjectName("BtnTheme");

        sidebarLayout->addWidget(BtnTheme);

        BtnLogout = new QPushButton(Sidebar);
        BtnLogout->setObjectName("BtnLogout");

        sidebarLayout->addWidget(BtnLogout);

        SideFooter = new QLabel(Sidebar);
        SideFooter->setObjectName("SideFooter");

        sidebarLayout->addWidget(SideFooter);


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

        AppLogo_2 = new QLabel(UserChip);
        AppLogo_2->setObjectName("AppLogo_2");
        AppLogo_2->setMinimumSize(QSize(0, 48));
        AppLogo_2->setMaximumSize(QSize(100, 48));
        AppLogo_2->setPixmap(QPixmap(QString::fromUtf8(":/styles/Picture1.png")));
        AppLogo_2->setScaledContents(true);
        AppLogo_2->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        userChipLayout->addWidget(AppLogo_2);


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
        FinanceStack = new QStackedWidget(PageFinance);
        FinanceStack->setObjectName("FinanceStack");
        FinanceContent = new QWidget();
        FinanceContent->setObjectName("FinanceContent");
        financeContentLayout = new QVBoxLayout(FinanceContent);
        financeContentLayout->setSpacing(14);
        financeContentLayout->setObjectName("financeContentLayout");
        financeContentLayout->setContentsMargins(0, 0, 0, 0);
        CardFilter = new QFrame(FinanceContent);
        CardFilter->setObjectName("CardFilter");
        CardFilter->setFrameShape(QFrame::Shape::NoFrame);
        filterGrid = new QGridLayout(CardFilter);
        filterGrid->setObjectName("filterGrid");
        filterGrid->setHorizontalSpacing(12);
        filterGrid->setVerticalSpacing(10);
        filterGrid->setContentsMargins(16, 16, 16, 16);
        LblType = new QLabel(CardFilter);
        LblType->setObjectName("LblType");

        filterGrid->addWidget(LblType, 0, 0, 1, 1);

        LblCategory = new QLabel(CardFilter);
        LblCategory->setObjectName("LblCategory");

        filterGrid->addWidget(LblCategory, 0, 1, 1, 1);

        LblFrom = new QLabel(CardFilter);
        LblFrom->setObjectName("LblFrom");

        filterGrid->addWidget(LblFrom, 0, 2, 1, 1);

        LblTo = new QLabel(CardFilter);
        LblTo->setObjectName("LblTo");

        filterGrid->addWidget(LblTo, 0, 3, 1, 1);

        CbType = new QComboBox(CardFilter);
        CbType->setObjectName("CbType");

        filterGrid->addWidget(CbType, 1, 0, 1, 1);

        CbCategory = new QComboBox(CardFilter);
        CbCategory->setObjectName("CbCategory");

        filterGrid->addWidget(CbCategory, 1, 1, 1, 1);

        DateFrom = new QDateEdit(CardFilter);
        DateFrom->setObjectName("DateFrom");
        DateFrom->setCalendarPopup(true);

        filterGrid->addWidget(DateFrom, 1, 2, 1, 1);

        DateTo = new QDateEdit(CardFilter);
        DateTo->setObjectName("DateTo");
        DateTo->setCalendarPopup(true);

        filterGrid->addWidget(DateTo, 1, 3, 1, 1);

        EdSearch = new QLineEdit(CardFilter);
        EdSearch->setObjectName("EdSearch");

        filterGrid->addWidget(EdSearch, 2, 0, 1, 2);

        BtnApply = new QPushButton(CardFilter);
        BtnApply->setObjectName("BtnApply");

        filterGrid->addWidget(BtnApply, 2, 2, 1, 1);

        BtnReset = new QPushButton(CardFilter);
        BtnReset->setObjectName("BtnReset");

        filterGrid->addWidget(BtnReset, 2, 3, 1, 1);


        financeContentLayout->addWidget(CardFilter);

        CardTable = new QFrame(FinanceContent);
        CardTable->setObjectName("CardTable");
        CardTable->setFrameShape(QFrame::Shape::NoFrame);
        tableCardLayout = new QVBoxLayout(CardTable);
        tableCardLayout->setSpacing(10);
        tableCardLayout->setObjectName("tableCardLayout");
        tableCardLayout->setContentsMargins(16, 16, 16, 16);
        TableTitle = new QLabel(CardTable);
        TableTitle->setObjectName("TableTitle");

        tableCardLayout->addWidget(TableTitle);

        TableFinance = new QTableWidget(CardTable);
        if (TableFinance->columnCount() < 9)
            TableFinance->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        if (TableFinance->rowCount() < 3)
            TableFinance->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        TableFinance->setItem(0, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        TableFinance->setItem(0, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        TableFinance->setItem(0, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        TableFinance->setItem(0, 3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        TableFinance->setItem(0, 4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        TableFinance->setItem(0, 5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        TableFinance->setItem(0, 6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        TableFinance->setItem(0, 7, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        TableFinance->setItem(0, 8, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        TableFinance->setItem(1, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        TableFinance->setItem(1, 1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        TableFinance->setItem(1, 2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        TableFinance->setItem(1, 3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        TableFinance->setItem(1, 4, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        TableFinance->setItem(1, 5, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        TableFinance->setItem(1, 6, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        TableFinance->setItem(1, 7, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        TableFinance->setItem(1, 8, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        TableFinance->setItem(2, 0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        TableFinance->setItem(2, 1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        TableFinance->setItem(2, 2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        TableFinance->setItem(2, 3, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        TableFinance->setItem(2, 4, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        TableFinance->setItem(2, 5, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        TableFinance->setItem(2, 6, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        TableFinance->setItem(2, 7, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        TableFinance->setItem(2, 8, __qtablewidgetitem38);
        TableFinance->setObjectName("TableFinance");
        TableFinance->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableFinance->setAlternatingRowColors(true);
        TableFinance->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableFinance->setShowGrid(false);
        TableFinance->setSortingEnabled(true);
        TableFinance->setCornerButtonEnabled(false);
        TableFinance->setRowCount(3);
        TableFinance->setColumnCount(9);

        tableCardLayout->addWidget(TableFinance);

        tableActions = new QHBoxLayout();
        tableActions->setSpacing(10);
        tableActions->setObjectName("tableActions");
        BtnAdd = new QPushButton(CardTable);
        BtnAdd->setObjectName("BtnAdd");

        tableActions->addWidget(BtnAdd);

        BtnEdit = new QPushButton(CardTable);
        BtnEdit->setObjectName("BtnEdit");

        tableActions->addWidget(BtnEdit);

        BtnDelete = new QPushButton(CardTable);
        BtnDelete->setObjectName("BtnDelete");

        tableActions->addWidget(BtnDelete);

        tableActionsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        tableActions->addItem(tableActionsSpacer);

        BtnExport = new QPushButton(CardTable);
        BtnExport->setObjectName("BtnExport");

        tableActions->addWidget(BtnExport);


        tableCardLayout->addLayout(tableActions);


        financeContentLayout->addWidget(CardTable);

        FinanceStack->addWidget(FinanceContent);
        FinancePopupPage = new QWidget();
        FinancePopupPage->setObjectName("FinancePopupPage");
        financePopupLayout = new QVBoxLayout(FinancePopupPage);
        financePopupLayout->setObjectName("financePopupLayout");
        financePopupLayout->setContentsMargins(0, 0, 0, 0);
        OverlayFinance = new QFrame(FinancePopupPage);
        OverlayFinance->setObjectName("OverlayFinance");
        OverlayFinance->setFrameShape(QFrame::Shape::NoFrame);
        overlayFinanceLayout = new QVBoxLayout(OverlayFinance);
        overlayFinanceLayout->setObjectName("overlayFinanceLayout");
        overlayFinanceLayout->setContentsMargins(0, 0, 0, 0);
        ovTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayFinanceLayout->addItem(ovTop);

        PopupFinanceCard = new QFrame(OverlayFinance);
        PopupFinanceCard->setObjectName("PopupFinanceCard");
        PopupFinanceCard->setMinimumSize(QSize(760, 260));
        PopupFinanceCard->setMaximumSize(QSize(900, 400));
        PopupFinanceCard->setFrameShape(QFrame::Shape::NoFrame);
        popupFinanceCardLayout = new QVBoxLayout(PopupFinanceCard);
        popupFinanceCardLayout->setSpacing(12);
        popupFinanceCardLayout->setObjectName("popupFinanceCardLayout");
        popupFinanceCardLayout->setContentsMargins(16, 16, 16, 16);
        PopupTitleFinance = new QLabel(PopupFinanceCard);
        PopupTitleFinance->setObjectName("PopupTitleFinance");

        popupFinanceCardLayout->addWidget(PopupTitleFinance);

        popupFinanceGrid = new QGridLayout();
        popupFinanceGrid->setObjectName("popupFinanceGrid");
        popupFinanceGrid->setHorizontalSpacing(12);
        popupFinanceGrid->setVerticalSpacing(10);
        LblCode = new QLabel(PopupFinanceCard);
        LblCode->setObjectName("LblCode");

        popupFinanceGrid->addWidget(LblCode, 0, 0, 1, 1);

        FormCode = new QLineEdit(PopupFinanceCard);
        FormCode->setObjectName("FormCode");

        popupFinanceGrid->addWidget(FormCode, 0, 1, 1, 1);

        LblFType = new QLabel(PopupFinanceCard);
        LblFType->setObjectName("LblFType");

        popupFinanceGrid->addWidget(LblFType, 0, 2, 1, 1);

        FormType = new QComboBox(PopupFinanceCard);
        FormType->setObjectName("FormType");

        popupFinanceGrid->addWidget(FormType, 0, 3, 1, 1);

        LblAmount = new QLabel(PopupFinanceCard);
        LblAmount->setObjectName("LblAmount");

        popupFinanceGrid->addWidget(LblAmount, 1, 0, 1, 1);

        FormAmount = new QLineEdit(PopupFinanceCard);
        FormAmount->setObjectName("FormAmount");

        popupFinanceGrid->addWidget(FormAmount, 1, 1, 1, 1);

        LblCat2 = new QLabel(PopupFinanceCard);
        LblCat2->setObjectName("LblCat2");

        popupFinanceGrid->addWidget(LblCat2, 1, 2, 1, 1);

        FormCategory = new QComboBox(PopupFinanceCard);
        FormCategory->setObjectName("FormCategory");

        popupFinanceGrid->addWidget(FormCategory, 1, 3, 1, 1);

        LblDesc = new QLabel(PopupFinanceCard);
        LblDesc->setObjectName("LblDesc");

        popupFinanceGrid->addWidget(LblDesc, 2, 0, 1, 1);

        FormDesc = new QLineEdit(PopupFinanceCard);
        FormDesc->setObjectName("FormDesc");

        popupFinanceGrid->addWidget(FormDesc, 2, 1, 1, 3);

        LblDate2 = new QLabel(PopupFinanceCard);
        LblDate2->setObjectName("LblDate2");

        popupFinanceGrid->addWidget(LblDate2, 3, 0, 1, 1);

        FormDate = new QDateEdit(PopupFinanceCard);
        FormDate->setObjectName("FormDate");
        FormDate->setCalendarPopup(true);

        popupFinanceGrid->addWidget(FormDate, 3, 1, 1, 1);

        LblPay = new QLabel(PopupFinanceCard);
        LblPay->setObjectName("LblPay");

        popupFinanceGrid->addWidget(LblPay, 3, 2, 1, 1);

        FormPayMode = new QComboBox(PopupFinanceCard);
        FormPayMode->setObjectName("FormPayMode");

        popupFinanceGrid->addWidget(FormPayMode, 3, 3, 1, 1);

        LblCreated = new QLabel(PopupFinanceCard);
        LblCreated->setObjectName("LblCreated");

        popupFinanceGrid->addWidget(LblCreated, 4, 0, 1, 1);

        FormCreatedAt = new QDateEdit(PopupFinanceCard);
        FormCreatedAt->setObjectName("FormCreatedAt");
        FormCreatedAt->setEnabled(false);
        FormCreatedAt->setCalendarPopup(true);

        popupFinanceGrid->addWidget(FormCreatedAt, 4, 1, 1, 1);

        popupFinanceButtons = new QHBoxLayout();
        popupFinanceButtons->setObjectName("popupFinanceButtons");
        pfSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupFinanceButtons->addItem(pfSpacer);

        BtnPopupSaveFinance = new QPushButton(PopupFinanceCard);
        BtnPopupSaveFinance->setObjectName("BtnPopupSaveFinance");

        popupFinanceButtons->addWidget(BtnPopupSaveFinance);

        BtnPopupCancelFinance = new QPushButton(PopupFinanceCard);
        BtnPopupCancelFinance->setObjectName("BtnPopupCancelFinance");

        popupFinanceButtons->addWidget(BtnPopupCancelFinance);


        popupFinanceGrid->addLayout(popupFinanceButtons, 4, 2, 1, 2);


        popupFinanceCardLayout->addLayout(popupFinanceGrid);


        overlayFinanceLayout->addWidget(PopupFinanceCard);

        ovBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayFinanceLayout->addItem(ovBottom);


        financePopupLayout->addWidget(OverlayFinance);

        FinanceStack->addWidget(FinancePopupPage);

        financeLayout->addWidget(FinanceStack);

        Pages->addWidget(PageFinance);
        PageEmployee = new QWidget();
        PageEmployee->setObjectName("PageEmployee");
        empLayout = new QVBoxLayout(PageEmployee);
        empLayout->setObjectName("empLayout");
        EmpPlaceholder = new QLabel(PageEmployee);
        EmpPlaceholder->setObjectName("EmpPlaceholder");

        empLayout->addWidget(EmpPlaceholder);

        Pages->addWidget(PageEmployee);
        PagePublication = new QWidget();
        PagePublication->setObjectName("PagePublication");
        pubLayout = new QVBoxLayout(PagePublication);
        pubLayout->setObjectName("pubLayout");
        PubPlaceholder = new QLabel(PagePublication);
        PubPlaceholder->setObjectName("PubPlaceholder");

        pubLayout->addWidget(PubPlaceholder);

        Pages->addWidget(PagePublication);
        PageLabs = new QWidget();
        PageLabs->setObjectName("PageLabs");
        pageLabsLayout = new QVBoxLayout(PageLabs);
        pageLabsLayout->setObjectName("pageLabsLayout");
        pageLabsLayout->setContentsMargins(0, 0, 0, 0);
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
        PlansPlaceholder = new QLabel(PagePlans);
        PlansPlaceholder->setObjectName("PlansPlaceholder");

        plansLayout->addWidget(PlansPlaceholder);

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


        rightPanelLayout->addWidget(CardStats);


        bodyLayout->addWidget(RightPanel);


        mainAreaLayout->addLayout(bodyLayout);


        rootLayout->addWidget(MainArea);

        SmartResearchPublicationManagement->setCentralWidget(AppRoot);

        retranslateUi(SmartResearchPublicationManagement);

        Pages->setCurrentIndex(0);
        FinanceStack->setCurrentIndex(0);


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
        SideFooter->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Projet C++ - 2A12 (2025-2026)", nullptr));
        PageTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Smart Research", nullptr));
        UserRole->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Admin", nullptr));
        UserName->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Hichem", nullptr));
        AppLogo_2->setText(QString());
        LblType->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Type", nullptr));
        LblCategory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Cat\303\251gorie", nullptr));
        LblFrom->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "P\303\251riode (du)", nullptr));
        LblTo->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "au", nullptr));
        EdSearch->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "Rechercher (code, cat\303\251gorie, description...)", nullptr));
        BtnApply->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Appliquer", nullptr));
        BtnReset->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "R\303\251initialiser", nullptr));
        TableTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Transactions", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableFinance->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableFinance->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableFinance->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableFinance->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Montant", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TableFinance->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TableFinance->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = TableFinance->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Date transaction", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = TableFinance->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Mode paiement", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = TableFinance->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Date cr\303\251ation", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = TableFinance->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "TEST1", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = TableFinance->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "TEST2", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = TableFinance->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "TEST3", nullptr));

        const bool __sortingEnabled = TableFinance->isSortingEnabled();
        TableFinance->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem12 = TableFinance->item(0, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "20J", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = TableFinance->item(0, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "2OUH98H", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = TableFinance->item(0, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "29HUH", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = TableFinance->item(0, 3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "98UUOHJ", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = TableFinance->item(0, 4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "98H2O", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = TableFinance->item(0, 5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "HU", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = TableFinance->item(0, 6);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "98H2OUH", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = TableFinance->item(0, 7);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "298H82", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = TableFinance->item(0, 8);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "UOH2", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = TableFinance->item(1, 0);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "98H2O", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = TableFinance->item(1, 1);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "H2UOH2", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = TableFinance->item(1, 2);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "89", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = TableFinance->item(1, 3);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "H", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = TableFinance->item(1, 4);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "2UOHJ", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = TableFinance->item(1, 5);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "289892H082", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = TableFinance->item(1, 6);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "HI2I", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = TableFinance->item(1, 7);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "MJK2BUIOH", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = TableFinance->item(1, 8);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "2UOH", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = TableFinance->item(2, 0);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "2UO", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = TableFinance->item(2, 1);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "2UO", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = TableFinance->item(2, 2);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "2UH2", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = TableFinance->item(2, 3);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "092", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = TableFinance->item(2, 4);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "929H2", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = TableFinance->item(2, 5);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "08HJ2", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = TableFinance->item(2, 6);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "08H2", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = TableFinance->item(2, 7);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "08H", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = TableFinance->item(2, 8);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "208H", nullptr));
        TableFinance->setSortingEnabled(__sortingEnabled);

        BtnAdd->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Ajouter", nullptr));
        BtnEdit->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Modifier", nullptr));
        BtnDelete->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Supprimer", nullptr));
        BtnExport->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Exporter", nullptr));
        PopupTitleFinance->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Ajouter une transaction", nullptr));
        LblCode->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Code transaction", nullptr));
        FormCode->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "ex: TRX-2026-001", nullptr));
        LblFType->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Type", nullptr));
        LblAmount->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Montant", nullptr));
        FormAmount->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "ex: 2500", nullptr));
        LblCat2->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Cat\303\251gorie", nullptr));
        LblDesc->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Description", nullptr));
        FormDesc->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "D\303\251tails\342\200\246", nullptr));
        LblDate2->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Date transaction", nullptr));
        LblPay->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Mode paiement", nullptr));
        LblCreated->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Date cr\303\251ation", nullptr));
        BtnPopupSaveFinance->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Enregistrer", nullptr));
        BtnPopupCancelFinance->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Annuler", nullptr));
        EmpPlaceholder->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Module Employee (placeholder)", nullptr));
        PubPlaceholder->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Module Publication (placeholder)", nullptr));
        PlansPlaceholder->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Module Plans (placeholder)", nullptr));
        StatsTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Stats", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmartResearchPublicationManagement: public Ui_SmartResearchPublicationManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMARTRESEARCHPUBLICATIONMANAGEMENT_H
