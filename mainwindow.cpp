#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finance.h"
#include "labs.h"
#include "employe.h"
#include "inventory.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QApplication>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QTableWidgetItem>
#include <QDate>
#include <QDebug>
#include <QHeaderView>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QLocale>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QTime>
#include <QCryptographicHash>








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

// ==================== LABS HELPERS ====================
static QString makeQrLabs(const QString& nom, const QString& num)
{
    QString s = ("LAB-" + nom.trimmed() + "-" + num.trimmed()).toUpper();
    s.replace(" ", "_");
    return s.left(30); // QRLABS varchar(30)
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow),m_empId(-1)
{
    ui->setupUi(this);
}
MainWindow::MainWindow(int empId, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),m_empId(empId)
{
    ui->setupUi(this);
    ui->TableEmp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableEmp->setSelectionMode(QAbstractItemView::SingleSelection);

    // ===== INIT FINANCE =====
    initFinanceUi();
    // ===== INIT PUBLICATION =====
    initPublicationUi();
    loadPublications();
    // ===== INIT LABS =====
    initLabsUi();
    // ===== INIT INVENTORY =====
    initInventoryUi();


    setupTable(ui->tablePublication);
    setupTable(ui->TableEmp);
    loadEmployees();   // ← Charge les employés présents dans la BD au démarrage
    setupTable(ui->TableCongeEmp);
    setupTable(ui->TableFormations_Emp);
    setupTable(ui->TableInventory);
    setupTable(ui->TableFinance);
    setupTable(ui->TableLabs_2);
    setupTable(ui->tableProjets);
    connect(ui->lineSearchEmp, &QLineEdit::textChanged,
            this, &MainWindow::filterEmployees);
    connect(ui->btnTrier_emp, &QPushButton::clicked,   // ← adapte le nom du bouton
            this, &MainWindow::sortByEmbaucheDate);

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

    // Boutons checkables
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
void MainWindow::on_tableEmployees_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    // Option 1: rien faire
    // Option 2: debug
    // QMessageBox::information(this, "click", "Row clicked");
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

/* =========================================================
   INVENTORY DETAIL VIEW (AFFICHÉ) - FLUENT BRANDED
   ========================================================= */

/* Main page background - Soft Teal Gradient instead of solid white */
QWidget#afficheri {
    background: qlineargradient(
        x1:0, y1:0, x2:0, y2:1,
        stop:0 #F0FDF4,
        stop:1 #FFFFFF
    );
}

QFrame#CardGeneral, QFrame#CardStock, QFrame#CardDescription {
    background-color: #FFFFFF;
    border: 1px solid #E2E8F0;
    border-radius: 12px;
    padding: 15px;
    /* Soft shadow effect */
    border-bottom: 2px solid #CBD5E1;
}

/* Card Accent Border (Brand Green) */
QFrame#CardGeneral, QFrame#CardStock, QFrame#CardDescription {
    border-top: 4px solid #18A06A;
}

/* Key Labels - Subtle but clear */
QLabel#lbl_g1, QLabel#lbl_g2, QLabel#lbl_g3, QLabel#lbl_g4, QLabel#lbl_g5, QLabel#lbl_g6,
QLabel#lbl_s1, QLabel#lbl_s2, QLabel#lbl_s3, QLabel#lbl_s4, QLabel#lbl_s5, QLabel#lbl_s6,
QLabel#lbl_d1 {
    color: #64748B;
    font-size: 11px;
    font-weight: 700;
    text-transform: uppercase;
    letter-spacing: 1px;
    margin-right: 15px;
}

/* Value Labels - High contrast brand colors */
QLabel#aff_id, QLabel#aff_sku, QLabel#aff_name, QLabel#aff_type, QLabel#aff_price, QLabel#aff_status,
QLabel#aff_qtav, QLabel#aff_qtrs, QLabel#aff_threshold, QLabel#aff_zone, QLabel#aff_shelf, QLabel#aff_unit,
QLabel#aff_description {
    color: #0B2E1F;
    font-size: 14px;
    font-weight: 700;
    padding: 2px 8px;
    background: rgba(24, 160, 106, 0.05); /* Very light green tint for value background */
    border-radius: 4px;
}

/* Price specific - make it stand out */
QLabel#aff_price {
    color: #18A06A;
    font-size: 18px;
}

/* Description - readable and clean */
QLabel#aff_description {
    font-weight: 400;
    line-height: 1.6;
    color: #334155;
    background: transparent;
    padding: 10px 0px;
}

/* Header Text */
QLabel#aff_header_title {
    color: #0F7F55;
    font-size: 26px;
    font-weight: 900;
    margin-bottom: 5px;
}

/* Back Button - Rounded and Subtle */
QPushButton#retour_stat_6 {
    background: #FFFFFF;
    color: #0F7F55;
    border: 2px solid #0F7F55;
    border-radius: 20px;
    padding: 8px 20px;
}

QPushButton#retour_stat_6:hover {
    background: #F0FDF4;
    border-color: #1BBE7B;
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
    loadEmployees();
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

/* ===================== SLOTS DE NAVIGATION SIMPLES ===================== */

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

// LABS - Navigation
void MainWindow::on_btnVoirStatistiquesPub_2_clicked() { ui->stacked_L->setCurrentIndex(3); }
void MainWindow::on_btnAjouterPub_2_clicked() { ui->stacked_L->setCurrentIndex(2); }
void MainWindow::on_btnAjouterPub_4_clicked() { ui->stacked_L->setCurrentIndex(5); }
void MainWindow::on_BtnPopupCancelLabs_5_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_3_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_2_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_3_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_8_clicked() { ui->stacked_L->setCurrentIndex(0); }

// Inventory - Navigation
void MainWindow::on_BtnInventoryAdd_clicked() { ui->stacked_I->setCurrentIndex(1); }
void MainWindow::on_BtnInventoryAdd_2_clicked()
{
    const int r = ui->TableInventory->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Afficher", "Sélectionnez un produit.");
        return;
    }

    QTableWidgetItem *it = ui->TableInventory->item(r, 0);
    if (!it) return;

    // Read from basic columns
    const QString sku    = ui->TableInventory->item(r, 1)->text();
    const QString name   = ui->TableInventory->item(r, 2)->text();
    const QString price  = ui->TableInventory->item(r, 3)->text();
    const QString qtAv   = ui->TableInventory->item(r, 4)->text();
    const QString status = ui->TableInventory->item(r, 5)->text();

    // Read from UserRoles in column 0
    const QString id     = it->data(Qt::UserRole).toString();
    const QString zone   = it->data(Qt::UserRole + 1).toString();
    const QString shelf  = it->data(Qt::UserRole + 2).toString();
    const QString unit   = it->data(Qt::UserRole + 3).toString();
    const QString type   = it->data(Qt::UserRole + 4).toString();
    const QString desc   = it->data(Qt::UserRole + 5).toString();
    const QString qtRs   = it->data(Qt::UserRole + 6).toString();
    const QString thr    = it->data(Qt::UserRole + 7).toString();

    // Update Detail labels
    ui->aff_id->setText(id);
    ui->aff_sku->setText(sku);
    ui->aff_name->setText(name);
    ui->aff_type->setText(type);
    ui->aff_price->setText(price + " €");
    ui->aff_qtav->setText(qtAv);
    ui->aff_qtrs->setText(qtRs);
    ui->aff_threshold->setText(thr);
    ui->aff_unit->setText(unit);
    ui->aff_zone->setText(zone);
    ui->aff_shelf->setText(shelf);
    ui->aff_status->setText(status);
    ui->aff_description->setText(desc.isEmpty() ? "Pas de description" : desc);

    ui->stacked_I->setCurrentIndex(4);
}
// on_BtnInventoryEdit_clicked → full CRUD implementation below (//start inventory crud)
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

// Projets - Navigation
void MainWindow::on_retour_statn_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnRetourEditProj_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnRetourAddProj_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnAjouterProj_clicked() { ui->stack_proj->setCurrentIndex(1); }
void MainWindow::on_btnModifierProj_clicked() { ui->stack_proj->setCurrentIndex(2); }
void MainWindow::on_btnVoirStatistiquesProj_clicked() { ui->stack_proj->setCurrentIndex(3); }

// ==================== FINANCE HELPERS ====================

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

//================================================================================================================================================
void MainWindow::initPublicationUi()
{
    // Remplir combos (si pas déjà fait dans UI)
    ui->comboStatusBrevetAdd->clear();
    ui->comboStatusBrevetAdd->addItems({"En cours","Déposé","Accepté","Refusé","Publié"});

    ui->comboStatusBrevetEdit->clear();
    ui->comboStatusBrevetEdit->addItems({"En cours","Déposé","Accepté","Refusé","Publié"});

    // tablePublication : on suppose 8 colonnes visibles (sans lien_document)
    ui->tablePublication->setColumnCount(8);
    ui->tablePublication->setHorizontalHeaderLabels({
        "Titre","Résumé","Inventeurs","Domaine","Type","Numéro","Date dépôt","Statut"
    });
}

QString MainWindow::selectedPublicationId() const
{
    int row = ui->tablePublication->currentRow();
    if (row < 0) return {};
    auto *it = ui->tablePublication->item(row, 0);
    if (!it) return {};
    return it->data(Qt::UserRole).toString(); // ID stocké caché
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

    int r = 0;
    for (const auto &p : rows) {
        ui->tablePublication->insertRow(r);

        auto *itTitre = new QTableWidgetItem(p.titre);
        itTitre->setData(Qt::UserRole, p.id); // on cache ID_PUBLICATION ici
        ui->tablePublication->setItem(r, 0, itTitre);

        ui->tablePublication->setItem(r, 1, new QTableWidgetItem(p.resume));
        ui->tablePublication->setItem(r, 2, new QTableWidgetItem(p.inventeurs));
        ui->tablePublication->setItem(r, 3, new QTableWidgetItem(p.domaine));
        ui->tablePublication->setItem(r, 4, new QTableWidgetItem(p.type));
        ui->tablePublication->setItem(r, 5, new QTableWidgetItem(p.numero));
        ui->tablePublication->setItem(r, 6, new QTableWidgetItem(p.dateDepot));
        ui->tablePublication->setItem(r, 7, new QTableWidgetItem(p.statut));

        r++;
    }
}

//-----------------------------------------------------------------------------------------------
void MainWindow::on_btnAddPub_clicked()
{
    QString titre = ui->lineTitreAdd->text().trimmed();
    QString resume = ui->lineResumeAdd->text().trimmed();
    QString inventeurs = ui->lineInventeursAdd->text().trimmed();
    QString domaine = ui->lineDomaineAdd->text().trimmed();
    QString type = ui->comboTypeBrevetAdd->currentText();
    QString statut = ui->comboStatusBrevetAdd->currentText();
    QDate dateDepot = ui->dateDepotAdd->date();

    // ---- contrôle de saisie ----
    if (titre.isEmpty()) { QMessageBox::warning(this,"Saisie","Titre obligatoire"); return; }
    if (inventeurs.isEmpty()) { QMessageBox::warning(this,"Saisie","Inventeurs obligatoire"); return; }
    if (domaine.isEmpty()) { QMessageBox::warning(this,"Saisie","Domaine obligatoire"); return; }

    bool ok=false;
    int numero = ui->lineNumeroBrevetAdd->text().trimmed().toInt(&ok);
    if (!ok || numero<=0) { QMessageBox::warning(this,"Saisie","Numéro brevet invalide"); return; }

    Publication p(titre,resume,inventeurs,domaine,type,numero,dateDepot,statut);

    QString err;
    if (!p.ajouter(m_empId, &err)   ) {
        QMessageBox::critical(this,"SQL Error", err);
        return;
    }

    QMessageBox::information(this,"Ajout","Publication ajoutée ");
    ui->stack_pub->setCurrentIndex(0);
    loadPublications();
}

//-----------------------------------------------------------------------------------------------------
void MainWindow::on_btnModifierPub_clicked()
{
    QString id = selectedPublicationId();
    if (id.isEmpty()) {
        QMessageBox::warning(this,"Modification","Sélectionne une publication d'abord.");
        return;
    }
    idPublicationToEdit = id;

    int row = ui->tablePublication->currentRow();
    ui->lineTitreEdit->setText(ui->tablePublication->item(row,0)->text());
    ui->lineResumeEdit->setText(ui->tablePublication->item(row,1)->text());
    ui->lineInventeursEdit->setText(ui->tablePublication->item(row,2)->text());
    ui->lineDomaineEdit->setText(ui->tablePublication->item(row,3)->text());

    ui->comboTypeBrevetEdit->setCurrentText(ui->tablePublication->item(row,4)->text());
    ui->lineNumeroBrevetEdit->setText(ui->tablePublication->item(row,5)->text());

    ui->dateDepotEdit->setDate(QDate::fromString(ui->tablePublication->item(row,6)->text(),"yyyy-MM-dd"));
    ui->comboStatusBrevetEdit->setCurrentText(ui->tablePublication->item(row,7)->text());

    ui->stack_pub->setCurrentIndex(2);
}
//--------------------------------------------------------------------------------------------------------
void MainWindow::on_btnConfirmEditPub_clicked()
{
    if (idPublicationToEdit.isEmpty()) {
        QMessageBox::warning(this,"Modification","ID manquant.");
        return;
    }

    QString titre = ui->lineTitreEdit->text().trimmed();
    QString resume = ui->lineResumeEdit->text().trimmed();
    QString inventeurs = ui->lineInventeursEdit->text().trimmed();
    QString domaine = ui->lineDomaineEdit->text().trimmed();
    QString type = ui->comboTypeBrevetEdit->currentText();
    QString statut = ui->comboStatusBrevetEdit->currentText();
    QDate dateDepot = ui->dateDepotEdit->date();

    if (titre.isEmpty()) { QMessageBox::warning(this,"Saisie","Titre obligatoire"); return; }

    bool ok=false;
    int numero = ui->lineNumeroBrevetEdit->text().trimmed().toInt(&ok);
    if (!ok || numero<=0) { QMessageBox::warning(this,"Saisie","Numéro brevet invalide"); return; }

    QString err;
    if (!Publication::modifier(idPublicationToEdit, titre,resume,inventeurs,domaine,type,numero,dateDepot,statut,&err)) {
        QMessageBox::critical(this,"SQL Error",err);
        return;
    }

    QMessageBox::information(this,"Modification","Modification réussie ");
    idPublicationToEdit.clear();
    ui->stack_pub->setCurrentIndex(0);
    loadPublications();
}
//-----------------------------------------------------------------------------------------------------
void MainWindow::on_btnSupprimerPub_clicked()
{
    QString id = selectedPublicationId();
    if (id.isEmpty()) {
        QMessageBox::warning(this,"Suppression","Sélectionne une publication d'abord.");
        return;
    }

    auto reply = QMessageBox::question(this,"Confirmation",
                                       "Voulez-vous vraiment supprimer cette publication ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    QString err;
    if (!Publication::supprimer(id, &err)) {
        QMessageBox::critical(this,"SQL Error",err);
        return;
    }

    QMessageBox::information(this,"Suppression","Suppression réussie ✅");
    loadPublications();
}

// ==================== FINANCE CRUD ====================

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
    const int IDEMP = m_empId;
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
    const int rightW = 520;
    const int rightX = W - M - rightW;

    setFont(24, true);
    QFontMetrics fmTitle(p.font());
    const int titleRectH = fmTitle.height() + fmTitle.descent() + 10;

    const int topY = M - 10;
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

    // Ligne séparatrice
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
}

// Autres boutons finance
void MainWindow::on_BtnAdd_3_clicked() { ui->stacked_F->setCurrentIndex(4); }
void MainWindow::on_BtnAdd_4_clicked() { ui->stacked_F->setCurrentIndex(3); }

// ==================== EMPLOYEE CRUD ====================

void MainWindow::loadEmployees()
{
    ui->TableEmp->clearContents();
    ui->TableEmp->setRowCount(0);

    QVector<Employe::Row> rows;
    QString errMsg;
    if (!Employe::chargerTout(rows, &errMsg)) {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les employés :\n" + errMsg);
        return;
    }

    ui->TableEmp->setColumnCount(10);
    ui->TableEmp->setHorizontalHeaderLabels({
        "CIN", "Nom", "Prénom", "Username", "Email",
        "Poste", "Département", "Date embauche", "Salaire", "Rôle"
    });

    ui->TableEmp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableEmp->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableEmp->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int rowIndex = 0;
    for (const auto &r : rows)
    {
        ui->TableEmp->insertRow(rowIndex);

        auto *itemCin = new QTableWidgetItem(r.cin);
        itemCin->setData(Qt::UserRole, r.idEmploye);
        ui->TableEmp->setItem(rowIndex, 0, itemCin);

        ui->TableEmp->setItem(rowIndex, 1, new QTableWidgetItem(r.nom));
        ui->TableEmp->setItem(rowIndex, 2, new QTableWidgetItem(r.prenom));
        ui->TableEmp->setItem(rowIndex, 3, new QTableWidgetItem(r.username));
        ui->TableEmp->setItem(rowIndex, 4, new QTableWidgetItem(r.email));
        ui->TableEmp->setItem(rowIndex, 5, new QTableWidgetItem(r.poste));
        ui->TableEmp->setItem(rowIndex, 6, new QTableWidgetItem(r.departement));
        ui->TableEmp->setItem(rowIndex, 7, new QTableWidgetItem(r.dateEmbauche));
        ui->TableEmp->setItem(rowIndex, 8, new QTableWidgetItem(QString::number(r.salaire, 'f', 2)));
        ui->TableEmp->setItem(rowIndex, 9, new QTableWidgetItem(r.role));

        rowIndex++;
    }

    ui->TableEmp->resizeColumnsToContents();
}

void MainWindow::on_btnSaveEmployee_clicked()
{
    QString cin         = ui->lineCINAdd->text().trimmed();
    QString nom         = ui->lineNomAdd->text().trimmed();
    QString prenom      = ui->linePrenomAdd->text().trimmed();
    QString username    = ui->lineUsernameAdd->text().trimmed();
    QString email       = ui->lineEmailAdd->text().trimmed();
    QString password    = ui->linePasswordAdd->text();
    QString poste       = ui->linePosteAdd->text().trimmed();
    QString departement = ui->lineDepartementAdd->text().trimmed();
    double  salaire     = ui->lineSalaireAdd->text().toDouble();
    QString role        = ui->comboRoleAdd->currentText().trimmed();
    QDate   dateEmb     = ui->dateEmbaucheAdd->date();

    // Validations de base
    if (cin.length() != 8 || !QRegularExpression("^[0-9]{8}$").match(cin).hasMatch()) {
        QMessageBox::warning(this, "CIN invalide", "Le CIN doit contenir exactement 8 chiffres.");
        return;
    }

    if (Employe::usernameExiste(username)) {
        QMessageBox::warning(this, "Username", "Ce nom d'utilisateur existe déjà.");
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Mot de passe", "Obligatoire.");
        return;
    }

    if (salaire <= 0) {
        QMessageBox::warning(this, "Salaire", "Doit être positif.");
        return;
    }

    QString passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    Employe e(cin, nom, prenom, username, passwordHash, email,
              poste, departement, dateEmb, salaire, role);

    QString errMsg;
    if (!e.ajouter(&errMsg)) {
        QMessageBox::critical(this, "Échec ajout", errMsg);
        return;
    }

    QMessageBox::information(this, "Succès", "Employé ajouté.");
    loadEmployees();
    ui->stack_emp->setCurrentIndex(0);

    // Reset
    ui->lineCINAdd->clear();
    ui->lineNomAdd->clear();
    ui->linePrenomAdd->clear();
    ui->lineUsernameAdd->clear();
    ui->linePasswordAdd->clear();
    ui->lineEmailAdd->clear();
    ui->linePosteAdd->clear();
    ui->lineDepartementAdd->clear();
    ui->lineSalaireAdd->clear();
    ui->comboRoleAdd->setCurrentIndex(0);
    ui->dateEmbaucheAdd->setDate(QDate::currentDate());
}

void MainWindow::on_btnSupprimer_emp_clicked()
{
    int row = ui->TableEmp->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une ligne.");
        return;
    }

    QTableWidgetItem *item = ui->TableEmp->item(row, 0);

    QString idEmploye = item->data(Qt::UserRole).toString(); // ✅ ID caché

    if (idEmploye.isEmpty()) {
        QMessageBox::critical(this, "Erreur",
                              "ID employé introuvable.");
        return;
    }

    QString nom = ui->TableEmp->item(row, 1)->text();
    QString prenom = ui->TableEmp->item(row, 2)->text();

    QMessageBox::StandardButton reply =
        QMessageBox::question(this,
                              "Confirmation",
                              "Supprimer " + nom + " " + prenom + " ?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes)
        return;

    QString err;
    if (Employe::supprimer(idEmploye, &err))
    {
        QMessageBox::information(this, "Succès",
                                 "Employé supprimé.");
        loadEmployees(); // ✅ Recharge tableau
    }
    else
    {
        QMessageBox::critical(this, "Erreur",
                              "Suppression échouée :\n" + err);
    }
}




void MainWindow::on_btnModifier_emp_clicked()
{
    int row = ui->TableEmp->currentRow();
    if(row < 0){
        QMessageBox::warning(this, "Sélection", "Veuillez sélectionner un employé !");
        return;
    }

    for(int col=0; col<ui->TableEmp->columnCount(); ++col){
        if(!ui->TableEmp->item(row, col))
            ui->TableEmp->setItem(row, col, new QTableWidgetItem(""));
    }

    ui->lineCIN_emp->setText(ui->TableEmp->item(row, 0)->text());
    ui->lineNomEmp->setText(ui->TableEmp->item(row, 1)->text());
    ui->linePrenomEmp->setText(ui->TableEmp->item(row, 2)->text());
    ui->lineUsernameEmp->setText(ui->TableEmp->item(row, 3)->text());
    ui->lineEmailEmp->setText(ui->TableEmp->item(row, 4)->text());
    ui->linePostemp->setText(ui->TableEmp->item(row, 5)->text());
    ui->lineDepartementEmp->setText(ui->TableEmp->item(row, 6)->text());
    ui->dateEmbaucheEmp->setDate(QDate::fromString(ui->TableEmp->item(row, 7)->text(), "yyyy-MM-dd"));
    ui->lineSalaireEmp->setText(ui->TableEmp->item(row, 8)->text());
    ui->comboRoleAdd_2->setCurrentText(ui->TableEmp->item(row, 9)->text());

    ancienCin = ui->lineCIN_emp->text();
    ancienUsername = ui->lineUsernameEmp->text();

    ui->stack_emp->setCurrentIndex(2);
}

void MainWindow::on_btnSaveEditEmployee_clicked()
{
    int row = ui->TableEmp->currentRow();
    if(row < 0){
        QMessageBox::warning(this, "Erreur", "Aucune ligne sélectionnée !");
        return;
    }

    for(int col=0; col<ui->TableEmp->columnCount(); ++col){
        if(!ui->TableEmp->item(row, col))
            ui->TableEmp->setItem(row, col, new QTableWidgetItem(""));
    }

    QString cin         = ui->lineCIN_emp->text().trimmed();
    QString nom         = ui->lineNomEmp->text().trimmed();
    QString prenom      = ui->linePrenomEmp->text().trimmed();
    QString username    = ui->lineUsernameEmp->text().trimmed();
    QString email       = ui->lineEmailEmp->text().trimmed();
    QString poste       = ui->linePostemp->text().trimmed();
    QString departement = ui->lineDepartementEmp->text().trimmed();
    QString salaire     = ui->lineSalaireEmp->text().trimmed();
    QString role        = ui->comboRoleAdd_2->currentText().trimmed();
    QString dateEmbauche= ui->dateEmbaucheEmp->date().toString("yyyy-MM-dd");

    for(int r=0; r<ui->TableEmp->rowCount(); ++r){
        if(r==row) continue;
        if(ui->TableEmp->item(r,0)->text() == cin){
            QMessageBox::critical(this,"Erreur","Ce CIN existe déjà !");
            return;
        }
        if(ui->TableEmp->item(r,3)->text() == username){
            QMessageBox::critical(this,"Erreur","Ce nom d'utilisateur existe déjà !");
            return;
        }
    }

    ui->TableEmp->item(row,0)->setText(cin);
    ui->TableEmp->item(row,1)->setText(nom);
    ui->TableEmp->item(row,2)->setText(prenom);
    ui->TableEmp->item(row,3)->setText(username);
    ui->TableEmp->item(row,4)->setText(email);
    ui->TableEmp->item(row,5)->setText(poste);
    ui->TableEmp->item(row,6)->setText(departement);
    ui->TableEmp->item(row,7)->setText(dateEmbauche);
    ui->TableEmp->item(row,8)->setText(salaire);
    ui->TableEmp->item(row,9)->setText(role);

    QMessageBox::information(this,"Succès","Employé modifié !");
    ui->stack_emp->setCurrentIndex(0);
}
void MainWindow::on_btnAnnuler_emp_clicked()
{
    ui->stack_emp->setCurrentIndex(0);
}



void MainWindow::filterEmployees(const QString &searchText)
{
    QString search = searchText.trimmed().toLower();

    // Si le champ est vide → montrer toutes les lignes
    if (search.isEmpty()) {
        for (int row = 0; row < ui->TableEmp->rowCount(); ++row) {
            ui->TableEmp->setRowHidden(row, false);
        }
        return;
    }

    // Sinon : filtrer
    for (int row = 0; row < ui->TableEmp->rowCount(); ++row) {
        // Colonne 0 = CIN
        QString cin = ui->TableEmp->item(row, 0) ? ui->TableEmp->item(row, 0)->text().toLower() : "";
        // Colonne 9 = Rôle (dans ta version à 10 colonnes)
        QString role = ui->TableEmp->item(row, 3) ? ui->TableEmp->item(row, 3)->text().toLower() : "";

        bool match = cin.contains(search) || role.contains(search);

        ui->TableEmp->setRowHidden(row, !match);
    }
}


void MainWindow::sortByEmbaucheDate()
{
    if (ui->TableEmp->rowCount() == 0) return;

    const int dateColumn = 7;  // Colonne "Date embauche" (vérifie bien que c'est 7 chez toi)

    // Structure temporaire pour trier : date + index de ligne original
    struct RowInfo {
        QDate date;
        int originalRow;
    };

    QVector<RowInfo> rowsInfo;
    rowsInfo.reserve(ui->TableEmp->rowCount());

    for (int row = 0; row < ui->TableEmp->rowCount(); ++row) {
        QString dateStr = ui->TableEmp->item(row, dateColumn)
        ? ui->TableEmp->item(row, dateColumn)->text().trimmed()
        : "";

        QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
        if (!date.isValid()) {
            date = QDate(1900, 1, 1);  // Valeur sentinelle pour les dates invalides
        }

        rowsInfo.append({date, row});
    }

    // Tri stable
    std::stable_sort(rowsInfo.begin(), rowsInfo.end(),
                     [this](const RowInfo &a, const RowInfo &b) {
                         if (embaucheAscending) {
                             return a.date < b.date;
                         } else {
                             return a.date > b.date;
                         }
                     });

    // Créer le nouvel ordre des lignes
    QVector<int> newOrder;
    newOrder.reserve(rowsInfo.size());
    for (const auto &info : rowsInfo) {
        newOrder.append(info.originalRow);
    }

    // Réorganiser les lignes dans le tableau (méthode sûre)
    QVector<QVector<QTableWidgetItem*>> backup(ui->TableEmp->rowCount());

    // Sauvegarder tous les items avant de déplacer
    for (int row = 0; row < ui->TableEmp->rowCount(); ++row) {
        backup[row].resize(ui->TableEmp->columnCount());
        for (int col = 0; col < ui->TableEmp->columnCount(); ++col) {
            backup[row][col] = ui->TableEmp->takeItem(row, col);
        }
    }

    // Remettre dans le nouvel ordre
    for (int newRow = 0; newRow < newOrder.size(); ++newRow) {
        int oldRow = newOrder[newRow];
        for (int col = 0; col < ui->TableEmp->columnCount(); ++col) {
            ui->TableEmp->setItem(newRow, col, backup[oldRow][col]);
        }
    }

    // Nettoyage (pas vraiment nécessaire ici car les items sont repris)
    // backup.clear(); inutile car les pointeurs ont été repris par setItem

    // Inverser pour le prochain clic
    embaucheAscending = !embaucheAscending;

    // Mettre à jour le texte du bouton avec flèche
    QString arrow = embaucheAscending ? "▲ (plus ancien en haut)" : "▼ (plus récent en haut)";
    ui->btnTrier_emp->setText("Trier par Date d'embauche " + arrow);
}
void MainWindow::on_btnForm_emp_clicked()
{
    ui->stack_emp->setCurrentIndex(5);
}












// ==================== LABS CRUD ====================

QString MainWindow::selectedLabsId() const
{
    const int r = ui->TableLabs_2->currentRow();
    if (r < 0) return {};

    QTableWidgetItem *it = ui->TableLabs_2->item(r, 1);
    if (!it) return {};
    return it->data(Qt::UserRole).toString();
}

void MainWindow::setupTableLabs()
{
    ui->TableLabs_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableLabs_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableLabs_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableLabs_2->verticalHeader()->setVisible(false);
    ui->TableLabs_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->TableLabs_2->setColumnCount(9);
    ui->TableLabs_2->setHorizontalHeaderLabels({
        "", "Nom Labo", "Responsable", "Numéro", "Localisation",
        "Disponibilité", "Spécialité", "Capacité", "QR Code"
    });
    ui->TableLabs_2->setColumnHidden(0, true);
}

void MainWindow::loadLabs()
{
    ui->TableLabs_2->setRowCount(0);

    QVector<Labs::Row> rows;
    QString err;
    if (!Labs::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    int row = 0;
    for (const auto& r : rows) {
        ui->TableLabs_2->insertRow(row);

        auto *itNom = new QTableWidgetItem(r.nomlabo);
        itNom->setData(Qt::UserRole, r.id);

        ui->TableLabs_2->setItem(row, 1, itNom);
        ui->TableLabs_2->setItem(row, 2, new QTableWidgetItem(r.responsable));
        ui->TableLabs_2->setItem(row, 3, new QTableWidgetItem(r.numero));
        ui->TableLabs_2->setItem(row, 4, new QTableWidgetItem(r.localisation));
        ui->TableLabs_2->setItem(row, 5, new QTableWidgetItem(r.disponibilite));
        ui->TableLabs_2->setItem(row, 6, new QTableWidgetItem(r.specialite));
        ui->TableLabs_2->setItem(row, 7, new QTableWidgetItem(r.resultat));
        ui->TableLabs_2->setItem(row, 8, new QTableWidgetItem(r.qrlabs));

        row++;
    }
}
void MainWindow::initLabsUi()
{
    // ✅ DISPONIBILITE (doit matcher la contrainte Oracle)
    ui->LabCap_3->clear();
    ui->LabCap_3->addItem("Disponible");
    ui->LabCap_3->addItem("Occupe");

    ui->LabCap_5->clear();
    ui->LabCap_5->addItem("Disponible");
    ui->LabCap_5->addItem("Occupe");

    setupTableLabs();
    loadLabs();
}

void MainWindow::on_BtnPopupResetLabs_3_clicked()
{
    ui->LabName_3->clear();
    ui->LabResponsible_3->clear();
    ui->LabNumber_3->clear();
    ui->LabLocation_3->clear();
    ui->LabName_12->clear();
    ui->LabSpec_3->setCurrentIndex(0);
    ui->LabCap_3->setCurrentIndex(0);
}

void MainWindow::on_BtnPopupSaveLabs_3_clicked()
{
    const QString nom   = ui->LabName_3->text().trimmed();
    const QString resp  = ui->LabResponsible_3->text().trimmed();
    const QString num   = ui->LabNumber_3->text().trimmed();
    const QString loc   = ui->LabLocation_3->text().trimmed();
    const QString spec  = ui->LabSpec_3->currentText().trimmed();
    const QString disp  = ui->LabCap_3->currentText().trimmed();
    const QString capa  = ui->LabName_12->text().trimmed();
    const QString qr    = makeQrLabs(nom, num);

    if (nom.isEmpty()) { QMessageBox::warning(this, "Ajout", "Nom labo obligatoire."); return; }
    if (resp.isEmpty()) { QMessageBox::warning(this, "Ajout", "Responsable obligatoire."); return; }
    if (num.isEmpty()) { QMessageBox::warning(this, "Ajout", "Numéro obligatoire."); return; }
    if (loc.isEmpty()) { QMessageBox::warning(this, "Ajout", "Localisation obligatoire."); return; }
    if (spec.isEmpty() || spec.startsWith("choisir")) { QMessageBox::warning(this, "Ajout", "Choisis une spécialité."); return; }
    if (disp.isEmpty() || disp.startsWith("choisir")) { QMessageBox::warning(this, "Ajout", "Choisis une disponibilité."); return; }
    if (capa.isEmpty()) { QMessageBox::warning(this, "Ajout", "Capacité obligatoire."); return; }

    const int IDEMP = m_empId;   // ✅ NUMBER

    Labs lab(nom, resp, num, loc, spec, disp, capa, qr, IDEMP);

    QString err;
    if (!lab.ajouter(&err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    ui->stacked_L->setCurrentIndex(0);
    loadLabs();
}

void MainWindow::on_BtnPopupResetLabs_5_clicked()
{
    ui->LabName_5->clear();
    ui->LabResponsible_5->clear();
    ui->LabNumber_5->clear();
    ui->LabLocation_5->clear();
    ui->LabName_13->clear();
    if (ui->LabSpec_5->count() > 0) ui->LabSpec_5->setCurrentIndex(0);
    if (ui->LabCap_5->count() > 0) ui->LabCap_5->setCurrentIndex(0);
}

void MainWindow::on_BtnPopupSaveLabs_5_clicked()
{
    if (idLabsToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "ID laboratoire introuvable.");
        return;
    }

    const QString nom   = ui->LabName_5->text().trimmed();
    const QString resp  = ui->LabResponsible_5->text().trimmed();
    const QString num   = ui->LabNumber_5->text().trimmed();
    const QString loc   = ui->LabLocation_5->text().trimmed();
    const QString spec  = ui->LabSpec_5->currentText().trimmed();
    const QString disp  = ui->LabCap_5->currentText().trimmed();
    const QString capa  = ui->LabName_13->text().trimmed();
    const QString qr    = makeQrLabs(nom, num);

    if (nom.isEmpty()) { QMessageBox::warning(this, "Modifier", "Nom labo obligatoire."); return; }
    if (resp.isEmpty()) { QMessageBox::warning(this, "Modifier", "Responsable obligatoire."); return; }
    if (num.isEmpty()) { QMessageBox::warning(this, "Modifier", "Numéro obligatoire."); return; }
    if (loc.isEmpty()) { QMessageBox::warning(this, "Modifier", "Localisation obligatoire."); return; }
    if (spec.isEmpty() || spec.startsWith("choisir")) { QMessageBox::warning(this, "Modifier", "Choisis une spécialité."); return; }
    if (disp.isEmpty() || disp.startsWith("choisir")) { QMessageBox::warning(this, "Modifier", "Choisis une disponibilité."); return; }
    if (capa.isEmpty()) { QMessageBox::warning(this, "Modifier", "Capacité obligatoire."); return; }

    QString err;
    if (!Labs::modifier(idLabsToEdit, nom, resp, num, loc, spec, disp, capa, qr, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    ui->stacked_L->setCurrentIndex(0);
    loadLabs();
}

void MainWindow::on_btnSupprimerPub_2_clicked()
{
    const QString id = selectedLabsId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Supprimer", "Sélectionne un laboratoire.");
        return;
    }

    auto reply = QMessageBox::question(this, "Confirmation",
                                       "Voulez-vous vraiment supprimer ce laboratoire ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    QString err;
    if (!Labs::supprimer(id, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    loadLabs();
}

void MainWindow::on_btnAppliquerPub_3_clicked()
{
    const QString key = ui->LabsSearch_2->text().trimmed().toLower();
    const QString spec = ui->LabsSpec_2->currentText().trimmed().toLower();
    const QString disp = ui->LabsCap_2->currentText().trimmed().toLower();

    for (int r = 0; r < ui->TableLabs_2->rowCount(); ++r) {
        const QString nom  = ui->TableLabs_2->item(r,1) ? ui->TableLabs_2->item(r,1)->text().toLower() : "";
        const QString resp = ui->TableLabs_2->item(r,2) ? ui->TableLabs_2->item(r,2)->text().toLower() : "";
        const QString num  = ui->TableLabs_2->item(r,3) ? ui->TableLabs_2->item(r,3)->text().toLower() : "";
        const QString loc  = ui->TableLabs_2->item(r,4) ? ui->TableLabs_2->item(r,4)->text().toLower() : "";
        const QString d    = ui->TableLabs_2->item(r,5) ? ui->TableLabs_2->item(r,5)->text().toLower() : "";
        const QString s    = ui->TableLabs_2->item(r,6) ? ui->TableLabs_2->item(r,6)->text().toLower() : "";

        bool ok = true;

        if (!key.isEmpty()) {
            ok &= (nom.contains(key) || resp.contains(key) || num.contains(key) || loc.contains(key));
        }
        if (!spec.isEmpty() && !spec.startsWith("choisir")) {
            ok &= s.contains(spec);
        }
        if (!disp.isEmpty() && !disp.startsWith("choisir")) {
            ok &= d.contains(disp);
        }

        ui->TableLabs_2->setRowHidden(r, !ok);
    }
}

void MainWindow::on_btnReinitialiserPub_3_clicked()
{
    ui->LabsSearch_2->clear();
    ui->LabsSpec_2->setCurrentIndex(0);
    ui->LabsCap_2->setCurrentIndex(0);

    for (int r = 0; r < ui->TableLabs_2->rowCount(); ++r) {
        ui->TableLabs_2->setRowHidden(r, false);
    }
}

void MainWindow::on_btnModifierPub_2_clicked()
{
    const int r = ui->TableLabs_2->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Modifier", "Sélectionne un laboratoire.");
        return;
    }

    idLabsToEdit = selectedLabsId();
    if (idLabsToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "ID introuvable.");
        return;
    }

    ui->LabName_5->setText(ui->TableLabs_2->item(r,1)->text());
    ui->LabResponsible_5->setText(ui->TableLabs_2->item(r,2)->text());
    ui->LabNumber_5->setText(ui->TableLabs_2->item(r,3)->text());
    ui->LabLocation_5->setText(ui->TableLabs_2->item(r,4)->text());

    const QString disp = ui->TableLabs_2->item(r,5)->text();
    int idxDisp = ui->LabCap_5->findText(disp);
    ui->LabCap_5->setCurrentIndex(qMax(0, idxDisp));

    const QString spec = ui->TableLabs_2->item(r,6)->text();
    int idxSpec = ui->LabSpec_5->findText(spec);
    ui->LabSpec_5->setCurrentIndex(qMax(0, idxSpec));

    ui->LabName_13->setText(ui->TableLabs_2->item(r,7) ? ui->TableLabs_2->item(r,7)->text() : "");

    ui->stacked_L->setCurrentIndex(1);
}

void MainWindow::on_btnAjouterPub_3_clicked()
{
    const int r = ui->TableLabs_2->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "afficher", "Sélectionne un laboratoire.");
        return;
    }

    idLabsToEdit = selectedLabsId();
    if (idLabsToEdit.isEmpty()) {
        QMessageBox::warning(this, "afficher", "ID introuvable.");
        return;
    }

    ui->aff1->setText(ui->TableLabs_2->item(r,1)->text());
    ui->aff5->setText(ui->TableLabs_2->item(r,2)->text());
    ui->aff6->setText(ui->TableLabs_2->item(r,3)->text());
    ui->aff2->setText(ui->TableLabs_2->item(r,4)->text());

    const QString disp = ui->TableLabs_2->item(r,5)->text();
    int idxDisp = ui->aff7->findText(disp);
    ui->aff7->setCurrentIndex(qMax(0, idxDisp));

    const QString spec = ui->TableLabs_2->item(r,6)->text();
    int idxSpec = ui->aff3->findText(spec);
    ui->aff3->setCurrentIndex(qMax(0, idxSpec));

    ui->aff4->setText(ui->TableLabs_2->item(r,7) ? ui->TableLabs_2->item(r,7)->text() : "");
    ui->stacked_L->setCurrentIndex(4);
}

//start inventory crud
// ==================== INVENTORY HELPERS ====================

QString MainWindow::selectedInventoryIdProduct() const
{
    const int r = ui->TableInventory->currentRow();
    if (r < 0) return {};
    QTableWidgetItem *it = ui->TableInventory->item(r, 0);
    return it ? it->data(Qt::UserRole).toString() : QString();
}

QString MainWindow::selectedInventorySku() const
{
    const int r = ui->TableInventory->currentRow();
    if (r < 0) return {};
    QTableWidgetItem *it = ui->TableInventory->item(r, 1);
    return it ? it->text() : QString();
}

// ── Init ─────────────────────────────────────────────────────────────────────

void MainWindow::initInventoryUi()
{
    // Populate Status combo (add form)
    ui->Status->clear();
    ui->Status->addItem("on hand",   "on hand");
    ui->Status->addItem("limited",   "limited");
    ui->Status->addItem("stock out", "stock out");

    // Populate Status combo (edit form)
    ui->Status_2->clear();
    ui->Status_2->addItem("on hand",   "on hand");
    ui->Status_2->addItem("limited",   "limited");
    ui->Status_2->addItem("stock out", "stock out");

    // Filter Status combo
    ui->InventoryStatus->clear();
    ui->InventoryStatus->addItem("-- Tous --", "");
    ui->InventoryStatus->addItem("on hand",   "on hand");
    ui->InventoryStatus->addItem("limited",   "limited");
    ui->InventoryStatus->addItem("stock out", "stock out");

    // Zone combo (Add form) – Zones A B C D
    ui->Zone->clear();
    ui->Zone->addItem("Zone A", "A");
    ui->Zone->addItem("Zone B", "B");
    ui->Zone->addItem("Zone C", "C");
    ui->Zone->addItem("Zone D", "D");

    // Zone combo (Edit form) – Zones A B C D
    ui->Zone_2->clear();
    ui->Zone_2->addItem("Zone A", "A");
    ui->Zone_2->addItem("Zone B", "B");
    ui->Zone_2->addItem("Zone C", "C");
    ui->Zone_2->addItem("Zone D", "D");

    // Zone filter combo – Zones A B C D
    ui->InventoryZone->clear();
    ui->InventoryZone->addItem("-- Toutes zones --", "");
    ui->InventoryZone->addItem("Zone A", "A");
    ui->InventoryZone->addItem("Zone B", "B");
    ui->InventoryZone->addItem("Zone C", "C");
    ui->InventoryZone->addItem("Zone D", "D");

    // Shelf combo (Add form) – RDC / 1st / 2nd / 3rd floor
    ui->Shelf->clear();
    ui->Shelf->addItem("RDC",       "RDC");
    ui->Shelf->addItem("1st floor", "1st floor");
    ui->Shelf->addItem("2nd floor", "2nd floor");
    ui->Shelf->addItem("3rd floor", "3rd floor");

    // Shelf combo (Edit form) – RDC / 1st / 2nd / 3rd floor
    ui->Shelf_2->clear();
    ui->Shelf_2->addItem("RDC",       "RDC");
    ui->Shelf_2->addItem("1st floor", "1st floor");
    ui->Shelf_2->addItem("2nd floor", "2nd floor");
    ui->Shelf_2->addItem("3rd floor", "3rd floor");

    // Unit combo (Add form) – KG / L / M
    ui->Unit->clear();
    ui->Unit->addItem("kg", "kg");
    ui->Unit->addItem("L",  "L");
    ui->Unit->addItem("m",  "m");

    // Unit combo (Edit form) – KG / L / M
    ui->Unit_2->clear();
    ui->Unit_2->addItem("kg", "kg");
    ui->Unit_2->addItem("L",  "L");
    ui->Unit_2->addItem("m",  "m");

    // Type combo (Add form)
    ui->Type->clear();
    ui->Type->addItem("Matière première",  "Matière première");
    ui->Type->addItem("Composant",          "Composant");
    ui->Type->addItem("Produit fini",       "Produit fini");
    ui->Type->addItem("Produit semi-fini",  "Produit semi-fini");
    ui->Type->addItem("Outil",              "Outil");
    ui->Type->addItem("Équipement",         "Équipement");
    ui->Type->addItem("Consommable",        "Consommable");
    ui->Type->addItem("Pièce de rechange",  "Pièce de rechange");

    // Type combo (Edit form)
    ui->Type_2->clear();
    ui->Type_2->addItem("Matière première",  "Matière première");
    ui->Type_2->addItem("Composant",          "Composant");
    ui->Type_2->addItem("Produit fini",       "Produit fini");
    ui->Type_2->addItem("Produit semi-fini",  "Produit semi-fini");
    ui->Type_2->addItem("Outil",              "Outil");
    ui->Type_2->addItem("Équipement",         "Équipement");
    ui->Type_2->addItem("Consommable",        "Consommable");
    ui->Type_2->addItem("Pièce de rechange",  "Pièce de rechange");

    // SKU Input Mask: 3 Letters - 3 Numbers (case insensitive input, forces upper)
    // Format: AAA-999
    ui->Sku->setInputMask(">AAA-999; ");
    ui->Sku_2->setInputMask(">AAA-999; ");

    // Name Validation: Uppercase Letters, Numbers and Spaces only
    QRegularExpression nameRegex("^[A-Z0-9 ]*$");
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->Name->setValidator(nameValidator);
    ui->Name_2->setValidator(nameValidator);

    setupTableInventory();
    ui->stacked_I->setCurrentIndex(0);
    loadInventory();
}

void MainWindow::setupTableInventory()
{
    ui->TableInventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableInventory->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableInventory->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableInventory->verticalHeader()->setVisible(false);
    ui->TableInventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Columns: ID | SKU | Nom | Prix | Qt_AV | STATUS
    ui->TableInventory->setColumnCount(6);
    ui->TableInventory->setHorizontalHeaderLabels({
        "ID", "SKU", "Nom", "Prix", "Qté disp.", "Statut"
    });
    ui->TableInventory->hideColumn(0); // Hide physical PK from Admin
    ui->TableInventory->setSortingEnabled(true);
    
    // SKU Input Mask: Alphanumeric prefix, hyphen, digits (relaxed to avoid blocking)
    ui->Sku->setInputMask(">NNN-NNN;0");
    ui->Sku_2->setInputMask(">NNN-NNN;0");

    // Hide ID input fields from Admin (automated)
    ui->IdProduct->setVisible(false);
    ui->IdProduct_2->setVisible(false);
    ui->LblIdProduct->setVisible(false);
    ui->LblIdProduct_2->setVisible(false);
}

// ── READ (load) ───────────────────────────────────────────────────────────────

void MainWindow::loadInventory()
{
    ui->TableInventory->setRowCount(0);

    QVector<Inventory::Row> rows;
    QString err;
    const int sortIdx = ui->InventorySort->currentIndex();
    QString orderBy = "SKU";
    if (sortIdx == 1) orderBy = "NAME ASC";
    else if (sortIdx == 2) orderBy = "PRICE ASC";
    else if (sortIdx == 3) orderBy = "PRICE DESC";

    if (!Inventory::chargerTout(rows, orderBy, &err)) {
        QMessageBox::critical(this, "Erreur SQL – Inventaire", err);
        return;
    }

    int r = 0;
    for (const auto &row : rows) {
        ui->TableInventory->insertRow(r);

        // col 0 – ID_PRODUCT (hidden PK stored in UserRole)
        auto *itId = new QTableWidgetItem(row.idProduct);
        itId->setData(Qt::UserRole,     row.idProduct);
        itId->setData(Qt::UserRole + 1, row.zone);        // store zone for edit pre-fill
        itId->setData(Qt::UserRole + 2, row.shelf);       // store shelf for edit pre-fill
        itId->setData(Qt::UserRole + 3, row.unit);        // store unit for edit pre-fill
        itId->setData(Qt::UserRole + 4, row.type);        // store type for edit pre-fill
        itId->setData(Qt::UserRole + 5, row.description); // store description
        itId->setData(Qt::UserRole + 6, row.qtRs);        // store qtRs
        itId->setData(Qt::UserRole + 7, row.threshold);   // store threshold
        ui->TableInventory->setItem(r, 0, itId);

        ui->TableInventory->setItem(r, 1, new QTableWidgetItem(row.sku));
        ui->TableInventory->setItem(r, 2, new QTableWidgetItem(row.name));
        ui->TableInventory->setItem(r, 3, new QTableWidgetItem(QString::number(row.price, 'f', 2)));
        ui->TableInventory->setItem(r, 4, new QTableWidgetItem(QString::number(row.qtAv)));
        ui->TableInventory->setItem(r, 5, new QTableWidgetItem(row.status));
        ++r;
    }
}

// ── CREATE ────────────────────────────────────────────────────────────────────

void MainWindow::on_BtnPopupSaveInventory_clicked()
{
    // Auto-uppercase for consistency
    const QString name      = ui->Name->text().trimmed().toUpper();
    const QString sku       = ui->Sku->text().trimmed().toUpper();
    
    // UI update to reflect uppercase
    ui->Name->setText(name);
    ui->Sku->setText(sku);

    const QString type      = ui->Type->currentData().toString();
    const int     qtAv      = ui->QtAv->value();
    const int     qtRs      = ui->QtRs->value();
    const int     threshold = ui->Threshold->value();
    const QString unit      = ui->Unit->currentData().toString();
    const double  price     = ui->Price->value();
    const QString status    = ui->Status->currentData().toString();
    const QString zone      = ui->Zone->currentData().toString();
    const QString shelf     = ui->Shelf->currentData().toString();
    const QString desc      = ui->Description->toPlainText().trimmed();

    // Validation: Name (Uppercase and Numbers only)
    QRegularExpression nameRegex("^[A-Z0-9 ]+$");
    if (!nameRegex.match(name).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des majuscules et des chiffres.");
        return;
    }

    // Validation: SKU (ABC-123 format: 3 letters, hyphen, 3 numbers)
    QRegularExpression skuRegex("^[A-Z]{3}-\\d{3}$");
    if (!skuRegex.match(sku).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le SKU doit respecter le format ABC-123 (3 lettres, un tiret, 3 chiffres).");
        return;
    }

    if (status.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Veuillez sélectionner un statut.");
        return;
    }

    Inventory inv(name, sku, type, qtAv, qtRs, threshold, unit, price, status, zone, shelf, desc);
    QString err;
    if (!inv.ajouter(&err)) {
        QMessageBox::critical(this, "Erreur SQL – Ajout", err);
        return;
    }

    QMessageBox::information(this, "Inventaire", "Produit ajouté avec succès.");
    ui->stacked_I->setCurrentIndex(0);
    loadInventory();
}

void MainWindow::on_BtnPopupResetInventory_clicked()
{
    ui->IdProduct->clear();
    ui->Sku->clear();
    ui->QtAv->setValue(0);
    ui->QtRs->setValue(0);
    ui->Threshold->setValue(0);
    ui->Price->setValue(0.0);
    ui->Status->setCurrentIndex(0);
    ui->Type->setCurrentIndex(0);
    ui->Unit->setCurrentIndex(0);
    ui->Zone->setCurrentIndex(0);
    ui->Shelf->setCurrentIndex(0);
    ui->Description->clear();
}

// ── UPDATE ────────────────────────────────────────────────────────────────────

void MainWindow::on_BtnInventoryEdit_clicked()
{
    const int r = ui->TableInventory->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Modifier", "Sélectionnez un produit.");
        return;
    }

    idProductToEdit = selectedInventoryIdProduct();
    skuToEdit       = selectedInventorySku();

    if (idProductToEdit.isEmpty() || skuToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "Impossible de récupérer l'ID ou le SKU.");
        return;
    }

    // Pre-fill the edit form
    ui->IdProduct_2->setText(ui->TableInventory->item(r, 0)->text());
    ui->Sku_2->setText(ui->TableInventory->item(r, 1)->text());
    ui->Name_2->setText(ui->TableInventory->item(r, 2)->text());
    ui->Price_2->setValue(ui->TableInventory->item(r, 3)->text().toDouble());
    ui->QtAv_2->setValue(ui->TableInventory->item(r, 4)->text().toInt());

    const QString statusVal = ui->TableInventory->item(r, 5)->text();
    int idx = ui->Status_2->findData(statusVal);
    ui->Status_2->setCurrentIndex(idx >= 0 ? idx : 0);

    // Pre-fill Zone combo (zone stored as "A"/"B"/"C"/"D" in UserRole+1)
    const QString zoneVal = ui->TableInventory->item(r, 0)->data(Qt::UserRole + 1).toString();
    int zoneIdx = ui->Zone_2->findData(zoneVal);
    ui->Zone_2->setCurrentIndex(zoneIdx >= 0 ? zoneIdx : 0);

    // Pre-fill Shelf combo (shelf stored in UserRole+2)
    const QString shelfVal = ui->TableInventory->item(r, 0)->data(Qt::UserRole + 2).toString();
    int shelfIdx = ui->Shelf_2->findData(shelfVal);
    ui->Shelf_2->setCurrentIndex(shelfIdx >= 0 ? shelfIdx : 0);

    // Pre-fill Unit combo (unit stored in UserRole+3)
    const QString unitVal = ui->TableInventory->item(r, 0)->data(Qt::UserRole + 3).toString();
    int unitIdx = ui->Unit_2->findData(unitVal);
    ui->Unit_2->setCurrentIndex(unitIdx >= 0 ? unitIdx : 0);

    // Pre-fill Type combo (type stored in UserRole+4)
    const QString typeVal = ui->TableInventory->item(r, 0)->data(Qt::UserRole + 4).toString();
    int typeIdx = ui->Type_2->findData(typeVal);
    ui->Type_2->setCurrentIndex(typeIdx >= 0 ? typeIdx : 0);

    // Pre-fill Description text (stored in UserRole+5)
    const QString descVal = ui->TableInventory->item(r, 0)->data(Qt::UserRole + 5).toString();
    ui->Description_2->setPlainText(descVal);

    ui->stacked_I->setCurrentIndex(2);
}

void MainWindow::on_BtnPopupSaveInventory_2_clicked()
{
    // Auto-uppercase for consistency
    const QString name      = ui->Name_2->text().trimmed().toUpper();
    const QString sku       = ui->Sku_2->text().trimmed().toUpper();

    // UI update to reflect uppercase
    ui->Name_2->setText(name);
    ui->Sku_2->setText(sku);

    const QString type      = ui->Type_2->currentData().toString();
    const int     qtAv      = ui->QtAv_2->value();
    const int     qtRs      = ui->QtRs_2->value();
    const int     threshold = ui->Threshold_2->value();
    const QString unit      = ui->Unit_2->currentData().toString();
    const double  price     = ui->Price_2->value();
    const QString status    = ui->Status_2->currentData().toString();
    const QString zone      = ui->Zone_2->currentData().toString();
    const QString shelf     = ui->Shelf_2->currentData().toString();
    const QString desc      = ui->Description_2->toPlainText().trimmed();

    if (idProductToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "Aucun produit sélectionné.");
        return;
    }

    // Validation: Name (Uppercase and Numbers only)
    QRegularExpression nameRegex("^[A-Z0-9 ]+$");
    if (!nameRegex.match(name).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des majuscules et des chiffres.");
        return;
    }

    // Validation: SKU (ABC-123 format: 3 letters, hyphen, 3 numbers)
    QRegularExpression skuRegex("^[A-Z]{3}-\\d{3}$");
    if (!skuRegex.match(sku).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le SKU doit respecter le format ABC-123 (3 lettres, un tiret, 3 chiffres).");
        return;
    }

    if (status.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Veuillez sélectionner un statut.");
        return;
    }

    QString err;
    if (!Inventory::modifier(idProductToEdit, name, sku, type, qtAv, qtRs, threshold, unit, price, status, zone, shelf, desc, &err)) {
        QMessageBox::critical(this, "Erreur SQL – Modification", err);
        return;
    }

    QMessageBox::information(this, "Inventaire", "Produit modifié avec succès.");
    idProductToEdit.clear();
    skuToEdit.clear();
    ui->stacked_I->setCurrentIndex(0);
    loadInventory();
}

void MainWindow::on_BtnPopupResetInventory_2_clicked()
{
    const int r = ui->TableInventory->currentRow();
    if (r < 0) return;

    ui->IdProduct_2->setText(ui->TableInventory->item(r, 0)->text());
    ui->Sku_2->setText(ui->TableInventory->item(r, 1)->text());
    ui->Name_2->setText(ui->TableInventory->item(r, 2)->text());
    ui->Price_2->setValue(ui->TableInventory->item(r, 3)->text().toDouble());
    ui->QtAv_2->setValue(ui->TableInventory->item(r, 4)->text().toInt());
    const QString statusVal = ui->TableInventory->item(r, 5)->text();
    int idx = ui->Status_2->findData(statusVal);
    ui->Status_2->setCurrentIndex(idx >= 0 ? idx : 0);
}

// ── DELETE ────────────────────────────────────────────────────────────────────

void MainWindow::on_BtnInventoryDelete_clicked()
{
    const QString id  = selectedInventoryIdProduct();
    const QString sku = selectedInventorySku();

    if (id.isEmpty() || sku.isEmpty()) {
        QMessageBox::warning(this, "Supprimer", "Sélectionnez un produit à supprimer.");
        return;
    }

    auto reply = QMessageBox::question(
        this,
        "Confirmation",
        QString("Supprimer le produit « %1 / %2 » ?").arg(id, sku),
        QMessageBox::Yes | QMessageBox::No
    );
    if (reply != QMessageBox::Yes) return;

    QString err;
    if (!Inventory::supprimer(id, sku, &err)) {
        QMessageBox::critical(this, "Erreur SQL – Suppression", err);
        return;
    }

    QMessageBox::information(this, "Inventaire", "Produit supprimé.");
    loadInventory();
}

// ── SEARCH / FILTER ───────────────────────────────────────────────────────────

void MainWindow::on_BtnInventoryApply_clicked()
{
    const QString kw     = ui->InventorySearch->text().trimmed();
    const QString status = ui->InventoryStatus->currentData().toString();
    const int     sortIdx = ui->InventorySort->currentIndex();

    QString orderBy = "SKU";
    if (sortIdx == 1) orderBy = "NAME ASC";
    else if (sortIdx == 2) orderBy = "PRICE ASC";
    else if (sortIdx == 3) orderBy = "PRICE DESC";

    QVector<Inventory::Row> rows;
    QString err;
    if (!Inventory::chercher(rows, kw, status, orderBy, &err)) {
        QMessageBox::critical(this, "Erreur SQL – Recherche", err);
        return;
    }

    ui->TableInventory->setRowCount(0);
    int r = 0;
    for (const auto &row : rows) {
        ui->TableInventory->insertRow(r);
        auto *itId = new QTableWidgetItem(row.idProduct);
        itId->setData(Qt::UserRole, row.idProduct);
        ui->TableInventory->setItem(r, 0, itId);
        ui->TableInventory->setItem(r, 1, new QTableWidgetItem(row.sku));
        ui->TableInventory->setItem(r, 2, new QTableWidgetItem(row.name));
        ui->TableInventory->setItem(r, 3, new QTableWidgetItem(QString::number(row.price, 'f', 2)));
        ui->TableInventory->setItem(r, 4, new QTableWidgetItem(QString::number(row.qtAv)));
        ui->TableInventory->setItem(r, 5, new QTableWidgetItem(row.status));
        ++r;
    }
}

//end



void MainWindow::on_btnAddProj_clicked()
{

}

