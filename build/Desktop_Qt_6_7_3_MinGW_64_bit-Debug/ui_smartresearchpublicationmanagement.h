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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QPushButton *BtnLogout;
    QToolButton *BtnTheme;
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
    QWidget *PageInventory;
    QVBoxLayout *invRootLayout;
    QStackedWidget *InventoryStack;
    QWidget *InventoryContent;
    QVBoxLayout *inventoryLayout;
    QFrame *InventoryCardFilter;
    QGridLayout *inventoryFilterGrid;
    QLabel *LblInventorySearch;
    QLabel *LblInventoryType;
    QLabel *LblInventoryStatus;
    QLabel *LblInventoryZone;
    QLineEdit *InventorySearch;
    QComboBox *InventoryType;
    QComboBox *InventoryStatus;
    QComboBox *InventoryZone;
    QPushButton *BtnInventoryApply;
    QFrame *InventoryCardTable;
    QVBoxLayout *inventoryTableLayout;
    QLabel *InventoryTitle;
    QTableWidget *TableInventory;
    QHBoxLayout *inventoryActions;
    QPushButton *BtnInventoryAdd;
    QPushButton *BtnInventoryEdit;
    QPushButton *BtnInventoryDelete;
    QSpacerItem *inventorySpacer;
    QPushButton *BtnInventoryExport;
    QWidget *InventoryPopup;
    QVBoxLayout *inventoryPopupLayout;
    QFrame *InventoryOverlay;
    QVBoxLayout *inventoryOverlayLayout;
    QSpacerItem *inventoryOverlayTop;
    QHBoxLayout *inventoryCenterRow;
    QSpacerItem *inventoryOverlayLeft;
    QFrame *PopupInventoryCard;
    QVBoxLayout *popupInventoryLayout;
    QHBoxLayout *popupInventoryHeader;
    QLabel *PopupTitleInventory;
    QSpacerItem *popupInventoryHeaderSpacer;
    QToolButton *BtnPopupCancelInventory;
    QFrame *PopupInventoryForm;
    QGridLayout *inventoryFormGrid;
    QLabel *LblIdProduct;
    QLineEdit *IdProduct;
    QLabel *LblName;
    QLineEdit *Name;
    QLabel *LblSku;
    QLineEdit *Sku;
    QLabel *LblType;
    QComboBox *Type;
    QLabel *LblQtAv;
    QSpinBox *QtAv;
    QLabel *LblQtRs;
    QSpinBox *QtRs;
    QLabel *LblThreshold;
    QSpinBox *Threshold;
    QLabel *LblUnit;
    QComboBox *Unit;
    QLabel *LblPrice;
    QDoubleSpinBox *Price;
    QLabel *LblStatus;
    QComboBox *Status;
    QLabel *LblZone;
    QComboBox *Zone;
    QLabel *LblShelf;
    QComboBox *Shelf;
    QHBoxLayout *popupInventoryActions;
    QSpacerItem *popupInventoryActionsLeft;
    QPushButton *BtnPopupSaveInventory;
    QPushButton *BtnPopupResetInventory;
    QSpacerItem *inventoryOverlayRight;
    QSpacerItem *inventoryOverlayBottom;
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

        BtnLogout = new QPushButton(Sidebar);
        BtnLogout->setObjectName("BtnLogout");

        sidebarLayout->addWidget(BtnLogout);

        BtnTheme = new QToolButton(Sidebar);
        BtnTheme->setObjectName("BtnTheme");

        sidebarLayout->addWidget(BtnTheme);


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
        Pages->addWidget(PageLabs);
        PageInventory = new QWidget();
        PageInventory->setObjectName("PageInventory");
        invRootLayout = new QVBoxLayout(PageInventory);
        invRootLayout->setSpacing(14);
        invRootLayout->setObjectName("invRootLayout");
        invRootLayout->setContentsMargins(0, 0, 0, 0);
        InventoryStack = new QStackedWidget(PageInventory);
        InventoryStack->setObjectName("InventoryStack");
        InventoryContent = new QWidget();
        InventoryContent->setObjectName("InventoryContent");
        inventoryLayout = new QVBoxLayout(InventoryContent);
        inventoryLayout->setSpacing(14);
        inventoryLayout->setObjectName("inventoryLayout");
        inventoryLayout->setContentsMargins(0, 0, 0, 0);
        InventoryCardFilter = new QFrame(InventoryContent);
        InventoryCardFilter->setObjectName("InventoryCardFilter");
        InventoryCardFilter->setFrameShape(QFrame::Shape::NoFrame);
        inventoryFilterGrid = new QGridLayout(InventoryCardFilter);
        inventoryFilterGrid->setObjectName("inventoryFilterGrid");
        inventoryFilterGrid->setHorizontalSpacing(12);
        inventoryFilterGrid->setVerticalSpacing(10);
        inventoryFilterGrid->setContentsMargins(16, 16, 16, 16);
        LblInventorySearch = new QLabel(InventoryCardFilter);
        LblInventorySearch->setObjectName("LblInventorySearch");

        inventoryFilterGrid->addWidget(LblInventorySearch, 0, 0, 1, 1);

        LblInventoryType = new QLabel(InventoryCardFilter);
        LblInventoryType->setObjectName("LblInventoryType");

        inventoryFilterGrid->addWidget(LblInventoryType, 0, 1, 1, 1);

        LblInventoryStatus = new QLabel(InventoryCardFilter);
        LblInventoryStatus->setObjectName("LblInventoryStatus");

        inventoryFilterGrid->addWidget(LblInventoryStatus, 0, 2, 1, 1);

        LblInventoryZone = new QLabel(InventoryCardFilter);
        LblInventoryZone->setObjectName("LblInventoryZone");

        inventoryFilterGrid->addWidget(LblInventoryZone, 0, 3, 1, 1);

        InventorySearch = new QLineEdit(InventoryCardFilter);
        InventorySearch->setObjectName("InventorySearch");

        inventoryFilterGrid->addWidget(InventorySearch, 1, 0, 1, 1);

        InventoryType = new QComboBox(InventoryCardFilter);
        InventoryType->setObjectName("InventoryType");

        inventoryFilterGrid->addWidget(InventoryType, 1, 1, 1, 1);

        InventoryStatus = new QComboBox(InventoryCardFilter);
        InventoryStatus->setObjectName("InventoryStatus");

        inventoryFilterGrid->addWidget(InventoryStatus, 1, 2, 1, 1);

        InventoryZone = new QComboBox(InventoryCardFilter);
        InventoryZone->setObjectName("InventoryZone");

        inventoryFilterGrid->addWidget(InventoryZone, 1, 3, 1, 1);

        BtnInventoryApply = new QPushButton(InventoryCardFilter);
        BtnInventoryApply->setObjectName("BtnInventoryApply");

        inventoryFilterGrid->addWidget(BtnInventoryApply, 1, 4, 1, 1);


        inventoryLayout->addWidget(InventoryCardFilter);

        InventoryCardTable = new QFrame(InventoryContent);
        InventoryCardTable->setObjectName("InventoryCardTable");
        InventoryCardTable->setFrameShape(QFrame::Shape::NoFrame);
        inventoryTableLayout = new QVBoxLayout(InventoryCardTable);
        inventoryTableLayout->setSpacing(10);
        inventoryTableLayout->setObjectName("inventoryTableLayout");
        inventoryTableLayout->setContentsMargins(16, 16, 16, 16);
        InventoryTitle = new QLabel(InventoryCardTable);
        InventoryTitle->setObjectName("InventoryTitle");

        inventoryTableLayout->addWidget(InventoryTitle);

        TableInventory = new QTableWidget(InventoryCardTable);
        if (TableInventory->columnCount() < 12)
            TableInventory->setColumnCount(12);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        TableInventory->setObjectName("TableInventory");
        TableInventory->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableInventory->setAlternatingRowColors(true);
        TableInventory->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableInventory->setShowGrid(false);
        TableInventory->setSortingEnabled(true);
        TableInventory->setCornerButtonEnabled(false);

        inventoryTableLayout->addWidget(TableInventory);

        inventoryActions = new QHBoxLayout();
        inventoryActions->setSpacing(10);
        inventoryActions->setObjectName("inventoryActions");
        BtnInventoryAdd = new QPushButton(InventoryCardTable);
        BtnInventoryAdd->setObjectName("BtnInventoryAdd");

        inventoryActions->addWidget(BtnInventoryAdd);

        BtnInventoryEdit = new QPushButton(InventoryCardTable);
        BtnInventoryEdit->setObjectName("BtnInventoryEdit");

        inventoryActions->addWidget(BtnInventoryEdit);

        BtnInventoryDelete = new QPushButton(InventoryCardTable);
        BtnInventoryDelete->setObjectName("BtnInventoryDelete");

        inventoryActions->addWidget(BtnInventoryDelete);

        inventorySpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inventoryActions->addItem(inventorySpacer);

        BtnInventoryExport = new QPushButton(InventoryCardTable);
        BtnInventoryExport->setObjectName("BtnInventoryExport");

        inventoryActions->addWidget(BtnInventoryExport);


        inventoryTableLayout->addLayout(inventoryActions);


        inventoryLayout->addWidget(InventoryCardTable);

        InventoryStack->addWidget(InventoryContent);
        InventoryPopup = new QWidget();
        InventoryPopup->setObjectName("InventoryPopup");
        inventoryPopupLayout = new QVBoxLayout(InventoryPopup);
        inventoryPopupLayout->setObjectName("inventoryPopupLayout");
        inventoryPopupLayout->setContentsMargins(0, 0, 0, 0);
        InventoryOverlay = new QFrame(InventoryPopup);
        InventoryOverlay->setObjectName("InventoryOverlay");
        InventoryOverlay->setFrameShape(QFrame::Shape::NoFrame);
        inventoryOverlayLayout = new QVBoxLayout(InventoryOverlay);
        inventoryOverlayLayout->setObjectName("inventoryOverlayLayout");
        inventoryOverlayLayout->setContentsMargins(0, 0, 0, 0);
        inventoryOverlayTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        inventoryOverlayLayout->addItem(inventoryOverlayTop);

        inventoryCenterRow = new QHBoxLayout();
        inventoryCenterRow->setObjectName("inventoryCenterRow");
        inventoryOverlayLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inventoryCenterRow->addItem(inventoryOverlayLeft);

        PopupInventoryCard = new QFrame(InventoryOverlay);
        PopupInventoryCard->setObjectName("PopupInventoryCard");
        PopupInventoryCard->setMinimumSize(QSize(760, 0));
        PopupInventoryCard->setFrameShape(QFrame::Shape::NoFrame);
        popupInventoryLayout = new QVBoxLayout(PopupInventoryCard);
        popupInventoryLayout->setSpacing(12);
        popupInventoryLayout->setObjectName("popupInventoryLayout");
        popupInventoryLayout->setContentsMargins(18, 18, 18, 18);
        popupInventoryHeader = new QHBoxLayout();
        popupInventoryHeader->setObjectName("popupInventoryHeader");
        PopupTitleInventory = new QLabel(PopupInventoryCard);
        PopupTitleInventory->setObjectName("PopupTitleInventory");

        popupInventoryHeader->addWidget(PopupTitleInventory);

        popupInventoryHeaderSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupInventoryHeader->addItem(popupInventoryHeaderSpacer);

        BtnPopupCancelInventory = new QToolButton(PopupInventoryCard);
        BtnPopupCancelInventory->setObjectName("BtnPopupCancelInventory");

        popupInventoryHeader->addWidget(BtnPopupCancelInventory);


        popupInventoryLayout->addLayout(popupInventoryHeader);

        PopupInventoryForm = new QFrame(PopupInventoryCard);
        PopupInventoryForm->setObjectName("PopupInventoryForm");
        PopupInventoryForm->setFrameShape(QFrame::Shape::NoFrame);
        inventoryFormGrid = new QGridLayout(PopupInventoryForm);
        inventoryFormGrid->setObjectName("inventoryFormGrid");
        inventoryFormGrid->setHorizontalSpacing(12);
        inventoryFormGrid->setVerticalSpacing(10);
        LblIdProduct = new QLabel(PopupInventoryForm);
        LblIdProduct->setObjectName("LblIdProduct");

        inventoryFormGrid->addWidget(LblIdProduct, 0, 0, 1, 1);

        IdProduct = new QLineEdit(PopupInventoryForm);
        IdProduct->setObjectName("IdProduct");

        inventoryFormGrid->addWidget(IdProduct, 0, 1, 1, 1);

        LblName = new QLabel(PopupInventoryForm);
        LblName->setObjectName("LblName");

        inventoryFormGrid->addWidget(LblName, 0, 2, 1, 1);

        Name = new QLineEdit(PopupInventoryForm);
        Name->setObjectName("Name");

        inventoryFormGrid->addWidget(Name, 0, 3, 1, 1);

        LblSku = new QLabel(PopupInventoryForm);
        LblSku->setObjectName("LblSku");

        inventoryFormGrid->addWidget(LblSku, 1, 0, 1, 1);

        Sku = new QLineEdit(PopupInventoryForm);
        Sku->setObjectName("Sku");

        inventoryFormGrid->addWidget(Sku, 1, 1, 1, 1);

        LblType = new QLabel(PopupInventoryForm);
        LblType->setObjectName("LblType");

        inventoryFormGrid->addWidget(LblType, 1, 2, 1, 1);

        Type = new QComboBox(PopupInventoryForm);
        Type->setObjectName("Type");

        inventoryFormGrid->addWidget(Type, 1, 3, 1, 1);

        LblQtAv = new QLabel(PopupInventoryForm);
        LblQtAv->setObjectName("LblQtAv");

        inventoryFormGrid->addWidget(LblQtAv, 2, 0, 1, 1);

        QtAv = new QSpinBox(PopupInventoryForm);
        QtAv->setObjectName("QtAv");
        QtAv->setMinimum(0);
        QtAv->setMaximum(10000);

        inventoryFormGrid->addWidget(QtAv, 2, 1, 1, 1);

        LblQtRs = new QLabel(PopupInventoryForm);
        LblQtRs->setObjectName("LblQtRs");

        inventoryFormGrid->addWidget(LblQtRs, 2, 2, 1, 1);

        QtRs = new QSpinBox(PopupInventoryForm);
        QtRs->setObjectName("QtRs");
        QtRs->setMinimum(0);
        QtRs->setMaximum(10000);

        inventoryFormGrid->addWidget(QtRs, 2, 3, 1, 1);

        LblThreshold = new QLabel(PopupInventoryForm);
        LblThreshold->setObjectName("LblThreshold");

        inventoryFormGrid->addWidget(LblThreshold, 3, 0, 1, 1);

        Threshold = new QSpinBox(PopupInventoryForm);
        Threshold->setObjectName("Threshold");
        Threshold->setMinimum(0);
        Threshold->setMaximum(10000);

        inventoryFormGrid->addWidget(Threshold, 3, 1, 1, 1);

        LblUnit = new QLabel(PopupInventoryForm);
        LblUnit->setObjectName("LblUnit");

        inventoryFormGrid->addWidget(LblUnit, 3, 2, 1, 1);

        Unit = new QComboBox(PopupInventoryForm);
        Unit->setObjectName("Unit");

        inventoryFormGrid->addWidget(Unit, 3, 3, 1, 1);

        LblPrice = new QLabel(PopupInventoryForm);
        LblPrice->setObjectName("LblPrice");

        inventoryFormGrid->addWidget(LblPrice, 4, 0, 1, 1);

        Price = new QDoubleSpinBox(PopupInventoryForm);
        Price->setObjectName("Price");
        Price->setDecimals(2);
        Price->setMinimum(0.000000000000000);
        Price->setMaximum(100000.000000000000000);

        inventoryFormGrid->addWidget(Price, 4, 1, 1, 1);

        LblStatus = new QLabel(PopupInventoryForm);
        LblStatus->setObjectName("LblStatus");

        inventoryFormGrid->addWidget(LblStatus, 4, 2, 1, 1);

        Status = new QComboBox(PopupInventoryForm);
        Status->setObjectName("Status");

        inventoryFormGrid->addWidget(Status, 4, 3, 1, 1);

        LblZone = new QLabel(PopupInventoryForm);
        LblZone->setObjectName("LblZone");

        inventoryFormGrid->addWidget(LblZone, 5, 0, 1, 1);

        Zone = new QComboBox(PopupInventoryForm);
        Zone->setObjectName("Zone");

        inventoryFormGrid->addWidget(Zone, 5, 1, 1, 1);

        LblShelf = new QLabel(PopupInventoryForm);
        LblShelf->setObjectName("LblShelf");

        inventoryFormGrid->addWidget(LblShelf, 5, 2, 1, 1);

        Shelf = new QComboBox(PopupInventoryForm);
        Shelf->setObjectName("Shelf");

        inventoryFormGrid->addWidget(Shelf, 5, 3, 1, 1);


        popupInventoryLayout->addWidget(PopupInventoryForm);

        popupInventoryActions = new QHBoxLayout();
        popupInventoryActions->setObjectName("popupInventoryActions");
        popupInventoryActionsLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupInventoryActions->addItem(popupInventoryActionsLeft);

        BtnPopupSaveInventory = new QPushButton(PopupInventoryCard);
        BtnPopupSaveInventory->setObjectName("BtnPopupSaveInventory");

        popupInventoryActions->addWidget(BtnPopupSaveInventory);

        BtnPopupResetInventory = new QPushButton(PopupInventoryCard);
        BtnPopupResetInventory->setObjectName("BtnPopupResetInventory");

        popupInventoryActions->addWidget(BtnPopupResetInventory);


        popupInventoryLayout->addLayout(popupInventoryActions);


        inventoryCenterRow->addWidget(PopupInventoryCard);

        inventoryOverlayRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inventoryCenterRow->addItem(inventoryOverlayRight);


        inventoryOverlayLayout->addLayout(inventoryCenterRow);

        inventoryOverlayBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        inventoryOverlayLayout->addItem(inventoryOverlayBottom);


        inventoryPopupLayout->addWidget(InventoryOverlay);

        InventoryStack->addWidget(InventoryPopup);

        invRootLayout->addWidget(InventoryStack);

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

        InventoryStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SmartResearchPublicationManagement);
    } // setupUi

    void retranslateUi(QMainWindow *SmartResearchPublicationManagement)
    {
        SmartResearchPublicationManagement->setWindowTitle(QCoreApplication::translate("SmartResearchPublicationManagement", "Smart Research Lab", nullptr));
        AppLogo->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "VORTEX", nullptr));
        BtnEmployee->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "EMPLOYEE", nullptr));
        BtnFinance->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "FINANCE", nullptr));
        BtnPublication->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "PUBLICATION", nullptr));
        BtnLabs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "LABS \360\237\247\252", nullptr));
        BtnInventory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "INVENTORY", nullptr));
        BtnPlans->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "PLANS", nullptr));
        BtnLogout->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "LOG OUT", nullptr));
#if QT_CONFIG(tooltip)
        BtnTheme->setToolTip(QCoreApplication::translate("SmartResearchPublicationManagement", "Changer le th\303\250me (Jour/Nuit)", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnTheme->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "MODE \360\237\214\236 / \360\237\214\232", nullptr));
        PageTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Smart Research", nullptr));
        UserRole->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Admin", nullptr));
        UserName->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Azer", nullptr));
        LblInventorySearch->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Recherche", nullptr));
        LblInventoryType->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Type", nullptr));
        LblInventoryStatus->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Statut", nullptr));
        LblInventoryZone->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Zone", nullptr));
        InventorySearch->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "ID, nom, SKU\342\200\246", nullptr));
        BtnInventoryApply->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Appliquer", nullptr));
        BtnInventoryApply->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "primary", nullptr)));
        InventoryTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Inventaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableInventory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableInventory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableInventory->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "SKU", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableInventory->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TableInventory->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Qt Av.", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TableInventory->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Qt Rs.", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = TableInventory->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Seuil", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = TableInventory->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Unit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = TableInventory->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = TableInventory->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = TableInventory->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "\303\211tag\303\250re", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = TableInventory->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Statut", nullptr));
        BtnInventoryAdd->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Ajouter\342\236\225", nullptr));
        BtnInventoryAdd->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "primary", nullptr)));
        BtnInventoryEdit->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Modifier  \360\237\226\216", nullptr));
        BtnInventoryEdit->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "ghost", nullptr)));
        BtnInventoryDelete->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Supprimer\342\235\214", nullptr));
        BtnInventoryDelete->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "danger", nullptr)));
        BtnInventoryExport->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Exporter PDF \342\254\207\357\270\217", nullptr));
        BtnInventoryExport->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "chip", nullptr)));
        PopupTitleInventory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Ajouter un produit", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelInventory->setToolTip(QCoreApplication::translate("SmartResearchPublicationManagement", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelInventory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "\342\234\225", nullptr));
        LblIdProduct->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "ID Produit", nullptr));
        IdProduct->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "PROD-001", nullptr));
        LblName->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Nom", nullptr));
        Name->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "Nom du produit", nullptr));
        LblSku->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "SKU", nullptr));
        Sku->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "SKU-001", nullptr));
        LblType->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Type", nullptr));
        Type->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "S\303\251lectionner type", nullptr));
        LblQtAv->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Qt Disponible", nullptr));
        LblQtRs->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Qt R\303\251serv\303\251e", nullptr));
        LblThreshold->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Seuil min", nullptr));
        LblUnit->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Unit\303\251", nullptr));
        Unit->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "S\303\251lectionner unit\303\251", nullptr));
        LblPrice->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Prix (\342\202\254)", nullptr));
        Price->setPrefix(QCoreApplication::translate("SmartResearchPublicationManagement", "\342\202\254 ", nullptr));
        LblStatus->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Statut", nullptr));
        Status->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "S\303\251lectionner statut", nullptr));
        LblZone->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Zone", nullptr));
        Zone->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "S\303\251lectionner zone", nullptr));
        LblShelf->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "\303\211tag\303\250re", nullptr));
        Shelf->setPlaceholderText(QCoreApplication::translate("SmartResearchPublicationManagement", "S\303\251lectionner \303\251tag\303\250re", nullptr));
        BtnPopupSaveInventory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Enregistrer", nullptr));
        BtnPopupSaveInventory->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "primary", nullptr)));
        BtnPopupResetInventory->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "Vider", nullptr));
        BtnPopupResetInventory->setProperty("property", QVariant(QCoreApplication::translate("SmartResearchPublicationManagement", "ghost", nullptr)));
        StatsTitle->setText(QCoreApplication::translate("SmartResearchPublicationManagement", "D\303\251penses vs Revenus / mois", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmartResearchPublicationManagement: public Ui_SmartResearchPublicationManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMARTRESEARCHPUBLICATIONMANAGEMENT_H
