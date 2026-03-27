#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ocrscanner.h"
#include "session.h"  // <--- INDISPENSABLE pour lire le rôle
#include <QGraphicsDropShadowEffect>
#include <QDir> // Ajoutez ceci en haut du fichier si absent
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
#include "session.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtSql/QSqlQuery>
#include <QClipboard>

#include <QMouseEvent>
#include "publication.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <QHeaderView>

#include <QLayout>

#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>



#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>





#include "mailsender.h"
#include "currencyconverter.h"
#include <QInputDialog>
#include <QRegularExpression>
#include <QSettings>
#include <QFile>







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
// (makeQrLabs supprimé : la colonne QRLABS n'existe pas dans la table)


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    // On installe le filtre sur le champ de localisation
    ui->setupUi(this);
    ui->textChatPub->setStyleSheet("background-color: white; color: black;");
    connect(ui->btnEnvoyerQuestionPub, &QPushButton::clicked,
            this, &MainWindow::on_btnEnvoyerQuestionPub_clicked);
    connect(ui->btnRetourChatbotPub, &QPushButton::clicked,
            this, &MainWindow::on_btnRetourChatbotPub_clicked);

    if (!ui->statsWidgetPub->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->statsWidgetPub);
        ui->statsWidgetPub->setLayout(layout);
    }
    // On active la détection d'événements sur le champ aff2
    ui->aff2->installEventFilter(this);

    // Optionnel : verrouiller les champs dès le démarrage
    verrouillerChampsAffichage();
    // === STATISTIQUES LABORATOIRES ===
    connect(ui->btnVoirStatistiquesPub_2, &QPushButton::clicked,
            this, &MainWindow::showLabsPaymentStats);

    //employee

    ui->lineCINAdd->setInputMask("99999999");
    ui->lineCIN_emp->setInputMask("99999999");

    // --- CONTROLE SALAIRE (Nombres décimaux uniquement) ---
    // Autorise les nombres de 0 à 999,999.99
    QDoubleValidator *salaryValidator = new QDoubleValidator(0.0, 999999.0, 2, this);
    salaryValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineSalaireAdd->setValidator(salaryValidator);
    ui->lineSalaireEmp->setValidator(salaryValidator);

    // --- CONTROLE NOM / PRENOM (Lettres uniquement) ---
    QRegularExpression nameRegex("^[a-zA-ZáàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ ]*$");
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->lineNomAdd->setValidator(nameValidator);
    ui->linePrenomAdd->setValidator(nameValidator);
    ui->lineNomEmp->setValidator(nameValidator);
    ui->linePrenomEmp->setValidator(nameValidator);
    // Force la connexion si l'auto-connect échoue



    //pointage


    model = new QSqlQueryModel(this);

    // 3. La requête avec TES colonnes exactes
    QString queryStr = "SELECT CIN, NOM, PRENOM, USERNAME, DATE_POINTAGE, HEURE_ARRIVEE, HEURE_DEPART, STATUT_JOURNALIER FROM EMPLOYES";

    model->setQuery(queryStr);

    // 4. Vérification d'erreur (Indispensable pour Oracle)
    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur Oracle", "Détail : " + model->lastError().text());
    } else {
        // 5. Liaison avec l'interface
        ui->tableView->setModel(model);

        // 6. Design du tableau
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    }

    // 7. Connexion du scanner (Vérifie que l'objet s'appelle bien input_badge)
    connect(ui->input_badge, &QLineEdit::returnPressed, this, &MainWindow::simulerPointage);





    // --- STYLE DU TABLEAU (Géré par le QSS global) ---
    ui->tableView->setStyleSheet("");

    // --- OPTIONS D'AFFICHAGE ---
    ui->tableView->setAlternatingRowColors(true); // Active les couleurs alternées
    ui->tableView->verticalHeader()->setVisible(false); // Cache la colonne des numéros (1, 2, 3...)
    ui->tableView->setFrameShape(QFrame::NoFrame); // Enlève le cadre lourd
    ui->tableView->setShowGrid(false); // Plus moderne sans les lignes de grille
    //pointage

    //employee

    // --- Configuration des Tables ---
    ui->TableEmp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableEmp->setSelectionMode(QAbstractItemView::SingleSelection);

    setupTable(ui->tablePublication);
    setupTable(ui->TableEmp);
    setupTable(ui->TableCongeEmp);
    setupTable(ui->TableFormations_Emp);
    setupTable(ui->TableInventory);
    setupTable(ui->TableFinance);
    setupTable(ui->TableLabs_2);
    setupTable(ui->tableProjets);

    // --- Initialisation des Modules ---
    initFinanceUi();
    initPublicationUi();
    loadPublications();
    initLabsUi();
    initInventoryUi();
    loadEmployees();

    // --- Connexions Signaux/Slots ---
    connect(ui->lineSearchEmp, &QLineEdit::textChanged, this, &MainWindow::filterEmployees);
    connect(ui->btnTrier_emp, &QPushButton::clicked, this, &MainWindow::sortByEmbaucheDate);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWindow::updateTopTitle);

    // --- Style Table Publication ---
    ui->tablePublication->setShowGrid(true);
    ui->tablePublication->setGridStyle(Qt::SolidLine);
    auto header = ui->tablePublication->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setDefaultAlignment(Qt::AlignCenter);
    ui->tablePublication->verticalHeader()->setVisible(false);
    ui->tablePublication->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePublication->setSortingEnabled(true);

    // --- Design & Branding ---
    updateTopTitle(ui->stackedWidget->currentIndex());
    ui->lblBrand->setText(R"(<span style="color:#0B1220; font-weight:900;">Smart</span><span style="color:#1F8E95; font-weight:900;">ResearchLab</span>)");
    ui->lblBrand->setTextFormat(Qt::RichText);

    // --- Configuration des Boutons Sidebar ---
    QList<QPushButton*> navButtons = {
        ui->btnEmployee, ui->btnInventaire, ui->btnPublication,
        ui->btnFinance, ui->btnLaboratoires, ui->btnProjets
    };

    for(auto btn : navButtons) {
        btn->setCheckable(true);
        btn->setFocusPolicy(Qt::NoFocus);
    }
    ui->btnDeconnecter->setFocusPolicy(Qt::NoFocus);

    applyModernStyle();

    // --- Navigation Sidebar ---
    connect(ui->btnEmployee,     &QPushButton::clicked, this, &MainWindow::goEmployee);
    connect(ui->btnInventaire,    &QPushButton::clicked, this, &MainWindow::goInventaire);
    connect(ui->btnPublication,   &QPushButton::clicked, this, &MainWindow::goPublication);
    connect(ui->btnFinance,      &QPushButton::clicked, this, &MainWindow::goFinance);
    connect(ui->btnLaboratoires,  &QPushButton::clicked, this, &MainWindow::goLaboratoires);
    connect(ui->btnProjets,       &QPushButton::clicked, this, &MainWindow::goProjets);
    connect(ui->btnDeconnecter,   &QPushButton::clicked, this, &MainWindow::onDeconnecter);
    connect(ui->btnThemeToggle,   &QPushButton::clicked, this, &MainWindow::toggleTheme);

    // --- Effets Visuels (Ombres) ---
    auto shadowSidebar = new QGraphicsDropShadowEffect(this);
    shadowSidebar->setBlurRadius(22);
    shadowSidebar->setOffset(0, 6);
    shadowSidebar->setColor(QColor(0, 0, 0, 60));
    ui->sidebarFrame->setGraphicsEffect(shadowSidebar);

    // NOTE: Ne pas appliquer QGraphicsEffect sur stackedWidget —
    // cela casse la réception des clics sur tous les boutons enfants.

    // ==========================================
    //    GESTION DES RÔLES (Session)
    // ==========================================
    configurerPermissions();

    // Finance : connexions explicites (slots déclarés en protected:, pas private slots:)
    connect(ui->BtnAdd,                  &QPushButton::clicked, this, &MainWindow::on_BtnAdd_clicked);
    connect(ui->BtnEdit,                 &QPushButton::clicked, this, &MainWindow::on_BtnEdit_clicked);
    connect(ui->BtnDelete,               &QPushButton::clicked, this, &MainWindow::on_BtnDelete_clicked);
    connect(ui->BtnApply,                &QPushButton::clicked, this, &MainWindow::on_BtnApply_clicked);
    connect(ui->BtnReset,                &QPushButton::clicked, this, &MainWindow::on_BtnReset_clicked);
    connect(ui->BtnExport,               &QPushButton::clicked, this, &MainWindow::on_BtnExport_clicked);
    connect(ui->BtnPopupSaveFinance,     &QPushButton::clicked, this, &MainWindow::on_BtnPopupSaveFinance_clicked);
    connect(ui->BtnPopupCancelFinance,   &QPushButton::clicked, this, &MainWindow::on_BtnPopupCancelFinance_clicked);
    connect(ui->BtnPopupSaveFinance_2,   &QPushButton::clicked, this, &MainWindow::on_BtnPopupSaveFinance_2_clicked);
    connect(ui->BtnPopupCancelFinance_2, &QPushButton::clicked, this, &MainWindow::on_BtnPopupCancelFinance_2_clicked);
    connect(ui->BtnAdd_4,                &QPushButton::clicked, this, &MainWindow::on_BtnAdd_4_clicked);
    connect(ui->BtnConvertCurrency,      &QPushButton::clicked, this, &MainWindow::openCurrencyConverter);
    connect(ui->BtnConvertCurrency_2,    &QPushButton::clicked, this, [this](){
        CurrencyConverterDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted && dlg.convertedAmountDT() > 0.0)
            ui->FormAmount_2->setText(QString::number(dlg.convertedAmountDT(), 'f', 3));
    });
    connect(ui->BtnOcrReceipt,           &QPushButton::clicked, this, &MainWindow::on_BtnOcrReceipt_clicked);

    connect(ui->BtnExportLabsDirect, &QPushButton::clicked, this, &MainWindow::on_BtnExportLabsDirect_clicked);
    connect(ui->btn_reset, &QPushButton::clicked,
            this, &MainWindow::on_btn_reset_clicked);
    connect(ui->pointage, &QPushButton::clicked,
            this, &MainWindow::on_pointage_clicked);
    connect(ui->btn_ret, &QPushButton::clicked,
            this, &MainWindow::on_btn_ret_clicked);
}




void MainWindow::on_btnStat_emp_clicked()
{
    QStringList categories;
    QList<double> valeurs;

    // 2. RÉCUPÉRATION DES DONNÉES (Ajusté selon ta photo SQL Developer)
    // J'utilise NVL pour transformer les cases vides (NULL) en 0
    QSqlQuery query("SELECT NOM, NVL(NB_ABSENCES, 0) FROM EMPLOYES ORDER BY NB_ABSENCES DESC");

    bool hasData = false;
    while (query.next()) {
        hasData = true;
        QString nom = query.value(0).toString();
        int nbAbsences = query.value(1).toInt();
        double taux = (static_cast<double>(nbAbsences) / 22.0) * 100.0;
        valeurs    << taux;
        categories << nom;
    }

    if (!hasData) {
        QMessageBox::warning(this, "Stats", "Aucune donnée d'absence trouvée dans la base !");
        return;
    }

    // 3. Création de la série
    QBarSet *set = new QBarSet("Taux d'absentéisme (%)");
    for (double v : std::as_const(valeurs)) *set << v;
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Optionnel : Afficher la valeur au-dessus de chaque barre
    series->setLabelsVisible(true);
    series->setLabelsFormat("@value%");

    // 4. Configuration du Graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Analyse de l'Absentéisme par Employé");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 5. Axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Taux d'absentéisme (%)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 6. Affichage
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800, 500);
    chartView->setWindowTitle("Statistiques RH - Vortex");
    chartView->show();
}
void MainWindow::simulerPointage() {
    QString cinSaisi = ui->input_badge->text().trimmed();
    ui->input_badge->clear();
    if (cinSaisi.isEmpty()) return;

    QString dateAujourdhui = QDate::currentDate().toString("yyyy-MM-dd");
    QSqlQuery query;

    // 1. ON VÉRIFIE SI L'EMPLOYÉ A DÉJÀ POINTÉ AUJOURD'HUI
    query.prepare("SELECT HEURE_ARRIVEE, HEURE_DEPART, PRENOM FROM EMPLOYES "
                  "WHERE CIN = :cin AND DATE_POINTAGE = TO_DATE(:d, 'YYYY-MM-DD')");
    query.bindValue(":cin", cinSaisi);
    query.bindValue(":d", dateAujourdhui);

    if (query.exec() && query.next()) {
        // --- L'EMPLOYÉ EST DÉJÀ DANS LA TABLE POUR AUJOURD'HUI ---
        QString hArrivee = query.value("HEURE_ARRIVEE").toString();
        QString hDepart = query.value("HEURE_DEPART").toString();

        if (!hArrivee.isEmpty() && hDepart.isEmpty()) {
            // Il a une arrivée mais pas de départ -> On enregistre le DÉPART
            QSqlQuery upd;
            upd.prepare("UPDATE EMPLOYES SET HEURE_DEPART = :h "
                        "WHERE CIN = :cin AND DATE_POINTAGE = TO_DATE(:d, 'YYYY-MM-DD')");
            upd.bindValue(":h", QTime::currentTime().toString("hh:mm"));
            upd.bindValue(":cin", cinSaisi);
            upd.bindValue(":d", dateAujourdhui);

            if(upd.exec()) {
                ui->label_feedback->setText("👋 DÉPART ENREGISTRÉ : " + query.value("PRENOM").toString());
                ui->label_feedback->setStyleSheet("color: blue; font-weight: bold;");
            }
        } else {
            ui->label_feedback->setText("⚠️ DÉJÀ POINTÉ POUR AUJOURD'HUI");
            ui->label_feedback->setStyleSheet("color: orange; font-weight: bold;");
        }

    } else {
        // --- PREMIER PASSAGE DE LA JOURNÉE (ARRIVÉE) ---
        // On vérifie d'abord que le CIN existe dans la base globale
        QSqlQuery checkExist;
        checkExist.prepare("SELECT PRENOM FROM EMPLOYES WHERE CIN = :cin");
        checkExist.bindValue(":cin", cinSaisi);

        if (checkExist.exec() && checkExist.next()) {
            QSqlQuery ins;
            ins.prepare("UPDATE EMPLOYES SET DATE_POINTAGE = TO_DATE(:d, 'YYYY-MM-DD'), "
                        "HEURE_ARRIVEE = :h, STATUT_JOURNALIER = 'Présent' "
                        "WHERE CIN = :cin");
            ins.bindValue(":d", dateAujourdhui);
            ins.bindValue(":h", QTime::currentTime().toString("hh:mm"));
            ins.bindValue(":cin", cinSaisi);

            if (ins.exec()) {
                ui->label_feedback->setText("✅ ARRIVÉE ENREGISTRÉE : " + checkExist.value("PRENOM").toString());
                ui->label_feedback->setStyleSheet("color: green; font-weight: bold;");
            }
        } else {
            ui->label_feedback->setText("❌ CIN INCONNU");
            ui->label_feedback->setStyleSheet("color: red; font-weight: bold;");
        }
    }

    // MISE À JOUR DU TABLEAU VISUEL
    model->setQuery("SELECT CIN, NOM, PRENOM, USERNAME, DATE_POINTAGE, HEURE_ARRIVEE, HEURE_DEPART, STATUT_JOURNALIER FROM EMPLOYES");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->aff2 && event->type() == QEvent::MouseButtonDblClick) {
        QClipboard *clipboard = QApplication::clipboard();
        QString texte = clipboard->text();

        if (!texte.isEmpty()) {
            ui->aff2->setReadOnly(false);
            ui->aff2->setText(texte);
            ui->aff2->setReadOnly(true);
        }
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_btn_exportt_clicked() {
    // 1. Récupérer la date du jour et la formater (ex: 25_03_2026)
    QString dateStr = QDate::currentDate().toString("dd_MM_yyyy");

    // 2. Proposer le nom de fichier avec la date par défaut
    QString defaultName = QString("Pointage_%1.csv").arg(dateStr);

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter Pointage", defaultName, "Excel (*.csv)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setGenerateByteOrderMark(true);

        // Titres des colonnes
        for (int i = 0; i < model->columnCount(); i++) {
            out << model->headerData(i, Qt::Horizontal).toString() << (i == model->columnCount()-1 ? "" : ";");
        }
        out << "\n";

        // Données des lignes
        for (int r = 0; r < model->rowCount(); r++) {
            for (int c = 0; c < model->columnCount(); c++) {
                out << model->index(r, c).data().toString() << (c == model->columnCount()-1 ? "" : ";");
            }
            out << "\n";
        }
        file.close();
        QMessageBox::information(this, "Succès", "Fichier Excel généré !");
    }
}
void MainWindow::on_btn_reset_clicked() {
    // 1. Demander confirmation
    auto reply = QMessageBox::question(this, "Clôture de journée",
                                       "Voulez-vous comptabiliser les absences et préparer la nouvelle journée ?",
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;

        // --- ÉTAPE A : INCRÉMENTATION ---
        // On ajoute +1 à la colonne NB_ABSENCES pour tous ceux qui sont marqués 'Absent'
        // IMPORTANT : Vérifie que ta colonne s'appelle bien NB_ABSENCES dans ta table EMPLOYES
        bool okInc = query.exec("UPDATE EMPLOYES SET NB_ABSENCES = NVL(NB_ABSENCES, 0) + 1 "
                                "WHERE STATUT_JOURNALIER = 'Absent'");

        if (!okInc) {
            QMessageBox::critical(this, "Erreur", "Échec de la comptabilisation : " + query.lastError().text());
            return; // On arrête tout si le calcul échoue pour ne pas perdre les données
        }

        // --- ÉTAPE B : RESET DU TABLEAU ---
        // On remet tout à NULL et on remet tout le monde à 'Absent' par défaut pour demain
        if (query.exec("UPDATE EMPLOYES SET DATE_POINTAGE = NULL, HEURE_ARRIVEE = NULL, "
                       "HEURE_DEPART = NULL, STATUT_JOURNALIER = 'Absent'")) {

            // Rafraîchissement du modèle (le tableau que l'on voit à l'écran)
            model->setQuery("SELECT CIN, NOM, PRENOM, USERNAME, DATE_POINTAGE, HEURE_ARRIVEE, HEURE_DEPART, STATUT_JOURNALIER FROM EMPLOYES");

            QMessageBox::information(this, "Succès", "Absences enregistrées et système réinitialisé !");

            // OPTIONNEL : Si ton graphique est ouvert, on le met à jour
            // on_btnStat_emp_clicked();

        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors du reset : " + query.lastError().text());
        }
    }
}
void MainWindow::on_btn_ret_clicked()
{
    ui->stack_emp->setCurrentIndex(0);

}
void MainWindow::on_pointage_clicked()
{
    ui->stack_emp->setCurrentIndex(6);

}


//fct userper




void MainWindow::configurerPermissions() {
    Session& session = Session::instance();
    QString role = session.getRole();

    // --- ÉTAPE 1 : Nettoyage (On cache tout la sidebar) ---
    ui->btnEmployee->hide();
    ui->btnInventaire->hide();
    ui->btnPublication->hide();
    ui->btnFinance->hide();
    ui->btnLaboratoires->hide();
    ui->btnProjets->hide();

    // --- ÉTAPE 2 : Attribution de l'Environnement ---
    if (role == "Admin") {
        // 🔥 ADMIN : accès total
        ui->btnEmployee->show();
        ui->btnInventaire->show();
        ui->btnPublication->show();
        ui->btnFinance->show();
        ui->btnLaboratoires->show();
        ui->btnProjets->show();

        // Page par défaut
        ui->stackedWidget->setCurrentIndex(0);
        setActiveButton(ui->btnEmployee);
    }
    if (role == "RH") {
        // Environnement RH : Gestion du personnel et congés
        ui->btnEmployee->show();
        ui->stackedWidget->setCurrentIndex(0); // Index de la page Employés
        setActiveButton(ui->btnEmployee);
    }
    else if (role == "Responsable_financier") {
        // Environnement Finance : Salaires et budgets
        ui->btnFinance->show();
        ui->stackedWidget->setCurrentIndex(3); // Index de la page Finance
        setActiveButton(ui->btnFinance);
    }
    else if (role == "Responsable_de_stock") {
        // Environnement Stock : Inventaire et matériel
        ui->btnInventaire->show();
        ui->stackedWidget->setCurrentIndex(1); // Index de la page Inventaire
        setActiveButton(ui->btnInventaire);
    }
    else if (role == "Responsable_Labos") {
        // Environnement Laboratoire
        ui->btnLaboratoires->show();
        ui->stackedWidget->setCurrentIndex(4); // Index de la page Labos
        setActiveButton(ui->btnLaboratoires);
    }
    else if (role == "Chercheur") {
        // Environnement Recherche : Publications seulement
        ui->btnPublication->show();
        ui->stackedWidget->setCurrentIndex(2); // Index Publications
        setActiveButton(ui->btnPublication);
    }
    else if (role == "Directeur_de_projet") {
        // Environnement Management : Projets et Publications
        ui->btnProjets->show();
        ui->btnPublication->show();
        ui->stackedWidget->setCurrentIndex(5); // Index Projets
        setActiveButton(ui->btnProjets);
    }

    // Mise à jour du titre en haut de l'écran
    updateTopTitle(ui->stackedWidget->currentIndex());
}




//fin fct


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::applyModernStyle()
{
    // Lire la préférence depuis QSettings et synchroniser l'état
    QSettings settings("SmartResearchLab", "Theme");
    m_isDarkTheme = settings.value("darkMode", false).toBool();
    updateThemeButton();
    // Le style global a déjà été appliqué dans main.cpp au démarrage
    return;
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

void MainWindow::toggleTheme()
{
    m_isDarkTheme = !m_isDarkTheme;

    // Charger et appliquer le fichier QSS correspondant
    QString themeFile = m_isDarkTheme ? ":/theme/style.qss" : ":/theme/style_light.qss";
    QFile f(themeFile);
    if (f.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(QLatin1String(f.readAll()));
        f.close();
    }

    // Persister la préférence
    QSettings settings("SmartResearchLab", "Theme");
    settings.setValue("darkMode", m_isDarkTheme);

    updateThemeButton();
}

void MainWindow::updateThemeButton()
{
    if (m_isDarkTheme) {
        ui->btnThemeToggle->setText(QString::fromUtf8("\xe2\x98\x80\xef\xb8\x8f  Mode Jour"));
        ui->btnThemeToggle->setToolTip("Passer en th\u00E8me clair");
        // En mode nuit (fond bleu tr\u00e8s fonc\u00e9) : l'id\u00e9al est un texte blanc/clair pour le mot "Smart"
        ui->lblBrand->setText(R"(<span style="color:#e2e8f0; font-weight:900;">Smart</span><span style="color:#38bdf8; font-weight:900;">ResearchLab</span>)");
    } else {
        ui->btnThemeToggle->setText(QString::fromUtf8("\xf0\x9f\x8c\x99  Mode Nuit"));
        ui->btnThemeToggle->setToolTip("Passer en th\u00E8me sombre");
        // En mode jour (fond blanc) : le mot "Smart" doit \u00eatre noir/fonc\u00e9
        ui->lblBrand->setText(R"(<span style="color:#1e293b; font-weight:900;">Smart</span><span style="color:#1F8E95; font-weight:900;">ResearchLab</span>)");
    }
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
        emit logoutRequested();
        this->close();
    }
}

void MainWindow::updateTopTitle(int index)
{
    QString pageName;
    switch(index)
    {
    case 0: pageName = "Employee"; break;
    case 1: pageName = "Inventaire"; break;
    case 2: pageName = "Publication"; break;
    case 3: pageName = "Finance"; break;
    case 4: pageName = "Laboratoires"; break;
    case 5: pageName = "Projets"; break;
    }

    QString greeting = (QTime::currentTime().hour() < 18) ? "Bonjour" : "Bonsoir";
    QString userName = Session::instance().getNom().split(" ").last(); // Extrait le prénom
    if (userName.isEmpty()) userName = "Utilisateur";

    // Augmenter dynamiquement la largeur du label pour ne pas couper le texte
    ui->lblPageTitle->setMinimumWidth(400);
    // On déplace le label pour qu'il ait assez d'espace même s'il est aligné à droite
    ui->lblPageTitle->setGeometry(QRect(180, 10, 400, 31));

    ui->lblPageTitle->setText(pageName + QString::fromUtf8("  |  %1 %2")
                              .arg(greeting, userName));
}

/* ===================== SLOTS DE NAVIGATION SIMPLES ===================== */

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


/* ===================== SLOTS DE LABS ===================== */

// ── Helper interne : cherche val dans combo de façon insensible à la casse ──
static void setComboValue(QComboBox *cb, const QString &val)
{
    int idx = cb->findText(val, Qt::MatchFixedString | Qt::MatchCaseSensitive);
    if (idx < 0) idx = cb->findText(val, Qt::MatchFixedString);
    cb->setCurrentIndex(idx >= 0 ? idx : 0);
}

// ── Export direct vers C:/GestionLabs/ ──
// ── Export direct des données de la page d'affichage vers un fichier TXT ──
// ── Export direct des données de la page d'affichage vers un fichier TXT ──
void MainWindow::on_BtnExportLabsDirect_clicked()
{
    // Vérifier que les champs de la page d'affichage contiennent des données
    if (ui->aff1->text().trimmed().isEmpty() &&
        ui->aff5->text().trimmed().isEmpty() &&
        ui->aff2->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Exportation",
                             "Aucune donnée de laboratoire à exporter.\n"
                             "Veuillez d'abord sélectionner et afficher un laboratoire.");
        return;
    }

    // Récupérer le nom du laboratoire pour nommer le fichier
    QString nomLabo = ui->aff1->text().trimmed();
    if (nomLabo.isEmpty()) nomLabo = "Laboratoire_Inconnu";

    // Nettoyer le nom du laboratoire pour l'utiliser dans le nom de fichier
    nomLabo = nomLabo.replace(QRegularExpression("[^a-zA-Z0-9_-]"), "_");
    if (nomLabo.length() > 30) nomLabo = nomLabo.left(30);

    // Créer le nom du fichier avec date et heure
    const QString folderPath = "C:/GestionLabs";
    QDir dir(folderPath);
    if (!dir.exists()) dir.mkpath(".");

    const QString dateTimeStr = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    const QString fileName = folderPath + "/" + nomLabo + "_" + dateTimeStr + ".txt";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur d'exportation",
                              QString("Impossible de créer le fichier :\n%1\n\n"
                                      "Vérifiez les droits d'écriture sur le dossier C:/GestionLabs")
                                  .arg(fileName));
        return;
    }

    QTextStream out(&file);

    // ========== EN-TÊTE ==========
    out << "=====================================================================\n";
    out << "|                                                                   |\n";
    out << "|           FICHE D'INFORMATION - LABORATOIRE                       |\n";
    out << "|                                                                   |\n";
    out << "=====================================================================\n\n";

    out << "Date d'exportation : " << QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss") << "\n\n";

    // ========== INFORMATIONS GÉNÉRALES ==========
    out << "┌─────────────────────────────────────────────────────────────────┐\n";
    out << "│                    INFORMATIONS GÉNÉRALES                       │\n";
    out << "├─────────────────────────────────────────────────────────────────┤\n";

    QString ligne1 = QString("│ %1 : %2").arg("Nom du Laboratoire", -40).arg(ui->aff1->text().trimmed());
    out << ligne1.leftJustified(67, ' ') << "│\n";

    QString ligne2 = QString("│ %1 : %2").arg("Responsable", -40).arg(ui->aff5->text().trimmed());
    out << ligne2.leftJustified(67, ' ') << "│\n";

    QString ligne3 = QString("│ %1 : %2").arg("Numéro de téléphone", -40).arg(ui->aff6->text().trimmed());
    out << ligne3.leftJustified(67, ' ') << "│\n";

    QString ligne4 = QString("│ %1 : %2").arg("Localisation", -40).arg(ui->aff2->text().trimmed());
    out << ligne4.leftJustified(67, ' ') << "│\n";

    out << "└─────────────────────────────────────────────────────────────────┘\n\n";

    // ========== CARACTÉRISTIQUES TECHNIQUES ==========
    out << "┌─────────────────────────────────────────────────────────────────┐\n";
    out << "│                 CARACTÉRISTIQUES TECHNIQUES                     │\n";
    out << "├─────────────────────────────────────────────────────────────────┤\n";

    QString ligne5 = QString("│ %1 : %2").arg("Spécialité", -40).arg(ui->aff3->currentText());
    out << ligne5.leftJustified(67, ' ') << "│\n";

    QString ligne6 = QString("│ %1 : %2").arg("Disponibilité", -40).arg(ui->aff7->currentText());
    out << ligne6.leftJustified(67, ' ') << "│\n";

    QString ligne7 = QString("│ %1 : %2").arg("Résultat actuel", -40).arg(ui->aff3_2->currentText());
    out << ligne7.leftJustified(67, ' ') << "│\n";

    QString ligne8 = QString("│ %1 : %2").arg("Statut de paiement", -40).arg(ui->aff7_2->currentText());
    out << ligne8.leftJustified(67, ' ') << "│\n";

    out << "└─────────────────────────────────────────────────────────────────┘\n\n";

    // ========== INFORMATIONS COMPLÉMENTAIRES ==========
    out << "┌─────────────────────────────────────────────────────────────────┐\n";
    out << "│                   INFORMATIONS COMPLÉMENTAIRES                  │"
           "|\n";
    out << "├─────────────────────────────────────────────────────────────────┤\n";
    out << "│                                                                 │\n";

    // Vérifier le statut de disponibilité pour un message personnalisé
    QString disponibilite = ui->aff7->currentText().toLower();
    if (disponibilite.contains("disponible")) {
        out << "│ ✔ Le laboratoire est actuellement DISPONIBLE pour toute demande.    │\n";
    } else if (disponibilite.contains("occupe")) {
        out << "│ ⚠ Le laboratoire est actuellement OCCUPÉ.                            │\n";
    }

    // Vérifier le statut de paiement
    QString paiement = ui->aff7_2->currentText().toLower();
    if (paiement.contains("payer")) {
        out << "│ ✓ Paiement effectué - Services opérationnels.                        │\n";
    } else if (paiement.contains("non payer")) {
        out << "│ ✗ Paiement en attente - Veuillez régulariser la situation.           │\n";
    }

    out << "│                                                                 │\n";
    out << "└─────────────────────────────────────────────────────────────────┘\n\n";

    // ========== FOOTER ==========
    out << "=====================================================================\n";

    QString footer1 = QString("| %1").arg("Document généré automatiquement par SmartResearchLab");
    out << footer1.leftJustified(69, ' ') << "|\n";

    QString footer2 = QString("| %1").arg("En cas de question, veuillez contacter l'administrateur");
    out << footer2.leftJustified(69, ' ') << "|\n";

    out << "=====================================================================\n";

    file.close();

    // ========== MESSAGE DE SUCCÈS ==========
    QMessageBox::information(this, "Exportation Réussie",
                             QString("Les données du laboratoire ont été exportées avec succès !\n\n"
                                     "Fichier : %1\n\n"
                                     "Le fichier a été ouvert dans le bloc-notes.")
                                 .arg(fileName));

    // Ouvrir le fichier avec l'application par défaut (Bloc-notes sur Windows)
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void MainWindow::on_btnOpenGoogleMaps_clicked()
{
    // Récupérer la localisation depuis le champ aff2
    QString location = ui->aff2->text().trimmed();

    if (location.isEmpty()) {
        QMessageBox::warning(this, "Localisation vide",
                             "Aucune localisation n'est disponible pour ce laboratoire.\n"
                             "Veuillez d'abord sélectionner et afficher un laboratoire.");
        return;
    }

    // Construire l'URL Google Maps
    QString encodedLocation = QUrl::toPercentEncoding(location);
    QString googleMapsUrl = QString("https://www.google.com/maps/search/%1").arg(encodedLocation);

    // Ouvrir l'URL
    bool opened = QDesktopServices::openUrl(QUrl(googleMapsUrl));

    if (!opened) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir Google Maps.");
    }
}

void MainWindow::on_btnVoirStatistiquesPub_2_clicked()
{
    showLabsPaymentStats();
}

// ── Statistiques paiement ──
void MainWindow::showLabsPaymentStats()
{
    // Valeurs exactes en BD : 'payer' / 'non payer' (minuscules)
    QSqlQuery query(R"(
        SELECT NOMLABO,
               SUM(CASE WHEN LOWER(PAIEMENT) = 'payer'     THEN 1 ELSE 0 END) AS Paye,
               SUM(CASE WHEN LOWER(PAIEMENT) = 'non payer' THEN 1 ELSE 0 END) AS NonPaye,
               COUNT(*) AS Total
        FROM LABS
        GROUP BY NOMLABO
        ORDER BY NOMLABO
    )");

    QStringList categories;
    QVector<double> payePercent;
    QVector<double> nonPayePercent;
    bool hasData = false;

    while (query.next()) {
        hasData = true;
        const QString nomLabo = query.value(0).toString();
        const int paye        = query.value(1).toInt();
        const int nonPaye     = query.value(2).toInt();
        const int total       = query.value(3).toInt();
        const double pPaye    = total > 0 ? (static_cast<double>(paye)    / total) * 100.0 : 0.0;
        const double pNonPaye = total > 0 ? (static_cast<double>(nonPaye) / total) * 100.0 : 0.0;
        categories     << nomLabo;
        payePercent    << pPaye;
        nonPayePercent << pNonPaye;
    }

    if (!hasData) {
        QMessageBox::warning(this, "Statistiques Laboratoires", "Aucune donnée de paiement trouvée.");
        return;
    }

    QBarSet *setPaye    = new QBarSet("Payé (%)");   setPaye->setColor(QColor(39, 174, 96)); 
    QBarSet *setNonPaye = new QBarSet("Non Payé (%)"); setNonPaye->setColor(QColor(231, 76, 60));

    for (int i = 0; i < payePercent.size(); ++i) {
        *setPaye    << payePercent[i];
        *setNonPaye << nonPayePercent[i];
    }

    QBarSeries *series = new QBarSeries();
    series->append(setPaye);
    series->append(setNonPaye);
    series->setLabelsVisible(true);
    series->setLabelsFormat("@value %");

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage de Paiement par Laboratoire");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Pourcentage (%)");
    axisY->setLabelFormat("%.1f%%");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(950, 620);
    chartView->setWindowTitle("Statistiques Paiement (%) - Laboratoires");
    chartView->setAttribute(Qt::WA_DeleteOnClose);
    chartView->show();
}

// ── Navigation ──
void MainWindow::on_btnAjouterPub_2_clicked() { ui->stacked_L->setCurrentIndex(2); }
void MainWindow::on_BtnPopupCancelLabs_5_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_3_clicked() { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_2_clicked()        { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_3_clicked()        { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_9_clicked()        { ui->stacked_L->setCurrentIndex(0); }
void MainWindow::on_retour_stat_8_clicked()        { ui->stacked_L->setCurrentIndex(0); }

// ── Maps ──
void MainWindow::on_btnPasteLocation_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    const QString coordinates = clipboard->text();
    if (!coordinates.isEmpty()) {
        ui->LabLocation_3->setText(coordinates);
        ui->LabLocation_5->setText(coordinates);
    }
}
void MainWindow::on_btnAjouterPub_4_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.google.com/maps/@36.8065,10.1815,12z"));
    QMessageBox::information(this, "Instructions Localisation",
                             "1. Cherchez le lieu sur Google Maps.\n"
                             "2. Faites un clic-droit sur le point exact.\n"
                             "3. Cliquez sur les coordonnées pour les copier.\n"
                             "4. Revenez ici et collez (Ctrl+V) dans le champ Localisation.");
}
void MainWindow::on_btnAjouterPub_5_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.google.com/maps/@36.8065,10.1815,12z"));
    QMessageBox::information(this, "Instructions Localisation",
                             "1. Cherchez le lieu sur Google Maps.\n"
                             "2. Faites un clic-droit sur le point exact.\n"
                             "3. Cliquez sur les coordonnées pour les copier.\n"
                             "4. Revenez ici et collez (Ctrl+V) dans le champ Localisation.");
}
void MainWindow::on_btnmapl_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.google.com/maps/@36.8065,10.1815,12z"));
    QMessageBox::information(this, "Instructions Localisation",
                             "1. Cherchez le lieu sur Google Maps.\n"
                             "2. Faites un clic-droit sur le point exact.\n"
                             "3. Cliquez sur les coordonnées pour les copier.\n"
                             "4. Revenez ici et collez (Ctrl+V) dans le champ Localisation.");
}
// Inventory - Navigation
// ====================== AJOUT ======================
void MainWindow::on_BtnInventoryAdd_clicked()
{
    // Réinitialiser le formulaire d'ajout
    ui->aff1->clear();
    ui->aff2->clear();
    ui->aff3->setCurrentIndex(0);   // spécialité
    ui->aff7->setCurrentIndex(0);   // disponibilité
    ui->aff3_2->setCurrentIndex(0); // résultat
    ui->aff7_2->setCurrentIndex(0); // paiement

    ui->stacked_I->setCurrentIndex(1); // Page d'ajout
}
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

// ==================== FINANCE CRUD ====================

void MainWindow::initFinanceUi()
{
    // --- ComboBox (AJOUT) : valeurs DB via currentData() ---
    ui->FormType->clear();
    ui->FormType->addItem("Dépense", "Depense");   // affichage accent, valeur DB sans accent
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
    ui->FormType_2->addItem("Dépense", "Depense");  // affichage accent, valeur DB sans accent
    ui->FormType_2->addItem("Revenu",  "Revenu");

    ui->FormPayMode_2->clear();
    ui->FormPayMode_2->addItem("Espèces",        "especes");
    ui->FormPayMode_2->addItem("Chèque",         "cheque");
    ui->FormPayMode_2->addItem("Virement",       "virement");
    ui->FormPayMode_2->addItem("Carte bancaire", "carte_bancaire");
    ui->FormPayMode_2->addItem("Facture",        "facture");
    ui->FormPayMode_2->addItem("Remboursement",  "remboursement");

    setupTableFinance();

    ui->DateFrom->setDate(QDate(2000, 1, 1));
    ui->DateTo->setDate(QDate::currentDate());

    // Utilise désormais le style global (QSS) défini dans style_light.qss / style.qss
    ui->BtnConvertCurrency->setStyleSheet("");
    ui->BtnConvertCurrency_2->setStyleSheet("");

    ui->BtnOcrReceipt->setStyleSheet("");

    // ── LblOcrHint : badge hint stylé ────────────────────────────────────────
    ui->LblOcrHint->setStyleSheet(
        "QLabel {"
        "  color: #4a9fa5;"
        "  font-size: 9.5px;"
        "  font-style: italic;"
        "  font-weight: 500;"
        "  background: rgba(31,142,149,0.07);"
        "  border-radius: 6px;"
        "  padding: 4px 10px;"
        "}");

    ui->stacked_F->setCurrentIndex(0);
    loadFinance();

    // Graphique stats : se met à jour quand le combo change
    connect(ui->comboBox_3, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int){ updateFinanceStats(); });

    // --- Connexions pour mise à jour automatique de la liste ---
    connect(ui->CbType, &QComboBox::currentIndexChanged, this, &MainWindow::on_BtnApply_clicked);
    connect(ui->EdSearch, &QLineEdit::textChanged, this, &MainWindow::on_BtnApply_clicked);
    connect(ui->DateFrom, &QDateEdit::dateChanged, this, &MainWindow::on_BtnApply_clicked);
    connect(ui->DateTo, &QDateEdit::dateChanged, this, &MainWindow::on_BtnApply_clicked);
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
    ui->TableFinance->setSortingEnabled(true);
    ui->TableFinance->setHorizontalHeaderLabels({
        "Code", "Type", "Montant", "Catégorie",
        "Description", "Date", "Mode", "Création"
    });

    // Petite phrase pour guider l'utilisateur
    QString tip = "Transactions <small><i>(Astuce : Cliquez sur les en-têtes pour trier)</i></small>";
    ui->TableTitle->setText(tip);
}

void MainWindow::loadFinance()
{
    ui->TableFinance->setSortingEnabled(false);
    ui->TableFinance->setRowCount(0);

    QVector<Finance::Row> rows;
    QString err;
    if (!Finance::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    int row = 0;
    for (const auto& r : std::as_const(rows)) {
        ui->TableFinance->insertRow(row);

        auto *itCode = new QTableWidgetItem(r.code);
        itCode->setData(Qt::UserRole, r.id); // ID caché
        ui->TableFinance->setItem(row, 0, itCode);

        // Affichage avec accent ; valeur DB (sans accent) en UserRole pour modifier/PDF
        const QString typeDisplay = (r.type == "Depense") ? "Dépense" : r.type;
        auto *itType = new QTableWidgetItem(typeDisplay);
        itType->setData(Qt::UserRole, r.type); // "Depense" ou "Revenu"
        ui->TableFinance->setItem(row, 1, itType);

        auto *itMontant = new QTableWidgetItem();
        itMontant->setData(Qt::DisplayRole, r.montant.toDouble()); // tri numérique correct
        ui->TableFinance->setItem(row, 2, itMontant);

        ui->TableFinance->setItem(row, 3, new QTableWidgetItem(r.categorie));
        ui->TableFinance->setItem(row, 4, new QTableWidgetItem(r.description));
        ui->TableFinance->setItem(row, 5, new QTableWidgetItem(r.dateTransaction));
        ui->TableFinance->setItem(row, 6, new QTableWidgetItem(r.modePaiement));
        ui->TableFinance->setItem(row, 7, new QTableWidgetItem(r.dateCreation));

        row++;
    }
    ui->TableFinance->setSortingEnabled(true);
}

void MainWindow::updateFinanceStats()
{
    const int idx = ui->comboBox_3->currentIndex();

    // Récupérer ou créer le QChartView dans la page statsF
    QChartView *cv = ui->statsF->findChild<QChartView*>("finChartView");
    if (!cv) {
        cv = new QChartView(ui->statsF);
        cv->setObjectName("finChartView");
        cv->setGeometry(ui->stat_pub_3->geometry());
        cv->setRenderHint(QPainter::Antialiasing);
        cv->show();
        ui->stat_pub_3->hide();
    }

    // ── Palette multicolore pour les barres ─────────────────────────────
    static const QVector<QColor> palette = {
        QColor(31, 142, 149), QColor(39, 174, 96), QColor(230, 126, 34),
        QColor(142, 68, 173), QColor(41, 128, 185), QColor(192, 57, 43),
        QColor(22, 160, 133), QColor(211, 84, 0), QColor(44, 62, 80),
        QColor(243, 156, 18)
    };

    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setBackgroundBrush(m_isDarkTheme ? QColor(15, 23, 42) : QColor(242, 235, 228));
    chart->setTitleFont(QFont("Segoe UI", 13, QFont::Bold));
    chart->setTitleBrush(m_isDarkTheme ? QColor(241, 245, 249) : QColor(45, 55, 72));

    if (idx == 0) {
        // ════════════════════════════════════════════════════════════════
        //  DONUT : Dépenses vs Revenus
        // ════════════════════════════════════════════════════════════════
        double totalDep = 0, totalRev = 0;
        QSqlQuery q("SELECT TYPETRANSACTION, SUM(MONTANT) FROM FINANCE "
                    "GROUP BY TYPETRANSACTION");
        while (q.next()) {
            const QString t = q.value(0).toString();
            if (t == "Depense") totalDep = q.value(1).toDouble();
            else                totalRev = q.value(1).toDouble();
        }

        const double total = totalRev - totalDep ;

        QPieSeries *pie = new QPieSeries();
        pie->setHoleSize(0.40);

        auto addSlice = [&](const QString& label, double val, const QColor& col) {
            if (val <= 0) return;
            const double pct = (total > 0) ? (val / total * 100.0) : 0;
            QString lbl = QString("%1\n%2 DT\n(%3 %)")
                              .arg(label, QLocale(QLocale::French).toString(val,'f',2), QString::number(pct,'f',1));
            auto *sl = pie->append(lbl, val);
            sl->setColor(col);
            sl->setLabelColor(m_isDarkTheme ? QColor(241, 245, 249) : QColor(45, 55, 72));
            sl->setLabelFont(QFont("Segoe UI", 9, QFont::Bold));
            sl->setLabelVisible(true);
            sl->setLabelPosition(QPieSlice::LabelOutside);
            if (val == qMax(totalDep, totalRev)) sl->setExploded(true);
        };

        addSlice("Dépenses", totalDep, QColor(192, 57, 43));
        addSlice("Revenus",  totalRev, QColor(39, 174, 96));

        if (pie->count() == 0) {
            pie->append("Aucune donnée", 1)->setColor(QColor(189, 195, 199));
        }

        chart->addSeries(pie);
        chart->setTitle(QString("Dépenses vs Revenus   |   Total : %1 DT")
                            .arg(QLocale(QLocale::French).toString(total,'f',2)));
        chart->legend()->setVisible(true);
        chart->legend()->setLabelColor(m_isDarkTheme ? QColor(241, 245, 249) : QColor(45, 55, 72));
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->legend()->setFont(QFont("Segoe UI", 10));

    } else {
        // ════════════════════════════════════════════════════════════════
        //  BARRES multicolores : par catégorie
        // ════════════════════════════════════════════════════════════════
        const QString typeFilter = (idx == 2) ? "Depense" : "Revenu";
        const QString title      = (idx == 2) ? "Dépenses par catégorie"
                                              : "Revenus par catégorie";
        QSqlQuery q;
        q.prepare("SELECT NVL(CATEGORIE,'Sans catégorie'), SUM(MONTANT) "
                  "FROM FINANCE WHERE TYPETRANSACTION=:t "
                  "GROUP BY CATEGORIE ORDER BY SUM(MONTANT) DESC");
        q.bindValue(":t", typeFilter);
        q.exec();

        QStringList cats;
        QList<double> vals;
        while (q.next()) {
            cats << q.value(0).toString();
            vals << q.value(1).toDouble();
        }
        if (cats.isEmpty()) { cats << "Aucune donnée"; vals << 0; }

        // Un seul QBarSet avec toutes les valeurs → N barres alignées sur N catégories
        const QColor barColor = (idx == 2) ? QColor(192, 57, 43) : QColor(39, 174, 96);
        auto *set = new QBarSet("Montant (DT)");
        set->setColor(barColor);
        set->setBorderColor(barColor.darker(120));
        set->setLabelColor(m_isDarkTheme ? QColor(241, 245, 249) : QColor(45, 55, 72));
        set->setLabelFont(QFont("Segoe UI", 8, QFont::Bold));
        for (double v : std::as_const(vals)) *set << v;

        QBarSeries *series = new QBarSeries();
        series->append(set);
        series->setLabelsVisible(true);
        series->setLabelsFormat("@value DT");
        series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

        QBarCategoryAxis *axX = new QBarCategoryAxis();
        axX->append(cats);
        axX->setLabelsColor(m_isDarkTheme ? QColor(148, 163, 184) : QColor(45, 55, 72));
        axX->setLabelsFont(QFont("Segoe UI", 8));
        axX->setGridLineVisible(false);

        QValueAxis *axY = new QValueAxis();
        axY->setLabelsColor(m_isDarkTheme ? QColor(148, 163, 184) : QColor(45, 55, 72));
        axY->setLabelsFont(QFont("Segoe UI", 8));
        axY->setTitleText("Montant (DT)");
        axY->setTitleFont(QFont("Segoe UI", 9, QFont::Bold));
        axY->setTitleBrush(m_isDarkTheme ? QColor(241, 245, 249) : QColor(45, 55, 72));
        axY->setGridLineColor(m_isDarkTheme ? QColor(30, 58, 95) : QColor(226, 232, 240));
        axY->setGridLineVisible(!m_isDarkTheme);

        chart->addSeries(series);
        chart->setTitle(title);
        chart->addAxis(axX, Qt::AlignBottom); series->attachAxis(axX);
        chart->addAxis(axY, Qt::AlignLeft);   series->attachAxis(axY);
        chart->legend()->setVisible(false); // inutile avec 1 seul set
    }

    cv->setChart(chart);
    cv->setBackgroundBrush(m_isDarkTheme ? QColor(15, 23, 42) : QColor(242, 235, 228));
}

void MainWindow::openCurrencyConverter()
{
    CurrencyConverterDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted && dlg.convertedAmountDT() > 0.0) {
        // Injecter le montant converti dans le champ Montant du formulaire
        ui->FormAmount->setText(
            QString::number(dlg.convertedAmountDT(), 'f', 3));
    }
}

void MainWindow::on_BtnOcrReceipt_clicked()
{
    OcrScannerDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;

    const OcrResult &r = dlg.result();

    if (r.hasAmount && r.amount > 0.0)
        ui->FormAmount->setText(QString::number(r.amount, 'f', 2));

    if (r.hasDate && r.date.isValid())
        ui->FormDate->setDate(r.date);

    if (!r.type.isEmpty()) {
        // FormType comboBox items : "Dépense"/"Revenu" — match by data
        for (int i = 0; i < ui->FormType->count(); ++i) {
            if (ui->FormType->itemData(i).toString() == r.type) {
                ui->FormType->setCurrentIndex(i);
                break;
            }
        }
    }

    if (!r.category.isEmpty())
        ui->FormCategory->setText(r.category);

    if (!r.description.isEmpty() && ui->FormDesc->text().isEmpty())
        ui->FormDesc->setText(r.description);
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

    const QString IDEMP = Session::instance().getId();

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

    // TYPE : lire la valeur DB depuis UserRole (ex: "Depense") pour findData
    const QString typeDb = ui->TableFinance->item(r,1)->data(Qt::UserRole).toString();
    int idxType = ui->FormType_2->findData(typeDb);
    ui->FormType_2->setCurrentIndex(qMax(0, idxType));

    // Montant : stocké en DisplayRole (double), on récupère la chaîne formatée
    const double montantVal = ui->TableFinance->item(r,2)->data(Qt::DisplayRole).toDouble();
    ui->FormAmount_2->setText(QString::number(montantVal, 'f', 2));
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

    const double tva      = totalHT * 0.19;
    const double totalTTC = totalHT + tva;

    const QString invoiceNo   = makeInvoiceNumber();
    const QString invoiceDate = QDate::currentDate().toString("dd/MM/yyyy");
    const bool    isDepense   = (row.type == "Depense" || row.type == "Dépense");
    const QString typeLabel   = isDepense ? "DÉPENSE" : "REVENU";

    QString designation = row.categorie.trimmed();
    const QString desc = row.description.trimmed();
    if (!desc.isEmpty() && desc != "(null)") designation += " — " + desc;
    if (designation.isEmpty()) designation = "Transaction interne";

    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(200);

    QPainter p(&pdf);
    if (!p.isActive()) return false;
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    const int W = pdf.width();
    const int H = pdf.height();
    const int M = 100;

    // ── Palette ──────────────────────────────────────────────────────────
    const QColor cDarkTeal (13, 90, 95);
    const QColor cTeal     (31, 142, 149);
    const QColor cLightTeal(232, 248, 248);
    const QColor cAccent   = isDepense ? QColor(192, 57, 43) : QColor(39, 174, 96);
    const QColor cDark     (45, 55, 72);
    const QColor cMid      (113, 128, 150);
    const QColor cLight    (242, 235, 228);
    const QColor cBorder   (226, 232, 240);
    const QColor cWhite    (Qt::white);

    const int tableW = W - 2 * M;
    int y = 0;

    auto sf = [&](int pt, bool bold = false) {
        QFont f("Segoe UI", pt); f.setBold(bold); p.setFont(f);
    };
    auto fillR = [&](const QRect& r, const QColor& c) {
        p.save(); p.setPen(Qt::NoPen); p.setBrush(c); p.drawRect(r); p.restore();
    };
    auto fillRR = [&](const QRect& r, int radius, const QColor& c) {
        p.save(); p.setPen(Qt::NoPen); p.setBrush(c);
        p.drawRoundedRect(r, radius, radius); p.restore();
    };

    // ════════════════════════════════════════════════════════════════════
    //  BANDE HEADER
    // ════════════════════════════════════════════════════════════════════
    const int hdrH = 190;
    fillR(QRect(0, 0, W, hdrH), cDarkTeal);
    // Bande accent verticale gauche
    fillR(QRect(0, 0, 16, hdrH), cAccent);

    // Nom société
    sf(22, true); p.setPen(cWhite);
    p.drawText(QRect(M + 8, 28, W / 2, 52), Qt::AlignLeft | Qt::AlignVCenter, "SmartResearchLab");

    sf(9, false); p.setPen(QColor(180, 230, 232));
    p.drawText(QRect(M + 8, 84, W / 2 + 100, 22), Qt::AlignLeft | Qt::AlignVCenter,
               "Urban Park, Ariana 1080, Tunisie");
    p.drawText(QRect(M + 8, 108, W / 2 + 100, 22), Qt::AlignLeft | Qt::AlignVCenter,
               "+216 XX XXX XXX   ·   finance@smartresearchlab.tn");

    // Titre droite
    sf(30, true); p.setPen(cWhite);
    p.drawText(QRect(W / 2, 20, W / 2 - M - 8, 58), Qt::AlignRight | Qt::AlignVCenter, "FACTURE");
    sf(10, false); p.setPen(QColor(180, 230, 232));
    p.drawText(QRect(W / 2, 80, W / 2 - M - 8, 24), Qt::AlignRight | Qt::AlignVCenter,
               "N°  " + invoiceNo);
    p.drawText(QRect(W / 2, 106, W / 2 - M - 8, 24), Qt::AlignRight | Qt::AlignVCenter,
               "Émise le : " + invoiceDate);

    y = hdrH + 30;

    // ════════════════════════════════════════════════════════════════════
    //  BADGE TYPE
    // ════════════════════════════════════════════════════════════════════
    fillRR(QRect(M, y, 250, 44), 10, cAccent);
    sf(13, true); p.setPen(cWhite);
    p.drawText(QRect(M, y, 250, 44), Qt::AlignCenter, typeLabel);
    y += 44 + 30;

    // ════════════════════════════════════════════════════════════════════
    //  CARDS INFO (Document | Référence)
    // ════════════════════════════════════════════════════════════════════
    const int cardH = 148;
    const int cGap  = 22;
    const int cardW = (tableW - cGap) / 2;

    auto drawCard = [&](int cx, int cy, int cw, int ch,
                        const QString& title,
                        const QStringList& keys,
                        const QStringList& vals)
    {
        fillRR(QRect(cx, cy, cw, ch), 10, cLight);
        p.save(); p.setPen(QPen(cBorder, 1)); p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(QRect(cx, cy, cw, ch), 10, 10); p.restore();

        // Titre card
        fillR(QRect(cx, cy, cw, 38), cTeal);
        // Correction coins bas du titre
        p.fillRect(QRect(cx, cy + 20, cw, 18), cTeal);

        sf(11, true); p.setPen(cWhite);
        p.drawText(QRect(cx + 16, cy, cw - 32, 38), Qt::AlignVCenter | Qt::AlignLeft, title);

        int ry = cy + 46;
        for (int i = 0; i < keys.size() && i < vals.size(); ++i) {
            sf(9, true);  p.setPen(cMid);
            p.drawText(QRect(cx + 16, ry, cw / 2 - 10, 24), Qt::AlignLeft | Qt::AlignVCenter, keys[i]);
            sf(9, false); p.setPen(cDark);
            p.drawText(QRect(cx + cw / 2, ry, cw / 2 - 16, 24), Qt::AlignLeft | Qt::AlignVCenter, vals[i]);
            ry += 28;
        }
    };

    drawCard(M, y, cardW, cardH,
             "DOCUMENT",
             {"Type :", "Usage :", "TVA :"},
             {typeLabel, "Interne – Société", "19 %"});

    drawCard(M + cardW + cGap, y, cardW, cardH,
             "RÉFÉRENCE",
             {"Code :", "Date transaction :", "Mode paiement :"},
             {row.code, row.dateTransaction, row.modePaiement});

    y += cardH + 36;

    // ════════════════════════════════════════════════════════════════════
    //  TABLEAU ARTICLES
    // ════════════════════════════════════════════════════════════════════
    const int colDesc = int(tableW * 0.55);
    const int colQty  = int(tableW * 0.10);
    const int colPU   = int(tableW * 0.175);
    const int colTot  = tableW - colDesc - colQty - colPU;
    const int tHdrH   = 40;
    const int tRowH   = 66;

    // En-tête tableau (fond teal)
    fillR(QRect(M, y, tableW, tHdrH), cTeal);
    // Coins bas plats
    p.fillRect(QRect(M, y + tHdrH / 2, tableW, tHdrH / 2), cTeal);

    sf(10, true); p.setPen(cWhite);
    int cx = M;
    p.drawText(QRect(cx + 14, y, colDesc - 14, tHdrH), Qt::AlignVCenter | Qt::AlignLeft, "Désignation");
    cx += colDesc;
    p.drawText(QRect(cx, y, colQty, tHdrH), Qt::AlignCenter, "Qté");
    cx += colQty;
    p.drawText(QRect(cx, y, colPU, tHdrH), Qt::AlignCenter, "P.U. HT");
    cx += colPU;
    p.drawText(QRect(cx, y, colTot, tHdrH), Qt::AlignCenter, "Total HT");
    y += tHdrH;

    // Ligne article (fond teinté)
    fillR(QRect(M, y, tableW, tRowH), cLightTeal);
    // Séparateurs verticaux
    p.save(); p.setPen(QPen(cBorder, 1)); p.setBrush(Qt::NoBrush);
    cx = M + colDesc; p.drawLine(cx, y, cx, y + tRowH);
    cx += colQty;     p.drawLine(cx, y, cx, y + tRowH);
    cx += colPU;      p.drawLine(cx, y, cx, y + tRowH);
    // Bordure externe
    p.drawRect(QRect(M, y, tableW, tRowH));
    p.restore();

    sf(10, false); p.setPen(cDark);
    p.drawText(QRect(M + 14, y + 8, colDesc - 28, tRowH - 16),
               Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, designation);
    cx = M + colDesc;
    p.drawText(QRect(cx, y, colQty, tRowH), Qt::AlignCenter, "1");
    cx += colQty;
    p.drawText(QRect(cx, y, colPU, tRowH), Qt::AlignCenter, fmtDT(totalHT));
    cx += colPU;
    p.drawText(QRect(cx, y, colTot, tRowH), Qt::AlignCenter, fmtDT(totalHT));
    y += tRowH + 28;

    // ════════════════════════════════════════════════════════════════════
    //  BLOC TOTAUX
    // ════════════════════════════════════════════════════════════════════
    const int totW  = 560;
    const int totX  = W - M - totW;
    const int lineH = 38;

    auto totLine = [&](const QString& k, const QString& v, bool highlight) {
        if (highlight) {
            fillRR(QRect(totX, y, totW, lineH), 7, cAccent);
            sf(12, true); p.setPen(cWhite);
        } else {
            fillR(QRect(totX, y, totW, lineH), cLight);
            p.save(); p.setPen(QPen(cBorder, 1)); p.setBrush(Qt::NoBrush);
            p.drawRect(QRect(totX, y, totW, lineH)); p.restore();
            sf(10, false); p.setPen(cDark);
        }
        p.drawText(QRect(totX + 18, y, totW / 2, lineH), Qt::AlignLeft  | Qt::AlignVCenter, k);
        p.drawText(QRect(totX + totW/2, y, totW/2 - 18, lineH), Qt::AlignRight | Qt::AlignVCenter, v);
        y += lineH + 5;
    };

    totLine("Sous-total HT", fmtDT(totalHT),  false);
    totLine("TVA (19 %)",    fmtDT(tva),       false);
    totLine("TOTAL TTC",     fmtDT(totalTTC),  true);

    // ════════════════════════════════════════════════════════════════════
    //  PIED DE PAGE
    // ════════════════════════════════════════════════════════════════════
    const int footY = H - M - 68;
    fillR(QRect(M, footY, tableW, 3), cTeal);

    sf(8, false); p.setPen(cMid);
    p.drawText(QRect(M, footY + 12, tableW, 22),
               Qt::AlignLeft | Qt::AlignVCenter,
               "Document confidentiel — usage interne uniquement.");
    p.drawText(QRect(M, footY + 12, tableW, 22),
               Qt::AlignRight | Qt::AlignVCenter,
               "Généré par SmartResearchLab · Module Finance");
    p.drawText(QRect(M, footY + 38, tableW, 22),
               Qt::AlignCenter,
               "SmartResearchLab  ·  Urban Park, Ariana 1080  ·  finance@smartresearchlab.tn");

    p.end();
    return true;
}

void MainWindow::on_BtnApply_clicked()
{
    QVector<Finance::Row> rows;
    QString err;
    if (!Finance::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "SQL Error", err);
        return;
    }

    // Lecture des critères
    const int typeIdx = ui->CbType->currentIndex();           // 0=tous 1=Dépense 2=Revenu
    QString typeVal = (typeIdx == 0) ? "" : ui->CbType->currentText();
    if (typeVal == "Dépense") typeVal = "Depense";            // normalisation accent → DB
    const QDate   dateFrom = ui->DateFrom->date();
    const QDate   dateTo   = ui->DateTo->date();
    const QString search   = ui->EdSearch->text().trimmed().toLower();

    ui->TableFinance->setSortingEnabled(false);
    ui->TableFinance->setRowCount(0);
    int row = 0;
    for (const auto& r : std::as_const(rows)) {
        // Filtre type
        if (!typeVal.isEmpty() && r.type != typeVal) continue;

        // Filtre période
        const QDate dt = QDate::fromString(r.dateTransaction, "yyyy-MM-dd");
        if (dt.isValid() && (dt < dateFrom || dt > dateTo)) continue;

        // Filtre texte libre (code, catégorie, description)
        if (!search.isEmpty()) {
            const bool match = r.code.toLower().contains(search)
                            || r.categorie.toLower().contains(search)
                            || r.description.toLower().contains(search);
            if (!match) continue;
        }

        ui->TableFinance->insertRow(row);
        auto *itCode = new QTableWidgetItem(r.code);
        itCode->setData(Qt::UserRole, r.id);
        ui->TableFinance->setItem(row, 0, itCode);

        const QString typeDisplay = (r.type == "Depense") ? "Dépense" : r.type;
        auto *itType = new QTableWidgetItem(typeDisplay);
        itType->setData(Qt::UserRole, r.type);
        ui->TableFinance->setItem(row, 1, itType);

        auto *itMontant = new QTableWidgetItem();
        itMontant->setData(Qt::DisplayRole, r.montant.toDouble());
        ui->TableFinance->setItem(row, 2, itMontant);

        ui->TableFinance->setItem(row, 3, new QTableWidgetItem(r.categorie));
        ui->TableFinance->setItem(row, 4, new QTableWidgetItem(r.description));
        ui->TableFinance->setItem(row, 5, new QTableWidgetItem(r.dateTransaction));
        ui->TableFinance->setItem(row, 6, new QTableWidgetItem(r.modePaiement));
        ui->TableFinance->setItem(row, 7, new QTableWidgetItem(r.dateCreation));
        row++;
    }
    ui->TableFinance->setSortingEnabled(true);
}

void MainWindow::on_BtnReset_clicked()
{
    ui->CbType->setCurrentIndex(0);
    ui->DateFrom->setDate(QDate(2000, 1, 1));
    ui->DateTo->setDate(QDate::currentDate());
    ui->EdSearch->clear();
    on_BtnApply_clicked(); // Rafraîchir via la logique de filtrage
}

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
void MainWindow::on_BtnAdd_4_clicked()
{
    ui->stacked_F->setCurrentIndex(3);
    updateFinanceStats();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++PUUUUUUUBLIIIICAAAAATTTIIIOOONNNNNN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QString MainWindow::selectedPublicationId() const
{
    int row = ui->tablePublication->currentRow();
    if (row < 0) return "";

    QTableWidgetItem *item = ui->tablePublication->item(row, 0);
    if (!item) return "";

    return item->data(Qt::UserRole).toString();
}

void MainWindow::initPublicationUi()
{
    ui->tablePublication->setColumnCount(8);
    ui->tablePublication->setHorizontalHeaderLabels({
        "Titre",
        "Inventeurs",
        "Domaine",
        "Type brevet",
        "Numero brevet",
        "Date depot",
        "Statut brevet",
        "Resume"
    });

    ui->tablePublication->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePublication->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablePublication->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePublication->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablePublication->verticalHeader()->setVisible(false);
}

void MainWindow::loadPublications()
{
    ui->tablePublication->setSortingEnabled(false);
    ui->tablePublication->clearContents();
    ui->tablePublication->setRowCount(0);

    QVector<Publication::Row> rows;
    QString err;

    if (!Publication::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }

    for (const auto &r : std::as_const(rows)) {
        int row = ui->tablePublication->rowCount();
        ui->tablePublication->insertRow(row);

        QTableWidgetItem *titreItem = new QTableWidgetItem(r.titre);
        titreItem->setData(Qt::UserRole, r.idPublication);

        ui->tablePublication->setItem(row, 0, titreItem);
        ui->tablePublication->setItem(row, 1, new QTableWidgetItem(r.inventeurs));
        ui->tablePublication->setItem(row, 2, new QTableWidgetItem(r.domaineFabrication));
        ui->tablePublication->setItem(row, 3, new QTableWidgetItem(r.typeBrevet));
        ui->tablePublication->setItem(row, 4, new QTableWidgetItem(QString::number(r.numeroBrevet)));

        // DATE : affichage simple en yyyy-MM-dd
        ui->tablePublication->setItem(row, 5, new QTableWidgetItem(r.dateDepot));

        ui->tablePublication->setItem(row, 6, new QTableWidgetItem(r.statutBrevet));
        ui->tablePublication->setItem(row, 7, new QTableWidgetItem(r.resume));
    }

    ui->tablePublication->setSortingEnabled(true);
    ui->tablePublication->resizeColumnsToContents();
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
    idPublicationToEdit.clear();
    ui->stack_pub->setCurrentIndex(0);
}

//_______________statbtn____________
void MainWindow::on_btnVoirStatistiquesPub_clicked()
{
    showPublicationStats();

}
//__________________________________

void MainWindow::on_btnAddPub_clicked()
{
    QString titre       = ui->lineTitreAdd->text().trimmed();
    QString inventeurs  = ui->lineInventeursAdd->text().trimmed();
    QString resume      = ui->lineResumeAdd->text().trimmed();
    QString domaine     = ui->lineDomaineAdd->text().trimmed();
    QString typeBrevet  = ui->comboTypeBrevetAdd->currentText().trimmed();
    QString statut      = ui->comboStatusBrevetAdd->currentText().trimmed();
    QString numText     = ui->lineNumeroBrevetAdd->text().trimmed();
    QDate dateDepot     = ui->dateDepotAdd->date();

    if (titre.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Le titre est obligatoire.");
        return;
    }

    if (inventeurs.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Le champ inventeurs est obligatoire.");
        return;
    }

    bool okNum = true;
    int numeroBrevet = 0;
    if (!numText.isEmpty()) {
        numeroBrevet = numText.toInt(&okNum);
        if (!okNum) {
            QMessageBox::warning(this, "Ajout", "Le numero de brevet doit etre numerique.");
            return;
        }
    }

    QString idEmp = "7"; // remplace par l'id de l'utilisateur connecté si tu l'as

    Publication p(
        titre,
        resume,
        inventeurs,
        domaine,
        typeBrevet,
        numeroBrevet,
        dateDepot,
        statut,
        idEmp
        );

    QString err;
    if (!p.ajouter(&err)) {
        QMessageBox::critical(this, "Erreur SQL", err);
        return;
    }

    QMessageBox::information(this, "Succes", "Publication ajoutee avec succes.");

    ui->lineTitreAdd->clear();
    ui->lineInventeursAdd->clear();
    ui->lineResumeAdd->clear();
    ui->lineDomaineAdd->clear();
    ui->lineNumeroBrevetAdd->clear();
    ui->dateDepotAdd->setDate(QDate::currentDate());
    ui->comboTypeBrevetAdd->setCurrentIndex(0);
    ui->comboStatusBrevetAdd->setCurrentIndex(0);

    loadPublications();
    ui->stack_pub->setCurrentIndex(0);
}

void MainWindow::on_btnModifierPub_clicked()
{
    int row = ui->tablePublication->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Modification", "Veuillez selectionner une publication.");
        return;
    }

    idPublicationToEdit = selectedPublicationId();
    if (idPublicationToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modification", "ID publication introuvable.");
        return;
    }

    ui->lineTitreEdit->setText(ui->tablePublication->item(row, 0)->text());
    ui->lineInventeursEdit->setText(ui->tablePublication->item(row, 1)->text());
    ui->lineDomaineEdit->setText(ui->tablePublication->item(row, 2)->text());

    {
        QString type = ui->tablePublication->item(row, 3)->text();
        int idx = ui->comboTypeBrevetEdit->findText(type);
        if (idx >= 0) ui->comboTypeBrevetEdit->setCurrentIndex(idx);
    }

    ui->lineNumeroBrevetEdit->setText(ui->tablePublication->item(row, 4)->text());

    {
        QDate d = QDate::fromString(ui->tablePublication->item(row, 5)->text(), "yyyy-MM-dd");
        if (d.isValid())
            ui->dateDepotEdit->setDate(d);
        else
            ui->dateDepotEdit->setDate(QDate::currentDate());
    }

    {
        QString statut = ui->tablePublication->item(row, 6)->text();
        int idx = ui->comboStatusBrevetEdit->findText(statut);
        if (idx >= 0) ui->comboStatusBrevetEdit->setCurrentIndex(idx);
    }

    ui->lineResumeEdit->setText(ui->tablePublication->item(row, 7)->text());

    ui->stack_pub->setCurrentIndex(2);
}

void MainWindow::on_btnConfirmEditPub_clicked()
{
    if (idPublicationToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Aucune publication selectionnee.");
        return;
    }

    QString titre       = ui->lineTitreEdit->text().trimmed();
    QString inventeurs  = ui->lineInventeursEdit->text().trimmed();
    QString resume      = ui->lineResumeEdit->text().trimmed();
    QString domaine     = ui->lineDomaineEdit->text().trimmed();
    QString typeBrevet  = ui->comboTypeBrevetEdit->currentText().trimmed();
    QString statut      = ui->comboStatusBrevetEdit->currentText().trimmed();
    QString numText     = ui->lineNumeroBrevetEdit->text().trimmed();
    QDate dateDepot     = ui->dateDepotEdit->date();

    if (titre.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Le titre est obligatoire.");
        return;
    }

    if (inventeurs.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Le champ inventeurs est obligatoire.");
        return;
    }

    bool okNum = true;
    int numeroBrevet = 0;
    if (!numText.isEmpty()) {
        numeroBrevet = numText.toInt(&okNum);
        if (!okNum) {
            QMessageBox::warning(this, "Modification", "Le numero de brevet doit etre numerique.");
            return;
        }
    }

    QString idEmp = "7"; // remplace par l'id session si disponible

    Publication p(
        titre,
        resume,
        inventeurs,
        domaine,
        typeBrevet,
        numeroBrevet,
        dateDepot,
        statut,
        idEmp
        );

    QString err;
    if (!p.modifier(idPublicationToEdit, &err)) {
        QMessageBox::critical(this, "Erreur SQL", err);
        return;
    }

    QMessageBox::information(this, "Succes", "Publication modifiee avec succes.");

    idPublicationToEdit.clear();
    loadPublications();
    ui->stack_pub->setCurrentIndex(0);
}

void MainWindow::on_btnSupprimerPub_clicked()
{
    int row = ui->tablePublication->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Suppression", "Veuillez selectionner une publication.");
        return;
    }

    QString idPublication = selectedPublicationId();
    if (idPublication.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "ID publication introuvable.");
        return;
    }

    QString titre = ui->tablePublication->item(row, 0)->text();

    QMessageBox::StandardButton rep = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous supprimer la publication :\n" + titre + " ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (rep != QMessageBox::Yes)
        return;

    QString err;
    if (!Publication::supprimer(idPublication, &err)) {
        QMessageBox::critical(this, "Erreur SQL", err);
        return;
    }

    QMessageBox::information(this, "Succes", "Publication supprimee avec succes.");
    loadPublications();
}

//===========================pdf==============================
void MainWindow::on_btnExporterPub_clicked()
{
    if (ui->tablePublication->rowCount() == 0) {
        QMessageBox::warning(this, "Export PDF", "Aucune publication à exporter.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter les publications en PDF",
        "Liste_Publications.pdf",
        "PDF Files (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setResolution(300);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    const int margin = 60;
    const int pageWidth = pdf.width();
    const int pageHeight = pdf.height();

    int y = margin;

    QFont titleFont("Arial", 16, QFont::Bold);
    QFont headerFont("Arial", 9, QFont::Bold);
    QFont cellFont("Arial", 8);

    // ===== Titre =====
    painter.setFont(titleFont);
    painter.drawText(margin, y, "Liste des Publications");
    y += 50;

    painter.setFont(QFont("Arial", 9));
    painter.drawText(margin, y, "Date : " + QDate::currentDate().toString("dd/MM/yyyy")
                                    + "    Heure : " + QTime::currentTime().toString("hh:mm:ss"));
    y += 40;

    // ===== Configuration tableau =====
    int columnCount = ui->tablePublication->columnCount();
    int rowCount = ui->tablePublication->rowCount();

    if (columnCount <= 0) {
        painter.end();
        QMessageBox::warning(this, "Export PDF", "Le tableau ne contient aucune colonne.");
        return;
    }

    int tableWidth = pageWidth - 2 * margin;
    int rowHeight = 45;
    int headerHeight = 50;

    QVector<int> colWidths;
    colWidths << 220  // Titre
              << 160  // Inventeurs
              << 140  // Domaine
              << 120  // Type brevet
              << 100  // Numero brevet
              << 110  // Date depot
              << 120  // Statut brevet
              << 220; // Resume

    // sécurité si le nombre de colonnes diffère
    while (colWidths.size() < columnCount)
        colWidths << 120;

    if (colWidths.size() > columnCount)
        colWidths.resize(columnCount);

    int totalWidth = 0;
    for (int w : std::as_const(colWidths)) totalWidth += w;

    double scale = static_cast<double>(tableWidth) / totalWidth;
    for (int i = 0; i < colWidths.size(); ++i)
        colWidths[i] = int(colWidths[i] * scale);

    auto drawTableHeader = [&]() {
        int x = margin;
        painter.setFont(headerFont);

        for (int c = 0; c < columnCount; ++c) {
            QRect rect(x, y, colWidths[c], headerHeight);
            painter.drawRect(rect);

            QString headerText;
            QTableWidgetItem *headerItem = ui->tablePublication->horizontalHeaderItem(c);
            if (headerItem)
                headerText = headerItem->text();
            else
                headerText = QString("Colonne %1").arg(c + 1);

            painter.drawText(rect.adjusted(4, 4, -4, -4),
                             Qt::AlignCenter | Qt::TextWordWrap,
                             headerText);

            x += colWidths[c];
        }

        y += headerHeight;
    };

    drawTableHeader();

    // ===== Lignes =====
    painter.setFont(cellFont);

    for (int r = 0; r < rowCount; ++r) {

        // saut de page
        if (y + rowHeight > pageHeight - margin) {
            pdf.newPage();
            y = margin;

            painter.setFont(titleFont);
            painter.drawText(margin, y, "Liste des Publications");
            y += 40;

            painter.setFont(QFont("Arial", 9));
            painter.drawText(margin, y, "Suite");
            y += 30;

            drawTableHeader();
            painter.setFont(cellFont);
        }

        int x = margin;

        for (int c = 0; c < columnCount; ++c) {
            QRect rect(x, y, colWidths[c], rowHeight);
            painter.drawRect(rect);

            QString text;
            QTableWidgetItem *item = ui->tablePublication->item(r, c);
            if (item)
                text = item->text();

            painter.drawText(rect.adjusted(4, 4, -4, -4),
                             Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,
                             text);

            x += colWidths[c];
        }

        y += rowHeight;
    }

    painter.end();

    QMessageBox::information(this, "Succès", "Le PDF des publications a été exporté avec succès.");
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
//=====================recherche par titre et doi =====================
void MainWindow::on_lineSearchPub_textChanged(const QString &text)
{
    QString search = text.trimmed().toLower();

    // Bonus : si le champ est vide, on réaffiche toutes les lignes
    if (search.isEmpty()) {
        for (int i = 0; i < ui->tablePublication->rowCount(); i++) {
            ui->tablePublication->setRowHidden(i, false);
        }
        return;
    }

    for (int i = 0; i < ui->tablePublication->rowCount(); i++) {
        QString titre = ui->tablePublication->item(i, 0)->text().toLower();
        QString numero = ui->tablePublication->item(i, 4)->text().toLower();

        bool match = titre.contains(search) || numero.contains(search);

        ui->tablePublication->setRowHidden(i, !match);
    }
}
//======================tri par titre===================
int getColumnIndex(QTableWidget *table, const QString &headerName)
{
    for (int i = 0; i < table->columnCount(); i++) {
        if (table->horizontalHeaderItem(i)->text() == headerName)
            return i;
    }
    return -1;
}

void MainWindow::on_comboTriPub_currentIndexChanged(int /*index*/)
{
    on_btnAppliquerPub_clicked();
}

void MainWindow::on_comboBox_currentIndexChanged(int /*index*/)
{
    showPublicationStats();
}

void MainWindow::on_pointage_pressed()
{
    // géré par on_pointage_clicked
}

void MainWindow::on_btnAppliquerPub_clicked()
{
    QString choix = ui->comboTriPub->currentText().trimmed();

    if (choix == "Titre") {
        ui->tablePublication->sortItems(0, Qt::AscendingOrder);
    }
    else if (choix == "Date depot") {
        ui->tablePublication->sortItems(5, Qt::DescendingOrder);
    }
}
//=====================stat======================
void MainWindow::clearLayout(QLayout *layout)
{
    if (!layout) return;

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget())
            delete item->widget();
        delete item;
    }
}

void MainWindow::showPublicationStats()
{
    QString choix = ui->comboBox->currentText().trimmed().toLower();

    if (choix.contains("domaine")) {
        showPublicationStatsByDomaine();
    }
    else if (choix.contains("statut")) {
        showPublicationStatsByStatut();
    }
    else {
        QMessageBox::warning(this, "Statistiques", "Choix invalide.");
    }
}

void MainWindow::showPublicationStatsByDomaine()
{
    QStringList categories;
    QList<double> valeurs;
    int maxValue = 0;

    QSqlQuery query;
    query.prepare(
        "SELECT DOMAINE_FABRICATION, COUNT(*) "
        "FROM PUBLICATIONS "
        "GROUP BY DOMAINE_FABRICATION "
        "ORDER BY COUNT(*) DESC"
        );

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    bool hasData = false;
    while (query.next()) {
        hasData = true;
        QString domaine = query.value(0).toString().trimmed();
        int nb = query.value(1).toInt();
        if (domaine.isEmpty()) domaine = "Non specifie";

        if (nb > maxValue)
            maxValue = nb;

        valeurs << nb;
        categories << domaine;
    }

    if (!hasData) {
        QMessageBox::information(this, "Statistiques", "Aucune publication trouvee.");
        return;
    }

    QBarSet *set = new QBarSet("Nombre de publications");
    for (int v : std::as_const(valeurs)) *set << v;

    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des publications par domaine");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxValue + 2);
    axisY->setTitleText("Nombre de publications");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 600);
    chartView->setWindowTitle("Statistiques Publications - Par Domaine");
    chartView->setAttribute(Qt::WA_DeleteOnClose);
    chartView->show();
}

void MainWindow::showPublicationStatsByStatut()
{
    QStringList categories;
    QList<double> valeurs;
    int maxValue = 0;

    QSqlQuery query;
    query.prepare(
        "SELECT STATUT_BREVET, COUNT(*) "
        "FROM PUBLICATIONS "
        "GROUP BY STATUT_BREVET "
        "ORDER BY COUNT(*) DESC"
        );

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    bool hasData = false;
    while (query.next()) {
        hasData = true;

        QString statut = query.value(0).toString().trimmed();
        int nb = query.value(1).toInt();

        if (statut.isEmpty()) statut = "Non specifie";

        if (nb > maxValue) maxValue = nb;
        valeurs    << nb;
        categories << statut;
    }

    if (!hasData) {
        QMessageBox::information(this, "Statistiques", "Aucune publication trouvee.");
        return;
    }

    QBarSet *set = new QBarSet("Nombre de publications");
    for (double v : std::as_const(valeurs)) *set << v;

    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des publications par statut");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxValue + 2);
    axisY->setTitleText("Nombre de publications");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 600);
    chartView->setWindowTitle("Statistiques Publications - Statut");
    chartView->setAttribute(Qt::WA_DeleteOnClose);
    chartView->show();
}
//===========================chatbot==============================================
void MainWindow::on_btnChatbotPub_clicked()
{
    ui->stack_pub->setCurrentIndex(4);
}
void MainWindow::on_btnRetourChatbotPub_clicked()
{
    ui->stack_pub->setCurrentIndex(0);
}

QString MainWindow::formaterResultatsPublication(QSqlQuery &query)
{
    QString resultat;
    int count = 0;

    while (query.next()) {
        count++;

        QString titre   = query.value("TITRE").toString();
        QString domaine = query.value("DOMAINE_FABRICATION").toString();
        QString type    = query.value("TYPE_BREVET").toString();
        QString numero  = query.value("NUMERO_BREVET").toString();
        QString date    = query.value("DATE_DEPOT").toDate().toString("yyyy-MM-dd");
        QString statut  = query.value("STATUT_BREVET").toString();

        resultat += "• Titre: " + titre
                    + " | Numero: " + numero
                    + " | Date: " + date
                    + " | Statut: " + statut
                    + " | Domaine: " + domaine
                    + " | Type: " + type
                    + "\n";
    }

    if (count == 0)
        return "Il n'y a pas de publication correspondante.";

    return resultat;
}

QString MainWindow::genererReponsePublication(const QString &question)
{
    QString q = question.trimmed().toLower();

    if (q.isEmpty())
        return "Veuillez écrire une question.";

    QSqlQuery query;

    // =========================
    // 1) QUESTIONS DE NOMBRE
    // =========================
    if (q.contains("combien")) {
        if (q.contains("accept")) {
            query.prepare("SELECT COUNT(*) FROM PUBLICATIONS WHERE LOWER(STATUT_BREVET) LIKE '%accept%'");
            if (query.exec() && query.next())
                return "Il y a " + QString::number(query.value(0).toInt()) + " publications acceptées.";
            return "Erreur lors de la lecture de la base.";
        }

        if (q.contains("refus")) {
            query.prepare("SELECT COUNT(*) FROM PUBLICATIONS WHERE LOWER(STATUT_BREVET) LIKE '%refus%'");
            if (query.exec() && query.next())
                return "Il y a " + QString::number(query.value(0).toInt()) + " publications refusées.";
            return "Erreur lors de la lecture de la base.";
        }

        if (q.contains("cours")) {
            query.prepare("SELECT COUNT(*) FROM PUBLICATIONS WHERE LOWER(STATUT_BREVET) LIKE '%cours%'");
            if (query.exec() && query.next())
                return "Il y a " + QString::number(query.value(0).toInt()) + " publications en cours.";
            return "Erreur lors de la lecture de la base.";
        }

        if (q.contains("publ")) {
            query.prepare("SELECT COUNT(*) FROM PUBLICATIONS WHERE LOWER(STATUT_BREVET) LIKE '%publ%'");
            if (query.exec() && query.next())
                return "Il y a " + QString::number(query.value(0).toInt()) + " publications publiées.";
            return "Erreur lors de la lecture de la base.";
        }

        // nombre total
        query.prepare("SELECT COUNT(*) FROM PUBLICATIONS");
        if (query.exec() && query.next())
            return "Il y a " + QString::number(query.value(0).toInt()) + " publications.";
        return "Erreur lors de la lecture de la base.";
    }

    // =========================
    // 2) RECHERCHE PAR NUMERO
    // =========================
    QRegularExpression regexNumero("(\\d{4,})");
    QRegularExpressionMatch matchNumero = regexNumero.match(q);

    if (q.contains("numero") || q.contains("numéro") || matchNumero.hasMatch()) {
        QString numero = matchNumero.hasMatch() ? matchNumero.captured(1) : "";

        if (!numero.isEmpty()) {
            if (q.contains("statut")) {
                query.prepare("SELECT TITRE, STATUT_BREVET FROM PUBLICATIONS WHERE NUMERO_BREVET = :num");
                query.bindValue(":num", numero);

                if (!query.exec())
                    return "Erreur SQL : " + query.lastError().text();

                if (query.next()) {
                    return "Le statut de la publication \"" + query.value(0).toString()
                    + "\" est : " + query.value(1).toString() + ".";
                }
                return "Il n'y a pas de publication avec ce numéro.";
            }
            else {
                query.prepare(
                    "SELECT TITRE, DOMAINE_FABRICATION, TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET "
                    "FROM PUBLICATIONS WHERE NUMERO_BREVET = :num"
                    );
                query.bindValue(":num", numero);

                if (!query.exec())
                    return "Erreur SQL : " + query.lastError().text();

                return formaterResultatsPublication(query);
            }
        }
    }

    // =========================
    // 3) RECHERCHE PAR DATE
    // formats supportés:
    // yyyy-MM-dd
    // dd/MM/yyyy
    // =========================
    QRegularExpression regexDateIso("(\\d{4}-\\d{2}-\\d{2})");
    QRegularExpression regexDateFr("(\\d{2}/\\d{2}/\\d{4})");

    QString dateCherchee;

    QRegularExpressionMatch matchIso = regexDateIso.match(q);
    QRegularExpressionMatch matchFr  = regexDateFr.match(q);

    if (matchIso.hasMatch()) {
        dateCherchee = matchIso.captured(1);
    } else if (matchFr.hasMatch()) {
        QDate d = QDate::fromString(matchFr.captured(1), "dd/MM/yyyy");
        if (d.isValid())
            dateCherchee = d.toString("yyyy-MM-dd");
    }

    if (!dateCherchee.isEmpty()) {
        if (q.contains("statut")) {
            query.prepare(
                "SELECT TITRE, STATUT_BREVET "
                "FROM PUBLICATIONS "
                "WHERE TRUNC(DATE_DEPOT) = TO_DATE(:d, 'YYYY-MM-DD')"
                );
            query.bindValue(":d", dateCherchee);

            if (!query.exec())
                return "Erreur SQL : " + query.lastError().text();

            if (query.next()) {
                return "Le statut de la publication \"" + query.value(0).toString()
                + "\" est : " + query.value(1).toString() + ".";
            }
            return "Il n'y a pas de publication à cette date.";
        }
        else {
            query.prepare(
                "SELECT TITRE, DOMAINE_FABRICATION, TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET "
                "FROM PUBLICATIONS "
                "WHERE TRUNC(DATE_DEPOT) = TO_DATE(:d, 'YYYY-MM-DD')"
                );
            query.bindValue(":d", dateCherchee);

            if (!query.exec())
                return "Erreur SQL : " + query.lastError().text();

            return formaterResultatsPublication(query);
        }
    }

    // =========================
    // 4) RECHERCHE PAR TITRE
    // Exemples:
    // - donne la publication de titre smartphone
    // - quel est le statut de smartphone
    // =========================
    if (q.contains("titre") || q.contains("statut") || q.contains("publication")) {
        QString titreCherche = q;

        titreCherche.replace("quel est le statut de", "");
        titreCherche.replace("quel est le statut du", "");
        titreCherche.replace("quel est le statut", "");
        titreCherche.replace("donne la publication de titre", "");
        titreCherche.replace("donne la publication du titre", "");
        titreCherche.replace("donne la publication", "");
        titreCherche.replace("titre", "");
        titreCherche.replace("de", "");
        titreCherche = titreCherche.trimmed();

        if (!titreCherche.isEmpty()) {
            if (q.contains("statut")) {
                query.prepare(
                    "SELECT TITRE, STATUT_BREVET "
                    "FROM PUBLICATIONS "
                    "WHERE LOWER(TITRE) LIKE :titre"
                    );
                query.bindValue(":titre", "%" + titreCherche + "%");

                if (!query.exec())
                    return "Erreur SQL : " + query.lastError().text();

                if (query.next()) {
                    return "Le statut de la publication \"" + query.value(0).toString()
                    + "\" est : " + query.value(1).toString() + ".";
                }
                return "Il n'y a pas de publication avec ce titre.";
            }
            else {
                query.prepare(
                    "SELECT TITRE, DOMAINE_FABRICATION, TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET "
                    "FROM PUBLICATIONS "
                    "WHERE LOWER(TITRE) LIKE :titre"
                    );
                query.bindValue(":titre", "%" + titreCherche + "%");

                if (!query.exec())
                    return "Erreur SQL : " + query.lastError().text();

                return formaterResultatsPublication(query);
            }
        }
    }

    return "Je n'ai pas compris la question.";
}

void MainWindow::on_btnEnvoyerQuestionPub_clicked()
{
    QString question = ui->lineQuestionPub->text().trimmed();

    if (question.isEmpty())
        return;

    ui->textChatPub->append("Vous : " + question);

    QString reponse = genererReponsePublication(question);

    ui->textChatPub->append("Bot : " + reponse);
    ui->textChatPub->append(""); // ligne vide

    ui->lineQuestionPub->clear();
}

//=================================mailing=========================================
bool MainWindow::emailValide(const QString &email)
{
    QRegularExpression regex("^[A-Za-z0-9._%+-]+@gmail\\.com$");
    return regex.match(email).hasMatch();
}
QString MainWindow::genererContenuMailPublications()
{
    QSqlQuery query;
    query.prepare(
        "SELECT TITRE, RESUME, INVENTEURS, DOMAINE_FABRICATION, "
        "TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET "
        "FROM PUBLICATIONS "
        "ORDER BY ID_PUBLICATION ASC"
        );

    if (!query.exec()) {
        return "Erreur SQL : " + query.lastError().text();
    }

    QString contenu;
    contenu += "Liste des publications\n\n";

    int count = 0;

    while (query.next()) {
        count++;

        contenu += "Publication " + QString::number(count) + "\n";
        contenu += "Titre : " + query.value(0).toString() + "\n";
        contenu += "Resume : " + query.value(1).toString() + "\n";
        contenu += "Inventeurs : " + query.value(2).toString() + "\n";
        contenu += "Domaine : " + query.value(3).toString() + "\n";
        contenu += "Type brevet : " + query.value(4).toString() + "\n";
        contenu += "Numero brevet : " + query.value(5).toString() + "\n";
        contenu += "Date depot : " + query.value(6).toDate().toString("yyyy-MM-dd") + "\n";
        contenu += "Statut brevet : " + query.value(7).toString() + "\n";
        contenu += "----------------------------------\n";
    }

    if (count == 0) {
        return "Aucune publication disponible.";
    }

    return contenu;
}

void MainWindow::on_btnMailingPub_clicked()
{
    bool ok = false;

    QString emailDest = QInputDialog::getText(
                            this,
                            "Mailing Publications",
                            "Entrez un Gmail destinataire :",
                            QLineEdit::Normal,
                            "",
                            &ok
                            ).trimmed();

    if (!ok || emailDest.isEmpty())
        return;

    if (!emailValide(emailDest)) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un vrai Gmail.");
        return;
    }

    QString contenu = genererContenuMailPublications();

    if (contenu.startsWith("Erreur SQL")) {
        QMessageBox::critical(this, "Erreur", contenu);
        return;
    }

    QString erreur;
    MailSender sender;

    const QString smtpUser = "rrayyyrrayyy@gmail.com";
    const QString smtpPass = "qxel rihn nrrl fgtq";

    bool success = sender.envoyerMail(
        smtpUser,
        smtpPass,
        emailDest,
        "Liste des publications",
        contenu,
        erreur
        );

    if (success) {
        QMessageBox::information(this, "Succès", "Mail envoyé avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", erreur);
    }
}
// ==================== EMPLOYEE CRUD ====================

void MainWindow::loadEmployees()
{
    ui->TableEmp->setSortingEnabled(false); // Désactiver le tri pendant le remplissage
    ui->TableEmp->clearContents();
    ui->TableEmp->setRowCount(0);

    QVector<Employe::Row> rows;
    QString errMsg;
    if (!Employe::chargerTout(rows, &errMsg)) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données :\n" + errMsg);
        return;
    }

    for (const auto &r : std::as_const(rows)) {
        int row = ui->TableEmp->rowCount();
        ui->TableEmp->insertRow(row);

        // Colonne 0 : CIN + ID SQL caché dans le UserRole
        auto *itemCin = new QTableWidgetItem(r.cin);
        itemCin->setData(Qt::UserRole, r.idEmploye);
        ui->TableEmp->setItem(row, 0, itemCin);

        ui->TableEmp->setItem(row, 1, new QTableWidgetItem(r.nom));
        ui->TableEmp->setItem(row, 2, new QTableWidgetItem(r.prenom));
        ui->TableEmp->setItem(row, 3, new QTableWidgetItem(r.username));
        ui->TableEmp->setItem(row, 4, new QTableWidgetItem(r.email));
        ui->TableEmp->setItem(row, 5, new QTableWidgetItem(r.poste));
        ui->TableEmp->setItem(row, 6, new QTableWidgetItem(r.departement));

        // Date (Triable)
        auto *itemDate = new QTableWidgetItem(r.dateEmbauche);
        itemDate->setData(Qt::EditRole, QDate::fromString(r.dateEmbauche, "yyyy-MM-dd"));
        ui->TableEmp->setItem(row, 7, itemDate);

        // Salaire (Numérique)
        auto *itemSal = new QTableWidgetItem(QString::number(r.salaire, 'f', 2));
        itemSal->setData(Qt::EditRole, r.salaire);
        ui->TableEmp->setItem(row, 8, itemSal);

        ui->TableEmp->setItem(row, 9, new QTableWidgetItem(r.role));
    }
    ui->TableEmp->resizeColumnsToContents();
}
void MainWindow::on_btnSaveEmployee_clicked()
{
    // 1. Récupération des données
    QString cin         = ui->lineCINAdd->text().trimmed();
    QString nom         = ui->lineNomAdd->text().trimmed();
    QString prenom      = ui->linePrenomAdd->text().trimmed();
    QString username    = ui->lineUsernameAdd->text().trimmed();
    QString email       = ui->lineEmailAdd->text().trimmed();
    QString password    = ui->linePasswordAdd->text(); // On ne trim pas un mot de passe
    QString poste       = ui->linePosteAdd->text().trimmed();
    QString departement = ui->lineDepartementAdd->text().trimmed();
    QString salaireStr  = ui->lineSalaireAdd->text().trimmed();
    QString role        = ui->comboRoleAdd->currentText();
    QDate dateEmb       = ui->dateEmbaucheAdd->date();

    // 2. CONTRAINTE : Tous les champs obligatoires
    if (cin.isEmpty() || nom.isEmpty() || prenom.isEmpty() || username.isEmpty() ||
        email.isEmpty() || password.isEmpty() || poste.isEmpty() ||
        departement.isEmpty() || salaireStr.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs du formulaire.");
        return;
    }

    // 3. CONTRAINTE : CIN (Exactement 8 chiffres)
    QRegularExpression cinRegex("^[0-9]{8}$");
    if (!cinRegex.match(cin).hasMatch()) {
        QMessageBox::warning(this, "Format CIN", "Le CIN doit contenir exactement 8 chiffres.");
        return;
    }

    // 4. CONTRAINTE : Format EMAIL (Regex standard)
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.[a-z]{2,4}$", QRegularExpression::CaseInsensitiveOption);
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Format Email", "L'adresse email saisie est invalide (ex: exemple@mail.com).");
        return;
    }

    // 5. CONTRAINTE : Unicité (Vérification SQL)
    if (Employe::usernameExiste(username)) {
        QMessageBox::warning(this, "Doublon", "Ce nom d'utilisateur est déjà utilisé.");
        return;
    }

    // NB: Tu peux ajouter Employe::emailExiste(email) si tu as créé la fonction en SQL

    // 6. Hachage et Enregistrement
    QString passHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    double salaire = salaireStr.toDouble();

    Employe e(cin, nom, prenom, username, passHash, email, poste, departement, dateEmb, salaire, role);

    QString errMsg;
    if (e.ajouter(&errMsg)) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès.");
        loadEmployees();
        ui->stack_emp->setCurrentIndex(0);
        // Optionnel : Vider les champs après succès
    } else {
        QMessageBox::critical(this, "Erreur SQL", "L'ajout a échoué :\n" + errMsg);
    }
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
    if (row < 0) {
        QMessageBox::warning(this, "Sélection", "Veuillez sélectionner un employé.");
        return;
    }

    // Remplissage des champs de l'interface de modification
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

    ui->stack_emp->setCurrentIndex(2); // Aller vers la page de modif
}
void MainWindow::on_btnSaveEditEmployee_clicked()
{
    int row = ui->TableEmp->currentRow();
    if (row < 0) return;

    QString idEmploye = ui->TableEmp->item(row, 0)->data(Qt::UserRole).toString();

    // Récupération des saisies
    QString cin      = ui->lineCIN_emp->text().trimmed();
    QString nom      = ui->lineNomEmp->text().trimmed();
    QString prenom   = ui->linePrenomEmp->text().trimmed();
    QString username = ui->lineUsernameEmp->text().trimmed();
    QString email    = ui->lineEmailEmp->text().trimmed();
    QString salaireS = ui->lineSalaireEmp->text().trimmed();

    // 1. Validation : Champs vides
    if (cin.isEmpty() || nom.isEmpty() || prenom.isEmpty() || username.isEmpty() || email.isEmpty() || salaireS.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires.");
        return;
    }

    // 2. Validation : Format CIN (8 chiffres)
    if (!QRegularExpression("^[0-9]{8}$").match(cin).hasMatch()) {
        QMessageBox::warning(this, "Format CIN", "Le CIN doit comporter exactement 8 chiffres.");
        return;
    }

    // 3. Validation : Format Email
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.[a-z]{2,4}$", QRegularExpression::CaseInsensitiveOption);
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Format Email", "L'adresse email est invalide.");
        return;
    }

    // 4. Validation : Unicité (Sauf pour la ligne en cours de modification)
    for (int i = 0; i < ui->TableEmp->rowCount(); ++i) {
        if (i == row) continue; // On ignore la ligne actuelle

        if (ui->TableEmp->item(i, 0)->text() == cin) {
            QMessageBox::warning(this, "Doublon", "Ce CIN est déjà attribué à un autre employé.");
            return;
        }
        if (ui->TableEmp->item(i, 3)->text() == username) {
            QMessageBox::warning(this, "Doublon", "Ce nom d'utilisateur est déjà pris.");
            return;
        }
        if (ui->TableEmp->item(i, 4)->text() == email) { // Colonne 4 = Email
            QMessageBox::warning(this, "Doublon", "Cet email est déjà utilisé par un autre employé.");
            return;
        }
    }

    // 5. Exécution de l'Update
    Employe e(cin, nom, prenom, username, "", email,
              ui->linePostemp->text().trimmed(),
              ui->lineDepartementEmp->text().trimmed(),
              ui->dateEmbaucheEmp->date(),
              salaireS.toDouble(),
              ui->comboRoleAdd_2->currentText());

    QString errMsg;
    if (e.modifier(idEmploye, &errMsg)) {
        QMessageBox::information(this, "Succès", "L'employé a été mis à jour.");
        loadEmployees();
        ui->stack_emp->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur SQL :\n" + errMsg);
    }
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











// ==================== FIN EMPLOYEE CRUD ====================


// ==================== LABS CRUD ====================

// ── Verrouiller champs affichage (page 4) ──
void MainWindow::verrouillerChampsAffichage() {
    ui->aff1->setReadOnly(true);
    ui->aff5->setReadOnly(true);
    ui->aff6->setReadOnly(true);
    ui->aff2->setReadOnly(true);
    ui->aff3->setEnabled(false);
    ui->aff7->setEnabled(false);
    ui->aff7_2->setEnabled(false);
    ui->aff3_2->setEnabled(false);
}

/// ── Export PDF avec dialogue ──
void MainWindow::on_BtnExportLabs_clicked()
{
    const QString fileName = QFileDialog::getSaveFileName(
        this, "Exporter les Laboratoires", "Liste_Labs.pdf", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    try {
        QPdfWriter pdfWriter(fileName);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        pdfWriter.setPageOrientation(QPageLayout::Portrait); // Mode portrait pour mieux afficher les détails
        pdfWriter.setResolution(300);

        QPainter painter(&pdfWriter);
        if (!painter.isActive())
            throw std::runtime_error("Impossible d'écrire dans le fichier.");

        // Variables de positionnement
        int x = 100;
        int y = 100;
        int lineHeight = 40;
        int labelWidth = 200;
        int valueWidth = 500;

        painter.setFont(QFont("Arial", 18, QFont::Bold));
        painter.drawText(x, y, "FICHE DÉTAILLÉE DU LABORATOIRE");
        y += 80;

        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(x, y, "INFORMATIONS GÉNÉRALES");
        y += 30;

        painter.setFont(QFont("Arial", 10));

        // Récupération des valeurs depuis les champs de la page d'affichage
        // Nom du laboratoire
        painter.drawText(x, y, "Nom du laboratoire :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff1->text());
        y += lineHeight;

        // Responsable
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Responsable :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff5->text());
        y += lineHeight;

        // Numéro de téléphone
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Numéro de téléphone :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff6->text());
        y += lineHeight;

        // Localisation
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Localisation :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff2->text());
        y += lineHeight;

        // Séparateur
        y += 20;
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(x, y, "CARACTÉRISTIQUES TECHNIQUES");
        y += 30;
        painter.setFont(QFont("Arial", 10));

        // Spécialité
        painter.drawText(x, y, "Spécialité :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff3->currentText());
        y += lineHeight;

        // Disponibilité
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Disponibilité :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff7->currentText());
        y += lineHeight;

        // Résultat
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Résultat / Statut :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff3_2->currentText());
        y += lineHeight;

        // Paiement
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Statut de paiement :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, ui->aff7_2->currentText());
        y += lineHeight + 30;

        // Ajout d'une section d'informations supplémentaires
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(x, y, "INFORMATIONS COMPLÉMENTAIRES");
        y += 30;
        painter.setFont(QFont("Arial", 10));

        // Date d'exportation
        painter.drawText(x, y, "Date d'exportation :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, QDate::currentDate().toString("dd/MM/yyyy"));
        y += lineHeight;

        // Heure d'exportation
        painter.setFont(QFont("Arial", 10));
        painter.drawText(x, y, "Heure d'exportation :");
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(x + labelWidth, y, QTime::currentTime().toString("hh:mm:ss"));

        painter.end();

        QMessageBox::information(this, "Succès", "L'exportation PDF de la fiche détaillée a été réalisée avec succès !");
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Erreur d'exportation",
                              QString("L'exportation a échoué : %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Erreur", "Une erreur inconnue est survenue.");
    }
}
// ── ID sélectionné ──
QString MainWindow::selectedLabsId() const
{
    const int r = ui->TableLabs_2->currentRow();
    if (r < 0) return {};
    QTableWidgetItem *it = ui->TableLabs_2->item(r, 0);
    return it ? it->text().trimmed() : QString();
}

// ── Configuration tableau ──
void MainWindow::setupTableLabs()
{
    ui->TableLabs_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableLabs_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableLabs_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableLabs_2->verticalHeader()->setVisible(false);
    ui->TableLabs_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // IMPORTANT: Activer le tri
    ui->TableLabs_2->setSortingEnabled(true);

    ui->TableLabs_2->setColumnCount(9);
    ui->TableLabs_2->setHorizontalHeaderLabels({
        "IDLABO", "Nom Laboratoire", "Responsable", "Numéro",
        "Localisation", "Disponibilité", "Spécialité", "Résultat", "Paiement"
    });

    // Masquer la colonne ID si vous voulez (optionnel)
    // ui->TableLabs_2->hideColumn(0);
}
// ── Chargement ──
void MainWindow::loadLabs()
{
    // Désactiver temporairement les signaux de filtrage pendant le chargement
    ui->LabsSearch_2->blockSignals(true);
    ui->LabsSpec_2->blockSignals(true);
    ui->LabsCap_2->blockSignals(true);

    ui->TableLabs_2->setSortingEnabled(false);
    ui->TableLabs_2->setRowCount(0);

    QVector<Labs::Row> rows;
    QString err;
    if (!Labs::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "Erreur - Laboratoires", err);
        ui->TableLabs_2->setSortingEnabled(true);

        // Réactiver les signaux
        ui->LabsSearch_2->blockSignals(false);
        ui->LabsSpec_2->blockSignals(false);
        ui->LabsCap_2->blockSignals(false);
        return;
    }

    for (int i = 0; i < rows.size(); ++i) {
        const auto &r = rows[i];
        ui->TableLabs_2->insertRow(i);

        QTableWidgetItem *idItem = new QTableWidgetItem(r.id);
        idItem->setData(Qt::UserRole, r.id);
        ui->TableLabs_2->setItem(i, 0, idItem);

        ui->TableLabs_2->setItem(i, 1, new QTableWidgetItem(r.nomlabo));
        ui->TableLabs_2->setItem(i, 2, new QTableWidgetItem(r.responsable));
        ui->TableLabs_2->setItem(i, 3, new QTableWidgetItem(r.numero));
        ui->TableLabs_2->setItem(i, 4, new QTableWidgetItem(r.localisation));
        ui->TableLabs_2->setItem(i, 5, new QTableWidgetItem(r.disponibilite));
        ui->TableLabs_2->setItem(i, 6, new QTableWidgetItem(r.specialite));
        ui->TableLabs_2->setItem(i, 7, new QTableWidgetItem(r.resultat));
        ui->TableLabs_2->setItem(i, 8, new QTableWidgetItem(r.paiement));
    }

    ui->TableLabs_2->setSortingEnabled(true);

    // Réactiver les signaux et appliquer le filtrage
    ui->LabsSearch_2->blockSignals(false);
    ui->LabsSpec_2->blockSignals(false);
    ui->LabsCap_2->blockSignals(false);

    // Appliquer le filtrage initial
    filterLabsDynamic();
}
void MainWindow::filterLabsDynamic()
{
    const QString key = ui->LabsSearch_2->text().trimmed().toLower();
    const QString spec = ui->LabsSpec_2->currentText().trimmed().toLower();
    const QString disp = ui->LabsCap_2->currentText().trimmed().toLower();

    // Désactiver le tri TEMPORAIREMENT pendant le filtrage
    ui->TableLabs_2->setSortingEnabled(false);

    int visibleCount = 0;

    for (int r = 0; r < ui->TableLabs_2->rowCount(); ++r) {
        // Récupérer les valeurs des colonnes
        QString nom = "";
        QString responsable = "";
        QString numero = "";
        QString localisation = "";
        QString disponibilite = "";
        QString specialite = "";

        if (ui->TableLabs_2->item(r, 1)) nom = ui->TableLabs_2->item(r, 1)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 2)) responsable = ui->TableLabs_2->item(r, 2)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 3)) numero = ui->TableLabs_2->item(r, 3)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 4)) localisation = ui->TableLabs_2->item(r, 4)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 5)) disponibilite = ui->TableLabs_2->item(r, 5)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 6)) specialite = ui->TableLabs_2->item(r, 6)->text().trimmed().toLower();

        bool ok = true;

        // Filtre par recherche texte (recherche dans nom, responsable, numero, localisation)
        if (!key.isEmpty()) {
            ok = (nom.contains(key) || responsable.contains(key) ||
                  numero.contains(key) || localisation.contains(key));
        }

        // Filtre par spécialité (si différent de "toutes les spécialités")
        if (ok && !spec.isEmpty() && !spec.startsWith("toutes")) {
            ok = (specialite == spec);
        }

        // Filtre par disponibilité (si différent de "toutes les disponibilités")
        if (ok && !disp.isEmpty() && !disp.startsWith("toutes")) {
            ok = (disponibilite == disp);
        }

        ui->TableLabs_2->setRowHidden(r, !ok);
        if (ok) visibleCount++;
    }

    // RÉACTIVER le tri APRÈS le filtrage
    ui->TableLabs_2->setSortingEnabled(true);

    // Optionnel: Afficher le nombre de résultats dans le placeholder
    if (visibleCount == 0 && (!key.isEmpty() || !spec.startsWith("toutes") || !disp.startsWith("toutes"))) {
        ui->LabsSearch_2->setPlaceholderText("Aucun résultat - Modifiez vos critères");
    } else {
        ui->LabsSearch_2->setPlaceholderText(QString("Rechercher (%1 laboratoires)").arg(visibleCount));
    }
}

void MainWindow::resetLabsFilters()
{
    // Bloquer les signaux pour éviter de déclencher le filtrage plusieurs fois
    ui->LabsSearch_2->blockSignals(true);
    ui->LabsSpec_2->blockSignals(true);
    ui->LabsCap_2->blockSignals(true);

    // Réinitialiser les champs
    ui->LabsSearch_2->clear();
    ui->LabsSpec_2->setCurrentIndex(0);  // "Toutes les spécialités"
    ui->LabsCap_2->setCurrentIndex(0);   // "Toutes les disponibilités"

    // Réactiver les signaux
    ui->LabsSearch_2->blockSignals(false);
    ui->LabsSpec_2->blockSignals(false);
    ui->LabsCap_2->blockSignals(false);

    // Rafraîchir l'affichage
    filterLabsDynamic();

    qDebug() << "Filtres réinitialisés";
}

// ── Init ──
void MainWindow::initLabsUi()
{
    setupTableLabs();

    // Configurer les combobox de filtrage avec les bonnes valeurs
    ui->LabsSpec_2->clear();
    ui->LabsSpec_2->addItem("Toutes les spécialités");
    ui->LabsSpec_2->addItem("interieur");
    ui->LabsSpec_2->addItem("exterieur");

    ui->LabsCap_2->clear();
    ui->LabsCap_2->addItem("Toutes les disponibilités");
    ui->LabsCap_2->addItem("Disponible");
    ui->LabsCap_2->addItem("Occupe");

    // S'assurer que le tri est activé
    ui->TableLabs_2->setSortingEnabled(true);

    loadLabs();

    // ========== CONNEXIONS POUR RECHERCHE DYNAMIQUE ==========
    // Recherche en temps réel quand l'utilisateur tape
    connect(ui->LabsSearch_2, &QLineEdit::textChanged, this, &MainWindow::filterLabsDynamic);

    // Filtrage quand la spécialité change
    connect(ui->LabsSpec_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::filterLabsDynamic);

    // Filtrage quand la disponibilité change
    connect(ui->LabsCap_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::filterLabsDynamic);

    // Connecter les boutons (optionnels, mais on les garde)
    //connect(ui->btnAppliquerPub_3, &QPushButton::clicked, this, &MainWindow::filterLabsDynamic);
    connect(ui->btnReinitialiserPub_3, &QPushButton::clicked, this, &MainWindow::resetLabsFilters);

    connect(ui->BtnPopupSaveLabs_3,  &QPushButton::clicked, this, &MainWindow::on_BtnPopupSaveLabs_3_clicked);
    connect(ui->BtnPopupResetLabs_3, &QPushButton::clicked, this, &MainWindow::on_BtnPopupResetLabs_3_clicked);
    connect(ui->BtnPopupSaveLabs_5,  &QPushButton::clicked, this, &MainWindow::on_BtnPopupSaveLabs_5_clicked);
    connect(ui->BtnPopupResetLabs_5, &QPushButton::clicked, this, &MainWindow::on_BtnPopupResetLabs_5_clicked);
    connect(ui->btnSupprimerPub_2,   &QPushButton::clicked, this, &MainWindow::on_btnSupprimerPub_2_clicked);
    connect(ui->BtnExportLabsDirect, &QPushButton::clicked, this, &MainWindow::on_BtnExportLabsDirect_clicked);

    connect(ui->BtnPopupCancelLabs_3, &QPushButton::clicked, this, [this](){ ui->stacked_L->setCurrentIndex(0); });
    connect(ui->BtnPopupCancelLabs_5, &QPushButton::clicked, this, [this](){ ui->stacked_L->setCurrentIndex(0); });
}
void MainWindow::onMapLocationSelected(const QString& title)
{
    if (title.contains(",") && title.contains(QRegularExpression("\\d"))) {
        ui->LabLocation_3->setText(title);
        ui->LabLocation_5->setText(title);
        QMessageBox::information(this, "Localisation", "Position capturée : " + title);
    }
}
// ====================== PAGE 2 – AJOUT ======================
void MainWindow::on_BtnPopupResetLabs_3_clicked()
{
    ui->LabName_3->clear();
    ui->LabResponsible_3->clear();
    ui->LabNumber_3->clear();
    ui->LabLocation_3->clear();
    ui->LabSpec_3->setCurrentIndex(0);
    ui->LabCap_3->setCurrentIndex(0);
    ui->LabSpec_4->setCurrentIndex(0);
    ui->LabCap_4->setCurrentIndex(0);
}

void MainWindow::on_BtnPopupSaveLabs_3_clicked()
{
    const QString nomLabo       = ui->LabName_3->text().trimmed();
    const QString responsable   = ui->LabResponsible_3->text().trimmed();
    const QString numero        = ui->LabNumber_3->text().trimmed();
    const QString localisation  = ui->LabLocation_3->text().trimmed();
    const QString specialite    = ui->LabSpec_3->currentText();
    const QString disponibilite = ui->LabCap_3->currentText();
    const QString resultat      = ui->LabSpec_4->currentText();
    const QString paiement      = ui->LabCap_4->currentText();

    if (nomLabo.isEmpty() || localisation.isEmpty() || responsable.isEmpty() || numero.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Veuillez remplir tous les champs texte !");
        return;
    }
    if (specialite.toLower().contains("choisir") || disponibilite.toLower().contains("choisir")
        || resultat.toLower().contains("choisir") || paiement.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez faire un choix valide dans toutes les listes déroulantes !");
        return;
    }

    Labs lab(nomLabo, responsable, numero, localisation, specialite, disponibilite, resultat, paiement, "1");
    QString err;
    if (!lab.ajouter(&err)) {
        QMessageBox::critical(this, "Échec de l'ajout", "Impossible d'ajouter le laboratoire :\n" + err);
        return;
    }

    QMessageBox::information(this, "Succès", "Laboratoire ajouté avec succès !");
    ui->stacked_L->setCurrentIndex(0);
    loadLabs();
    on_BtnPopupResetLabs_3_clicked();
}

// ====================== PAGE 1 – MODIFICATION ======================
void MainWindow::on_BtnPopupResetLabs_5_clicked()
{
    if (idLabsToEdit.isEmpty()) return;
    Labs::Row r;
    QString err;
    if (!Labs::getById(idLabsToEdit, r, &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }
    ui->LabName_5->setText(r.nomlabo);
    ui->LabResponsible_5->setText(r.responsable);
    ui->LabNumber_5->setText(r.numero);
    ui->LabLocation_5->setText(r.localisation);
    setComboValue(ui->LabCap_5,  r.disponibilite);
    setComboValue(ui->LabSpec_5, r.specialite);
    setComboValue(ui->LabSpec_6, r.resultat);
    setComboValue(ui->LabCap_6,  r.paiement);
}

void MainWindow::on_BtnPopupSaveLabs_5_clicked()
{
    if (idLabsToEdit.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun laboratoire sélectionné pour modification.");
        return;
    }

    const QString nomLabo       = ui->LabName_5->text().trimmed();
    const QString responsable   = ui->LabResponsible_5->text().trimmed();
    const QString numero        = ui->LabNumber_5->text().trimmed();
    const QString localisation  = ui->LabLocation_5->text().trimmed();
    const QString specialite    = ui->LabSpec_5->currentText();
    const QString disponibilite = ui->LabCap_5->currentText();
    const QString resultat      = ui->LabSpec_6->currentText();
    const QString paiement      = ui->LabCap_6->currentText();

    if (nomLabo.isEmpty() || localisation.isEmpty() || responsable.isEmpty() || numero.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Tous les champs textes sont obligatoires !");
        return;
    }
    if (specialite.toLower().contains("modifier") || disponibilite.toLower().contains("choisir")
        || resultat.toLower().contains("modifier") || paiement.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez faire un choix valide dans toutes les listes déroulantes !");
        return;
    }

    QString err;
    if (!Labs::modifier(idLabsToEdit, nomLabo, responsable, numero, localisation,
                        specialite, disponibilite, resultat, paiement, &err)) {
        QMessageBox::critical(this, "Erreur de modification", err);
        return;
    }

    QMessageBox::information(this, "Succès", "Laboratoire modifié avec succès !");
    idLabsToEdit.clear();
    ui->stacked_L->setCurrentIndex(0);
    loadLabs();
}

// ====================== PAGE 0 – SUPPRESSION ======================
void MainWindow::on_btnSupprimerPub_2_clicked()
{
    const int row = ui->TableLabs_2->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Supprimer", "Veuillez sélectionner un laboratoire.");
        return;
    }

    const QString id  = ui->TableLabs_2->item(row, 0)->text();
    const QString nom = ui->TableLabs_2->item(row, 1)->text();

    if (QMessageBox::question(this, "Confirmation",
                              QString("Voulez-vous vraiment supprimer le laboratoire :\n%1 (ID: %2) ?").arg(nom, id),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
        return;

    QString err;
    if (!Labs::supprimer(id, &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }

    QMessageBox::information(this, "Succès", "Laboratoire supprimé avec succès.");
    loadLabs();
}

// ====================== PAGE 0 – FILTRE / RECHERCHE ======================
void MainWindow::on_btnAppliquerPub_3_clicked()
{
    const QString key = ui->LabsSearch_2->text().trimmed().toLower();
    const QString spec = ui->LabsSpec_2->currentText().trimmed().toLower();
    const QString disp = ui->LabsCap_2->currentText().trimmed().toLower();

    // Désactiver le tri TEMPORAIREMENT pendant le filtrage
    ui->TableLabs_2->setSortingEnabled(false);

    int visibleCount = 0;

    for (int r = 0; r < ui->TableLabs_2->rowCount(); ++r) {
        // Récupérer les valeurs des colonnes
        QString id = "";
        QString nom = "";
        QString responsable = "";
        QString numero = "";
        QString localisation = "";
        QString disponibilite = "";
        QString specialite = "";
        QString resultat = "";
        QString paiement = "";

        if (ui->TableLabs_2->item(r, 0)) id = ui->TableLabs_2->item(r, 0)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 1)) nom = ui->TableLabs_2->item(r, 1)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 2)) responsable = ui->TableLabs_2->item(r, 2)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 3)) numero = ui->TableLabs_2->item(r, 3)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 4)) localisation = ui->TableLabs_2->item(r, 4)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 5)) disponibilite = ui->TableLabs_2->item(r, 5)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 6)) specialite = ui->TableLabs_2->item(r, 6)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 7)) resultat = ui->TableLabs_2->item(r, 7)->text().trimmed().toLower();
        if (ui->TableLabs_2->item(r, 8)) paiement = ui->TableLabs_2->item(r, 8)->text().trimmed().toLower();

        bool ok = true;

        // Filtre par recherche texte (recherche dans nom, responsable, numero, localisation)
        if (!key.isEmpty()) {
            ok = (nom.contains(key) || responsable.contains(key) ||
                  numero.contains(key) || localisation.contains(key));
        }

        // Filtre par spécialité (si différent de "choisir un specialite" ou "choisir un specialite")
        if (ok && !spec.isEmpty() && !spec.startsWith("choisir")) {
            ok = (specialite == spec);
        }

        // Filtre par disponibilité (si différent de "choisir disponibilite" ou "choisir le Disponabilite")
        if (ok && !disp.isEmpty() && !disp.startsWith("choisir")) {
            ok = (disponibilite == disp);
        }

        ui->TableLabs_2->setRowHidden(r, !ok);
        if (ok) visibleCount++;
        // Ajoutez ces qDebug() pour voir les valeurs
        qDebug() << "Recherche texte:" << key;
        qDebug() << "Spécialité sélectionnée:" << spec;
        qDebug() << "Disponibilité sélectionnée:" << disp;

        for (int r = 0; r < ui->TableLabs_2->rowCount(); ++r) {
            if (ui->TableLabs_2->item(r, 1)) {
                qDebug() << "Ligne" << r << "- Nom:" << ui->TableLabs_2->item(r, 1)->text();
                qDebug() << "Ligne" << r << "- Spécialité:" << (ui->TableLabs_2->item(r, 6) ? ui->TableLabs_2->item(r, 6)->text() : "vide");
                qDebug() << "Ligne" << r << "- Disponibilité:" << (ui->TableLabs_2->item(r, 5) ? ui->TableLabs_2->item(r, 5)->text() : "vide");
            }
        }
    }

    // RÉACTIVER le tri APRÈS le filtrage
    ui->TableLabs_2->setSortingEnabled(true);

    // Afficher un message si aucun résultat
    if (visibleCount == 0 && (!key.isEmpty() || !spec.startsWith("choisir") || !disp.startsWith("choisir"))) {
        QMessageBox::information(this, "Recherche", "Aucun laboratoire ne correspond à vos critères de recherche.");
    }
}
void MainWindow::on_btnReinitialiserPub_3_clicked()
{
    // Vider les champs de recherche
    ui->LabsSearch_2->clear();
    ui->LabsSpec_2->setCurrentIndex(0);  // "choisir un specialite"
    ui->LabsCap_2->setCurrentIndex(0);   // "Choisir disponibilite"

    // Désactiver le tri TEMPORAIREMENT
    ui->TableLabs_2->setSortingEnabled(false);

    // Afficher toutes les lignes
    for (int r = 0; r < ui->TableLabs_2->rowCount(); ++r) {
        ui->TableLabs_2->setRowHidden(r, false);
    }

    // RÉACTIVER le tri
    ui->TableLabs_2->setSortingEnabled(true);

    qDebug() << "Filtres réinitialisés, toutes les lignes sont visibles";
}
// ====================== PAGE 1 – OUVRIR MODIFIER ======================
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

    ui->LabName_5->setText(ui->TableLabs_2->item(r, 1)->text());
    ui->LabResponsible_5->setText(ui->TableLabs_2->item(r, 2)->text());
    ui->LabNumber_5->setText(ui->TableLabs_2->item(r, 3)->text());
    ui->LabLocation_5->setText(ui->TableLabs_2->item(r, 4)->text());

    setComboValue(ui->LabCap_5,  ui->TableLabs_2->item(r, 5)->text()); // Disponibilité
    setComboValue(ui->LabSpec_5, ui->TableLabs_2->item(r, 6)->text()); // Spécialité
    setComboValue(ui->LabSpec_6, ui->TableLabs_2->item(r, 7)->text()); // Résultat
    setComboValue(ui->LabCap_6,  ui->TableLabs_2->item(r, 8)->text()); // Paiement

    ui->stacked_L->setCurrentIndex(1);
}

// ====================== PAGE 4 – AFFICHER DÉTAIL ======================
void MainWindow::on_btnAjouterPub_3_clicked()
{
    const int r = ui->TableLabs_2->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Afficher", "Sélectionne un laboratoire à afficher.");
        return;
    }

    ui->aff1->setText(ui->TableLabs_2->item(r, 1)->text()); // Nom
    ui->aff5->setText(ui->TableLabs_2->item(r, 2)->text()); // Responsable
    ui->aff6->setText(ui->TableLabs_2->item(r, 3)->text()); // Numéro
    ui->aff2->setText(ui->TableLabs_2->item(r, 4)->text()); // Localisation

    setComboValue(ui->aff7,   ui->TableLabs_2->item(r, 5)->text()); // Disponibilité
    setComboValue(ui->aff3,   ui->TableLabs_2->item(r, 6)->text()); // Spécialité
    setComboValue(ui->aff3_2, ui->TableLabs_2->item(r, 7)->text()); // Résultat
    setComboValue(ui->aff7_2, ui->TableLabs_2->item(r, 8)->text()); // Paiement

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
    for (const auto &row : std::as_const(rows)) {
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

// ====================== MODIFICATION ======================
void MainWindow::on_BtnInventoryEdit_clicked()
{
    int row = ui->TableLabs_2->currentRow();

    // Vérification si aucune ligne n'est sélectionnée
    if (row < 0) {
        QMessageBox::warning(this, "Modifier", "Veuillez sélectionner un laboratoire dans le tableau.");
        return;
    }

    // Récupération sécurisée de l'ID
    QTableWidgetItem *item = ui->TableLabs_2->item(row, 0);
    if (!item || item->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Erreur", "ID introuvable (colonne ID vide).");
        return;
    }

    idLabsToEdit = item->text().trimmed();

    Labs::Row r;
    QString err;

    if (!Labs::getById(idLabsToEdit, r, &err)) {
        QMessageBox::critical(this, "Erreur",
                              "ID introuvable dans la base de données.\n\nDétail : " + err);
        idLabsToEdit.clear();
        return;
    }

    // Pré-remplissage du formulaire de modification
    ui->aff1->setText(r.nomlabo);           // Nom Laboratoire
    ui->aff2->setText(r.localisation);
    ui->aff3->setCurrentText(r.specialite);
    ui->aff7->setCurrentText(r.disponibilite);
    ui->aff3_2->setCurrentText(r.resultat);
    ui->aff7_2->setCurrentText(r.paiement);

    ui->stacked_I->setCurrentIndex(2);      // Page Modification
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
    for (const auto &row : std::as_const(rows)) {
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









