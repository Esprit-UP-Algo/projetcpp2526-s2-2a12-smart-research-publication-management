/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayoutMain;
    QFrame *sidebarFrame;
    QVBoxLayout *verticalLayoutSidebar;
    QLabel *logoLabel;
    QPushButton *btnEmployee;
    QPushButton *btnInventaire;
    QPushButton *btnPublication;
    QPushButton *btnFinance;
    QPushButton *btnLaboratoires;
    QPushButton *btnProjets;
    QSpacerItem *verticalSpacer;
    QPushButton *btnDeconnecter;
    QVBoxLayout *verticalLayoutRight;
    QFrame *topBar;
    QLabel *lblBrand;
    QLabel *lblPageTitle;
    QStackedWidget *stackedWidget;
    QWidget *pageEmployee;
    QVBoxLayout *verticalLayoutPage0;
    QStackedWidget *stack_emp;
    QWidget *page_Emp;
    QGridLayout *gridLayout_4;
    QLineEdit *lineSearchEmp;
    QPushButton *btnChercher_emp;
    QPushButton *btnExporter_emp_excel;
    QPushButton *btnTrier_emp;
    QTableWidget *TableEmp;
    QPushButton *btnConge_emp_3;
    QPushButton *btnConge_emp;
    QPushButton *btnConge_emp_2;
    QPushButton *btnAjouterEmp;
    QPushButton *btnTrier_emp_3;
    QPushButton *btnExporter_emp_excel_3;
    QWidget *page_add_Emp;
    QGroupBox *groupBox_2;
    QLabel *label_8;
    QLabel *label_12;
    QSpinBox *spinHeuresTravAdd;
    QLabel *label_7;
    QLabel *label_14;
    QLabel *label_6;
    QLineEdit *lineNomAdd;
    QLabel *label_5;
    QLineEdit *lineDepartementAdd;
    QLineEdit *lineCINAdd;
    QLineEdit *lineEmailAdd;
    QLabel *label;
    QLineEdit *linePosteAdd;
    QLabel *label_3;
    QDateEdit *datePointageAdd;
    QPushButton *btnSaveEmployee;
    QCheckBox *checkAbsenceAdd;
    QLabel *label_4;
    QLineEdit *lineTypeContratAdd;
    QLabel *label_15;
    QLineEdit *linePasswordAdd;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_13;
    QDateEdit *dateEmbaucheAdd;
    QSpinBox *spinHeuresSuppAdd;
    QLabel *label_9;
    QLineEdit *linePrenomAdd;
    QLabel *label_2;
    QLineEdit *lineUsernameAdd;
    QLineEdit *lineSalaireAdd;
    QToolButton *BtnPopupCancelLabs_8;
    QPushButton *btnSaveEmployee_2;
    QWidget *page_Edit_Emp;
    QDateEdit *datePointageEmp;
    QLineEdit *linePrenomEmp;
    QLineEdit *lineEmailEmp;
    QDateEdit *dateEmbaucheEmp;
    QLabel *labelUsernameEdit_3;
    QLineEdit *lineTypeContratEmp;
    QLineEdit *linePostemp;
    QLabel *labelSalaireEdit_3;
    QLineEdit *lineCIN_emp;
    QLabel *labelCINEdit_3;
    QLabel *labelPrenomEdit_3;
    QLabel *labelHeuresTravEdit_3;
    QLabel *labelAbsenceEdit_3;
    QLineEdit *lineNomEmp;
    QLineEdit *lineDepartementEmp;
    QLabel *labelDatePointageEdit_3;
    QSpinBox *spinHeuresSuppEmp;
    QLabel *labelDateEmbaucheEdit_3;
    QLabel *labelTypeContratEdit_3;
    QLabel *labelNomEdit_3;
    QLineEdit *lineUsernameEmp;
    QLabel *labelPosteEdit_3;
    QLineEdit *lineSalaireEmp;
    QCheckBox *checkAbsenceEmp;
    QSpinBox *spinHeuresTravemp;
    QLabel *labelDepartementEdit_3;
    QLabel *labelHeuresSuppEdit_3;
    QLabel *labelEmailEdit_3;
    QPushButton *btnSaveEditEmployee_3;
    QPushButton *btnCancelEditEmp;
    QToolButton *BtnPopupCancelLabs_10;
    QWidget *page_Stat;
    QGroupBox *groupBox;
    QToolButton *BtnPopupCancelLabs_9;
    QWidget *page_conge;
    QGroupBox *groupBox_3;
    QPushButton *Rejeter_conge_Emp;
    QPushButton *Accepter_conge_Emp;
    QTableWidget *TableCongeEmp;
    QToolButton *BtnPopupCancelLabs_7;
    QWidget *page_formation;
    QGroupBox *groupBox_4;
    QPushButton *Modifier_Formations_Emp;
    QTableWidget *TableFormations_Emp;
    QPushButton *Exporter_Formations_Emp;
    QToolButton *BtnPopupCancelLabs_6;
    QWidget *pageInventaire;
    QVBoxLayout *verticalLayoutPage1;
    QStackedWidget *stacked_I;
    QWidget *inventory;
    QGridLayout *gridLayout_3;
    QFrame *InventoryCardTable;
    QVBoxLayout *inventoryTableLayout;
    QTableWidget *TableInventory;
    QHBoxLayout *inventoryActions;
    QPushButton *BtnInventoryAdd;
    QPushButton *BtnInventoryAdd_2;
    QPushButton *BtnInventoryEdit;
    QPushButton *BtnInventoryDelete;
    QSpacerItem *inventorySpacer;
    QPushButton *BtnInventoryAdd_5;
    QPushButton *BtnInventoryExport;
    QFrame *InventoryCardFilter;
    QGridLayout *inventoryFilterGrid;
    QLineEdit *InventorySearch;
    QComboBox *InventoryStatus;
    QComboBox *InventoryType;
    QLabel *LblInventoryStatus;
    QLabel *LblInventorySearch;
    QPushButton *BtnInventoryApply;
    QComboBox *InventoryZone;
    QLabel *LblInventoryZone;
    QLabel *LblInventoryType;
    QWidget *ajouteri;
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
    QLabel *LblType_2;
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
    QWidget *modifieri;
    QFrame *PopupInventoryCard_2;
    QVBoxLayout *popupInventoryLayout_2;
    QHBoxLayout *popupInventoryHeader_2;
    QLabel *PopupTitleInventory_2;
    QSpacerItem *popupInventoryHeaderSpacer_2;
    QToolButton *BtnPopupCancelInventory_2;
    QFrame *PopupInventoryForm_2;
    QGridLayout *inventoryFormGrid_2;
    QLabel *LblIdProduct_2;
    QLineEdit *IdProduct_2;
    QLabel *LblName_2;
    QLineEdit *Name_2;
    QLabel *LblSku_2;
    QLineEdit *Sku_2;
    QLabel *LblType_3;
    QComboBox *Type_2;
    QLabel *LblQtAv_2;
    QSpinBox *QtAv_2;
    QLabel *LblQtRs_2;
    QSpinBox *QtRs_2;
    QLabel *LblThreshold_2;
    QSpinBox *Threshold_2;
    QLabel *LblUnit_2;
    QComboBox *Unit_2;
    QLabel *LblPrice_2;
    QDoubleSpinBox *Price_2;
    QLabel *LblStatus_2;
    QComboBox *Status_2;
    QLabel *LblZone_2;
    QComboBox *Zone_2;
    QLabel *LblShelf_2;
    QComboBox *Shelf_2;
    QHBoxLayout *popupInventoryActions_2;
    QSpacerItem *popupInventoryActionsLeft_2;
    QPushButton *BtnPopupSaveInventory_2;
    QPushButton *BtnPopupResetInventory_2;
    QWidget *stati;
    QLabel *stat_pub_6;
    QPushButton *retour_stat_7;
    QWidget *afficheri;
    QLabel *stat_pub_5;
    QPushButton *retour_stat_6;
    QWidget *pagePublication;
    QVBoxLayout *verticalLayoutPubRoot;
    QStackedWidget *stack_pub;
    QWidget *page_pub_list;
    QVBoxLayout *verticalLayoutPubList;
    QTableWidget *tablePublication;
    QLineEdit *lineSearchPub;
    QGridLayout *gridLayoutPubFilters;
    QPushButton *btnReinitialiserPub;
    QLabel *lblCategoriePub;
    QDateEdit *dateDuPub;
    QComboBox *comboCategoriePub;
    QLabel *lblPeriodeDuPub;
    QPushButton *btnAppliquerPub;
    QHBoxLayout *horizontalLayoutPubBottom;
    QPushButton *btnVoirStatistiquesPub;
    QSpacerItem *horizontalSpacerPubBottom;
    QPushButton *btnAjouterPub;
    QPushButton *btnModifierPub;
    QPushButton *btnSupprimerPub;
    QPushButton *btnExporterPub;
    QWidget *page_pub_add;
    QGridLayout *gridLayoutPubAdd;
    QHBoxLayout *hLayoutAddButtons;
    QSpacerItem *spacerAddButtons;
    QPushButton *btnAddPub;
    QPushButton *btnRetourAddPub;
    QLineEdit *lineResumeAdd;
    QLabel *lblTypeBrevetAdd;
    QComboBox *comboTypeBrevetAdd;
    QLabel *lblDomaineAdd;
    QLabel *lblStatusBrevetAdd;
    QLabel *lblResumeAdd;
    QDateEdit *dateDepotAdd;
    QLineEdit *lineNumeroBrevetAdd;
    QLabel *lblDateDepotAdd;
    QLineEdit *lineTitreAdd;
    QComboBox *comboStatusBrevetAdd;
    QLabel *lblNumeroBrevetAdd;
    QLineEdit *lineDomaineAdd;
    QLineEdit *lineInventeursAdd;
    QLabel *lblTitreAdd;
    QLabel *lblInventeursAdd;
    QWidget *page_pub_edit;
    QGridLayout *gridLayoutPubEdit;
    QLabel *lblInventeursEdit;
    QLineEdit *lineTitreEdit;
    QLabel *lblTypeBrevetEdit;
    QLineEdit *lineResumeEdit;
    QLabel *lblDomaineEdit;
    QComboBox *comboTypeBrevetEdit;
    QLabel *lblResumeEdit;
    QComboBox *comboStatusBrevetEdit;
    QDateEdit *dateDepotEdit;
    QHBoxLayout *hLayoutEditButtons;
    QSpacerItem *spacerEditButtons;
    QPushButton *btnConfirmEditPub;
    QPushButton *btnRetourEditPub;
    QLineEdit *lineInventeursEdit;
    QLineEdit *lineNumeroBrevetEdit;
    QLabel *lblDateDepotEdit;
    QLabel *lblTitreEdit;
    QLabel *lblStatusBrevetEdit;
    QLineEdit *lineDomaineEdit;
    QLabel *lblNumeroBrevetEdit;
    QWidget *page_pub_empty;
    QVBoxLayout *verticalLayoutPubEmpty;
    QLabel *stat_pub;
    QComboBox *comboBox;
    QPushButton *retour_stat;
    QWidget *pageFinance;
    QVBoxLayout *verticalLayoutPage3;
    QStackedWidget *stacked_F;
    QWidget *finance;
    QGridLayout *gridLayout;
    QFrame *CardFilter;
    QGridLayout *filterGrid;
    QLabel *LblTo;
    QDateEdit *DateFrom;
    QComboBox *CbType;
    QLabel *LblFrom;
    QLineEdit *EdSearch;
    QLabel *LblType;
    QDateEdit *DateTo;
    QPushButton *BtnReset;
    QPushButton *BtnApply;
    QFrame *CardTable;
    QVBoxLayout *tableCardLayout;
    QLabel *TableTitle;
    QTableWidget *TableFinance;
    QHBoxLayout *tableActions;
    QPushButton *BtnAdd;
    QPushButton *BtnEdit;
    QPushButton *BtnDelete;
    QSpacerItem *tableActionsSpacer;
    QPushButton *BtnAdd_4;
    QPushButton *BtnExport;
    QWidget *ajouterF;
    QGridLayout *gridLayout_2;
    QFrame *OverlayFinance;
    QVBoxLayout *overlayFinanceLayout;
    QSpacerItem *ovTop;
    QFrame *PopupFinanceCard;
    QVBoxLayout *popupFinanceCardLayout;
    QLabel *PopupTitleFinance;
    QGridLayout *popupFinanceGrid;
    QLabel *LblAmount;
    QComboBox *FormPayMode;
    QLabel *LblCat2;
    QLabel *LblCode;
    QLineEdit *FormDesc;
    QDateEdit *FormDate;
    QLabel *LblDesc;
    QDateEdit *FormCreatedAt;
    QLabel *LblDate2;
    QComboBox *FormType;
    QHBoxLayout *popupFinanceButtons;
    QSpacerItem *pfSpacer;
    QPushButton *BtnPopupSaveFinance;
    QPushButton *BtnPopupCancelFinance;
    QLabel *LblFType;
    QLabel *LblCreated;
    QLineEdit *FormCode;
    QLabel *LblPay;
    QLineEdit *FormAmount;
    QLineEdit *FormCategory;
    QSpacerItem *ovBottom;
    QWidget *modifierF;
    QFrame *OverlayFinance_2;
    QVBoxLayout *overlayFinanceLayout_2;
    QSpacerItem *ovTop_2;
    QFrame *PopupFinanceCard_2;
    QVBoxLayout *popupFinanceCardLayout_2;
    QLabel *PopupTitleFinance_2;
    QGridLayout *popupFinanceGrid_2;
    QDateEdit *FormDate_2;
    QComboBox *FormPayMode_2;
    QLineEdit *FormCategory_2;
    QLabel *LblCode_2;
    QComboBox *FormType_2;
    QLabel *LblCreated_2;
    QLabel *LblAmount_2;
    QLabel *LblDesc_2;
    QLineEdit *FormCode_2;
    QLabel *LblPay_2;
    QLabel *LblCat2_2;
    QLabel *LblDate2_2;
    QHBoxLayout *popupFinanceButtons_2;
    QSpacerItem *pfSpacer_2;
    QPushButton *BtnPopupSaveFinance_2;
    QPushButton *BtnPopupCancelFinance_2;
    QLineEdit *FormDesc_2;
    QDateEdit *FormCreatedAt_2;
    QLabel *LblFType_2;
    QLineEdit *FormAmount_2;
    QSpacerItem *ovBottom_2;
    QWidget *statsF;
    QComboBox *comboBox_3;
    QLabel *stat_pub_3;
    QPushButton *retour_stat_4;
    QWidget *afficherF;
    QPushButton *retour_stat_5;
    QLabel *stat_pub_4;
    QWidget *pageLaboratoires;
    QVBoxLayout *verticalLayoutPage4;
    QStackedWidget *stacked_L;
    QWidget *Lab;
    QGridLayout *gridLayout_6;
    QTableWidget *TableLabs_2;
    QPushButton *btnExporterPub_2;
    QPushButton *btnVoirStatistiquesPub_2;
    QPushButton *btnAjouterPub_4;
    QPushButton *btnAjouterPub_3;
    QPushButton *btnAjouterPub_2;
    QPushButton *btnModifierPub_2;
    QPushButton *btnSupprimerPub_2;
    QFrame *LabsCardFilter_2;
    QGridLayout *gridLayout_5;
    QLabel *LblLabsSearch_2;
    QLabel *LblLabsSpec_2;
    QLabel *LblLabsCap_2;
    QPushButton *btnAppliquerPub_3;
    QLineEdit *LabsSearch_2;
    QComboBox *LabsSpec_2;
    QComboBox *LabsCap_2;
    QPushButton *btnReinitialiserPub_3;
    QWidget *modifierL;
    QFrame *PopupLabsCard_4;
    QFrame *PopupLabsForm_5;
    QLineEdit *LabLocation_5;
    QLineEdit *LabResponsible_5;
    QComboBox *LabSpec_5;
    QLabel *LblLabCap_5;
    QLabel *LblLabLoc_5;
    QLabel *LblLabName_5;
    QLabel *LblLabNum_5;
    QLineEdit *LabName_5;
    QLineEdit *LabNumber_5;
    QLabel *LblLabResp_5;
    QLabel *LblLabSpec_5;
    QComboBox *LabCap_5;
    QWidget *layoutWidget;
    QHBoxLayout *popupLabsHeader_5;
    QLabel *PopupTitleLabs_5;
    QSpacerItem *popupLabsHeaderSpacer_5;
    QToolButton *BtnPopupCancelLabs_5;
    QPushButton *BtnPopupResetLabs_5;
    QPushButton *BtnPopupSaveLabs_5;
    QWidget *ajouterL;
    QFrame *PopupLabsCard_3;
    QFrame *PopupLabsForm_3;
    QLineEdit *LabLocation_3;
    QLineEdit *LabResponsible_3;
    QComboBox *LabSpec_3;
    QLabel *LblLabCap_3;
    QLabel *LblLabLoc_3;
    QLabel *LblLabName_3;
    QLabel *LblLabNum_3;
    QLineEdit *LabName_3;
    QLineEdit *LabNumber_3;
    QLabel *LblLabResp_3;
    QLabel *LblLabSpec_3;
    QComboBox *LabCap_3;
    QWidget *layoutWidget1;
    QHBoxLayout *popupLabsHeader_3;
    QLabel *PopupTitleLabs_3;
    QSpacerItem *popupLabsHeaderSpacer_3;
    QToolButton *BtnPopupCancelLabs_3;
    QPushButton *BtnPopupSaveLabs_3;
    QPushButton *BtnPopupResetLabs_3;
    QWidget *statL;
    QPushButton *retour_stat_2;
    QComboBox *comboBox_2;
    QLabel *stat_pub_2;
    QWidget *affichierL;
    QPushButton *retour_stat_3;
    QWidget *mapsL;
    QLabel *stat_pub_7;
    QPushButton *retour_stat_8;
    QWidget *pageProjets;
    QVBoxLayout *verticalLayoutProjRoot;
    QStackedWidget *stack_proj;
    QWidget *page_proj_list;
    QVBoxLayout *verticalLayoutProjList;
    QLineEdit *lineSearchProj;
    QGridLayout *gridLayoutProjFilters;
    QDateEdit *dateDuProj;
    QComboBox *comboCategorieProj;
    QPushButton *btnAppliquerProj;
    QLabel *lblCategorieProj;
    QLabel *lblPeriodeDuProj;
    QTableWidget *tableProjets;
    QHBoxLayout *horizontalLayoutProjBottom;
    QPushButton *btnAjouterProj;
    QPushButton *btnModifierProj;
    QPushButton *btnSupprimerProj;
    QSpacerItem *horizontalSpacerProjBottom;
    QPushButton *btnVoirStatistiquesProj;
    QWidget *page_proj_add;
    QGridLayout *gridLayoutProjAdd;
    QHBoxLayout *hLayoutAddButtons1;
    QSpacerItem *spacerAddButtons1;
    QPushButton *btnAddProj;
    QPushButton *btnRetourAddProj;
    QLineEdit *lineResumeAdd1;
    QLabel *lblTypeBrevetAdd1;
    QComboBox *comboTypeBrevetAdd1;
    QLabel *lblDomaineAdd1;
    QLabel *lblStatusBrevetAdd1;
    QLabel *lblResumeAdd1;
    QDateEdit *dateDepotAdd1;
    QLineEdit *lineNumeroBrevetAdd1;
    QLabel *lblDateDepotAdd1;
    QLineEdit *lineTitreAdd1;
    QComboBox *comboStatusBrevetAdd1;
    QLabel *lblNumeroBrevetAdd1;
    QLineEdit *lineDomaineAdd1;
    QLineEdit *lineInventeursAdd1;
    QLabel *lblTitreAdd1;
    QLabel *lblInventeursAdd1;
    QWidget *page_proj_edit;
    QGridLayout *gridLayoutProjEdit;
    QLabel *lblInventeursEdit1;
    QLineEdit *lineTitreEdit1;
    QLabel *lblTypeBrevetEdit1;
    QLineEdit *lineResumeEdit1;
    QLabel *lblDomaineEdit1;
    QComboBox *comboTypeBrevetEdit1;
    QLabel *lblResumeEdit1;
    QComboBox *comboStatusBrevetEdit1;
    QDateEdit *dateDepotEdit1;
    QHBoxLayout *hLayoutEditButtons1;
    QSpacerItem *spacerEditButtons1;
    QPushButton *btnConfirmEditProj;
    QPushButton *btnRetourEditProj;
    QLineEdit *lineInventeursEdit1;
    QLineEdit *lineNumeroBrevetEdit1;
    QLabel *lblDateDepotEdit1;
    QLabel *lblTitreEdit1;
    QLabel *lblStatusBrevetEdit1;
    QLineEdit *lineDomaineEdit1;
    QLabel *lblNumeroBrevetEdit1;
    QWidget *page_proj_empty;
    QVBoxLayout *verticalLayoutProjEmpty;
    QLabel *stat_pub1;
    QPushButton *retour_statn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1528, 769);
        MainWindow->setMinimumSize(QSize(1100, 650));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutMain = new QHBoxLayout(centralwidget);
        horizontalLayoutMain->setSpacing(16);
        horizontalLayoutMain->setObjectName("horizontalLayoutMain");
        horizontalLayoutMain->setContentsMargins(16, 16, 16, 16);
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(240, 0));
        sidebarFrame->setMaximumSize(QSize(260, 16777215));
        sidebarFrame->setFrameShape(QFrame::Shape::StyledPanel);
        sidebarFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayoutSidebar = new QVBoxLayout(sidebarFrame);
        verticalLayoutSidebar->setSpacing(12);
        verticalLayoutSidebar->setObjectName("verticalLayoutSidebar");
        verticalLayoutSidebar->setContentsMargins(14, 14, 14, 14);
        logoLabel = new QLabel(sidebarFrame);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setStyleSheet(QString::fromUtf8(""));

        verticalLayoutSidebar->addWidget(logoLabel);

        btnEmployee = new QPushButton(sidebarFrame);
        btnEmployee->setObjectName("btnEmployee");

        verticalLayoutSidebar->addWidget(btnEmployee);

        btnInventaire = new QPushButton(sidebarFrame);
        btnInventaire->setObjectName("btnInventaire");

        verticalLayoutSidebar->addWidget(btnInventaire);

        btnPublication = new QPushButton(sidebarFrame);
        btnPublication->setObjectName("btnPublication");

        verticalLayoutSidebar->addWidget(btnPublication);

        btnFinance = new QPushButton(sidebarFrame);
        btnFinance->setObjectName("btnFinance");

        verticalLayoutSidebar->addWidget(btnFinance);

        btnLaboratoires = new QPushButton(sidebarFrame);
        btnLaboratoires->setObjectName("btnLaboratoires");

        verticalLayoutSidebar->addWidget(btnLaboratoires);

        btnProjets = new QPushButton(sidebarFrame);
        btnProjets->setObjectName("btnProjets");

        verticalLayoutSidebar->addWidget(btnProjets);

        verticalSpacer = new QSpacerItem(17, 262, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutSidebar->addItem(verticalSpacer);

        btnDeconnecter = new QPushButton(sidebarFrame);
        btnDeconnecter->setObjectName("btnDeconnecter");

        verticalLayoutSidebar->addWidget(btnDeconnecter);


        horizontalLayoutMain->addWidget(sidebarFrame);

        verticalLayoutRight = new QVBoxLayout();
        verticalLayoutRight->setSpacing(12);
        verticalLayoutRight->setObjectName("verticalLayoutRight");
        verticalLayoutRight->setContentsMargins(0, 0, 0, 0);
        topBar = new QFrame(centralwidget);
        topBar->setObjectName("topBar");
        topBar->setMinimumSize(QSize(0, 56));
        topBar->setMaximumSize(QSize(16777215, 70));
        topBar->setFrameShape(QFrame::Shape::NoFrame);
        lblBrand = new QLabel(topBar);
        lblBrand->setObjectName("lblBrand");
        lblBrand->setGeometry(QRect(14, 10, 160, 22));
        lblBrand->setTextFormat(Qt::TextFormat::RichText);
        lblBrand->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        lblPageTitle = new QLabel(topBar);
        lblPageTitle->setObjectName("lblPageTitle");
        lblPageTitle->setGeometry(QRect(320, 10, 200, 22));
        QFont font;
        font.setFamilies({QString::fromUtf8("Vivaldi")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        lblPageTitle->setFont(font);
        lblPageTitle->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayoutRight->addWidget(topBar);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageEmployee = new QWidget();
        pageEmployee->setObjectName("pageEmployee");
        verticalLayoutPage0 = new QVBoxLayout(pageEmployee);
        verticalLayoutPage0->setObjectName("verticalLayoutPage0");
        stack_emp = new QStackedWidget(pageEmployee);
        stack_emp->setObjectName("stack_emp");
        page_Emp = new QWidget();
        page_Emp->setObjectName("page_Emp");
        gridLayout_4 = new QGridLayout(page_Emp);
        gridLayout_4->setObjectName("gridLayout_4");
        lineSearchEmp = new QLineEdit(page_Emp);
        lineSearchEmp->setObjectName("lineSearchEmp");

        gridLayout_4->addWidget(lineSearchEmp, 0, 0, 1, 2);

        btnChercher_emp = new QPushButton(page_Emp);
        btnChercher_emp->setObjectName("btnChercher_emp");

        gridLayout_4->addWidget(btnChercher_emp, 0, 2, 1, 1);

        btnExporter_emp_excel = new QPushButton(page_Emp);
        btnExporter_emp_excel->setObjectName("btnExporter_emp_excel");

        gridLayout_4->addWidget(btnExporter_emp_excel, 0, 3, 1, 1);

        btnTrier_emp = new QPushButton(page_Emp);
        btnTrier_emp->setObjectName("btnTrier_emp");

        gridLayout_4->addWidget(btnTrier_emp, 0, 4, 1, 1);

        TableEmp = new QTableWidget(page_Emp);
        if (TableEmp->columnCount() < 9)
            TableEmp->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        if (TableEmp->rowCount() < 9)
            TableEmp->setRowCount(9);
        TableEmp->setObjectName("TableEmp");
        TableEmp->setMinimumSize(QSize(0, 280));
        TableEmp->setRowCount(9);
        TableEmp->setColumnCount(9);

        gridLayout_4->addWidget(TableEmp, 1, 0, 3, 4);

        btnConge_emp_3 = new QPushButton(page_Emp);
        btnConge_emp_3->setObjectName("btnConge_emp_3");

        gridLayout_4->addWidget(btnConge_emp_3, 1, 4, 1, 1);

        btnConge_emp = new QPushButton(page_Emp);
        btnConge_emp->setObjectName("btnConge_emp");

        gridLayout_4->addWidget(btnConge_emp, 2, 4, 1, 1);

        btnConge_emp_2 = new QPushButton(page_Emp);
        btnConge_emp_2->setObjectName("btnConge_emp_2");

        gridLayout_4->addWidget(btnConge_emp_2, 3, 4, 1, 1);

        btnAjouterEmp = new QPushButton(page_Emp);
        btnAjouterEmp->setObjectName("btnAjouterEmp");

        gridLayout_4->addWidget(btnAjouterEmp, 4, 0, 1, 1);

        btnTrier_emp_3 = new QPushButton(page_Emp);
        btnTrier_emp_3->setObjectName("btnTrier_emp_3");

        gridLayout_4->addWidget(btnTrier_emp_3, 4, 1, 1, 1);

        btnExporter_emp_excel_3 = new QPushButton(page_Emp);
        btnExporter_emp_excel_3->setObjectName("btnExporter_emp_excel_3");

        gridLayout_4->addWidget(btnExporter_emp_excel_3, 4, 2, 1, 2);

        stack_emp->addWidget(page_Emp);
        page_add_Emp = new QWidget();
        page_add_Emp->setObjectName("page_add_Emp");
        groupBox_2 = new QGroupBox(page_add_Emp);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(0, 0, 1181, 591));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(550, 50, 100, 34));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(550, 250, 100, 34));
        spinHeuresTravAdd = new QSpinBox(groupBox_2);
        spinHeuresTravAdd->setObjectName("spinHeuresTravAdd");
        spinHeuresTravAdd->setGeometry(QRect(714, 300, 250, 40));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 350, 100, 34));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(550, 350, 128, 34));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 300, 100, 34));
        lineNomAdd = new QLineEdit(groupBox_2);
        lineNomAdd->setObjectName("lineNomAdd");
        lineNomAdd->setGeometry(QRect(150, 250, 250, 40));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 250, 100, 34));
        lineDepartementAdd = new QLineEdit(groupBox_2);
        lineDepartementAdd->setObjectName("lineDepartementAdd");
        lineDepartementAdd->setGeometry(QRect(714, 50, 250, 40));
        lineCINAdd = new QLineEdit(groupBox_2);
        lineCINAdd->setObjectName("lineCINAdd");
        lineCINAdd->setGeometry(QRect(150, 50, 250, 40));
        lineEmailAdd = new QLineEdit(groupBox_2);
        lineEmailAdd->setObjectName("lineEmailAdd");
        lineEmailAdd->setGeometry(QRect(150, 200, 250, 40));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 50, 100, 20));
        linePosteAdd = new QLineEdit(groupBox_2);
        linePosteAdd->setObjectName("linePosteAdd");
        linePosteAdd->setGeometry(QRect(150, 350, 250, 40));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 150, 100, 34));
        datePointageAdd = new QDateEdit(groupBox_2);
        datePointageAdd->setObjectName("datePointageAdd");
        datePointageAdd->setGeometry(QRect(714, 250, 250, 40));
        btnSaveEmployee = new QPushButton(groupBox_2);
        btnSaveEmployee->setObjectName("btnSaveEmployee");
        btnSaveEmployee->setGeometry(QRect(180, 460, 250, 40));
        checkAbsenceAdd = new QCheckBox(groupBox_2);
        checkAbsenceAdd->setObjectName("checkAbsenceAdd");
        checkAbsenceAdd->setGeometry(QRect(150, 400, 21, 31));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 200, 100, 34));
        lineTypeContratAdd = new QLineEdit(groupBox_2);
        lineTypeContratAdd->setObjectName("lineTypeContratAdd");
        lineTypeContratAdd->setGeometry(QRect(714, 100, 250, 40));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(40, 400, 100, 15));
        linePasswordAdd = new QLineEdit(groupBox_2);
        linePasswordAdd->setObjectName("linePasswordAdd");
        linePasswordAdd->setGeometry(QRect(150, 150, 250, 40));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(550, 150, 100, 34));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(550, 200, 100, 34));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(550, 300, 93, 34));
        dateEmbaucheAdd = new QDateEdit(groupBox_2);
        dateEmbaucheAdd->setObjectName("dateEmbaucheAdd");
        dateEmbaucheAdd->setGeometry(QRect(714, 150, 250, 40));
        spinHeuresSuppAdd = new QSpinBox(groupBox_2);
        spinHeuresSuppAdd->setObjectName("spinHeuresSuppAdd");
        spinHeuresSuppAdd->setGeometry(QRect(714, 350, 250, 40));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(550, 100, 100, 34));
        linePrenomAdd = new QLineEdit(groupBox_2);
        linePrenomAdd->setObjectName("linePrenomAdd");
        linePrenomAdd->setGeometry(QRect(150, 300, 250, 40));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 100, 100, 34));
        lineUsernameAdd = new QLineEdit(groupBox_2);
        lineUsernameAdd->setObjectName("lineUsernameAdd");
        lineUsernameAdd->setGeometry(QRect(150, 100, 250, 40));
        lineSalaireAdd = new QLineEdit(groupBox_2);
        lineSalaireAdd->setObjectName("lineSalaireAdd");
        lineSalaireAdd->setGeometry(QRect(714, 200, 250, 40));
        BtnPopupCancelLabs_8 = new QToolButton(groupBox_2);
        BtnPopupCancelLabs_8->setObjectName("BtnPopupCancelLabs_8");
        BtnPopupCancelLabs_8->setGeometry(QRect(1090, 60, 31, 27));
        btnSaveEmployee_2 = new QPushButton(groupBox_2);
        btnSaveEmployee_2->setObjectName("btnSaveEmployee_2");
        btnSaveEmployee_2->setGeometry(QRect(630, 460, 250, 40));
        stack_emp->addWidget(page_add_Emp);
        page_Edit_Emp = new QWidget();
        page_Edit_Emp->setObjectName("page_Edit_Emp");
        datePointageEmp = new QDateEdit(page_Edit_Emp);
        datePointageEmp->setObjectName("datePointageEmp");
        datePointageEmp->setGeometry(QRect(710, 200, 481, 41));
        linePrenomEmp = new QLineEdit(page_Edit_Emp);
        linePrenomEmp->setObjectName("linePrenomEmp");
        linePrenomEmp->setGeometry(QRect(110, 270, 351, 31));
        lineEmailEmp = new QLineEdit(page_Edit_Emp);
        lineEmailEmp->setObjectName("lineEmailEmp");
        lineEmailEmp->setGeometry(QRect(110, 160, 351, 31));
        dateEmbaucheEmp = new QDateEdit(page_Edit_Emp);
        dateEmbaucheEmp->setObjectName("dateEmbaucheEmp");
        dateEmbaucheEmp->setGeometry(QRect(710, 100, 481, 41));
        labelUsernameEdit_3 = new QLabel(page_Edit_Emp);
        labelUsernameEdit_3->setObjectName("labelUsernameEdit_3");
        labelUsernameEdit_3->setGeometry(QRect(30, 110, 71, 31));
        lineTypeContratEmp = new QLineEdit(page_Edit_Emp);
        lineTypeContratEmp->setObjectName("lineTypeContratEmp");
        lineTypeContratEmp->setGeometry(QRect(710, 50, 481, 41));
        linePostemp = new QLineEdit(page_Edit_Emp);
        linePostemp->setObjectName("linePostemp");
        linePostemp->setGeometry(QRect(110, 340, 351, 31));
        labelSalaireEdit_3 = new QLabel(page_Edit_Emp);
        labelSalaireEdit_3->setObjectName("labelSalaireEdit_3");
        labelSalaireEdit_3->setGeometry(QRect(600, 160, 61, 21));
        lineCIN_emp = new QLineEdit(page_Edit_Emp);
        lineCIN_emp->setObjectName("lineCIN_emp");
        lineCIN_emp->setGeometry(QRect(110, 50, 351, 31));
        lineCIN_emp->setReadOnly(true);
        labelCINEdit_3 = new QLabel(page_Edit_Emp);
        labelCINEdit_3->setObjectName("labelCINEdit_3");
        labelCINEdit_3->setGeometry(QRect(29, 55, 41, 21));
        labelPrenomEdit_3 = new QLabel(page_Edit_Emp);
        labelPrenomEdit_3->setObjectName("labelPrenomEdit_3");
        labelPrenomEdit_3->setGeometry(QRect(30, 270, 61, 31));
        labelHeuresTravEdit_3 = new QLabel(page_Edit_Emp);
        labelHeuresTravEdit_3->setObjectName("labelHeuresTravEdit_3");
        labelHeuresTravEdit_3->setGeometry(QRect(570, 270, 141, 31));
        labelAbsenceEdit_3 = new QLabel(page_Edit_Emp);
        labelAbsenceEdit_3->setObjectName("labelAbsenceEdit_3");
        labelAbsenceEdit_3->setGeometry(QRect(560, 400, 45, 16));
        lineNomEmp = new QLineEdit(page_Edit_Emp);
        lineNomEmp->setObjectName("lineNomEmp");
        lineNomEmp->setGeometry(QRect(110, 210, 351, 31));
        lineDepartementEmp = new QLineEdit(page_Edit_Emp);
        lineDepartementEmp->setObjectName("lineDepartementEmp");
        lineDepartementEmp->setGeometry(QRect(110, 400, 351, 31));
        labelDatePointageEdit_3 = new QLabel(page_Edit_Emp);
        labelDatePointageEdit_3->setObjectName("labelDatePointageEdit_3");
        labelDatePointageEdit_3->setGeometry(QRect(590, 210, 111, 21));
        spinHeuresSuppEmp = new QSpinBox(page_Edit_Emp);
        spinHeuresSuppEmp->setObjectName("spinHeuresSuppEmp");
        spinHeuresSuppEmp->setGeometry(QRect(710, 320, 481, 41));
        labelDateEmbaucheEdit_3 = new QLabel(page_Edit_Emp);
        labelDateEmbaucheEdit_3->setObjectName("labelDateEmbaucheEdit_3");
        labelDateEmbaucheEdit_3->setGeometry(QRect(590, 110, 111, 21));
        labelTypeContratEdit_3 = new QLabel(page_Edit_Emp);
        labelTypeContratEdit_3->setObjectName("labelTypeContratEdit_3");
        labelTypeContratEdit_3->setGeometry(QRect(590, 50, 111, 31));
        labelNomEdit_3 = new QLabel(page_Edit_Emp);
        labelNomEdit_3->setObjectName("labelNomEdit_3");
        labelNomEdit_3->setGeometry(QRect(30, 210, 61, 31));
        lineUsernameEmp = new QLineEdit(page_Edit_Emp);
        lineUsernameEmp->setObjectName("lineUsernameEmp");
        lineUsernameEmp->setGeometry(QRect(110, 110, 351, 31));
        labelPosteEdit_3 = new QLabel(page_Edit_Emp);
        labelPosteEdit_3->setObjectName("labelPosteEdit_3");
        labelPosteEdit_3->setGeometry(QRect(30, 340, 51, 31));
        lineSalaireEmp = new QLineEdit(page_Edit_Emp);
        lineSalaireEmp->setObjectName("lineSalaireEmp");
        lineSalaireEmp->setGeometry(QRect(710, 150, 481, 41));
        checkAbsenceEmp = new QCheckBox(page_Edit_Emp);
        checkAbsenceEmp->setObjectName("checkAbsenceEmp");
        checkAbsenceEmp->setGeometry(QRect(750, 400, 31, 31));
        spinHeuresTravemp = new QSpinBox(page_Edit_Emp);
        spinHeuresTravemp->setObjectName("spinHeuresTravemp");
        spinHeuresTravemp->setGeometry(QRect(710, 261, 481, 41));
        labelDepartementEdit_3 = new QLabel(page_Edit_Emp);
        labelDepartementEdit_3->setObjectName("labelDepartementEdit_3");
        labelDepartementEdit_3->setGeometry(QRect(20, 400, 69, 16));
        labelHeuresSuppEdit_3 = new QLabel(page_Edit_Emp);
        labelHeuresSuppEdit_3->setObjectName("labelHeuresSuppEdit_3");
        labelHeuresSuppEdit_3->setGeometry(QRect(560, 330, 128, 16));
        labelEmailEdit_3 = new QLabel(page_Edit_Emp);
        labelEmailEdit_3->setObjectName("labelEmailEdit_3");
        labelEmailEdit_3->setGeometry(QRect(30, 160, 61, 21));
        btnSaveEditEmployee_3 = new QPushButton(page_Edit_Emp);
        btnSaveEditEmployee_3->setObjectName("btnSaveEditEmployee_3");
        btnSaveEditEmployee_3->setGeometry(QRect(330, 490, 231, 41));
        btnCancelEditEmp = new QPushButton(page_Edit_Emp);
        btnCancelEditEmp->setObjectName("btnCancelEditEmp");
        btnCancelEditEmp->setGeometry(QRect(660, 490, 221, 41));
        BtnPopupCancelLabs_10 = new QToolButton(page_Edit_Emp);
        BtnPopupCancelLabs_10->setObjectName("BtnPopupCancelLabs_10");
        BtnPopupCancelLabs_10->setGeometry(QRect(1180, 10, 31, 27));
        stack_emp->addWidget(page_Edit_Emp);
        page_Stat = new QWidget();
        page_Stat->setObjectName("page_Stat");
        groupBox = new QGroupBox(page_Stat);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 30, 941, 461));
        BtnPopupCancelLabs_9 = new QToolButton(page_Stat);
        BtnPopupCancelLabs_9->setObjectName("BtnPopupCancelLabs_9");
        BtnPopupCancelLabs_9->setGeometry(QRect(1080, 50, 31, 27));
        stack_emp->addWidget(page_Stat);
        page_conge = new QWidget();
        page_conge->setObjectName("page_conge");
        groupBox_3 = new QGroupBox(page_conge);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(50, 40, 1151, 541));
        Rejeter_conge_Emp = new QPushButton(groupBox_3);
        Rejeter_conge_Emp->setObjectName("Rejeter_conge_Emp");
        Rejeter_conge_Emp->setGeometry(QRect(650, 470, 200, 41));
        Accepter_conge_Emp = new QPushButton(groupBox_3);
        Accepter_conge_Emp->setObjectName("Accepter_conge_Emp");
        Accepter_conge_Emp->setGeometry(QRect(370, 470, 200, 41));
        TableCongeEmp = new QTableWidget(groupBox_3);
        if (TableCongeEmp->columnCount() < 6)
            TableCongeEmp->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        if (TableCongeEmp->rowCount() < 30)
            TableCongeEmp->setRowCount(30);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(6, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(7, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(8, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(9, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(10, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(11, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(12, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(13, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(14, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(15, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(16, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(17, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(18, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(19, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        TableCongeEmp->setVerticalHeaderItem(20, __qtablewidgetitem35);
        TableCongeEmp->setObjectName("TableCongeEmp");
        TableCongeEmp->setGeometry(QRect(210, 100, 651, 321));
        TableCongeEmp->setMinimumSize(QSize(0, 280));
        TableCongeEmp->setRowCount(30);
        TableCongeEmp->setColumnCount(6);
        BtnPopupCancelLabs_7 = new QToolButton(groupBox_3);
        BtnPopupCancelLabs_7->setObjectName("BtnPopupCancelLabs_7");
        BtnPopupCancelLabs_7->setGeometry(QRect(1090, 40, 31, 27));
        stack_emp->addWidget(page_conge);
        page_formation = new QWidget();
        page_formation->setObjectName("page_formation");
        groupBox_4 = new QGroupBox(page_formation);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(30, 10, 1181, 571));
        Modifier_Formations_Emp = new QPushButton(groupBox_4);
        Modifier_Formations_Emp->setObjectName("Modifier_Formations_Emp");
        Modifier_Formations_Emp->setGeometry(QRect(100, 500, 441, 24));
        TableFormations_Emp = new QTableWidget(groupBox_4);
        if (TableFormations_Emp->columnCount() < 8)
            TableFormations_Emp->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(7, __qtablewidgetitem43);
        if (TableFormations_Emp->rowCount() < 9)
            TableFormations_Emp->setRowCount(9);
        TableFormations_Emp->setObjectName("TableFormations_Emp");
        TableFormations_Emp->setGeometry(QRect(70, 90, 901, 371));
        TableFormations_Emp->setMinimumSize(QSize(0, 280));
        TableFormations_Emp->setRowCount(9);
        TableFormations_Emp->setColumnCount(8);
        Exporter_Formations_Emp = new QPushButton(groupBox_4);
        Exporter_Formations_Emp->setObjectName("Exporter_Formations_Emp");
        Exporter_Formations_Emp->setGeometry(QRect(660, 500, 321, 24));
        BtnPopupCancelLabs_6 = new QToolButton(groupBox_4);
        BtnPopupCancelLabs_6->setObjectName("BtnPopupCancelLabs_6");
        BtnPopupCancelLabs_6->setGeometry(QRect(1040, 50, 31, 27));
        stack_emp->addWidget(page_formation);

        verticalLayoutPage0->addWidget(stack_emp);

        stackedWidget->addWidget(pageEmployee);
        pageInventaire = new QWidget();
        pageInventaire->setObjectName("pageInventaire");
        verticalLayoutPage1 = new QVBoxLayout(pageInventaire);
        verticalLayoutPage1->setObjectName("verticalLayoutPage1");
        stacked_I = new QStackedWidget(pageInventaire);
        stacked_I->setObjectName("stacked_I");
        inventory = new QWidget();
        inventory->setObjectName("inventory");
        gridLayout_3 = new QGridLayout(inventory);
        gridLayout_3->setObjectName("gridLayout_3");
        InventoryCardTable = new QFrame(inventory);
        InventoryCardTable->setObjectName("InventoryCardTable");
        InventoryCardTable->setFrameShape(QFrame::Shape::NoFrame);
        inventoryTableLayout = new QVBoxLayout(InventoryCardTable);
        inventoryTableLayout->setSpacing(10);
        inventoryTableLayout->setObjectName("inventoryTableLayout");
        inventoryTableLayout->setContentsMargins(16, 16, 16, 16);
        TableInventory = new QTableWidget(InventoryCardTable);
        if (TableInventory->columnCount() < 12)
            TableInventory->setColumnCount(12);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(2, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(3, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(4, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(5, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(6, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(7, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(8, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(9, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(10, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(11, __qtablewidgetitem55);
        if (TableInventory->rowCount() < 5)
            TableInventory->setRowCount(5);
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

        BtnInventoryAdd_2 = new QPushButton(InventoryCardTable);
        BtnInventoryAdd_2->setObjectName("BtnInventoryAdd_2");

        inventoryActions->addWidget(BtnInventoryAdd_2);

        BtnInventoryEdit = new QPushButton(InventoryCardTable);
        BtnInventoryEdit->setObjectName("BtnInventoryEdit");

        inventoryActions->addWidget(BtnInventoryEdit);

        BtnInventoryDelete = new QPushButton(InventoryCardTable);
        BtnInventoryDelete->setObjectName("BtnInventoryDelete");

        inventoryActions->addWidget(BtnInventoryDelete);

        inventorySpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inventoryActions->addItem(inventorySpacer);

        BtnInventoryAdd_5 = new QPushButton(InventoryCardTable);
        BtnInventoryAdd_5->setObjectName("BtnInventoryAdd_5");

        inventoryActions->addWidget(BtnInventoryAdd_5);

        BtnInventoryExport = new QPushButton(InventoryCardTable);
        BtnInventoryExport->setObjectName("BtnInventoryExport");

        inventoryActions->addWidget(BtnInventoryExport);


        inventoryTableLayout->addLayout(inventoryActions);


        gridLayout_3->addWidget(InventoryCardTable, 1, 0, 1, 1);

        InventoryCardFilter = new QFrame(inventory);
        InventoryCardFilter->setObjectName("InventoryCardFilter");
        InventoryCardFilter->setFrameShape(QFrame::Shape::NoFrame);
        inventoryFilterGrid = new QGridLayout(InventoryCardFilter);
        inventoryFilterGrid->setObjectName("inventoryFilterGrid");
        inventoryFilterGrid->setHorizontalSpacing(12);
        inventoryFilterGrid->setVerticalSpacing(10);
        inventoryFilterGrid->setContentsMargins(16, 16, 16, 16);
        InventorySearch = new QLineEdit(InventoryCardFilter);
        InventorySearch->setObjectName("InventorySearch");

        inventoryFilterGrid->addWidget(InventorySearch, 1, 0, 1, 1);

        InventoryStatus = new QComboBox(InventoryCardFilter);
        InventoryStatus->addItem(QString());
        InventoryStatus->addItem(QString());
        InventoryStatus->addItem(QString());
        InventoryStatus->setObjectName("InventoryStatus");

        inventoryFilterGrid->addWidget(InventoryStatus, 1, 2, 1, 1);

        InventoryType = new QComboBox(InventoryCardFilter);
        InventoryType->setObjectName("InventoryType");

        inventoryFilterGrid->addWidget(InventoryType, 1, 1, 1, 1);

        LblInventoryStatus = new QLabel(InventoryCardFilter);
        LblInventoryStatus->setObjectName("LblInventoryStatus");

        inventoryFilterGrid->addWidget(LblInventoryStatus, 0, 2, 1, 1);

        LblInventorySearch = new QLabel(InventoryCardFilter);
        LblInventorySearch->setObjectName("LblInventorySearch");

        inventoryFilterGrid->addWidget(LblInventorySearch, 0, 0, 1, 1);

        BtnInventoryApply = new QPushButton(InventoryCardFilter);
        BtnInventoryApply->setObjectName("BtnInventoryApply");

        inventoryFilterGrid->addWidget(BtnInventoryApply, 1, 4, 1, 1);

        InventoryZone = new QComboBox(InventoryCardFilter);
        InventoryZone->addItem(QString());
        InventoryZone->addItem(QString());
        InventoryZone->addItem(QString());
        InventoryZone->addItem(QString());
        InventoryZone->setObjectName("InventoryZone");

        inventoryFilterGrid->addWidget(InventoryZone, 1, 3, 1, 1);

        LblInventoryZone = new QLabel(InventoryCardFilter);
        LblInventoryZone->setObjectName("LblInventoryZone");

        inventoryFilterGrid->addWidget(LblInventoryZone, 0, 3, 1, 1);

        LblInventoryType = new QLabel(InventoryCardFilter);
        LblInventoryType->setObjectName("LblInventoryType");

        inventoryFilterGrid->addWidget(LblInventoryType, 0, 1, 1, 1);


        gridLayout_3->addWidget(InventoryCardFilter, 0, 0, 1, 1);

        stacked_I->addWidget(inventory);
        ajouteri = new QWidget();
        ajouteri->setObjectName("ajouteri");
        PopupInventoryCard = new QFrame(ajouteri);
        PopupInventoryCard->setObjectName("PopupInventoryCard");
        PopupInventoryCard->setGeometry(QRect(170, 50, 831, 471));
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

        LblType_2 = new QLabel(PopupInventoryForm);
        LblType_2->setObjectName("LblType_2");

        inventoryFormGrid->addWidget(LblType_2, 1, 2, 1, 1);

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

        stacked_I->addWidget(ajouteri);
        modifieri = new QWidget();
        modifieri->setObjectName("modifieri");
        PopupInventoryCard_2 = new QFrame(modifieri);
        PopupInventoryCard_2->setObjectName("PopupInventoryCard_2");
        PopupInventoryCard_2->setGeometry(QRect(140, 50, 891, 501));
        PopupInventoryCard_2->setMinimumSize(QSize(760, 0));
        PopupInventoryCard_2->setFrameShape(QFrame::Shape::NoFrame);
        popupInventoryLayout_2 = new QVBoxLayout(PopupInventoryCard_2);
        popupInventoryLayout_2->setSpacing(12);
        popupInventoryLayout_2->setObjectName("popupInventoryLayout_2");
        popupInventoryLayout_2->setContentsMargins(18, 18, 18, 18);
        popupInventoryHeader_2 = new QHBoxLayout();
        popupInventoryHeader_2->setObjectName("popupInventoryHeader_2");
        PopupTitleInventory_2 = new QLabel(PopupInventoryCard_2);
        PopupTitleInventory_2->setObjectName("PopupTitleInventory_2");

        popupInventoryHeader_2->addWidget(PopupTitleInventory_2);

        popupInventoryHeaderSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupInventoryHeader_2->addItem(popupInventoryHeaderSpacer_2);

        BtnPopupCancelInventory_2 = new QToolButton(PopupInventoryCard_2);
        BtnPopupCancelInventory_2->setObjectName("BtnPopupCancelInventory_2");

        popupInventoryHeader_2->addWidget(BtnPopupCancelInventory_2);


        popupInventoryLayout_2->addLayout(popupInventoryHeader_2);

        PopupInventoryForm_2 = new QFrame(PopupInventoryCard_2);
        PopupInventoryForm_2->setObjectName("PopupInventoryForm_2");
        PopupInventoryForm_2->setFrameShape(QFrame::Shape::NoFrame);
        inventoryFormGrid_2 = new QGridLayout(PopupInventoryForm_2);
        inventoryFormGrid_2->setObjectName("inventoryFormGrid_2");
        inventoryFormGrid_2->setHorizontalSpacing(12);
        inventoryFormGrid_2->setVerticalSpacing(10);
        LblIdProduct_2 = new QLabel(PopupInventoryForm_2);
        LblIdProduct_2->setObjectName("LblIdProduct_2");

        inventoryFormGrid_2->addWidget(LblIdProduct_2, 0, 0, 1, 1);

        IdProduct_2 = new QLineEdit(PopupInventoryForm_2);
        IdProduct_2->setObjectName("IdProduct_2");

        inventoryFormGrid_2->addWidget(IdProduct_2, 0, 1, 1, 1);

        LblName_2 = new QLabel(PopupInventoryForm_2);
        LblName_2->setObjectName("LblName_2");

        inventoryFormGrid_2->addWidget(LblName_2, 0, 2, 1, 1);

        Name_2 = new QLineEdit(PopupInventoryForm_2);
        Name_2->setObjectName("Name_2");

        inventoryFormGrid_2->addWidget(Name_2, 0, 3, 1, 1);

        LblSku_2 = new QLabel(PopupInventoryForm_2);
        LblSku_2->setObjectName("LblSku_2");

        inventoryFormGrid_2->addWidget(LblSku_2, 1, 0, 1, 1);

        Sku_2 = new QLineEdit(PopupInventoryForm_2);
        Sku_2->setObjectName("Sku_2");

        inventoryFormGrid_2->addWidget(Sku_2, 1, 1, 1, 1);

        LblType_3 = new QLabel(PopupInventoryForm_2);
        LblType_3->setObjectName("LblType_3");

        inventoryFormGrid_2->addWidget(LblType_3, 1, 2, 1, 1);

        Type_2 = new QComboBox(PopupInventoryForm_2);
        Type_2->setObjectName("Type_2");

        inventoryFormGrid_2->addWidget(Type_2, 1, 3, 1, 1);

        LblQtAv_2 = new QLabel(PopupInventoryForm_2);
        LblQtAv_2->setObjectName("LblQtAv_2");

        inventoryFormGrid_2->addWidget(LblQtAv_2, 2, 0, 1, 1);

        QtAv_2 = new QSpinBox(PopupInventoryForm_2);
        QtAv_2->setObjectName("QtAv_2");
        QtAv_2->setMinimum(0);
        QtAv_2->setMaximum(10000);

        inventoryFormGrid_2->addWidget(QtAv_2, 2, 1, 1, 1);

        LblQtRs_2 = new QLabel(PopupInventoryForm_2);
        LblQtRs_2->setObjectName("LblQtRs_2");

        inventoryFormGrid_2->addWidget(LblQtRs_2, 2, 2, 1, 1);

        QtRs_2 = new QSpinBox(PopupInventoryForm_2);
        QtRs_2->setObjectName("QtRs_2");
        QtRs_2->setMinimum(0);
        QtRs_2->setMaximum(10000);

        inventoryFormGrid_2->addWidget(QtRs_2, 2, 3, 1, 1);

        LblThreshold_2 = new QLabel(PopupInventoryForm_2);
        LblThreshold_2->setObjectName("LblThreshold_2");

        inventoryFormGrid_2->addWidget(LblThreshold_2, 3, 0, 1, 1);

        Threshold_2 = new QSpinBox(PopupInventoryForm_2);
        Threshold_2->setObjectName("Threshold_2");
        Threshold_2->setMinimum(0);
        Threshold_2->setMaximum(10000);

        inventoryFormGrid_2->addWidget(Threshold_2, 3, 1, 1, 1);

        LblUnit_2 = new QLabel(PopupInventoryForm_2);
        LblUnit_2->setObjectName("LblUnit_2");

        inventoryFormGrid_2->addWidget(LblUnit_2, 3, 2, 1, 1);

        Unit_2 = new QComboBox(PopupInventoryForm_2);
        Unit_2->setObjectName("Unit_2");

        inventoryFormGrid_2->addWidget(Unit_2, 3, 3, 1, 1);

        LblPrice_2 = new QLabel(PopupInventoryForm_2);
        LblPrice_2->setObjectName("LblPrice_2");

        inventoryFormGrid_2->addWidget(LblPrice_2, 4, 0, 1, 1);

        Price_2 = new QDoubleSpinBox(PopupInventoryForm_2);
        Price_2->setObjectName("Price_2");
        Price_2->setDecimals(2);
        Price_2->setMinimum(0.000000000000000);
        Price_2->setMaximum(100000.000000000000000);

        inventoryFormGrid_2->addWidget(Price_2, 4, 1, 1, 1);

        LblStatus_2 = new QLabel(PopupInventoryForm_2);
        LblStatus_2->setObjectName("LblStatus_2");

        inventoryFormGrid_2->addWidget(LblStatus_2, 4, 2, 1, 1);

        Status_2 = new QComboBox(PopupInventoryForm_2);
        Status_2->setObjectName("Status_2");

        inventoryFormGrid_2->addWidget(Status_2, 4, 3, 1, 1);

        LblZone_2 = new QLabel(PopupInventoryForm_2);
        LblZone_2->setObjectName("LblZone_2");

        inventoryFormGrid_2->addWidget(LblZone_2, 5, 0, 1, 1);

        Zone_2 = new QComboBox(PopupInventoryForm_2);
        Zone_2->setObjectName("Zone_2");

        inventoryFormGrid_2->addWidget(Zone_2, 5, 1, 1, 1);

        LblShelf_2 = new QLabel(PopupInventoryForm_2);
        LblShelf_2->setObjectName("LblShelf_2");

        inventoryFormGrid_2->addWidget(LblShelf_2, 5, 2, 1, 1);

        Shelf_2 = new QComboBox(PopupInventoryForm_2);
        Shelf_2->setObjectName("Shelf_2");

        inventoryFormGrid_2->addWidget(Shelf_2, 5, 3, 1, 1);


        popupInventoryLayout_2->addWidget(PopupInventoryForm_2);

        popupInventoryActions_2 = new QHBoxLayout();
        popupInventoryActions_2->setObjectName("popupInventoryActions_2");
        popupInventoryActionsLeft_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupInventoryActions_2->addItem(popupInventoryActionsLeft_2);

        BtnPopupSaveInventory_2 = new QPushButton(PopupInventoryCard_2);
        BtnPopupSaveInventory_2->setObjectName("BtnPopupSaveInventory_2");

        popupInventoryActions_2->addWidget(BtnPopupSaveInventory_2);

        BtnPopupResetInventory_2 = new QPushButton(PopupInventoryCard_2);
        BtnPopupResetInventory_2->setObjectName("BtnPopupResetInventory_2");

        popupInventoryActions_2->addWidget(BtnPopupResetInventory_2);


        popupInventoryLayout_2->addLayout(popupInventoryActions_2);

        stacked_I->addWidget(modifieri);
        stati = new QWidget();
        stati->setObjectName("stati");
        stat_pub_6 = new QLabel(stati);
        stat_pub_6->setObjectName("stat_pub_6");
        stat_pub_6->setGeometry(QRect(180, 70, 1021, 381));
        retour_stat_7 = new QPushButton(stati);
        retour_stat_7->setObjectName("retour_stat_7");
        retour_stat_7->setGeometry(QRect(60, 520, 1071, 41));
        stacked_I->addWidget(stati);
        afficheri = new QWidget();
        afficheri->setObjectName("afficheri");
        stat_pub_5 = new QLabel(afficheri);
        stat_pub_5->setObjectName("stat_pub_5");
        stat_pub_5->setGeometry(QRect(170, 70, 1021, 381));
        retour_stat_6 = new QPushButton(afficheri);
        retour_stat_6->setObjectName("retour_stat_6");
        retour_stat_6->setGeometry(QRect(90, 530, 1101, 41));
        stacked_I->addWidget(afficheri);

        verticalLayoutPage1->addWidget(stacked_I);

        stackedWidget->addWidget(pageInventaire);
        pagePublication = new QWidget();
        pagePublication->setObjectName("pagePublication");
        verticalLayoutPubRoot = new QVBoxLayout(pagePublication);
        verticalLayoutPubRoot->setObjectName("verticalLayoutPubRoot");
        stack_pub = new QStackedWidget(pagePublication);
        stack_pub->setObjectName("stack_pub");
        page_pub_list = new QWidget();
        page_pub_list->setObjectName("page_pub_list");
        verticalLayoutPubList = new QVBoxLayout(page_pub_list);
        verticalLayoutPubList->setSpacing(12);
        verticalLayoutPubList->setObjectName("verticalLayoutPubList");
        tablePublication = new QTableWidget(page_pub_list);
        if (tablePublication->columnCount() < 8)
            tablePublication->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(1, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(2, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(3, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(4, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(5, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(6, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(7, __qtablewidgetitem63);
        if (tablePublication->rowCount() < 9)
            tablePublication->setRowCount(9);
        tablePublication->setObjectName("tablePublication");
        tablePublication->setMinimumSize(QSize(0, 280));
        tablePublication->setRowCount(9);
        tablePublication->setColumnCount(8);

        verticalLayoutPubList->addWidget(tablePublication);

        lineSearchPub = new QLineEdit(page_pub_list);
        lineSearchPub->setObjectName("lineSearchPub");

        verticalLayoutPubList->addWidget(lineSearchPub);

        gridLayoutPubFilters = new QGridLayout();
        gridLayoutPubFilters->setObjectName("gridLayoutPubFilters");
        gridLayoutPubFilters->setHorizontalSpacing(14);
        gridLayoutPubFilters->setVerticalSpacing(10);
        btnReinitialiserPub = new QPushButton(page_pub_list);
        btnReinitialiserPub->setObjectName("btnReinitialiserPub");

        gridLayoutPubFilters->addWidget(btnReinitialiserPub, 2, 1, 1, 1);

        lblCategoriePub = new QLabel(page_pub_list);
        lblCategoriePub->setObjectName("lblCategoriePub");

        gridLayoutPubFilters->addWidget(lblCategoriePub, 0, 0, 1, 1);

        dateDuPub = new QDateEdit(page_pub_list);
        dateDuPub->setObjectName("dateDuPub");
        dateDuPub->setCalendarPopup(true);
        dateDuPub->setDate(QDate(2000, 1, 1));

        gridLayoutPubFilters->addWidget(dateDuPub, 1, 1, 1, 1);

        comboCategoriePub = new QComboBox(page_pub_list);
        comboCategoriePub->addItem(QString());
        comboCategoriePub->addItem(QString());
        comboCategoriePub->addItem(QString());
        comboCategoriePub->setObjectName("comboCategoriePub");

        gridLayoutPubFilters->addWidget(comboCategoriePub, 0, 1, 1, 1);

        lblPeriodeDuPub = new QLabel(page_pub_list);
        lblPeriodeDuPub->setObjectName("lblPeriodeDuPub");

        gridLayoutPubFilters->addWidget(lblPeriodeDuPub, 1, 0, 1, 1);

        btnAppliquerPub = new QPushButton(page_pub_list);
        btnAppliquerPub->setObjectName("btnAppliquerPub");

        gridLayoutPubFilters->addWidget(btnAppliquerPub, 2, 0, 1, 1);


        verticalLayoutPubList->addLayout(gridLayoutPubFilters);

        horizontalLayoutPubBottom = new QHBoxLayout();
        horizontalLayoutPubBottom->setSpacing(12);
        horizontalLayoutPubBottom->setObjectName("horizontalLayoutPubBottom");
        btnVoirStatistiquesPub = new QPushButton(page_pub_list);
        btnVoirStatistiquesPub->setObjectName("btnVoirStatistiquesPub");

        horizontalLayoutPubBottom->addWidget(btnVoirStatistiquesPub);

        horizontalSpacerPubBottom = new QSpacerItem(360, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutPubBottom->addItem(horizontalSpacerPubBottom);

        btnAjouterPub = new QPushButton(page_pub_list);
        btnAjouterPub->setObjectName("btnAjouterPub");

        horizontalLayoutPubBottom->addWidget(btnAjouterPub);

        btnModifierPub = new QPushButton(page_pub_list);
        btnModifierPub->setObjectName("btnModifierPub");

        horizontalLayoutPubBottom->addWidget(btnModifierPub);

        btnSupprimerPub = new QPushButton(page_pub_list);
        btnSupprimerPub->setObjectName("btnSupprimerPub");

        horizontalLayoutPubBottom->addWidget(btnSupprimerPub);

        btnExporterPub = new QPushButton(page_pub_list);
        btnExporterPub->setObjectName("btnExporterPub");

        horizontalLayoutPubBottom->addWidget(btnExporterPub);


        verticalLayoutPubList->addLayout(horizontalLayoutPubBottom);

        stack_pub->addWidget(page_pub_list);
        page_pub_add = new QWidget();
        page_pub_add->setObjectName("page_pub_add");
        gridLayoutPubAdd = new QGridLayout(page_pub_add);
        gridLayoutPubAdd->setObjectName("gridLayoutPubAdd");
        gridLayoutPubAdd->setHorizontalSpacing(40);
        gridLayoutPubAdd->setVerticalSpacing(20);
        gridLayoutPubAdd->setContentsMargins(60, 28, 60, 28);
        hLayoutAddButtons = new QHBoxLayout();
        hLayoutAddButtons->setObjectName("hLayoutAddButtons");
        spacerAddButtons = new QSpacerItem(480, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutAddButtons->addItem(spacerAddButtons);

        btnAddPub = new QPushButton(page_pub_add);
        btnAddPub->setObjectName("btnAddPub");

        hLayoutAddButtons->addWidget(btnAddPub);

        btnRetourAddPub = new QPushButton(page_pub_add);
        btnRetourAddPub->setObjectName("btnRetourAddPub");

        hLayoutAddButtons->addWidget(btnRetourAddPub);


        gridLayoutPubAdd->addLayout(hLayoutAddButtons, 6, 0, 1, 4);

        lineResumeAdd = new QLineEdit(page_pub_add);
        lineResumeAdd->setObjectName("lineResumeAdd");

        gridLayoutPubAdd->addWidget(lineResumeAdd, 1, 3, 1, 1);

        lblTypeBrevetAdd = new QLabel(page_pub_add);
        lblTypeBrevetAdd->setObjectName("lblTypeBrevetAdd");

        gridLayoutPubAdd->addWidget(lblTypeBrevetAdd, 2, 0, 1, 1);

        comboTypeBrevetAdd = new QComboBox(page_pub_add);
        comboTypeBrevetAdd->setObjectName("comboTypeBrevetAdd");

        gridLayoutPubAdd->addWidget(comboTypeBrevetAdd, 2, 1, 1, 1);

        lblDomaineAdd = new QLabel(page_pub_add);
        lblDomaineAdd->setObjectName("lblDomaineAdd");

        gridLayoutPubAdd->addWidget(lblDomaineAdd, 1, 0, 1, 1);

        lblStatusBrevetAdd = new QLabel(page_pub_add);
        lblStatusBrevetAdd->setObjectName("lblStatusBrevetAdd");

        gridLayoutPubAdd->addWidget(lblStatusBrevetAdd, 5, 0, 1, 1);

        lblResumeAdd = new QLabel(page_pub_add);
        lblResumeAdd->setObjectName("lblResumeAdd");

        gridLayoutPubAdd->addWidget(lblResumeAdd, 1, 2, 1, 1);

        dateDepotAdd = new QDateEdit(page_pub_add);
        dateDepotAdd->setObjectName("dateDepotAdd");
        dateDepotAdd->setCalendarPopup(true);
        dateDepotAdd->setDate(QDate(2000, 1, 1));

        gridLayoutPubAdd->addWidget(dateDepotAdd, 4, 1, 1, 1);

        lineNumeroBrevetAdd = new QLineEdit(page_pub_add);
        lineNumeroBrevetAdd->setObjectName("lineNumeroBrevetAdd");

        gridLayoutPubAdd->addWidget(lineNumeroBrevetAdd, 3, 1, 1, 1);

        lblDateDepotAdd = new QLabel(page_pub_add);
        lblDateDepotAdd->setObjectName("lblDateDepotAdd");

        gridLayoutPubAdd->addWidget(lblDateDepotAdd, 4, 0, 1, 1);

        lineTitreAdd = new QLineEdit(page_pub_add);
        lineTitreAdd->setObjectName("lineTitreAdd");

        gridLayoutPubAdd->addWidget(lineTitreAdd, 0, 1, 1, 1);

        comboStatusBrevetAdd = new QComboBox(page_pub_add);
        comboStatusBrevetAdd->setObjectName("comboStatusBrevetAdd");

        gridLayoutPubAdd->addWidget(comboStatusBrevetAdd, 5, 1, 1, 1);

        lblNumeroBrevetAdd = new QLabel(page_pub_add);
        lblNumeroBrevetAdd->setObjectName("lblNumeroBrevetAdd");

        gridLayoutPubAdd->addWidget(lblNumeroBrevetAdd, 3, 0, 1, 1);

        lineDomaineAdd = new QLineEdit(page_pub_add);
        lineDomaineAdd->setObjectName("lineDomaineAdd");

        gridLayoutPubAdd->addWidget(lineDomaineAdd, 1, 1, 1, 1);

        lineInventeursAdd = new QLineEdit(page_pub_add);
        lineInventeursAdd->setObjectName("lineInventeursAdd");

        gridLayoutPubAdd->addWidget(lineInventeursAdd, 0, 3, 1, 1);

        lblTitreAdd = new QLabel(page_pub_add);
        lblTitreAdd->setObjectName("lblTitreAdd");

        gridLayoutPubAdd->addWidget(lblTitreAdd, 0, 0, 1, 1);

        lblInventeursAdd = new QLabel(page_pub_add);
        lblInventeursAdd->setObjectName("lblInventeursAdd");

        gridLayoutPubAdd->addWidget(lblInventeursAdd, 0, 2, 1, 1);

        stack_pub->addWidget(page_pub_add);
        page_pub_edit = new QWidget();
        page_pub_edit->setObjectName("page_pub_edit");
        gridLayoutPubEdit = new QGridLayout(page_pub_edit);
        gridLayoutPubEdit->setObjectName("gridLayoutPubEdit");
        gridLayoutPubEdit->setHorizontalSpacing(40);
        gridLayoutPubEdit->setVerticalSpacing(20);
        gridLayoutPubEdit->setContentsMargins(60, 28, 60, 28);
        lblInventeursEdit = new QLabel(page_pub_edit);
        lblInventeursEdit->setObjectName("lblInventeursEdit");

        gridLayoutPubEdit->addWidget(lblInventeursEdit, 2, 2, 1, 1);

        lineTitreEdit = new QLineEdit(page_pub_edit);
        lineTitreEdit->setObjectName("lineTitreEdit");

        gridLayoutPubEdit->addWidget(lineTitreEdit, 0, 1, 1, 1);

        lblTypeBrevetEdit = new QLabel(page_pub_edit);
        lblTypeBrevetEdit->setObjectName("lblTypeBrevetEdit");

        gridLayoutPubEdit->addWidget(lblTypeBrevetEdit, 2, 0, 1, 1);

        lineResumeEdit = new QLineEdit(page_pub_edit);
        lineResumeEdit->setObjectName("lineResumeEdit");

        gridLayoutPubEdit->addWidget(lineResumeEdit, 3, 3, 1, 1);

        lblDomaineEdit = new QLabel(page_pub_edit);
        lblDomaineEdit->setObjectName("lblDomaineEdit");

        gridLayoutPubEdit->addWidget(lblDomaineEdit, 1, 0, 1, 1);

        comboTypeBrevetEdit = new QComboBox(page_pub_edit);
        comboTypeBrevetEdit->setObjectName("comboTypeBrevetEdit");

        gridLayoutPubEdit->addWidget(comboTypeBrevetEdit, 2, 1, 1, 1);

        lblResumeEdit = new QLabel(page_pub_edit);
        lblResumeEdit->setObjectName("lblResumeEdit");

        gridLayoutPubEdit->addWidget(lblResumeEdit, 3, 2, 1, 1);

        comboStatusBrevetEdit = new QComboBox(page_pub_edit);
        comboStatusBrevetEdit->setObjectName("comboStatusBrevetEdit");

        gridLayoutPubEdit->addWidget(comboStatusBrevetEdit, 1, 3, 1, 1);

        dateDepotEdit = new QDateEdit(page_pub_edit);
        dateDepotEdit->setObjectName("dateDepotEdit");
        dateDepotEdit->setCalendarPopup(true);
        dateDepotEdit->setDate(QDate(2000, 1, 1));

        gridLayoutPubEdit->addWidget(dateDepotEdit, 0, 3, 1, 1);

        hLayoutEditButtons = new QHBoxLayout();
        hLayoutEditButtons->setObjectName("hLayoutEditButtons");
        spacerEditButtons = new QSpacerItem(480, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutEditButtons->addItem(spacerEditButtons);

        btnConfirmEditPub = new QPushButton(page_pub_edit);
        btnConfirmEditPub->setObjectName("btnConfirmEditPub");

        hLayoutEditButtons->addWidget(btnConfirmEditPub);

        btnRetourEditPub = new QPushButton(page_pub_edit);
        btnRetourEditPub->setObjectName("btnRetourEditPub");

        hLayoutEditButtons->addWidget(btnRetourEditPub);


        gridLayoutPubEdit->addLayout(hLayoutEditButtons, 5, 0, 1, 4);

        lineInventeursEdit = new QLineEdit(page_pub_edit);
        lineInventeursEdit->setObjectName("lineInventeursEdit");

        gridLayoutPubEdit->addWidget(lineInventeursEdit, 2, 3, 1, 1);

        lineNumeroBrevetEdit = new QLineEdit(page_pub_edit);
        lineNumeroBrevetEdit->setObjectName("lineNumeroBrevetEdit");

        gridLayoutPubEdit->addWidget(lineNumeroBrevetEdit, 3, 1, 1, 1);

        lblDateDepotEdit = new QLabel(page_pub_edit);
        lblDateDepotEdit->setObjectName("lblDateDepotEdit");

        gridLayoutPubEdit->addWidget(lblDateDepotEdit, 0, 2, 1, 1);

        lblTitreEdit = new QLabel(page_pub_edit);
        lblTitreEdit->setObjectName("lblTitreEdit");

        gridLayoutPubEdit->addWidget(lblTitreEdit, 0, 0, 1, 1);

        lblStatusBrevetEdit = new QLabel(page_pub_edit);
        lblStatusBrevetEdit->setObjectName("lblStatusBrevetEdit");

        gridLayoutPubEdit->addWidget(lblStatusBrevetEdit, 1, 2, 1, 1);

        lineDomaineEdit = new QLineEdit(page_pub_edit);
        lineDomaineEdit->setObjectName("lineDomaineEdit");

        gridLayoutPubEdit->addWidget(lineDomaineEdit, 1, 1, 1, 1);

        lblNumeroBrevetEdit = new QLabel(page_pub_edit);
        lblNumeroBrevetEdit->setObjectName("lblNumeroBrevetEdit");

        gridLayoutPubEdit->addWidget(lblNumeroBrevetEdit, 3, 0, 1, 1);

        stack_pub->addWidget(page_pub_edit);
        page_pub_empty = new QWidget();
        page_pub_empty->setObjectName("page_pub_empty");
        verticalLayoutPubEmpty = new QVBoxLayout(page_pub_empty);
        verticalLayoutPubEmpty->setObjectName("verticalLayoutPubEmpty");
        stat_pub = new QLabel(page_pub_empty);
        stat_pub->setObjectName("stat_pub");

        verticalLayoutPubEmpty->addWidget(stat_pub);

        comboBox = new QComboBox(page_pub_empty);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayoutPubEmpty->addWidget(comboBox);

        retour_stat = new QPushButton(page_pub_empty);
        retour_stat->setObjectName("retour_stat");

        verticalLayoutPubEmpty->addWidget(retour_stat);

        stack_pub->addWidget(page_pub_empty);

        verticalLayoutPubRoot->addWidget(stack_pub);

        stackedWidget->addWidget(pagePublication);
        pageFinance = new QWidget();
        pageFinance->setObjectName("pageFinance");
        verticalLayoutPage3 = new QVBoxLayout(pageFinance);
        verticalLayoutPage3->setObjectName("verticalLayoutPage3");
        stacked_F = new QStackedWidget(pageFinance);
        stacked_F->setObjectName("stacked_F");
        finance = new QWidget();
        finance->setObjectName("finance");
        gridLayout = new QGridLayout(finance);
        gridLayout->setObjectName("gridLayout");
        CardFilter = new QFrame(finance);
        CardFilter->setObjectName("CardFilter");
        CardFilter->setFrameShape(QFrame::Shape::NoFrame);
        filterGrid = new QGridLayout(CardFilter);
        filterGrid->setObjectName("filterGrid");
        filterGrid->setHorizontalSpacing(12);
        filterGrid->setVerticalSpacing(10);
        filterGrid->setContentsMargins(16, 16, 16, 16);
        LblTo = new QLabel(CardFilter);
        LblTo->setObjectName("LblTo");
        LblTo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        filterGrid->addWidget(LblTo, 0, 3, 1, 1);

        DateFrom = new QDateEdit(CardFilter);
        DateFrom->setObjectName("DateFrom");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(true);
        DateFrom->setFont(font1);
        DateFrom->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        DateFrom->setAlignment(Qt::AlignmentFlag::AlignCenter);
        DateFrom->setCalendarPopup(true);

        filterGrid->addWidget(DateFrom, 1, 2, 1, 1);

        CbType = new QComboBox(CardFilter);
        CbType->addItem(QString());
        CbType->addItem(QString());
        CbType->addItem(QString());
        CbType->setObjectName("CbType");

        filterGrid->addWidget(CbType, 1, 0, 1, 1);

        LblFrom = new QLabel(CardFilter);
        LblFrom->setObjectName("LblFrom");
        LblFrom->setAlignment(Qt::AlignmentFlag::AlignCenter);

        filterGrid->addWidget(LblFrom, 0, 2, 1, 1);

        EdSearch = new QLineEdit(CardFilter);
        EdSearch->setObjectName("EdSearch");

        filterGrid->addWidget(EdSearch, 2, 0, 1, 2);

        LblType = new QLabel(CardFilter);
        LblType->setObjectName("LblType");
        QFont font2;
        font2.setPointSize(11);
        LblType->setFont(font2);

        filterGrid->addWidget(LblType, 0, 0, 1, 1);

        DateTo = new QDateEdit(CardFilter);
        DateTo->setObjectName("DateTo");
        DateTo->setFont(font1);
        DateTo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        DateTo->setAlignment(Qt::AlignmentFlag::AlignCenter);
        DateTo->setCalendarPopup(true);

        filterGrid->addWidget(DateTo, 1, 3, 1, 1);

        BtnReset = new QPushButton(CardFilter);
        BtnReset->setObjectName("BtnReset");

        filterGrid->addWidget(BtnReset, 2, 3, 1, 1);

        BtnApply = new QPushButton(CardFilter);
        BtnApply->setObjectName("BtnApply");

        filterGrid->addWidget(BtnApply, 2, 2, 1, 1);


        gridLayout->addWidget(CardFilter, 0, 0, 1, 1);

        CardTable = new QFrame(finance);
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
        if (TableFinance->columnCount() < 8)
            TableFinance->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(0, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(1, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(2, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(3, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(4, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(5, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(6, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(7, __qtablewidgetitem71);
        if (TableFinance->rowCount() < 3)
            TableFinance->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(0, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(1, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(2, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        TableFinance->setItem(0, 0, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        TableFinance->setItem(0, 1, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        TableFinance->setItem(0, 2, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        TableFinance->setItem(0, 3, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        TableFinance->setItem(0, 4, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        TableFinance->setItem(0, 5, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        TableFinance->setItem(0, 6, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        TableFinance->setItem(0, 7, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        TableFinance->setItem(1, 0, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        TableFinance->setItem(1, 1, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        TableFinance->setItem(1, 2, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        TableFinance->setItem(1, 3, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        TableFinance->setItem(1, 4, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        TableFinance->setItem(1, 5, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        TableFinance->setItem(1, 6, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        TableFinance->setItem(1, 7, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        TableFinance->setItem(2, 0, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        TableFinance->setItem(2, 1, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        TableFinance->setItem(2, 2, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        TableFinance->setItem(2, 3, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        TableFinance->setItem(2, 4, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        TableFinance->setItem(2, 5, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        TableFinance->setItem(2, 6, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        TableFinance->setItem(2, 7, __qtablewidgetitem98);
        TableFinance->setObjectName("TableFinance");
        TableFinance->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableFinance->setAlternatingRowColors(true);
        TableFinance->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableFinance->setShowGrid(false);
        TableFinance->setSortingEnabled(true);
        TableFinance->setCornerButtonEnabled(false);
        TableFinance->setRowCount(3);
        TableFinance->setColumnCount(8);

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

        BtnAdd_4 = new QPushButton(CardTable);
        BtnAdd_4->setObjectName("BtnAdd_4");

        tableActions->addWidget(BtnAdd_4);

        BtnExport = new QPushButton(CardTable);
        BtnExport->setObjectName("BtnExport");

        tableActions->addWidget(BtnExport);


        tableCardLayout->addLayout(tableActions);


        gridLayout->addWidget(CardTable, 1, 0, 1, 1);

        stacked_F->addWidget(finance);
        ajouterF = new QWidget();
        ajouterF->setObjectName("ajouterF");
        gridLayout_2 = new QGridLayout(ajouterF);
        gridLayout_2->setObjectName("gridLayout_2");
        OverlayFinance = new QFrame(ajouterF);
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
        LblAmount = new QLabel(PopupFinanceCard);
        LblAmount->setObjectName("LblAmount");

        popupFinanceGrid->addWidget(LblAmount, 1, 0, 1, 1);

        FormPayMode = new QComboBox(PopupFinanceCard);
        FormPayMode->addItem(QString());
        FormPayMode->addItem(QString());
        FormPayMode->addItem(QString());
        FormPayMode->addItem(QString());
        FormPayMode->addItem(QString());
        FormPayMode->addItem(QString());
        FormPayMode->setObjectName("FormPayMode");

        popupFinanceGrid->addWidget(FormPayMode, 3, 3, 1, 1);

        LblCat2 = new QLabel(PopupFinanceCard);
        LblCat2->setObjectName("LblCat2");

        popupFinanceGrid->addWidget(LblCat2, 1, 2, 1, 1);

        LblCode = new QLabel(PopupFinanceCard);
        LblCode->setObjectName("LblCode");

        popupFinanceGrid->addWidget(LblCode, 0, 0, 1, 1);

        FormDesc = new QLineEdit(PopupFinanceCard);
        FormDesc->setObjectName("FormDesc");

        popupFinanceGrid->addWidget(FormDesc, 2, 1, 1, 3);

        FormDate = new QDateEdit(PopupFinanceCard);
        FormDate->setObjectName("FormDate");
        FormDate->setCalendarPopup(true);

        popupFinanceGrid->addWidget(FormDate, 3, 1, 1, 1);

        LblDesc = new QLabel(PopupFinanceCard);
        LblDesc->setObjectName("LblDesc");

        popupFinanceGrid->addWidget(LblDesc, 2, 0, 1, 1);

        FormCreatedAt = new QDateEdit(PopupFinanceCard);
        FormCreatedAt->setObjectName("FormCreatedAt");
        FormCreatedAt->setEnabled(false);
        FormCreatedAt->setCalendarPopup(true);

        popupFinanceGrid->addWidget(FormCreatedAt, 4, 1, 1, 1);

        LblDate2 = new QLabel(PopupFinanceCard);
        LblDate2->setObjectName("LblDate2");

        popupFinanceGrid->addWidget(LblDate2, 3, 0, 1, 1);

        FormType = new QComboBox(PopupFinanceCard);
        FormType->addItem(QString());
        FormType->addItem(QString());
        FormType->setObjectName("FormType");

        popupFinanceGrid->addWidget(FormType, 0, 3, 1, 1);

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

        LblFType = new QLabel(PopupFinanceCard);
        LblFType->setObjectName("LblFType");

        popupFinanceGrid->addWidget(LblFType, 0, 2, 1, 1);

        LblCreated = new QLabel(PopupFinanceCard);
        LblCreated->setObjectName("LblCreated");

        popupFinanceGrid->addWidget(LblCreated, 4, 0, 1, 1);

        FormCode = new QLineEdit(PopupFinanceCard);
        FormCode->setObjectName("FormCode");

        popupFinanceGrid->addWidget(FormCode, 0, 1, 1, 1);

        LblPay = new QLabel(PopupFinanceCard);
        LblPay->setObjectName("LblPay");

        popupFinanceGrid->addWidget(LblPay, 3, 2, 1, 1);

        FormAmount = new QLineEdit(PopupFinanceCard);
        FormAmount->setObjectName("FormAmount");

        popupFinanceGrid->addWidget(FormAmount, 1, 1, 1, 1);

        FormCategory = new QLineEdit(PopupFinanceCard);
        FormCategory->setObjectName("FormCategory");
        FormCategory->setMaximumSize(QSize(150, 16777215));

        popupFinanceGrid->addWidget(FormCategory, 1, 3, 1, 1);


        popupFinanceCardLayout->addLayout(popupFinanceGrid);


        overlayFinanceLayout->addWidget(PopupFinanceCard);

        ovBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayFinanceLayout->addItem(ovBottom);


        gridLayout_2->addWidget(OverlayFinance, 0, 0, 1, 1);

        stacked_F->addWidget(ajouterF);
        modifierF = new QWidget();
        modifierF->setObjectName("modifierF");
        OverlayFinance_2 = new QFrame(modifierF);
        OverlayFinance_2->setObjectName("OverlayFinance_2");
        OverlayFinance_2->setGeometry(QRect(40, 10, 1041, 581));
        OverlayFinance_2->setFrameShape(QFrame::Shape::NoFrame);
        overlayFinanceLayout_2 = new QVBoxLayout(OverlayFinance_2);
        overlayFinanceLayout_2->setObjectName("overlayFinanceLayout_2");
        overlayFinanceLayout_2->setContentsMargins(0, 0, 0, 0);
        ovTop_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayFinanceLayout_2->addItem(ovTop_2);

        PopupFinanceCard_2 = new QFrame(OverlayFinance_2);
        PopupFinanceCard_2->setObjectName("PopupFinanceCard_2");
        PopupFinanceCard_2->setMinimumSize(QSize(760, 260));
        PopupFinanceCard_2->setMaximumSize(QSize(900, 400));
        PopupFinanceCard_2->setFrameShape(QFrame::Shape::NoFrame);
        popupFinanceCardLayout_2 = new QVBoxLayout(PopupFinanceCard_2);
        popupFinanceCardLayout_2->setSpacing(12);
        popupFinanceCardLayout_2->setObjectName("popupFinanceCardLayout_2");
        popupFinanceCardLayout_2->setContentsMargins(16, 16, 16, 16);
        PopupTitleFinance_2 = new QLabel(PopupFinanceCard_2);
        PopupTitleFinance_2->setObjectName("PopupTitleFinance_2");

        popupFinanceCardLayout_2->addWidget(PopupTitleFinance_2);

        popupFinanceGrid_2 = new QGridLayout();
        popupFinanceGrid_2->setObjectName("popupFinanceGrid_2");
        popupFinanceGrid_2->setHorizontalSpacing(12);
        popupFinanceGrid_2->setVerticalSpacing(10);
        FormDate_2 = new QDateEdit(PopupFinanceCard_2);
        FormDate_2->setObjectName("FormDate_2");
        FormDate_2->setCalendarPopup(true);

        popupFinanceGrid_2->addWidget(FormDate_2, 3, 1, 1, 1);

        FormPayMode_2 = new QComboBox(PopupFinanceCard_2);
        FormPayMode_2->addItem(QString());
        FormPayMode_2->addItem(QString());
        FormPayMode_2->addItem(QString());
        FormPayMode_2->addItem(QString());
        FormPayMode_2->addItem(QString());
        FormPayMode_2->addItem(QString());
        FormPayMode_2->setObjectName("FormPayMode_2");

        popupFinanceGrid_2->addWidget(FormPayMode_2, 3, 3, 1, 1);

        FormCategory_2 = new QLineEdit(PopupFinanceCard_2);
        FormCategory_2->setObjectName("FormCategory_2");
        FormCategory_2->setMaximumSize(QSize(150, 16777215));

        popupFinanceGrid_2->addWidget(FormCategory_2, 1, 3, 1, 1);

        LblCode_2 = new QLabel(PopupFinanceCard_2);
        LblCode_2->setObjectName("LblCode_2");

        popupFinanceGrid_2->addWidget(LblCode_2, 0, 0, 1, 1);

        FormType_2 = new QComboBox(PopupFinanceCard_2);
        FormType_2->addItem(QString());
        FormType_2->addItem(QString());
        FormType_2->setObjectName("FormType_2");

        popupFinanceGrid_2->addWidget(FormType_2, 0, 3, 1, 1);

        LblCreated_2 = new QLabel(PopupFinanceCard_2);
        LblCreated_2->setObjectName("LblCreated_2");

        popupFinanceGrid_2->addWidget(LblCreated_2, 4, 0, 1, 1);

        LblAmount_2 = new QLabel(PopupFinanceCard_2);
        LblAmount_2->setObjectName("LblAmount_2");

        popupFinanceGrid_2->addWidget(LblAmount_2, 1, 0, 1, 1);

        LblDesc_2 = new QLabel(PopupFinanceCard_2);
        LblDesc_2->setObjectName("LblDesc_2");

        popupFinanceGrid_2->addWidget(LblDesc_2, 2, 0, 1, 1);

        FormCode_2 = new QLineEdit(PopupFinanceCard_2);
        FormCode_2->setObjectName("FormCode_2");

        popupFinanceGrid_2->addWidget(FormCode_2, 0, 1, 1, 1);

        LblPay_2 = new QLabel(PopupFinanceCard_2);
        LblPay_2->setObjectName("LblPay_2");

        popupFinanceGrid_2->addWidget(LblPay_2, 3, 2, 1, 1);

        LblCat2_2 = new QLabel(PopupFinanceCard_2);
        LblCat2_2->setObjectName("LblCat2_2");

        popupFinanceGrid_2->addWidget(LblCat2_2, 1, 2, 1, 1);

        LblDate2_2 = new QLabel(PopupFinanceCard_2);
        LblDate2_2->setObjectName("LblDate2_2");

        popupFinanceGrid_2->addWidget(LblDate2_2, 3, 0, 1, 1);

        popupFinanceButtons_2 = new QHBoxLayout();
        popupFinanceButtons_2->setObjectName("popupFinanceButtons_2");
        pfSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupFinanceButtons_2->addItem(pfSpacer_2);

        BtnPopupSaveFinance_2 = new QPushButton(PopupFinanceCard_2);
        BtnPopupSaveFinance_2->setObjectName("BtnPopupSaveFinance_2");

        popupFinanceButtons_2->addWidget(BtnPopupSaveFinance_2);

        BtnPopupCancelFinance_2 = new QPushButton(PopupFinanceCard_2);
        BtnPopupCancelFinance_2->setObjectName("BtnPopupCancelFinance_2");

        popupFinanceButtons_2->addWidget(BtnPopupCancelFinance_2);


        popupFinanceGrid_2->addLayout(popupFinanceButtons_2, 4, 2, 1, 2);

        FormDesc_2 = new QLineEdit(PopupFinanceCard_2);
        FormDesc_2->setObjectName("FormDesc_2");

        popupFinanceGrid_2->addWidget(FormDesc_2, 2, 1, 1, 3);

        FormCreatedAt_2 = new QDateEdit(PopupFinanceCard_2);
        FormCreatedAt_2->setObjectName("FormCreatedAt_2");
        FormCreatedAt_2->setEnabled(false);
        FormCreatedAt_2->setCalendarPopup(true);

        popupFinanceGrid_2->addWidget(FormCreatedAt_2, 4, 1, 1, 1);

        LblFType_2 = new QLabel(PopupFinanceCard_2);
        LblFType_2->setObjectName("LblFType_2");

        popupFinanceGrid_2->addWidget(LblFType_2, 0, 2, 1, 1);

        FormAmount_2 = new QLineEdit(PopupFinanceCard_2);
        FormAmount_2->setObjectName("FormAmount_2");

        popupFinanceGrid_2->addWidget(FormAmount_2, 1, 1, 1, 1);


        popupFinanceCardLayout_2->addLayout(popupFinanceGrid_2);


        overlayFinanceLayout_2->addWidget(PopupFinanceCard_2);

        ovBottom_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayFinanceLayout_2->addItem(ovBottom_2);

        stacked_F->addWidget(modifierF);
        statsF = new QWidget();
        statsF->setObjectName("statsF");
        comboBox_3 = new QComboBox(statsF);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(20, 550, 531, 41));
        stat_pub_3 = new QLabel(statsF);
        stat_pub_3->setObjectName("stat_pub_3");
        stat_pub_3->setGeometry(QRect(10, 30, 1242, 451));
        retour_stat_4 = new QPushButton(statsF);
        retour_stat_4->setObjectName("retour_stat_4");
        retour_stat_4->setGeometry(QRect(670, 550, 561, 41));
        stacked_F->addWidget(statsF);
        afficherF = new QWidget();
        afficherF->setObjectName("afficherF");
        retour_stat_5 = new QPushButton(afficherF);
        retour_stat_5->setObjectName("retour_stat_5");
        retour_stat_5->setGeometry(QRect(110, 520, 1041, 41));
        stat_pub_4 = new QLabel(afficherF);
        stat_pub_4->setObjectName("stat_pub_4");
        stat_pub_4->setGeometry(QRect(53, 47, 1021, 381));
        stacked_F->addWidget(afficherF);

        verticalLayoutPage3->addWidget(stacked_F);

        stackedWidget->addWidget(pageFinance);
        pageLaboratoires = new QWidget();
        pageLaboratoires->setObjectName("pageLaboratoires");
        verticalLayoutPage4 = new QVBoxLayout(pageLaboratoires);
        verticalLayoutPage4->setObjectName("verticalLayoutPage4");
        stacked_L = new QStackedWidget(pageLaboratoires);
        stacked_L->setObjectName("stacked_L");
        Lab = new QWidget();
        Lab->setObjectName("Lab");
        gridLayout_6 = new QGridLayout(Lab);
        gridLayout_6->setObjectName("gridLayout_6");
        TableLabs_2 = new QTableWidget(Lab);
        if (TableLabs_2->columnCount() < 9)
            TableLabs_2->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(0, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(1, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(2, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(3, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(4, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(5, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(6, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(7, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(8, __qtablewidgetitem107);
        if (TableLabs_2->rowCount() < 4)
            TableLabs_2->setRowCount(4);
        TableLabs_2->setObjectName("TableLabs_2");
        TableLabs_2->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableLabs_2->setAlternatingRowColors(true);
        TableLabs_2->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableLabs_2->setShowGrid(false);
        TableLabs_2->setSortingEnabled(true);
        TableLabs_2->setCornerButtonEnabled(false);

        gridLayout_6->addWidget(TableLabs_2, 0, 0, 2, 4);

        btnExporterPub_2 = new QPushButton(Lab);
        btnExporterPub_2->setObjectName("btnExporterPub_2");

        gridLayout_6->addWidget(btnExporterPub_2, 0, 4, 1, 1);

        btnVoirStatistiquesPub_2 = new QPushButton(Lab);
        btnVoirStatistiquesPub_2->setObjectName("btnVoirStatistiquesPub_2");

        gridLayout_6->addWidget(btnVoirStatistiquesPub_2, 1, 4, 1, 1);

        btnAjouterPub_4 = new QPushButton(Lab);
        btnAjouterPub_4->setObjectName("btnAjouterPub_4");

        gridLayout_6->addWidget(btnAjouterPub_4, 2, 4, 1, 1);

        btnAjouterPub_3 = new QPushButton(Lab);
        btnAjouterPub_3->setObjectName("btnAjouterPub_3");

        gridLayout_6->addWidget(btnAjouterPub_3, 3, 0, 1, 1);

        btnAjouterPub_2 = new QPushButton(Lab);
        btnAjouterPub_2->setObjectName("btnAjouterPub_2");

        gridLayout_6->addWidget(btnAjouterPub_2, 3, 1, 1, 1);

        btnModifierPub_2 = new QPushButton(Lab);
        btnModifierPub_2->setObjectName("btnModifierPub_2");

        gridLayout_6->addWidget(btnModifierPub_2, 3, 2, 1, 1);

        btnSupprimerPub_2 = new QPushButton(Lab);
        btnSupprimerPub_2->setObjectName("btnSupprimerPub_2");

        gridLayout_6->addWidget(btnSupprimerPub_2, 3, 3, 1, 1);

        LabsCardFilter_2 = new QFrame(Lab);
        LabsCardFilter_2->setObjectName("LabsCardFilter_2");
        LabsCardFilter_2->setFrameShape(QFrame::Shape::NoFrame);
        gridLayout_5 = new QGridLayout(LabsCardFilter_2);
        gridLayout_5->setObjectName("gridLayout_5");
        LblLabsSearch_2 = new QLabel(LabsCardFilter_2);
        LblLabsSearch_2->setObjectName("LblLabsSearch_2");

        gridLayout_5->addWidget(LblLabsSearch_2, 0, 0, 1, 1);

        LblLabsSpec_2 = new QLabel(LabsCardFilter_2);
        LblLabsSpec_2->setObjectName("LblLabsSpec_2");

        gridLayout_5->addWidget(LblLabsSpec_2, 0, 1, 1, 1);

        LblLabsCap_2 = new QLabel(LabsCardFilter_2);
        LblLabsCap_2->setObjectName("LblLabsCap_2");

        gridLayout_5->addWidget(LblLabsCap_2, 0, 2, 1, 1);

        btnAppliquerPub_3 = new QPushButton(LabsCardFilter_2);
        btnAppliquerPub_3->setObjectName("btnAppliquerPub_3");

        gridLayout_5->addWidget(btnAppliquerPub_3, 0, 3, 1, 1);

        LabsSearch_2 = new QLineEdit(LabsCardFilter_2);
        LabsSearch_2->setObjectName("LabsSearch_2");

        gridLayout_5->addWidget(LabsSearch_2, 1, 0, 1, 1);

        LabsSpec_2 = new QComboBox(LabsCardFilter_2);
        LabsSpec_2->addItem(QString());
        LabsSpec_2->addItem(QString());
        LabsSpec_2->addItem(QString());
        LabsSpec_2->setObjectName("LabsSpec_2");

        gridLayout_5->addWidget(LabsSpec_2, 1, 1, 1, 1);

        LabsCap_2 = new QComboBox(LabsCardFilter_2);
        LabsCap_2->addItem(QString());
        LabsCap_2->addItem(QString());
        LabsCap_2->addItem(QString());
        LabsCap_2->setObjectName("LabsCap_2");

        gridLayout_5->addWidget(LabsCap_2, 1, 2, 1, 1);

        btnReinitialiserPub_3 = new QPushButton(LabsCardFilter_2);
        btnReinitialiserPub_3->setObjectName("btnReinitialiserPub_3");

        gridLayout_5->addWidget(btnReinitialiserPub_3, 1, 3, 1, 1);


        gridLayout_6->addWidget(LabsCardFilter_2, 2, 0, 1, 4);

        stacked_L->addWidget(Lab);
        modifierL = new QWidget();
        modifierL->setObjectName("modifierL");
        PopupLabsCard_4 = new QFrame(modifierL);
        PopupLabsCard_4->setObjectName("PopupLabsCard_4");
        PopupLabsCard_4->setGeometry(QRect(10, 10, 1191, 581));
        PopupLabsCard_4->setMinimumSize(QSize(760, 0));
        PopupLabsCard_4->setFrameShape(QFrame::Shape::NoFrame);
        PopupLabsForm_5 = new QFrame(PopupLabsCard_4);
        PopupLabsForm_5->setObjectName("PopupLabsForm_5");
        PopupLabsForm_5->setGeometry(QRect(100, 170, 1025, 250));
        PopupLabsForm_5->setFrameShape(QFrame::Shape::NoFrame);
        LabLocation_5 = new QLineEdit(PopupLabsForm_5);
        LabLocation_5->setObjectName("LabLocation_5");
        LabLocation_5->setGeometry(QRect(102, 79, 341, 41));
        LabResponsible_5 = new QLineEdit(PopupLabsForm_5);
        LabResponsible_5->setObjectName("LabResponsible_5");
        LabResponsible_5->setGeometry(QRect(677, 26, 301, 41));
        LabSpec_5 = new QComboBox(PopupLabsForm_5);
        LabSpec_5->setObjectName("LabSpec_5");
        LabSpec_5->setGeometry(QRect(102, 132, 341, 41));
        LblLabCap_5 = new QLabel(PopupLabsForm_5);
        LblLabCap_5->setObjectName("LblLabCap_5");
        LblLabCap_5->setGeometry(QRect(581, 132, 58, 20));
        LblLabLoc_5 = new QLabel(PopupLabsForm_5);
        LblLabLoc_5->setObjectName("LblLabLoc_5");
        LblLabLoc_5->setGeometry(QRect(11, 79, 79, 20));
        LblLabName_5 = new QLabel(PopupLabsForm_5);
        LblLabName_5->setObjectName("LblLabName_5");
        LblLabName_5->setGeometry(QRect(11, 26, 67, 20));
        LblLabNum_5 = new QLabel(PopupLabsForm_5);
        LblLabNum_5->setObjectName("LblLabNum_5");
        LblLabNum_5->setGeometry(QRect(581, 79, 54, 20));
        LabName_5 = new QLineEdit(PopupLabsForm_5);
        LabName_5->setObjectName("LabName_5");
        LabName_5->setGeometry(QRect(102, 26, 341, 31));
        LabNumber_5 = new QLineEdit(PopupLabsForm_5);
        LabNumber_5->setObjectName("LabNumber_5");
        LabNumber_5->setGeometry(QRect(677, 79, 301, 41));
        LblLabResp_5 = new QLabel(PopupLabsForm_5);
        LblLabResp_5->setObjectName("LblLabResp_5");
        LblLabResp_5->setGeometry(QRect(581, 26, 84, 20));
        LblLabSpec_5 = new QLabel(PopupLabsForm_5);
        LblLabSpec_5->setObjectName("LblLabSpec_5");
        LblLabSpec_5->setGeometry(QRect(11, 132, 65, 20));
        LabCap_5 = new QComboBox(PopupLabsForm_5);
        LabCap_5->setObjectName("LabCap_5");
        LabCap_5->setGeometry(QRect(677, 132, 301, 41));
        layoutWidget = new QWidget(PopupLabsCard_4);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(140, 30, 921, 71));
        popupLabsHeader_5 = new QHBoxLayout(layoutWidget);
        popupLabsHeader_5->setObjectName("popupLabsHeader_5");
        popupLabsHeader_5->setContentsMargins(0, 0, 0, 0);
        PopupTitleLabs_5 = new QLabel(layoutWidget);
        PopupTitleLabs_5->setObjectName("PopupTitleLabs_5");

        popupLabsHeader_5->addWidget(PopupTitleLabs_5);

        popupLabsHeaderSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupLabsHeader_5->addItem(popupLabsHeaderSpacer_5);

        BtnPopupCancelLabs_5 = new QToolButton(layoutWidget);
        BtnPopupCancelLabs_5->setObjectName("BtnPopupCancelLabs_5");

        popupLabsHeader_5->addWidget(BtnPopupCancelLabs_5);

        BtnPopupResetLabs_5 = new QPushButton(PopupLabsCard_4);
        BtnPopupResetLabs_5->setObjectName("BtnPopupResetLabs_5");
        BtnPopupResetLabs_5->setEnabled(true);
        BtnPopupResetLabs_5->setGeometry(QRect(667, 470, 150, 45));
        BtnPopupSaveLabs_5 = new QPushButton(PopupLabsCard_4);
        BtnPopupSaveLabs_5->setObjectName("BtnPopupSaveLabs_5");
        BtnPopupSaveLabs_5->setGeometry(QRect(400, 470, 150, 45));
        stacked_L->addWidget(modifierL);
        ajouterL = new QWidget();
        ajouterL->setObjectName("ajouterL");
        PopupLabsCard_3 = new QFrame(ajouterL);
        PopupLabsCard_3->setObjectName("PopupLabsCard_3");
        PopupLabsCard_3->setGeometry(QRect(0, 0, 1191, 591));
        PopupLabsCard_3->setMinimumSize(QSize(760, 0));
        PopupLabsCard_3->setFrameShape(QFrame::Shape::NoFrame);
        PopupLabsForm_3 = new QFrame(PopupLabsCard_3);
        PopupLabsForm_3->setObjectName("PopupLabsForm_3");
        PopupLabsForm_3->setGeometry(QRect(100, 170, 1025, 250));
        PopupLabsForm_3->setFrameShape(QFrame::Shape::NoFrame);
        LabLocation_3 = new QLineEdit(PopupLabsForm_3);
        LabLocation_3->setObjectName("LabLocation_3");
        LabLocation_3->setGeometry(QRect(102, 79, 341, 41));
        LabResponsible_3 = new QLineEdit(PopupLabsForm_3);
        LabResponsible_3->setObjectName("LabResponsible_3");
        LabResponsible_3->setGeometry(QRect(677, 26, 301, 41));
        LabSpec_3 = new QComboBox(PopupLabsForm_3);
        LabSpec_3->setObjectName("LabSpec_3");
        LabSpec_3->setGeometry(QRect(102, 132, 341, 41));
        LblLabCap_3 = new QLabel(PopupLabsForm_3);
        LblLabCap_3->setObjectName("LblLabCap_3");
        LblLabCap_3->setGeometry(QRect(581, 132, 58, 20));
        LblLabLoc_3 = new QLabel(PopupLabsForm_3);
        LblLabLoc_3->setObjectName("LblLabLoc_3");
        LblLabLoc_3->setGeometry(QRect(11, 79, 79, 20));
        LblLabName_3 = new QLabel(PopupLabsForm_3);
        LblLabName_3->setObjectName("LblLabName_3");
        LblLabName_3->setGeometry(QRect(11, 26, 67, 20));
        LblLabNum_3 = new QLabel(PopupLabsForm_3);
        LblLabNum_3->setObjectName("LblLabNum_3");
        LblLabNum_3->setGeometry(QRect(581, 79, 54, 20));
        LabName_3 = new QLineEdit(PopupLabsForm_3);
        LabName_3->setObjectName("LabName_3");
        LabName_3->setGeometry(QRect(102, 26, 341, 31));
        LabNumber_3 = new QLineEdit(PopupLabsForm_3);
        LabNumber_3->setObjectName("LabNumber_3");
        LabNumber_3->setGeometry(QRect(677, 79, 301, 41));
        LblLabResp_3 = new QLabel(PopupLabsForm_3);
        LblLabResp_3->setObjectName("LblLabResp_3");
        LblLabResp_3->setGeometry(QRect(581, 26, 84, 20));
        LblLabSpec_3 = new QLabel(PopupLabsForm_3);
        LblLabSpec_3->setObjectName("LblLabSpec_3");
        LblLabSpec_3->setGeometry(QRect(11, 132, 65, 20));
        LabCap_3 = new QComboBox(PopupLabsForm_3);
        LabCap_3->setObjectName("LabCap_3");
        LabCap_3->setGeometry(QRect(677, 132, 301, 41));
        layoutWidget1 = new QWidget(PopupLabsCard_3);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(100, 20, 991, 61));
        popupLabsHeader_3 = new QHBoxLayout(layoutWidget1);
        popupLabsHeader_3->setObjectName("popupLabsHeader_3");
        popupLabsHeader_3->setContentsMargins(0, 0, 0, 0);
        PopupTitleLabs_3 = new QLabel(layoutWidget1);
        PopupTitleLabs_3->setObjectName("PopupTitleLabs_3");

        popupLabsHeader_3->addWidget(PopupTitleLabs_3);

        popupLabsHeaderSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupLabsHeader_3->addItem(popupLabsHeaderSpacer_3);

        BtnPopupCancelLabs_3 = new QToolButton(layoutWidget1);
        BtnPopupCancelLabs_3->setObjectName("BtnPopupCancelLabs_3");

        popupLabsHeader_3->addWidget(BtnPopupCancelLabs_3);

        BtnPopupSaveLabs_3 = new QPushButton(PopupLabsCard_3);
        BtnPopupSaveLabs_3->setObjectName("BtnPopupSaveLabs_3");
        BtnPopupSaveLabs_3->setGeometry(QRect(380, 490, 150, 45));
        BtnPopupResetLabs_3 = new QPushButton(PopupLabsCard_3);
        BtnPopupResetLabs_3->setObjectName("BtnPopupResetLabs_3");
        BtnPopupResetLabs_3->setGeometry(QRect(570, 490, 150, 45));
        stacked_L->addWidget(ajouterL);
        statL = new QWidget();
        statL->setObjectName("statL");
        retour_stat_2 = new QPushButton(statL);
        retour_stat_2->setObjectName("retour_stat_2");
        retour_stat_2->setGeometry(QRect(700, 520, 300, 41));
        comboBox_2 = new QComboBox(statL);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(30, 540, 531, 41));
        stat_pub_2 = new QLabel(statL);
        stat_pub_2->setObjectName("stat_pub_2");
        stat_pub_2->setGeometry(QRect(20, 20, 1242, 451));
        stacked_L->addWidget(statL);
        affichierL = new QWidget();
        affichierL->setObjectName("affichierL");
        retour_stat_3 = new QPushButton(affichierL);
        retour_stat_3->setObjectName("retour_stat_3");
        retour_stat_3->setGeometry(QRect(700, 520, 301, 41));
        stacked_L->addWidget(affichierL);
        mapsL = new QWidget();
        mapsL->setObjectName("mapsL");
        stat_pub_7 = new QLabel(mapsL);
        stat_pub_7->setObjectName("stat_pub_7");
        stat_pub_7->setGeometry(QRect(150, 60, 1021, 381));
        retour_stat_8 = new QPushButton(mapsL);
        retour_stat_8->setObjectName("retour_stat_8");
        retour_stat_8->setGeometry(QRect(150, 510, 971, 51));
        stacked_L->addWidget(mapsL);

        verticalLayoutPage4->addWidget(stacked_L);

        stackedWidget->addWidget(pageLaboratoires);
        pageProjets = new QWidget();
        pageProjets->setObjectName("pageProjets");
        verticalLayoutProjRoot = new QVBoxLayout(pageProjets);
        verticalLayoutProjRoot->setObjectName("verticalLayoutProjRoot");
        stack_proj = new QStackedWidget(pageProjets);
        stack_proj->setObjectName("stack_proj");
        page_proj_list = new QWidget();
        page_proj_list->setObjectName("page_proj_list");
        verticalLayoutProjList = new QVBoxLayout(page_proj_list);
        verticalLayoutProjList->setSpacing(12);
        verticalLayoutProjList->setObjectName("verticalLayoutProjList");
        lineSearchProj = new QLineEdit(page_proj_list);
        lineSearchProj->setObjectName("lineSearchProj");

        verticalLayoutProjList->addWidget(lineSearchProj);

        gridLayoutProjFilters = new QGridLayout();
        gridLayoutProjFilters->setObjectName("gridLayoutProjFilters");
        gridLayoutProjFilters->setHorizontalSpacing(14);
        gridLayoutProjFilters->setVerticalSpacing(10);
        dateDuProj = new QDateEdit(page_proj_list);
        dateDuProj->setObjectName("dateDuProj");
        dateDuProj->setCalendarPopup(true);
        dateDuProj->setDate(QDate(2000, 1, 1));

        gridLayoutProjFilters->addWidget(dateDuProj, 1, 1, 1, 1);

        comboCategorieProj = new QComboBox(page_proj_list);
        comboCategorieProj->addItem(QString());
        comboCategorieProj->addItem(QString());
        comboCategorieProj->setObjectName("comboCategorieProj");

        gridLayoutProjFilters->addWidget(comboCategorieProj, 0, 1, 1, 1);

        btnAppliquerProj = new QPushButton(page_proj_list);
        btnAppliquerProj->setObjectName("btnAppliquerProj");

        gridLayoutProjFilters->addWidget(btnAppliquerProj, 2, 0, 1, 1);

        lblCategorieProj = new QLabel(page_proj_list);
        lblCategorieProj->setObjectName("lblCategorieProj");

        gridLayoutProjFilters->addWidget(lblCategorieProj, 0, 0, 1, 1);

        lblPeriodeDuProj = new QLabel(page_proj_list);
        lblPeriodeDuProj->setObjectName("lblPeriodeDuProj");

        gridLayoutProjFilters->addWidget(lblPeriodeDuProj, 1, 0, 1, 1);


        verticalLayoutProjList->addLayout(gridLayoutProjFilters);

        tableProjets = new QTableWidget(page_proj_list);
        if (tableProjets->columnCount() < 8)
            tableProjets->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(0, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(1, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(2, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(3, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(4, __qtablewidgetitem112);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(5, __qtablewidgetitem113);
        QTableWidgetItem *__qtablewidgetitem114 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(6, __qtablewidgetitem114);
        QTableWidgetItem *__qtablewidgetitem115 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(7, __qtablewidgetitem115);
        if (tableProjets->rowCount() < 9)
            tableProjets->setRowCount(9);
        tableProjets->setObjectName("tableProjets");
        tableProjets->setMinimumSize(QSize(0, 280));
        tableProjets->setRowCount(9);
        tableProjets->setColumnCount(8);

        verticalLayoutProjList->addWidget(tableProjets);

        horizontalLayoutProjBottom = new QHBoxLayout();
        horizontalLayoutProjBottom->setSpacing(12);
        horizontalLayoutProjBottom->setObjectName("horizontalLayoutProjBottom");
        btnAjouterProj = new QPushButton(page_proj_list);
        btnAjouterProj->setObjectName("btnAjouterProj");

        horizontalLayoutProjBottom->addWidget(btnAjouterProj);

        btnModifierProj = new QPushButton(page_proj_list);
        btnModifierProj->setObjectName("btnModifierProj");

        horizontalLayoutProjBottom->addWidget(btnModifierProj);

        btnSupprimerProj = new QPushButton(page_proj_list);
        btnSupprimerProj->setObjectName("btnSupprimerProj");

        horizontalLayoutProjBottom->addWidget(btnSupprimerProj);

        horizontalSpacerProjBottom = new QSpacerItem(360, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutProjBottom->addItem(horizontalSpacerProjBottom);

        btnVoirStatistiquesProj = new QPushButton(page_proj_list);
        btnVoirStatistiquesProj->setObjectName("btnVoirStatistiquesProj");

        horizontalLayoutProjBottom->addWidget(btnVoirStatistiquesProj);


        verticalLayoutProjList->addLayout(horizontalLayoutProjBottom);

        stack_proj->addWidget(page_proj_list);
        page_proj_add = new QWidget();
        page_proj_add->setObjectName("page_proj_add");
        gridLayoutProjAdd = new QGridLayout(page_proj_add);
        gridLayoutProjAdd->setObjectName("gridLayoutProjAdd");
        gridLayoutProjAdd->setHorizontalSpacing(40);
        gridLayoutProjAdd->setVerticalSpacing(20);
        gridLayoutProjAdd->setContentsMargins(60, 28, 60, 28);
        hLayoutAddButtons1 = new QHBoxLayout();
        hLayoutAddButtons1->setObjectName("hLayoutAddButtons1");
        spacerAddButtons1 = new QSpacerItem(480, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutAddButtons1->addItem(spacerAddButtons1);

        btnAddProj = new QPushButton(page_proj_add);
        btnAddProj->setObjectName("btnAddProj");

        hLayoutAddButtons1->addWidget(btnAddProj);

        btnRetourAddProj = new QPushButton(page_proj_add);
        btnRetourAddProj->setObjectName("btnRetourAddProj");

        hLayoutAddButtons1->addWidget(btnRetourAddProj);


        gridLayoutProjAdd->addLayout(hLayoutAddButtons1, 6, 0, 1, 4);

        lineResumeAdd1 = new QLineEdit(page_proj_add);
        lineResumeAdd1->setObjectName("lineResumeAdd1");

        gridLayoutProjAdd->addWidget(lineResumeAdd1, 1, 3, 1, 1);

        lblTypeBrevetAdd1 = new QLabel(page_proj_add);
        lblTypeBrevetAdd1->setObjectName("lblTypeBrevetAdd1");

        gridLayoutProjAdd->addWidget(lblTypeBrevetAdd1, 2, 0, 1, 1);

        comboTypeBrevetAdd1 = new QComboBox(page_proj_add);
        comboTypeBrevetAdd1->setObjectName("comboTypeBrevetAdd1");

        gridLayoutProjAdd->addWidget(comboTypeBrevetAdd1, 2, 1, 1, 1);

        lblDomaineAdd1 = new QLabel(page_proj_add);
        lblDomaineAdd1->setObjectName("lblDomaineAdd1");

        gridLayoutProjAdd->addWidget(lblDomaineAdd1, 1, 0, 1, 1);

        lblStatusBrevetAdd1 = new QLabel(page_proj_add);
        lblStatusBrevetAdd1->setObjectName("lblStatusBrevetAdd1");

        gridLayoutProjAdd->addWidget(lblStatusBrevetAdd1, 5, 0, 1, 1);

        lblResumeAdd1 = new QLabel(page_proj_add);
        lblResumeAdd1->setObjectName("lblResumeAdd1");

        gridLayoutProjAdd->addWidget(lblResumeAdd1, 1, 2, 1, 1);

        dateDepotAdd1 = new QDateEdit(page_proj_add);
        dateDepotAdd1->setObjectName("dateDepotAdd1");
        dateDepotAdd1->setCalendarPopup(true);
        dateDepotAdd1->setDate(QDate(2000, 1, 1));

        gridLayoutProjAdd->addWidget(dateDepotAdd1, 4, 1, 1, 1);

        lineNumeroBrevetAdd1 = new QLineEdit(page_proj_add);
        lineNumeroBrevetAdd1->setObjectName("lineNumeroBrevetAdd1");

        gridLayoutProjAdd->addWidget(lineNumeroBrevetAdd1, 3, 1, 1, 1);

        lblDateDepotAdd1 = new QLabel(page_proj_add);
        lblDateDepotAdd1->setObjectName("lblDateDepotAdd1");

        gridLayoutProjAdd->addWidget(lblDateDepotAdd1, 4, 0, 1, 1);

        lineTitreAdd1 = new QLineEdit(page_proj_add);
        lineTitreAdd1->setObjectName("lineTitreAdd1");

        gridLayoutProjAdd->addWidget(lineTitreAdd1, 0, 1, 1, 1);

        comboStatusBrevetAdd1 = new QComboBox(page_proj_add);
        comboStatusBrevetAdd1->setObjectName("comboStatusBrevetAdd1");

        gridLayoutProjAdd->addWidget(comboStatusBrevetAdd1, 5, 1, 1, 1);

        lblNumeroBrevetAdd1 = new QLabel(page_proj_add);
        lblNumeroBrevetAdd1->setObjectName("lblNumeroBrevetAdd1");

        gridLayoutProjAdd->addWidget(lblNumeroBrevetAdd1, 3, 0, 1, 1);

        lineDomaineAdd1 = new QLineEdit(page_proj_add);
        lineDomaineAdd1->setObjectName("lineDomaineAdd1");

        gridLayoutProjAdd->addWidget(lineDomaineAdd1, 1, 1, 1, 1);

        lineInventeursAdd1 = new QLineEdit(page_proj_add);
        lineInventeursAdd1->setObjectName("lineInventeursAdd1");

        gridLayoutProjAdd->addWidget(lineInventeursAdd1, 0, 3, 1, 1);

        lblTitreAdd1 = new QLabel(page_proj_add);
        lblTitreAdd1->setObjectName("lblTitreAdd1");

        gridLayoutProjAdd->addWidget(lblTitreAdd1, 0, 0, 1, 1);

        lblInventeursAdd1 = new QLabel(page_proj_add);
        lblInventeursAdd1->setObjectName("lblInventeursAdd1");

        gridLayoutProjAdd->addWidget(lblInventeursAdd1, 0, 2, 1, 1);

        stack_proj->addWidget(page_proj_add);
        page_proj_edit = new QWidget();
        page_proj_edit->setObjectName("page_proj_edit");
        gridLayoutProjEdit = new QGridLayout(page_proj_edit);
        gridLayoutProjEdit->setObjectName("gridLayoutProjEdit");
        gridLayoutProjEdit->setHorizontalSpacing(40);
        gridLayoutProjEdit->setVerticalSpacing(20);
        gridLayoutProjEdit->setContentsMargins(60, 28, 60, 28);
        lblInventeursEdit1 = new QLabel(page_proj_edit);
        lblInventeursEdit1->setObjectName("lblInventeursEdit1");

        gridLayoutProjEdit->addWidget(lblInventeursEdit1, 2, 2, 1, 1);

        lineTitreEdit1 = new QLineEdit(page_proj_edit);
        lineTitreEdit1->setObjectName("lineTitreEdit1");

        gridLayoutProjEdit->addWidget(lineTitreEdit1, 0, 1, 1, 1);

        lblTypeBrevetEdit1 = new QLabel(page_proj_edit);
        lblTypeBrevetEdit1->setObjectName("lblTypeBrevetEdit1");

        gridLayoutProjEdit->addWidget(lblTypeBrevetEdit1, 2, 0, 1, 1);

        lineResumeEdit1 = new QLineEdit(page_proj_edit);
        lineResumeEdit1->setObjectName("lineResumeEdit1");

        gridLayoutProjEdit->addWidget(lineResumeEdit1, 3, 3, 1, 1);

        lblDomaineEdit1 = new QLabel(page_proj_edit);
        lblDomaineEdit1->setObjectName("lblDomaineEdit1");

        gridLayoutProjEdit->addWidget(lblDomaineEdit1, 1, 0, 1, 1);

        comboTypeBrevetEdit1 = new QComboBox(page_proj_edit);
        comboTypeBrevetEdit1->setObjectName("comboTypeBrevetEdit1");

        gridLayoutProjEdit->addWidget(comboTypeBrevetEdit1, 2, 1, 1, 1);

        lblResumeEdit1 = new QLabel(page_proj_edit);
        lblResumeEdit1->setObjectName("lblResumeEdit1");

        gridLayoutProjEdit->addWidget(lblResumeEdit1, 3, 2, 1, 1);

        comboStatusBrevetEdit1 = new QComboBox(page_proj_edit);
        comboStatusBrevetEdit1->setObjectName("comboStatusBrevetEdit1");

        gridLayoutProjEdit->addWidget(comboStatusBrevetEdit1, 1, 3, 1, 1);

        dateDepotEdit1 = new QDateEdit(page_proj_edit);
        dateDepotEdit1->setObjectName("dateDepotEdit1");
        dateDepotEdit1->setCalendarPopup(true);
        dateDepotEdit1->setDate(QDate(2000, 1, 1));

        gridLayoutProjEdit->addWidget(dateDepotEdit1, 0, 3, 1, 1);

        hLayoutEditButtons1 = new QHBoxLayout();
        hLayoutEditButtons1->setObjectName("hLayoutEditButtons1");
        spacerEditButtons1 = new QSpacerItem(480, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutEditButtons1->addItem(spacerEditButtons1);

        btnConfirmEditProj = new QPushButton(page_proj_edit);
        btnConfirmEditProj->setObjectName("btnConfirmEditProj");

        hLayoutEditButtons1->addWidget(btnConfirmEditProj);

        btnRetourEditProj = new QPushButton(page_proj_edit);
        btnRetourEditProj->setObjectName("btnRetourEditProj");

        hLayoutEditButtons1->addWidget(btnRetourEditProj);


        gridLayoutProjEdit->addLayout(hLayoutEditButtons1, 5, 0, 1, 4);

        lineInventeursEdit1 = new QLineEdit(page_proj_edit);
        lineInventeursEdit1->setObjectName("lineInventeursEdit1");

        gridLayoutProjEdit->addWidget(lineInventeursEdit1, 2, 3, 1, 1);

        lineNumeroBrevetEdit1 = new QLineEdit(page_proj_edit);
        lineNumeroBrevetEdit1->setObjectName("lineNumeroBrevetEdit1");

        gridLayoutProjEdit->addWidget(lineNumeroBrevetEdit1, 3, 1, 1, 1);

        lblDateDepotEdit1 = new QLabel(page_proj_edit);
        lblDateDepotEdit1->setObjectName("lblDateDepotEdit1");

        gridLayoutProjEdit->addWidget(lblDateDepotEdit1, 0, 2, 1, 1);

        lblTitreEdit1 = new QLabel(page_proj_edit);
        lblTitreEdit1->setObjectName("lblTitreEdit1");

        gridLayoutProjEdit->addWidget(lblTitreEdit1, 0, 0, 1, 1);

        lblStatusBrevetEdit1 = new QLabel(page_proj_edit);
        lblStatusBrevetEdit1->setObjectName("lblStatusBrevetEdit1");

        gridLayoutProjEdit->addWidget(lblStatusBrevetEdit1, 1, 2, 1, 1);

        lineDomaineEdit1 = new QLineEdit(page_proj_edit);
        lineDomaineEdit1->setObjectName("lineDomaineEdit1");

        gridLayoutProjEdit->addWidget(lineDomaineEdit1, 1, 1, 1, 1);

        lblNumeroBrevetEdit1 = new QLabel(page_proj_edit);
        lblNumeroBrevetEdit1->setObjectName("lblNumeroBrevetEdit1");

        gridLayoutProjEdit->addWidget(lblNumeroBrevetEdit1, 3, 0, 1, 1);

        stack_proj->addWidget(page_proj_edit);
        page_proj_empty = new QWidget();
        page_proj_empty->setObjectName("page_proj_empty");
        verticalLayoutProjEmpty = new QVBoxLayout(page_proj_empty);
        verticalLayoutProjEmpty->setObjectName("verticalLayoutProjEmpty");
        stat_pub1 = new QLabel(page_proj_empty);
        stat_pub1->setObjectName("stat_pub1");

        verticalLayoutProjEmpty->addWidget(stat_pub1);

        retour_statn = new QPushButton(page_proj_empty);
        retour_statn->setObjectName("retour_statn");

        verticalLayoutProjEmpty->addWidget(retour_statn);

        stack_proj->addWidget(page_proj_empty);

        verticalLayoutProjRoot->addWidget(stack_proj);

        stackedWidget->addWidget(pageProjets);

        verticalLayoutRight->addWidget(stackedWidget);


        horizontalLayoutMain->addLayout(verticalLayoutRight);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1528, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);
        stack_emp->setCurrentIndex(0);
        stacked_I->setCurrentIndex(0);
        stack_pub->setCurrentIndex(1);
        stacked_F->setCurrentIndex(0);
        stacked_L->setCurrentIndex(0);
        stack_proj->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Smart Research Publication Management", nullptr));
        logoLabel->setText(QString());
        btnEmployee->setText(QCoreApplication::translate("MainWindow", "Employee", nullptr));
        btnInventaire->setText(QCoreApplication::translate("MainWindow", "Inventaire", nullptr));
        btnPublication->setText(QCoreApplication::translate("MainWindow", "Publication", nullptr));
        btnFinance->setText(QCoreApplication::translate("MainWindow", "Finance", nullptr));
        btnLaboratoires->setText(QCoreApplication::translate("MainWindow", "Laboratoires", nullptr));
        btnProjets->setText(QCoreApplication::translate("MainWindow", "Projets", nullptr));
        btnDeconnecter->setText(QCoreApplication::translate("MainWindow", "D\303\251connecter", nullptr));
        lblBrand->setText(QCoreApplication::translate("MainWindow", "SmartResearchLab", nullptr));
        lblPageTitle->setText(QCoreApplication::translate("MainWindow", "Employee", nullptr));
        lineSearchEmp->setText(QString());
        lineSearchEmp->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (recherche par CIN ou role...)", nullptr));
        btnChercher_emp->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        btnExporter_emp_excel->setText(QCoreApplication::translate("MainWindow", "exporter Excel", nullptr));
        btnTrier_emp->setText(QCoreApplication::translate("MainWindow", "Trier par Date creation", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableEmp->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableEmp->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableEmp->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableEmp->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TableEmp->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TableEmp->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Departement", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = TableEmp->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Date_emb", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = TableEmp->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = TableEmp->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        btnConge_emp_3->setText(QCoreApplication::translate("MainWindow", "Voir statistique", nullptr));
        btnConge_emp->setText(QCoreApplication::translate("MainWindow", "Cong\303\251", nullptr));
        btnConge_emp_2->setText(QCoreApplication::translate("MainWindow", "Formations", nullptr));
        btnAjouterEmp->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnTrier_emp_3->setText(QCoreApplication::translate("MainWindow", "Modifier employ\303\251", nullptr));
        btnExporter_emp_excel_3->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ajout ", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "D\303\251partement", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Date Pointage", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Heures Suppl\303\251mentaires", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        btnSaveEmployee->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Absence", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Date Embauche", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Heures Travaill\303\251es", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Type Contrat", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_8->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_8->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        btnSaveEmployee_2->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        labelUsernameEdit_3->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        labelSalaireEdit_3->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        labelCINEdit_3->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        labelPrenomEdit_3->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        labelHeuresTravEdit_3->setText(QCoreApplication::translate("MainWindow", "Heures Travaill\303\251es", nullptr));
        labelAbsenceEdit_3->setText(QCoreApplication::translate("MainWindow", "Absence", nullptr));
        labelDatePointageEdit_3->setText(QCoreApplication::translate("MainWindow", "Date Pointage", nullptr));
        labelDateEmbaucheEdit_3->setText(QCoreApplication::translate("MainWindow", "Date Embauche", nullptr));
        labelTypeContratEdit_3->setText(QCoreApplication::translate("MainWindow", "Type Contrat", nullptr));
        labelNomEdit_3->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        labelPosteEdit_3->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        labelDepartementEdit_3->setText(QCoreApplication::translate("MainWindow", "D\303\251partement", nullptr));
        labelHeuresSuppEdit_3->setText(QCoreApplication::translate("MainWindow", "Heures Suppl\303\251mentaires", nullptr));
        labelEmailEdit_3->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        btnSaveEditEmployee_3->setText(QCoreApplication::translate("MainWindow", "Enregistrer les modifications", nullptr));
        btnCancelEditEmp->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_10->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_10->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Stat", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_9->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_9->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Cong\303\251e", nullptr));
        Rejeter_conge_Emp->setText(QCoreApplication::translate("MainWindow", "Rejet\303\251", nullptr));
        Accepter_conge_Emp->setText(QCoreApplication::translate("MainWindow", "Accepter", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = TableCongeEmp->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = TableCongeEmp->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = TableCongeEmp->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Date_deb", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = TableCongeEmp->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "DateFin", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = TableCongeEmp->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = TableCongeEmp->horizontalHeaderItem(5);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_7->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_7->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Formation", nullptr));
        Modifier_Formations_Emp->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = TableFormations_Emp->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = TableFormations_Emp->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = TableFormations_Emp->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = TableFormations_Emp->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Dur\303\251e", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = TableFormations_Emp->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = TableFormations_Emp->horizontalHeaderItem(5);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "cout", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = TableFormations_Emp->horizontalHeaderItem(6);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = TableFormations_Emp->horizontalHeaderItem(7);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "valorisation", nullptr));
        Exporter_Formations_Emp->setText(QCoreApplication::translate("MainWindow", "Exporter vers le DG", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_6->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_6->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = TableInventory->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "SKU", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = TableInventory->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = TableInventory->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = TableInventory->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Qt Av.", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = TableInventory->horizontalHeaderItem(5);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Qt Rs.", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = TableInventory->horizontalHeaderItem(6);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Seuil", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = TableInventory->horizontalHeaderItem(7);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "Unit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = TableInventory->horizontalHeaderItem(8);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = TableInventory->horizontalHeaderItem(9);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = TableInventory->horizontalHeaderItem(10);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "\303\211tag\303\250re", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = TableInventory->horizontalHeaderItem(11);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        BtnInventoryAdd->setText(QCoreApplication::translate("MainWindow", "Ajouter\342\236\225", nullptr));
        BtnInventoryAdd->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnInventoryAdd_2->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        BtnInventoryAdd_2->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnInventoryEdit->setText(QCoreApplication::translate("MainWindow", "Modifier  \360\237\226\216", nullptr));
        BtnInventoryEdit->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        BtnInventoryDelete->setText(QCoreApplication::translate("MainWindow", "Supprimer\342\235\214", nullptr));
        BtnInventoryDelete->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "danger", nullptr)));
        BtnInventoryAdd_5->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        BtnInventoryAdd_5->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnInventoryExport->setText(QCoreApplication::translate("MainWindow", "Exporter PDF \342\254\207\357\270\217", nullptr));
        BtnInventoryExport->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "chip", nullptr)));
        InventorySearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID, nom, SKU\342\200\246", nullptr));
        InventoryStatus->setItemText(0, QCoreApplication::translate("MainWindow", "on_hand", nullptr));
        InventoryStatus->setItemText(1, QCoreApplication::translate("MainWindow", "Limited", nullptr));
        InventoryStatus->setItemText(2, QCoreApplication::translate("MainWindow", "stock_out", nullptr));

        LblInventoryStatus->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        LblInventorySearch->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        BtnInventoryApply->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        BtnInventoryApply->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        InventoryZone->setItemText(0, QCoreApplication::translate("MainWindow", "A", nullptr));
        InventoryZone->setItemText(1, QCoreApplication::translate("MainWindow", "B", nullptr));
        InventoryZone->setItemText(2, QCoreApplication::translate("MainWindow", "C", nullptr));
        InventoryZone->setItemText(3, QCoreApplication::translate("MainWindow", "D", nullptr));

        LblInventoryZone->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        LblInventoryType->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        PopupTitleInventory->setText(QCoreApplication::translate("MainWindow", "Ajouter un produit", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelInventory->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelInventory->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        LblIdProduct->setText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));
        IdProduct->setPlaceholderText(QCoreApplication::translate("MainWindow", "PROD-001", nullptr));
        LblName->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        Name->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom du produit", nullptr));
        LblSku->setText(QCoreApplication::translate("MainWindow", "SKU", nullptr));
        Sku->setPlaceholderText(QCoreApplication::translate("MainWindow", "SKU-001", nullptr));
        LblType_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        Type->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner type", nullptr));
        LblQtAv->setText(QCoreApplication::translate("MainWindow", "Qt Disponible", nullptr));
        LblQtRs->setText(QCoreApplication::translate("MainWindow", "Qt R\303\251serv\303\251e", nullptr));
        LblThreshold->setText(QCoreApplication::translate("MainWindow", "Seuil min", nullptr));
        LblUnit->setText(QCoreApplication::translate("MainWindow", "Unit\303\251", nullptr));
        Unit->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner unit\303\251", nullptr));
        LblPrice->setText(QCoreApplication::translate("MainWindow", "Prix (\342\202\254)", nullptr));
        Price->setPrefix(QCoreApplication::translate("MainWindow", "\342\202\254 ", nullptr));
        LblStatus->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        Status->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner statut", nullptr));
        LblZone->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        Zone->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner zone", nullptr));
        LblShelf->setText(QCoreApplication::translate("MainWindow", "\303\211tag\303\250re", nullptr));
        Shelf->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner \303\251tag\303\250re", nullptr));
        BtnPopupSaveInventory->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        BtnPopupSaveInventory->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnPopupResetInventory->setText(QCoreApplication::translate("MainWindow", "Vider", nullptr));
        BtnPopupResetInventory->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        PopupTitleInventory_2->setText(QCoreApplication::translate("MainWindow", "Modifier un produit", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelInventory_2->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelInventory_2->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        LblIdProduct_2->setText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));
        IdProduct_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "PROD-001", nullptr));
        LblName_2->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        Name_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom du produit", nullptr));
        LblSku_2->setText(QCoreApplication::translate("MainWindow", "SKU", nullptr));
        Sku_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "SKU-001", nullptr));
        LblType_3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        Type_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner type", nullptr));
        LblQtAv_2->setText(QCoreApplication::translate("MainWindow", "Qt Disponible", nullptr));
        LblQtRs_2->setText(QCoreApplication::translate("MainWindow", "Qt R\303\251serv\303\251e", nullptr));
        LblThreshold_2->setText(QCoreApplication::translate("MainWindow", "Seuil min", nullptr));
        LblUnit_2->setText(QCoreApplication::translate("MainWindow", "Unit\303\251", nullptr));
        Unit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner unit\303\251", nullptr));
        LblPrice_2->setText(QCoreApplication::translate("MainWindow", "Prix (\342\202\254)", nullptr));
        Price_2->setPrefix(QCoreApplication::translate("MainWindow", "\342\202\254 ", nullptr));
        LblStatus_2->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        Status_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner statut", nullptr));
        LblZone_2->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        Zone_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner zone", nullptr));
        LblShelf_2->setText(QCoreApplication::translate("MainWindow", "\303\211tag\303\250re", nullptr));
        Shelf_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionner \303\251tag\303\250re", nullptr));
        BtnPopupSaveInventory_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnPopupSaveInventory_2->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnPopupResetInventory_2->setText(QCoreApplication::translate("MainWindow", "Vider", nullptr));
        BtnPopupResetInventory_2->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        stat_pub_6->setText(QString());
        retour_stat_7->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        stat_pub_5->setText(QString());
        retour_stat_6->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tablePublication->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "Titre", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tablePublication->horizontalHeaderItem(1);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "resume", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tablePublication->horizontalHeaderItem(2);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("MainWindow", "Inventeurs", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tablePublication->horizontalHeaderItem(3);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("MainWindow", "domaine_fabrication", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tablePublication->horizontalHeaderItem(4);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("MainWindow", "type_brevet", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tablePublication->horizontalHeaderItem(5);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("MainWindow", "numero_brevet", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tablePublication->horizontalHeaderItem(6);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("MainWindow", "date_depot", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tablePublication->horizontalHeaderItem(7);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("MainWindow", "statut_brevet", nullptr));
        lineSearchPub->setText(QString());
        lineSearchPub->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (recherche par DOI...)", nullptr));
        btnReinitialiserPub->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        lblCategoriePub->setText(QCoreApplication::translate("MainWindow", "TRIER PAR :", nullptr));
        comboCategoriePub->setItemText(0, QCoreApplication::translate("MainWindow", "date", nullptr));
        comboCategoriePub->setItemText(1, QCoreApplication::translate("MainWindow", "statut", nullptr));
        comboCategoriePub->setItemText(2, QCoreApplication::translate("MainWindow", "titre", nullptr));

        lblPeriodeDuPub->setText(QCoreApplication::translate("MainWindow", "DATE_DEPOT", nullptr));
        btnAppliquerPub->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        btnVoirStatistiquesPub->setText(QCoreApplication::translate("MainWindow", "voir statistiques", nullptr));
        btnAjouterPub->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierPub->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerPub->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnExporterPub->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnAddPub->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnRetourAddPub->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lblTypeBrevetAdd->setText(QCoreApplication::translate("MainWindow", "type_brevet :", nullptr));
        lblDomaineAdd->setText(QCoreApplication::translate("MainWindow", "domaine_fabrication :", nullptr));
        lblStatusBrevetAdd->setText(QCoreApplication::translate("MainWindow", "status_brevet :", nullptr));
        lblResumeAdd->setText(QCoreApplication::translate("MainWindow", "resume :", nullptr));
        lblDateDepotAdd->setText(QCoreApplication::translate("MainWindow", "date_depot", nullptr));
        lblNumeroBrevetAdd->setText(QCoreApplication::translate("MainWindow", "numero_brevet :", nullptr));
        lblTitreAdd->setText(QCoreApplication::translate("MainWindow", "titre :", nullptr));
        lblInventeursAdd->setText(QCoreApplication::translate("MainWindow", "inventeurs :", nullptr));
        lblInventeursEdit->setText(QCoreApplication::translate("MainWindow", "inventeurs :", nullptr));
        lblTypeBrevetEdit->setText(QCoreApplication::translate("MainWindow", "type_brevet :", nullptr));
        lblDomaineEdit->setText(QCoreApplication::translate("MainWindow", "domaine_fabrication :", nullptr));
        lblResumeEdit->setText(QCoreApplication::translate("MainWindow", "resume :", nullptr));
        btnConfirmEditPub->setText(QCoreApplication::translate("MainWindow", "confirmer", nullptr));
        btnRetourEditPub->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lblDateDepotEdit->setText(QCoreApplication::translate("MainWindow", "date_depot", nullptr));
        lblTitreEdit->setText(QCoreApplication::translate("MainWindow", "titre :", nullptr));
        lblStatusBrevetEdit->setText(QCoreApplication::translate("MainWindow", "status_brevet :", nullptr));
        lblNumeroBrevetEdit->setText(QCoreApplication::translate("MainWindow", "numero_brevet :", nullptr));
        stat_pub->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "statistiques par domaines", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "statistiques par statut", nullptr));

        retour_stat->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        LblTo->setText(QCoreApplication::translate("MainWindow", "Au", nullptr));
        CbType->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir le type :", nullptr));
        CbType->setItemText(1, QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        CbType->setItemText(2, QCoreApplication::translate("MainWindow", "Revenu", nullptr));

        LblFrom->setText(QCoreApplication::translate("MainWindow", "P\303\251riode (du)", nullptr));
        EdSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (code, cat\303\251gorie, description...)", nullptr));
        LblType->setText(QCoreApplication::translate("MainWindow", "Recherche :", nullptr));
        BtnReset->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        BtnApply->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        TableTitle->setText(QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = TableFinance->horizontalHeaderItem(0);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("MainWindow", "CODETRANSA", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = TableFinance->horizontalHeaderItem(1);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = TableFinance->horizontalHeaderItem(2);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("MainWindow", "Montant en Dt", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = TableFinance->horizontalHeaderItem(3);
        ___qtablewidgetitem45->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = TableFinance->horizontalHeaderItem(4);
        ___qtablewidgetitem46->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = TableFinance->horizontalHeaderItem(5);
        ___qtablewidgetitem47->setText(QCoreApplication::translate("MainWindow", "Date transaction", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = TableFinance->horizontalHeaderItem(6);
        ___qtablewidgetitem48->setText(QCoreApplication::translate("MainWindow", "Mode paiement", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = TableFinance->horizontalHeaderItem(7);
        ___qtablewidgetitem49->setText(QCoreApplication::translate("MainWindow", "Date cr\303\251ation", nullptr));

        const bool __sortingEnabled = TableFinance->isSortingEnabled();
        TableFinance->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem50 = TableFinance->item(0, 0);
        ___qtablewidgetitem50->setText(QCoreApplication::translate("MainWindow", "TRX001", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = TableFinance->item(0, 1);
        ___qtablewidgetitem51->setText(QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = TableFinance->item(0, 2);
        ___qtablewidgetitem52->setText(QCoreApplication::translate("MainWindow", "120.50", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = TableFinance->item(0, 3);
        ___qtablewidgetitem53->setText(QCoreApplication::translate("MainWindow", "Fournitures", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = TableFinance->item(0, 4);
        ___qtablewidgetitem54->setText(QCoreApplication::translate("MainWindow", "Achat de papier et cartouches d\342\200\231encre", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = TableFinance->item(0, 5);
        ___qtablewidgetitem55->setText(QCoreApplication::translate("MainWindow", "2026-02-15", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = TableFinance->item(0, 6);
        ___qtablewidgetitem56->setText(QCoreApplication::translate("MainWindow", "carte bancaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = TableFinance->item(0, 7);
        ___qtablewidgetitem57->setText(QCoreApplication::translate("MainWindow", "2026-02-15", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = TableFinance->item(1, 0);
        ___qtablewidgetitem58->setText(QCoreApplication::translate("MainWindow", "TRX002", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = TableFinance->item(1, 1);
        ___qtablewidgetitem59->setText(QCoreApplication::translate("MainWindow", "Revenu", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = TableFinance->item(1, 2);
        ___qtablewidgetitem60->setText(QCoreApplication::translate("MainWindow", "850.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = TableFinance->item(1, 3);
        ___qtablewidgetitem61->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = TableFinance->item(1, 4);
        ___qtablewidgetitem62->setText(QCoreApplication::translate("MainWindow", "Paiement mission freelance", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = TableFinance->item(1, 5);
        ___qtablewidgetitem63->setText(QCoreApplication::translate("MainWindow", "2026-02-10", nullptr));
        QTableWidgetItem *___qtablewidgetitem64 = TableFinance->item(1, 6);
        ___qtablewidgetitem64->setText(QCoreApplication::translate("MainWindow", "virement", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = TableFinance->item(1, 7);
        ___qtablewidgetitem65->setText(QCoreApplication::translate("MainWindow", "2026-02-10", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = TableFinance->item(2, 0);
        ___qtablewidgetitem66->setText(QCoreApplication::translate("MainWindow", "TRX003", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = TableFinance->item(2, 1);
        ___qtablewidgetitem67->setText(QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = TableFinance->item(2, 2);
        ___qtablewidgetitem68->setText(QCoreApplication::translate("MainWindow", "60.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = TableFinance->item(2, 3);
        ___qtablewidgetitem69->setText(QCoreApplication::translate("MainWindow", "Transport", nullptr));
        QTableWidgetItem *___qtablewidgetitem70 = TableFinance->item(2, 4);
        ___qtablewidgetitem70->setText(QCoreApplication::translate("MainWindow", "Frais d\303\251placement client", nullptr));
        QTableWidgetItem *___qtablewidgetitem71 = TableFinance->item(2, 5);
        ___qtablewidgetitem71->setText(QCoreApplication::translate("MainWindow", "2026-02-18", nullptr));
        QTableWidgetItem *___qtablewidgetitem72 = TableFinance->item(2, 6);
        ___qtablewidgetitem72->setText(QCoreApplication::translate("MainWindow", "especes", nullptr));
        QTableWidgetItem *___qtablewidgetitem73 = TableFinance->item(2, 7);
        ___qtablewidgetitem73->setText(QCoreApplication::translate("MainWindow", "2026-02-18", nullptr));
        TableFinance->setSortingEnabled(__sortingEnabled);

        BtnAdd->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        BtnEdit->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnDelete->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        BtnAdd_4->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        BtnExport->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        PopupTitleFinance->setText(QCoreApplication::translate("MainWindow", "Ajouter une transaction", nullptr));
        LblAmount->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        FormPayMode->setItemText(0, QCoreApplication::translate("MainWindow", "Especes", nullptr));
        FormPayMode->setItemText(1, QCoreApplication::translate("MainWindow", "Cheque", nullptr));
        FormPayMode->setItemText(2, QCoreApplication::translate("MainWindow", "Virement", nullptr));
        FormPayMode->setItemText(3, QCoreApplication::translate("MainWindow", "Carte bancaire", nullptr));
        FormPayMode->setItemText(4, QCoreApplication::translate("MainWindow", "Facture", nullptr));
        FormPayMode->setItemText(5, QCoreApplication::translate("MainWindow", "Remboursement", nullptr));

        LblCat2->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        LblCode->setText(QCoreApplication::translate("MainWindow", "Code transaction", nullptr));
        FormDesc->setPlaceholderText(QCoreApplication::translate("MainWindow", "D\303\251tails\342\200\246", nullptr));
        LblDesc->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        LblDate2->setText(QCoreApplication::translate("MainWindow", "Date transaction", nullptr));
        FormType->setItemText(0, QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        FormType->setItemText(1, QCoreApplication::translate("MainWindow", "Revenu", nullptr));

        BtnPopupSaveFinance->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        BtnPopupCancelFinance->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        LblFType->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        LblCreated->setText(QCoreApplication::translate("MainWindow", "Date cr\303\251ation", nullptr));
        FormCode->setPlaceholderText(QCoreApplication::translate("MainWindow", "ex: TRX-2026-001", nullptr));
        LblPay->setText(QCoreApplication::translate("MainWindow", "Mode paiement", nullptr));
        FormAmount->setPlaceholderText(QCoreApplication::translate("MainWindow", "ex: 2500", nullptr));
        FormCategory->setPlaceholderText(QString());
        PopupTitleFinance_2->setText(QCoreApplication::translate("MainWindow", "Modifier une transaction", nullptr));
        FormPayMode_2->setItemText(0, QCoreApplication::translate("MainWindow", "Especes", nullptr));
        FormPayMode_2->setItemText(1, QCoreApplication::translate("MainWindow", "Cheque", nullptr));
        FormPayMode_2->setItemText(2, QCoreApplication::translate("MainWindow", "Virement", nullptr));
        FormPayMode_2->setItemText(3, QCoreApplication::translate("MainWindow", "Carte bancaire", nullptr));
        FormPayMode_2->setItemText(4, QCoreApplication::translate("MainWindow", "Facture", nullptr));
        FormPayMode_2->setItemText(5, QCoreApplication::translate("MainWindow", "Remboursement", nullptr));

        FormCategory_2->setPlaceholderText(QString());
        LblCode_2->setText(QCoreApplication::translate("MainWindow", "Code transaction", nullptr));
        FormType_2->setItemText(0, QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        FormType_2->setItemText(1, QCoreApplication::translate("MainWindow", "Revenu", nullptr));

        LblCreated_2->setText(QCoreApplication::translate("MainWindow", "Date cr\303\251ation", nullptr));
        LblAmount_2->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        LblDesc_2->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        FormCode_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "ex: TRX-2026-001", nullptr));
        LblPay_2->setText(QCoreApplication::translate("MainWindow", "Mode paiement", nullptr));
        LblCat2_2->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        LblDate2_2->setText(QCoreApplication::translate("MainWindow", "Date transaction", nullptr));
        BtnPopupSaveFinance_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnPopupCancelFinance_2->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        FormDesc_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "D\303\251tails\342\200\246", nullptr));
        LblFType_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        FormAmount_2->setPlaceholderText(QString());
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "D\303\251penses vs Revenus", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Statistiques de Revenus", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Statistiques de D\303\251penses", nullptr));

        stat_pub_3->setText(QString());
        retour_stat_4->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        retour_stat_5->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        stat_pub_4->setText(QString());
        QTableWidgetItem *___qtablewidgetitem74 = TableLabs_2->horizontalHeaderItem(1);
        ___qtablewidgetitem74->setText(QCoreApplication::translate("MainWindow", "Nom Labo", nullptr));
        QTableWidgetItem *___qtablewidgetitem75 = TableLabs_2->horizontalHeaderItem(2);
        ___qtablewidgetitem75->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        QTableWidgetItem *___qtablewidgetitem76 = TableLabs_2->horizontalHeaderItem(3);
        ___qtablewidgetitem76->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        QTableWidgetItem *___qtablewidgetitem77 = TableLabs_2->horizontalHeaderItem(4);
        ___qtablewidgetitem77->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        QTableWidgetItem *___qtablewidgetitem78 = TableLabs_2->horizontalHeaderItem(5);
        ___qtablewidgetitem78->setText(QCoreApplication::translate("MainWindow", "disponibilite", nullptr));
        QTableWidgetItem *___qtablewidgetitem79 = TableLabs_2->horizontalHeaderItem(6);
        ___qtablewidgetitem79->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem80 = TableLabs_2->horizontalHeaderItem(7);
        ___qtablewidgetitem80->setText(QCoreApplication::translate("MainWindow", "Capacit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem81 = TableLabs_2->horizontalHeaderItem(8);
        ___qtablewidgetitem81->setText(QCoreApplication::translate("MainWindow", "QR Code", nullptr));
        btnExporterPub_2->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnVoirStatistiquesPub_2->setText(QCoreApplication::translate("MainWindow", "voir statistiques", nullptr));
        btnAjouterPub_4->setText(QCoreApplication::translate("MainWindow", "Maps", nullptr));
        btnAjouterPub_3->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        btnAjouterPub_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierPub_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerPub_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        LblLabsSearch_2->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        LblLabsSpec_2->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        LblLabsCap_2->setText(QCoreApplication::translate("MainWindow", "disponibilite", nullptr));
        btnAppliquerPub_3->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        LabsSearch_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "nom, responsable, localisation, num\303\251ro\342\200\246", nullptr));
        LabsSpec_2->setItemText(0, QCoreApplication::translate("MainWindow", "choisir un specialite", nullptr));
        LabsSpec_2->setItemText(1, QCoreApplication::translate("MainWindow", "interieur", nullptr));
        LabsSpec_2->setItemText(2, QCoreApplication::translate("MainWindow", "exterieur", nullptr));

        LabsCap_2->setItemText(0, QCoreApplication::translate("MainWindow", "choisir disponibilite", nullptr));
        LabsCap_2->setItemText(1, QCoreApplication::translate("MainWindow", "disponible", nullptr));
        LabsCap_2->setItemText(2, QCoreApplication::translate("MainWindow", "occupe", nullptr));

        btnReinitialiserPub_3->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        LabLocation_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Bloc B, Salle 204", nullptr));
        LabResponsible_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom responsable", nullptr));
        LblLabCap_5->setText(QCoreApplication::translate("MainWindow", "Capacit\303\251", nullptr));
        LblLabLoc_5->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        LblLabName_5->setText(QCoreApplication::translate("MainWindow", "Nom labo", nullptr));
        LblLabNum_5->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        LabName_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Laboratoire IA", nullptr));
        LabNumber_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "204", nullptr));
        LblLabResp_5->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        LblLabSpec_5->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        PopupTitleLabs_5->setText(QCoreApplication::translate("MainWindow", "Modifier un laboratoire", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_5->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_5->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        BtnPopupResetLabs_5->setText(QCoreApplication::translate("MainWindow", "Vider", nullptr));
        BtnPopupResetLabs_5->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        BtnPopupSaveLabs_5->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnPopupSaveLabs_5->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        LabLocation_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Bloc B, Salle 204", nullptr));
        LabResponsible_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom responsable", nullptr));
        LblLabCap_3->setText(QCoreApplication::translate("MainWindow", "Capacit\303\251", nullptr));
        LblLabLoc_3->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        LblLabName_3->setText(QCoreApplication::translate("MainWindow", "Nom labo", nullptr));
        LblLabNum_3->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        LabName_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Laboratoire IA", nullptr));
        LabNumber_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "204", nullptr));
        LblLabResp_3->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        LblLabSpec_3->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        PopupTitleLabs_3->setText(QCoreApplication::translate("MainWindow", "Ajouter un laboratoire", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_3->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_3->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        BtnPopupSaveLabs_3->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        BtnPopupSaveLabs_3->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnPopupResetLabs_3->setText(QCoreApplication::translate("MainWindow", "Vider", nullptr));
        BtnPopupResetLabs_3->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        retour_stat_2->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "statistiques par domaines", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "statistiques par statut", nullptr));

        stat_pub_2->setText(QString());
        retour_stat_3->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        stat_pub_7->setText(QString());
        retour_stat_8->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lineSearchProj->setText(QString());
        lineSearchProj->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (recherche par DOI...)", nullptr));
        comboCategorieProj->setItemText(0, QCoreApplication::translate("MainWindow", "date", nullptr));
        comboCategorieProj->setItemText(1, QCoreApplication::translate("MainWindow", "titre", nullptr));

        btnAppliquerProj->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        lblCategorieProj->setText(QCoreApplication::translate("MainWindow", "TRIER PAR :", nullptr));
        lblPeriodeDuProj->setText(QCoreApplication::translate("MainWindow", "DATE", nullptr));
        QTableWidgetItem *___qtablewidgetitem82 = tableProjets->horizontalHeaderItem(0);
        ___qtablewidgetitem82->setText(QCoreApplication::translate("MainWindow", "nom_Projet ", nullptr));
        QTableWidgetItem *___qtablewidgetitem83 = tableProjets->horizontalHeaderItem(1);
        ___qtablewidgetitem83->setText(QCoreApplication::translate("MainWindow", "description", nullptr));
        QTableWidgetItem *___qtablewidgetitem84 = tableProjets->horizontalHeaderItem(2);
        ___qtablewidgetitem84->setText(QCoreApplication::translate("MainWindow", "objectifs  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem85 = tableProjets->horizontalHeaderItem(3);
        ___qtablewidgetitem85->setText(QCoreApplication::translate("MainWindow", "date_D\303\251but    ", nullptr));
        QTableWidgetItem *___qtablewidgetitem86 = tableProjets->horizontalHeaderItem(4);
        ___qtablewidgetitem86->setText(QCoreApplication::translate("MainWindow", "date_Fin_Prevue  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem87 = tableProjets->horizontalHeaderItem(5);
        ___qtablewidgetitem87->setText(QCoreApplication::translate("MainWindow", "date_Fin_Reelle  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem88 = tableProjets->horizontalHeaderItem(6);
        ___qtablewidgetitem88->setText(QCoreApplication::translate("MainWindow", "statut  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem89 = tableProjets->horizontalHeaderItem(7);
        ___qtablewidgetitem89->setText(QCoreApplication::translate("MainWindow", "priorite ", nullptr));
        btnAjouterProj->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierProj->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerProj->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnVoirStatistiquesProj->setText(QCoreApplication::translate("MainWindow", "voir statistiques", nullptr));
        btnAddProj->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnRetourAddProj->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lblTypeBrevetAdd1->setText(QCoreApplication::translate("MainWindow", "objectifs  ", nullptr));
        lblDomaineAdd1->setText(QCoreApplication::translate("MainWindow", "description  ", nullptr));
        lblStatusBrevetAdd1->setText(QCoreApplication::translate("MainWindow", "date_Fin_Reelle  ", nullptr));
        lblResumeAdd1->setText(QCoreApplication::translate("MainWindow", "priorite ", nullptr));
        lblDateDepotAdd1->setText(QCoreApplication::translate("MainWindow", "date_Fin_Prevue  ", nullptr));
        lblNumeroBrevetAdd1->setText(QCoreApplication::translate("MainWindow", "date_D\303\251but    ", nullptr));
        lblTitreAdd1->setText(QCoreApplication::translate("MainWindow", "nom_Projet ", nullptr));
        lblInventeursAdd1->setText(QCoreApplication::translate("MainWindow", "statut  ", nullptr));
        lblInventeursEdit1->setText(QCoreApplication::translate("MainWindow", "statut  ", nullptr));
        lblTypeBrevetEdit1->setText(QCoreApplication::translate("MainWindow", "objectifs  ", nullptr));
        lblDomaineEdit1->setText(QCoreApplication::translate("MainWindow", "description  ", nullptr));
        lblResumeEdit1->setText(QCoreApplication::translate("MainWindow", "priorite ", nullptr));
        btnConfirmEditProj->setText(QCoreApplication::translate("MainWindow", "confirmer", nullptr));
        btnRetourEditProj->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lblDateDepotEdit1->setText(QCoreApplication::translate("MainWindow", "date_D\303\251but    ", nullptr));
        lblTitreEdit1->setText(QCoreApplication::translate("MainWindow", "nom_Projet ", nullptr));
        lblStatusBrevetEdit1->setText(QCoreApplication::translate("MainWindow", "date_Fin_Reelle  ", nullptr));
        lblNumeroBrevetEdit1->setText(QCoreApplication::translate("MainWindow", "date_Fin_Prevue  ", nullptr));
        stat_pub1->setText(QString());
        retour_statn->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
