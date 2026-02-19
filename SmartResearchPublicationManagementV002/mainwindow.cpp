#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QStyle>



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

