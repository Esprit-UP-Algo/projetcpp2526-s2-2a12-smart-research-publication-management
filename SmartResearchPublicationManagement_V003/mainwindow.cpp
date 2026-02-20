#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finance.h"

#include <QApplication>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QTableWidgetItem>
#include <QDate>
#include <QDebug>
#include <QHeaderView>
#include <QRegularExpression>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QLocale>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QTime>

static void setupTable(QTableWidget* t)
{
    if (!t) return;

    t->setShowGrid(true);
    t->setGridStyle(Qt::SolidLine);
    t->setAlternatingRowColors(false);

    auto h = t->horizontalHeader();
    h->setSectionResizeMode(QHeaderView::Stretch);
    h->setStretchLastSection(false);
    h->setDefaultAlignment(Qt::AlignCenter);

    t->verticalHeader()->setVisible(false);
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setSelectionMode(QAbstractItemView::SingleSelection);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setWordWrap(false);
    t->setSortingEnabled(true);
}
static double parseAmount(const QString& raw, bool *okOut=nullptr)
{
    bool ok = false;
    double v = QLocale::c().toDouble(raw, &ok);
    if (!ok) v = raw.toDouble(&ok);
    if (okOut) *okOut = ok;
    return v;
}

static QString fmtDT(double v)
{
    const QLocale fr(QLocale::French, QLocale::Tunisia);
    return fr.toString(v, 'f', 3) + " DT";
}

static QString makeInvoiceNumber()
{
    // FAC-INT-20260220-153045
    return "FAC-INT-" + QDate::currentDate().toString("yyyyMMdd")
           + "-" + QTime::currentTime().toString("hhmmss");
}

static void drawRect(QPainter& p, const QRect& r) { p.drawRect(r); }
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ===== INIT FINANCE =====
    initFinanceUi();
    // ===== INIT publication =====
    initPublicationUi();

    setupTable(ui->tablePublication);
    setupTable(ui->TableEmp);
    setupTable(ui->TableCongeEmp);
    setupTable(ui->TableFormations_Emp);
    setupTable(ui->TableInventory);
    setupTable(ui->TableFinance);
    setupTable(ui->TableLabs_2);
    setupTable(ui->tableProjets);

    // ===== Table Publication : lignes séparatrices + alignement =====
    ui->tablePublication->setShowGrid(true);
    ui->tablePublication->setGridStyle(Qt::SolidLine);
    ui->tablePublication->setAlternatingRowColors(false);

    auto header = ui->tablePublication->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setStretchLastSection(false);
    header->setDefaultAlignment(Qt::AlignCenter);

    ui->tablePublication->verticalHeader()->setVisible(false);
    ui->tablePublication->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePublication->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablePublication->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePublication->setWordWrap(false);
    ui->tablePublication->setSortingEnabled(true);

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

    ui->btnEmployee->setFocusPolicy(Qt::NoFocus);
    ui->btnInventaire->setFocusPolicy(Qt::NoFocus);
    ui->btnPublication->setFocusPolicy(Qt::NoFocus);
    ui->btnFinance->setFocusPolicy(Qt::NoFocus);
    ui->btnLaboratoires->setFocusPolicy(Qt::NoFocus);
    ui->btnProjets->setFocusPolicy(Qt::NoFocus);
    ui->btnDeconnecter->setFocusPolicy(Qt::NoFocus);

    applyModernStyle();

    connect(ui->btnEmployee,     &QPushButton::clicked, this, &MainWindow::goEmployee);
    connect(ui->btnInventaire,   &QPushButton::clicked, this, &MainWindow::goInventaire);
    connect(ui->btnPublication,  &QPushButton::clicked, this, &MainWindow::goPublication);
    connect(ui->btnFinance,      &QPushButton::clicked, this, &MainWindow::goFinance);
    connect(ui->btnLaboratoires, &QPushButton::clicked, this, &MainWindow::goLaboratoires);
    connect(ui->btnProjets,      &QPushButton::clicked, this, &MainWindow::goProjets);

    connect(ui->btnDeconnecter,  &QPushButton::clicked, this, &MainWindow::onDeconnecter);

    ui->stackedWidget->setCurrentIndex(0);
    setActiveButton(ui->btnEmployee);

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
    const QString qss = R"(

/* =========================================================
   GLOBAL / BASE
   ========================================================= */
QMainWindow {
    background-color: #F3F7FF;
}

QWidget {
    font-family: "Segoe UI", "Inter", "Arial";
    font-size: 13px;
    color: #0F172A;
}

QToolTip {
    background: #0F172A;
    color: white;
    border: 1px solid #111111;
    padding: 6px 10px;
    border-radius: 8px;
}

QWidget#centralwidget {
    background-color: #F4F6F8;
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

QFrame#sidebarFrame {
    border-radius: 18px;
    background-color: #F8FBFC;
    background-image: url(":/img/images/sidebar_bg.png");
    background-repeat: no-repeat;
    background-position: left bottom;
    background-size: 260px 600px;
}

QLabel#titleLabel {
    font-size: 18px;
    font-weight: 800;
    color: #0B1220;
    padding: 12px 10px;
    margin: 6px 6px 0px 6px;
    border-radius: 12px;
}

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

QPushButton:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #3CCAD3,
        stop:1 #28A3AB
    );
}

QPushButton:pressed {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #1C8A91,
        stop:1 #166F75
    );
}

QPushButton:checked {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #1F8E95,
        stop:1 #166F75
    );
    border: 2px solid rgba(0, 0, 0, 0.65);
    color: white;
}

QPushButton:checked:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #238F96,
        stop:1 #18797E
    );
}

QPushButton#btnDeconnecter {
    color: #B91C1C;
    background-color: #FFFFFF;
    border: 2px solid #111111;
}

QPushButton#btnDeconnecter:hover { background-color: #FFECEC; }
QPushButton#btnDeconnecter:pressed { background-color: #FFD6D6; }

QStackedWidget#stackedWidget {
    border-radius: 16px;
    border: 2px solid #111111;
    background-image: url(":/img/images/background.png");
    background-repeat: no-repeat;
    background-position: center;
    background-size: cover;
}

QStackedWidget QWidget { background-color: transparent; }

QLabel {
    color: #0F172A;
    font-size: 14px;
    font-weight: 800;
    letter-spacing: 0.6px;
}

QLabel#labelEmployee,
QLabel#labelInventaire,
QLabel#labelPublication,
QLabel#labelFinance,
QLabel#labelLaboratoires,
QLabel#labelProjets {
    font-size: 22px;
    font-weight: 900;
}

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

QMessageBox { background: #FFFFFF; }
QMessageBox QLabel { color: #0F172A; font-size: 14px; font-weight: 700; }
QMessageBox QPushButton { min-width: 90px; text-align: center; }

/* ---- MODULES TABLES ---- */
QStackedWidget#stack_pub QTableWidget,
QStackedWidget#stack_emp QTableWidget,
QStackedWidget#stacked_I QTableWidget,
QStackedWidget#stacked_F QTableWidget,
QStackedWidget#stack_proj QTableWidget,
QStackedWidget#stacked_L QTableWidget {
    background: #FFFFFF;
    border: 2px solid #18A06A;
    border-radius: 12px;
    gridline-color: #18A06A;
    selection-background-color: rgba(24,160,106,35);
    selection-color: #0B2E1F;
}

QStackedWidget#stack_pub QHeaderView::section,
QStackedWidget#stack_emp QHeaderView::section,
QStackedWidget#stacked_I QHeaderView::section,
QStackedWidget#stacked_F QHeaderView::section,
QStackedWidget#stack_proj QHeaderView::section,
QStackedWidget#stacked_L QHeaderView::section {
    background: #FFFFFF;
    color: #0B2E1F;
    border: 1px solid #18A06A;
    padding: 8px 10px;
    font-weight: 800;
}

QStackedWidget#stack_pub QTableCornerButton::section,
QStackedWidget#stack_emp QTableCornerButton::section,
QStackedWidget#stacked_I QTableCornerButton::section,
QStackedWidget#stacked_F QTableCornerButton::section,
QStackedWidget#stack_proj QTableCornerButton::section,
QStackedWidget#stacked_L QTableCornerButton::section {
    background: #FFFFFF;
    border: 1px solid #18A06A;
}

/* ---- INPUTS MODULES ---- */
QStackedWidget#stack_pub QLineEdit,
QStackedWidget#stack_emp QLineEdit,
QStackedWidget#stacked_I QLineEdit,
QStackedWidget#stacked_F QLineEdit,
QStackedWidget#stacked_L QLineEdit,
QStackedWidget#stack_proj QLineEdit,

QStackedWidget#stack_pub QComboBox,
QStackedWidget#stack_emp QComboBox,
QStackedWidget#stacked_I QComboBox,
QStackedWidget#stacked_F QComboBox,
QStackedWidget#stacked_L QComboBox,
QStackedWidget#stack_proj QComboBox,

QStackedWidget#stack_pub QDateEdit,
QStackedWidget#stack_emp QDateEdit,
QStackedWidget#stacked_I QDateEdit,
QStackedWidget#stack_proj QDateEdit,
QStackedWidget#stacked_F QDateEdit,
QStackedWidget#stacked_L QDateEdit {
    background: #FFFFFF;
    border: 2px solid #18A06A;
    border-radius: 10px;
    padding: 6px 10px;
    color: #0B2E1F;
}

QStackedWidget#stack_pub QLineEdit:focus,
QStackedWidget#stack_emp QLineEdit:focus,
QStackedWidget#stacked_I QLineEdit:focus,
QStackedWidget#stacked_F QLineEdit:focus,
QStackedWidget#stacked_L QLineEdit:focus,
QStackedWidget#stack_proj QLineEdit:focus,

QStackedWidget#stack_pub QComboBox:focus,
QStackedWidget#stack_emp QComboBox:focus,
QStackedWidget#stacked_I QComboBox:focus,
QStackedWidget#stacked_F QComboBox:focus,
QStackedWidget#stacked_L QComboBox:focus,
QStackedWidget#stack_proj QComboBox:focus,

QStackedWidget#stack_pub QDateEdit:focus,
QStackedWidget#stack_emp QDateEdit:focus,
QStackedWidget#stacked_I QDateEdit:focus,
QStackedWidget#stack_proj QDateEdit:focus,
QStackedWidget#stacked_F QDateEdit:focus,
QStackedWidget#stacked_L QDateEdit:focus {
    border: 2px solid #0F7F55;
}

QStackedWidget#stack_pub QPushButton,
QStackedWidget#stack_emp QPushButton,
QStackedWidget#stacked_I QPushButton,
QStackedWidget#stack_proj QPushButton,
QStackedWidget#stacked_F QPushButton,
QStackedWidget#stacked_L QPushButton {
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

QStackedWidget#stack_pub QPushButton:hover,
QStackedWidget#stack_emp QPushButton:hover,
QStackedWidget#stacked_I QPushButton:hover,
QStackedWidget#stack_proj QPushButton:hover,
QStackedWidget#stacked_F QPushButton:hover,
QStackedWidget#stacked_L QPushButton:hover {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #1BBE7B,
        stop:1 #35D596
    );
}

QStackedWidget#stack_pub QPushButton:pressed,
QStackedWidget#stack_emp QPushButton:pressed,
QStackedWidget#stacked_I QPushButton:pressed,
QStackedWidget#stacked_F QPushButton:pressed,
QStackedWidget#stacked_L QPushButton:pressed {
    background: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #0F7F55,
        stop:1 #0B6A47
    );
}

)";

    qApp->setStyleSheet(qss);
}

void MainWindow::setActiveButton(QPushButton *btn)
{
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

/* ===================== (TES AUTRES SLOTS - INCHANGÉS) ===================== */

void MainWindow::on_btnAjouterPub_clicked() { ui->stack_pub->setCurrentIndex(1); }
void MainWindow::on_btnRetourAddPub_clicked() { ui->stack_pub->setCurrentIndex(0); }
void MainWindow::on_btnRetourEditPub_clicked() { ui->stack_pub->setCurrentIndex(0); }
void MainWindow::on_btnVoirStatistiquesPub_clicked() { ui->stack_pub->setCurrentIndex(3); }
void MainWindow::on_retour_stat_clicked() { ui->stack_pub->setCurrentIndex(0); }
void MainWindow::on_btnAjouterEmp_clicked() { ui->stack_emp->setCurrentIndex(1); }
void MainWindow::on_btnTrier_emp_3_clicked() { ui->stack_emp->setCurrentIndex(2); }

void MainWindow::on_BtnPopupCancelInventory_2_triggered(QAction *action)
{
    Q_UNUSED(action);
}

void MainWindow::on_btnConge_emp_3_clicked() { ui->stack_emp->setCurrentIndex(3); }
void MainWindow::on_btnConge_emp_clicked() { ui->stack_emp->setCurrentIndex(4); }
void MainWindow::on_btnConge_emp_2_clicked() { ui->stack_emp->setCurrentIndex(5); }

void MainWindow::on_btnChercher_emp_clicked()
{
    QMessageBox::information(this, "chercher", "chercheeee");
}

void MainWindow::on_btnExporter_emp_excel_3_clicked()
{
    auto reply = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous vraiment supprimer cette employee ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        qDebug() << "YES cliqué";
    }
}

void MainWindow::on_btnTrier_emp_clicked() {}

// LABS
void MainWindow::on_btnVoirStatistiquesPub_2_clicked() { ui->stacked_L->setCurrentIndex(3); }
void MainWindow::on_btnAjouterPub_2_clicked() { ui->stacked_L->setCurrentIndex(2); }
void MainWindow::on_btnModifierPub_2_clicked() { ui->stacked_L->setCurrentIndex(1); }
void MainWindow::on_btnAjouterPub_3_clicked() { ui->stacked_L->setCurrentIndex(4); }
void MainWindow::on_btnAjouterPub_4_clicked() { ui->stacked_L->setCurrentIndex(5); }
void MainWindow::on_BtnPopupCancelLabs_5_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_3_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_2_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_3_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_8_clicked() { ui->stacked_L->setCurrentIndex(0); }

// Inventory
void MainWindow::on_BtnInventoryAdd_clicked() { ui->stacked_I->setCurrentIndex(1); }
void MainWindow::on_BtnInventoryAdd_2_clicked() { ui->stacked_I->setCurrentIndex(4); }
void MainWindow::on_BtnInventoryEdit_clicked() { ui->stacked_I->setCurrentIndex(2); }
void MainWindow::on_BtnInventoryAdd_5_clicked() { ui->stacked_I->setCurrentIndex(3); }
void MainWindow::on_retour_stat_7_clicked() { ui->stacked_I->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelInventory_2_clicked() { ui->stacked_I->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelInventory_clicked() { ui->stacked_I->setCurrentIndex(0); }
void MainWindow::on_retour_stat_6_clicked() { ui->stacked_I->setCurrentIndex(0); }

// Finance “retour” existants
void MainWindow::on_retour_stat_4_clicked() { ui->stacked_F->setCurrentIndex(0); }
void MainWindow::on_retour_stat_5_clicked() { ui->stacked_F->setCurrentIndex(0); }

// Emp cancels
void MainWindow::on_BtnPopupCancelLabs_6_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_btnCancelEditEmp_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_10_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_9_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_7_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_8_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_btnSaveEmployee_2_clicked() { ui->stack_emp->setCurrentIndex(0); }

// Projets
void MainWindow::on_retour_statn_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnRetourEditProj_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnRetourAddProj_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnAjouterProj_clicked() { ui->stack_proj->setCurrentIndex(1); }
void MainWindow::on_btnModifierProj_clicked() { ui->stack_proj->setCurrentIndex(2); }
void MainWindow::on_btnVoirStatistiquesProj_clicked() { ui->stack_proj->setCurrentIndex(3); }
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
// ======================================= FINANCE_HICHEM_CRUD ======================================= /
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINANCE :
// - Ajout selectedFinanceId() (utilisé partout pour récupérer l’ID caché)
// - on_BtnEdit_clicked() corrigé (combo data/text + dates safe + bug ligne collée)
// - on_BtnPopupSaveFinance_clicked() : validations + conversion montant safe
// - on_BtnPopupSaveFinance_2_clicked() : idem
// - on_BtnDelete_clicked() : utilise selectedFinanceId()
// - setupTableFinance() : garde ta table 8 colonnes (ID caché Qt::UserRole)
// - helper propre (ID caché dans Qt::UserRole colonne 0)
QString MainWindow::selectedFinanceId() const
{
    const int r = ui->TableFinance->currentRow();
    if (r < 0) return {};

    QTableWidgetItem *it = ui->TableFinance->item(r, 0);
    if (!it) return {};

    return it->data(Qt::UserRole).toString();
}
Finance::Row MainWindow::selectedFinanceRowFromTable(bool *ok) const
{
    if (ok) *ok = false;

    const int r = ui->TableFinance->currentRow();
    if (r < 0) return {};

    auto item = [&](int c)->QTableWidgetItem* { return ui->TableFinance->item(r, c); };
    if (!item(0)) return {};

    Finance::Row row;
    row.id = item(0)->data(Qt::UserRole).toString(); // caché (IDFINANCE)
    row.code = item(0)->text();
    row.type = item(1) ? item(1)->text() : "";
    row.montant = item(2) ? item(2)->text() : "";
    row.categorie = item(3) ? item(3)->text() : "";
    row.description = item(4) ? item(4)->text() : "";
    row.dateTransaction = item(5) ? item(5)->text() : "";
    row.modePaiement = item(6) ? item(6)->text() : "";
    row.dateCreation = item(7) ? item(7)->text() : "";

    if (ok) *ok = true;
    return row;
}
//===================publication crud===============================================
void MainWindow::initPublicationUi()
{
    // Combo Type Brevet (Add)
    ui->comboTypeBrevetAdd->clear();
    ui->comboTypeBrevetAdd->addItem("Brevet", "Brevet");
    ui->comboTypeBrevetAdd->addItem("Article", "Article");
    ui->comboTypeBrevetAdd->addItem("Autre", "Autre");

    // Combo Type Brevet (Edit)
    ui->comboTypeBrevetEdit->clear();
    ui->comboTypeBrevetEdit->addItem("Brevet", "Brevet");
    ui->comboTypeBrevetEdit->addItem("Article", "Article");
    ui->comboTypeBrevetEdit->addItem("Autre", "Autre");

    // Statut (contrainte SQL)
    ui->comboStatusBrevetAdd->clear();
    ui->comboStatusBrevetAdd->addItem("En cours", "En cours");
    ui->comboStatusBrevetAdd->addItem("Déposé", "Déposé");
    ui->comboStatusBrevetAdd->addItem("Accepté", "Accepté");
    ui->comboStatusBrevetAdd->addItem("Refusé", "Refusé");
    ui->comboStatusBrevetAdd->addItem("Publié", "Publié");

    ui->comboStatusBrevetEdit->clear();
    ui->comboStatusBrevetEdit->addItem("En cours", "En cours");
    ui->comboStatusBrevetEdit->addItem("Déposé", "Déposé");
    ui->comboStatusBrevetEdit->addItem("Accepté", "Accepté");
    ui->comboStatusBrevetEdit->addItem("Refusé", "Refusé");
    ui->comboStatusBrevetEdit->addItem("Publié", "Publié");

    setupTablePublication();
    ui->stack_pub->setCurrentIndex(0);
    loadPublications();
}

void MainWindow::setupTablePublication()
{
    ui->tablePublication->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePublication->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePublication->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablePublication->verticalHeader()->setVisible(false);
    ui->tablePublication->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 8 colonnes visibles, ID caché dans UserRole col 0
    ui->tablePublication->setColumnCount(8);
    ui->tablePublication->setHorizontalHeaderLabels({
        "Titre", "Résumé", "Inventeurs", "Domaine",
        "Type", "Numéro", "Date dépôt", "Statut"
    });
}

void MainWindow::loadPublications()
{
    ui->tablePublication->setRowCount(0);

    QVector<Publication::Row> rows;
    QString err;
    if (!Publication::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    int row = 0;
    for (const auto& r : rows) {
        ui->tablePublication->insertRow(row);

        auto *itTitre = new QTableWidgetItem(r.titre);
        itTitre->setData(Qt::UserRole, r.id); // ID caché
        ui->tablePublication->setItem(row, 0, itTitre);

        ui->tablePublication->setItem(row, 1, new QTableWidgetItem(r.resume));
        ui->tablePublication->setItem(row, 2, new QTableWidgetItem(r.inventeurs));
        ui->tablePublication->setItem(row, 3, new QTableWidgetItem(r.domaineFabrication));
        ui->tablePublication->setItem(row, 4, new QTableWidgetItem(r.typeBrevet));
        ui->tablePublication->setItem(row, 5, new QTableWidgetItem(r.numeroBrevet));
        ui->tablePublication->setItem(row, 6, new QTableWidgetItem(r.dateDepot));
        ui->tablePublication->setItem(row, 7, new QTableWidgetItem(r.statutBrevet));

        row++;
    }
}

QString MainWindow::selectedPublicationId() const
{
    int row = ui->tablePublication->currentRow();
    if (row < 0) return {};

    QTableWidgetItem *it = ui->tablePublication->item(row, 0);
    if (!it) return {};
    return it->data(Qt::UserRole).toString();
}
//===========
void MainWindow::on_btnAddPub_clicked()
{
    const QString titre = ui->lineTitreAdd->text().trimmed();
    const QString resume = ui->lineResumeAdd->text().trimmed();
    const QString inventeurs = ui->lineInventeursAdd->text().trimmed();
    const QString domaine = ui->lineDomaineAdd->text().trimmed();
    const QString typeBrevet = ui->comboTypeBrevetAdd->currentData().toString();
    const QString statut = ui->comboStatusBrevetAdd->currentData().toString();
    const QDate dateDepot = ui->dateDepotAdd->date();

    // ====== CONTROLE DE SAISIE ======
    if (titre.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Le titre est obligatoire.");
        ui->lineTitreAdd->setFocus();
        return;
    }
    if (inventeurs.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Le champ inventeurs est obligatoire.");
        ui->lineInventeursAdd->setFocus();
        return;
    }
    if (domaine.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Le domaine de fabrication est obligatoire.");
        ui->lineDomaineAdd->setFocus();
        return;
    }
    if (!dateDepot.isValid()) {
        QMessageBox::warning(this, "Ajout", "Date dépôt invalide.");
        return;
    }

    bool okNum = false;
    int numero = ui->lineNumeroBrevetAdd->text().trimmed().toInt(&okNum);
    if (!okNum || numero <= 0) {
        QMessageBox::warning(this, "Ajout", "Numéro brevet invalide (entier > 0).");
        ui->lineNumeroBrevetAdd->setFocus();
        return;
    }

    // ====== INSERT DB ======
    Publication p(titre, resume, inventeurs, domaine, typeBrevet, numero, dateDepot, statut);
    QString err;
    if (!p.ajouter(&err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    QMessageBox::information(this, "Ajout", "Publication ajoutée avec succès.");
    ui->stack_pub->setCurrentIndex(0);
    loadPublications();
}
//===========
void MainWindow::on_btnModifierPub_clicked()
{
    const QString id = selectedPublicationId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Sélectionne une publication d'abord.");
        return;
    }
    idPublicationToEdit = id;

    int row = ui->tablePublication->currentRow();
    ui->lineTitreEdit->setText(ui->tablePublication->item(row, 0)->text());
    ui->lineResumeEdit->setText(ui->tablePublication->item(row, 1)->text());
    ui->lineInventeursEdit->setText(ui->tablePublication->item(row, 2)->text());
    ui->lineDomaineEdit->setText(ui->tablePublication->item(row, 3)->text());

    const QString type = ui->tablePublication->item(row, 4)->text();
    int idxType = ui->comboTypeBrevetEdit->findData(type);
    ui->comboTypeBrevetEdit->setCurrentIndex(idxType >= 0 ? idxType : 0);

    ui->lineNumeroBrevetEdit->setText(ui->tablePublication->item(row, 5)->text());

    const QString dateStr = ui->tablePublication->item(row, 6)->text();
    ui->dateDepotEdit->setDate(QDate::fromString(dateStr, "yyyy-MM-dd"));

    const QString statut = ui->tablePublication->item(row, 7)->text();
    int idxStatut = ui->comboStatusBrevetEdit->findData(statut);
    ui->comboStatusBrevetEdit->setCurrentIndex(idxStatut >= 0 ? idxStatut : 0);

    ui->stack_pub->setCurrentIndex(2);
}
//================
void MainWindow::on_btnConfirmEditPub_clicked()
{
    if (idPublicationToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modification", "ID publication manquant.");
        return;
    }

    const QString titre = ui->lineTitreEdit->text().trimmed();
    const QString resume = ui->lineResumeEdit->text().trimmed();
    const QString inventeurs = ui->lineInventeursEdit->text().trimmed();
    const QString domaine = ui->lineDomaineEdit->text().trimmed();
    const QString typeBrevet = ui->comboTypeBrevetEdit->currentData().toString();
    const QString statut = ui->comboStatusBrevetEdit->currentData().toString();
    const QDate dateDepot = ui->dateDepotEdit->date();

    // ====== CONTROLE DE SAISIE ======
    if (titre.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Le titre est obligatoire.");
        ui->lineTitreEdit->setFocus();
        return;
    }

    bool okNum = false;
    int numero = ui->lineNumeroBrevetEdit->text().trimmed().toInt(&okNum);
    if (!okNum || numero <= 0) {
        QMessageBox::warning(this, "Modification", "Numéro brevet invalide (entier > 0).");
        ui->lineNumeroBrevetEdit->setFocus();
        return;
    }

    // ====== UPDATE DB ======
    QString err;
    if (!Publication::modifier(idPublicationToEdit, titre, resume, inventeurs, domaine,
                               typeBrevet, numero, dateDepot, statut, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    QMessageBox::information(this, "Modification", "Publication modifiée avec succès.");
    idPublicationToEdit.clear();
    ui->stack_pub->setCurrentIndex(0);
    loadPublications();
}
//=============
void MainWindow::on_btnSupprimerPub_clicked()
{
    const QString id = selectedPublicationId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une publication d'abord.");
        return;
    }

    auto reply = QMessageBox::question(
        this, "Confirmation",
        "Voulez-vous vraiment supprimer cette publication ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes) return;

    QString err;
    if (!Publication::supprimer(id, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    QMessageBox::information(this, "Suppression", "Publication supprimée avec succès.");
    loadPublications();
}



//=======================================================================================

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

    setupTableFinance();

    ui->stacked_F->setCurrentIndex(0);
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

    QVector<Finance::Row> rows;
    QString err;
    if (!Finance::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    int row = 0;
    for (const auto& r : rows) {
        ui->TableFinance->insertRow(row);

        auto *itCode = new QTableWidgetItem(r.code);
        itCode->setData(Qt::UserRole, r.id); // ID caché
        ui->TableFinance->setItem(row, 0, itCode);

        ui->TableFinance->setItem(row, 1, new QTableWidgetItem(r.type));
        ui->TableFinance->setItem(row, 2, new QTableWidgetItem(r.montant));
        ui->TableFinance->setItem(row, 3, new QTableWidgetItem(r.categorie));
        ui->TableFinance->setItem(row, 4, new QTableWidgetItem(r.description));
        ui->TableFinance->setItem(row, 5, new QTableWidgetItem(r.dateTransaction));
        ui->TableFinance->setItem(row, 6, new QTableWidgetItem(r.modePaiement));
        ui->TableFinance->setItem(row, 7, new QTableWidgetItem(r.dateCreation));

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

void MainWindow::on_btnFinance_clicked()
{
    showFinanceList();
}

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

void MainWindow::on_BtnPopupSaveFinance_clicked()
{
    const QString code = ui->FormCode->text().trimmed();
    const QString type = ui->FormType->currentData().toString();
    const QString mode = ui->FormPayMode->currentData().toString();
    const QString cat  = ui->FormCategory->text().trimmed();
    const QString desc = ui->FormDesc->text().trimmed();
    const QDate   dt   = ui->FormDate->date();
    const QDate   dc   = ui->FormCreatedAt->date();

    // --- Validation CODE ---
    if (code.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Le code transaction est obligatoire.");
        ui->FormCode->setFocus();
        return;
    }
    // Exemple de format conseillé: TRX001 / FIN-2026-01 ...
    // (tu peux adapter selon ton cahier des charges)
    static const QRegularExpression reCode(R"(^[A-Za-z0-9_-]{3,20}$)");
    if (!reCode.match(code).hasMatch()) {
        QMessageBox::warning(this, "Ajout",
                             "Code invalide.\nUtilise 3 à 20 caractères (lettres/chiffres/_/-).");
        ui->FormCode->setFocus();
        return;
    }

    // --- Validation Catégorie ---
    if (cat.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "La catégorie est obligatoire.");
        ui->FormCategory->setFocus();
        return;
    }

    // --- Validation Montant ---
    bool okAmount = false;
    const double montant = ui->FormAmount->text().trimmed().toDouble(&okAmount);
    if (!okAmount) {
        QMessageBox::warning(this, "Ajout", "Montant invalide (nombre attendu).");
        ui->FormAmount->setFocus();
        return;
    }
    if (montant <= 0.0) {
        QMessageBox::warning(this, "Ajout", "Le montant doit être strictement positif.");
        ui->FormAmount->setFocus();
        return;
    }

    // --- Validation Dates ---
    if (!dt.isValid() || !dc.isValid()) {
        QMessageBox::warning(this, "Ajout", "Date invalide.");
        return;
    }
    if (dc < dt) {
        QMessageBox::warning(this, "Ajout",
                             "La date de création ne doit pas être avant la date de transaction.");
        return;
    }

    // --- IDEMP placeholder (à remplacer quand Employe intégré) ---
    // IMPORTANT: si la BD impose une FK, il faut que cette valeur existe sinon insertion échoue.
    const QString IDEMP = "1234"; // placeholder "technique"
    // 👉 dès que Employee est prêt: IDEMP = employe connecté ou combo CIN

    Finance f(code, type, montant, cat, desc, dt, mode, dc, IDEMP);

    QString err;
    if (!f.ajouter(&err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    ui->stacked_F->setCurrentIndex(0);
    loadFinance();
}


void MainWindow::on_BtnEdit_clicked()
{
    const int r = ui->TableFinance->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Modifier", "Sélectionne une transaction.");
        return;
    }

    idFinanceToEdit = selectedFinanceId();
    if (idFinanceToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "ID introuvable.");
        return;
    }

    ui->FormCode_2->setText(ui->TableFinance->item(r,0)->text());

    // TYPE : data == "Dépense"/"Revenu"
    const QString typeDb = ui->TableFinance->item(r,1)->text();
    int idxType = ui->FormType_2->findData(typeDb);
    if (idxType < 0) idxType = ui->FormType_2->findText(typeDb);
    ui->FormType_2->setCurrentIndex(qMax(0, idxType));

    ui->FormAmount_2->setText(ui->TableFinance->item(r,2)->text());
    ui->FormCategory_2->setText(ui->TableFinance->item(r,3)->text());
    ui->FormDesc_2->setText(ui->TableFinance->item(r,4)->text());

    // Date transaction safe
    QDate dt = QDate::fromString(ui->TableFinance->item(r,5)->text(), "yyyy-MM-dd");
    ui->FormDate_2->setDate(dt.isValid() ? dt : QDate::currentDate());

    // MODE : data == "especes/cheque/..."
    const QString modeDb = ui->TableFinance->item(r,6)->text();
    int idxMode = ui->FormPayMode_2->findData(modeDb);
    if (idxMode < 0) idxMode = ui->FormPayMode_2->findText(modeDb);
    ui->FormPayMode_2->setCurrentIndex(qMax(0, idxMode));

    // Date création safe
    QDate dc = QDate::fromString(ui->TableFinance->item(r,7)->text(), "yyyy-MM-dd");
    ui->FormCreatedAt_2->setDate(dc.isValid() ? dc : QDate::currentDate());

    ui->stacked_F->setCurrentIndex(2); // modifierF
}

void MainWindow::on_BtnPopupCancelFinance_2_clicked()
{
    idFinanceToEdit.clear();
    ui->stacked_F->setCurrentIndex(0);
}

void MainWindow::on_BtnPopupSaveFinance_2_clicked()
{
    if (idFinanceToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "ID manquant. Re-sélectionne la transaction.");
        return;
    }

    const QString code = ui->FormCode_2->text().trimmed();
    const QString type = ui->FormType_2->currentData().toString();
    const QString mode = ui->FormPayMode_2->currentData().toString();
    const QString cat  = ui->FormCategory_2->text().trimmed();
    const QString desc = ui->FormDesc_2->text().trimmed();
    const QDate   dt   = ui->FormDate_2->date();
    const QDate   dc   = ui->FormCreatedAt_2->date();

    if (code.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "Le code transaction est obligatoire.");
        ui->FormCode_2->setFocus();
        return;
    }
    static const QRegularExpression reCode(R"(^[A-Za-z0-9_-]{3,20}$)");
    if (!reCode.match(code).hasMatch()) {
        QMessageBox::warning(this, "Modifier",
                             "Code invalide.\nUtilise 3 à 20 caractères (lettres/chiffres/_/-).");
        ui->FormCode_2->setFocus();
        return;
    }

    if (cat.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "La catégorie est obligatoire.");
        ui->FormCategory_2->setFocus();
        return;
    }

    bool okAmount = false;
    const double montant = ui->FormAmount_2->text().trimmed().toDouble(&okAmount);
    if (!okAmount) {
        QMessageBox::warning(this, "Modifier", "Montant invalide (nombre attendu).");
        ui->FormAmount_2->setFocus();
        return;
    }
    if (montant <= 0.0) {
        QMessageBox::warning(this, "Modifier", "Le montant doit être strictement positif.");
        ui->FormAmount_2->setFocus();
        return;
    }

    if (!dt.isValid() || !dc.isValid()) {
        QMessageBox::warning(this, "Modifier", "Date invalide.");
        return;
    }
    if (dc < dt) {
        QMessageBox::warning(this, "Modifier",
                             "La date de création ne doit pas être avant la date de transaction.");
        return;
    }

    QString err;
    const bool ok = Finance::modifier(
        idFinanceToEdit,
        code,
        type,
        montant,
        cat,
        desc,
        dt,
        mode,
        dc,
        &err
        );

    if (!ok) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    idFinanceToEdit.clear();
    ui->stacked_F->setCurrentIndex(0);
    loadFinance();
}


void MainWindow::on_BtnDelete_clicked()
{
    const QString id = selectedFinanceId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Supprimer", "Sélectionne une transaction.");
        return;
    }

    auto rep = QMessageBox::question(this, "Suppression",
                                     "Confirmer la suppression ?",
                                     QMessageBox::Yes | QMessageBox::No);
    if (rep != QMessageBox::Yes) return;

    QString err;
    if (!Finance::supprimer(id, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    loadFinance();
}
bool MainWindow::exportInternalInvoicePdf_19(const QString& filePath, const Finance::Row& row)
{
    bool okAmt = false;
    const double totalHT = parseAmount(row.montant, &okAmt);
    if (!okAmt || totalHT <= 0.0) {
        QMessageBox::warning(this, "Export", "Montant invalide pour la transaction sélectionnée.");
        return false;
    }

    const double tvaRate = 0.19;
    const double tva = totalHT * tvaRate;
    const double totalTTC = totalHT + tva;

    // Société
    const QString companyName = "Smart ResearchLab";
    const QString companyAddress = "Urban Park, Ariana 1080, Tunisie";
    const QString companyEmail = "finance@smartresearchlab.tn";
    const QString companyPhone = "+216 XX XXX XXX";

    const QString invoiceNo = makeInvoiceNumber();
    const QString invoiceDate = QDate::currentDate().toString("dd/MM/yyyy");

    const QString typeLabel = (row.type.trimmed() == "Dépense") ? "DÉPENSE" : "REVENU";

    QString designation = row.categorie.trimmed();
    const QString desc = row.description.trimmed();
    if (!desc.isEmpty() && desc != "(null)") designation += " — " + desc;
    if (designation.trimmed().isEmpty()) designation = "Transaction interne";

    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(200);

    QPainter p(&pdf);
    if (!p.isActive()) return false;

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    const int W = pdf.width();
    const int H = pdf.height();
    const int M = 90;              // marges
    int y = M;

    auto setFont = [&](int pt, bool bold=false){
        QFont f("Segoe UI", pt);
        f.setBold(bold);
        p.setFont(f);
    };

    QPen pen(Qt::black);
    pen.setWidth(1);
    p.setPen(pen);

    // ================= HEADER (GAUCHE: SOCIÉTÉ) =================
    setFont(18, true);
    p.drawText(QRect(M, y, W/2, 30), Qt::AlignLeft | Qt::AlignVCenter, companyName);
    y += 30;

    setFont(10);
    p.drawText(QRect(M, y, W/2 + 200, 16), Qt::AlignLeft | Qt::AlignVCenter, companyAddress);
    y += 16;
    p.drawText(QRect(M, y, W/2 + 200, 16), Qt::AlignLeft | Qt::AlignVCenter,
               companyPhone + "  |  " + companyEmail);

    // ================= HEADER (DROITE: FACTURE) =================
    // IMPORTANT: rect assez grand + on place en haut, pas collé
    const int rightW = 520;
    const int rightX = W - M - rightW;

    setFont(24, true);
    QFontMetrics fmTitle(p.font());
    const int titleRectH = fmTitle.height() + fmTitle.descent() + 10;

    const int topY = M - 10; // petite marge pour éviter le clip
    p.drawText(QRect(rightX, topY, rightW, titleRectH),
               Qt::AlignRight | Qt::AlignVCenter,
               "FACTURE INTERNE");

    setFont(10, true);
    p.drawText(QRect(rightX, topY + titleRectH + 4, rightW, 16),
               Qt::AlignRight | Qt::AlignVCenter,
               "N° : " + invoiceNo);

    setFont(10, false);
    p.drawText(QRect(rightX, topY + titleRectH + 22, rightW, 16),
               Qt::AlignRight | Qt::AlignVCenter,
               "Date : " + invoiceDate);

    // Ligne séparatrice (y = max de ce qui a été écrit en haut)
    y = qMax(y + 20, topY + titleRectH + 50);
    p.drawLine(M, y, W - M, y);
    y += 20;

    // ================= BLOCS INFO =================
    const int boxH = 120;
    const int gap = 18;
    const int boxW = (W - 2*M - gap) / 2;

    QRect boxDoc(M, y, boxW, boxH);
    QRect boxRef(M + boxW + gap, y, boxW, boxH);
    p.drawRect(boxDoc);
    p.drawRect(boxRef);

    setFont(11, true);
    p.drawText(boxDoc.adjusted(12, 10, -12, -10), Qt::AlignLeft, "Document");
    p.drawText(boxRef.adjusted(12, 10, -12, -10), Qt::AlignLeft, "Référence");

    setFont(10, false);
    p.drawText(boxDoc.adjusted(12, 35, -12, -10),
               Qt::AlignLeft | Qt::TextWordWrap,
               "Type : " + typeLabel + "\n"
                                       "Usage : Interne (Société)\n"
                                       "TVA : 19%");

    p.drawText(boxRef.adjusted(12, 35, -12, -10),
               Qt::AlignLeft | Qt::TextWordWrap,
               "Transaction : " + row.code + "\n"
                                             "Date transaction : " + row.dateTransaction + "\n"
                                           "Mode paiement : " + row.modePaiement);

    y += boxH + 18;

    // ================= TABLE LIGNES =================
    const int tableW = W - 2*M;
    const int headerH = 32;
    const int itemH = 56;

    const int colDesc = int(tableW * 0.56);
    const int colQty  = int(tableW * 0.10);
    const int colPU   = int(tableW * 0.17);
    const int colTot  = tableW - colDesc - colQty - colPU;

    // Header
    p.drawRect(QRect(M, y, tableW, headerH));
    p.drawLine(M + colDesc, y, M + colDesc, y + headerH);
    p.drawLine(M + colDesc + colQty, y, M + colDesc + colQty, y + headerH);
    p.drawLine(M + colDesc + colQty + colPU, y, M + colDesc + colQty + colPU, y + headerH);

    setFont(10, true);
    p.drawText(QRect(M + 10, y, colDesc - 20, headerH), Qt::AlignVCenter | Qt::AlignLeft, "Désignation");
    p.drawText(QRect(M + colDesc, y, colQty, headerH), Qt::AlignCenter, "Qt");
    p.drawText(QRect(M + colDesc + colQty, y, colPU, headerH), Qt::AlignCenter, "P.U (HT)");
    p.drawText(QRect(M + colDesc + colQty + colPU, y, colTot, headerH), Qt::AlignCenter, "Total (HT)");

    y += headerH;

    // Ligne
    p.drawRect(QRect(M, y, tableW, itemH));
    p.drawLine(M + colDesc, y, M + colDesc, y + itemH);
    p.drawLine(M + colDesc + colQty, y, M + colDesc + colQty, y + itemH);
    p.drawLine(M + colDesc + colQty + colPU, y, M + colDesc + colQty + colPU, y + itemH);

    setFont(10, false);
    p.drawText(QRect(M + 10, y + 6, colDesc - 20, itemH - 12),
               Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap,
               designation);

    p.drawText(QRect(M + colDesc, y, colQty, itemH), Qt::AlignCenter, "1");
    p.drawText(QRect(M + colDesc + colQty, y, colPU, itemH), Qt::AlignCenter, fmtDT(totalHT));
    p.drawText(QRect(M + colDesc + colQty + colPU, y, colTot, itemH), Qt::AlignCenter, fmtDT(totalHT));

    y += itemH + 18;

    // ================= TOTAUX =================
    const int totBoxW = 520;
    const int totBoxH = 130;
    QRect totalsBox(W - M - totBoxW, y, totBoxW, totBoxH);
    p.drawRect(totalsBox);

    int ty = totalsBox.y() + 18;
    auto line = [&](const QString& k, const QString& v, bool bold=false){
        setFont(10, bold);
        p.drawText(QRect(totalsBox.x()+14, ty, totBoxW-28, 18), Qt::AlignLeft, k);
        p.drawText(QRect(totalsBox.x()+14, ty, totBoxW-28, 18), Qt::AlignRight, v);
        ty += 26;
    };

    line("Sous-total (HT)", fmtDT(totalHT));
    line("TVA (19%)", fmtDT(tva));
    line("TOTAL TTC", fmtDT(totalTTC), true);

    y += totBoxH + 18;

    // ================= PIED DE PAGE =================
    setFont(9, false);
    p.drawText(QRect(M, H - M - 50, tableW, 50),
               Qt::AlignLeft | Qt::TextWordWrap,
               "Facture interne (sans client). Document généré automatiquement par le module Finance.");

    p.end();
    return true;
}
void MainWindow::on_BtnApply_clicked() {}
void MainWindow::on_BtnReset_clicked() {}
void MainWindow::on_BtnExport_clicked()
{
    bool ok = false;
    const Finance::Row row = selectedFinanceRowFromTable(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Export", "Sélectionne une transaction.");
        return;
    }

    const QString filePath = QFileDialog::getSaveFileName(
        this,
        "Exporter Facture Interne (PDF)",
        "FactureInterne_" + row.code + ".pdf",
        "PDF (*.pdf)"
        );
    if (filePath.isEmpty()) return;

    if (!exportInternalInvoicePdf_19(filePath, row)) {
        QMessageBox::critical(this, "Erreur", "Génération PDF échouée.");
        return;
    }

    QMessageBox::information(this, "Export", "Facture générée ✅");
    // optionnel ouvrir direct :
    // QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

// Tes boutons finance “autres” (inchangés)
void MainWindow::on_BtnAdd_3_clicked() { ui->stacked_F->setCurrentIndex(4); }
void MainWindow::on_BtnAdd_4_clicked() { ui->stacked_F->setCurrentIndex(3); }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
// ===================================== FIN FINANCE ============================================== //
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
