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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
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
    QPushButton *btnThemeToggle;
    QPushButton *btnDeconnecter;
    QVBoxLayout *verticalLayoutRight;
    QFrame *topBar;
    QLabel *lblBrand;
    QLabel *lblPageTitle;
    QPushButton *btnNotif;
    QStackedWidget *stackedWidget;
    QWidget *pageEmployee;
    QVBoxLayout *verticalLayoutPage0;
    QStackedWidget *stack_emp;
    QWidget *page_Emp;
    QGridLayout *gridLayout_4;
    QLineEdit *lineSearchEmp;
    QPushButton *btnTrier_emp;
    QPushButton *btnModifier_emp;
    QPushButton *pointage;
    QPushButton *btnAjouterEmp;
    QTableWidget *TableEmp;
    QPushButton *btnSupprimer_emp;
    QPushButton *btnStat_emp;
    QWidget *page_add_Emp;
    QVBoxLayout *addEmpLayout;
    QHBoxLayout *addEmpTitleRow;
    QLabel *lblAddEmpTitle;
    QSpacerItem *spacerItem;
    QToolButton *BtnPopupCancelLabs_8;
    QGroupBox *groupBox_2;
    QGridLayout *addEmpGrid;
    QLabel *label;
    QLineEdit *lineCINAdd;
    QLabel *label_8;
    QComboBox *comboDepartementAdd;
    QLabel *label_2;
    QLineEdit *lineUsernameAdd;
    QLabel *label_7;
    QComboBox *comboPosteAdd;
    QLabel *label_3;
    QHBoxLayout *passwordRow;
    QLineEdit *linePasswordAdd;
    QProgressBar *passwordStrengthBarAdd;
    QLabel *passwordStrengthLabelAdd;
    QLabel *label_10;
    QDateEdit *dateEmbaucheAdd;
    QLabel *label_4;
    QLineEdit *lineEmailAdd;
    QLabel *label_11;
    QLineEdit *lineSalaireAdd;
    QLabel *label_5;
    QLineEdit *lineNomAdd;
    QLabel *label_25;
    QPushButton *btnScanFace;
    QLabel *label_6;
    QLineEdit *linePrenomAdd;
    QLabel *label_cam;
    QLabel *label_12;
    QComboBox *comboRoleAdd;
    QHBoxLayout *addEmpBtnRow;
    QSpacerItem *spacerItem1;
    QPushButton *btnSaveEmployee;
    QPushButton *btnAnnuler_emp;
    QSpacerItem *spacerItem2;
    QWidget *page_Edit_Emp;
    QVBoxLayout *editEmpLayout;
    QHBoxLayout *editEmpTitleRow;
    QLabel *lblEditEmpTitle;
    QSpacerItem *spacerItem3;
    QToolButton *BtnPopupCancelLabs_10;
    QGroupBox *groupBox_6;
    QGridLayout *editEmpGrid;
    QLabel *labelCINEdit_3;
    QLineEdit *lineCIN_emp;
    QLabel *labelDateEmbaucheEdit_3;
    QDateEdit *dateEmbaucheEmp;
    QLabel *labelUsernameEdit_3;
    QLineEdit *lineUsernameEmp;
    QLabel *labelSalaireEdit_3;
    QLineEdit *lineSalaireEmp;
    QLabel *labelEmailEdit_3;
    QLineEdit *lineEmailEmp;
    QLabel *labelPosteEdit_3;
    QComboBox *comboPosteEmp;
    QLabel *labelNomEdit_3;
    QLineEdit *lineNomEmp;
    QLabel *labelDepartementEdit_3;
    QComboBox *comboDepartementEmp;
    QLabel *labelPrenomEdit_3;
    QLineEdit *linePrenomEmp;
    QLabel *label_13;
    QComboBox *comboRoleAdd_2;
    QHBoxLayout *editEmpBtnRow;
    QSpacerItem *spacerItem4;
    QPushButton *btnSaveEditEmployee;
    QPushButton *btnCancelEditEmp;
    QSpacerItem *spacerItem5;
    QWidget *page_Stat;
    QVBoxLayout *statEmpLayout;
    QHBoxLayout *statEmpTitleRow;
    QSpacerItem *spacerItem6;
    QToolButton *BtnPopupCancelLabs_9;
    QGroupBox *groupBox;
    QVBoxLayout *statGroupLayout;
    QWidget *page_conge;
    QVBoxLayout *congeLayout;
    QHBoxLayout *congeTitleRow;
    QSpacerItem *spacerItem7;
    QToolButton *BtnPopupCancelLabs_7;
    QGroupBox *groupBox_3;
    QVBoxLayout *congeGroupLayout;
    QTableWidget *TableCongeEmp;
    QHBoxLayout *congeBtnRow;
    QSpacerItem *spacerItem8;
    QPushButton *Accepter_conge_Emp;
    QPushButton *Rejeter_conge_Emp;
    QSpacerItem *spacerItem9;
    QWidget *page_formation;
    QVBoxLayout *formationLayout;
    QHBoxLayout *formationTitleRow;
    QSpacerItem *spacerItem10;
    QToolButton *BtnPopupCancelLabs_6;
    QGroupBox *groupBox_4;
    QVBoxLayout *formationGroupLayout;
    QTableWidget *TableFormations_Emp;
    QHBoxLayout *formationBtnRow;
    QSpacerItem *spacerItem11;
    QPushButton *Modifier_Formations_Emp;
    QPushButton *Exporter_Formations_Emp;
    QSpacerItem *spacerItem12;
    QWidget *page;
    QVBoxLayout *pointageLayout;
    QHBoxLayout *pointageTitleRow;
    QLabel *label_15;
    QSpacerItem *spacerItem13;
    QToolButton *btn_ret;
    QGroupBox *groupBox_5;
    QVBoxLayout *pointageGroupLayout;
    QFrame *frame;
    QVBoxLayout *pointageFrameLayout;
    QTableView *tableView;
    QHBoxLayout *pointageBadgeRow;
    QLabel *label_9;
    QLineEdit *input_badge;
    QPushButton *btn_reset;
    QPushButton *btn_exportt;
    QLabel *label_feedback;
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
    QPushButton *BtnInventoryReset;
    QComboBox *InventoryZone;
    QLabel *LblInventoryZone;
    QLabel *LblInventoryType;
    QLabel *LblInventorySort;
    QComboBox *InventorySort;
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
    QLabel *LblDescription;
    QTextEdit *Description;
    QHBoxLayout *popupInventoryActions;
    QSpacerItem *popupInventoryActionsLeft;
    QPushButton *BtnPopupAutoSaveInventory;
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
    QLabel *LblDescription_2;
    QTextEdit *Description_2;
    QHBoxLayout *popupInventoryActions_2;
    QSpacerItem *popupInventoryActionsLeft_2;
    QPushButton *BtnPopupSaveInventory_2;
    QPushButton *BtnPopupResetInventory_2;
    QWidget *stati;
    QLabel *stat_pub_6;
    QPushButton *retour_stat_7;
    QWidget *afficheri;
    QVBoxLayout *detailInventoryRootLayout;
    QHBoxLayout *detailHeaderLayout;
    QLabel *aff_header_title;
    QSpacerItem *hSpacerDetailHeader;
    QPushButton *retour_stat_6;
    QHBoxLayout *detailCardsLayout;
    QFrame *CardGeneral;
    QFormLayout *formGeneral;
    QLabel *lbl_g1;
    QLabel *aff_id;
    QLabel *lbl_g2;
    QLabel *aff_sku;
    QLabel *lbl_g3;
    QLabel *aff_name;
    QLabel *lbl_g4;
    QLabel *aff_type;
    QLabel *lbl_g5;
    QLabel *aff_price;
    QLabel *lbl_g6;
    QLabel *aff_status;
    QFrame *CardStock;
    QFormLayout *formStock;
    QLabel *lbl_s1;
    QLabel *aff_qtav;
    QLabel *lbl_s2;
    QLabel *aff_qtrs;
    QLabel *lbl_s3;
    QLabel *aff_threshold;
    QLabel *lbl_s4;
    QLabel *aff_unit;
    QLabel *lbl_s5;
    QLabel *aff_zone;
    QLabel *lbl_s6;
    QLabel *aff_shelf;
    QFrame *CardDescription;
    QVBoxLayout *vLayoutDesc;
    QLabel *lbl_d1;
    QLabel *aff_description;
    QHBoxLayout *detailExportButtonsLayout;
    QPushButton *BtnInventoryDetailExportPdf;
    QSpacerItem *vSpacerDetailBottom;
    QWidget *pagePublication;
    QVBoxLayout *verticalLayoutPubRoot;
    QStackedWidget *stack_pub;
    QWidget *page_pub_list;
    QVBoxLayout *verticalLayoutPubList;
    QTableWidget *tablePublication;
    QLineEdit *lineSearchPub;
    QGridLayout *gridLayoutPubFilters;
    QPushButton *btnAppliquerPub;
    QPushButton *btnReinitialiserPub;
    QComboBox *comboTriPub;
    QLabel *lblCategoriePub;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayoutPubBottom;
    QPushButton *btnVoirStatistiquesPub;
    QPushButton *btnChatbotPub;
    QPushButton *btnMailingPub;
    QSpacerItem *horizontalSpacerPubBottom;
    QPushButton *btnAjouterPub;
    QPushButton *btnModifierPub;
    QPushButton *btnSupprimerPub;
    QPushButton *btnExporterPub;
    QWidget *page_pub_add;
    QGridLayout *gridLayoutPubAdd;
    QLabel *lblStatusBrevetAdd;
    QLabel *lblTitreAdd;
    QLineEdit *lineResumeAdd;
    QDateEdit *dateDepotAdd;
    QComboBox *comboTypeBrevetAdd;
    QLabel *lblTypeBrevetAdd;
    QLabel *lblInventeursAdd;
    QLabel *lblDomaineAdd;
    QLineEdit *lineDomaineAdd;
    QLabel *lblResumeAdd;
    QLabel *lblDateDepotAdd;
    QLineEdit *lineNumeroBrevetAdd;
    QLabel *lblNumeroBrevetAdd;
    QLineEdit *lineTitreAdd;
    QComboBox *comboStatusBrevetAdd;
    QHBoxLayout *hLayoutAddButtons;
    QSpacerItem *spacerAddButtons;
    QPushButton *btnAddPub;
    QPushButton *btnRetourAddPub;
    QComboBox *lineInventeursAdd;
    QWidget *page_pub_edit;
    QGridLayout *gridLayoutPubEdit;
    QLineEdit *lineNumeroBrevetEdit;
    QLabel *lblDateDepotEdit;
    QLabel *lblTypeBrevetEdit;
    QComboBox *comboStatusBrevetEdit;
    QLabel *lblResumeEdit;
    QHBoxLayout *hLayoutEditButtons;
    QSpacerItem *spacerEditButtons;
    QPushButton *btnConfirmEditPub;
    QPushButton *btnRetourEditPub;
    QLabel *lblStatusBrevetEdit;
    QComboBox *comboTypeBrevetEdit;
    QLabel *lblTitreEdit;
    QDateEdit *dateDepotEdit;
    QLabel *lblDomaineEdit;
    QLineEdit *lineTitreEdit;
    QLineEdit *lineDomaineEdit;
    QLabel *lblInventeursEdit;
    QLineEdit *lineResumeEdit;
    QLabel *lblNumeroBrevetEdit;
    QComboBox *lineInventeursEdit;
    QWidget *page_pub_empty;
    QVBoxLayout *verticalLayoutPubEmpty;
    QWidget *statsWidgetPub;
    QPushButton *retour_stat;
    QWidget *page_2;
    QFormLayout *formLayout;
    QLabel *label_14;
    QTextEdit *textChatPub;
    QLineEdit *lineQuestionPub;
    QPushButton *btnEnvoyerQuestionPub;
    QPushButton *btnRetourChatbotPub;
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
    QFrame *PopupFinanceCard;
    QVBoxLayout *popupFinanceCardLayout;
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
    QHBoxLayout *layoutAmountRow;
    QPushButton *BtnAmountDecr;
    QLineEdit *FormAmount;
    QPushButton *BtnAmountIncr;
    QPushButton *BtnConvertCurrency;
    QLineEdit *FormCategory;
    QVBoxLayout *layoutOcrSection;
    QPushButton *BtnOcrReceipt;
    QLabel *LblOcrHint;
    QWidget *modifierF;
    QGridLayout *gridLayout_modifierF;
    QFrame *OverlayFinance_2;
    QVBoxLayout *overlayFinanceLayout_2;
    QFrame *PopupFinanceCard_2;
    QVBoxLayout *popupFinanceCardLayout_2;
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
    QHBoxLayout *layoutAmountRow_2;
    QPushButton *BtnAmountDecr_2;
    QLineEdit *FormAmount_2;
    QPushButton *BtnAmountIncr_2;
    QPushButton *BtnConvertCurrency_2;
    QWidget *statsF;
    QVBoxLayout *statsFLayout;
    QLabel *stat_pub_3;
    QHBoxLayout *statsFBottomRow;
    QComboBox *comboBox_3;
    QSpacerItem *spacerItem14;
    QPushButton *retour_stat_4;
    QWidget *afficherF;
    QPushButton *retour_stat_5;
    QLabel *stat_pub_4;
    QWidget *pageLaboratoires;
    QVBoxLayout *verticalLayoutPage4;
    QStackedWidget *stacked_L;
    QWidget *Lab;
    QVBoxLayout *verticalLayout_Lab;
    QFrame *LabsCardFilter_2;
    QHBoxLayout *labsFilterLayout;
    QLineEdit *LabsSearch_2;
    QComboBox *LabsSpec_2;
    QComboBox *LabsCap_2;
    QSpacerItem *labsFilterSpacer;
    QPushButton *btnLabReserveProduct;
    QPushButton *btnReinitialiserPub_3;
    QTableWidget *TableLabs_2;
    QHBoxLayout *labsActionBtns;
    QPushButton *btnAjouterPub_3;
    QPushButton *btnAjouterPub_2;
    QPushButton *btnModifierPub_2;
    QPushButton *btnSupprimerPub_2;
    QSpacerItem *labsBtnSpacer;
    QPushButton *btnStatLabs;
    QHBoxLayout *labsReserveRow;
    QSpacerItem *labsReserveSpacer;
    QWidget *modifierL;
    QLineEdit *LabReste_5;
    QLabel *label_23;
    QPushButton *BtnPopupResetLabs_5;
    QVBoxLayout *modifierLLayout;
    QLabel *lblPageTitle_4;
    QGridLayout *modifierLGrid;
    QLabel *LblLabName_5;
    QLineEdit *LabName_5;
    QLabel *LblLabResp_5;
    QComboBox *LabResponsible_5;
    QLabel *LblLabLoc_5;
    QLineEdit *LabLocation_5;
    QLabel *LblLabNum_5;
    QLineEdit *LabNumber_5;
    QLabel *LblLabSpec_5;
    QComboBox *LabSpec_5;
    QLabel *LblLabCap_5;
    QComboBox *LabCap_5;
    QLabel *LblLabSpec_14;
    QComboBox *LabSpec_6;
    QLabel *LblLabSpec_15;
    QComboBox *LabCap_6;
    QLabel *label_22;
    QDoubleSpinBox *LabMontant_5;
    QLabel *label_24;
    QDoubleSpinBox *LabMontantPaye_5;
    QSpacerItem *modifierLSpacer;
    QHBoxLayout *labsEditBtnRow;
    QPushButton *BtnPopupSaveLabs_5;
    QSpacerItem *labsEditBtnSpacer;
    QPushButton *retour_stat_9;
    QWidget *ajouterL;
    QVBoxLayout *ajouterLMainLayout;
    QLineEdit *LabReste_3;
    QLabel *label_21;
    QLabel *lblPageTitle_3;
    QGridLayout *labsAddFormGrid;
    QLabel *LblLabName_3;
    QLineEdit *LabName_3;
    QLabel *LblLabResp_3;
    QComboBox *LabResponsible_3;
    QLabel *LblLabLoc_3;
    QLineEdit *LabLocation_3;
    QLabel *LblLabNum_3;
    QLineEdit *LabNumber_3;
    QLabel *LblLabSpec_3;
    QComboBox *LabSpec_3;
    QLabel *LblLabCap_3;
    QComboBox *LabCap_3;
    QLabel *LblLabSpec_12;
    QComboBox *LabSpec_4;
    QLabel *LblLabSpec_13;
    QComboBox *LabCap_4;
    QLabel *label_20;
    QDoubleSpinBox *LabMontant_3;
    QLabel *label_19;
    QDoubleSpinBox *LabMontantPaye_3;
    QSpacerItem *verticalSpacerAddLab;
    QHBoxLayout *labsAddBtnRow;
    QPushButton *BtnPopupSaveLabs_3;
    QPushButton *BtnPopupResetLabs_3;
    QPushButton *retour_stat_8;
    QWidget *statL;
    QPushButton *retour_stat_2;
    QComboBox *comboBox_2;
    QLabel *stat_pub_2;
    QWidget *affichierL;
    QVBoxLayout *affichierLLayout;
    QLabel *lblPageTitle_2;
    QHBoxLayout *affichierLContentRow;
    QFrame *PopupLabsForm_4;
    QGridLayout *affichierLGrid;
    QLabel *LblLabName_6;
    QLineEdit *aff1;
    QLabel *LblLabResp_6;
    QLineEdit *aff5;
    QLabel *LblLabLoc_6;
    QLineEdit *aff2;
    QLabel *LblLabNum_6;
    QLineEdit *aff6;
    QLabel *LblLabSpec_6;
    QComboBox *aff3;
    QLabel *LblLabCap_6;
    QComboBox *aff7;
    QLabel *LblLabSpec_7;
    QComboBox *aff3_2;
    QLabel *LblLabSpec_8;
    QComboBox *aff7_2;
    QLabel *label_16;
    QLineEdit *aff_montant;
    QLabel *label_18;
    QLineEdit *aff_montant_paye;
    QLabel *label_17;
    QLineEdit *aff_reste;
    QFrame *qrPanelFrame;
    QVBoxLayout *qrPanelLayout;
    QLabel *labQrTitle;
    QLabel *labQrDisplay;
    QLabel *labQrHint;
    QLabel *labQrUrl;
    QSpacerItem *spacerItem15;
    QHBoxLayout *affichierLBtnRow;
    QPushButton *btnPaiementLab;
    QPushButton *BtnExportLabsDirect;
    QSpacerItem *affichierLBtnSpacer;
    QPushButton *retour_stat_3;
    QWidget *mapsL;
    QWidget *labReserveProduct;
    QLabel *lblLabReserveTitle;
    QLabel *lblLabReserveHint;
    QTableWidget *TableLabReserveProducts;
    QLabel *lblLabReserveQty;
    QSpinBox *spinLabReserveQty;
    QPushButton *btnLabReserveValidate;
    QPushButton *btnLabReserveBack;
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
    QPushButton *btnFiltrerDateProj;
    QLabel *lblCategorieProj;
    QLabel *lblPeriodeDuProj;
    QTableWidget *tableProjets;
    QHBoxLayout *horizontalLayoutProjBottom;
    QPushButton *btnAjouterProj;
    QPushButton *btnModifierProj;
    QPushButton *btnSupprimerProj;
    QPushButton *btnSmsProj;
    QSpacerItem *horizontalSpacerProjBottom;
    QPushButton *btnVoirStatistiquesProj;
    QPushButton *btnExportPdfProj;
    QWidget *page_proj_add;
    QGridLayout *gridLayoutProjAdd;
    QHBoxLayout *hLayoutAddButtonsProj;
    QSpacerItem *spacerAddButtonsProj;
    QPushButton *btnAddProj;
    QPushButton *btnRetourAddProj;
    QComboBox *lineResumeAddProj;
    QLabel *lblTypeBrevetAddProj;
    QLabel *lblDomaineAddProj;
    QLabel *lblStatusBrevetAddProj;
    QLabel *lblResumeAddProj;
    QLabel *lblDateDepotAddProj;
    QLineEdit *lineTitreAddProj;
    QLabel *lblNumeroBrevetAddProj;
    QLineEdit *lineDomaineAddProj;
    QComboBox *lineInventeursAddProj;
    QLabel *lblTitreAddProj;
    QLabel *lblInventeursAddProj;
    QDateEdit *dateEdit;
    QDateEdit *dateEdit_2;
    QLineEdit *lineEdit;
    QDateEdit *dateEdit_3;
    QWidget *page_proj_edit;
    QGridLayout *gridLayoutProjEdit;
    QLabel *lblInventeursEditProj;
    QLineEdit *lineTitreEditProj;
    QLabel *lblTypeBrevetEditProj;
    QComboBox *lineResumeEditProj;
    QLabel *lblDomaineEditProj;
    QLabel *lblResumeEditProj;
    QHBoxLayout *hLayoutEditButtonsProj;
    QSpacerItem *spacerEditButtonsProj;
    QPushButton *btnConfirmEditProj;
    QPushButton *btnRetourEditProj;
    QComboBox *lineInventeursEditProj;
    QLabel *lblDateDepotEditProj;
    QLabel *lblTitreEditProj;
    QLabel *lblStatusBrevetEditProj;
    QLineEdit *lineDomaineEditProj;
    QLabel *lblNumeroBrevetEditProj;
    QDateEdit *dateEdit_4;
    QDateEdit *dateEdit_5;
    QLineEdit *lineEdit_2;
    QDateEdit *dateEdit_6;
    QWidget *page_proj_empty;
    QVBoxLayout *verticalLayoutProjEmpty;
    QLabel *lblStatsTitleProj;
    QHBoxLayout *hLayoutProjStats;
    QWidget *statsWidgetProjStatus;
    QWidget *statsWidgetProjPrio;
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

        btnThemeToggle = new QPushButton(sidebarFrame);
        btnThemeToggle->setObjectName("btnThemeToggle");

        verticalLayoutSidebar->addWidget(btnThemeToggle);

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
        lblPageTitle->setGeometry(QRect(390, 10, 191, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Vivaldi")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        lblPageTitle->setFont(font);
        lblPageTitle->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        btnNotif = new QPushButton(topBar);
        btnNotif->setObjectName("btnNotif");
        btnNotif->setGeometry(QRect(1140, 20, 75, 24));
        btnNotif->setStyleSheet(QString::fromUtf8("border: none; font-weight: bold; color: #333;"));

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

        btnTrier_emp = new QPushButton(page_Emp);
        btnTrier_emp->setObjectName("btnTrier_emp");

        gridLayout_4->addWidget(btnTrier_emp, 0, 3, 1, 1);

        btnModifier_emp = new QPushButton(page_Emp);
        btnModifier_emp->setObjectName("btnModifier_emp");

        gridLayout_4->addWidget(btnModifier_emp, 4, 1, 1, 1);

        pointage = new QPushButton(page_Emp);
        pointage->setObjectName("pointage");

        gridLayout_4->addWidget(pointage, 0, 2, 1, 1);

        btnAjouterEmp = new QPushButton(page_Emp);
        btnAjouterEmp->setObjectName("btnAjouterEmp");

        gridLayout_4->addWidget(btnAjouterEmp, 4, 0, 1, 1);

        TableEmp = new QTableWidget(page_Emp);
        if (TableEmp->columnCount() < 10)
            TableEmp->setColumnCount(10);
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
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        TableEmp->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (TableEmp->rowCount() < 9)
            TableEmp->setRowCount(9);
        TableEmp->setObjectName("TableEmp");
        TableEmp->setMinimumSize(QSize(0, 280));
        TableEmp->setRowCount(9);
        TableEmp->setColumnCount(10);

        gridLayout_4->addWidget(TableEmp, 1, 0, 1, 4);

        btnSupprimer_emp = new QPushButton(page_Emp);
        btnSupprimer_emp->setObjectName("btnSupprimer_emp");

        gridLayout_4->addWidget(btnSupprimer_emp, 4, 2, 1, 1);

        btnStat_emp = new QPushButton(page_Emp);
        btnStat_emp->setObjectName("btnStat_emp");

        gridLayout_4->addWidget(btnStat_emp, 4, 3, 1, 1);

        stack_emp->addWidget(page_Emp);
        page_add_Emp = new QWidget();
        page_add_Emp->setObjectName("page_add_Emp");
        addEmpLayout = new QVBoxLayout(page_add_Emp);
        addEmpLayout->setSpacing(14);
        addEmpLayout->setObjectName("addEmpLayout");
        addEmpLayout->setContentsMargins(20, 12, 20, 12);
        addEmpTitleRow = new QHBoxLayout();
        addEmpTitleRow->setObjectName("addEmpTitleRow");
        lblAddEmpTitle = new QLabel(page_add_Emp);
        lblAddEmpTitle->setObjectName("lblAddEmpTitle");
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        lblAddEmpTitle->setFont(font1);
        lblAddEmpTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        addEmpTitleRow->addWidget(lblAddEmpTitle);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        addEmpTitleRow->addItem(spacerItem);

        BtnPopupCancelLabs_8 = new QToolButton(page_add_Emp);
        BtnPopupCancelLabs_8->setObjectName("BtnPopupCancelLabs_8");

        addEmpTitleRow->addWidget(BtnPopupCancelLabs_8);


        addEmpLayout->addLayout(addEmpTitleRow);

        groupBox_2 = new QGroupBox(page_add_Emp);
        groupBox_2->setObjectName("groupBox_2");
        addEmpGrid = new QGridLayout(groupBox_2);
        addEmpGrid->setSpacing(10);
        addEmpGrid->setObjectName("addEmpGrid");
        addEmpGrid->setContentsMargins(16, 16, 16, 16);
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setMinimumSize(QSize(100, 0));

        addEmpGrid->addWidget(label, 0, 0, 1, 1);

        lineCINAdd = new QLineEdit(groupBox_2);
        lineCINAdd->setObjectName("lineCINAdd");
        lineCINAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(lineCINAdd, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(100, 0));

        addEmpGrid->addWidget(label_8, 0, 2, 1, 1);

        comboDepartementAdd = new QComboBox(groupBox_2);
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->addItem(QString());
        comboDepartementAdd->setObjectName("comboDepartementAdd");
        comboDepartementAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(comboDepartementAdd, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        addEmpGrid->addWidget(label_2, 1, 0, 1, 1);

        lineUsernameAdd = new QLineEdit(groupBox_2);
        lineUsernameAdd->setObjectName("lineUsernameAdd");
        lineUsernameAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(lineUsernameAdd, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");

        addEmpGrid->addWidget(label_7, 1, 2, 1, 1);

        comboPosteAdd = new QComboBox(groupBox_2);
        comboPosteAdd->addItem(QString());
        comboPosteAdd->addItem(QString());
        comboPosteAdd->addItem(QString());
        comboPosteAdd->addItem(QString());
        comboPosteAdd->addItem(QString());
        comboPosteAdd->addItem(QString());
        comboPosteAdd->addItem(QString());
        comboPosteAdd->setObjectName("comboPosteAdd");
        comboPosteAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(comboPosteAdd, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        addEmpGrid->addWidget(label_3, 2, 0, 1, 1);

        passwordRow = new QHBoxLayout();
        passwordRow->setSpacing(6);
        passwordRow->setObjectName("passwordRow");
        linePasswordAdd = new QLineEdit(groupBox_2);
        linePasswordAdd->setObjectName("linePasswordAdd");
        linePasswordAdd->setMinimumSize(QSize(0, 36));

        passwordRow->addWidget(linePasswordAdd);

        passwordStrengthBarAdd = new QProgressBar(groupBox_2);
        passwordStrengthBarAdd->setObjectName("passwordStrengthBarAdd");
        passwordStrengthBarAdd->setMaximumSize(QSize(90, 16777215));
        passwordStrengthBarAdd->setMaximum(100);
        passwordStrengthBarAdd->setValue(0);
        passwordStrengthBarAdd->setTextVisible(false);

        passwordRow->addWidget(passwordStrengthBarAdd);

        passwordStrengthLabelAdd = new QLabel(groupBox_2);
        passwordStrengthLabelAdd->setObjectName("passwordStrengthLabelAdd");

        passwordRow->addWidget(passwordStrengthLabelAdd);


        addEmpGrid->addLayout(passwordRow, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");

        addEmpGrid->addWidget(label_10, 2, 2, 1, 1);

        dateEmbaucheAdd = new QDateEdit(groupBox_2);
        dateEmbaucheAdd->setObjectName("dateEmbaucheAdd");
        dateEmbaucheAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(dateEmbaucheAdd, 2, 3, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        addEmpGrid->addWidget(label_4, 3, 0, 1, 1);

        lineEmailAdd = new QLineEdit(groupBox_2);
        lineEmailAdd->setObjectName("lineEmailAdd");
        lineEmailAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(lineEmailAdd, 3, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");

        addEmpGrid->addWidget(label_11, 3, 2, 1, 1);

        lineSalaireAdd = new QLineEdit(groupBox_2);
        lineSalaireAdd->setObjectName("lineSalaireAdd");
        lineSalaireAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(lineSalaireAdd, 3, 3, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        addEmpGrid->addWidget(label_5, 4, 0, 1, 1);

        lineNomAdd = new QLineEdit(groupBox_2);
        lineNomAdd->setObjectName("lineNomAdd");
        lineNomAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(lineNomAdd, 4, 1, 1, 1);

        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName("label_25");

        addEmpGrid->addWidget(label_25, 4, 2, 1, 1);

        btnScanFace = new QPushButton(groupBox_2);
        btnScanFace->setObjectName("btnScanFace");
        btnScanFace->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(btnScanFace, 4, 3, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        addEmpGrid->addWidget(label_6, 5, 0, 1, 1);

        linePrenomAdd = new QLineEdit(groupBox_2);
        linePrenomAdd->setObjectName("linePrenomAdd");
        linePrenomAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(linePrenomAdd, 5, 1, 1, 1);

        label_cam = new QLabel(groupBox_2);
        label_cam->setObjectName("label_cam");
        label_cam->setAlignment(Qt::AlignmentFlag::AlignCenter);

        addEmpGrid->addWidget(label_cam, 5, 2, 1, 2);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");

        addEmpGrid->addWidget(label_12, 6, 0, 1, 1);

        comboRoleAdd = new QComboBox(groupBox_2);
        comboRoleAdd->addItem(QString());
        comboRoleAdd->addItem(QString());
        comboRoleAdd->addItem(QString());
        comboRoleAdd->addItem(QString());
        comboRoleAdd->addItem(QString());
        comboRoleAdd->addItem(QString());
        comboRoleAdd->addItem(QString());
        comboRoleAdd->setObjectName("comboRoleAdd");
        comboRoleAdd->setMinimumSize(QSize(0, 36));

        addEmpGrid->addWidget(comboRoleAdd, 6, 1, 1, 1);

        addEmpGrid->setColumnStretch(1, 1);
        addEmpGrid->setColumnStretch(3, 1);

        addEmpLayout->addWidget(groupBox_2);

        addEmpBtnRow = new QHBoxLayout();
        addEmpBtnRow->setSpacing(12);
        addEmpBtnRow->setObjectName("addEmpBtnRow");
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        addEmpBtnRow->addItem(spacerItem1);

        btnSaveEmployee = new QPushButton(page_add_Emp);
        btnSaveEmployee->setObjectName("btnSaveEmployee");
        btnSaveEmployee->setMinimumSize(QSize(160, 38));

        addEmpBtnRow->addWidget(btnSaveEmployee);

        btnAnnuler_emp = new QPushButton(page_add_Emp);
        btnAnnuler_emp->setObjectName("btnAnnuler_emp");
        btnAnnuler_emp->setMinimumSize(QSize(160, 38));

        addEmpBtnRow->addWidget(btnAnnuler_emp);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        addEmpBtnRow->addItem(spacerItem2);


        addEmpLayout->addLayout(addEmpBtnRow);

        stack_emp->addWidget(page_add_Emp);
        page_Edit_Emp = new QWidget();
        page_Edit_Emp->setObjectName("page_Edit_Emp");
        editEmpLayout = new QVBoxLayout(page_Edit_Emp);
        editEmpLayout->setSpacing(14);
        editEmpLayout->setObjectName("editEmpLayout");
        editEmpLayout->setContentsMargins(20, 12, 20, 12);
        editEmpTitleRow = new QHBoxLayout();
        editEmpTitleRow->setObjectName("editEmpTitleRow");
        lblEditEmpTitle = new QLabel(page_Edit_Emp);
        lblEditEmpTitle->setObjectName("lblEditEmpTitle");
        lblEditEmpTitle->setFont(font1);
        lblEditEmpTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        editEmpTitleRow->addWidget(lblEditEmpTitle);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        editEmpTitleRow->addItem(spacerItem3);

        BtnPopupCancelLabs_10 = new QToolButton(page_Edit_Emp);
        BtnPopupCancelLabs_10->setObjectName("BtnPopupCancelLabs_10");

        editEmpTitleRow->addWidget(BtnPopupCancelLabs_10);


        editEmpLayout->addLayout(editEmpTitleRow);

        groupBox_6 = new QGroupBox(page_Edit_Emp);
        groupBox_6->setObjectName("groupBox_6");
        editEmpGrid = new QGridLayout(groupBox_6);
        editEmpGrid->setSpacing(10);
        editEmpGrid->setObjectName("editEmpGrid");
        editEmpGrid->setContentsMargins(16, 16, 16, 16);
        labelCINEdit_3 = new QLabel(groupBox_6);
        labelCINEdit_3->setObjectName("labelCINEdit_3");
        labelCINEdit_3->setMinimumSize(QSize(100, 0));

        editEmpGrid->addWidget(labelCINEdit_3, 0, 0, 1, 1);

        lineCIN_emp = new QLineEdit(groupBox_6);
        lineCIN_emp->setObjectName("lineCIN_emp");
        lineCIN_emp->setMinimumSize(QSize(0, 36));
        lineCIN_emp->setReadOnly(true);

        editEmpGrid->addWidget(lineCIN_emp, 0, 1, 1, 1);

        labelDateEmbaucheEdit_3 = new QLabel(groupBox_6);
        labelDateEmbaucheEdit_3->setObjectName("labelDateEmbaucheEdit_3");
        labelDateEmbaucheEdit_3->setMinimumSize(QSize(100, 0));

        editEmpGrid->addWidget(labelDateEmbaucheEdit_3, 0, 2, 1, 1);

        dateEmbaucheEmp = new QDateEdit(groupBox_6);
        dateEmbaucheEmp->setObjectName("dateEmbaucheEmp");
        dateEmbaucheEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(dateEmbaucheEmp, 0, 3, 1, 1);

        labelUsernameEdit_3 = new QLabel(groupBox_6);
        labelUsernameEdit_3->setObjectName("labelUsernameEdit_3");

        editEmpGrid->addWidget(labelUsernameEdit_3, 1, 0, 1, 1);

        lineUsernameEmp = new QLineEdit(groupBox_6);
        lineUsernameEmp->setObjectName("lineUsernameEmp");
        lineUsernameEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(lineUsernameEmp, 1, 1, 1, 1);

        labelSalaireEdit_3 = new QLabel(groupBox_6);
        labelSalaireEdit_3->setObjectName("labelSalaireEdit_3");

        editEmpGrid->addWidget(labelSalaireEdit_3, 1, 2, 1, 1);

        lineSalaireEmp = new QLineEdit(groupBox_6);
        lineSalaireEmp->setObjectName("lineSalaireEmp");
        lineSalaireEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(lineSalaireEmp, 1, 3, 1, 1);

        labelEmailEdit_3 = new QLabel(groupBox_6);
        labelEmailEdit_3->setObjectName("labelEmailEdit_3");

        editEmpGrid->addWidget(labelEmailEdit_3, 2, 0, 1, 1);

        lineEmailEmp = new QLineEdit(groupBox_6);
        lineEmailEmp->setObjectName("lineEmailEmp");
        lineEmailEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(lineEmailEmp, 2, 1, 1, 1);

        labelPosteEdit_3 = new QLabel(groupBox_6);
        labelPosteEdit_3->setObjectName("labelPosteEdit_3");

        editEmpGrid->addWidget(labelPosteEdit_3, 2, 2, 1, 1);

        comboPosteEmp = new QComboBox(groupBox_6);
        comboPosteEmp->addItem(QString());
        comboPosteEmp->addItem(QString());
        comboPosteEmp->addItem(QString());
        comboPosteEmp->addItem(QString());
        comboPosteEmp->addItem(QString());
        comboPosteEmp->addItem(QString());
        comboPosteEmp->addItem(QString());
        comboPosteEmp->setObjectName("comboPosteEmp");
        comboPosteEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(comboPosteEmp, 2, 3, 1, 1);

        labelNomEdit_3 = new QLabel(groupBox_6);
        labelNomEdit_3->setObjectName("labelNomEdit_3");

        editEmpGrid->addWidget(labelNomEdit_3, 3, 0, 1, 1);

        lineNomEmp = new QLineEdit(groupBox_6);
        lineNomEmp->setObjectName("lineNomEmp");
        lineNomEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(lineNomEmp, 3, 1, 1, 1);

        labelDepartementEdit_3 = new QLabel(groupBox_6);
        labelDepartementEdit_3->setObjectName("labelDepartementEdit_3");

        editEmpGrid->addWidget(labelDepartementEdit_3, 3, 2, 1, 1);

        comboDepartementEmp = new QComboBox(groupBox_6);
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->addItem(QString());
        comboDepartementEmp->setObjectName("comboDepartementEmp");
        comboDepartementEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(comboDepartementEmp, 3, 3, 1, 1);

        labelPrenomEdit_3 = new QLabel(groupBox_6);
        labelPrenomEdit_3->setObjectName("labelPrenomEdit_3");

        editEmpGrid->addWidget(labelPrenomEdit_3, 4, 0, 1, 1);

        linePrenomEmp = new QLineEdit(groupBox_6);
        linePrenomEmp->setObjectName("linePrenomEmp");
        linePrenomEmp->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(linePrenomEmp, 4, 1, 1, 1);

        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName("label_13");

        editEmpGrid->addWidget(label_13, 4, 2, 1, 1);

        comboRoleAdd_2 = new QComboBox(groupBox_6);
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->addItem(QString());
        comboRoleAdd_2->setObjectName("comboRoleAdd_2");
        comboRoleAdd_2->setMinimumSize(QSize(0, 36));

        editEmpGrid->addWidget(comboRoleAdd_2, 4, 3, 1, 1);

        editEmpGrid->setColumnStretch(1, 1);
        editEmpGrid->setColumnStretch(3, 1);

        editEmpLayout->addWidget(groupBox_6);

        editEmpBtnRow = new QHBoxLayout();
        editEmpBtnRow->setSpacing(12);
        editEmpBtnRow->setObjectName("editEmpBtnRow");
        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        editEmpBtnRow->addItem(spacerItem4);

        btnSaveEditEmployee = new QPushButton(page_Edit_Emp);
        btnSaveEditEmployee->setObjectName("btnSaveEditEmployee");
        btnSaveEditEmployee->setMinimumSize(QSize(200, 38));

        editEmpBtnRow->addWidget(btnSaveEditEmployee);

        btnCancelEditEmp = new QPushButton(page_Edit_Emp);
        btnCancelEditEmp->setObjectName("btnCancelEditEmp");
        btnCancelEditEmp->setMinimumSize(QSize(160, 38));

        editEmpBtnRow->addWidget(btnCancelEditEmp);

        spacerItem5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        editEmpBtnRow->addItem(spacerItem5);


        editEmpLayout->addLayout(editEmpBtnRow);

        stack_emp->addWidget(page_Edit_Emp);
        page_Stat = new QWidget();
        page_Stat->setObjectName("page_Stat");
        statEmpLayout = new QVBoxLayout(page_Stat);
        statEmpLayout->setSpacing(8);
        statEmpLayout->setObjectName("statEmpLayout");
        statEmpLayout->setContentsMargins(16, 8, 16, 8);
        statEmpTitleRow = new QHBoxLayout();
        statEmpTitleRow->setObjectName("statEmpTitleRow");
        spacerItem6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statEmpTitleRow->addItem(spacerItem6);

        BtnPopupCancelLabs_9 = new QToolButton(page_Stat);
        BtnPopupCancelLabs_9->setObjectName("BtnPopupCancelLabs_9");

        statEmpTitleRow->addWidget(BtnPopupCancelLabs_9);


        statEmpLayout->addLayout(statEmpTitleRow);

        groupBox = new QGroupBox(page_Stat);
        groupBox->setObjectName("groupBox");
        statGroupLayout = new QVBoxLayout(groupBox);
        statGroupLayout->setSpacing(0);
        statGroupLayout->setObjectName("statGroupLayout");

        statEmpLayout->addWidget(groupBox);

        stack_emp->addWidget(page_Stat);
        page_conge = new QWidget();
        page_conge->setObjectName("page_conge");
        congeLayout = new QVBoxLayout(page_conge);
        congeLayout->setSpacing(12);
        congeLayout->setObjectName("congeLayout");
        congeLayout->setContentsMargins(16, 8, 16, 12);
        congeTitleRow = new QHBoxLayout();
        congeTitleRow->setObjectName("congeTitleRow");
        spacerItem7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        congeTitleRow->addItem(spacerItem7);

        BtnPopupCancelLabs_7 = new QToolButton(page_conge);
        BtnPopupCancelLabs_7->setObjectName("BtnPopupCancelLabs_7");

        congeTitleRow->addWidget(BtnPopupCancelLabs_7);


        congeLayout->addLayout(congeTitleRow);

        groupBox_3 = new QGroupBox(page_conge);
        groupBox_3->setObjectName("groupBox_3");
        congeGroupLayout = new QVBoxLayout(groupBox_3);
        congeGroupLayout->setSpacing(12);
        congeGroupLayout->setObjectName("congeGroupLayout");
        TableCongeEmp = new QTableWidget(groupBox_3);
        if (TableCongeEmp->columnCount() < 6)
            TableCongeEmp->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        TableCongeEmp->setHorizontalHeaderItem(5, __qtablewidgetitem15);
        if (TableCongeEmp->rowCount() < 30)
            TableCongeEmp->setRowCount(30);
        TableCongeEmp->setObjectName("TableCongeEmp");
        TableCongeEmp->setMinimumSize(QSize(0, 280));
        TableCongeEmp->setRowCount(30);
        TableCongeEmp->setColumnCount(6);

        congeGroupLayout->addWidget(TableCongeEmp);

        congeBtnRow = new QHBoxLayout();
        congeBtnRow->setSpacing(12);
        congeBtnRow->setObjectName("congeBtnRow");
        spacerItem8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        congeBtnRow->addItem(spacerItem8);

        Accepter_conge_Emp = new QPushButton(groupBox_3);
        Accepter_conge_Emp->setObjectName("Accepter_conge_Emp");
        Accepter_conge_Emp->setMinimumSize(QSize(160, 38));

        congeBtnRow->addWidget(Accepter_conge_Emp);

        Rejeter_conge_Emp = new QPushButton(groupBox_3);
        Rejeter_conge_Emp->setObjectName("Rejeter_conge_Emp");
        Rejeter_conge_Emp->setMinimumSize(QSize(160, 38));

        congeBtnRow->addWidget(Rejeter_conge_Emp);

        spacerItem9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        congeBtnRow->addItem(spacerItem9);


        congeGroupLayout->addLayout(congeBtnRow);


        congeLayout->addWidget(groupBox_3);

        stack_emp->addWidget(page_conge);
        page_formation = new QWidget();
        page_formation->setObjectName("page_formation");
        formationLayout = new QVBoxLayout(page_formation);
        formationLayout->setSpacing(12);
        formationLayout->setObjectName("formationLayout");
        formationLayout->setContentsMargins(16, 8, 16, 12);
        formationTitleRow = new QHBoxLayout();
        formationTitleRow->setObjectName("formationTitleRow");
        spacerItem10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formationTitleRow->addItem(spacerItem10);

        BtnPopupCancelLabs_6 = new QToolButton(page_formation);
        BtnPopupCancelLabs_6->setObjectName("BtnPopupCancelLabs_6");

        formationTitleRow->addWidget(BtnPopupCancelLabs_6);


        formationLayout->addLayout(formationTitleRow);

        groupBox_4 = new QGroupBox(page_formation);
        groupBox_4->setObjectName("groupBox_4");
        formationGroupLayout = new QVBoxLayout(groupBox_4);
        formationGroupLayout->setSpacing(12);
        formationGroupLayout->setObjectName("formationGroupLayout");
        TableFormations_Emp = new QTableWidget(groupBox_4);
        if (TableFormations_Emp->columnCount() < 8)
            TableFormations_Emp->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(5, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(6, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        TableFormations_Emp->setHorizontalHeaderItem(7, __qtablewidgetitem23);
        if (TableFormations_Emp->rowCount() < 9)
            TableFormations_Emp->setRowCount(9);
        TableFormations_Emp->setObjectName("TableFormations_Emp");
        TableFormations_Emp->setMinimumSize(QSize(0, 280));
        TableFormations_Emp->setRowCount(9);
        TableFormations_Emp->setColumnCount(8);

        formationGroupLayout->addWidget(TableFormations_Emp);

        formationBtnRow = new QHBoxLayout();
        formationBtnRow->setSpacing(12);
        formationBtnRow->setObjectName("formationBtnRow");
        spacerItem11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formationBtnRow->addItem(spacerItem11);

        Modifier_Formations_Emp = new QPushButton(groupBox_4);
        Modifier_Formations_Emp->setObjectName("Modifier_Formations_Emp");
        Modifier_Formations_Emp->setMinimumSize(QSize(160, 38));

        formationBtnRow->addWidget(Modifier_Formations_Emp);

        Exporter_Formations_Emp = new QPushButton(groupBox_4);
        Exporter_Formations_Emp->setObjectName("Exporter_Formations_Emp");
        Exporter_Formations_Emp->setMinimumSize(QSize(200, 38));

        formationBtnRow->addWidget(Exporter_Formations_Emp);

        spacerItem12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formationBtnRow->addItem(spacerItem12);


        formationGroupLayout->addLayout(formationBtnRow);


        formationLayout->addWidget(groupBox_4);

        stack_emp->addWidget(page_formation);
        page = new QWidget();
        page->setObjectName("page");
        pointageLayout = new QVBoxLayout(page);
        pointageLayout->setSpacing(10);
        pointageLayout->setObjectName("pointageLayout");
        pointageLayout->setContentsMargins(16, 8, 16, 12);
        pointageTitleRow = new QHBoxLayout();
        pointageTitleRow->setObjectName("pointageTitleRow");
        label_15 = new QLabel(page);
        label_15->setObjectName("label_15");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(15);
        font2.setWeight(QFont::DemiBold);
        label_15->setFont(font2);

        pointageTitleRow->addWidget(label_15);

        spacerItem13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        pointageTitleRow->addItem(spacerItem13);

        btn_ret = new QToolButton(page);
        btn_ret->setObjectName("btn_ret");

        pointageTitleRow->addWidget(btn_ret);


        pointageLayout->addLayout(pointageTitleRow);

        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName("groupBox_5");
        pointageGroupLayout = new QVBoxLayout(groupBox_5);
        pointageGroupLayout->setSpacing(10);
        pointageGroupLayout->setObjectName("pointageGroupLayout");
        frame = new QFrame(groupBox_5);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        pointageFrameLayout = new QVBoxLayout(frame);
        pointageFrameLayout->setSpacing(8);
        pointageFrameLayout->setObjectName("pointageFrameLayout");
        pointageFrameLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(frame);
        tableView->setObjectName("tableView");
        tableView->setMinimumSize(QSize(0, 300));

        pointageFrameLayout->addWidget(tableView);

        pointageBadgeRow = new QHBoxLayout();
        pointageBadgeRow->setSpacing(10);
        pointageBadgeRow->setObjectName("pointageBadgeRow");
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        QFont font3;
        font3.setPointSize(13);
        label_9->setFont(font3);

        pointageBadgeRow->addWidget(label_9);

        input_badge = new QLineEdit(frame);
        input_badge->setObjectName("input_badge");
        input_badge->setMinimumSize(QSize(0, 44));

        pointageBadgeRow->addWidget(input_badge);

        btn_reset = new QPushButton(frame);
        btn_reset->setObjectName("btn_reset");
        btn_reset->setMinimumSize(QSize(140, 44));

        pointageBadgeRow->addWidget(btn_reset);

        btn_exportt = new QPushButton(frame);
        btn_exportt->setObjectName("btn_exportt");
        btn_exportt->setMinimumSize(QSize(140, 44));

        pointageBadgeRow->addWidget(btn_exportt);


        pointageFrameLayout->addLayout(pointageBadgeRow);


        pointageGroupLayout->addWidget(frame);

        label_feedback = new QLabel(groupBox_5);
        label_feedback->setObjectName("label_feedback");
        label_feedback->setAlignment(Qt::AlignmentFlag::AlignCenter);

        pointageGroupLayout->addWidget(label_feedback);


        pointageLayout->addWidget(groupBox_5);

        stack_emp->addWidget(page);

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
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(3, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(4, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(5, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(6, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(7, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(8, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(9, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(10, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        TableInventory->setHorizontalHeaderItem(11, __qtablewidgetitem35);
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

        inventoryFilterGrid->addWidget(BtnInventoryApply, 1, 5, 1, 1);

        BtnInventoryReset = new QPushButton(InventoryCardFilter);
        BtnInventoryReset->setObjectName("BtnInventoryReset");

        inventoryFilterGrid->addWidget(BtnInventoryReset, 1, 6, 1, 1);

        InventoryZone = new QComboBox(InventoryCardFilter);
        InventoryZone->addItem(QString());
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

        LblInventorySort = new QLabel(InventoryCardFilter);
        LblInventorySort->setObjectName("LblInventorySort");

        inventoryFilterGrid->addWidget(LblInventorySort, 0, 4, 1, 1);

        InventorySort = new QComboBox(InventoryCardFilter);
        InventorySort->addItem(QString());
        InventorySort->addItem(QString());
        InventorySort->addItem(QString());
        InventorySort->addItem(QString());
        InventorySort->setObjectName("InventorySort");

        inventoryFilterGrid->addWidget(InventorySort, 1, 4, 1, 1);


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

        LblDescription = new QLabel(PopupInventoryForm);
        LblDescription->setObjectName("LblDescription");

        inventoryFormGrid->addWidget(LblDescription, 6, 0, 1, 1);

        Description = new QTextEdit(PopupInventoryForm);
        Description->setObjectName("Description");

        inventoryFormGrid->addWidget(Description, 6, 1, 1, 3);


        popupInventoryLayout->addWidget(PopupInventoryForm);

        popupInventoryActions = new QHBoxLayout();
        popupInventoryActions->setObjectName("popupInventoryActions");
        popupInventoryActionsLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        popupInventoryActions->addItem(popupInventoryActionsLeft);

        BtnPopupAutoSaveInventory = new QPushButton(PopupInventoryCard);
        BtnPopupAutoSaveInventory->setObjectName("BtnPopupAutoSaveInventory");

        popupInventoryActions->addWidget(BtnPopupAutoSaveInventory);

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

        LblDescription_2 = new QLabel(PopupInventoryForm_2);
        LblDescription_2->setObjectName("LblDescription_2");

        inventoryFormGrid_2->addWidget(LblDescription_2, 6, 0, 1, 1);

        Description_2 = new QTextEdit(PopupInventoryForm_2);
        Description_2->setObjectName("Description_2");

        inventoryFormGrid_2->addWidget(Description_2, 6, 1, 1, 3);


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
        detailInventoryRootLayout = new QVBoxLayout(afficheri);
        detailInventoryRootLayout->setSpacing(20);
        detailInventoryRootLayout->setObjectName("detailInventoryRootLayout");
        detailInventoryRootLayout->setContentsMargins(30, 30, 30, 30);
        detailHeaderLayout = new QHBoxLayout();
        detailHeaderLayout->setObjectName("detailHeaderLayout");
        aff_header_title = new QLabel(afficheri);
        aff_header_title->setObjectName("aff_header_title");

        detailHeaderLayout->addWidget(aff_header_title);

        hSpacerDetailHeader = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        detailHeaderLayout->addItem(hSpacerDetailHeader);

        retour_stat_6 = new QPushButton(afficheri);
        retour_stat_6->setObjectName("retour_stat_6");

        detailHeaderLayout->addWidget(retour_stat_6);


        detailInventoryRootLayout->addLayout(detailHeaderLayout);

        detailCardsLayout = new QHBoxLayout();
        detailCardsLayout->setSpacing(20);
        detailCardsLayout->setObjectName("detailCardsLayout");
        CardGeneral = new QFrame(afficheri);
        CardGeneral->setObjectName("CardGeneral");
        formGeneral = new QFormLayout(CardGeneral);
        formGeneral->setObjectName("formGeneral");
        formGeneral->setVerticalSpacing(12);
        lbl_g1 = new QLabel(CardGeneral);
        lbl_g1->setObjectName("lbl_g1");

        formGeneral->setWidget(0, QFormLayout::LabelRole, lbl_g1);

        aff_id = new QLabel(CardGeneral);
        aff_id->setObjectName("aff_id");

        formGeneral->setWidget(0, QFormLayout::FieldRole, aff_id);

        lbl_g2 = new QLabel(CardGeneral);
        lbl_g2->setObjectName("lbl_g2");

        formGeneral->setWidget(1, QFormLayout::LabelRole, lbl_g2);

        aff_sku = new QLabel(CardGeneral);
        aff_sku->setObjectName("aff_sku");

        formGeneral->setWidget(1, QFormLayout::FieldRole, aff_sku);

        lbl_g3 = new QLabel(CardGeneral);
        lbl_g3->setObjectName("lbl_g3");

        formGeneral->setWidget(2, QFormLayout::LabelRole, lbl_g3);

        aff_name = new QLabel(CardGeneral);
        aff_name->setObjectName("aff_name");

        formGeneral->setWidget(2, QFormLayout::FieldRole, aff_name);

        lbl_g4 = new QLabel(CardGeneral);
        lbl_g4->setObjectName("lbl_g4");

        formGeneral->setWidget(3, QFormLayout::LabelRole, lbl_g4);

        aff_type = new QLabel(CardGeneral);
        aff_type->setObjectName("aff_type");

        formGeneral->setWidget(3, QFormLayout::FieldRole, aff_type);

        lbl_g5 = new QLabel(CardGeneral);
        lbl_g5->setObjectName("lbl_g5");

        formGeneral->setWidget(4, QFormLayout::LabelRole, lbl_g5);

        aff_price = new QLabel(CardGeneral);
        aff_price->setObjectName("aff_price");

        formGeneral->setWidget(4, QFormLayout::FieldRole, aff_price);

        lbl_g6 = new QLabel(CardGeneral);
        lbl_g6->setObjectName("lbl_g6");

        formGeneral->setWidget(5, QFormLayout::LabelRole, lbl_g6);

        aff_status = new QLabel(CardGeneral);
        aff_status->setObjectName("aff_status");

        formGeneral->setWidget(5, QFormLayout::FieldRole, aff_status);


        detailCardsLayout->addWidget(CardGeneral);

        CardStock = new QFrame(afficheri);
        CardStock->setObjectName("CardStock");
        formStock = new QFormLayout(CardStock);
        formStock->setObjectName("formStock");
        formStock->setVerticalSpacing(12);
        lbl_s1 = new QLabel(CardStock);
        lbl_s1->setObjectName("lbl_s1");

        formStock->setWidget(0, QFormLayout::LabelRole, lbl_s1);

        aff_qtav = new QLabel(CardStock);
        aff_qtav->setObjectName("aff_qtav");

        formStock->setWidget(0, QFormLayout::FieldRole, aff_qtav);

        lbl_s2 = new QLabel(CardStock);
        lbl_s2->setObjectName("lbl_s2");

        formStock->setWidget(1, QFormLayout::LabelRole, lbl_s2);

        aff_qtrs = new QLabel(CardStock);
        aff_qtrs->setObjectName("aff_qtrs");

        formStock->setWidget(1, QFormLayout::FieldRole, aff_qtrs);

        lbl_s3 = new QLabel(CardStock);
        lbl_s3->setObjectName("lbl_s3");

        formStock->setWidget(2, QFormLayout::LabelRole, lbl_s3);

        aff_threshold = new QLabel(CardStock);
        aff_threshold->setObjectName("aff_threshold");

        formStock->setWidget(2, QFormLayout::FieldRole, aff_threshold);

        lbl_s4 = new QLabel(CardStock);
        lbl_s4->setObjectName("lbl_s4");

        formStock->setWidget(3, QFormLayout::LabelRole, lbl_s4);

        aff_unit = new QLabel(CardStock);
        aff_unit->setObjectName("aff_unit");

        formStock->setWidget(3, QFormLayout::FieldRole, aff_unit);

        lbl_s5 = new QLabel(CardStock);
        lbl_s5->setObjectName("lbl_s5");

        formStock->setWidget(4, QFormLayout::LabelRole, lbl_s5);

        aff_zone = new QLabel(CardStock);
        aff_zone->setObjectName("aff_zone");

        formStock->setWidget(4, QFormLayout::FieldRole, aff_zone);

        lbl_s6 = new QLabel(CardStock);
        lbl_s6->setObjectName("lbl_s6");

        formStock->setWidget(5, QFormLayout::LabelRole, lbl_s6);

        aff_shelf = new QLabel(CardStock);
        aff_shelf->setObjectName("aff_shelf");

        formStock->setWidget(5, QFormLayout::FieldRole, aff_shelf);


        detailCardsLayout->addWidget(CardStock);


        detailInventoryRootLayout->addLayout(detailCardsLayout);

        CardDescription = new QFrame(afficheri);
        CardDescription->setObjectName("CardDescription");
        vLayoutDesc = new QVBoxLayout(CardDescription);
        vLayoutDesc->setObjectName("vLayoutDesc");
        lbl_d1 = new QLabel(CardDescription);
        lbl_d1->setObjectName("lbl_d1");

        vLayoutDesc->addWidget(lbl_d1);

        aff_description = new QLabel(CardDescription);
        aff_description->setObjectName("aff_description");
        aff_description->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        aff_description->setWordWrap(true);

        vLayoutDesc->addWidget(aff_description);


        detailInventoryRootLayout->addWidget(CardDescription);

        detailExportButtonsLayout = new QHBoxLayout();
        detailExportButtonsLayout->setSpacing(10);
        detailExportButtonsLayout->setObjectName("detailExportButtonsLayout");
        BtnInventoryDetailExportPdf = new QPushButton(afficheri);
        BtnInventoryDetailExportPdf->setObjectName("BtnInventoryDetailExportPdf");

        detailExportButtonsLayout->addWidget(BtnInventoryDetailExportPdf);


        detailInventoryRootLayout->addLayout(detailExportButtonsLayout);

        vSpacerDetailBottom = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        detailInventoryRootLayout->addItem(vSpacerDetailBottom);

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
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tablePublication->setHorizontalHeaderItem(7, __qtablewidgetitem43);
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
        btnAppliquerPub = new QPushButton(page_pub_list);
        btnAppliquerPub->setObjectName("btnAppliquerPub");

        gridLayoutPubFilters->addWidget(btnAppliquerPub, 2, 0, 1, 1);

        btnReinitialiserPub = new QPushButton(page_pub_list);
        btnReinitialiserPub->setObjectName("btnReinitialiserPub");

        gridLayoutPubFilters->addWidget(btnReinitialiserPub, 2, 1, 1, 1);

        comboTriPub = new QComboBox(page_pub_list);
        comboTriPub->addItem(QString());
        comboTriPub->addItem(QString());
        comboTriPub->setObjectName("comboTriPub");

        gridLayoutPubFilters->addWidget(comboTriPub, 0, 1, 1, 1);

        lblCategoriePub = new QLabel(page_pub_list);
        lblCategoriePub->setObjectName("lblCategoriePub");

        gridLayoutPubFilters->addWidget(lblCategoriePub, 0, 0, 1, 1);


        verticalLayoutPubList->addLayout(gridLayoutPubFilters);

        comboBox = new QComboBox(page_pub_list);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayoutPubList->addWidget(comboBox);

        horizontalLayoutPubBottom = new QHBoxLayout();
        horizontalLayoutPubBottom->setSpacing(12);
        horizontalLayoutPubBottom->setObjectName("horizontalLayoutPubBottom");
        btnVoirStatistiquesPub = new QPushButton(page_pub_list);
        btnVoirStatistiquesPub->setObjectName("btnVoirStatistiquesPub");

        horizontalLayoutPubBottom->addWidget(btnVoirStatistiquesPub);

        btnChatbotPub = new QPushButton(page_pub_list);
        btnChatbotPub->setObjectName("btnChatbotPub");

        horizontalLayoutPubBottom->addWidget(btnChatbotPub);

        btnMailingPub = new QPushButton(page_pub_list);
        btnMailingPub->setObjectName("btnMailingPub");

        horizontalLayoutPubBottom->addWidget(btnMailingPub);

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
        lblStatusBrevetAdd = new QLabel(page_pub_add);
        lblStatusBrevetAdd->setObjectName("lblStatusBrevetAdd");

        gridLayoutPubAdd->addWidget(lblStatusBrevetAdd, 6, 0, 1, 1);

        lblTitreAdd = new QLabel(page_pub_add);
        lblTitreAdd->setObjectName("lblTitreAdd");

        gridLayoutPubAdd->addWidget(lblTitreAdd, 0, 0, 1, 1);

        lineResumeAdd = new QLineEdit(page_pub_add);
        lineResumeAdd->setObjectName("lineResumeAdd");

        gridLayoutPubAdd->addWidget(lineResumeAdd, 2, 3, 1, 1);

        dateDepotAdd = new QDateEdit(page_pub_add);
        dateDepotAdd->setObjectName("dateDepotAdd");
        dateDepotAdd->setCalendarPopup(true);
        dateDepotAdd->setDate(QDate(2000, 1, 1));

        gridLayoutPubAdd->addWidget(dateDepotAdd, 5, 1, 1, 1);

        comboTypeBrevetAdd = new QComboBox(page_pub_add);
        comboTypeBrevetAdd->addItem(QString());
        comboTypeBrevetAdd->addItem(QString());
        comboTypeBrevetAdd->addItem(QString());
        comboTypeBrevetAdd->setObjectName("comboTypeBrevetAdd");

        gridLayoutPubAdd->addWidget(comboTypeBrevetAdd, 3, 1, 1, 1);

        lblTypeBrevetAdd = new QLabel(page_pub_add);
        lblTypeBrevetAdd->setObjectName("lblTypeBrevetAdd");

        gridLayoutPubAdd->addWidget(lblTypeBrevetAdd, 3, 0, 1, 1);

        lblInventeursAdd = new QLabel(page_pub_add);
        lblInventeursAdd->setObjectName("lblInventeursAdd");

        gridLayoutPubAdd->addWidget(lblInventeursAdd, 0, 2, 1, 1);

        lblDomaineAdd = new QLabel(page_pub_add);
        lblDomaineAdd->setObjectName("lblDomaineAdd");

        gridLayoutPubAdd->addWidget(lblDomaineAdd, 2, 0, 1, 1);

        lineDomaineAdd = new QLineEdit(page_pub_add);
        lineDomaineAdd->setObjectName("lineDomaineAdd");

        gridLayoutPubAdd->addWidget(lineDomaineAdd, 2, 1, 1, 1);

        lblResumeAdd = new QLabel(page_pub_add);
        lblResumeAdd->setObjectName("lblResumeAdd");

        gridLayoutPubAdd->addWidget(lblResumeAdd, 2, 2, 1, 1);

        lblDateDepotAdd = new QLabel(page_pub_add);
        lblDateDepotAdd->setObjectName("lblDateDepotAdd");

        gridLayoutPubAdd->addWidget(lblDateDepotAdd, 5, 0, 1, 1);

        lineNumeroBrevetAdd = new QLineEdit(page_pub_add);
        lineNumeroBrevetAdd->setObjectName("lineNumeroBrevetAdd");

        gridLayoutPubAdd->addWidget(lineNumeroBrevetAdd, 4, 1, 1, 1);

        lblNumeroBrevetAdd = new QLabel(page_pub_add);
        lblNumeroBrevetAdd->setObjectName("lblNumeroBrevetAdd");

        gridLayoutPubAdd->addWidget(lblNumeroBrevetAdd, 4, 0, 1, 1);

        lineTitreAdd = new QLineEdit(page_pub_add);
        lineTitreAdd->setObjectName("lineTitreAdd");

        gridLayoutPubAdd->addWidget(lineTitreAdd, 0, 1, 1, 1);

        comboStatusBrevetAdd = new QComboBox(page_pub_add);
        comboStatusBrevetAdd->addItem(QString());
        comboStatusBrevetAdd->addItem(QString());
        comboStatusBrevetAdd->addItem(QString());
        comboStatusBrevetAdd->addItem(QString());
        comboStatusBrevetAdd->addItem(QString());
        comboStatusBrevetAdd->setObjectName("comboStatusBrevetAdd");

        gridLayoutPubAdd->addWidget(comboStatusBrevetAdd, 6, 1, 1, 1);

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


        gridLayoutPubAdd->addLayout(hLayoutAddButtons, 7, 0, 1, 4);

        lineInventeursAdd = new QComboBox(page_pub_add);
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->addItem(QString());
        lineInventeursAdd->setObjectName("lineInventeursAdd");

        gridLayoutPubAdd->addWidget(lineInventeursAdd, 0, 3, 1, 1);

        stack_pub->addWidget(page_pub_add);
        page_pub_edit = new QWidget();
        page_pub_edit->setObjectName("page_pub_edit");
        gridLayoutPubEdit = new QGridLayout(page_pub_edit);
        gridLayoutPubEdit->setObjectName("gridLayoutPubEdit");
        gridLayoutPubEdit->setHorizontalSpacing(40);
        gridLayoutPubEdit->setVerticalSpacing(20);
        gridLayoutPubEdit->setContentsMargins(60, 28, 60, 28);
        lineNumeroBrevetEdit = new QLineEdit(page_pub_edit);
        lineNumeroBrevetEdit->setObjectName("lineNumeroBrevetEdit");

        gridLayoutPubEdit->addWidget(lineNumeroBrevetEdit, 4, 1, 1, 1);

        lblDateDepotEdit = new QLabel(page_pub_edit);
        lblDateDepotEdit->setObjectName("lblDateDepotEdit");

        gridLayoutPubEdit->addWidget(lblDateDepotEdit, 0, 2, 1, 1);

        lblTypeBrevetEdit = new QLabel(page_pub_edit);
        lblTypeBrevetEdit->setObjectName("lblTypeBrevetEdit");

        gridLayoutPubEdit->addWidget(lblTypeBrevetEdit, 2, 0, 1, 1);

        comboStatusBrevetEdit = new QComboBox(page_pub_edit);
        comboStatusBrevetEdit->addItem(QString());
        comboStatusBrevetEdit->addItem(QString());
        comboStatusBrevetEdit->addItem(QString());
        comboStatusBrevetEdit->addItem(QString());
        comboStatusBrevetEdit->addItem(QString());
        comboStatusBrevetEdit->setObjectName("comboStatusBrevetEdit");

        gridLayoutPubEdit->addWidget(comboStatusBrevetEdit, 1, 3, 1, 1);

        lblResumeEdit = new QLabel(page_pub_edit);
        lblResumeEdit->setObjectName("lblResumeEdit");

        gridLayoutPubEdit->addWidget(lblResumeEdit, 4, 2, 1, 1);

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


        gridLayoutPubEdit->addLayout(hLayoutEditButtons, 6, 0, 1, 4);

        lblStatusBrevetEdit = new QLabel(page_pub_edit);
        lblStatusBrevetEdit->setObjectName("lblStatusBrevetEdit");

        gridLayoutPubEdit->addWidget(lblStatusBrevetEdit, 1, 2, 1, 1);

        comboTypeBrevetEdit = new QComboBox(page_pub_edit);
        comboTypeBrevetEdit->addItem(QString());
        comboTypeBrevetEdit->addItem(QString());
        comboTypeBrevetEdit->addItem(QString());
        comboTypeBrevetEdit->setObjectName("comboTypeBrevetEdit");

        gridLayoutPubEdit->addWidget(comboTypeBrevetEdit, 2, 1, 1, 1);

        lblTitreEdit = new QLabel(page_pub_edit);
        lblTitreEdit->setObjectName("lblTitreEdit");

        gridLayoutPubEdit->addWidget(lblTitreEdit, 0, 0, 1, 1);

        dateDepotEdit = new QDateEdit(page_pub_edit);
        dateDepotEdit->setObjectName("dateDepotEdit");
        dateDepotEdit->setCalendarPopup(true);
        dateDepotEdit->setDate(QDate(2000, 1, 1));

        gridLayoutPubEdit->addWidget(dateDepotEdit, 0, 3, 1, 1);

        lblDomaineEdit = new QLabel(page_pub_edit);
        lblDomaineEdit->setObjectName("lblDomaineEdit");

        gridLayoutPubEdit->addWidget(lblDomaineEdit, 1, 0, 1, 1);

        lineTitreEdit = new QLineEdit(page_pub_edit);
        lineTitreEdit->setObjectName("lineTitreEdit");

        gridLayoutPubEdit->addWidget(lineTitreEdit, 0, 1, 1, 1);

        lineDomaineEdit = new QLineEdit(page_pub_edit);
        lineDomaineEdit->setObjectName("lineDomaineEdit");

        gridLayoutPubEdit->addWidget(lineDomaineEdit, 1, 1, 1, 1);

        lblInventeursEdit = new QLabel(page_pub_edit);
        lblInventeursEdit->setObjectName("lblInventeursEdit");

        gridLayoutPubEdit->addWidget(lblInventeursEdit, 2, 2, 1, 1);

        lineResumeEdit = new QLineEdit(page_pub_edit);
        lineResumeEdit->setObjectName("lineResumeEdit");

        gridLayoutPubEdit->addWidget(lineResumeEdit, 4, 3, 1, 1);

        lblNumeroBrevetEdit = new QLabel(page_pub_edit);
        lblNumeroBrevetEdit->setObjectName("lblNumeroBrevetEdit");

        gridLayoutPubEdit->addWidget(lblNumeroBrevetEdit, 4, 0, 1, 1);

        lineInventeursEdit = new QComboBox(page_pub_edit);
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->addItem(QString());
        lineInventeursEdit->setObjectName("lineInventeursEdit");

        gridLayoutPubEdit->addWidget(lineInventeursEdit, 2, 3, 1, 1);

        stack_pub->addWidget(page_pub_edit);
        page_pub_empty = new QWidget();
        page_pub_empty->setObjectName("page_pub_empty");
        verticalLayoutPubEmpty = new QVBoxLayout(page_pub_empty);
        verticalLayoutPubEmpty->setObjectName("verticalLayoutPubEmpty");
        statsWidgetPub = new QWidget(page_pub_empty);
        statsWidgetPub->setObjectName("statsWidgetPub");

        verticalLayoutPubEmpty->addWidget(statsWidgetPub);

        retour_stat = new QPushButton(page_pub_empty);
        retour_stat->setObjectName("retour_stat");

        verticalLayoutPubEmpty->addWidget(retour_stat);

        stack_pub->addWidget(page_pub_empty);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        formLayout = new QFormLayout(page_2);
        formLayout->setObjectName("formLayout");
        label_14 = new QLabel(page_2);
        label_14->setObjectName("label_14");

        formLayout->setWidget(0, QFormLayout::SpanningRole, label_14);

        textChatPub = new QTextEdit(page_2);
        textChatPub->setObjectName("textChatPub");
        textChatPub->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::SpanningRole, textChatPub);

        lineQuestionPub = new QLineEdit(page_2);
        lineQuestionPub->setObjectName("lineQuestionPub");

        formLayout->setWidget(2, QFormLayout::SpanningRole, lineQuestionPub);

        btnEnvoyerQuestionPub = new QPushButton(page_2);
        btnEnvoyerQuestionPub->setObjectName("btnEnvoyerQuestionPub");

        formLayout->setWidget(3, QFormLayout::LabelRole, btnEnvoyerQuestionPub);

        btnRetourChatbotPub = new QPushButton(page_2);
        btnRetourChatbotPub->setObjectName("btnRetourChatbotPub");

        formLayout->setWidget(4, QFormLayout::LabelRole, btnRetourChatbotPub);

        stack_pub->addWidget(page_2);

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
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Consolas")});
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setUnderline(true);
        DateFrom->setFont(font4);
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
        QFont font5;
        font5.setPointSize(11);
        LblType->setFont(font5);

        filterGrid->addWidget(LblType, 0, 0, 1, 1);

        DateTo = new QDateEdit(CardFilter);
        DateTo->setObjectName("DateTo");
        DateTo->setFont(font4);
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
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(2, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(3, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(4, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(5, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(6, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        TableFinance->setHorizontalHeaderItem(7, __qtablewidgetitem51);
        if (TableFinance->rowCount() < 3)
            TableFinance->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(0, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(1, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        TableFinance->setVerticalHeaderItem(2, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        TableFinance->setItem(0, 0, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        TableFinance->setItem(0, 1, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        TableFinance->setItem(0, 2, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        TableFinance->setItem(0, 3, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        TableFinance->setItem(0, 4, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        TableFinance->setItem(0, 5, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        TableFinance->setItem(0, 6, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        TableFinance->setItem(0, 7, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        TableFinance->setItem(1, 0, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        TableFinance->setItem(1, 1, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        TableFinance->setItem(1, 2, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        TableFinance->setItem(1, 3, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        TableFinance->setItem(1, 4, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        TableFinance->setItem(1, 5, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        TableFinance->setItem(1, 6, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        TableFinance->setItem(1, 7, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        TableFinance->setItem(2, 0, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        TableFinance->setItem(2, 1, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        TableFinance->setItem(2, 2, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        TableFinance->setItem(2, 3, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        TableFinance->setItem(2, 4, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        TableFinance->setItem(2, 5, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        TableFinance->setItem(2, 6, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        TableFinance->setItem(2, 7, __qtablewidgetitem78);
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
        PopupFinanceCard = new QFrame(OverlayFinance);
        PopupFinanceCard->setObjectName("PopupFinanceCard");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PopupFinanceCard->sizePolicy().hasHeightForWidth());
        PopupFinanceCard->setSizePolicy(sizePolicy);
        PopupFinanceCard->setFrameShape(QFrame::Shape::NoFrame);
        popupFinanceCardLayout = new QVBoxLayout(PopupFinanceCard);
        popupFinanceCardLayout->setSpacing(12);
        popupFinanceCardLayout->setObjectName("popupFinanceCardLayout");
        popupFinanceCardLayout->setContentsMargins(16, 16, 16, 16);
        popupFinanceGrid = new QGridLayout();
        popupFinanceGrid->setObjectName("popupFinanceGrid");
        popupFinanceGrid->setHorizontalSpacing(4);
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

        layoutAmountRow = new QHBoxLayout();
        layoutAmountRow->setSpacing(6);
        layoutAmountRow->setObjectName("layoutAmountRow");
        BtnAmountDecr = new QPushButton(PopupFinanceCard);
        BtnAmountDecr->setObjectName("BtnAmountDecr");
        BtnAmountDecr->setMaximumSize(QSize(30, 30));

        layoutAmountRow->addWidget(BtnAmountDecr);

        FormAmount = new QLineEdit(PopupFinanceCard);
        FormAmount->setObjectName("FormAmount");

        layoutAmountRow->addWidget(FormAmount);

        BtnAmountIncr = new QPushButton(PopupFinanceCard);
        BtnAmountIncr->setObjectName("BtnAmountIncr");
        BtnAmountIncr->setMaximumSize(QSize(30, 30));

        layoutAmountRow->addWidget(BtnAmountIncr);

        BtnConvertCurrency = new QPushButton(PopupFinanceCard);
        BtnConvertCurrency->setObjectName("BtnConvertCurrency");
        BtnConvertCurrency->setMinimumSize(QSize(0, 0));
        BtnConvertCurrency->setMaximumSize(QSize(160, 30));
        BtnConvertCurrency->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        layoutAmountRow->addWidget(BtnConvertCurrency);


        popupFinanceGrid->addLayout(layoutAmountRow, 1, 1, 1, 1);

        FormCategory = new QLineEdit(PopupFinanceCard);
        FormCategory->setObjectName("FormCategory");
        FormCategory->setMaximumSize(QSize(150, 16777215));

        popupFinanceGrid->addWidget(FormCategory, 1, 3, 1, 1);

        layoutOcrSection = new QVBoxLayout();
        layoutOcrSection->setSpacing(5);
        layoutOcrSection->setObjectName("layoutOcrSection");
        BtnOcrReceipt = new QPushButton(PopupFinanceCard);
        BtnOcrReceipt->setObjectName("BtnOcrReceipt");
        BtnOcrReceipt->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        layoutOcrSection->addWidget(BtnOcrReceipt);

        LblOcrHint = new QLabel(PopupFinanceCard);
        LblOcrHint->setObjectName("LblOcrHint");
        QFont font6;
        font6.setBold(true);
        font6.setItalic(true);
        LblOcrHint->setFont(font6);
        LblOcrHint->setAlignment(Qt::AlignmentFlag::AlignCenter);
        LblOcrHint->setWordWrap(true);

        layoutOcrSection->addWidget(LblOcrHint);


        popupFinanceGrid->addLayout(layoutOcrSection, 5, 0, 1, 4);


        popupFinanceCardLayout->addLayout(popupFinanceGrid);


        overlayFinanceLayout->addWidget(PopupFinanceCard);


        gridLayout_2->addWidget(OverlayFinance, 0, 0, 1, 1);

        stacked_F->addWidget(ajouterF);
        modifierF = new QWidget();
        modifierF->setObjectName("modifierF");
        gridLayout_modifierF = new QGridLayout(modifierF);
        gridLayout_modifierF->setObjectName("gridLayout_modifierF");
        OverlayFinance_2 = new QFrame(modifierF);
        OverlayFinance_2->setObjectName("OverlayFinance_2");
        OverlayFinance_2->setFrameShape(QFrame::Shape::NoFrame);
        overlayFinanceLayout_2 = new QVBoxLayout(OverlayFinance_2);
        overlayFinanceLayout_2->setObjectName("overlayFinanceLayout_2");
        overlayFinanceLayout_2->setContentsMargins(0, 0, 0, 0);
        PopupFinanceCard_2 = new QFrame(OverlayFinance_2);
        PopupFinanceCard_2->setObjectName("PopupFinanceCard_2");
        sizePolicy.setHeightForWidth(PopupFinanceCard_2->sizePolicy().hasHeightForWidth());
        PopupFinanceCard_2->setSizePolicy(sizePolicy);
        PopupFinanceCard_2->setFrameShape(QFrame::Shape::NoFrame);
        popupFinanceCardLayout_2 = new QVBoxLayout(PopupFinanceCard_2);
        popupFinanceCardLayout_2->setSpacing(12);
        popupFinanceCardLayout_2->setObjectName("popupFinanceCardLayout_2");
        popupFinanceCardLayout_2->setContentsMargins(16, 16, 16, 16);
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

        layoutAmountRow_2 = new QHBoxLayout();
        layoutAmountRow_2->setSpacing(6);
        layoutAmountRow_2->setObjectName("layoutAmountRow_2");
        BtnAmountDecr_2 = new QPushButton(PopupFinanceCard_2);
        BtnAmountDecr_2->setObjectName("BtnAmountDecr_2");
        BtnAmountDecr_2->setMaximumSize(QSize(30, 30));

        layoutAmountRow_2->addWidget(BtnAmountDecr_2);

        FormAmount_2 = new QLineEdit(PopupFinanceCard_2);
        FormAmount_2->setObjectName("FormAmount_2");

        layoutAmountRow_2->addWidget(FormAmount_2);

        BtnAmountIncr_2 = new QPushButton(PopupFinanceCard_2);
        BtnAmountIncr_2->setObjectName("BtnAmountIncr_2");
        BtnAmountIncr_2->setMaximumSize(QSize(30, 30));

        layoutAmountRow_2->addWidget(BtnAmountIncr_2);

        BtnConvertCurrency_2 = new QPushButton(PopupFinanceCard_2);
        BtnConvertCurrency_2->setObjectName("BtnConvertCurrency_2");
        BtnConvertCurrency_2->setMinimumSize(QSize(0, 0));
        BtnConvertCurrency_2->setMaximumSize(QSize(160, 30));
        BtnConvertCurrency_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        layoutAmountRow_2->addWidget(BtnConvertCurrency_2);


        popupFinanceGrid_2->addLayout(layoutAmountRow_2, 1, 1, 1, 1);


        popupFinanceCardLayout_2->addLayout(popupFinanceGrid_2);


        overlayFinanceLayout_2->addWidget(PopupFinanceCard_2);


        gridLayout_modifierF->addWidget(OverlayFinance_2, 0, 0, 1, 1);

        stacked_F->addWidget(modifierF);
        statsF = new QWidget();
        statsF->setObjectName("statsF");
        statsFLayout = new QVBoxLayout(statsF);
        statsFLayout->setSpacing(10);
        statsFLayout->setObjectName("statsFLayout");
        statsFLayout->setContentsMargins(12, 12, 12, 12);
        stat_pub_3 = new QLabel(statsF);
        stat_pub_3->setObjectName("stat_pub_3");
        sizePolicy.setHeightForWidth(stat_pub_3->sizePolicy().hasHeightForWidth());
        stat_pub_3->setSizePolicy(sizePolicy);

        statsFLayout->addWidget(stat_pub_3);

        statsFBottomRow = new QHBoxLayout();
        statsFBottomRow->setSpacing(12);
        statsFBottomRow->setObjectName("statsFBottomRow");
        comboBox_3 = new QComboBox(statsF);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setMinimumSize(QSize(200, 38));

        statsFBottomRow->addWidget(comboBox_3);

        spacerItem14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statsFBottomRow->addItem(spacerItem14);

        retour_stat_4 = new QPushButton(statsF);
        retour_stat_4->setObjectName("retour_stat_4");
        retour_stat_4->setMinimumSize(QSize(160, 38));

        statsFBottomRow->addWidget(retour_stat_4);


        statsFLayout->addLayout(statsFBottomRow);

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
        verticalLayout_Lab = new QVBoxLayout(Lab);
        verticalLayout_Lab->setSpacing(8);
        verticalLayout_Lab->setObjectName("verticalLayout_Lab");
        verticalLayout_Lab->setContentsMargins(12, 10, 12, 10);
        LabsCardFilter_2 = new QFrame(Lab);
        LabsCardFilter_2->setObjectName("LabsCardFilter_2");
        LabsCardFilter_2->setFrameShape(QFrame::Shape::NoFrame);
        labsFilterLayout = new QHBoxLayout(LabsCardFilter_2);
        labsFilterLayout->setSpacing(10);
        labsFilterLayout->setObjectName("labsFilterLayout");
        labsFilterLayout->setContentsMargins(0, 0, 0, 0);
        LabsSearch_2 = new QLineEdit(LabsCardFilter_2);
        LabsSearch_2->setObjectName("LabsSearch_2");

        labsFilterLayout->addWidget(LabsSearch_2);

        LabsSpec_2 = new QComboBox(LabsCardFilter_2);
        LabsSpec_2->addItem(QString());
        LabsSpec_2->addItem(QString());
        LabsSpec_2->addItem(QString());
        LabsSpec_2->setObjectName("LabsSpec_2");

        labsFilterLayout->addWidget(LabsSpec_2);

        LabsCap_2 = new QComboBox(LabsCardFilter_2);
        LabsCap_2->addItem(QString());
        LabsCap_2->addItem(QString());
        LabsCap_2->addItem(QString());
        LabsCap_2->setObjectName("LabsCap_2");

        labsFilterLayout->addWidget(LabsCap_2);

        labsFilterSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsFilterLayout->addItem(labsFilterSpacer);

        btnLabReserveProduct = new QPushButton(LabsCardFilter_2);
        btnLabReserveProduct->setObjectName("btnLabReserveProduct");

        labsFilterLayout->addWidget(btnLabReserveProduct);

        btnReinitialiserPub_3 = new QPushButton(LabsCardFilter_2);
        btnReinitialiserPub_3->setObjectName("btnReinitialiserPub_3");

        labsFilterLayout->addWidget(btnReinitialiserPub_3);


        verticalLayout_Lab->addWidget(LabsCardFilter_2);

        TableLabs_2 = new QTableWidget(Lab);
        if (TableLabs_2->columnCount() < 11)
            TableLabs_2->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(0, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(1, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(2, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(3, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(4, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(5, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(6, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(7, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(8, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(9, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        TableLabs_2->setHorizontalHeaderItem(10, __qtablewidgetitem89);
        TableLabs_2->setObjectName("TableLabs_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(TableLabs_2->sizePolicy().hasHeightForWidth());
        TableLabs_2->setSizePolicy(sizePolicy1);
        TableLabs_2->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableLabs_2->setAlternatingRowColors(true);
        TableLabs_2->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableLabs_2->setShowGrid(false);
        TableLabs_2->setSortingEnabled(true);
        TableLabs_2->setCornerButtonEnabled(false);

        verticalLayout_Lab->addWidget(TableLabs_2);

        labsActionBtns = new QHBoxLayout();
        labsActionBtns->setSpacing(10);
        labsActionBtns->setObjectName("labsActionBtns");
        btnAjouterPub_3 = new QPushButton(Lab);
        btnAjouterPub_3->setObjectName("btnAjouterPub_3");

        labsActionBtns->addWidget(btnAjouterPub_3);

        btnAjouterPub_2 = new QPushButton(Lab);
        btnAjouterPub_2->setObjectName("btnAjouterPub_2");

        labsActionBtns->addWidget(btnAjouterPub_2);

        btnModifierPub_2 = new QPushButton(Lab);
        btnModifierPub_2->setObjectName("btnModifierPub_2");

        labsActionBtns->addWidget(btnModifierPub_2);

        btnSupprimerPub_2 = new QPushButton(Lab);
        btnSupprimerPub_2->setObjectName("btnSupprimerPub_2");

        labsActionBtns->addWidget(btnSupprimerPub_2);

        labsBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsActionBtns->addItem(labsBtnSpacer);

        btnStatLabs = new QPushButton(Lab);
        btnStatLabs->setObjectName("btnStatLabs");

        labsActionBtns->addWidget(btnStatLabs);


        verticalLayout_Lab->addLayout(labsActionBtns);

        labsReserveRow = new QHBoxLayout();
        labsReserveRow->setObjectName("labsReserveRow");
        labsReserveSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsReserveRow->addItem(labsReserveSpacer);


        verticalLayout_Lab->addLayout(labsReserveRow);

        stacked_L->addWidget(Lab);
        modifierL = new QWidget();
        modifierL->setObjectName("modifierL");
        LabReste_5 = new QLineEdit(modifierL);
        LabReste_5->setObjectName("LabReste_5");
        LabReste_5->setGeometry(QRect(0, 0, 100, 30));
        LabReste_5->setVisible(false);
        label_23 = new QLabel(modifierL);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(0, 0, 36, 20));
        label_23->setVisible(false);
        BtnPopupResetLabs_5 = new QPushButton(modifierL);
        BtnPopupResetLabs_5->setObjectName("BtnPopupResetLabs_5");
        BtnPopupResetLabs_5->setGeometry(QRect(0, 0, 80, 29));
        BtnPopupResetLabs_5->setVisible(false);
        modifierLLayout = new QVBoxLayout(modifierL);
        modifierLLayout->setSpacing(20);
        modifierLLayout->setObjectName("modifierLLayout");
        modifierLLayout->setContentsMargins(24, 14, 24, 14);
        lblPageTitle_4 = new QLabel(modifierL);
        lblPageTitle_4->setObjectName("lblPageTitle_4");
        lblPageTitle_4->setFont(font);
        lblPageTitle_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        modifierLLayout->addWidget(lblPageTitle_4);

        modifierLGrid = new QGridLayout();
        modifierLGrid->setSpacing(12);
        modifierLGrid->setObjectName("modifierLGrid");
        LblLabName_5 = new QLabel(modifierL);
        LblLabName_5->setObjectName("LblLabName_5");
        LblLabName_5->setMinimumSize(QSize(120, 0));

        modifierLGrid->addWidget(LblLabName_5, 0, 0, 1, 1);

        LabName_5 = new QLineEdit(modifierL);
        LabName_5->setObjectName("LabName_5");
        LabName_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabName_5, 0, 1, 1, 1);

        LblLabResp_5 = new QLabel(modifierL);
        LblLabResp_5->setObjectName("LblLabResp_5");
        LblLabResp_5->setMinimumSize(QSize(120, 0));

        modifierLGrid->addWidget(LblLabResp_5, 0, 2, 1, 1);

        LabResponsible_5 = new QComboBox(modifierL);
        LabResponsible_5->setObjectName("LabResponsible_5");
        LabResponsible_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabResponsible_5, 0, 3, 1, 1);

        LblLabLoc_5 = new QLabel(modifierL);
        LblLabLoc_5->setObjectName("LblLabLoc_5");

        modifierLGrid->addWidget(LblLabLoc_5, 1, 0, 1, 1);

        LabLocation_5 = new QLineEdit(modifierL);
        LabLocation_5->setObjectName("LabLocation_5");
        LabLocation_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabLocation_5, 1, 1, 1, 1);

        LblLabNum_5 = new QLabel(modifierL);
        LblLabNum_5->setObjectName("LblLabNum_5");

        modifierLGrid->addWidget(LblLabNum_5, 1, 2, 1, 1);

        LabNumber_5 = new QLineEdit(modifierL);
        LabNumber_5->setObjectName("LabNumber_5");
        LabNumber_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabNumber_5, 1, 3, 1, 1);

        LblLabSpec_5 = new QLabel(modifierL);
        LblLabSpec_5->setObjectName("LblLabSpec_5");

        modifierLGrid->addWidget(LblLabSpec_5, 2, 0, 1, 1);

        LabSpec_5 = new QComboBox(modifierL);
        LabSpec_5->addItem(QString());
        LabSpec_5->addItem(QString());
        LabSpec_5->addItem(QString());
        LabSpec_5->setObjectName("LabSpec_5");
        LabSpec_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabSpec_5, 2, 1, 1, 1);

        LblLabCap_5 = new QLabel(modifierL);
        LblLabCap_5->setObjectName("LblLabCap_5");

        modifierLGrid->addWidget(LblLabCap_5, 2, 2, 1, 1);

        LabCap_5 = new QComboBox(modifierL);
        LabCap_5->addItem(QString());
        LabCap_5->addItem(QString());
        LabCap_5->addItem(QString());
        LabCap_5->setObjectName("LabCap_5");
        LabCap_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabCap_5, 2, 3, 1, 1);

        LblLabSpec_14 = new QLabel(modifierL);
        LblLabSpec_14->setObjectName("LblLabSpec_14");

        modifierLGrid->addWidget(LblLabSpec_14, 3, 0, 1, 1);

        LabSpec_6 = new QComboBox(modifierL);
        LabSpec_6->addItem(QString());
        LabSpec_6->addItem(QString());
        LabSpec_6->addItem(QString());
        LabSpec_6->addItem(QString());
        LabSpec_6->setObjectName("LabSpec_6");
        LabSpec_6->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabSpec_6, 3, 1, 1, 1);

        LblLabSpec_15 = new QLabel(modifierL);
        LblLabSpec_15->setObjectName("LblLabSpec_15");

        modifierLGrid->addWidget(LblLabSpec_15, 3, 2, 1, 1);

        LabCap_6 = new QComboBox(modifierL);
        LabCap_6->addItem(QString());
        LabCap_6->addItem(QString());
        LabCap_6->addItem(QString());
        LabCap_6->setObjectName("LabCap_6");
        LabCap_6->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabCap_6, 3, 3, 1, 1);

        label_22 = new QLabel(modifierL);
        label_22->setObjectName("label_22");

        modifierLGrid->addWidget(label_22, 4, 0, 1, 1);

        LabMontant_5 = new QDoubleSpinBox(modifierL);
        LabMontant_5->setObjectName("LabMontant_5");
        LabMontant_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabMontant_5, 4, 1, 1, 1);

        label_24 = new QLabel(modifierL);
        label_24->setObjectName("label_24");

        modifierLGrid->addWidget(label_24, 4, 2, 1, 1);

        LabMontantPaye_5 = new QDoubleSpinBox(modifierL);
        LabMontantPaye_5->setObjectName("LabMontantPaye_5");
        LabMontantPaye_5->setMinimumSize(QSize(0, 40));

        modifierLGrid->addWidget(LabMontantPaye_5, 4, 3, 1, 1);

        modifierLGrid->setColumnStretch(1, 1);
        modifierLGrid->setColumnStretch(3, 1);

        modifierLLayout->addLayout(modifierLGrid);

        modifierLSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        modifierLLayout->addItem(modifierLSpacer);

        labsEditBtnRow = new QHBoxLayout();
        labsEditBtnRow->setSpacing(10);
        labsEditBtnRow->setObjectName("labsEditBtnRow");
        BtnPopupSaveLabs_5 = new QPushButton(modifierL);
        BtnPopupSaveLabs_5->setObjectName("BtnPopupSaveLabs_5");

        labsEditBtnRow->addWidget(BtnPopupSaveLabs_5);

        labsEditBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        labsEditBtnRow->addItem(labsEditBtnSpacer);

        retour_stat_9 = new QPushButton(modifierL);
        retour_stat_9->setObjectName("retour_stat_9");

        labsEditBtnRow->addWidget(retour_stat_9);


        modifierLLayout->addLayout(labsEditBtnRow);

        stacked_L->addWidget(modifierL);
        ajouterL = new QWidget();
        ajouterL->setObjectName("ajouterL");
        ajouterLMainLayout = new QVBoxLayout(ajouterL);
        ajouterLMainLayout->setSpacing(18);
        ajouterLMainLayout->setObjectName("ajouterLMainLayout");
        ajouterLMainLayout->setContentsMargins(40, 18, 40, 18);
        LabReste_3 = new QLineEdit(ajouterL);
        LabReste_3->setObjectName("LabReste_3");
        LabReste_3->setMaximumSize(QSize(0, 0));
        LabReste_3->setVisible(false);

        ajouterLMainLayout->addWidget(LabReste_3);

        label_21 = new QLabel(ajouterL);
        label_21->setObjectName("label_21");
        label_21->setMaximumSize(QSize(0, 0));
        label_21->setVisible(false);

        ajouterLMainLayout->addWidget(label_21);

        lblPageTitle_3 = new QLabel(ajouterL);
        lblPageTitle_3->setObjectName("lblPageTitle_3");
        lblPageTitle_3->setFont(font);
        lblPageTitle_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        ajouterLMainLayout->addWidget(lblPageTitle_3);

        labsAddFormGrid = new QGridLayout();
        labsAddFormGrid->setObjectName("labsAddFormGrid");
        labsAddFormGrid->setHorizontalSpacing(16);
        labsAddFormGrid->setVerticalSpacing(16);
        LblLabName_3 = new QLabel(ajouterL);
        LblLabName_3->setObjectName("LblLabName_3");
        LblLabName_3->setMinimumSize(QSize(120, 0));

        labsAddFormGrid->addWidget(LblLabName_3, 0, 0, 1, 1);

        LabName_3 = new QLineEdit(ajouterL);
        LabName_3->setObjectName("LabName_3");
        LabName_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabName_3, 0, 1, 1, 1);

        LblLabResp_3 = new QLabel(ajouterL);
        LblLabResp_3->setObjectName("LblLabResp_3");
        LblLabResp_3->setMinimumSize(QSize(120, 0));

        labsAddFormGrid->addWidget(LblLabResp_3, 0, 2, 1, 1);

        LabResponsible_3 = new QComboBox(ajouterL);
        LabResponsible_3->setObjectName("LabResponsible_3");
        LabResponsible_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabResponsible_3, 0, 3, 1, 1);

        LblLabLoc_3 = new QLabel(ajouterL);
        LblLabLoc_3->setObjectName("LblLabLoc_3");

        labsAddFormGrid->addWidget(LblLabLoc_3, 1, 0, 1, 1);

        LabLocation_3 = new QLineEdit(ajouterL);
        LabLocation_3->setObjectName("LabLocation_3");
        LabLocation_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabLocation_3, 1, 1, 1, 1);

        LblLabNum_3 = new QLabel(ajouterL);
        LblLabNum_3->setObjectName("LblLabNum_3");

        labsAddFormGrid->addWidget(LblLabNum_3, 1, 2, 1, 1);

        LabNumber_3 = new QLineEdit(ajouterL);
        LabNumber_3->setObjectName("LabNumber_3");
        LabNumber_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabNumber_3, 1, 3, 1, 1);

        LblLabSpec_3 = new QLabel(ajouterL);
        LblLabSpec_3->setObjectName("LblLabSpec_3");

        labsAddFormGrid->addWidget(LblLabSpec_3, 2, 0, 1, 1);

        LabSpec_3 = new QComboBox(ajouterL);
        LabSpec_3->addItem(QString());
        LabSpec_3->addItem(QString());
        LabSpec_3->addItem(QString());
        LabSpec_3->setObjectName("LabSpec_3");
        LabSpec_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabSpec_3, 2, 1, 1, 1);

        LblLabCap_3 = new QLabel(ajouterL);
        LblLabCap_3->setObjectName("LblLabCap_3");

        labsAddFormGrid->addWidget(LblLabCap_3, 2, 2, 1, 1);

        LabCap_3 = new QComboBox(ajouterL);
        LabCap_3->addItem(QString());
        LabCap_3->addItem(QString());
        LabCap_3->addItem(QString());
        LabCap_3->setObjectName("LabCap_3");
        LabCap_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabCap_3, 2, 3, 1, 1);

        LblLabSpec_12 = new QLabel(ajouterL);
        LblLabSpec_12->setObjectName("LblLabSpec_12");

        labsAddFormGrid->addWidget(LblLabSpec_12, 3, 0, 1, 1);

        LabSpec_4 = new QComboBox(ajouterL);
        LabSpec_4->addItem(QString());
        LabSpec_4->addItem(QString());
        LabSpec_4->addItem(QString());
        LabSpec_4->addItem(QString());
        LabSpec_4->setObjectName("LabSpec_4");
        LabSpec_4->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabSpec_4, 3, 1, 1, 1);

        LblLabSpec_13 = new QLabel(ajouterL);
        LblLabSpec_13->setObjectName("LblLabSpec_13");

        labsAddFormGrid->addWidget(LblLabSpec_13, 3, 2, 1, 1);

        LabCap_4 = new QComboBox(ajouterL);
        LabCap_4->addItem(QString());
        LabCap_4->addItem(QString());
        LabCap_4->addItem(QString());
        LabCap_4->setObjectName("LabCap_4");
        LabCap_4->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabCap_4, 3, 3, 1, 1);

        label_20 = new QLabel(ajouterL);
        label_20->setObjectName("label_20");

        labsAddFormGrid->addWidget(label_20, 4, 0, 1, 1);

        LabMontant_3 = new QDoubleSpinBox(ajouterL);
        LabMontant_3->setObjectName("LabMontant_3");
        LabMontant_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabMontant_3, 4, 1, 1, 1);

        label_19 = new QLabel(ajouterL);
        label_19->setObjectName("label_19");

        labsAddFormGrid->addWidget(label_19, 4, 2, 1, 1);

        LabMontantPaye_3 = new QDoubleSpinBox(ajouterL);
        LabMontantPaye_3->setObjectName("LabMontantPaye_3");
        LabMontantPaye_3->setMinimumSize(QSize(0, 40));

        labsAddFormGrid->addWidget(LabMontantPaye_3, 4, 3, 1, 1);


        ajouterLMainLayout->addLayout(labsAddFormGrid);

        verticalSpacerAddLab = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        ajouterLMainLayout->addItem(verticalSpacerAddLab);

        labsAddBtnRow = new QHBoxLayout();
        labsAddBtnRow->setSpacing(10);
        labsAddBtnRow->setObjectName("labsAddBtnRow");
        BtnPopupSaveLabs_3 = new QPushButton(ajouterL);
        BtnPopupSaveLabs_3->setObjectName("BtnPopupSaveLabs_3");

        labsAddBtnRow->addWidget(BtnPopupSaveLabs_3);

        BtnPopupResetLabs_3 = new QPushButton(ajouterL);
        BtnPopupResetLabs_3->setObjectName("BtnPopupResetLabs_3");

        labsAddBtnRow->addWidget(BtnPopupResetLabs_3);

        retour_stat_8 = new QPushButton(ajouterL);
        retour_stat_8->setObjectName("retour_stat_8");

        labsAddBtnRow->addWidget(retour_stat_8);


        ajouterLMainLayout->addLayout(labsAddBtnRow);

        stacked_L->addWidget(ajouterL);
        statL = new QWidget();
        statL->setObjectName("statL");
        retour_stat_2 = new QPushButton(statL);
        retour_stat_2->setObjectName("retour_stat_2");
        retour_stat_2->setGeometry(QRect(700, 520, 300, 41));
        comboBox_2 = new QComboBox(statL);
        comboBox_2->addItem(QString());
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
        affichierLLayout = new QVBoxLayout(affichierL);
        affichierLLayout->setSpacing(14);
        affichierLLayout->setObjectName("affichierLLayout");
        affichierLLayout->setContentsMargins(20, 12, 20, 12);
        lblPageTitle_2 = new QLabel(affichierL);
        lblPageTitle_2->setObjectName("lblPageTitle_2");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Vivaldi")});
        font7.setPointSize(14);
        font7.setBold(true);
        font7.setItalic(true);
        lblPageTitle_2->setFont(font7);
        lblPageTitle_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        affichierLLayout->addWidget(lblPageTitle_2);

        affichierLContentRow = new QHBoxLayout();
        affichierLContentRow->setSpacing(18);
        affichierLContentRow->setObjectName("affichierLContentRow");
        PopupLabsForm_4 = new QFrame(affichierL);
        PopupLabsForm_4->setObjectName("PopupLabsForm_4");
        PopupLabsForm_4->setFrameShape(QFrame::Shape::StyledPanel);
        PopupLabsForm_4->setFrameShadow(QFrame::Shadow::Raised);
        affichierLGrid = new QGridLayout(PopupLabsForm_4);
        affichierLGrid->setSpacing(10);
        affichierLGrid->setObjectName("affichierLGrid");
        affichierLGrid->setContentsMargins(16, 16, 16, 16);
        LblLabName_6 = new QLabel(PopupLabsForm_4);
        LblLabName_6->setObjectName("LblLabName_6");
        LblLabName_6->setMinimumSize(QSize(110, 0));

        affichierLGrid->addWidget(LblLabName_6, 0, 0, 1, 1);

        aff1 = new QLineEdit(PopupLabsForm_4);
        aff1->setObjectName("aff1");
        aff1->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff1, 0, 1, 1, 1);

        LblLabResp_6 = new QLabel(PopupLabsForm_4);
        LblLabResp_6->setObjectName("LblLabResp_6");
        LblLabResp_6->setMinimumSize(QSize(110, 0));

        affichierLGrid->addWidget(LblLabResp_6, 0, 2, 1, 1);

        aff5 = new QLineEdit(PopupLabsForm_4);
        aff5->setObjectName("aff5");
        aff5->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff5, 0, 3, 1, 1);

        LblLabLoc_6 = new QLabel(PopupLabsForm_4);
        LblLabLoc_6->setObjectName("LblLabLoc_6");

        affichierLGrid->addWidget(LblLabLoc_6, 1, 0, 1, 1);

        aff2 = new QLineEdit(PopupLabsForm_4);
        aff2->setObjectName("aff2");
        aff2->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff2, 1, 1, 1, 1);

        LblLabNum_6 = new QLabel(PopupLabsForm_4);
        LblLabNum_6->setObjectName("LblLabNum_6");

        affichierLGrid->addWidget(LblLabNum_6, 1, 2, 1, 1);

        aff6 = new QLineEdit(PopupLabsForm_4);
        aff6->setObjectName("aff6");
        aff6->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff6, 1, 3, 1, 1);

        LblLabSpec_6 = new QLabel(PopupLabsForm_4);
        LblLabSpec_6->setObjectName("LblLabSpec_6");

        affichierLGrid->addWidget(LblLabSpec_6, 2, 0, 1, 1);

        aff3 = new QComboBox(PopupLabsForm_4);
        aff3->addItem(QString());
        aff3->addItem(QString());
        aff3->addItem(QString());
        aff3->setObjectName("aff3");
        aff3->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff3, 2, 1, 1, 1);

        LblLabCap_6 = new QLabel(PopupLabsForm_4);
        LblLabCap_6->setObjectName("LblLabCap_6");

        affichierLGrid->addWidget(LblLabCap_6, 2, 2, 1, 1);

        aff7 = new QComboBox(PopupLabsForm_4);
        aff7->addItem(QString());
        aff7->addItem(QString());
        aff7->addItem(QString());
        aff7->setObjectName("aff7");
        aff7->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff7, 2, 3, 1, 1);

        LblLabSpec_7 = new QLabel(PopupLabsForm_4);
        LblLabSpec_7->setObjectName("LblLabSpec_7");

        affichierLGrid->addWidget(LblLabSpec_7, 3, 0, 1, 1);

        aff3_2 = new QComboBox(PopupLabsForm_4);
        aff3_2->addItem(QString());
        aff3_2->addItem(QString());
        aff3_2->addItem(QString());
        aff3_2->addItem(QString());
        aff3_2->setObjectName("aff3_2");
        aff3_2->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff3_2, 3, 1, 1, 1);

        LblLabSpec_8 = new QLabel(PopupLabsForm_4);
        LblLabSpec_8->setObjectName("LblLabSpec_8");

        affichierLGrid->addWidget(LblLabSpec_8, 3, 2, 1, 1);

        aff7_2 = new QComboBox(PopupLabsForm_4);
        aff7_2->addItem(QString());
        aff7_2->addItem(QString());
        aff7_2->addItem(QString());
        aff7_2->setObjectName("aff7_2");
        aff7_2->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff7_2, 3, 3, 1, 1);

        label_16 = new QLabel(PopupLabsForm_4);
        label_16->setObjectName("label_16");

        affichierLGrid->addWidget(label_16, 4, 0, 1, 1);

        aff_montant = new QLineEdit(PopupLabsForm_4);
        aff_montant->setObjectName("aff_montant");
        aff_montant->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff_montant, 4, 1, 1, 1);

        label_18 = new QLabel(PopupLabsForm_4);
        label_18->setObjectName("label_18");

        affichierLGrid->addWidget(label_18, 4, 2, 1, 1);

        aff_montant_paye = new QLineEdit(PopupLabsForm_4);
        aff_montant_paye->setObjectName("aff_montant_paye");
        aff_montant_paye->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff_montant_paye, 4, 3, 1, 1);

        label_17 = new QLabel(PopupLabsForm_4);
        label_17->setObjectName("label_17");

        affichierLGrid->addWidget(label_17, 5, 0, 1, 1);

        aff_reste = new QLineEdit(PopupLabsForm_4);
        aff_reste->setObjectName("aff_reste");
        aff_reste->setMinimumSize(QSize(0, 36));

        affichierLGrid->addWidget(aff_reste, 5, 1, 1, 1);

        affichierLGrid->setColumnStretch(1, 1);
        affichierLGrid->setColumnStretch(3, 1);

        affichierLContentRow->addWidget(PopupLabsForm_4);

        qrPanelFrame = new QFrame(affichierL);
        qrPanelFrame->setObjectName("qrPanelFrame");
        qrPanelFrame->setMinimumSize(QSize(210, 0));
        qrPanelFrame->setMaximumSize(QSize(230, 16777215));
        qrPanelFrame->setFrameShape(QFrame::Shape::StyledPanel);
        qrPanelFrame->setFrameShadow(QFrame::Shadow::Raised);
        qrPanelLayout = new QVBoxLayout(qrPanelFrame);
        qrPanelLayout->setSpacing(10);
        qrPanelLayout->setObjectName("qrPanelLayout");
        qrPanelLayout->setContentsMargins(12, 16, 12, 16);
        labQrTitle = new QLabel(qrPanelFrame);
        labQrTitle->setObjectName("labQrTitle");
        labQrTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        qrPanelLayout->addWidget(labQrTitle);

        labQrDisplay = new QLabel(qrPanelFrame);
        labQrDisplay->setObjectName("labQrDisplay");
        labQrDisplay->setMinimumSize(QSize(180, 180));
        labQrDisplay->setMaximumSize(QSize(200, 200));
        labQrDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labQrDisplay->setWordWrap(true);

        qrPanelLayout->addWidget(labQrDisplay);

        labQrHint = new QLabel(qrPanelFrame);
        labQrHint->setObjectName("labQrHint");
        labQrHint->setAlignment(Qt::AlignmentFlag::AlignCenter);

        qrPanelLayout->addWidget(labQrHint);

        labQrUrl = new QLabel(qrPanelFrame);
        labQrUrl->setObjectName("labQrUrl");
        labQrUrl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labQrUrl->setWordWrap(true);

        qrPanelLayout->addWidget(labQrUrl);

        spacerItem15 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        qrPanelLayout->addItem(spacerItem15);


        affichierLContentRow->addWidget(qrPanelFrame);


        affichierLLayout->addLayout(affichierLContentRow);

        affichierLBtnRow = new QHBoxLayout();
        affichierLBtnRow->setSpacing(10);
        affichierLBtnRow->setObjectName("affichierLBtnRow");
        btnPaiementLab = new QPushButton(affichierL);
        btnPaiementLab->setObjectName("btnPaiementLab");
        btnPaiementLab->setMinimumSize(QSize(0, 42));

        affichierLBtnRow->addWidget(btnPaiementLab);

        BtnExportLabsDirect = new QPushButton(affichierL);
        BtnExportLabsDirect->setObjectName("BtnExportLabsDirect");
        BtnExportLabsDirect->setMinimumSize(QSize(0, 42));

        affichierLBtnRow->addWidget(BtnExportLabsDirect);

        affichierLBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        affichierLBtnRow->addItem(affichierLBtnSpacer);

        retour_stat_3 = new QPushButton(affichierL);
        retour_stat_3->setObjectName("retour_stat_3");
        retour_stat_3->setMinimumSize(QSize(0, 42));

        affichierLBtnRow->addWidget(retour_stat_3);


        affichierLLayout->addLayout(affichierLBtnRow);

        stacked_L->addWidget(affichierL);
        mapsL = new QWidget();
        mapsL->setObjectName("mapsL");
        stacked_L->addWidget(mapsL);
        labReserveProduct = new QWidget();
        labReserveProduct->setObjectName("labReserveProduct");
        lblLabReserveTitle = new QLabel(labReserveProduct);
        lblLabReserveTitle->setObjectName("lblLabReserveTitle");
        lblLabReserveTitle->setGeometry(QRect(20, 20, 900, 40));
        lblLabReserveHint = new QLabel(labReserveProduct);
        lblLabReserveHint->setObjectName("lblLabReserveHint");
        lblLabReserveHint->setGeometry(QRect(20, 55, 1100, 30));
        lblLabReserveHint->setWordWrap(true);
        TableLabReserveProducts = new QTableWidget(labReserveProduct);
        TableLabReserveProducts->setObjectName("TableLabReserveProducts");
        TableLabReserveProducts->setGeometry(QRect(20, 95, 1150, 380));
        TableLabReserveProducts->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        TableLabReserveProducts->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        TableLabReserveProducts->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        TableLabReserveProducts->setSortingEnabled(false);
        lblLabReserveQty = new QLabel(labReserveProduct);
        lblLabReserveQty->setObjectName("lblLabReserveQty");
        lblLabReserveQty->setGeometry(QRect(20, 490, 200, 30));
        spinLabReserveQty = new QSpinBox(labReserveProduct);
        spinLabReserveQty->setObjectName("spinLabReserveQty");
        spinLabReserveQty->setGeometry(QRect(220, 485, 120, 35));
        spinLabReserveQty->setMinimum(1);
        spinLabReserveQty->setMaximum(999999);
        btnLabReserveValidate = new QPushButton(labReserveProduct);
        btnLabReserveValidate->setObjectName("btnLabReserveValidate");
        btnLabReserveValidate->setGeometry(QRect(400, 480, 180, 45));
        btnLabReserveBack = new QPushButton(labReserveProduct);
        btnLabReserveBack->setObjectName("btnLabReserveBack");
        btnLabReserveBack->setGeometry(QRect(620, 480, 180, 45));
        stacked_L->addWidget(labReserveProduct);

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

        btnFiltrerDateProj = new QPushButton(page_proj_list);
        btnFiltrerDateProj->setObjectName("btnFiltrerDateProj");

        gridLayoutProjFilters->addWidget(btnFiltrerDateProj, 2, 1, 1, 1);

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
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(0, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(1, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(2, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(3, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(4, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(5, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(6, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tableProjets->setHorizontalHeaderItem(7, __qtablewidgetitem97);
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

        btnSmsProj = new QPushButton(page_proj_list);
        btnSmsProj->setObjectName("btnSmsProj");

        horizontalLayoutProjBottom->addWidget(btnSmsProj);

        horizontalSpacerProjBottom = new QSpacerItem(360, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutProjBottom->addItem(horizontalSpacerProjBottom);

        btnVoirStatistiquesProj = new QPushButton(page_proj_list);
        btnVoirStatistiquesProj->setObjectName("btnVoirStatistiquesProj");

        horizontalLayoutProjBottom->addWidget(btnVoirStatistiquesProj);

        btnExportPdfProj = new QPushButton(page_proj_list);
        btnExportPdfProj->setObjectName("btnExportPdfProj");

        horizontalLayoutProjBottom->addWidget(btnExportPdfProj);


        verticalLayoutProjList->addLayout(horizontalLayoutProjBottom);

        stack_proj->addWidget(page_proj_list);
        page_proj_add = new QWidget();
        page_proj_add->setObjectName("page_proj_add");
        gridLayoutProjAdd = new QGridLayout(page_proj_add);
        gridLayoutProjAdd->setObjectName("gridLayoutProjAdd");
        gridLayoutProjAdd->setHorizontalSpacing(40);
        gridLayoutProjAdd->setVerticalSpacing(20);
        gridLayoutProjAdd->setContentsMargins(60, 28, 60, 28);
        hLayoutAddButtonsProj = new QHBoxLayout();
        hLayoutAddButtonsProj->setObjectName("hLayoutAddButtonsProj");
        spacerAddButtonsProj = new QSpacerItem(480, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutAddButtonsProj->addItem(spacerAddButtonsProj);

        btnAddProj = new QPushButton(page_proj_add);
        btnAddProj->setObjectName("btnAddProj");

        hLayoutAddButtonsProj->addWidget(btnAddProj);

        btnRetourAddProj = new QPushButton(page_proj_add);
        btnRetourAddProj->setObjectName("btnRetourAddProj");

        hLayoutAddButtonsProj->addWidget(btnRetourAddProj);


        gridLayoutProjAdd->addLayout(hLayoutAddButtonsProj, 6, 0, 1, 4);

        lineResumeAddProj = new QComboBox(page_proj_add);
        lineResumeAddProj->addItem(QString());
        lineResumeAddProj->addItem(QString());
        lineResumeAddProj->setObjectName("lineResumeAddProj");

        gridLayoutProjAdd->addWidget(lineResumeAddProj, 1, 3, 1, 1);

        lblTypeBrevetAddProj = new QLabel(page_proj_add);
        lblTypeBrevetAddProj->setObjectName("lblTypeBrevetAddProj");

        gridLayoutProjAdd->addWidget(lblTypeBrevetAddProj, 2, 0, 1, 1);

        lblDomaineAddProj = new QLabel(page_proj_add);
        lblDomaineAddProj->setObjectName("lblDomaineAddProj");

        gridLayoutProjAdd->addWidget(lblDomaineAddProj, 1, 0, 1, 1);

        lblStatusBrevetAddProj = new QLabel(page_proj_add);
        lblStatusBrevetAddProj->setObjectName("lblStatusBrevetAddProj");

        gridLayoutProjAdd->addWidget(lblStatusBrevetAddProj, 5, 0, 1, 1);

        lblResumeAddProj = new QLabel(page_proj_add);
        lblResumeAddProj->setObjectName("lblResumeAddProj");

        gridLayoutProjAdd->addWidget(lblResumeAddProj, 1, 2, 1, 1);

        lblDateDepotAddProj = new QLabel(page_proj_add);
        lblDateDepotAddProj->setObjectName("lblDateDepotAddProj");

        gridLayoutProjAdd->addWidget(lblDateDepotAddProj, 4, 0, 1, 1);

        lineTitreAddProj = new QLineEdit(page_proj_add);
        lineTitreAddProj->setObjectName("lineTitreAddProj");

        gridLayoutProjAdd->addWidget(lineTitreAddProj, 0, 1, 1, 1);

        lblNumeroBrevetAddProj = new QLabel(page_proj_add);
        lblNumeroBrevetAddProj->setObjectName("lblNumeroBrevetAddProj");

        gridLayoutProjAdd->addWidget(lblNumeroBrevetAddProj, 3, 0, 1, 1);

        lineDomaineAddProj = new QLineEdit(page_proj_add);
        lineDomaineAddProj->setObjectName("lineDomaineAddProj");

        gridLayoutProjAdd->addWidget(lineDomaineAddProj, 1, 1, 1, 1);

        lineInventeursAddProj = new QComboBox(page_proj_add);
        lineInventeursAddProj->addItem(QString());
        lineInventeursAddProj->addItem(QString());
        lineInventeursAddProj->addItem(QString());
        lineInventeursAddProj->setObjectName("lineInventeursAddProj");

        gridLayoutProjAdd->addWidget(lineInventeursAddProj, 0, 3, 1, 1);

        lblTitreAddProj = new QLabel(page_proj_add);
        lblTitreAddProj->setObjectName("lblTitreAddProj");

        gridLayoutProjAdd->addWidget(lblTitreAddProj, 0, 0, 1, 1);

        lblInventeursAddProj = new QLabel(page_proj_add);
        lblInventeursAddProj->setObjectName("lblInventeursAddProj");

        gridLayoutProjAdd->addWidget(lblInventeursAddProj, 0, 2, 1, 1);

        dateEdit = new QDateEdit(page_proj_add);
        dateEdit->setObjectName("dateEdit");

        gridLayoutProjAdd->addWidget(dateEdit, 3, 1, 1, 1);

        dateEdit_2 = new QDateEdit(page_proj_add);
        dateEdit_2->setObjectName("dateEdit_2");

        gridLayoutProjAdd->addWidget(dateEdit_2, 4, 1, 1, 1);

        lineEdit = new QLineEdit(page_proj_add);
        lineEdit->setObjectName("lineEdit");

        gridLayoutProjAdd->addWidget(lineEdit, 2, 1, 1, 1);

        dateEdit_3 = new QDateEdit(page_proj_add);
        dateEdit_3->setObjectName("dateEdit_3");

        gridLayoutProjAdd->addWidget(dateEdit_3, 5, 1, 1, 1);

        stack_proj->addWidget(page_proj_add);
        page_proj_edit = new QWidget();
        page_proj_edit->setObjectName("page_proj_edit");
        gridLayoutProjEdit = new QGridLayout(page_proj_edit);
        gridLayoutProjEdit->setObjectName("gridLayoutProjEdit");
        gridLayoutProjEdit->setHorizontalSpacing(40);
        gridLayoutProjEdit->setVerticalSpacing(20);
        gridLayoutProjEdit->setContentsMargins(60, 28, 60, 28);
        lblInventeursEditProj = new QLabel(page_proj_edit);
        lblInventeursEditProj->setObjectName("lblInventeursEditProj");

        gridLayoutProjEdit->addWidget(lblInventeursEditProj, 2, 2, 1, 1);

        lineTitreEditProj = new QLineEdit(page_proj_edit);
        lineTitreEditProj->setObjectName("lineTitreEditProj");

        gridLayoutProjEdit->addWidget(lineTitreEditProj, 0, 1, 1, 1);

        lblTypeBrevetEditProj = new QLabel(page_proj_edit);
        lblTypeBrevetEditProj->setObjectName("lblTypeBrevetEditProj");

        gridLayoutProjEdit->addWidget(lblTypeBrevetEditProj, 2, 0, 1, 1);

        lineResumeEditProj = new QComboBox(page_proj_edit);
        lineResumeEditProj->addItem(QString());
        lineResumeEditProj->addItem(QString());
        lineResumeEditProj->setObjectName("lineResumeEditProj");

        gridLayoutProjEdit->addWidget(lineResumeEditProj, 3, 3, 1, 1);

        lblDomaineEditProj = new QLabel(page_proj_edit);
        lblDomaineEditProj->setObjectName("lblDomaineEditProj");

        gridLayoutProjEdit->addWidget(lblDomaineEditProj, 1, 0, 1, 1);

        lblResumeEditProj = new QLabel(page_proj_edit);
        lblResumeEditProj->setObjectName("lblResumeEditProj");

        gridLayoutProjEdit->addWidget(lblResumeEditProj, 3, 2, 1, 1);

        hLayoutEditButtonsProj = new QHBoxLayout();
        hLayoutEditButtonsProj->setObjectName("hLayoutEditButtonsProj");
        spacerEditButtonsProj = new QSpacerItem(480, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutEditButtonsProj->addItem(spacerEditButtonsProj);

        btnConfirmEditProj = new QPushButton(page_proj_edit);
        btnConfirmEditProj->setObjectName("btnConfirmEditProj");

        hLayoutEditButtonsProj->addWidget(btnConfirmEditProj);

        btnRetourEditProj = new QPushButton(page_proj_edit);
        btnRetourEditProj->setObjectName("btnRetourEditProj");

        hLayoutEditButtonsProj->addWidget(btnRetourEditProj);


        gridLayoutProjEdit->addLayout(hLayoutEditButtonsProj, 5, 0, 1, 4);

        lineInventeursEditProj = new QComboBox(page_proj_edit);
        lineInventeursEditProj->addItem(QString());
        lineInventeursEditProj->addItem(QString());
        lineInventeursEditProj->addItem(QString());
        lineInventeursEditProj->setObjectName("lineInventeursEditProj");

        gridLayoutProjEdit->addWidget(lineInventeursEditProj, 2, 3, 1, 1);

        lblDateDepotEditProj = new QLabel(page_proj_edit);
        lblDateDepotEditProj->setObjectName("lblDateDepotEditProj");

        gridLayoutProjEdit->addWidget(lblDateDepotEditProj, 0, 2, 1, 1);

        lblTitreEditProj = new QLabel(page_proj_edit);
        lblTitreEditProj->setObjectName("lblTitreEditProj");

        gridLayoutProjEdit->addWidget(lblTitreEditProj, 0, 0, 1, 1);

        lblStatusBrevetEditProj = new QLabel(page_proj_edit);
        lblStatusBrevetEditProj->setObjectName("lblStatusBrevetEditProj");

        gridLayoutProjEdit->addWidget(lblStatusBrevetEditProj, 1, 2, 1, 1);

        lineDomaineEditProj = new QLineEdit(page_proj_edit);
        lineDomaineEditProj->setObjectName("lineDomaineEditProj");

        gridLayoutProjEdit->addWidget(lineDomaineEditProj, 1, 1, 1, 1);

        lblNumeroBrevetEditProj = new QLabel(page_proj_edit);
        lblNumeroBrevetEditProj->setObjectName("lblNumeroBrevetEditProj");

        gridLayoutProjEdit->addWidget(lblNumeroBrevetEditProj, 3, 0, 1, 1);

        dateEdit_4 = new QDateEdit(page_proj_edit);
        dateEdit_4->setObjectName("dateEdit_4");

        gridLayoutProjEdit->addWidget(dateEdit_4, 1, 3, 1, 1);

        dateEdit_5 = new QDateEdit(page_proj_edit);
        dateEdit_5->setObjectName("dateEdit_5");

        gridLayoutProjEdit->addWidget(dateEdit_5, 0, 3, 1, 1);

        lineEdit_2 = new QLineEdit(page_proj_edit);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayoutProjEdit->addWidget(lineEdit_2, 2, 1, 1, 1);

        dateEdit_6 = new QDateEdit(page_proj_edit);
        dateEdit_6->setObjectName("dateEdit_6");

        gridLayoutProjEdit->addWidget(dateEdit_6, 3, 1, 1, 1);

        stack_proj->addWidget(page_proj_edit);
        page_proj_empty = new QWidget();
        page_proj_empty->setObjectName("page_proj_empty");
        verticalLayoutProjEmpty = new QVBoxLayout(page_proj_empty);
        verticalLayoutProjEmpty->setObjectName("verticalLayoutProjEmpty");
        lblStatsTitleProj = new QLabel(page_proj_empty);
        lblStatsTitleProj->setObjectName("lblStatsTitleProj");
        lblStatsTitleProj->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutProjEmpty->addWidget(lblStatsTitleProj);

        hLayoutProjStats = new QHBoxLayout();
        hLayoutProjStats->setObjectName("hLayoutProjStats");
        statsWidgetProjStatus = new QWidget(page_proj_empty);
        statsWidgetProjStatus->setObjectName("statsWidgetProjStatus");
        statsWidgetProjStatus->setMinimumSize(QSize(0, 300));

        hLayoutProjStats->addWidget(statsWidgetProjStatus);

        statsWidgetProjPrio = new QWidget(page_proj_empty);
        statsWidgetProjPrio->setObjectName("statsWidgetProjPrio");
        statsWidgetProjPrio->setMinimumSize(QSize(0, 300));

        hLayoutProjStats->addWidget(statsWidgetProjPrio);


        verticalLayoutProjEmpty->addLayout(hLayoutProjStats);

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
        menubar->setGeometry(QRect(0, 0, 1528, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);
        stack_emp->setCurrentIndex(0);
        stacked_I->setCurrentIndex(0);
        stack_pub->setCurrentIndex(0);
        stacked_F->setCurrentIndex(0);
        stacked_L->setCurrentIndex(2);
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
#if QT_CONFIG(tooltip)
        btnThemeToggle->setToolTip(QCoreApplication::translate("MainWindow", "Passer en th\303\250me sombre", nullptr));
#endif // QT_CONFIG(tooltip)
        btnThemeToggle->setText(QCoreApplication::translate("MainWindow", "\360\237\214\231  Mode Nuit", nullptr));
        btnDeconnecter->setText(QCoreApplication::translate("MainWindow", "D\303\251connecter", nullptr));
        lblBrand->setText(QCoreApplication::translate("MainWindow", "SmartResearchLab", nullptr));
        lblPageTitle->setText(QCoreApplication::translate("MainWindow", "Employee", nullptr));
        btnNotif->setText(QCoreApplication::translate("MainWindow", "\360\237\224\224 (0)", nullptr));
        lineSearchEmp->setText(QString());
        lineSearchEmp->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (recherche par CIN ,Username ou de role ...)", nullptr));
        btnTrier_emp->setText(QCoreApplication::translate("MainWindow", "Trier par Date d'embauche", nullptr));
        btnModifier_emp->setText(QCoreApplication::translate("MainWindow", "Modifier employ\303\251", nullptr));
        pointage->setText(QCoreApplication::translate("MainWindow", "Pointage", nullptr));
        btnAjouterEmp->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableEmp->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableEmp->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableEmp->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableEmp->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TableEmp->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TableEmp->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = TableEmp->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Departement", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = TableEmp->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Date_emb", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = TableEmp->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = TableEmp->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        btnSupprimer_emp->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnStat_emp->setText(QCoreApplication::translate("MainWindow", "Voir statistique", nullptr));
        lblAddEmpTitle->setText(QCoreApplication::translate("MainWindow", "Ajouter un employ\303\251", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_8->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_8->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_2->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "D\303\251partement", nullptr));
        comboDepartementAdd->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir un d\303\251partement", nullptr));
        comboDepartementAdd->setItemText(1, QCoreApplication::translate("MainWindow", "Projet", nullptr));
        comboDepartementAdd->setItemText(2, QCoreApplication::translate("MainWindow", "Inventaire", nullptr));
        comboDepartementAdd->setItemText(3, QCoreApplication::translate("MainWindow", "RH", nullptr));
        comboDepartementAdd->setItemText(4, QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        comboDepartementAdd->setItemText(5, QCoreApplication::translate("MainWindow", "Laboratoires", nullptr));
        comboDepartementAdd->setItemText(6, QCoreApplication::translate("MainWindow", "Finance", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        comboPosteAdd->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir un poste", nullptr));
        comboPosteAdd->setItemText(1, QCoreApplication::translate("MainWindow", "RH", nullptr));
        comboPosteAdd->setItemText(2, QCoreApplication::translate("MainWindow", "Chercheur", nullptr));
        comboPosteAdd->setItemText(3, QCoreApplication::translate("MainWindow", "Responsable_laboratoire", nullptr));
        comboPosteAdd->setItemText(4, QCoreApplication::translate("MainWindow", "Directeur_de_projet", nullptr));
        comboPosteAdd->setItemText(5, QCoreApplication::translate("MainWindow", "Responsable_financier", nullptr));
        comboPosteAdd->setItemText(6, QCoreApplication::translate("MainWindow", "Responsable_de_stock", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        passwordStrengthLabelAdd->setText(QCoreApplication::translate("MainWindow", "\342\200\224", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Date Embauche", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Scanner votre visage", nullptr));
        btnScanFace->setText(QCoreApplication::translate("MainWindow", "Scanner", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_cam->setText(QString());
        label_12->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        comboRoleAdd->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir un role", nullptr));
        comboRoleAdd->setItemText(1, QCoreApplication::translate("MainWindow", "RH", nullptr));
        comboRoleAdd->setItemText(2, QCoreApplication::translate("MainWindow", "Responsable_financier", nullptr));
        comboRoleAdd->setItemText(3, QCoreApplication::translate("MainWindow", "Responsable_de_stock", nullptr));
        comboRoleAdd->setItemText(4, QCoreApplication::translate("MainWindow", "Chercheur", nullptr));
        comboRoleAdd->setItemText(5, QCoreApplication::translate("MainWindow", "Directeur_de_projet", nullptr));
        comboRoleAdd->setItemText(6, QCoreApplication::translate("MainWindow", "Responsable_Labos", nullptr));

        btnSaveEmployee->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        btnAnnuler_emp->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        lblEditEmpTitle->setText(QCoreApplication::translate("MainWindow", "Modifier un employ\303\251", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_10->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_10->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_6->setTitle(QString());
        labelCINEdit_3->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        labelDateEmbaucheEdit_3->setText(QCoreApplication::translate("MainWindow", "Date Embauche", nullptr));
        labelUsernameEdit_3->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        labelSalaireEdit_3->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        labelEmailEdit_3->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        labelPosteEdit_3->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        comboPosteEmp->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir un poste", nullptr));
        comboPosteEmp->setItemText(1, QCoreApplication::translate("MainWindow", "RH", nullptr));
        comboPosteEmp->setItemText(2, QCoreApplication::translate("MainWindow", "Chercheur", nullptr));
        comboPosteEmp->setItemText(3, QCoreApplication::translate("MainWindow", "Responsable_laboratoire", nullptr));
        comboPosteEmp->setItemText(4, QCoreApplication::translate("MainWindow", "Directeur_de_projet", nullptr));
        comboPosteEmp->setItemText(5, QCoreApplication::translate("MainWindow", "Responsable_financier", nullptr));
        comboPosteEmp->setItemText(6, QCoreApplication::translate("MainWindow", "Responsable_de_stock", nullptr));

        labelNomEdit_3->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        labelDepartementEdit_3->setText(QCoreApplication::translate("MainWindow", "D\303\251partement", nullptr));
        comboDepartementEmp->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir un d\303\251partement", nullptr));
        comboDepartementEmp->setItemText(1, QCoreApplication::translate("MainWindow", "RH", nullptr));
        comboDepartementEmp->setItemText(2, QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        comboDepartementEmp->setItemText(3, QCoreApplication::translate("MainWindow", "Laboratoires", nullptr));
        comboDepartementEmp->setItemText(4, QCoreApplication::translate("MainWindow", "Inventaire", nullptr));
        comboDepartementEmp->setItemText(5, QCoreApplication::translate("MainWindow", "Finance", nullptr));
        comboDepartementEmp->setItemText(6, QCoreApplication::translate("MainWindow", "Projet", nullptr));

        labelPrenomEdit_3->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        comboRoleAdd_2->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir un role", nullptr));
        comboRoleAdd_2->setItemText(1, QCoreApplication::translate("MainWindow", "RH", nullptr));
        comboRoleAdd_2->setItemText(2, QCoreApplication::translate("MainWindow", "Responsable_financier", nullptr));
        comboRoleAdd_2->setItemText(3, QCoreApplication::translate("MainWindow", "Responsable_de_stock", nullptr));
        comboRoleAdd_2->setItemText(4, QCoreApplication::translate("MainWindow", "Chercheur", nullptr));
        comboRoleAdd_2->setItemText(5, QCoreApplication::translate("MainWindow", "Directeur_de_projet", nullptr));
        comboRoleAdd_2->setItemText(6, QCoreApplication::translate("MainWindow", "Responsable_Labos", nullptr));

        btnSaveEditEmployee->setText(QCoreApplication::translate("MainWindow", "Enregistrer les modifications", nullptr));
        btnCancelEditEmp->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_9->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_9->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Statistiques employ\303\251s", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_7->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_7->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Cong\303\251s", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = TableCongeEmp->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = TableCongeEmp->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = TableCongeEmp->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Date_deb", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = TableCongeEmp->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "DateFin", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = TableCongeEmp->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = TableCongeEmp->horizontalHeaderItem(5);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        Accepter_conge_Emp->setText(QCoreApplication::translate("MainWindow", "Accepter", nullptr));
        Rejeter_conge_Emp->setText(QCoreApplication::translate("MainWindow", "Rejet\303\251", nullptr));
#if QT_CONFIG(tooltip)
        BtnPopupCancelLabs_6->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnPopupCancelLabs_6->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Formations", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = TableFormations_Emp->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = TableFormations_Emp->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = TableFormations_Emp->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = TableFormations_Emp->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Dur\303\251e", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = TableFormations_Emp->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = TableFormations_Emp->horizontalHeaderItem(5);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "cout", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = TableFormations_Emp->horizontalHeaderItem(6);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = TableFormations_Emp->horizontalHeaderItem(7);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "valorisation", nullptr));
        Modifier_Formations_Emp->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        Exporter_Formations_Emp->setText(QCoreApplication::translate("MainWindow", "Exporter vers le DG", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Pointage", nullptr));
#if QT_CONFIG(tooltip)
        btn_ret->setToolTip(QCoreApplication::translate("MainWindow", "Fermer", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_ret->setText(QCoreApplication::translate("MainWindow", "\342\234\225", nullptr));
        groupBox_5->setTitle(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "Scanner votre badge ici :", nullptr));
        btn_reset->setText(QCoreApplication::translate("MainWindow", "Reset pointage", nullptr));
        btn_exportt->setText(QCoreApplication::translate("MainWindow", "Exporter excel", nullptr));
        label_feedback->setText(QString());
        QTableWidgetItem *___qtablewidgetitem24 = TableInventory->horizontalHeaderItem(1);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "SKU", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = TableInventory->horizontalHeaderItem(2);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = TableInventory->horizontalHeaderItem(3);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = TableInventory->horizontalHeaderItem(4);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Qt Av.", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = TableInventory->horizontalHeaderItem(5);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Qt Rs.", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = TableInventory->horizontalHeaderItem(6);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "Seuil", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = TableInventory->horizontalHeaderItem(7);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "Unit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = TableInventory->horizontalHeaderItem(8);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = TableInventory->horizontalHeaderItem(9);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = TableInventory->horizontalHeaderItem(10);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "\303\211tag\303\250re", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = TableInventory->horizontalHeaderItem(11);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
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
        InventoryStatus->setItemText(0, QCoreApplication::translate("MainWindow", "-- Tous --", nullptr));
        InventoryStatus->setItemText(1, QCoreApplication::translate("MainWindow", "on_hand", nullptr));
        InventoryStatus->setItemText(2, QCoreApplication::translate("MainWindow", "Limited", nullptr));
        InventoryStatus->setItemText(3, QCoreApplication::translate("MainWindow", "stock_out", nullptr));

        LblInventoryStatus->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        LblInventorySearch->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        BtnInventoryApply->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        BtnInventoryApply->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnInventoryReset->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        InventoryZone->setItemText(0, QCoreApplication::translate("MainWindow", "-- Tous --", nullptr));
        InventoryZone->setItemText(1, QCoreApplication::translate("MainWindow", "A", nullptr));
        InventoryZone->setItemText(2, QCoreApplication::translate("MainWindow", "B", nullptr));
        InventoryZone->setItemText(3, QCoreApplication::translate("MainWindow", "C", nullptr));
        InventoryZone->setItemText(4, QCoreApplication::translate("MainWindow", "D", nullptr));

        LblInventoryZone->setText(QCoreApplication::translate("MainWindow", "Zone", nullptr));
        LblInventoryType->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        LblInventorySort->setText(QCoreApplication::translate("MainWindow", "Trier par", nullptr));
        InventorySort->setItemText(0, QCoreApplication::translate("MainWindow", "SKU", nullptr));
        InventorySort->setItemText(1, QCoreApplication::translate("MainWindow", "Nom (A-Z)", nullptr));
        InventorySort->setItemText(2, QCoreApplication::translate("MainWindow", "Prix (Croissant)", nullptr));
        InventorySort->setItemText(3, QCoreApplication::translate("MainWindow", "Prix (D\303\251croissant)", nullptr));

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
        Sku->setPlaceholderText(QCoreApplication::translate("MainWindow", "ABC-123", nullptr));
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
        LblDescription->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        Description->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez une description...", nullptr));
        BtnPopupAutoSaveInventory->setText(QCoreApplication::translate("MainWindow", "Ajout Automatique", nullptr));
        BtnPopupAutoSaveInventory->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "secondary", nullptr)));
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
        Sku_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "ABC-123", nullptr));
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
        LblDescription_2->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        Description_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez une description...", nullptr));
        BtnPopupSaveInventory_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnPopupSaveInventory_2->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnPopupResetInventory_2->setText(QCoreApplication::translate("MainWindow", "Vider", nullptr));
        BtnPopupResetInventory_2->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        stat_pub_6->setText(QString());
        retour_stat_7->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        aff_header_title->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 24px; font-weight: 900; color: #0B2E1F;", nullptr));
        aff_header_title->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Fiche Produit d\303\251taill\303\251e", nullptr));
        retour_stat_6->setText(QCoreApplication::translate("MainWindow", "\342\206\220 Retour au Stock", nullptr));
        lbl_g1->setText(QCoreApplication::translate("MainWindow", "\360\237\206\224 ID PRODUIT", nullptr));
        aff_id->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_g2->setText(QCoreApplication::translate("MainWindow", "\360\237\224\226 SKU", nullptr));
        aff_sku->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_g3->setText(QCoreApplication::translate("MainWindow", "\360\237\223\233 NOM", nullptr));
        aff_name->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_g4->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 TYPE", nullptr));
        aff_type->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_g5->setText(QCoreApplication::translate("MainWindow", "\360\237\222\260 PRIX", nullptr));
        aff_price->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_g6->setText(QCoreApplication::translate("MainWindow", "\342\234\250 STATUT", nullptr));
        aff_status->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_s1->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 DISPONIBLE", nullptr));
        aff_qtav->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_s2->setText(QCoreApplication::translate("MainWindow", "\360\237\224\222 R\303\211SERV\303\211", nullptr));
        aff_qtrs->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_s3->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 SEUIL MIN", nullptr));
        aff_threshold->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_s4->setText(QCoreApplication::translate("MainWindow", "\360\237\223\217 UNIT\303\211", nullptr));
        aff_unit->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_s5->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215 ZONE", nullptr));
        aff_zone->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_s6->setText(QCoreApplication::translate("MainWindow", "\360\237\252\234 \303\211TAG\303\210RE", nullptr));
        aff_shelf->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        lbl_d1->setText(QCoreApplication::translate("MainWindow", "DESCRIPTION", nullptr));
        aff_description->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        BtnInventoryDetailExportPdf->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        BtnInventoryDetailExportPdf->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        QTableWidgetItem *___qtablewidgetitem35 = tablePublication->horizontalHeaderItem(0);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "Titre", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tablePublication->horizontalHeaderItem(1);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("MainWindow", "resume", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tablePublication->horizontalHeaderItem(2);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("MainWindow", "Inventeurs", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tablePublication->horizontalHeaderItem(3);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("MainWindow", "domaine_fabrication", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tablePublication->horizontalHeaderItem(4);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("MainWindow", "type_brevet", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tablePublication->horizontalHeaderItem(5);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("MainWindow", "numero_brevet", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tablePublication->horizontalHeaderItem(6);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("MainWindow", "date_depot", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tablePublication->horizontalHeaderItem(7);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("MainWindow", "statut_brevet", nullptr));
        lineSearchPub->setText(QString());
        lineSearchPub->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (recherche par Titre , par DOI...)", nullptr));
        btnAppliquerPub->setText(QCoreApplication::translate("MainWindow", "Appliquer", nullptr));
        btnReinitialiserPub->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        comboTriPub->setItemText(0, QCoreApplication::translate("MainWindow", "Titre", nullptr));
        comboTriPub->setItemText(1, QCoreApplication::translate("MainWindow", "Date depot", nullptr));

        lblCategoriePub->setText(QCoreApplication::translate("MainWindow", "TRIER PAR :", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "statistiques par domaines", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "statistiques par statut", nullptr));

        btnVoirStatistiquesPub->setText(QCoreApplication::translate("MainWindow", "voir statistiques", nullptr));
        btnChatbotPub->setText(QCoreApplication::translate("MainWindow", "Chatbot", nullptr));
        btnMailingPub->setText(QCoreApplication::translate("MainWindow", "Mailing", nullptr));
        btnAjouterPub->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierPub->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerPub->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnExporterPub->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        lblStatusBrevetAdd->setText(QCoreApplication::translate("MainWindow", "status_brevet :", nullptr));
        lblTitreAdd->setText(QCoreApplication::translate("MainWindow", "titre :", nullptr));
        comboTypeBrevetAdd->setItemText(0, QCoreApplication::translate("MainWindow", "produit", nullptr));
        comboTypeBrevetAdd->setItemText(1, QCoreApplication::translate("MainWindow", "procede", nullptr));
        comboTypeBrevetAdd->setItemText(2, QCoreApplication::translate("MainWindow", "amelioration", nullptr));

        lblTypeBrevetAdd->setText(QCoreApplication::translate("MainWindow", "type_brevet :", nullptr));
        lblInventeursAdd->setText(QCoreApplication::translate("MainWindow", "inventeurs :", nullptr));
        lblDomaineAdd->setText(QCoreApplication::translate("MainWindow", "domaine_fabrication :", nullptr));
        lblResumeAdd->setText(QCoreApplication::translate("MainWindow", "resume :", nullptr));
        lblDateDepotAdd->setText(QCoreApplication::translate("MainWindow", "date_depot", nullptr));
        lblNumeroBrevetAdd->setText(QCoreApplication::translate("MainWindow", "numero_brevet :", nullptr));
        comboStatusBrevetAdd->setItemText(0, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        comboStatusBrevetAdd->setItemText(1, QCoreApplication::translate("MainWindow", "Depose", nullptr));
        comboStatusBrevetAdd->setItemText(2, QCoreApplication::translate("MainWindow", "Accepte", nullptr));
        comboStatusBrevetAdd->setItemText(3, QCoreApplication::translate("MainWindow", "Refuse", nullptr));
        comboStatusBrevetAdd->setItemText(4, QCoreApplication::translate("MainWindow", "Publie", nullptr));

        btnAddPub->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnRetourAddPub->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lineInventeursAdd->setItemText(0, QCoreApplication::translate("MainWindow", "RH", nullptr));
        lineInventeursAdd->setItemText(1, QCoreApplication::translate("MainWindow", "Responsable_financier", nullptr));
        lineInventeursAdd->setItemText(2, QCoreApplication::translate("MainWindow", "Responsable_de_stock", nullptr));
        lineInventeursAdd->setItemText(3, QCoreApplication::translate("MainWindow", "Chercheur", nullptr));
        lineInventeursAdd->setItemText(4, QCoreApplication::translate("MainWindow", "Directeur_de_projet", nullptr));
        lineInventeursAdd->setItemText(5, QCoreApplication::translate("MainWindow", "Responsable_Labos", nullptr));
        lineInventeursAdd->setItemText(6, QCoreApplication::translate("MainWindow", "Admin", nullptr));

        lblDateDepotEdit->setText(QCoreApplication::translate("MainWindow", "date_depot", nullptr));
        lblTypeBrevetEdit->setText(QCoreApplication::translate("MainWindow", "type_brevet :", nullptr));
        comboStatusBrevetEdit->setItemText(0, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        comboStatusBrevetEdit->setItemText(1, QCoreApplication::translate("MainWindow", "Depose", nullptr));
        comboStatusBrevetEdit->setItemText(2, QCoreApplication::translate("MainWindow", "Accepte", nullptr));
        comboStatusBrevetEdit->setItemText(3, QCoreApplication::translate("MainWindow", "Refuse", nullptr));
        comboStatusBrevetEdit->setItemText(4, QCoreApplication::translate("MainWindow", "Publie", nullptr));

        lblResumeEdit->setText(QCoreApplication::translate("MainWindow", "resume :", nullptr));
        btnConfirmEditPub->setText(QCoreApplication::translate("MainWindow", "confirmer", nullptr));
        btnRetourEditPub->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lblStatusBrevetEdit->setText(QCoreApplication::translate("MainWindow", "status_brevet :", nullptr));
        comboTypeBrevetEdit->setItemText(0, QCoreApplication::translate("MainWindow", "produit", nullptr));
        comboTypeBrevetEdit->setItemText(1, QCoreApplication::translate("MainWindow", "procede", nullptr));
        comboTypeBrevetEdit->setItemText(2, QCoreApplication::translate("MainWindow", "amelioration", nullptr));

        lblTitreEdit->setText(QCoreApplication::translate("MainWindow", "titre :", nullptr));
        lblDomaineEdit->setText(QCoreApplication::translate("MainWindow", "domaine_fabrication :", nullptr));
        lblInventeursEdit->setText(QCoreApplication::translate("MainWindow", "inventeurs :", nullptr));
        lblNumeroBrevetEdit->setText(QCoreApplication::translate("MainWindow", "numero_brevet :", nullptr));
        lineInventeursEdit->setItemText(0, QCoreApplication::translate("MainWindow", "RH", nullptr));
        lineInventeursEdit->setItemText(1, QCoreApplication::translate("MainWindow", "Responsable_financier", nullptr));
        lineInventeursEdit->setItemText(2, QCoreApplication::translate("MainWindow", "Responsable_de_stock", nullptr));
        lineInventeursEdit->setItemText(3, QCoreApplication::translate("MainWindow", "Chercheur", nullptr));
        lineInventeursEdit->setItemText(4, QCoreApplication::translate("MainWindow", "Directeur_de_projet", nullptr));
        lineInventeursEdit->setItemText(5, QCoreApplication::translate("MainWindow", "Responsable_Labos", nullptr));
        lineInventeursEdit->setItemText(6, QCoreApplication::translate("MainWindow", "Admin", nullptr));

        retour_stat->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Chatbot Publications :", nullptr));
        btnEnvoyerQuestionPub->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        btnRetourChatbotPub->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
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
        QTableWidgetItem *___qtablewidgetitem43 = TableFinance->horizontalHeaderItem(0);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("MainWindow", "CODETRANSA", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = TableFinance->horizontalHeaderItem(1);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = TableFinance->horizontalHeaderItem(2);
        ___qtablewidgetitem45->setText(QCoreApplication::translate("MainWindow", "Montant en Dt", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = TableFinance->horizontalHeaderItem(3);
        ___qtablewidgetitem46->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = TableFinance->horizontalHeaderItem(4);
        ___qtablewidgetitem47->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = TableFinance->horizontalHeaderItem(5);
        ___qtablewidgetitem48->setText(QCoreApplication::translate("MainWindow", "Date transaction", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = TableFinance->horizontalHeaderItem(6);
        ___qtablewidgetitem49->setText(QCoreApplication::translate("MainWindow", "Mode paiement", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = TableFinance->horizontalHeaderItem(7);
        ___qtablewidgetitem50->setText(QCoreApplication::translate("MainWindow", "Date cr\303\251ation", nullptr));

        const bool __sortingEnabled = TableFinance->isSortingEnabled();
        TableFinance->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem51 = TableFinance->item(0, 0);
        ___qtablewidgetitem51->setText(QCoreApplication::translate("MainWindow", "TRX001", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = TableFinance->item(0, 1);
        ___qtablewidgetitem52->setText(QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = TableFinance->item(0, 2);
        ___qtablewidgetitem53->setText(QCoreApplication::translate("MainWindow", "120.50", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = TableFinance->item(0, 3);
        ___qtablewidgetitem54->setText(QCoreApplication::translate("MainWindow", "Fournitures", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = TableFinance->item(0, 4);
        ___qtablewidgetitem55->setText(QCoreApplication::translate("MainWindow", "Achat de papier et cartouches d\342\200\231encre", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = TableFinance->item(0, 5);
        ___qtablewidgetitem56->setText(QCoreApplication::translate("MainWindow", "2026-02-15", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = TableFinance->item(0, 6);
        ___qtablewidgetitem57->setText(QCoreApplication::translate("MainWindow", "carte bancaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = TableFinance->item(0, 7);
        ___qtablewidgetitem58->setText(QCoreApplication::translate("MainWindow", "2026-02-15", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = TableFinance->item(1, 0);
        ___qtablewidgetitem59->setText(QCoreApplication::translate("MainWindow", "TRX002", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = TableFinance->item(1, 1);
        ___qtablewidgetitem60->setText(QCoreApplication::translate("MainWindow", "Revenu", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = TableFinance->item(1, 2);
        ___qtablewidgetitem61->setText(QCoreApplication::translate("MainWindow", "850.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = TableFinance->item(1, 3);
        ___qtablewidgetitem62->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = TableFinance->item(1, 4);
        ___qtablewidgetitem63->setText(QCoreApplication::translate("MainWindow", "Paiement mission freelance", nullptr));
        QTableWidgetItem *___qtablewidgetitem64 = TableFinance->item(1, 5);
        ___qtablewidgetitem64->setText(QCoreApplication::translate("MainWindow", "2026-02-10", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = TableFinance->item(1, 6);
        ___qtablewidgetitem65->setText(QCoreApplication::translate("MainWindow", "virement", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = TableFinance->item(1, 7);
        ___qtablewidgetitem66->setText(QCoreApplication::translate("MainWindow", "2026-02-10", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = TableFinance->item(2, 0);
        ___qtablewidgetitem67->setText(QCoreApplication::translate("MainWindow", "TRX003", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = TableFinance->item(2, 1);
        ___qtablewidgetitem68->setText(QCoreApplication::translate("MainWindow", "D\303\251pense", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = TableFinance->item(2, 2);
        ___qtablewidgetitem69->setText(QCoreApplication::translate("MainWindow", "60.00", nullptr));
        QTableWidgetItem *___qtablewidgetitem70 = TableFinance->item(2, 3);
        ___qtablewidgetitem70->setText(QCoreApplication::translate("MainWindow", "Transport", nullptr));
        QTableWidgetItem *___qtablewidgetitem71 = TableFinance->item(2, 4);
        ___qtablewidgetitem71->setText(QCoreApplication::translate("MainWindow", "Frais d\303\251placement client", nullptr));
        QTableWidgetItem *___qtablewidgetitem72 = TableFinance->item(2, 5);
        ___qtablewidgetitem72->setText(QCoreApplication::translate("MainWindow", "2026-02-18", nullptr));
        QTableWidgetItem *___qtablewidgetitem73 = TableFinance->item(2, 6);
        ___qtablewidgetitem73->setText(QCoreApplication::translate("MainWindow", "especes", nullptr));
        QTableWidgetItem *___qtablewidgetitem74 = TableFinance->item(2, 7);
        ___qtablewidgetitem74->setText(QCoreApplication::translate("MainWindow", "2026-02-18", nullptr));
        TableFinance->setSortingEnabled(__sortingEnabled);

        BtnAdd->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        BtnEdit->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnDelete->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        BtnAdd_4->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        BtnExport->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
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
        BtnAmountDecr->setText(QCoreApplication::translate("MainWindow", "\342\210\222", nullptr));
        FormAmount->setPlaceholderText(QCoreApplication::translate("MainWindow", "ex: 2500", nullptr));
        BtnAmountIncr->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(tooltip)
        BtnConvertCurrency->setToolTip(QCoreApplication::translate("MainWindow", "Convertir EUR / USD / GBP \342\206\222 DT en temps r\303\251el", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnConvertCurrency->setText(QCoreApplication::translate("MainWindow", " Convertir \360\237\222\261", nullptr));
        FormCategory->setPlaceholderText(QString());
#if QT_CONFIG(tooltip)
        BtnOcrReceipt->setToolTip(QCoreApplication::translate("MainWindow", "Importez une image de re\303\247u : montant, date et cat\303\251gorie extraits automatiquement", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnOcrReceipt->setText(QCoreApplication::translate("MainWindow", "\360\237\223\267   Scanner un re\303\247u ou une facture   \342\200\224   remplissage automatique du formulaire", nullptr));
        LblOcrHint->setText(QCoreApplication::translate("MainWindow", "\360\237\222\241  Conseil : utilisez une photo nette, bien \303\251clair\303\251e pour une meilleure pr\303\251cision de reconnaissance.", nullptr));
        FormPayMode_2->setItemText(0, QCoreApplication::translate("MainWindow", "Especes", nullptr));
        FormPayMode_2->setItemText(1, QCoreApplication::translate("MainWindow", "Cheque", nullptr));
        FormPayMode_2->setItemText(2, QCoreApplication::translate("MainWindow", "Virement", nullptr));
        FormPayMode_2->setItemText(3, QCoreApplication::translate("MainWindow", "Carte bancaire", nullptr));
        FormPayMode_2->setItemText(4, QCoreApplication::translate("MainWindow", "Facture", nullptr));
        FormPayMode_2->setItemText(5, QCoreApplication::translate("MainWindow", "Remboursement", nullptr));

        FormCategory_2->setPlaceholderText(QString());
        LblCode_2->setText(QCoreApplication::translate("MainWindow", "Code transaction", nullptr));
        FormType_2->setItemText(0, QCoreApplication::translate("MainWindow", "Depense", nullptr));
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
        BtnAmountDecr_2->setText(QCoreApplication::translate("MainWindow", "\342\210\222", nullptr));
        FormAmount_2->setPlaceholderText(QString());
        BtnAmountIncr_2->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(tooltip)
        BtnConvertCurrency_2->setToolTip(QCoreApplication::translate("MainWindow", "Convertir EUR / USD / GBP \342\206\222 DT en temps r\303\251el", nullptr));
#endif // QT_CONFIG(tooltip)
        BtnConvertCurrency_2->setText(QCoreApplication::translate("MainWindow", "\360\237\222\261 Convertir", nullptr));
        stat_pub_3->setText(QString());
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "D\303\251penses vs Revenus", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Statistiques de Revenus", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Statistiques de D\303\251penses", nullptr));

        retour_stat_4->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        retour_stat_5->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        stat_pub_4->setText(QString());
        LabsSearch_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "nom, responsable, localisation, num\303\251ro\342\200\246", nullptr));
        LabsSpec_2->setItemText(0, QCoreApplication::translate("MainWindow", "choisir un specialite", nullptr));
        LabsSpec_2->setItemText(1, QCoreApplication::translate("MainWindow", "interieur", nullptr));
        LabsSpec_2->setItemText(2, QCoreApplication::translate("MainWindow", "exterieur", nullptr));

        LabsCap_2->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir disponibilite", nullptr));
        LabsCap_2->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));
        LabsCap_2->setItemText(2, QCoreApplication::translate("MainWindow", "Occupe", nullptr));

#if QT_CONFIG(tooltip)
        btnLabReserveProduct->setToolTip(QCoreApplication::translate("MainWindow", "S\303\251lectionner un produit du stock et une quantit\303\251 r\303\251serv\303\251e pour les laboratoires (refl\303\251t\303\251 dans les statistiques inventaire)", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLabReserveProduct->setText(QCoreApplication::translate("MainWindow", "R\303\251server un produit (inventaire)", nullptr));
        btnReinitialiserPub_3->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        QTableWidgetItem *___qtablewidgetitem75 = TableLabs_2->horizontalHeaderItem(0);
        ___qtablewidgetitem75->setText(QCoreApplication::translate("MainWindow", "Nom Labo", nullptr));
        QTableWidgetItem *___qtablewidgetitem76 = TableLabs_2->horizontalHeaderItem(1);
        ___qtablewidgetitem76->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        QTableWidgetItem *___qtablewidgetitem77 = TableLabs_2->horizontalHeaderItem(2);
        ___qtablewidgetitem77->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        QTableWidgetItem *___qtablewidgetitem78 = TableLabs_2->horizontalHeaderItem(3);
        ___qtablewidgetitem78->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        QTableWidgetItem *___qtablewidgetitem79 = TableLabs_2->horizontalHeaderItem(4);
        ___qtablewidgetitem79->setText(QCoreApplication::translate("MainWindow", "disponibilite", nullptr));
        QTableWidgetItem *___qtablewidgetitem80 = TableLabs_2->horizontalHeaderItem(5);
        ___qtablewidgetitem80->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem81 = TableLabs_2->horizontalHeaderItem(6);
        ___qtablewidgetitem81->setText(QCoreApplication::translate("MainWindow", "Paiement", nullptr));
        QTableWidgetItem *___qtablewidgetitem82 = TableLabs_2->horizontalHeaderItem(7);
        ___qtablewidgetitem82->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        QTableWidgetItem *___qtablewidgetitem83 = TableLabs_2->horizontalHeaderItem(8);
        ___qtablewidgetitem83->setText(QCoreApplication::translate("MainWindow", "Montant_paye", nullptr));
        QTableWidgetItem *___qtablewidgetitem84 = TableLabs_2->horizontalHeaderItem(9);
        ___qtablewidgetitem84->setText(QCoreApplication::translate("MainWindow", "Reste", nullptr));
        QTableWidgetItem *___qtablewidgetitem85 = TableLabs_2->horizontalHeaderItem(10);
        ___qtablewidgetitem85->setText(QCoreApplication::translate("MainWindow", "Resultat", nullptr));
        btnAjouterPub_3->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        btnAjouterPub_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierPub_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerPub_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnStatLabs->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Reste", nullptr));
        BtnPopupResetLabs_5->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        lblPageTitle_4->setText(QCoreApplication::translate("MainWindow", "Modifier un laboratoire", nullptr));
        LblLabName_5->setText(QCoreApplication::translate("MainWindow", "Nom labo", nullptr));
        LabName_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Laboratoire IA", nullptr));
        LblLabResp_5->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        LabResponsible_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom responsable", nullptr));
        LblLabLoc_5->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        LabLocation_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Bloc B, Salle 204", nullptr));
        LblLabNum_5->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        LabNumber_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "204", nullptr));
        LblLabSpec_5->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        LabSpec_5->setItemText(0, QCoreApplication::translate("MainWindow", "modifier votre specialite", nullptr));
        LabSpec_5->setItemText(1, QCoreApplication::translate("MainWindow", "interieur", nullptr));
        LabSpec_5->setItemText(2, QCoreApplication::translate("MainWindow", "exterieur", nullptr));

        LblLabCap_5->setText(QCoreApplication::translate("MainWindow", "Disponibilite", nullptr));
        LabCap_5->setItemText(0, QCoreApplication::translate("MainWindow", "choisir votre Disponabilite", nullptr));
        LabCap_5->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));
        LabCap_5->setItemText(2, QCoreApplication::translate("MainWindow", "Occupe", nullptr));

        LblLabSpec_14->setText(QCoreApplication::translate("MainWindow", "Resultat", nullptr));
        LabSpec_6->setItemText(0, QCoreApplication::translate("MainWindow", "modifier votre resultat", nullptr));
        LabSpec_6->setItemText(1, QCoreApplication::translate("MainWindow", "pr\303\251t", nullptr));
        LabSpec_6->setItemText(2, QCoreApplication::translate("MainWindow", "En attente", nullptr));
        LabSpec_6->setItemText(3, QCoreApplication::translate("MainWindow", "En ex\303\251cution", nullptr));

        LblLabSpec_15->setText(QCoreApplication::translate("MainWindow", "Paiement", nullptr));
        LabCap_6->setItemText(0, QCoreApplication::translate("MainWindow", "choisir votre paiement", nullptr));
        LabCap_6->setItemText(1, QCoreApplication::translate("MainWindow", "payer", nullptr));
        LabCap_6->setItemText(2, QCoreApplication::translate("MainWindow", "non payer", nullptr));

        label_22->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Montant_paye", nullptr));
        BtnPopupSaveLabs_5->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        BtnPopupSaveLabs_5->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        retour_stat_9->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Reste", nullptr));
        lblPageTitle_3->setText(QCoreApplication::translate("MainWindow", "Ajouter un laboratoire", nullptr));
        LblLabName_3->setText(QCoreApplication::translate("MainWindow", "Nom labo", nullptr));
        LabName_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Laboratoire IA", nullptr));
        LblLabResp_3->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        LabResponsible_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom responsable", nullptr));
        LblLabLoc_3->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        LabLocation_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Bloc B, Salle 204", nullptr));
        LblLabNum_3->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        LabNumber_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "204", nullptr));
        LblLabSpec_3->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        LabSpec_3->setItemText(0, QCoreApplication::translate("MainWindow", "choisir un  specialite", nullptr));
        LabSpec_3->setItemText(1, QCoreApplication::translate("MainWindow", "interieur", nullptr));
        LabSpec_3->setItemText(2, QCoreApplication::translate("MainWindow", "exterieur", nullptr));

        LblLabCap_3->setText(QCoreApplication::translate("MainWindow", "Disponibilite", nullptr));
        LabCap_3->setItemText(0, QCoreApplication::translate("MainWindow", "choisir le Disponabilite", nullptr));
        LabCap_3->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));
        LabCap_3->setItemText(2, QCoreApplication::translate("MainWindow", "Occupe", nullptr));

        LblLabSpec_12->setText(QCoreApplication::translate("MainWindow", "Resultat", nullptr));
        LabSpec_4->setItemText(0, QCoreApplication::translate("MainWindow", "choisir un  resultat", nullptr));
        LabSpec_4->setItemText(1, QCoreApplication::translate("MainWindow", "En ex\303\251cution", nullptr));
        LabSpec_4->setItemText(2, QCoreApplication::translate("MainWindow", "En attente", nullptr));
        LabSpec_4->setItemText(3, QCoreApplication::translate("MainWindow", "Pr\303\252t", nullptr));

        LblLabSpec_13->setText(QCoreApplication::translate("MainWindow", "Paiement", nullptr));
        LabCap_4->setItemText(0, QCoreApplication::translate("MainWindow", "choisir le Paiement", nullptr));
        LabCap_4->setItemText(1, QCoreApplication::translate("MainWindow", "payer", nullptr));
        LabCap_4->setItemText(2, QCoreApplication::translate("MainWindow", "non payer", nullptr));

        label_20->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Montant_paye", nullptr));
        BtnPopupSaveLabs_3->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        BtnPopupSaveLabs_3->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "primary", nullptr)));
        BtnPopupResetLabs_3->setText(QCoreApplication::translate("MainWindow", "Vider", nullptr));
        BtnPopupResetLabs_3->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "ghost", nullptr)));
        retour_stat_8->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        retour_stat_2->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir votre domaine", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "statistiques par Specialite", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "statistiques par Disponabilite", nullptr));

        stat_pub_2->setText(QString());
        lblPageTitle_2->setText(QCoreApplication::translate("MainWindow", "Affichage d'un laboratoire", nullptr));
        LblLabName_6->setText(QCoreApplication::translate("MainWindow", "Nom labo", nullptr));
        aff1->setPlaceholderText(QCoreApplication::translate("MainWindow", "Laboratoire IA", nullptr));
        LblLabResp_6->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        aff5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom responsable", nullptr));
        LblLabLoc_6->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        aff2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Bloc B, Salle 204", nullptr));
        LblLabNum_6->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro", nullptr));
        aff6->setPlaceholderText(QCoreApplication::translate("MainWindow", "204", nullptr));
        LblLabSpec_6->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        aff3->setItemText(0, QCoreApplication::translate("MainWindow", "choisir un  specialite", nullptr));
        aff3->setItemText(1, QCoreApplication::translate("MainWindow", "interieur", nullptr));
        aff3->setItemText(2, QCoreApplication::translate("MainWindow", "exterieur", nullptr));

        LblLabCap_6->setText(QCoreApplication::translate("MainWindow", "Disponibilit\303\251", nullptr));
        aff7->setItemText(0, QCoreApplication::translate("MainWindow", "choisir la disponibilite", nullptr));
        aff7->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));
        aff7->setItemText(2, QCoreApplication::translate("MainWindow", "Occupe", nullptr));

        LblLabSpec_7->setText(QCoreApplication::translate("MainWindow", "R\303\251sultat", nullptr));
        aff3_2->setItemText(0, QCoreApplication::translate("MainWindow", "choisir un  resultat", nullptr));
        aff3_2->setItemText(1, QCoreApplication::translate("MainWindow", "En ex\303\251cution", nullptr));
        aff3_2->setItemText(2, QCoreApplication::translate("MainWindow", "En attente", nullptr));
        aff3_2->setItemText(3, QCoreApplication::translate("MainWindow", "Pr\303\252t", nullptr));

        LblLabSpec_8->setText(QCoreApplication::translate("MainWindow", "Paiement", nullptr));
        aff7_2->setItemText(0, QCoreApplication::translate("MainWindow", "choisir le paiement", nullptr));
        aff7_2->setItemText(1, QCoreApplication::translate("MainWindow", "payer", nullptr));
        aff7_2->setItemText(2, QCoreApplication::translate("MainWindow", "non payer", nullptr));

        label_16->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Montant pay\303\251", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Reste", nullptr));
        labQrTitle->setStyleSheet(QCoreApplication::translate("MainWindow", "font-weight:bold; font-size:12px; color:#333;", nullptr));
        labQrTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\261 QR Code statut", nullptr));
        labQrDisplay->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#f8f8f8; border:2px dashed #ccc; border-radius:10px; color:#aaa; font-size:11px; padding:4px;", nullptr));
        labQrDisplay->setText(QCoreApplication::translate("MainWindow", "S\303\251lectionnez un laboratoire", nullptr));
        labQrHint->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:13px; font-weight:bold; padding:6px; border-radius:8px;", nullptr));
        labQrHint->setText(QCoreApplication::translate("MainWindow", "\342\200\224", nullptr));
        labQrUrl->setStyleSheet(QCoreApplication::translate("MainWindow", "color:#999; font-size:9px;", nullptr));
        labQrUrl->setText(QString());
#if QT_CONFIG(tooltip)
        btnPaiementLab->setToolTip(QCoreApplication::translate("MainWindow", "Effectuer un paiement pour ce laboratoire", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPaiementLab->setText(QCoreApplication::translate("MainWindow", "Paiement", nullptr));
        BtnExportLabsDirect->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        retour_stat_3->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        lblLabReserveTitle->setText(QCoreApplication::translate("MainWindow", "R\303\251servation produit \342\200\224 stock inventaire pour les laboratoires", nullptr));
        lblLabReserveHint->setText(QCoreApplication::translate("MainWindow", "S\303\251lectionnez une ligne, indiquez la quantit\303\251 \303\240 r\303\251server, puis Valider. La quantit\303\251 r\303\251serv\303\251e (QT_RS) et les statistiques inventaire sont mises \303\240 jour.", nullptr));
        lblLabReserveQty->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 \303\240 r\303\251server", nullptr));
        btnLabReserveValidate->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        btnLabReserveBack->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        lineSearchProj->setText(QString());
        lineSearchProj->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher (recherche par DOI...)", nullptr));
        comboCategorieProj->setItemText(0, QCoreApplication::translate("MainWindow", "date", nullptr));
        comboCategorieProj->setItemText(1, QCoreApplication::translate("MainWindow", "titre", nullptr));

        btnAppliquerProj->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        btnFiltrerDateProj->setText(QCoreApplication::translate("MainWindow", "Chercher par date", nullptr));
        lblCategorieProj->setText(QCoreApplication::translate("MainWindow", "TRIER PAR :", nullptr));
        lblPeriodeDuProj->setText(QCoreApplication::translate("MainWindow", "DATE", nullptr));
        QTableWidgetItem *___qtablewidgetitem86 = tableProjets->horizontalHeaderItem(0);
        ___qtablewidgetitem86->setText(QCoreApplication::translate("MainWindow", "nom_Projet ", nullptr));
        QTableWidgetItem *___qtablewidgetitem87 = tableProjets->horizontalHeaderItem(1);
        ___qtablewidgetitem87->setText(QCoreApplication::translate("MainWindow", "description", nullptr));
        QTableWidgetItem *___qtablewidgetitem88 = tableProjets->horizontalHeaderItem(2);
        ___qtablewidgetitem88->setText(QCoreApplication::translate("MainWindow", "objectifs  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem89 = tableProjets->horizontalHeaderItem(3);
        ___qtablewidgetitem89->setText(QCoreApplication::translate("MainWindow", "date_D\303\251but    ", nullptr));
        QTableWidgetItem *___qtablewidgetitem90 = tableProjets->horizontalHeaderItem(4);
        ___qtablewidgetitem90->setText(QCoreApplication::translate("MainWindow", "date_Fin_Prevue  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem91 = tableProjets->horizontalHeaderItem(5);
        ___qtablewidgetitem91->setText(QCoreApplication::translate("MainWindow", "date_Fin_Reelle  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem92 = tableProjets->horizontalHeaderItem(6);
        ___qtablewidgetitem92->setText(QCoreApplication::translate("MainWindow", "statut  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem93 = tableProjets->horizontalHeaderItem(7);
        ___qtablewidgetitem93->setText(QCoreApplication::translate("MainWindow", "priorite ", nullptr));
        btnAjouterProj->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierProj->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerProj->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
#if QT_CONFIG(tooltip)
        btnSmsProj->setToolTip(QCoreApplication::translate("MainWindow", "Envoyer un SMS d'alerte pour ce projet", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSmsProj->setText(QCoreApplication::translate("MainWindow", "SMS", nullptr));
        btnVoirStatistiquesProj->setText(QCoreApplication::translate("MainWindow", "voir statistiques", nullptr));
#if QT_CONFIG(tooltip)
        btnExportPdfProj->setToolTip(QCoreApplication::translate("MainWindow", "Exporter les informations du projet s\303\251lectionn\303\251 en PDF", nullptr));
#endif // QT_CONFIG(tooltip)
        btnExportPdfProj->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnAddProj->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnRetourAddProj->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lineResumeAddProj->setItemText(0, QCoreApplication::translate("MainWindow", "Urgent", nullptr));
        lineResumeAddProj->setItemText(1, QCoreApplication::translate("MainWindow", "N'est pas urgent", nullptr));

        lblTypeBrevetAddProj->setText(QCoreApplication::translate("MainWindow", "objectifs  ", nullptr));
        lblDomaineAddProj->setText(QCoreApplication::translate("MainWindow", "description  ", nullptr));
        lblStatusBrevetAddProj->setText(QCoreApplication::translate("MainWindow", "date_Fin_Reelle  ", nullptr));
        lblResumeAddProj->setText(QCoreApplication::translate("MainWindow", "priorite ", nullptr));
        lblDateDepotAddProj->setText(QCoreApplication::translate("MainWindow", "date_Fin_Prevue  ", nullptr));
        lblNumeroBrevetAddProj->setText(QCoreApplication::translate("MainWindow", "date_D\303\251but    ", nullptr));
        lineInventeursAddProj->setItemText(0, QCoreApplication::translate("MainWindow", "N'a pas encore commenc\303\251", nullptr));
        lineInventeursAddProj->setItemText(1, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        lineInventeursAddProj->setItemText(2, QCoreApplication::translate("MainWindow", "Termin\303\251", nullptr));

        lblTitreAddProj->setText(QCoreApplication::translate("MainWindow", "nom_Projet ", nullptr));
        lblInventeursAddProj->setText(QCoreApplication::translate("MainWindow", "statut  ", nullptr));
        lblInventeursEditProj->setText(QCoreApplication::translate("MainWindow", "statut  ", nullptr));
        lblTypeBrevetEditProj->setText(QCoreApplication::translate("MainWindow", "objectifs  ", nullptr));
        lineResumeEditProj->setItemText(0, QCoreApplication::translate("MainWindow", "Urgent", nullptr));
        lineResumeEditProj->setItemText(1, QCoreApplication::translate("MainWindow", "N'est pas urgent", nullptr));

        lblDomaineEditProj->setText(QCoreApplication::translate("MainWindow", "description  ", nullptr));
        lblResumeEditProj->setText(QCoreApplication::translate("MainWindow", "priorite ", nullptr));
        btnConfirmEditProj->setText(QCoreApplication::translate("MainWindow", "confirmer", nullptr));
        btnRetourEditProj->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        lineInventeursEditProj->setItemText(0, QCoreApplication::translate("MainWindow", "N'a pas encore commenc\303\251", nullptr));
        lineInventeursEditProj->setItemText(1, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        lineInventeursEditProj->setItemText(2, QCoreApplication::translate("MainWindow", "Termin\303\251", nullptr));

        lblDateDepotEditProj->setText(QCoreApplication::translate("MainWindow", "date_D\303\251but    ", nullptr));
        lblTitreEditProj->setText(QCoreApplication::translate("MainWindow", "nom_Projet ", nullptr));
        lblStatusBrevetEditProj->setText(QCoreApplication::translate("MainWindow", "date_Fin_Reelle  ", nullptr));
        lblNumeroBrevetEditProj->setText(QCoreApplication::translate("MainWindow", "date_Fin_Prevue  ", nullptr));
        lblStatsTitleProj->setText(QCoreApplication::translate("MainWindow", "Statistiques des Projets", nullptr));
        retour_statn->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
