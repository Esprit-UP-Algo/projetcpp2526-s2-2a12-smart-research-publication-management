#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>




/*
    MAINWINDOW.CPP (COMPLET)
    - QSS long et détaillé intégré
    - Sidebar + stackedWidget
    - Bouton actif avec property active=true
    - Déconnecter: confirmation + quit
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{


    ui->setupUi(this);



    // ===== INIT FINANCE =====
    initFinanceUi();


    // ===== Table Publication : lignes séparatrices + alignement =====
    ui->tablePublication->setShowGrid(true);
    ui->tablePublication->setGridStyle(Qt::SolidLine);

    ui->tablePublication->setAlternatingRowColors(false);


    // ✅ Colonnes toutes égales
    auto header = ui->tablePublication->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);   // toutes les colonnes partagent l'espace
    header->setStretchLastSection(false);                 // important : désactive l'ancien comportement
    header->setDefaultAlignment(Qt::AlignCenter);


    ui->tablePublication->verticalHeader()->setVisible(false);
    ui->tablePublication->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePublication->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tablePublication->setEditTriggers(QAbstractItemView::NoEditTriggers); // optionnel
    ui->tablePublication->setWordWrap(false);
    ui->tablePublication->setSortingEnabled(true); // optionnel

    updateTopTitle(ui->stackedWidget->currentIndex());

    connect(ui->stackedWidget, &QStackedWidget::currentChanged,
            this, &MainWindow::updateTopTitle);


    ui->lblBrand->setText(R"(
    <span style="color:#0B1220; font-weight:900;">Smart</span>
    <span style="color:#1F8E95; font-weight:900;">ResearchLab</span>
    )");
    ui->lblBrand->setTextFormat(Qt::RichText);


    // ✅ ICI (juste après setupUi)
    ui->btnEmployee->setCheckable(true);
    ui->btnInventaire->setCheckable(true);
    ui->btnPublication->setCheckable(true);
    ui->btnFinance->setCheckable(true);
    ui->btnLaboratoires->setCheckable(true);
    ui->btnProjets->setCheckable(true);


    // Optionnel: enlever le focus rectangle sur les boutons (plus propre)
    ui->btnEmployee->setFocusPolicy(Qt::NoFocus);
    ui->btnInventaire->setFocusPolicy(Qt::NoFocus);
    ui->btnPublication->setFocusPolicy(Qt::NoFocus);
    ui->btnFinance->setFocusPolicy(Qt::NoFocus);
    ui->btnLaboratoires->setFocusPolicy(Qt::NoFocus);
    ui->btnProjets->setFocusPolicy(Qt::NoFocus);
    ui->btnDeconnecter->setFocusPolicy(Qt::NoFocus);

    // Appliquer le style moderne
    applyModernStyle();

    // Connexions boutons -> pages
    connect(ui->btnEmployee,     &QPushButton::clicked, this, &MainWindow::goEmployee);
    connect(ui->btnInventaire,   &QPushButton::clicked, this, &MainWindow::goInventaire);
    connect(ui->btnPublication,  &QPushButton::clicked, this, &MainWindow::goPublication);
    connect(ui->btnFinance,      &QPushButton::clicked, this, &MainWindow::goFinance);
    connect(ui->btnLaboratoires, &QPushButton::clicked, this, &MainWindow::goLaboratoires);
    connect(ui->btnProjets,      &QPushButton::clicked, this, &MainWindow::goProjets);

    // Déconnecter (pas de page)
    connect(ui->btnDeconnecter,  &QPushButton::clicked, this, &MainWindow::onDeconnecter);

    // Page par défaut
    ui->stackedWidget->setCurrentIndex(0);
    setActiveButton(ui->btnEmployee);

    // Optionnel : Ombre douce sur sidebar et contenu (look plus "pro")
    auto shadowSidebar = new QGraphicsDropShadowEffect(this);
    shadowSidebar->setBlurRadius(22);
    shadowSidebar->setOffset(0, 6);
    shadowSidebar->setColor(QColor(0, 0, 0, 60));
    ui->sidebarFrame->setGraphicsEffect(shadowSidebar);

    auto shadowStack = new QGraphicsDropShadowEffect(this);
    shadowStack->setBlurRadius(22);
    shadowStack->setOffset(0, 6);
    shadowStack->setColor(QColor(0, 0, 0, 60));
    ui->stackedWidget->setGraphicsEffect(shadowStack);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::applyModernStyle()
{
    /*
      QSS très détaillé :
      - Palette moderne (bleu/vert/blanc)
      - Bordures noires
      - Boutons "capsule" et état actif (gradient)
      - Hover/Pressed/Disabled
      - Scrollbars (si tu ajoutes des tables/listes plus tard)
      - MessageBox stylé
      - ToolTip stylé
    */

    const QString qss = R"(

/* =========================================================
   GLOBAL / BASE
   ========================================================= */
QMainWindow {
    background-color: #F3F7FF; /* fond très léger */
}

QWidget {
    font-family: "Segoe UI", "Inter", "Arial";
    font-size: 13px;
    color: #0F172A;
}

/* ToolTip */
QToolTip {
    background: #0F172A;
    color: white;
    border: 1px solid #111111;
    padding: 6px 10px;
    border-radius: 8px;
}

QWidget#centralwidget {
    background-color: #F4F6F8;   /* blanc sale moderne */
}


QLabel#lblPageTitle {
    font-size: 18px;
    font-weight: 900;
    color: #1F8E95;
    letter-spacing: 0.5px;
}


QLabel#logoLabel {
    min-height: 210px;

    background-image: url(":/img/images/logoLabel.png");
    background-repeat: no-repeat;
    background-position: center;
    background-size: contain;
}

QLabel#stat_pub {
    min-height: 100px;

    background-image: url(":/img/images/stat_pub.png");
    background-repeat: no-repeat;
    background-position: center;
    background-size: contain;
}

/* =========================================================
   SIDEBAR
   ========================================================= */
QFrame#sidebarFrame {      /* tu peux garder la bordure noire */
    border-radius: 18px;

    background-color: #F8FBFC;
    background-image: url(":/img/images/sidebar_bg.png");
    background-repeat: no-repeat;
    background-position: left bottom;
    background-size: 260px 600px;   /* ajuste si besoin */
}

/* Titre */
QLabel#titleLabel {
    font-size: 18px;
    font-weight: 800;
    color: #0B1220;
    padding: 12px 10px;
    margin: 6px 6px 0px 6px;
    border-radius: 12px;


}


/* =========================================================
   SIDEBAR BUTTONS (TEAL LIKE SCREENSHOT)
   ========================================================= */

QPushButton {
    min-height: 46px;
    padding: 12px 18px;
    margin: 6px 10px;

    border-radius: 12px;
    border: none;

    color: #FFFFFF;
    font-size: 14px;
    font-weight: 800;
    letter-spacing: 1px;

    text-align: left;

    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #2EBBC3,
        stop:1 #1F8E95
    );
}

/* Hover */
QPushButton:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #3CCAD3,
        stop:1 #28A3AB
    );
}

/* Pressed */
QPushButton:pressed {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #1C8A91,
        stop:1 #166F75
    );
}

/* Reste cliqué */
QPushButton:checked {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #177A80,
        stop:1 #135F63
    );

    border: 2px solid rgba(255, 255, 255, 0.45);
}

/* ==============================
   BOUTON ACTIF (reste cliqué)
   ============================== */

QPushButton:checked {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #1F8E95,
        stop:1 #166F75
    );

    border: 2px solid rgba(0, 0, 0, 0.65);
    color: white;
}

/* Actif + hover (légèrement plus clair) */
QPushButton:checked:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #238F96,
        stop:1 #18797E
    );
}

/* =========================================================
   LOGOUT BUTTON
   ========================================================= */
QPushButton#btnDeconnecter {
    color: #B91C1C;
    background-color: #FFFFFF;
    border: 2px solid #111111;
}

QPushButton#btnDeconnecter:hover {
    background-color: #FFECEC;
}

QPushButton#btnDeconnecter:pressed {
    background-color: #FFD6D6;
}

/* =========================================================
   STACKED WIDGET BACKGROUND IMAGE
   ========================================================= */
QStackedWidget#stackedWidget {
    border-radius: 16px;
    border: 2px solid #111111;

    background-image: url(":/img/images/background.png");
    background-repeat: no-repeat;
    background-position: center;
    background-size: cover;
}


/* Pages */
QStackedWidget QWidget {
    background-color: transparent;
}

/* Les labels dans les pages */
QLabel {
    color: #0F172A;
}

/* Si tu veux que les gros titres des pages soient plus grands :
   -> Donne objectName aux labels (ex: labelEmployee, labelFinance...) */
QLabel#labelEmployee,
QLabel#labelInventaire,
QLabel#labelPublication,
QLabel#labelFinance,
QLabel#labelLaboratoires,
QLabel#labelProjets {
    font-size: 22px;
    font-weight: 900;
}


/* =========================================================
   SCROLLBARS (utile pour plus tard: tables, listes, scrollarea)
   ========================================================= */
QScrollBar:vertical {
    background: #F1F5F9;
    width: 12px;
    margin: 10px 4px 10px 4px;
    border-radius: 6px;
    border: 1px solid #111111;
}

QScrollBar::handle:vertical {
    background: #1D4ED8;
    min-height: 30px;
    border-radius: 6px;
    border: 1px solid #111111;
}

QScrollBar::handle:vertical:hover {
    background: #2563EB;
}

QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical {
    height: 0px;
    width: 0px;
}

QScrollBar::add-page:vertical,
QScrollBar::sub-page:vertical {
    background: none;
}

QScrollBar:horizontal {
    background: #F1F5F9;
    height: 12px;
    margin: 4px 10px 4px 10px;
    border-radius: 6px;
    border: 1px solid #111111;
}

QScrollBar::handle:horizontal {
    background: #10B981;
    min-width: 30px;
    border-radius: 6px;
    border: 1px solid #111111;
}

QScrollBar::handle:horizontal:hover {
    background: #34D399;
}

QScrollBar::add-line:horizontal,
QScrollBar::sub-line:horizontal {
    height: 0px;
    width: 0px;
}

QScrollBar::add-page:horizontal,
QScrollBar::sub-page:horizontal {
    background: none;
}

/* =========================================================
   TABLES / INPUTS (si tu ajoutes QTableWidget, QLineEdit...)
   ========================================================= */
QLineEdit, QTextEdit, QPlainTextEdit, QComboBox, QSpinBox, QDoubleSpinBox, QDateEdit {
    border: 2px solid #111111;
    border-radius: 10px;
    padding: 6px 10px;
    background: #FFFFFF;
    selection-background-color: #1D4ED8;
    selection-color: white;
}

QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus, QComboBox:focus {
    border: 2px solid #1D4ED8;
}

QTableWidget {
    border: 2px solid #111111;
    border-radius: 12px;
    gridline-color: #111111;
    background: #FFFFFF;
}

QHeaderView::section {
    background: #FFFFFF;
    border: 1px solid #111111;
    padding: 8px;
    font-weight: 800;
}

/* =========================================================
   MESSAGE BOX (QMessageBox)
   ========================================================= */
QMessageBox {
    background: #FFFFFF;
}

QMessageBox QLabel {
    color: #0F172A;
    font-size: 14px;
    font-weight: 700;
}

QMessageBox QPushButton {
    min-width: 90px;
    text-align: center;
}

/* =========================================================
   FIN
   ========================================================= */
/* =========================================================
   PUBLICATION (stack_pub) : TABLE BLANCHE + BORDURES VERTES
   + BOUTONS VERT MODERNE
   ========================================================= */

/* ---- TABLE (uniquement celle de Publication) ---- */
QStackedWidget#stack_pub QTableWidget,
QStackedWidget#stack_pub QTableView {
    background: #FFFFFF;
    border: 2px solid #18A06A;      /* vert moderne */
    border-radius: 12px;
    gridline-color: #18A06A;
    selection-background-color: rgba(24,160,106,35);
    selection-color: #0B2E1F;
}

QStackedWidget#stack_pub QHeaderView::section {
    background: #FFFFFF;
    color: #0B2E1F;
    border: 1px solid #18A06A;
    padding: 8px 10px;
    font-weight: 800;
}

QStackedWidget#stack_pub QTableCornerButton::section {
    background: #FFFFFF;
    border: 1px solid #18A06A;
}

/* (optionnel) scrollbars du tableau */
QStackedWidget#stack_pub QScrollBar::handle:vertical,
QStackedWidget#stack_pub QScrollBar::handle:horizontal {
    background: rgba(24,160,106,140);
    border: 1px solid rgba(15,127,85,140);
}

/* ---- INPUTS de Publication (search/combobox/date) en blanc bord vert ---- */
QStackedWidget#stack_pub QLineEdit,
QStackedWidget#stack_pub QComboBox,
QStackedWidget#stack_pub QDateEdit {
    background: #FFFFFF;
    border: 2px solid #18A06A;
    border-radius: 10px;
    padding: 6px 10px;
    color: #0B2E1F;
}

QStackedWidget#stack_pub QLineEdit:focus,
QStackedWidget#stack_pub QComboBox:focus,
QStackedWidget#stack_pub QDateEdit:focus {
    border: 2px solid #0F7F55;
}

QStackedWidget#stack_pub QComboBox::drop-down,
QStackedWidget#stack_pub QDateEdit::drop-down {
    border-left: 2px solid #18A06A;
    width: 28px;
}

/* ---- BOUTONS dans stack_pub (vert moderne) ---- */
QStackedWidget#stack_pub QPushButton {
    min-height: 42px;
    padding: 10px 18px;
    margin: 6px 10px;

    border-radius: 12px;
    border: 2px solid #0F7F55;

    color: #FFFFFF;
    font-size: 14px;
    font-weight: 800;
    letter-spacing: 1px;
    text-align: center;

    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #18A06A,
        stop:1 #1BBE7B
    );
}

QStackedWidget#stack_pub QPushButton:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #1BBE7B,
        stop:1 #35D596
    );
}

QStackedWidget#stack_pub QPushButton:pressed {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #0F7F55,
        stop:1 #0B6A47
    );
}

/* (optionnel) si tu veux que "Supprimer" soit rouge même dans stack_pub, commente ce bloc */
/*
QStackedWidget#stack_pub QPushButton#btnSupprimerPub {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 #EF4444, stop:1 #DC2626);
    border: 2px solid #991B1B;
}
QStackedWidget#stack_pub QPushButton#btnSupprimerPub:hover {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 #F87171, stop:1 #EF4444);
}
QStackedWidget#stack_pub QPushButton#btnSupprimerPub:pressed {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 #B91C1C, stop:1 #991B1B);
}
*/



)";

    qApp->setStyleSheet(qss);
}

void MainWindow::setActiveButton(QPushButton *btn)
{
    // Boutons de navigation (sans btnDeconnecter)
    QPushButton* buttons[] = {
        ui->btnEmployee,
        ui->btnInventaire,
        ui->btnPublication,
        ui->btnFinance,
        ui->btnLaboratoires,
        ui->btnProjets
    };

    for (auto *b : buttons) {
        b->setProperty("active", b == btn);
        b->style()->unpolish(b);
        b->style()->polish(b);
        b->update();
        b->setChecked(b == btn);
    }
}

/* ===================== NAVIGATION ===================== */

void MainWindow::goEmployee()
{
    ui->stackedWidget->setCurrentIndex(0);
    setActiveButton(ui->btnEmployee);
}

void MainWindow::goInventaire()
{
    ui->stackedWidget->setCurrentIndex(1);
    setActiveButton(ui->btnInventaire);
}

void MainWindow::goPublication()
{
    ui->stackedWidget->setCurrentIndex(2);
    setActiveButton(ui->btnPublication);
}

void MainWindow::goFinance()
{
    showFinanceList();

    ui->stackedWidget->setCurrentIndex(3);
    setActiveButton(ui->btnFinance);
}

void MainWindow::goLaboratoires()
{
    ui->stackedWidget->setCurrentIndex(4);
    setActiveButton(ui->btnLaboratoires);
}

void MainWindow::goProjets()
{
    ui->stackedWidget->setCurrentIndex(5);
    setActiveButton(ui->btnProjets);
}



/* ===================== LOGOUT ===================== */

void MainWindow::onDeconnecter()
{
    auto reply = QMessageBox::question(
        this,
        "Déconnexion",
        "Voulez-vous vraiment vous déconnecter ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}
void MainWindow::updateTopTitle(int index)
{
    switch(index)
    {
    case 0: ui->lblPageTitle->setText("Employee"); break;
    case 1: ui->lblPageTitle->setText("Inventaire"); break;
    case 2: ui->lblPageTitle->setText("Publication"); break;
    case 3: ui->lblPageTitle->setText("Finance"); break;
    case 4: ui->lblPageTitle->setText("Laboratoires"); break;
    case 5: ui->lblPageTitle->setText("Projets"); break;
    default: ui->lblPageTitle->setText(""); break;
    }
}


void MainWindow::on_btnAjouterPub_clicked()
{
    ui->stack_pub->setCurrentIndex(1);
}


void MainWindow::on_btnRetourAddPub_clicked()
{
    ui->stack_pub->setCurrentIndex(0);
}


void MainWindow::on_btnRetourEditPub_clicked()
{
    ui->stack_pub->setCurrentIndex(0);
}


void MainWindow::on_btnModifierPub_clicked()
{
    ui->stack_pub->setCurrentIndex(2);
}


void MainWindow::on_btnVoirStatistiquesPub_clicked()
{
    ui->stack_pub->setCurrentIndex(3);
}


void MainWindow::on_retour_stat_clicked()
{
    ui->stack_pub->setCurrentIndex(0);
}

void MainWindow::on_btnSupprimerPub_clicked()
{
    int row = ui->tablePublication->currentRow();

    // Vérifier si une ligne est sélectionnée


    // Confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous vraiment supprimer cette publication ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Supprimer la ligne du tableau (exemple)
        ui->tablePublication->removeRow(row);

        QMessageBox::information(this, "Suppression", "Publication supprimée avec succès.");
    }
}


void MainWindow::on_btnAjouterEmp_clicked()
{
    ui->stack_emp->setCurrentIndex(1);
}


void MainWindow::on_btnTrier_emp_3_clicked()
{
      ui->stack_emp->setCurrentIndex(2);
}


void MainWindow::on_btnConge_emp_3_clicked()
{
    ui->stack_emp->setCurrentIndex(3);

}


void MainWindow::on_btnConge_emp_clicked()
{
    ui->stack_emp->setCurrentIndex(4);

}


void MainWindow::on_btnConge_emp_2_clicked()
{
    ui->stack_emp->setCurrentIndex(5);

}


void MainWindow::on_btnChercher_emp_clicked()
{
    QMessageBox::information(this, "chercher", "chercheeee");
}


void MainWindow::on_btnExporter_emp_excel_3_clicked()
{
    // Vérifier si une ligne est sélectionnée


    // Confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous vraiment supprimer cette employee ?",
        QMessageBox::Yes | QMessageBox::No
        );

}


void MainWindow::on_btnTrier_emp_clicked()
{

}

//button LABS
void MainWindow::on_btnVoirStatistiquesPub_2_clicked()
{
    ui->stacked_L->setCurrentIndex(3);
}


void MainWindow::on_btnAjouterPub_2_clicked()
{
    ui->stacked_L->setCurrentIndex(2);
}


void MainWindow::on_btnModifierPub_2_clicked()
{
    ui->stacked_L->setCurrentIndex(1);
}


void MainWindow::on_btnAjouterPub_3_clicked()
{
    ui->stacked_L->setCurrentIndex(4);
}


void MainWindow::on_btnAjouterPub_4_clicked()
{
    ui->stacked_L->setCurrentIndex(5);
}


void MainWindow::on_BtnPopupCancelLabs_5_clicked()
{
    ui->stacked_L->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelLabs_3_clicked()
{
    ui->stacked_L->setCurrentIndex(0);
}


void MainWindow::on_retour_stat_2_clicked()
{
    ui->stacked_L->setCurrentIndex(0);
}


void MainWindow::on_retour_stat_3_clicked()
{
    ui->stacked_L->setCurrentIndex(0);
}


void MainWindow::on_retour_stat_8_clicked()
{
    ui->stacked_L->setCurrentIndex(0);
}
// buton Inventory

void MainWindow::on_BtnInventoryAdd_clicked()
{
    ui->stacked_I->setCurrentIndex(1);
}


void MainWindow::on_BtnInventoryAdd_2_clicked()
{
    ui->stacked_I->setCurrentIndex(4);
}


void MainWindow::on_BtnInventoryEdit_clicked()
{
    ui->stacked_I->setCurrentIndex(2);
}


void MainWindow::on_BtnInventoryAdd_5_clicked()
{
    ui->stacked_I->setCurrentIndex(3);
}


void MainWindow::on_retour_stat_7_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelInventory_2_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelInventory_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}


void MainWindow::on_retour_stat_6_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}


void MainWindow::on_retour_stat_4_clicked()
{
    ui->stacked_F->setCurrentIndex(0);
}


void MainWindow::on_retour_stat_5_clicked()
{
    ui->stacked_F->setCurrentIndex(0);
}

void MainWindow::on_BtnAdd_3_clicked()
{
    ui->stacked_F->setCurrentIndex(4);
}


void MainWindow::on_BtnAdd_4_clicked()
{
    ui->stacked_F->setCurrentIndex(3);
}


void MainWindow::on_BtnPopupCancelLabs_6_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}


void MainWindow::on_btnCancelEditEmp_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelLabs_10_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelLabs_9_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelLabs_7_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}


void MainWindow::on_BtnPopupCancelLabs_8_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}


void MainWindow::on_btnSaveEmployee_2_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}
void MainWindow::on_BtnPopupCancelInventory_2_triggered(QAction *arg1)
{
    Q_UNUSED(arg1);
    ui->stacked_I->setCurrentIndex(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ============================================================================
/****************************************************
 *                 FINANCE MODULE
 *  - UI init (combos)
 *  - Table setup/load
 *  - CRUD: Add / Edit / Delete
 *  - Filters: Apply / Reset / Export
 ****************************************************/
// ============================================================================

// ---------- FINANCE: init combos ----------

void MainWindow::initFinanceUi()
{
    // --- ComboBox (AJOUT) : valeurs DB via currentData() ---
    ui->FormType->clear();
    ui->FormType->addItem("Dépense", "Dépense");
    ui->FormType->addItem("Revenu",  "Revenu");

    ui->FormPayMode->clear();
    ui->FormPayMode->addItem("Espèces",        "especes");
    ui->FormPayMode->addItem("Chèque",         "cheque");
    ui->FormPayMode->addItem("Virement",       "virement");
    ui->FormPayMode->addItem("Carte bancaire", "carte_bancaire");
    ui->FormPayMode->addItem("Facture",        "facture");
    ui->FormPayMode->addItem("Remboursement",  "remboursement");

    // --- ComboBox (MODIF) : mêmes valeurs DB ---
    ui->FormType_2->clear();
    ui->FormType_2->addItem("Dépense", "Dépense");
    ui->FormType_2->addItem("Revenu",  "Revenu");

    ui->FormPayMode_2->clear();
    ui->FormPayMode_2->addItem("Espèces",        "especes");
    ui->FormPayMode_2->addItem("Chèque",         "cheque");
    ui->FormPayMode_2->addItem("Virement",       "virement");
    ui->FormPayMode_2->addItem("Carte bancaire", "carte_bancaire");
    ui->FormPayMode_2->addItem("Facture",        "facture");
    ui->FormPayMode_2->addItem("Remboursement",  "remboursement");

    // --- Table ---
    setupTableFinance();

    // --- Page Finance (liste) ---
    ui->stacked_F->setCurrentIndex(0);

    // --- 1er chargement ---
    loadFinance();
}

void MainWindow::setupTableFinance()
{
    ui->TableFinance->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableFinance->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableFinance->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableFinance->verticalHeader()->setVisible(false);
    ui->TableFinance->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 8 colonnes visibles (ID caché dans UserRole col 0)
    ui->TableFinance->setColumnCount(8);
    ui->TableFinance->setHorizontalHeaderLabels({
        "Code", "Type", "Montant", "Catégorie",
        "Description", "Date", "Mode", "Création"
    });
}

void MainWindow::loadFinance()
{
    ui->TableFinance->setRowCount(0);

    QSqlQuery q;
    q.prepare(
        "SELECT IDFINANCE, CODETRANSA, TYPETRANSACTION, MONTANT, CATEGORIE, "
        "       DESCRIPTION, TO_CHAR(DATETRANSACTION,'YYYY-MM-DD'), "
        "       MODEPAIEMENT, TO_CHAR(DATECREATION,'YYYY-MM-DD') "
        "FROM HICHEM.FINANCE "
        "ORDER BY DATETRANSACTION DESC"
        );

    if (!q.exec()) {
        QMessageBox::critical(this, "SQL Error", q.lastError().text());
        return;
    }

    int row = 0;
    while (q.next()) {
        ui->TableFinance->insertRow(row);

        const QString id   = q.value(0).toString(); // caché
        const QString code = q.value(1).toString();

        auto *itCode = new QTableWidgetItem(code);
        itCode->setData(Qt::UserRole, id); // ID caché
        ui->TableFinance->setItem(row, 0, itCode);

        ui->TableFinance->setItem(row, 1, new QTableWidgetItem(q.value(2).toString()));
        ui->TableFinance->setItem(row, 2, new QTableWidgetItem(q.value(3).toString()));
        ui->TableFinance->setItem(row, 3, new QTableWidgetItem(q.value(4).toString()));
        ui->TableFinance->setItem(row, 4, new QTableWidgetItem(q.value(5).toString()));
        ui->TableFinance->setItem(row, 5, new QTableWidgetItem(q.value(6).toString()));
        ui->TableFinance->setItem(row, 6, new QTableWidgetItem(q.value(7).toString()));
        ui->TableFinance->setItem(row, 7, new QTableWidgetItem(q.value(8).toString()));

        row++;
    }
}

void MainWindow::showFinanceList()
{
    ui->stackedWidget->setCurrentIndex(3);  // page Finance
    ui->stacked_F->setCurrentIndex(0);      // sous-page liste
    setActiveButton(ui->btnFinance);
    loadFinance();
}

// ---------------------------
// NAV FINANCE
// ---------------------------
void MainWindow::on_btnFinance_clicked()
{
    showFinanceList();
}

// ---------------------------
// ADD (ouvrir)
// ---------------------------
void MainWindow::on_BtnAdd_clicked()
{
    ui->stacked_F->setCurrentIndex(1); // ajouterF

    ui->FormCode->clear();
    ui->FormAmount->clear();
    ui->FormCategory->clear();
    ui->FormDesc->clear();

    ui->FormType->setCurrentIndex(0);
    ui->FormPayMode->setCurrentIndex(0);

    ui->FormDate->setDate(QDate::currentDate());
    ui->FormCreatedAt->setDate(QDate::currentDate());
}

void MainWindow::on_BtnPopupCancelFinance_clicked()
{
    ui->stacked_F->setCurrentIndex(0);
}

// ---------------------------
// ADD (save)
// ---------------------------
void MainWindow::on_BtnPopupSaveFinance_clicked()
{
    const QString code = ui->FormCode->text().trimmed();
    const QString type = ui->FormType->currentData().toString();       // DB value
    const QString mode = ui->FormPayMode->currentData().toString();    // DB value
    const double  montant = ui->FormAmount->text().toDouble();
    const QString cat  = ui->FormCategory->text().trimmed();
    const QString desc = ui->FormDesc->text().trimmed();
    const QDate   dt   = ui->FormDate->date();
    const QDate   dc   = ui->FormCreatedAt->date();

    if (code.isEmpty() || cat.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Code et Catégorie obligatoires.");
        return;
    }

    // IDFINANCE = MAX+1
    QSqlQuery qid;
    if (!qid.exec("SELECT NVL(MAX(IDFINANCE),0)+1 FROM HICHEM.FINANCE")) {
        QMessageBox::critical(this, "SQL Error", qid.lastError().text());
        return;
    }
    qid.next();
    const int newId = qid.value(0).toInt();

    // IMPORTANT: CINEMP doit exister dans EMPLOYE (FK)
    const QString cinemp = "1234"; // mets un CIN existant

    QSqlQuery q;
    q.prepare(
        "INSERT INTO HICHEM.FINANCE "
        "(IDFINANCE, CODETRANSA, TYPETRANSACTION, MONTANT, CATEGORIE, DESCRIPTION, "
        " DATETRANSACTION, MODEPAIEMENT, DATECREATION, CINEMP) "
        "VALUES (:id, :code, :type, :montant, :cat, :desc, :dt, :mode, :dc, :cin)"
        );

    q.bindValue(":id", newId);
    q.bindValue(":code", code);
    q.bindValue(":type", type);
    q.bindValue(":montant", montant);
    q.bindValue(":cat", cat);
    q.bindValue(":desc", desc);
    q.bindValue(":dt", dt);
    q.bindValue(":mode", mode);
    q.bindValue(":dc", dc);
    q.bindValue(":cin", cinemp);

    if (!q.exec()) {
        QMessageBox::critical(this, "SQL Error", q.lastError().text());
        return;
    }

    ui->stacked_F->setCurrentIndex(0);
    loadFinance();
}

// ---------------------------
// EDIT (ouvrir)
// ---------------------------
void MainWindow::on_BtnEdit_clicked()
{
    const int r = ui->TableFinance->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Modifier", "Sélectionne une transaction.");
        return;
    }

    idFinanceToEdit = ui->TableFinance->item(r, 0)->data(Qt::UserRole).toString();
    if (idFinanceToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "ID introuvable.");
        return;
    }

    ui->FormCode_2->setText(ui->TableFinance->item(r,0)->text());
    ui->FormType_2->setCurrentText(ui->TableFinance->item(r,1)->text());
    ui->FormAmount_2->setText(ui->TableFinance->item(r,2)->text());
    ui->FormCategory_2->setText(ui->TableFinance->item(r,3)->text());
    ui->FormDesc_2->setText(ui->TableFinance->item(r,4)->text());
    ui->FormDate_2->setDate(QDate::fromString(ui->TableFinance->item(r,5)->text(), "yyyy-MM-dd"));
    ui->FormPayMode_2->setCurrentText(ui->TableFinance->item(r,6)->text());
    ui->FormCreatedAt_2->setDate(QDate::fromString(ui->TableFinance->item(r,7)->text(), "yyyy-MM-dd"));

    ui->stacked_F->setCurrentIndex(2); // modifierF
}

void MainWindow::on_BtnPopupCancelFinance_2_clicked()
{
    idFinanceToEdit.clear();
    ui->stacked_F->setCurrentIndex(0);
}

// ---------------------------
// EDIT (save)
// ---------------------------
void MainWindow::on_BtnPopupSaveFinance_2_clicked()
{
    if (idFinanceToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "ID manquant. Re-sélectionne.");
        return;
    }

    QSqlQuery q;
    q.prepare(
        "UPDATE HICHEM.FINANCE SET "
        "CODETRANSA=:code, "
        "TYPETRANSACTION=:type, "
        "MONTANT=:montant, "
        "CATEGORIE=:cat, "
        "DESCRIPTION=:desc, "
        "DATETRANSACTION=:dt, "
        "MODEPAIEMENT=:mode, "
        "DATECREATION=:dc "
        "WHERE IDFINANCE=:id"
        );

    q.bindValue(":code", ui->FormCode_2->text().trimmed());
    q.bindValue(":type", ui->FormType_2->currentData().toString());       // DB value
    q.bindValue(":montant", ui->FormAmount_2->text().toDouble());
    q.bindValue(":cat", ui->FormCategory_2->text().trimmed());
    q.bindValue(":desc", ui->FormDesc_2->text().trimmed());
    q.bindValue(":dt", ui->FormDate_2->date());
    q.bindValue(":mode", ui->FormPayMode_2->currentData().toString());    // DB value
    q.bindValue(":dc", ui->FormCreatedAt_2->date());
    q.bindValue(":id", idFinanceToEdit);

    if (!q.exec()) {
        QMessageBox::critical(this, "SQL Error", q.lastError().text());
        return;
    }

    idFinanceToEdit.clear();
    ui->stacked_F->setCurrentIndex(0);
    loadFinance();
}

// ---------------------------
// DELETE
// ---------------------------
void MainWindow::on_BtnDelete_clicked()
{
    const int r = ui->TableFinance->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Supprimer", "Sélectionne une transaction.");
        return;
    }

    const QString id = ui->TableFinance->item(r,0)->data(Qt::UserRole).toString();

    auto rep = QMessageBox::question(this, "Suppression",
                                     "Confirmer la suppression ?",
                                     QMessageBox::Yes | QMessageBox::No);
    if (rep != QMessageBox::Yes) return;

    QSqlQuery q;
    q.prepare("DELETE FROM HICHEM.FINANCE WHERE IDFINANCE=:id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(this, "SQL Error", q.lastError().text());
        return;
    }

    loadFinance();
}
// ///////////////////////////////////////////////END FINANCE////////////////////////////////////////////////////////////////////////////////////// //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
