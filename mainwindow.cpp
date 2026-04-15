#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ocrscanner.h"
#include "session.h"  // <--- INDISPENSABLE pour lire le rôle
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QEasingCurve>
#include "projet.h"
#include <QGraphicsDropShadowEffect>
#include <QDir>
#include "finance.h"
#include "labs.h"
#include "employe.h"
#include "inventory.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QAbstractSpinBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QApplication>
#include <QMessageBox>
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
#include "mapdialog.h"
#include <QTime>
#include <QCryptographicHash>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QClipboard>

#include <QMouseEvent>
#include "publication.h"

#include <QLayout>

#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>








#include "mailsender.h"
#include <QLabel>
#include <QProgressBar>
#include "currencyconverter.h"
#include <QInputDialog>
#include <QSettings>
#include <QFile>
#include <QRandomGenerator>



#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>

#include <QBuffer>
#include <QScrollArea>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkRequest>


#include <QCamera>
#include <QImageCapture>  // <-- En Qt 6, c'est QImageCapture (sans "Camera")
#include <QMediaDevices>  // Utile pour trouver la caméra par défaut
#include <QMediaCaptureSession> // NOUVEAU en Qt 6 : c'est le "cerveau" qui lie tout
#include <QTimer>
#include <QEventLoop>

class QProgressBar;
class QLabel;
static void updatePasswordStrengthUiAddEmp(const QString &, QProgressBar *, QLabel *);





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

static bool inventorySkuExists(const QString &sku, const QString &excludeId = QString())
{
    if (sku.trimmed().isEmpty()) return false;
    QSqlQuery q;
    QString sql = "SELECT COUNT(*) FROM PRODUCT WHERE UPPER(TRIM(SKU)) = :sku";
    if (!excludeId.trimmed().isEmpty()) {
        sql += " AND TO_CHAR(ID_PRODUCT) <> :id";
    }
    q.prepare(sql);
    q.bindValue(":sku", sku.trimmed().toUpper());
    if (!excludeId.trimmed().isEmpty()) {
        q.bindValue(":id", excludeId.trimmed());
    }
    if (!q.exec() || !q.next()) return false;
    return q.value(0).toInt() > 0;
}

static QString normalizeSkuInput(const QString &raw)
{
    // Keep only alnum chars, force uppercase, and shape as AAA-999.
    QString compact;
    compact.reserve(raw.size());
    for (const QChar ch : raw.toUpper()) {
        if (ch.isLetterOrNumber()) compact += ch;
    }

    QString letters;
    QString digits;
    letters.reserve(3);
    digits.reserve(3);
    for (const QChar ch : compact) {
        if (letters.size() < 3) {
            if (ch.isLetter()) letters += ch;
            continue;
        }
        if (digits.size() < 3 && ch.isDigit()) {
            digits += ch;
        }
    }

    QString out = letters;
    if (letters.size() == 3 && (!digits.isEmpty() || compact.size() > 3)) {
        out += '-';
    }
    out += digits;
    return out.left(7);
}

static QString generateTxCode(const QString &type, const QString &mode)
{
    const QString datePart = QDate::currentDate().toString("yyyyMMdd");
    const QString typePart = (type == "Revenu") ? "REV" : "DEP";
    QString modePart = "ESP";
    if (mode == "virement") modePart = "VIR";
    else if (mode == "cheque") modePart = "CHQ";
    else if (mode == "carte_bancaire") modePart = "CB";
    else if (mode == "facture") modePart = "FAC";
    else if (mode == "remboursement") modePart = "RMB";

    for (int i = 1; i <= 9999; ++i) {
        const QString candidate = QString("%1-%2-%3-%4")
                                      .arg(typePart, modePart, datePart, QString::number(i).rightJustified(4, '0'));
        QSqlQuery q;
        q.prepare("SELECT COUNT(*) FROM FINANCE WHERE CODETRANSA = :code");
        q.bindValue(":code", candidate);
        if (q.exec() && q.next() && q.value(0).toInt() == 0) {
            return candidate;
        }
    }
    return QString("%1-%2-%3-%4")
        .arg(typePart, modePart, datePart, QString::number(QRandomGenerator::global()->bounded(1000, 9999)));
}

static void drawRect(QPainter& p, const QRect& r) { p.drawRect(r); }

// ─────────────────────────────────────────────────────────────────────────────
// ProportionalScaler : rend responsive une page à positionnement absolu.
// Installe un event filter sur le conteneur (QGroupBox) et redimensionne
// ses enfants proportionnellement à chaque resize.
// ─────────────────────────────────────────────────────────────────────────────
class ProportionalScaler : public QObject {
    QWidget *m_box;
    QSize    m_origSize;
    QList<QPair<QWidget*, QRect>> m_origGeos;
    QList<QPair<QWidget*, qreal>> m_origFonts;

public:
    explicit ProportionalScaler(QWidget *box, QObject *parent = nullptr)
        : QObject(parent), m_box(box)
    {
        m_origSize = box->size();
        for (auto *child : box->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
            m_origGeos.append({ child, child->geometry() });
            m_origFonts.append({ child, child->font().pointSizeF() });
        }
        box->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj != m_box || event->type() != QEvent::Resize) return false;
        if (m_origSize.isEmpty()) return false;

        const QSize newSize = m_box->size();
        const qreal xR = (qreal)newSize.width()  / m_origSize.width();
        const qreal yR = (qreal)newSize.height() / m_origSize.height();
        const qreal fR = qMin(xR, yR);

        for (auto &pair : m_origGeos) {
            QWidget *w = pair.first;
            if (!w) continue;
            const QRect &orig = pair.second;
            w->setGeometry(
                qRound(orig.x()      * xR),
                qRound(orig.y()      * yR),
                qRound(orig.width()  * xR),
                qRound(orig.height() * yR)
            );
        }
        for (auto &pair : m_origFonts) {
            QWidget *w = pair.first;
            if (!w) continue;
            QFont f = w->font();
            f.setPointSizeF(qMax(7.0, pair.second * fR));
            w->setFont(f);
        }
        return false;
    }
};

// Rend une page responsive : met le QGroupBox dans un layout + installe le scaler
static void makePageResponsive(QWidget *page)
{
    if (page->layout()) return; // déjà un layout

    QGroupBox *gb = page->findChild<QGroupBox*>(QString(), Qt::FindDirectChildrenOnly);
    if (!gb) return;

    // Scaler pour les enfants du groupBox (positionnement absolu)
    new ProportionalScaler(gb, gb);

    // Layout qui étire le groupBox à la taille de la page
    auto *layout = new QVBoxLayout(page);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(gb);
}

// ==================== LABS HELPERS ====================
// (makeQrLabs supprimé : la colonne QRLABS n'existe pas dans la table)


MainWindow::MainWindow(Arduino *arduino, QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // ─── Récupérer le pointeur Arduino connecté depuis main.cpp ──────────────
    A = arduino;

    // On installe le filtre sur le champ de localisation
    ui->setupUi(this);
    // Initialisation du manager réseau
    networkManager = new QNetworkAccessManager(this);

    // C'est cette ligne qui fait tout le travail invisible !
    this->lancerServeurIA();

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

    // 1. Créer un validateur qui n'accepte que les chiffres (0-9)
    // La regex [0-9]* signifie : autoriser n'importe quelle quantité de chiffres uniquement
    QRegularExpressionValidator *chiffresSeulement = new QRegularExpressionValidator(QRegularExpression("[0-9]*"), this);

    // 2. Appliquer le validateur aux champs
    ui->lineCINAdd->setValidator(chiffresSeulement);
    ui->lineCIN_emp->setValidator(chiffresSeulement);

    // 3. Limiter la longueur à 8 (pour éviter de dépasser la taille du CIN)
    ui->lineCINAdd->setMaxLength(8);
    ui->lineCIN_emp->setMaxLength(8);

    // 4. Supprimer l'InputMask pour éviter les barres verticales/soulignements
    ui->lineCINAdd->setInputMask("");
    ui->lineCIN_emp->setInputMask("");
    // Dans le constructeur de votre MainWindow
    ui->dateEmbaucheAdd->setCalendarPopup(true);
    ui->dateEmbaucheEmp->setCalendarPopup(true);

    // Optionnel : Définir la date actuelle par défaut au lieu de 1/1/2000
    ui->dateEmbaucheAdd->setDate(QDate::currentDate());
    ui->dateEmbaucheEmp->setDate(QDate::currentDate());

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





    // ── Système de notifications ──────────────────────────────────────────
    setupNotifButton();





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
    initProjetsUi();

    // --- Explicit project button connections ---
    connect(ui->btnAjouterProj,          &QPushButton::clicked, this, &MainWindow::on_btnAjouterProj_clicked);
    connect(ui->btnModifierProj,         &QPushButton::clicked, this, &MainWindow::on_btnModifierProj_clicked);
    connect(ui->btnSupprimerProj,        &QPushButton::clicked, this, &MainWindow::on_btnSupprimerProj_clicked);
    connect(ui->btnAddProj,              &QPushButton::clicked, this, &MainWindow::on_btnAddProj_clicked);
    connect(ui->btnConfirmEditProj,      &QPushButton::clicked, this, &MainWindow::on_btnConfirmEditProj_clicked);
    connect(ui->btnRetourAddProj,        &QPushButton::clicked, this, &MainWindow::on_btnRetourAddProj_clicked);
    connect(ui->btnRetourEditProj,       &QPushButton::clicked, this, &MainWindow::on_btnRetourEditProj_clicked);
    connect(ui->btnAppliquerProj,        &QPushButton::clicked, this, &MainWindow::on_btnAppliquerProj_clicked);
    connect(ui->btnFiltrerDateProj,      &QPushButton::clicked, this, &MainWindow::on_btnFiltrerDateProj_clicked);
    connect(ui->btnVoirStatistiquesProj, &QPushButton::clicked, this, &MainWindow::on_btnVoirStatistiquesProj_clicked);

    // --- Connexions Signaux/Slots ---
    connect(ui->linePasswordAdd, &QLineEdit::textChanged, this, [this](const QString &t) {
        updatePasswordStrengthUiAddEmp(t, ui->passwordStrengthBarAdd, ui->passwordStrengthLabelAdd);
    });
    updatePasswordStrengthUiAddEmp(QString(), ui->passwordStrengthBarAdd, ui->passwordStrengthLabelAdd);
    initEmployeUserGuidance();
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

    // NOTE: Ne pas appliquer QGraphicsEffect sur sidebarFrame NI sur stackedWidget —
    // un QGraphicsEffect sur un widget PARENT empêche les effets enfants (opacité,
    // glow, ripple) de se composer correctement : tout passe par un buffer offscreen
    // partagé et les rendus entrent en conflit. L'ombre est reproduite en CSS.

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
    connect(ui->btnAnnuler_emp, &QPushButton::clicked,
            this, &MainWindow::on_btnAnnuler_emp_clicked);
    connect(ui->BtnPopupCancelLabs_8, &QPushButton::clicked,
            this, &MainWindow::on_BtnPopupCancelLabs_8_clicked);
    connect(ui->BtnPopupCancelLabs_10, &QPushButton::clicked,
            this, &MainWindow::on_BtnPopupCancelLabs_10_clicked);
    networkManager = new QNetworkAccessManager(this);

    // ─── Rendre responsive toutes les pages à positionnement absolu ─────────
    // makePageResponsive est sans danger sur les pages avec layout (retour immédiat)
    QTimer::singleShot(0, this, [this]() {
        // Employé (nommées explicitement)
        makePageResponsive(ui->page_add_Emp);
        makePageResponsive(ui->page_Edit_Emp);
        makePageResponsive(ui->page_Stat);
        makePageResponsive(ui->page_conge);
        makePageResponsive(ui->page_formation);
        makePageResponsive(ui->page);

        // Tous les autres stacks : Publication, Projets, Finance, Inventory, Labs
        auto makeStackResponsive = [](QStackedWidget *sw) {
            if (!sw) return;
            for (int i = 0; i < sw->count(); ++i)
                makePageResponsive(sw->widget(i));
        };
        makeStackResponsive(ui->stack_pub);
        makeStackResponsive(ui->stack_proj);
        makeStackResponsive(ui->stacked_F);
        makeStackResponsive(ui->stacked_I);
        makeStackResponsive(ui->stacked_L);
    });

    // ─── Bouton hamburger : créé ICI (avant show) pour éviter le glitch d'affichage ───
    m_btnToggleSidebar = new QPushButton("\u2630", ui->topBar);
    m_btnToggleSidebar->setObjectName("btnToggleSidebar");
    m_btnToggleSidebar->setFixedSize(36, 36);
    m_btnToggleSidebar->setFocusPolicy(Qt::NoFocus);
    m_btnToggleSidebar->setCursor(Qt::PointingHandCursor);
    m_btnToggleSidebar->setToolTip("Masquer / Afficher la sidebar");
    {
        const int th = ui->topBar->height();
        m_btnToggleSidebar->move(14, qMax(0, (th - 36) / 2));
        ui->lblBrand->adjustSize();
        ui->lblBrand->move(58, qMax(0, (th - ui->lblBrand->height()) / 2));
    }
    m_btnToggleSidebar->show();
    connect(m_btnToggleSidebar, &QPushButton::clicked, this, &MainWindow::toggleSidebar);

    // ─── Forcer le bon positionnement de la topBar + scaling initial ─────────
    // On attend 1 tick pour que Qt ait calculé la vraie taille de la fenêtre.
    QTimer::singleShot(0, this, [this]() {
        if (ui && ui->topBar) {
            QResizeEvent re(size(), QSize());
            resizeEvent(&re);
        }
        // Premier scaling QSS (fenêtre à sa taille initiale/maximale)
        updateScaledQss();
    });

    // ─── Animations ───────────────────────────────────────────────────────────
    QTimer::singleShot(50, this, [this]() { initAnimations(); });

    // ─── Arduino RFID ─────────────────────────────────────────────────────────
    // La logique RFID est gérée par RfidHandler (actif avant le login).
    // MainWindow reçoit juste le signal pointageEffectue via onPointageRfid()
    // pour rafraîchir le tableau employés. Connexion faite dans main.cpp.
}






void MainWindow::on_btnStat_emp_clicked()
{
    // 1. DÉTERMINATION DE LA PÉRIODE (Janvier à Aujourd'hui)
    QDate dateActuelle = QDate::currentDate();
    int moisFin = dateActuelle.month(); // ex: 4 pour Avril
    int annee = dateActuelle.year();

    // Noms des mois en français pour le titre
    QString nomMoisDebut = QLocale(QLocale::French).monthName(1); // Janvier
    QString nomMoisFin = QLocale(QLocale::French).monthName(moisFin); // Avril

    // 2. RÉCUPÉRATION DES DONNÉES SQL
    QSqlQuery query;
    query.prepare("SELECT NOM, NVL(NB_ABSENCES, 0) AS TOTAL FROM EMPLOYES ORDER BY TOTAL DESC");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    // 3. PRÉPARATION DES SÉRIES GRAPHIQUES
    QBarSet *setNormal = new QBarSet("Taux sous le seuil (Ok)");
    QBarSet *setAlerte = new QBarSet("Taux Critique (>15%)");

    setNormal->setColor(QColor(127, 255, 212)); // Aquamarine
    setAlerte->setColor(QColor(255, 69, 0));     // Orange-Rouge vif

    QStringList categories;
    double diviseurMois = (moisFin > 0) ? static_cast<double>(moisFin) : 1.0;

    while (query.next()) {
        QString nom = query.value("NOM").toString();
        int totalAbs = query.value("TOTAL").toInt();

        // CALCUL PRÉCIS : (Total / Nb de mois) / 22 jours ouvrés * 100
        double taux = ((totalAbs / diviseurMois) / 22.0) * 100.0;
        taux = qRound(taux * 10.0) / 10.0; // Arrondi à 1 chiffre après la virgule

        categories << nom;

        // Segmentation visuelle
        if (taux >= 15.0) {
            *setAlerte << taux;
            *setNormal << 0;
        } else {
            *setNormal << taux;
            *setAlerte << 0;
        }
    }

    // 4. CONFIGURATION DU GRAPH (DÉTAILS MAXIMUM)
    QBarSeries *series = new QBarSeries();
    series->append(setNormal);
    series->append(setAlerte);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd); // Chiffres en haut
    series->setLabelsFormat("@value %");

    QChart *chart = new QChart();
    chart->addSeries(series);

    // Titre ultra-précis
    chart->setTitle(QString("<b>ANALYSE RH DÉTAILLÉE</b><br>"
                            "Période : %1 - %2 %3 | Base : 22j/mois")
                    .arg(nomMoisDebut).arg(nomMoisFin).arg(annee));

    // Ligne de seuil (Alerte Visuelle)
    QLineSeries *limitLine = new QLineSeries();
    limitLine->setName("Seuil Critique RH (15%)");
    limitLine->setPen(QPen(Qt::red, 3, Qt::DashLine));
    for(int i=0; i<categories.count(); ++i) limitLine->append(i, 15);
    chart->addSeries(limitLine);

    // 5. AXES DÉTAILLÉS
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Liste des Employés");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    limitLine->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setLabelFormat("%i%");
    axisY->setTitleText("Taux d'Absentéisme (%)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    limitLine->attachAxis(axisY);

    // 6. RENDU FINAL
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(1000, 600);
    chartView->setWindowTitle("Système Vortex - Rapport Statistiques");
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

// ─── Slot Arduino RFID : traiter les données reçues sur le port série ─────────
// Protocole Arduino → Qt  :  "UID:<hex_uid>:<id_labo>\n"
// Protocole Qt → Arduino  :  "1:<prenom>:<HH:MM>\n"   (accès OK)
//                             "0\n"                    (accès refusé)
void MainWindow::traiter_rfid()
{
    // Accumuler les octets reçus dans le tampon
    if (!A) return;
    rfidBuffer += A->read_from_arduino();

    // Traiter toutes les lignes complètes (terminées par \n)
    while (rfidBuffer.contains('\n')) {
        int idx = rfidBuffer.indexOf('\n');
        QByteArray ligne = rfidBuffer.left(idx).trimmed();
        rfidBuffer = rfidBuffer.mid(idx + 1);

        if (ligne.isEmpty()) continue;

        QString message = QString::fromUtf8(ligne);
        qDebug() << "[RFID] Reçu :" << message;

        // ── Vérifier que le message commence par "UID:" ─────────────────────
        if (!message.startsWith("UID:")) continue;

        // ── Parser  "UID:<hex_uid>:<id_labo>" ───────────────────────────────
        QStringList parts = message.split(':');
        // parts[0]="UID"  parts[1]=hex_uid  parts[2]=id_labo
        if (parts.size() < 3) {
            qDebug() << "[RFID] Format invalide :" << message;
            A->write_to_arduino("0\n");
            continue;
        }

        QString uidCarte = parts[1].trimmed().toUpper();
        QString idLabo   = parts[2].trimmed();

        // ── Requête : l'employé porteur de cette carte a-t-il accès à ce labo ?
        QSqlQuery q;
        // Utilise les tables existantes : EMPLOYES + LABS (via IDEMP)
        // L'employé doit avoir la carte ET être responsable de ce labo
        q.prepare(
            "SELECT e.ID_EMPLOYE, e.PRENOM "
            "FROM HICHEM.EMPLOYES e "
            "JOIN HICHEM.LABS l ON l.IDEMP = e.ID_EMPLOYE "
            "WHERE e.UID_CARTE = :uid AND l.IDLABO = :labo"
        );
        q.bindValue(":uid",  uidCarte);
        q.bindValue(":labo", idLabo);

        if (!q.exec()) {
            qDebug() << "[RFID] Erreur SQL :" << q.lastError().text();
            A->write_to_arduino("0\n");
            continue;
        }

        if (q.next()) {
            // ── Accès autorisé ───────────────────────────────────────────────
            QString idEmploye = q.value("ID_EMPLOYE").toString();
            QString prenom    = q.value("PRENOM").toString();
            QString heure     = QTime::currentTime().toString("HH:mm");
            QString date      = QDate::currentDate().toString("yyyy-MM-dd");

            // Enregistrer le pointage dans la base
            QSqlQuery upd;
            upd.prepare(
                "UPDATE HICHEM.EMPLOYES "
                "SET DATE_POINTAGE    = TO_DATE(:d, 'YYYY-MM-DD'), "
                "    HEURE_ARRIVEE    = :h, "
                "    STATUT_JOURNALIER = 'Présent' "
                "WHERE ID_EMPLOYE = :id"
            );
            upd.bindValue(":d",  date);
            upd.bindValue(":h",  heure);
            upd.bindValue(":id", idEmploye);

            if (upd.exec()) {
                qDebug() << "[RFID] Pointage enregistré pour" << prenom << "à" << heure;
            } else {
                qDebug() << "[RFID] Erreur UPDATE pointage :" << upd.lastError().text();
            }

            // Envoyer la confirmation à l'Arduino : "1:Prenom:HH:MM\n"
            // L'Arduino affichera sur LCD :
            //   Ligne 1 : "Bienvenue Prenom"
            //   Ligne 2 : "Pointe a HH:MM"
            QString reponse = QString("1:%1:%2\n").arg(prenom, heure);
            A->write_to_arduino(reponse.toUtf8());

            // Rafraîchir le tableau employés dans l'UI
            model->setQuery(
                "SELECT CIN, NOM, PRENOM, USERNAME, DATE_POINTAGE, "
                "HEURE_ARRIVEE, HEURE_DEPART, STATUT_JOURNALIER FROM EMPLOYES"
            );

        } else {
            // ── Accès refusé ─────────────────────────────────────────────────
            qDebug() << "[RFID] Accès refusé pour UID" << uidCarte << "labo" << idLabo;
            A->write_to_arduino("0\n");
        }
    }
}

// ─── Slot appelé par RfidHandler quand un pointage RFID réussit ──────────────
// Rafraîchit le tableau employés dans l'interface
void MainWindow::onPointageRfid(const QString &prenom, const QString &heure)
{
    qDebug() << "[MainWindow] Pointage RFID reçu :" << prenom << "à" << heure;
    model->setQuery(
        "SELECT CIN, NOM, PRENOM, USERNAME, DATE_POINTAGE, "
        "HEURE_ARRIVEE, HEURE_DEPART, STATUT_JOURNALIER FROM EMPLOYES"
    );
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    // ── Fermer le panneau de notifications si clic en dehors ─────────────
    if (m_notifPanel && m_notifPanel->isVisible()
        && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        QPoint gPos = me->globalPosition().toPoint();
        QRect panelRect(m_notifPanel->mapToGlobal(QPoint(0,0)), m_notifPanel->size());
        QRect btnRect(ui->btnNotif->mapToGlobal(QPoint(0,0)), ui->btnNotif->size());
        if (!panelRect.contains(gPos) && !btnRect.contains(gPos)) {
            m_notifPanel->hide();
        }
    }

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

    // Définition de tous les modules : bouton | emoji | label | page index
    struct BtnDef {
        QPushButton *btn;
        QString icon;
        QString label;
        int pageIndex;
    };
    const QList<BtnDef> allBtns = {
        { ui->btnEmployee,     "\U0001F464", "Employés",      0 },
        { ui->btnInventaire,   "\U0001F4E6", "Inventaire",    1 },
        { ui->btnPublication,  "\U0001F4C4", "Publications",  2 },
        { ui->btnFinance,      "\U0001F4B0", "Finance",       3 },
        { ui->btnLaboratoires, "\U0001F52C", "Laboratoires",  4 },
        { ui->btnProjets,      "\U0001F4CB", "Projets",       5 },
    };

    // Droits selon le rôle
    QList<QPushButton*> authorized;
    QPushButton *defaultBtn = ui->btnEmployee;
    int defaultPage = 0;

    if (role == "Admin") {
        for (const auto &b : allBtns) authorized << b.btn;
        defaultBtn  = ui->btnEmployee;
        defaultPage = 0;
    } else if (role == "RH") {
        authorized  = { ui->btnEmployee };
        defaultBtn  = ui->btnEmployee;
        defaultPage = 0;
    } else if (role == "Responsable_financier") {
        authorized  = { ui->btnFinance };
        defaultBtn  = ui->btnFinance;
        defaultPage = 3;
    } else if (role == "Responsable_de_stock") {
        authorized  = { ui->btnInventaire };
        defaultBtn  = ui->btnInventaire;
        defaultPage = 1;
    } else if (role == "Responsable_Labos") {
        authorized  = { ui->btnLaboratoires };
        defaultBtn  = ui->btnLaboratoires;
        defaultPage = 4;
    } else if (role == "Chercheur") {
        authorized  = { ui->btnPublication };
        defaultBtn  = ui->btnPublication;
        defaultPage = 2;
    } else if (role == "Directeur_de_projet") {
        authorized  = { ui->btnProjets, ui->btnPublication };
        defaultBtn  = ui->btnProjets;
        defaultPage = 5;
    }

    // Afficher TOUS les boutons — activer les autorisés, verrouiller les autres
    for (const auto &b : allBtns) {
        bool auth = authorized.contains(b.btn);
        b.btn->setVisible(true);
        b.btn->setEnabled(auth);
        if (auth) {
            b.btn->setText(b.icon + "  " + b.label);
            b.btn->setToolTip(QString());
        } else {
            b.btn->setText("\U0001F512  " + b.label);
            b.btn->setToolTip("Accès réservé — votre rôle ne permet pas d'accéder à ce module.");
        }
        b.btn->style()->unpolish(b.btn);
        b.btn->style()->polish(b.btn);
    }

    ui->stackedWidget->setCurrentIndex(defaultPage);
    setActiveButton(defaultBtn);
    updateTopTitle(ui->stackedWidget->currentIndex());
}




//fin fct
void MainWindow::genererScriptPython()
{
    // On définit le chemin : là où se trouve l'exécutable
    QString cheminScript = QCoreApplication::applicationDirPath() + "/face_id_vortex.py";
    QFile file(cheminScript);

    // On écrit le fichier (On l'écrase à chaque fois pour être sûr qu'il est à jour)
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // C'est ici que tu mets ton code Python exact
        out << "import cv2\n";
        out << "import sys\n";
        out << "try:\n";
        out << "    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')\n";
        out << "    cap = cv2.VideoCapture(0)\n";
        out << "    while True:\n";
        out << "        ret, frame = cap.read()\n";
        out << "        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)\n";
        out << "        faces = face_cascade.detectMultiScale(gray, 1.1, 4)\n";
        out << "        for (x, y, w, h) in faces:\n";
        out << "            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)\n";
        out << "        cv2.imshow('FaceID - Systeme Vortex', frame)\n";
        out << "        if cv2.waitKey(1) & 0xFF == ord('q'): break\n";
        out << "    cap.release()\n";
        out << "    cv2.destroyAllWindows()\n";
        out << "except Exception as e:\n";
        out << "    print(f'Erreur: {e}')\n";

        file.close();
    }
}

MainWindow::~MainWindow()
{
    if (processIA) {
            processIA->terminate(); // Tue le processus Python proprement
            processIA->waitForFinished(2000);
        }
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (!ui || !ui->topBar) return;

    const int w = ui->topBar->width();
    const int h = ui->topBar->height();

    // btnToggleSidebar : tout à gauche de la topBar
    ui->lblBrand->adjustSize(); // auto-fit width so "Lab" is never clipped
    if (m_btnToggleSidebar) {
        m_btnToggleSidebar->move(14, qMax(0, (h - 36) / 2));
        // lblBrand se décale à droite du bouton toggle
        ui->lblBrand->move(58, qMax(0, (h - ui->lblBrand->height()) / 2));
    } else {
        ui->lblBrand->move(14, (h - ui->lblBrand->height()) / 2);
    }

    // lblPageTitle : centré horizontalement dans la topBar
    ui->lblPageTitle->move(
        (w - ui->lblPageTitle->width()) / 2,
        (h - ui->lblPageTitle->height()) / 2);

    // btnNotif : aligné à droite avec marge de 10px
    const int btnNx = w - ui->btnNotif->width() - 10;
    const int btnNy = (h - ui->btnNotif->height()) / 2;
    ui->btnNotif->move(btnNx, btnNy);

    // Badge : coin supérieur-droit du bouton
    if (m_notifBadge) {
        m_notifBadge->move(btnNx + ui->btnNotif->width() - 10, btnNy - 5);
        m_notifBadge->raise();
    }

    // Mettre à jour la position de l'indicateur actif après resize
    if (m_activeIndicator) {
        const QList<QPushButton*> nav = {
            ui->btnEmployee, ui->btnInventaire, ui->btnPublication,
            ui->btnFinance, ui->btnLaboratoires, ui->btnProjets
        };
        for (auto *btn : nav) {
            if (btn->property("active").toBool()) {
                QPoint p = btn->mapTo(ui->sidebarFrame, QPoint(0, 0));
                m_activeIndicator->setGeometry(p.x(), p.y(), 4, btn->height());
                break;
            }
        }
    }

    // Vignette : toujours la taille de la fenêtre entière, au-dessus de tout
    if (m_vignetteOverlay) {
        m_vignetteOverlay->resize(size());
        m_vignetteOverlay->raise();
    }

    // ─── Scaling QSS proportionnel (debounce 80 ms) ──────────────────────────
    // On ne régénère pas le QSS à chaque pixel de resize : on attend la fin du
    // geste, ce qui évite les ralentissements tout en garantissant le résultat.
    if (!m_fontScaleTimer) {
        m_fontScaleTimer = new QTimer(this);
        m_fontScaleTimer->setSingleShot(true);
        connect(m_fontScaleTimer, &QTimer::timeout, this, &MainWindow::updateScaledQss);
    }
    m_fontScaleTimer->start(80);
}

// ─────────────────────────────────────────────────────────────────────────────
// VignetteOverlay — vignette néon respirante sur toute la fenêtre
// ─────────────────────────────────────────────────────────────────────────────
class VignetteOverlay : public QWidget {
    float m_phase = 0.0f;
    bool  m_dark;
public:
    explicit VignetteOverlay(QWidget *parent, bool dark) : QWidget(parent), m_dark(dark) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
        setAutoFillBackground(false);
        setStyleSheet("background: transparent;");

        auto *t = new QTimer(this);
        connect(t, &QTimer::timeout, this, [this]() {
            m_phase += 0.007f;
            if (m_phase > 6.2832f) m_phase = 0.0f;
            update();
        });
        t->start(40); // ~25 fps — léger et suffisant pour un effet breathing
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        const float pulse = (qSin(m_phase) + 1.0f) * 0.5f; // 0 → 1
        const int   a     = static_cast<int>(4 + pulse * 14); // 4 → 18

        // Couleur néon selon le thème
        const QColor c = m_dark
            ? QColor(14, 165, 233, a)
            : QColor(31, 142, 149, a);

        // Dégradé radial depuis chaque coin → effet vignette 4 coins
        const double r = qMax(width(), height()) * 0.60;
        const struct { double x, y; } corners[] = {
            {0.0,           0.0},
            {(double)width(), 0.0},
            {0.0,           (double)height()},
            {(double)width(), (double)height()}
        };
        for (const auto &corner : corners) {
            QRadialGradient g(corner.x, corner.y, r);
            g.setColorAt(0.00, c);
            g.setColorAt(0.55, QColor(c.red(), c.green(), c.blue(), a / 4));
            g.setColorAt(1.00, QColor(0, 0, 0, 0));
            painter.fillRect(rect(), g);
        }
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// HoverGlowHelper — event filter qui anime le glow d'un bouton sidebar
// ─────────────────────────────────────────────────────────────────────────────
class HoverGlowHelper : public QObject {
    QGraphicsDropShadowEffect *m_eff;
    QPropertyAnimation        *m_anim;
public:
    HoverGlowHelper(QGraphicsDropShadowEffect *eff, QPropertyAnimation *anim, QObject *parent)
        : QObject(parent), m_eff(eff), m_anim(anim) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        Q_UNUSED(obj)
        if (event->type() == QEvent::Enter) {
            m_anim->stop();
            m_anim->setStartValue(m_eff->blurRadius());
            m_anim->setEndValue(32.0);
            m_anim->start();
        } else if (event->type() == QEvent::Leave) {
            m_anim->stop();
            m_anim->setStartValue(m_eff->blurRadius());
            m_anim->setEndValue(0.0);
            m_anim->start();
        }
        return false;
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// initAnimations : démarre toutes les animations de l'interface
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::initAnimations()
{
    // ── 1. Slide-in sidebar au démarrage ─────────────────────────────────────
    const int maxW = 260;
    const int minW = 240;
    ui->sidebarFrame->setMaximumWidth(0);
    ui->sidebarFrame->setMinimumWidth(0);

    const QList<QPushButton*> navBtns = {
        ui->btnEmployee, ui->btnInventaire, ui->btnPublication,
        ui->btnFinance, ui->btnLaboratoires, ui->btnProjets
    };

    // Masquer les boutons nav + logo pour la stagger animation d'entrée
    for (auto *btn : navBtns) {
        auto *eff = new QGraphicsOpacityEffect(btn);
        eff->setOpacity(0.0);
        btn->setGraphicsEffect(eff);
    }
    {
        auto *eff = new QGraphicsOpacityEffect(ui->logoLabel);
        eff->setOpacity(0.0);
        ui->logoLabel->setGraphicsEffect(eff);
    }

    auto *animMax = new QPropertyAnimation(ui->sidebarFrame, "maximumWidth", this);
    animMax->setDuration(520);
    animMax->setStartValue(0);
    animMax->setEndValue(maxW);
    animMax->setEasingCurve(QEasingCurve::OutCubic);

    auto *animMin = new QPropertyAnimation(ui->sidebarFrame, "minimumWidth", this);
    animMin->setDuration(520);
    animMin->setStartValue(0);
    animMin->setEndValue(minW);
    animMin->setEasingCurve(QEasingCurve::OutCubic);

    auto *slideGroup = new QParallelAnimationGroup(this);
    slideGroup->addAnimation(animMax);
    slideGroup->addAnimation(animMin);

    // Après la slide : logo fade → stagger boutons → glows + indicateur
    connect(slideGroup, &QParallelAnimationGroup::finished, this, [this, navBtns]() {
        // Logo fade-in, puis glow pulse
        auto *logoEff = qobject_cast<QGraphicsOpacityEffect*>(ui->logoLabel->graphicsEffect());
        if (logoEff) {
            auto *logoFade = new QPropertyAnimation(logoEff, "opacity", ui->logoLabel);
            logoFade->setDuration(380);
            logoFade->setStartValue(0.0);
            logoFade->setEndValue(1.0);
            logoFade->setEasingCurve(QEasingCurve::OutCubic);
            connect(logoFade, &QPropertyAnimation::finished, this, [this]() {
                // Couleurs : cyan vif → blanc éclatant → retour
                const QColor c1 = m_isDarkTheme ? QColor(14, 165, 233, 255) : QColor(31, 142, 149, 240);
                const QColor c2 = m_isDarkTheme ? QColor(180, 235, 255, 255) : QColor(100, 220, 210, 255);

                m_logoGlowEffect = new QGraphicsDropShadowEffect(this);
                m_logoGlowEffect->setOffset(0, 0);
                m_logoGlowEffect->setColor(c1);
                m_logoGlowEffect->setBlurRadius(10.0);
                ui->logoLabel->setGraphicsEffect(m_logoGlowEffect);

                // Animation blur : 8 → 70 → 8 (bien visible)
                m_logoGlowAnim = new QPropertyAnimation(m_logoGlowEffect, "blurRadius", this);
                m_logoGlowAnim->setDuration(1800);
                m_logoGlowAnim->setStartValue(8.0);
                m_logoGlowAnim->setEndValue(70.0);
                m_logoGlowAnim->setEasingCurve(QEasingCurve::SineCurve);
                m_logoGlowAnim->setLoopCount(-1);
                m_logoGlowAnim->start();

                // Animation couleur : cyan → blanc → cyan (pulsation chromatique)
                auto *colorAnim = new QVariantAnimation(this);
                colorAnim->setStartValue(c1);
                colorAnim->setKeyValueAt(0.5, c2);
                colorAnim->setEndValue(c1);
                colorAnim->setDuration(1800);
                colorAnim->setEasingCurve(QEasingCurve::SineCurve);
                colorAnim->setLoopCount(-1);
                connect(colorAnim, &QVariantAnimation::valueChanged, this, [this](const QVariant &val) {
                    if (m_logoGlowEffect)
                        m_logoGlowEffect->setColor(val.value<QColor>());
                });
                colorAnim->start();
            });
            logoFade->start(QAbstractAnimation::DeleteWhenStopped);
        }

        // ── Stagger boutons (cascade) ─────────────────────────────────────────
        for (int i = 0; i < navBtns.size(); ++i) {
            QPushButton *btn = navBtns[i];
            QTimer::singleShot(i * 70, this, [btn]() {
                auto *eff = qobject_cast<QGraphicsOpacityEffect*>(btn->graphicsEffect());
                if (!eff) return;
                auto *anim = new QPropertyAnimation(eff, "opacity", btn);
                anim->setDuration(260);
                anim->setStartValue(0.0);
                anim->setEndValue(1.0);
                anim->setEasingCurve(QEasingCurve::OutCubic);
                anim->start(QAbstractAnimation::DeleteWhenStopped);
            });
        }

        // Après stagger fini → glow effects + active indicator
        const int totalMs = (navBtns.size() - 1) * 70 + 260 + 80;
        QTimer::singleShot(totalMs, this, [this]() {
            applyButtonGlowEffects();

            // ── Active indicator (barre cyan glissante) ───────────────────────
            m_activeIndicator = new QFrame(ui->sidebarFrame);
            m_activeIndicator->setAttribute(Qt::WA_TransparentForMouseEvents);
            m_activeIndicator->setObjectName("activeIndicator");
            m_activeIndicator->setFixedWidth(4);
            m_activeIndicator->raise();

            const QList<QPushButton*> nav = {
                ui->btnEmployee, ui->btnInventaire, ui->btnPublication,
                ui->btnFinance, ui->btnLaboratoires, ui->btnProjets
            };
            for (auto *btn : nav) {
                if (btn->property("active").toBool()) {
                    QPoint p = btn->mapTo(ui->sidebarFrame, QPoint(0, 0));
                    m_activeIndicator->setGeometry(p.x(), p.y(), 4, btn->height());
                    break;
                }
            }

            // Fade-in de l'indicateur
            auto *indEff = new QGraphicsOpacityEffect(m_activeIndicator);
            indEff->setOpacity(0.0);
            m_activeIndicator->setGraphicsEffect(indEff);
            m_activeIndicator->show();

            auto *indFade = new QPropertyAnimation(indEff, "opacity", m_activeIndicator);
            indFade->setDuration(400);
            indFade->setStartValue(0.0);
            indFade->setEndValue(1.0);
            indFade->start(QAbstractAnimation::DeleteWhenStopped);
        });
    });

    slideGroup->start(QAbstractAnimation::DeleteWhenStopped);

    // ── 2. Title fade effect (réutilisé à chaque changement de page) ─────────
    m_titleFadeEffect = new QGraphicsOpacityEffect(ui->lblPageTitle);
    m_titleFadeEffect->setOpacity(1.0);
    ui->lblPageTitle->setGraphicsEffect(m_titleFadeEffect);

    // ── 2b. Vignette overlay néon (breathing effect sur toute la fenêtre) ────
    m_vignetteOverlay = new VignetteOverlay(this, m_isDarkTheme);
    m_vignetteOverlay->resize(size());
    m_vignetteOverlay->raise();

    // ── 3. Brand — neon glow pulse + shimmer couleur simultanés ─────────────
    {
        // 3a. Neon drop shadow qui grossit/rétrécit (effet enseigne lumineuse)
        const QColor glowCol = m_isDarkTheme
            ? QColor(14, 165, 233, 210)
            : QColor(31, 142, 149, 190);

        auto *brandGlow = new QGraphicsDropShadowEffect(this);
        brandGlow->setOffset(0, 0);
        brandGlow->setColor(glowCol);
        brandGlow->setBlurRadius(6.0);
        ui->lblBrand->setGraphicsEffect(brandGlow);

        auto *glowAnim = new QPropertyAnimation(brandGlow, "blurRadius", this);
        glowAnim->setDuration(2600);
        glowAnim->setStartValue(4.0);
        glowAnim->setEndValue(18.0);
        glowAnim->setEasingCurve(QEasingCurve::SineCurve);
        glowAnim->setLoopCount(-1);
        glowAnim->start();

    }

    // ── 4. Bouton hamburger : déjà créé dans le constructeur avant show() ──────
    //     (rien à faire ici, connexion déjà faite)
}

// ─────────────────────────────────────────────────────────────────────────────
// applyButtonGlowEffects : installe les effets glow (hover) sur tous les btns
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::applyButtonGlowEffects()
{
    const QColor btnGlow = m_isDarkTheme
        ? QColor(14, 165, 233, 170)
        : QColor(31, 142, 149, 140);

    const QList<QPushButton*> navBtns = {
        ui->btnEmployee, ui->btnInventaire, ui->btnPublication,
        ui->btnFinance, ui->btnLaboratoires, ui->btnProjets
    };
    for (auto *btn : navBtns) {
        auto *glow = new QGraphicsDropShadowEffect(btn);
        glow->setOffset(0, 0);
        glow->setColor(btnGlow);
        glow->setBlurRadius(0.0);
        btn->setGraphicsEffect(glow);

        auto *anim = new QPropertyAnimation(glow, "blurRadius", btn);
        anim->setDuration(200);
        anim->setEasingCurve(QEasingCurve::OutQuad);
        btn->installEventFilter(new HoverGlowHelper(glow, anim, btn));
    }

    auto applySmallGlow = [](QPushButton *btn, QColor col) {
        auto *glow = new QGraphicsDropShadowEffect(btn);
        glow->setOffset(0, 0);
        glow->setColor(col);
        glow->setBlurRadius(0.0);
        btn->setGraphicsEffect(glow);

        auto *anim = new QPropertyAnimation(glow, "blurRadius", btn);
        anim->setDuration(180);
        anim->setEasingCurve(QEasingCurve::OutQuad);
        btn->installEventFilter(new HoverGlowHelper(glow, anim, btn));
    };
    applySmallGlow(ui->btnThemeToggle, QColor(14, 165, 233, 140));
    applySmallGlow(ui->btnDeconnecter, QColor(239, 68, 68, 140));

    // ── Glow universel : TOUS les boutons nommés de l'application ─────────────
    // (sidebar + topBar déjà couverts ci-dessus, on skip ceux qui ont déjà un effet)
    const QColor actionGlow = m_isDarkTheme
        ? QColor(14, 165, 233, 145)
        : QColor(31, 142, 149, 130);
    const QColor dangerGlow  = QColor(239, 68, 68, 130);

    const QStringList skipNames = { "btnToggleSidebar", "btnNotif",
                                    "btnEmployee", "btnInventaire", "btnPublication",
                                    "btnFinance", "btnLaboratoires", "btnProjets",
                                    "btnThemeToggle", "btnDeconnecter" };

    const QList<QPushButton*> allBtns = findChildren<QPushButton*>();
    for (auto *btn : allBtns) {
        const QString name = btn->objectName();
        if (name.isEmpty()) continue;                  // non-nommé → skip
        if (skipNames.contains(name)) continue;        // déjà traité → skip
        if (btn->graphicsEffect()) continue;           // effet déjà présent → skip

        // Boutons destructifs → rouge, autres → cyan/teal
        const bool isDanger = name.contains("Supprimer", Qt::CaseInsensitive)
                           || name.contains("Delete",    Qt::CaseInsensitive)
                           || name.contains("Cancel",    Qt::CaseInsensitive)
                           || name.contains("Annuler",   Qt::CaseInsensitive)
                           || name.contains("Deconnecter", Qt::CaseInsensitive);

        applySmallGlow(btn, isDanger ? dangerGlow : actionGlow);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// toggleSidebar : collapse / expand animé de la sidebar
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::toggleSidebar()
{
    m_sidebarExpanded = !m_sidebarExpanded;

    auto *animMax = new QPropertyAnimation(ui->sidebarFrame, "maximumWidth", this);
    auto *animMin = new QPropertyAnimation(ui->sidebarFrame, "minimumWidth", this);
    animMax->setDuration(340);
    animMin->setDuration(340);
    animMax->setEasingCurve(QEasingCurve::InOutCubic);
    animMin->setEasingCurve(QEasingCurve::InOutCubic);

    if (m_sidebarExpanded) {
        animMax->setStartValue(ui->sidebarFrame->maximumWidth());
        animMax->setEndValue(260);
        animMin->setStartValue(ui->sidebarFrame->minimumWidth());
        animMin->setEndValue(240);
        if (m_btnToggleSidebar) m_btnToggleSidebar->setText("\u2630");
    } else {
        animMax->setStartValue(ui->sidebarFrame->maximumWidth());
        animMax->setEndValue(0);
        animMin->setStartValue(ui->sidebarFrame->minimumWidth());
        animMin->setEndValue(0);
        if (m_btnToggleSidebar) m_btnToggleSidebar->setText("\u00bb");
    }

    auto *group = new QParallelAnimationGroup(this);
    group->addAnimation(animMax);
    group->addAnimation(animMin);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

// ─────────────────────────────────────────────────────────────────────────────
// animateActiveIndicator : glisse la barre cyan vers le bouton actif
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::animateActiveIndicator(QPushButton *btn)
{
    if (!m_activeIndicator || !btn) return;

    QPoint p = btn->mapTo(ui->sidebarFrame, QPoint(0, 0));
    QRect target(p.x(), p.y(), 4, btn->height());

    auto *anim = new QPropertyAnimation(m_activeIndicator, "geometry", this);
    anim->setDuration(300);
    anim->setStartValue(m_activeIndicator->geometry());
    anim->setEndValue(target);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

// ─────────────────────────────────────────────────────────────────────────────
// animateButtonClick : effet ripple (cercle cyan qui s'élargit et disparaît)
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::animateButtonClick(QPushButton *btn)
{
    if (!btn) return;

    const int finalSize = qMax(btn->width(), btn->height()) * 2;
    const int half      = finalSize / 2;
    const QPoint center = btn->rect().center();

    auto *ripple = new QWidget(btn);
    ripple->setAttribute(Qt::WA_TransparentForMouseEvents);
    ripple->setStyleSheet(QString(
        "background: rgba(14,165,233,0.45); border-radius: %1px;").arg(half));
    ripple->setGeometry(center.x() - 4, center.y() - 4, 8, 8);
    ripple->show();
    ripple->raise();

    auto *eff = new QGraphicsOpacityEffect(ripple);
    eff->setOpacity(0.7);
    ripple->setGraphicsEffect(eff);

    auto *geoAnim = new QPropertyAnimation(ripple, "geometry", ripple);
    geoAnim->setDuration(440);
    geoAnim->setStartValue(QRect(center.x() - 4, center.y() - 4, 8, 8));
    geoAnim->setEndValue(QRect(center.x() - half, center.y() - half, finalSize, finalSize));
    geoAnim->setEasingCurve(QEasingCurve::OutCubic);

    auto *fadeAnim = new QPropertyAnimation(eff, "opacity", ripple);
    fadeAnim->setDuration(440);
    fadeAnim->setStartValue(0.7);
    fadeAnim->setEndValue(0.0);
    fadeAnim->setEasingCurve(QEasingCurve::OutCubic);

    auto *group = new QParallelAnimationGroup(ripple);
    group->addAnimation(geoAnim);
    group->addAnimation(fadeAnim);
    connect(group, &QParallelAnimationGroup::finished, ripple, &QWidget::deleteLater);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

// ─────────────────────────────────────────────────────────────────────────────
// animatePageChange : fade-in du contenu + wipe overlay depuis le bas
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::animatePageChange(int newIndex)
{
    if (ui->stackedWidget->currentIndex() == newIndex) return;

    ui->stackedWidget->setCurrentIndex(newIndex);
    QWidget *newPage = ui->stackedWidget->currentWidget();

    // — Fade-in de la nouvelle page (0 → 1, 280 ms OutCubic) ──────────────
    if (newPage) {
        auto *pageEff = new QGraphicsOpacityEffect(newPage);
        pageEff->setOpacity(0.0);
        newPage->setGraphicsEffect(pageEff);

        auto *pageFade = new QPropertyAnimation(pageEff, "opacity", newPage);
        pageFade->setDuration(280);
        pageFade->setStartValue(0.0);
        pageFade->setEndValue(1.0);
        pageFade->setEasingCurve(QEasingCurve::OutCubic);
        connect(pageFade, &QPropertyAnimation::finished, newPage, [newPage]() {
            newPage->setGraphicsEffect(nullptr);
        });
        pageFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // — Overlay lumineux glissant depuis le bas (wipe reveal) ────────────
    const QString overlayStyle = m_isDarkTheme
        ? "background: rgba(14,165,233,0.09);"
        : "background: rgba(31,142,149,0.07);";

    auto *overlay = new QWidget(ui->stackedWidget);
    overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
    overlay->setStyleSheet(overlayStyle);
    overlay->resize(ui->stackedWidget->size());
    overlay->show();
    overlay->raise();

    auto *overlayEff = new QGraphicsOpacityEffect(overlay);
    overlayEff->setOpacity(0.85);
    overlay->setGraphicsEffect(overlayEff);

    const int startY = ui->stackedWidget->height() / 5;

    auto *slideAnim = new QPropertyAnimation(overlay, "pos", overlay);
    slideAnim->setDuration(380);
    slideAnim->setStartValue(QPoint(0, startY));
    slideAnim->setEndValue(QPoint(0, 0));
    slideAnim->setEasingCurve(QEasingCurve::OutQuart);

    auto *fadeOut = new QPropertyAnimation(overlayEff, "opacity", overlay);
    fadeOut->setDuration(380);
    fadeOut->setStartValue(0.85);
    fadeOut->setEndValue(0.0);
    fadeOut->setEasingCurve(QEasingCurve::OutCubic);

    auto *group = new QParallelAnimationGroup(overlay);
    group->addAnimation(slideAnim);
    group->addAnimation(fadeOut);
    connect(group, &QParallelAnimationGroup::finished, overlay, &QWidget::deleteLater);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

// ─────────────────────────────────────────────────────────────────────────────
// updateAnimationColors : met à jour les couleurs des animations au changement de thème
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::updateAnimationColors()
{
    if (!m_logoGlowEffect) return;
    const QColor glowCol = m_isDarkTheme
        ? QColor(14, 165, 233, 190)
        : QColor(31, 142, 149, 160);
    m_logoGlowEffect->setColor(glowCol);

    // Met à jour la couleur des glows sur les boutons sidebar
    const QColor btnGlow = m_isDarkTheme
        ? QColor(14, 165, 233, 170)
        : QColor(31, 142, 149, 140);

    const QList<QPushButton*> navBtns = {
        ui->btnEmployee, ui->btnInventaire, ui->btnPublication,
        ui->btnFinance, ui->btnLaboratoires, ui->btnProjets,
        ui->btnThemeToggle, ui->btnDeconnecter
    };
    for (auto *btn : navBtns) {
        if (auto *eff = qobject_cast<QGraphicsDropShadowEffect*>(btn->graphicsEffect())) {
            eff->setColor(btnGlow);
        }
    }
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
    min-height: 180px;
    /* pixmap chargé via setPixmap() dans updateThemeButton — pas de background-image */
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

void MainWindow::updateScaledQss()
{
    // Supprimé : qApp->setStyleSheet() sur chaque resize est trop coûteux
    // (re-parse + re-render de TOUS les widgets → lag systématique).
    // Le scaling des formulaires est géré par ProportionalScaler.
}

void MainWindow::toggleTheme()
{
    m_isDarkTheme = !m_isDarkTheme;

    // Charger et appliquer le fichier QSS correspondant
    QString themeFile = m_isDarkTheme
        ? QStringLiteral(":/theme/style_dark.qss")
        : QStringLiteral(":/theme/style_light.qss");
    QFile f(themeFile);
    if (f.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(QLatin1String(f.readAll()));
        f.close();
    }

    QSettings settings("SmartResearchLab", "Theme");
    settings.setValue("darkMode", m_isDarkTheme);

    updateThemeButton();
    updateAnimationColors();
}

void MainWindow::updateThemeButton()
{
    // Logo sidebar commun (logo_off.png) — centré, séparé par une ligne
    {
        QPixmap pix(":/img/images/logo_off.png");
        if (!pix.isNull()) {
            // Taille fixe : 160×160 px max dans la sidebar (240-260px wide)
            ui->logoLabel->setPixmap(
                pix.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        ui->logoLabel->setAlignment(Qt::AlignCenter);
        ui->logoLabel->setScaledContents(false);
        ui->logoLabel->setText(QString()); // pas de texte sur le pixmap
    }

    if (m_isDarkTheme) {
        ui->btnThemeToggle->setText(QString::fromUtf8("\xe2\x98\x80\xef\xb8\x8f  Mode Jour"));
        ui->btnThemeToggle->setToolTip("Passer en th\u00E8me clair");
        ui->lblBrand->setText(R"(<span style="color:#e2e8f0; font-weight:900;">Smart</span><span style="color:#38bdf8; font-weight:900;">ResearchLab</span>)");
        ui->logoLabel->setStyleSheet(
            "QLabel {"
            "  border-bottom: 2px solid rgba(14,165,233,0.35);"
            "  padding-bottom: 8px;"
            "  margin-bottom: 4px;"
            "  background: qlineargradient(x1:0,y1:0,x2:0,y2:1,"
            "    stop:0 rgba(14,165,233,0.06), stop:1 transparent);"
            "}");
    } else {
        ui->btnThemeToggle->setText(QString::fromUtf8("\xf0\x9f\x8c\x99  Mode Nuit"));
        ui->btnThemeToggle->setToolTip("Passer en th\u00E8me sombre");
        ui->lblBrand->setText(R"(<span style="color:#1e293b; font-weight:900;">Smart</span><span style="color:#1F8E95; font-weight:900;">ResearchLab</span>)");
        ui->logoLabel->setStyleSheet(
            "QLabel {"
            "  border-bottom: 2px solid rgba(31,142,149,0.35);"
            "  padding-bottom: 8px;"
            "  margin-bottom: 4px;"
            "  background: transparent;"
            "}");
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

    // Barre indicatrice glissante + ripple sur le bouton cliqué
    animateActiveIndicator(btn);
    animateButtonClick(btn);
}

/* ===================== NAVIGATION ===================== */

void MainWindow::initEmployeUserGuidance()
{
    ui->groupBox_2->setTitle(QStringLiteral("Nouvel employé"));
    ui->groupBox_2->setToolTip(
        QStringLiteral("Étapes : 1) Complétez tous les champs obligatoires  2) Cliquez sur « Enregistrer »  "
                        "3) Un code vous est envoyé par e-mail — saisissez-le  4) Le compte est créé et un e-mail de confirmation est envoyé."));
    ui->groupBox_6->setTitle(QStringLiteral("Modifier un employé"));
    ui->groupBox_6->setToolTip(
        QStringLiteral("Sélectionnez un employé dans la liste, modifiez les champs puis enregistrez. "
                        "Si l’e-mail change, un code de vérification est demandé."));

    ui->lineSearchEmp->setToolTip(
        QStringLiteral("Filtre la liste en temps réel : vous pouvez taper une partie du CIN "
                        "de l’identifiant ou du rôle."));
    ui->TableEmp->setToolTip(
        QStringLiteral("Cliquez sur une ligne pour la sélectionner. Utilisez « Modifier » ou « Supprimer » uniquement après sélection."));
    ui->btnAjouterEmp->setToolTip(QStringLiteral("Ouvre le formulaire de création d’un nouveau compte employé."));
    ui->btnModifier_emp->setToolTip(
        QStringLiteral("Sélectionnez d’abord une ligne dans le tableau, puis cliquez ici pour éditer cet employé."));
    ui->btnSupprimer_emp->setToolTip(
        QStringLiteral("Sélectionnez un employé dans le tableau, puis supprimez-le (action définitive)."));
    ui->btnTrier_emp->setToolTip(QStringLiteral("Trie la liste par date d’embauche. Cliquez à nouveau pour inverser l’ordre."));
    ui->pointage->setToolTip(QStringLiteral("Accès au module de pointage des présences."));
    ui->btnStat_emp->setToolTip(QStringLiteral("Ouvre les statistiques liées aux employés."));

    ui->lineCINAdd->setPlaceholderText(QStringLiteral("8 chiffres (CIN)"));
    ui->lineCINAdd->setToolTip(QStringLiteral("Numéro de la carte d’identité : exactement 8 chiffres, sans espaces. Doit être unique."));

    ui->lineUsernameAdd->setPlaceholderText(QStringLiteral("Identifiant de connexion"));
    ui->lineUsernameAdd->setToolTip(QStringLiteral("Nom d’utilisateur pour ouvrir une session dans l’application — doit être unique."));

    ui->linePasswordAdd->setPlaceholderText(QStringLiteral("Mot de passe fort (voir la barre à droite)"));
    ui->linePasswordAdd->setToolTip(
        QStringLiteral("Règles : au moins 10 caractères, avec minuscules, majuscules, chiffres et un caractère spécial. "
                        "La barre colorée doit afficher au minimum « Fort » pour pouvoir enregistrer."));
    ui->passwordStrengthBarAdd->setToolTip(QStringLiteral("Indicateur de robustesse : viser « Fort » ou « Très fort »."));
    ui->passwordStrengthLabelAdd->setToolTip(ui->passwordStrengthBarAdd->toolTip());

    ui->lineEmailAdd->setPlaceholderText(QStringLiteral("E-mail unique (vérification par code)"));
    ui->lineEmailAdd->setToolTip(
        QStringLiteral("Adresse e-mail qui ne doit pas déjà exister pour un autre employé. "
                        "Un code de vérification y sera envoyé avant la création du compte."));

    ui->lineNomAdd->setPlaceholderText(QStringLiteral("Nom de famille"));
    ui->linePrenomAdd->setPlaceholderText(QStringLiteral("Prénom"));
    ui->lineNomAdd->setToolTip(QStringLiteral("Nom affiché dans les listes et les documents."));
    ui->linePrenomAdd->setToolTip(QStringLiteral("Prénom de l’employé."));

    ui->comboRoleAdd->setToolTip(QStringLiteral("Rôle dans l’application (droits d’accès). Choisissez une valeur autre que la première ligne vide."));
    ui->comboDepartementAdd->setToolTip(QStringLiteral("Département : choisissez une entrée dans la liste déroulante."));
    ui->comboPosteAdd->setToolTip(QStringLiteral("Poste occupé : choisissez une entrée dans la liste déroulante."));

    ui->dateEmbaucheAdd->setToolTip(QStringLiteral("Date d’embauche ou de début de contrat."));
    ui->lineSalaireAdd->setPlaceholderText(QStringLiteral("Ex. 2500 ou 2500.50"));
    ui->lineSalaireAdd->setToolTip(QStringLiteral("Montant du salaire (nombre positif, séparateur décimal accepté)."));

    ui->btnSaveEmployee->setToolTip(
        QStringLiteral("Valide le formulaire : contrôle des données, mot de passe fort, e-mail disponible, "
                        "puis envoi d’un code par e-mail — saisissez le code dans la fenêtre qui s’affiche."));
    ui->btnAnnuler_emp->setToolTip(QStringLiteral("Retour à la liste sans enregistrer les données saisies."));
    ui->BtnPopupCancelLabs_8->setToolTip(QStringLiteral("Fermer le formulaire d’ajout et revenir à la liste."));

    ui->lineCIN_emp->setToolTip(QStringLiteral("Le CIN n’est pas modifiable pour éviter les incohérences avec les données légales."));
    ui->lineNomEmp->setPlaceholderText(QStringLiteral("Nom"));
    ui->linePrenomEmp->setPlaceholderText(QStringLiteral("Prénom"));
    ui->lineUsernameEmp->setToolTip(QStringLiteral("Identifiant de connexion — doit rester unique pour tous les comptes."));
    ui->lineEmailEmp->setToolTip(
        QStringLiteral("Si vous modifiez l’e-mail, un code de confirmation sera envoyé à la nouvelle adresse avant enregistrement."));
    ui->comboPosteEmp->setToolTip(QStringLiteral("Poste : liste déroulante."));
    ui->comboDepartementEmp->setToolTip(QStringLiteral("Département : liste déroulante."));
    ui->comboRoleAdd_2->setToolTip(QStringLiteral("Rôle applicatif — sélectionnez une valeur valide dans la liste."));
    ui->dateEmbaucheEmp->setToolTip(QStringLiteral("Date d’embauche."));
    ui->lineSalaireEmp->setPlaceholderText(QStringLiteral("Salaire (nombre)"));
    ui->btnSaveEditEmployee->setToolTip(QStringLiteral("Enregistre les changements (vérification des doublons et de l’e-mail si modifié)."));
    ui->btnCancelEditEmp->setToolTip(QStringLiteral("Annule et retourne à la liste sans sauvegarder."));
    ui->BtnPopupCancelLabs_10->setToolTip(QStringLiteral("Fermer l’écran de modification."));
}

void MainWindow::goEmployee()
{
    animatePageChange(0);
    setActiveButton(ui->btnEmployee);
    loadEmployees();
}

void MainWindow::checkAndShowInventoryAlerts() {
    QVector<Inventory::Row> alerts;
    QString err;
    if (!Inventory::checkThresholdAlerts(alerts, &err)) {
        qDebug() << "[INVENTORY] Erreur vérification seuils:" << err;
        return;
    }
    if (alerts.isEmpty()) return;

    // ── Notification cloche ───────────────────────────────────────────────
    for (const auto &row : std::as_const(alerts)) {
        const QString label = row.name.isEmpty() ? row.sku : row.name;
        ajouterNotification(
            "SYSTÈME",
            QString("⚠ Seuil atteint : %1 (dispo: %2 ≤ seuil: %3)")
                .arg(label)
                .arg(row.qtAv)
                .arg(row.threshold)
        );
    }

    // ── QMessageBox récapitulatif ─────────────────────────────────────────
    QString msg = QString("<b>%1 produit(s) ont atteint leur seuil :</b><br><br>")
                      .arg(alerts.size());

    for (const auto &row : std::as_const(alerts)) {
        const QString label = row.name.isEmpty() ? row.sku : row.name;
        QString color = (row.qtAv <= 0) ? "#DC2626" : "#D97706"; // rouge si épuisé, orange si limité
        msg += QString(
            "<span style='color:%4;'>⚠</span> "
            "<b>%1</b> &nbsp;|&nbsp; SKU: %2 "
            "&nbsp;|&nbsp; Disponible: <b>%3</b> "
            "&nbsp;|&nbsp; Seuil: <b>%5</b><br>"
        )
        .arg(label)
        .arg(row.sku)
        .arg(row.qtAv)
        .arg(color)
        .arg(row.threshold);
    }

    QMessageBox alert(this);
    alert.setWindowTitle("⚠ Alertes Inventaire — Seuil atteint");
    alert.setIcon(QMessageBox::Warning);
    alert.setTextFormat(Qt::RichText);
    alert.setText(msg);
    alert.setStandardButtons(QMessageBox::Ok);
    alert.setDefaultButton(QMessageBox::Ok);
    alert.exec();
}

void MainWindow::goInventaire() {
    animatePageChange(1);
    setActiveButton(ui->btnInventaire);
    refreshInventoryTypeFilter();
    checkAndShowInventoryAlerts();
}

void MainWindow::goPublication()
{
    animatePageChange(2);
    setActiveButton(ui->btnPublication);
}

void MainWindow::goFinance()
{
    animatePageChange(3);
    setActiveButton(ui->btnFinance);
}

void MainWindow::goLaboratoires()
{
    animatePageChange(4);
    setActiveButton(ui->btnLaboratoires);
}

void MainWindow::goProjets()
{
    animatePageChange(5);
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
    ui->lblPageTitle->setText(pageName + QString::fromUtf8("  |  %1 %2")
                              .arg(greeting, userName));

    // Animation fade-in du titre à chaque changement de page
    if (m_titleFadeEffect) {
        m_titleFadeEffect->setOpacity(0.0);
        auto *fadeIn = new QPropertyAnimation(m_titleFadeEffect, "opacity", this);
        fadeIn->setDuration(380);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->setEasingCurve(QEasingCurve::OutCubic);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    }
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

    // ========== INFORMATIONS COMPLÉMENTAIRES ==========

// PAR :
    out << "└─────────────────────────────────────────────────────────────────┘\n\n";

    // ========== INFORMATIONS FINANCIÈRES ==========
    out << "┌─────────────────────────────────────────────────────────────────┐\n";
    out << "│                    INFORMATIONS FINANCIÈRES                     │\n";
    out << "├─────────────────────────────────────────────────────────────────┤\n";

    {
        QString ligneM  = QString("│ %1 : %2 DT").arg("Montant total", -40).arg(ui->aff_montant->text().remove(" DT"));
        out << ligneM.leftJustified(67, ' ') << "│\n";
        QString ligneMP = QString("│ %1 : %2 DT").arg("Montant payé", -40).arg(ui->aff_montant_paye->text().remove(" DT"));
        out << ligneMP.leftJustified(67, ' ') << "│\n";
        QString ligneR  = QString("│ %1 : %2 DT").arg("Reste à payer", -40).arg(ui->aff_reste->text().remove(" DT"));
        out << ligneR.leftJustified(67, ' ') << "│\n";
    }
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
    QString location = ui->aff2->text().trimmed();

    if (location.isEmpty()) {
        QMessageBox::warning(this, "Localisation vide",
                             "Aucune localisation n'est disponible pour ce laboratoire.\n"
                             "Veuillez d'abord sélectionner et afficher un laboratoire.");
        return;
    }

    MapDialog dlg(MapDialog::ViewMode, location, this);
    dlg.exec();
}

void MainWindow::on_btnVoirStatistiquesPub_2_clicked()
{
    showLabsPaymentStats();
}

// ── Statistiques paiement ──
void MainWindow::showLabsPaymentStats()
{
    // ─── Graphique Paiement (Payé / Non payé) ───────────────────────
    QSqlQuery queryPmt(R"(
        SELECT NOMLABO,
               SUM(CASE WHEN LOWER(PAIEMENT) = 'payer'     THEN 1 ELSE 0 END) AS Paye,
               SUM(CASE WHEN LOWER(PAIEMENT) = 'non payer' THEN 1 ELSE 0 END) AS NonPaye,
               COUNT(*) AS Total
        FROM LABS
        GROUP BY NOMLABO
        ORDER BY NOMLABO
    )");

    QStringList categories;
    QVector<double> payePercent, nonPayePercent;
    bool hasData = false;

    while (queryPmt.next()) {
        hasData = true;
        const QString nomLabo = queryPmt.value(0).toString();
        const int paye        = queryPmt.value(1).toInt();
        const int nonPaye     = queryPmt.value(2).toInt();
        const int total       = queryPmt.value(3).toInt();
        categories     << nomLabo;
        payePercent    << (total > 0 ? (paye    * 100.0 / total) : 0.0);
        nonPayePercent << (total > 0 ? (nonPaye * 100.0 / total) : 0.0);
    }

    if (!hasData) {
        QMessageBox::warning(this, "Statistiques Laboratoires", "Aucune donnée trouvée.");
        return;
    }

    // ─── Graphique Montant / Payé / Reste ───────────────────────────
    QSqlQuery queryFin(R"(
        SELECT NOMLABO, SUM(MONTANT), SUM(MONTANT_PAYE), SUM(RESTE)
        FROM LABS
        GROUP BY NOMLABO
        ORDER BY NOMLABO
    )");

    QBarSet *setMontant      = new QBarSet("Montant Total (DT)");
    QBarSet *setMontantPaye  = new QBarSet("Montant Payé (DT)");
    QBarSet *setReste        = new QBarSet("Reste (DT)");
    setMontant->setColor(QColor(52, 152, 219));
    setMontantPaye->setColor(QColor(39, 174, 96));
    setReste->setColor(QColor(231, 76, 60));

    QStringList catsFin;
    while (queryFin.next()) {
        catsFin    << queryFin.value(0).toString();
        *setMontant     << queryFin.value(1).toDouble();
        *setMontantPaye << queryFin.value(2).toDouble();
        *setReste       << queryFin.value(3).toDouble();
    }

    // ── Fenêtre graphique Paiement (%) ──
    {
        QBarSet *setPaye    = new QBarSet("Payé (%)");
        QBarSet *setNonPaye = new QBarSet("Non Payé (%)");
        setPaye->setColor(QColor(39, 174, 96));
        setNonPaye->setColor(QColor(231, 76, 60));
        for (int i = 0; i < payePercent.size(); ++i) {
            *setPaye    << payePercent[i];
            *setNonPaye << nonPayePercent[i];
        }
        QBarSeries *s = new QBarSeries();
        s->append(setPaye); s->append(setNonPaye);
        s->setLabelsVisible(true); s->setLabelsFormat("@value %");

        QChart *chart = new QChart();
        chart->addSeries(s);
        chart->setTitle("Statut de Paiement par Laboratoire (%)");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom); s->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 100); axisY->setTitleText("Pourcentage (%)");
        axisY->setLabelFormat("%.1f%%");
        chart->addAxis(axisY, Qt::AlignLeft); s->attachAxis(axisY);

        QChartView *cv = new QChartView(chart);
        cv->setRenderHint(QPainter::Antialiasing);
        cv->setMinimumSize(950, 550);
        cv->setWindowTitle("Statistiques Paiement (%) - Laboratoires");
        cv->setAttribute(Qt::WA_DeleteOnClose);
        cv->show();
    }

    // ── Fenêtre graphique Montants (DT) ──
    if (!catsFin.isEmpty()) {
        QBarSeries *s2 = new QBarSeries();
        s2->append(setMontant); s2->append(setMontantPaye); s2->append(setReste);
        s2->setLabelsVisible(true); s2->setLabelsFormat("@value DT");

        QChart *chart2 = new QChart();
        chart2->addSeries(s2);
        chart2->setTitle("Montants par Laboratoire (DT)");
        chart2->setAnimationOptions(QChart::SeriesAnimations);
        chart2->legend()->setVisible(true);
        chart2->legend()->setAlignment(Qt::AlignBottom);

        QBarCategoryAxis *axX = new QBarCategoryAxis();
        axX->append(catsFin);
        chart2->addAxis(axX, Qt::AlignBottom); s2->attachAxis(axX);

        QValueAxis *axY = new QValueAxis();
        axY->setTitleText("Montant (DT)"); axY->setLabelFormat("%.2f");
        chart2->addAxis(axY, Qt::AlignLeft); s2->attachAxis(axY);

        QChartView *cv2 = new QChartView(chart2);
        cv2->setRenderHint(QPainter::Antialiasing);
        cv2->setMinimumSize(950, 550);
        cv2->setWindowTitle("Statistiques Financières - Laboratoires");
        cv2->setAttribute(Qt::WA_DeleteOnClose);
        cv2->show();
    }
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
    MapDialog *dlg = new MapDialog(MapDialog::PickMode, QString(), this);
    connect(dlg, &MapDialog::coordinatesSelected, this, &MainWindow::onMapLocationSelected);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}
void MainWindow::on_btnAjouterPub_5_clicked()
{
    MapDialog *dlg = new MapDialog(MapDialog::PickMode, QString(), this);
    connect(dlg, &MapDialog::coordinatesSelected, this, &MainWindow::onMapLocationSelected);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}
void MainWindow::on_btnmapl_3_clicked()
{
    MapDialog *dlg = new MapDialog(MapDialog::PickMode, QString(), this);
    connect(dlg, &MapDialog::coordinatesSelected, this, &MainWindow::onMapLocationSelected);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}
// Inventory - Navigation
// ====================== AJOUT ======================
void MainWindow::handleInventoryAdd()
{
    qDebug() << "[INVENTORY] handleInventoryAdd: Navigating to Choice Page";
    ui->stacked_I->setCurrentWidget(m_pageChoixAjoutInv);
}



void MainWindow::handleInventoryView()
{
    qDebug() << "[INVENTORY] handleInventoryView: Navigating to Index 4 (afficheri)";
    const int r = ui->TableInventory->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Afficher", "Sélectionne un produit à afficher.");
        return;
    }

    QTableWidgetItem *itId = ui->TableInventory->item(r, 0);
    if (!itId) return;

    ui->aff_id->setText(itId->text());
    ui->aff_sku->setText(ui->TableInventory->item(r, 1)->text());
    ui->aff_name->setText(ui->TableInventory->item(r, 2)->text());
    ui->aff_price->setText(ui->TableInventory->item(r, 3)->text());
    ui->aff_qtav->setText(ui->TableInventory->item(r, 4)->text());
    ui->aff_status->setText(ui->TableInventory->item(r, 5)->text());

    // Extra data from UserRole
    ui->aff_zone->setText(itId->data(Qt::UserRole + 1).toString());
    ui->aff_shelf->setText(itId->data(Qt::UserRole + 2).toString());
    ui->aff_unit->setText(itId->data(Qt::UserRole + 3).toString());
    ui->aff_type->setText(itId->data(Qt::UserRole + 4).toString());
    ui->aff_description->setText(itId->data(Qt::UserRole + 5).toString());
    ui->aff_qtrs->setText(itId->data(Qt::UserRole + 6).toString());
    ui->aff_threshold->setText(itId->data(Qt::UserRole + 7).toString());

    ui->stacked_I->setCurrentIndex(4); // "afficheri" page (Index 4)
}

void MainWindow::on_BtnPopupCancelInventory_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}

void MainWindow::on_BtnPopupCancelInventory_2_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}

void MainWindow::on_retour_stat_6_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}

void MainWindow::on_retour_stat_7_clicked()
{
    ui->stacked_I->setCurrentIndex(0);
}

void MainWindow::handleInventoryStats()
{
    QString err;
    if (!syncInventoryStatsFromProduct(&err)) {
        QMessageBox::critical(this, "Inventaire",
                              "Impossible de synchroniser les statistiques produit.\n\n"
                              "Détail : " + err);
        return;
    }

    loadInventory();
    showInventoryLabUsageStats();
    ui->stacked_I->setCurrentIndex(3); // "stati" page (Index 3)
}

bool MainWindow::syncInventoryStatsFromProduct(QString *err)
{
    // USE_COUNT = cumulative qty allocated to labs (updated only by lab reservation).
    // Do not overwrite it from QT_RS here.
    QSqlQuery ensureColumn;
    ensureColumn.exec(
        "ALTER TABLE PRODUCT ADD USE_COUNT NUMBER DEFAULT 0"
    );

    QSqlQuery q2;
    const QString sqlStatus = QStringLiteral(
        "UPDATE PRODUCT p "
        "SET p.STATUS = CASE "
        "  WHEN NVL(p.QT_AV, 0) = 0                                    THEN 'stock out' "
        "  WHEN NVL(p.QT_AV, 0) <= NVL(p.THRESHOLD, 0) * 2            THEN 'limited' "
        "  WHEN NVL(p.QT_AV, 0) >= NVL(p.THRESHOLD, 0) * 3            THEN 'on hand' "
        "  ELSE 'limited' "
        "END"
    );

    if (!q2.exec(sqlStatus)) {
        if (err) *err = q2.lastError().text();
        return false;
    }

    return true;
}

void MainWindow::showInventoryLabUsageStats()
{
    // Ensure the combo box exists for chart type selection
    QComboBox *combo = ui->stati->findChild<QComboBox*>(QStringLiteral("invChartTypeCombo"));
    if (!combo) {
        combo = new QComboBox(ui->stati);
        combo->setObjectName(QStringLiteral("invChartTypeCombo"));
        combo->addItem("Statistiques : Utilisation par Laboratoires (Colonnes)", 0);
        combo->addItem("Statistiques : Répartition par Statut (Cercle)", 1);
        
        // Match the styling
        combo->setStyleSheet(
            "QComboBox { background-color: white; border: 2px solid #e0be9c; border-radius: 8px; padding: 5px 15px; font-weight: bold; font-size: 14px; color: #333; }"
            "QComboBox::drop-down { border: none; width: 30px; }"
        );
        
        // Position it explicitly roughly above the chart region 
        // (Assuming ui->stat_pub_6 geometry handles the chart area, we place it near the top left)
        if (ui->stat_pub_6) {
            QRect g = ui->stat_pub_6->geometry();
            combo->setGeometry(g.x(), g.y() - 50, 450, 40);
        } else {
            combo->setGeometry(50, 20, 450, 40);
        }
        combo->show();
        combo->raise();
        
        connect(combo, &QComboBox::currentIndexChanged, this, [this](int) {
            this->showInventoryLabUsageStats();
        });
    }

    int chartType = combo->currentData().toInt();

    QChart *chart = new QChart();
    
    // Petite animation demandée : AllAnimations pour transitions douces
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setBackgroundBrush(m_isDarkTheme ? QColor(15, 23, 42) : QColor(252, 252, 250));
    chart->setTitleFont(QFont(QStringLiteral("Segoe UI"), 14, QFont::Bold));
    chart->setTitleBrush(m_isDarkTheme ? QColor(241, 245, 249) : QColor(45, 55, 72));

    if (chartType == 0) {
        // --- 1. GRAPHIQUE EN COLONNES (BAR CHART) ---
        QSqlQuery qLab;
        if (!qLab.exec(QStringLiteral(
                "SELECT * FROM ("
                "  SELECT NVL(NULLIF(TRIM(NAME), ''), SKU) AS NM, NVL(USE_COUNT, 0) AS UC "
                "  FROM PRODUCT "
                "  ORDER BY NVL(USE_COUNT, 0) DESC NULLS LAST"
                ") WHERE ROWNUM <= 20"))) {
            qDebug() << "[INVENTORY] stats query failed:" << qLab.lastError().text();
        }

        QStringList categories;
        QList<double> values;
        double maxY = 1.0;
        bool anyLabUsage = false;

        while (qLab.next()) {
            const QString nm = qLab.value(0).toString().trimmed();
            const double uc = qLab.value(1).toDouble();
            if (uc > 0)
                anyLabUsage = true;
            const QString label = nm.length() > 28 ? nm.left(25) + QLatin1String("…") : nm;
            categories << (label.isEmpty() ? QStringLiteral("(sans nom)") : label);
            values << uc;
            if (uc > maxY)
                maxY = uc;
        }

        if (categories.isEmpty()) {
            chart->setTitle(QStringLiteral("Inventaire — aucun produit"));
        } else if (anyLabUsage) {
            chart->setTitle(QStringLiteral("Produits les plus alloués aux laboratoires (USE_COUNT)"));
            QBarSet *set = new QBarSet(QStringLiteral("Quantité allouée (labs)"));
            set->setColor(QColor(31, 142, 149)); // Primary brand color
            for (double v : std::as_const(values))
                *set << v;
            QBarSeries *series = new QBarSeries();
            series->append(set);
            series->setLabelsVisible(true);
            series->setLabelsFormat(QStringLiteral("@value"));
            chart->addSeries(series);

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, maxY + qMax(1.0, maxY * 0.15));
            axisY->setTitleText(QStringLiteral("Quantité Utilisée"));
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
        } else {
            chart->setTitle(QStringLiteral("Aucun produit n'a encore été assigné à un laboratoire."));
        }
    } else {
        // --- 2. GRAPHIQUE EN CERCLE (PIE CHART) ---
        chart->setTitle(QStringLiteral("Répartition du stock par Statut"));
        QSqlQuery qSt;
        qSt.exec(QStringLiteral("SELECT STATUS, COUNT(*) FROM PRODUCT GROUP BY STATUS"));
        QPieSeries *pie = new QPieSeries();
        bool has = false;
        
        // Custom colors for status pie chart
        QList<QColor> colors = { QColor(45, 212, 191), QColor(251, 146, 60), QColor(248, 113, 113), QColor(148, 163, 184) };
        int colorIdx = 0;

        while (qSt.next()) {
            has = true;
            QString st = qSt.value(0).toString().trimmed();
            if (st.isEmpty())
                st = QStringLiteral("Non défini");
            const int c = qSt.value(1).toInt();
            QPieSlice *sl = pie->append(QStringLiteral("%1 (%2)").arg(st).arg(c), c);
            sl->setLabelVisible(true);
            sl->setBrush(colors[colorIdx % colors.size()]);
            // Explosion animation for slices to make it "jolie"
            sl->setExploded(true);
            sl->setExplodeDistanceFactor(0.05);
            colorIdx++;
        }
        if (!has) {
            chart->setTitle(QStringLiteral("Aucune donnée inventaire"));
        } else {
            chart->addSeries(pie);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);
        }
    }

    QChartView *cv = ui->stati->findChild<QChartView*>(QStringLiteral("inventoryLabUsageChart"));
    if (!cv) {
        cv = new QChartView(ui->stati);
        cv->setObjectName(QStringLiteral("inventoryLabUsageChart"));
        if (ui->stat_pub_6)
            cv->setGeometry(ui->stat_pub_6->geometry());
        cv->setRenderHint(QPainter::Antialiasing);
        cv->raise();
        if (ui->stat_pub_6)
            ui->stat_pub_6->hide();
    } else {
        QChart *old = cv->chart();
        if (old)
            old->deleteLater();
        if (ui->stat_pub_6)
            ui->stat_pub_6->hide();
    }
    cv->setChart(chart);
    cv->show();
}



// Finance “retour” existants
void MainWindow::on_retour_stat_4_clicked() { ui->stacked_F->setCurrentIndex(0); }
void MainWindow::on_retour_stat_5_clicked() { ui->stacked_F->setCurrentIndex(0); }

// Emp cancels
void MainWindow::on_BtnPopupCancelLabs_6_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_btnCancelEditEmp_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_10_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_9_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_8_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_btnSaveEmployee_2_clicked() { ui->stack_emp->setCurrentIndex(0); }
void MainWindow::on_BtnPopupCancelLabs_7_clicked() { ui->stack_emp->setCurrentIndex(0); }

// Projets - Navigation
void MainWindow::on_retour_statn_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnRetourEditProj_clicked() { ui->stack_proj->setCurrentIndex(0); }
void MainWindow::on_btnRetourAddProj_clicked()
{
    // clear add form on cancel
    ui->lineTitreAddProj->clear();
    ui->lineDomaineAddProj->clear();
    ui->lineEdit->clear();
    ui->lineInventeursAddProj->clear();
    ui->lineResumeAddProj->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
    ui->stack_proj->setCurrentIndex(0);
}
void MainWindow::on_btnAjouterProj_clicked() { ui->stack_proj->setCurrentIndex(1); }
void MainWindow::on_btnModifierProj_clicked()
{
    QString id = selectedProjetId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Sélection", "Veuillez sélectionner un projet à modifier.");
        return;
    }
    int r = ui->tableProjets->currentRow();
    if (!ui->tableProjets->item(r, 0)) return;
    ui->lineTitreEditProj->setText(ui->tableProjets->item(r,0)->text());
    ui->lineDomaineEditProj->setText(ui->tableProjets->item(r,1)->text());
    ui->lineEdit_2->setText(ui->tableProjets->item(r,2)->text());
    ui->dateEdit_5->setDate(QDate::fromString(ui->tableProjets->item(r,3)->text(), "yyyy-MM-dd"));
    ui->dateEdit_6->setDate(QDate::fromString(ui->tableProjets->item(r,4)->text(), "yyyy-MM-dd"));
    QString dfr = ui->tableProjets->item(r,5)->text();
    ui->dateEdit_4->setDate(dfr.isEmpty() ? QDate::currentDate() : QDate::fromString(dfr, "yyyy-MM-dd"));
    ui->lineInventeursEditProj->setCurrentText(ui->tableProjets->item(r,6)->text());
    ui->lineResumeEditProj->setCurrentText(ui->tableProjets->item(r,7)->text());
    idProjetToEdit = id;
    ui->stack_proj->setCurrentIndex(2);
}
void MainWindow::on_btnVoirStatistiquesProj_clicked()
{
    showProjetsStats();
    ui->stack_proj->setCurrentIndex(3);
}

void MainWindow::showProjetsStats()
{
    // --- Chart 1: Pie chart - Répartition par Statut ---
    QVector<Projet::Row> rows;
    QString err;
    if (!Projet::chargerTout(rows, &err) || rows.isEmpty()) return;

    // count by statut
    QMap<QString, int> statutCount;
    QMap<QString, int> prioCount;
    for (const auto &r : rows) {
        statutCount[r.statut.isEmpty() ? "Non défini" : r.statut]++;
        prioCount[r.priorite.isEmpty() ? "Non défini" : r.priorite]++;
    }

    // --- Pie: Statut ---
    QPieSeries *pieSeries = new QPieSeries();
    for (auto it = statutCount.begin(); it != statutCount.end(); ++it) {
        QPieSlice *slice = pieSeries->append(
            QString("%1 (%2)").arg(it.key()).arg(it.value()), it.value());
        slice->setLabelVisible(true);
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition par Statut");
    pieChart->setAnimationOptions(QChart::SeriesAnimations);
    pieChart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *pieView = new QChartView(pieChart);
    pieView->setRenderHint(QPainter::Antialiasing);

    // clear old layout and set new one
    QLayout *oldLayout1 = ui->statsWidgetProjStatus->layout();
    if (oldLayout1) {
        QLayoutItem *item;
        while ((item = oldLayout1->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout1;
    }
    QVBoxLayout *l1 = new QVBoxLayout(ui->statsWidgetProjStatus);
    l1->addWidget(pieView);

    // --- Bar: Priorité ---
    QBarSet *barSet = new QBarSet("Nombre de projets");
    QStringList prioLabels;
    for (auto it = prioCount.begin(); it != prioCount.end(); ++it) {
        prioLabels << it.key();
        *barSet << it.value();
    }

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);
    barSeries->setLabelsVisible(true);
    barSeries->setLabelsFormat("@value");

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Projets par Priorité");
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->legend()->setVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(prioLabels);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Nombre");
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *barView = new QChartView(barChart);
    barView->setRenderHint(QPainter::Antialiasing);

    QLayout *oldLayout2 = ui->statsWidgetProjPrio->layout();
    if (oldLayout2) {
        QLayoutItem *item;
        while ((item = oldLayout2->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout2;
    }
    QVBoxLayout *l2 = new QVBoxLayout(ui->statsWidgetProjPrio);
    l2->addWidget(barView);
}

// Projets - Init & Load
void MainWindow::initProjetsUi()
{
    ui->tableProjets->setColumnCount(8);
    ui->tableProjets->setHorizontalHeaderLabels({
        "Nom Projet","Description","Objectifs",
        "Date Début","Date Fin Prévue","Date Fin Réelle",
        "Statut","Priorité"
    });
    ui->tableProjets->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableProjets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableProjets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableProjets->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableProjets->verticalHeader()->setVisible(false);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    // filter date default
    ui->dateDuProj->setDate(QDate(2000, 1, 1));

    // live search
    connect(ui->lineSearchProj, &QLineEdit::textChanged, this, [this]() {
        on_btnAppliquerProj_clicked();
    });

    loadProjets();
}

void MainWindow::loadProjets()
{
    QVector<Projet::Row> rows;
    QString err;
    if (!Projet::chargerTout(rows, &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }
    ui->tableProjets->setRowCount(0);
    for (const auto &row : rows) {
        int r = ui->tableProjets->rowCount();
        ui->tableProjets->insertRow(r);
        auto setItem = [&](int col, const QString &val) {
            auto *item = new QTableWidgetItem(val);
            item->setData(Qt::UserRole, row.id);
            ui->tableProjets->setItem(r, col, item);
        };
        setItem(0, row.nom);
        setItem(1, row.description);
        setItem(2, row.objectifs);
        setItem(3, row.dateDebut);
        setItem(4, row.dateFinPrevue);
        setItem(5, row.dateFinReelle);
        setItem(6, row.statut);
        setItem(7, row.priorite);
    }
}

QString MainWindow::selectedProjetId() const
{
    int r = ui->tableProjets->currentRow();
    if (r < 0) return {};
    auto *item = ui->tableProjets->item(r, 0);
    return item ? item->data(Qt::UserRole).toString() : QString();
}

// Projets - Add
void MainWindow::on_btnAddProj_clicked()
{
    QString nom    = ui->lineTitreAddProj->text().trimmed();
    QString desc   = ui->lineDomaineAddProj->text().trimmed();
    QString obj    = ui->lineEdit->text().trimmed();
    QString statut = ui->lineInventeursAddProj->currentText();
    QString prio   = ui->lineResumeAddProj->currentText();
    QDate   dd     = ui->dateEdit->date();
    QDate   dfp    = ui->dateEdit_2->date();
    QDate   dfr    = ui->dateEdit_3->date();

    // controle de saisie - tous les champs obligatoires
    if (nom.isEmpty() || desc.isEmpty() || obj.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
            "Nom, Description et Objectifs sont obligatoires.");
        return;
    }
    if (dfp < dd) {
        QMessageBox::warning(this, "Dates invalides",
            "La date de fin prévue doit être après la date de début.");
        return;
    }

    Projet p(nom, desc, obj, dd, dfp, dfr, statut, prio);
    QString err;
    if (!p.ajouter(Session::instance().getId().toInt(), &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }

    ui->lineTitreAddProj->clear();
    ui->lineDomaineAddProj->clear();
    ui->lineEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    loadProjets();
    ui->stack_proj->setCurrentIndex(0);
    QMessageBox::information(this, "Succès", "Projet ajouté avec succès.");
}

// Projets - Edit confirm
void MainWindow::on_btnConfirmEditProj_clicked()
{
    if (idProjetToEdit.isEmpty()) return;

    QString nom    = ui->lineTitreEditProj->text().trimmed();
    QString desc   = ui->lineDomaineEditProj->text().trimmed();
    QString obj    = ui->lineEdit_2->text().trimmed();
    QString statut = ui->lineInventeursEditProj->currentText();
    QString prio   = ui->lineResumeEditProj->currentText();
    QDate   dd     = ui->dateEdit_5->date();
    QDate   dfp    = ui->dateEdit_6->date();
    QDate   dfr    = ui->dateEdit_4->date();

    // controle de saisie
    if (nom.isEmpty() || desc.isEmpty() || obj.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
            "Nom, Description et Objectifs sont obligatoires.");
        return;
    }
    if (dfp < dd) {
        QMessageBox::warning(this, "Dates invalides",
            "La date de fin prévue doit être après la date de début.");
        return;
    }

    QString err;
    if (!Projet::modifier(idProjetToEdit, nom, desc, obj, dd, dfp, dfr, statut, prio, &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }

    idProjetToEdit.clear();
    loadProjets();
    ui->stack_proj->setCurrentIndex(0);
    QMessageBox::information(this, "Succès", "Projet modifié avec succès.");
}

// Projets - Delete
void MainWindow::on_btnSupprimerProj_clicked()
{
    QString id = selectedProjetId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Sélection", "Veuillez sélectionner un projet à supprimer.");
        return;
    }
    auto reply = QMessageBox::question(this, "Confirmation",
        "Voulez-vous vraiment supprimer ce projet ?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    QString err;
    if (!Projet::supprimer(id, &err)) {
        QMessageBox::critical(this, "Erreur", err);
        return;
    }
    loadProjets();
    QMessageBox::information(this, "Succès", "Projet supprimé.");
}

// Projets - Sort (Trier)
void MainWindow::on_btnAppliquerProj_clicked()
{
    // first unhide all rows
    for (int r = 0; r < ui->tableProjets->rowCount(); ++r)
        ui->tableProjets->setRowHidden(r, false);

    // apply live search filter
    QString search = ui->lineSearchProj->text().trimmed().toLower();
    if (!search.isEmpty()) {
        for (int r = 0; r < ui->tableProjets->rowCount(); ++r) {
            auto *nomItem = ui->tableProjets->item(r, 0);
            bool match = nomItem && nomItem->text().toLower().contains(search);
            ui->tableProjets->setRowHidden(r, !match);
        }
    }

    // sort
    QString sortBy = ui->comboCategorieProj->currentText().toLower();
    if (sortBy == "titre")
        ui->tableProjets->sortItems(0, Qt::AscendingOrder);
    else if (sortBy == "date")
        ui->tableProjets->sortItems(3, Qt::AscendingOrder);
}

// Projets - Filter by date (closest match)
void MainWindow::on_btnFiltrerDateProj_clicked()
{
    QDate target = ui->dateDuProj->date();

    // collect all visible row dates
    int bestRow = -1;
    int bestDiff = INT_MAX;

    for (int r = 0; r < ui->tableProjets->rowCount(); ++r) {
        auto *dateItem = ui->tableProjets->item(r, 3);
        if (!dateItem || dateItem->text().isEmpty()) continue;
        QDate rowDate = QDate::fromString(dateItem->text(), "yyyy-MM-dd");
        if (!rowDate.isValid()) continue;

        int diff = qAbs(rowDate.daysTo(target));
        if (diff < bestDiff) {
            bestDiff = diff;
            bestRow = r;
        }
    }

    if (bestRow < 0) {
        QMessageBox::information(this, "Résultat", "Aucun projet trouvé.");
        return;
    }

    // hide all rows except the best match
    for (int r = 0; r < ui->tableProjets->rowCount(); ++r)
        ui->tableProjets->setRowHidden(r, r != bestRow);

    ui->tableProjets->selectRow(bestRow);
    ui->tableProjets->scrollToItem(ui->tableProjets->item(bestRow, 0));
}


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
    row.categorie = "";
    row.description = item(3) ? item(3)->text() : "";
    row.dateTransaction = item(4) ? item(4)->text() : "";
    row.modePaiement = item(5) ? item(5)->text() : "";
    row.dateCreation = item(6) ? item(6)->text() : "";

    if (ok) *ok = true;
    return row;
}

// ==================== FINANCE CRUD ====================

void MainWindow::initFinanceUi()
{
    ui->FormCode->setReadOnly(true);
    ui->FormCode_2->setReadOnly(true);
    // Date de transaction verrouillée dans modifier (non modifiable après création)
    ui->FormDate_2->setReadOnly(true);
    ui->FormDate_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->FormCategory->setVisible(false);
    ui->LblCat2->setVisible(false);
    ui->FormCategory_2->setVisible(false);
    ui->LblCat2_2->setVisible(false);

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

    // Max 9 chiffres avant la décimale, 2 après — bloque ORA-01438
    auto *amountValidator = new QRegularExpressionValidator(
        QRegularExpression("^\\d{0,9}([,.]\\d{0,2})?$"), this);
    ui->FormAmount->setValidator(amountValidator);
    ui->FormAmount_2->setValidator(amountValidator);

    auto adjustAmount = [](QLineEdit *edit, double delta) {
        if (!edit) return;
        bool ok = false;
        double val = edit->text().trimmed().replace(',', '.').toDouble(&ok);
        if (!ok) val = 0.0;
        val = qMax(0.0, val + delta);
        edit->setText(QString::number(val, 'f', 2));
    };
    connect(ui->BtnAmountDecr, &QPushButton::clicked, this, [=]() { adjustAmount(ui->FormAmount, -1.0); });
    connect(ui->BtnAmountIncr, &QPushButton::clicked, this, [=]() { adjustAmount(ui->FormAmount, +1.0); });
    connect(ui->BtnAmountDecr_2, &QPushButton::clicked, this, [=]() { adjustAmount(ui->FormAmount_2, -1.0); });
    connect(ui->BtnAmountIncr_2, &QPushButton::clicked, this, [=]() { adjustAmount(ui->FormAmount_2, +1.0); });

    auto refreshCodeAdd = [this]() {
        ui->FormCode->setText(generateTxCode(ui->FormType->currentData().toString(),
                                             ui->FormPayMode->currentData().toString()));
    };
    auto refreshCodeEdit = [this]() {
        ui->FormCode_2->setText(generateTxCode(ui->FormType_2->currentData().toString(),
                                               ui->FormPayMode_2->currentData().toString()));
    };
    connect(ui->FormType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int){ refreshCodeAdd(); });
    connect(ui->FormPayMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int){ refreshCodeAdd(); });
    connect(ui->FormType_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int){ refreshCodeEdit(); });
    connect(ui->FormPayMode_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int){ refreshCodeEdit(); });

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

    ui->TableFinance->setColumnCount(7);
    ui->TableFinance->setSortingEnabled(true);
    ui->TableFinance->setHorizontalHeaderLabels({
        "Code", "Type", "Montant", "Description", "Date", "Mode", "Création"
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
        const double montantNum = r.montant.toDouble();
        itMontant->setData(Qt::DisplayRole, QString::number(montantNum, 'f', 2)); // jamais notation scientifique
        itMontant->setData(Qt::UserRole, montantNum); // valeur numérique pour lecture modifier
        itMontant->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->TableFinance->setItem(row, 2, itMontant);

        ui->TableFinance->setItem(row, 3, new QTableWidgetItem(r.description));
        ui->TableFinance->setItem(row, 4, new QTableWidgetItem(r.dateTransaction));
        ui->TableFinance->setItem(row, 5, new QTableWidgetItem(r.modePaiement));
        ui->TableFinance->setItem(row, 6, new QTableWidgetItem(r.dateCreation));

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

    ui->FormCode->setText(generateTxCode(ui->FormType->currentData().toString(),
                                         ui->FormPayMode->currentData().toString()));
    ui->FormAmount->clear();
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
    const QString cat  = (type == "Revenu") ? "Revenu" : "Depense";
    const QString desc = ui->FormDesc->text().trimmed();
    const QDate   dt   = ui->FormDate->date();
    const QDate   dc   = ui->FormCreatedAt->date();

    if (code.isEmpty()) {
        QMessageBox::warning(this, "Ajout", "Code transaction introuvable.");
        return;
    }

    // --- Validation Montant ---
    bool okAmount = false;
    const double montant = ui->FormAmount->text().trimmed().replace(',', '.').toDouble(&okAmount);
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
    if (!ui->TableFinance->item(r, 0)) return;

    ui->FormCode_2->setText(ui->TableFinance->item(r,0)->text());

    // TYPE : lire la valeur DB depuis UserRole (ex: "Depense") pour findData
    const QString typeDb = ui->TableFinance->item(r,1)->data(Qt::UserRole).toString();
    int idxType = ui->FormType_2->findData(typeDb);
    ui->FormType_2->setCurrentIndex(qMax(0, idxType));

    // Montant : valeur numérique stockée en UserRole
    const double montantVal = ui->TableFinance->item(r,2)->data(Qt::UserRole).toDouble();
    ui->FormAmount_2->setText(QString::number(montantVal, 'f', 2));
    ui->FormDesc_2->setText(ui->TableFinance->item(r,3)->text());

    // Date transaction safe
    QDate dt = QDate::fromString(ui->TableFinance->item(r,4)->text(), "yyyy-MM-dd");
    ui->FormDate_2->setDate(dt.isValid() ? dt : QDate::currentDate());

    // MODE : data == "especes/cheque/..."
    const QString modeDb = ui->TableFinance->item(r,5)->text();
    int idxMode = ui->FormPayMode_2->findData(modeDb);
    if (idxMode < 0) idxMode = ui->FormPayMode_2->findText(modeDb);
    ui->FormPayMode_2->setCurrentIndex(qMax(0, idxMode));

    ui->FormCode_2->setText(generateTxCode(ui->FormType_2->currentData().toString(),
                                           ui->FormPayMode_2->currentData().toString()));

    // Date création safe
    QDate dc = QDate::fromString(ui->TableFinance->item(r,6)->text(), "yyyy-MM-dd");
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
    const QString cat  = (type == "Revenu") ? "Revenu" : "Depense";
    const QString desc = ui->FormDesc_2->text().trimmed();
    const QDate   dt   = ui->FormDate_2->date();
    const QDate   dc   = ui->FormCreatedAt_2->date();

    if (code.isEmpty()) {
        QMessageBox::warning(this, "Modifier", "Le code transaction est obligatoire.");
        ui->FormCode_2->setFocus();
        return;
    }

    bool okAmount = false;
    const double montant = ui->FormAmount_2->text().trimmed().replace(',', '.').toDouble(&okAmount);
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

    QString designation = row.description.trimmed();
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

        // Filtre texte libre (code, description)
        if (!search.isEmpty()) {
            const bool match = r.code.toLower().contains(search)
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
        const double montantNum2 = r.montant.toDouble();
        itMontant->setData(Qt::DisplayRole, QString::number(montantNum2, 'f', 2));
        itMontant->setData(Qt::UserRole, montantNum2);
        itMontant->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->TableFinance->setItem(row, 2, itMontant);

        ui->TableFinance->setItem(row, 3, new QTableWidgetItem(r.description));
        ui->TableFinance->setItem(row, 4, new QTableWidgetItem(r.dateTransaction));
        ui->TableFinance->setItem(row, 5, new QTableWidgetItem(r.modePaiement));
        ui->TableFinance->setItem(row, 6, new QTableWidgetItem(r.dateCreation));
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
    on_BtnApply_clicked();
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
static bool publicationNumeroExists(int numeroBrevet, const QString &excludeId = "")
{
    if (numeroBrevet <= 0)
        return false;

    QSqlQuery query;

    if (excludeId.isEmpty()) {
        query.prepare("SELECT COUNT(*) FROM PUBLICATIONS WHERE NUMERO_BREVET = :num");
        query.bindValue(":num", numeroBrevet);
    } else {
        query.prepare("SELECT COUNT(*) FROM PUBLICATIONS "
                      "WHERE NUMERO_BREVET = :num "
                      "AND ID_PUBLICATION <> :id");
        query.bindValue(":num", numeroBrevet);
        query.bindValue(":id", excludeId);
    }

    if (!query.exec()) {
        qDebug() << "Erreur vérification numéro brevet unique:" << query.lastError().text();
        return false;
    }

    if (query.next())
        return query.value(0).toInt() > 0;

    return false;
}
static void setFieldError(QWidget *w)
{
    if (!w) return;
    w->setStyleSheet(
        "border:2px solid red;"
        "background-color:#ffe6e6;"
        "color:black;"
    );
}

static void clearFieldError(QWidget *w)
{
    if (!w) return;
    w->setStyleSheet("");
}

static bool publicationTitleExists(const QString &titre, const QString &excludeId = "")
{
    QSqlQuery query;

    if (excludeId.isEmpty()) {
        query.prepare("SELECT COUNT(*) FROM PUBLICATIONS WHERE LOWER(TRIM(TITRE)) = LOWER(TRIM(:titre))");
        query.bindValue(":titre", titre);
    } else {
        query.prepare("SELECT COUNT(*) FROM PUBLICATIONS "
                      "WHERE LOWER(TRIM(TITRE)) = LOWER(TRIM(:titre)) "
                      "AND ID_PUBLICATION <> :id");
        query.bindValue(":titre", titre);
        query.bindValue(":id", excludeId);
    }

    if (!query.exec()) {
        qDebug() << "Erreur vérification titre unique:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
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

void MainWindow::on_btnModifierPub_clicked()
{
    // Colonnes : 0=titre(+id UserRole), 1=inventeurs, 2=domaine, 3=type,
    //            4=numeroBrevet, 5=dateDepot, 6=statut, 7=resume
    const int row = ui->tablePublication->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Modification", "Veuillez sélectionner une publication à modifier.");
        return;
    }
    idPublicationToEdit = selectedPublicationId();
    if (idPublicationToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modification", "ID publication introuvable.");
        return;
    }
    if (!ui->tablePublication->item(row, 0)) return;

    ui->lineTitreEdit->setText(ui->tablePublication->item(row, 0)->text());
    ui->lineInventeursEdit->setCurrentText(ui->tablePublication->item(row, 1)->text());
    ui->lineDomaineEdit->setText(ui->tablePublication->item(row, 2)->text());
    ui->comboTypeBrevetEdit->setCurrentText(ui->tablePublication->item(row, 3)->text());
    ui->lineNumeroBrevetEdit->setText(ui->tablePublication->item(row, 4)->text());
    QDate d = QDate::fromString(ui->tablePublication->item(row, 5)->text(), "yyyy-MM-dd");
    ui->dateDepotEdit->setDate(d.isValid() ? d : QDate::currentDate());
    ui->comboStatusBrevetEdit->setCurrentText(ui->tablePublication->item(row, 6)->text());
    ui->lineResumeEdit->setText(ui->tablePublication->item(row, 7)->text());

    ui->stack_pub->setCurrentIndex(2);
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
    QString inventeurs  = ui->lineInventeursAdd->currentText().trimmed(); // si QComboBox
    QString resume      = ui->lineResumeAdd->text().trimmed();
    QString domaine     = ui->lineDomaineAdd->text().trimmed();
    QString typeBrevet  = ui->comboTypeBrevetAdd->currentText().trimmed();
    QString statut      = ui->comboStatusBrevetAdd->currentText().trimmed();
    QString numText     = ui->lineNumeroBrevetAdd->text().trimmed();
    QDate dateDepot     = ui->dateDepotAdd->date();

    // Reset erreurs visuelles
    clearFieldError(ui->lineTitreAdd);
    clearFieldError(ui->lineInventeursAdd);
    clearFieldError(ui->lineResumeAdd);
    clearFieldError(ui->lineDomaineAdd);
    clearFieldError(ui->lineNumeroBrevetAdd);
    clearFieldError(ui->dateDepotAdd);
    clearFieldError(ui->comboTypeBrevetAdd);
    clearFieldError(ui->comboStatusBrevetAdd);

    bool hasError = false;

    // ===== Validation titre =====
    if (titre.isEmpty()) {
        setFieldError(ui->lineTitreAdd);
        hasError = true;
    } else if (publicationTitleExists(titre)) {
        setFieldError(ui->lineTitreAdd);
        QMessageBox::warning(this, "Ajout",
                             "Erreur : ce titre existe déjà, le titre doit être unique.");
        return;
    }

    // ===== Validation inventeurs =====
    if (inventeurs.isEmpty()) {
        setFieldError(ui->lineInventeursAdd);
        hasError = true;
    }

    // ===== Validation résumé =====
    if (resume.isEmpty()) {
        setFieldError(ui->lineResumeAdd);
        hasError = true;
    }

    // ===== Validation domaine =====
    if (domaine.isEmpty()) {
        setFieldError(ui->lineDomaineAdd);
        hasError = true;
    }

    // ===== Validation type brevet =====
    if (typeBrevet.isEmpty()) {
        setFieldError(ui->comboTypeBrevetAdd);
        hasError = true;
    }

    // ===== Validation statut =====
    if (statut.isEmpty()) {
        setFieldError(ui->comboStatusBrevetAdd);
        hasError = true;
    }

    // ===== Validation numéro brevet =====
    bool okNum = false;
    int numeroBrevet = 0;

    if (numText.isEmpty()) {
        setFieldError(ui->lineNumeroBrevetAdd);
        hasError = true;
    } else {
        numeroBrevet = numText.toInt(&okNum);
        if (!okNum || numeroBrevet <= 0) {
            setFieldError(ui->lineNumeroBrevetAdd);
            hasError = true;
        } else if (publicationNumeroExists(numeroBrevet)) {
            setFieldError(ui->lineNumeroBrevetAdd);
            QMessageBox::warning(this, "Ajout",
                                 "Erreur : ce numéro de brevet existe déjà, le numéro doit être unique.");
            return;
        }
    }

    // ===== Validation date =====
    if (!dateDepot.isValid()) {
        setFieldError(ui->dateDepotAdd);
        hasError = true;
    }

    if (hasError) {
        QMessageBox::warning(this, "Ajout", "Veuillez corriger les champs en rouge.");
        return;
    }

    QString idEmp = "7"; // à remplacer par l'id employé connecté si disponible

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

    QMessageBox::information(this, "Succès", "Publication ajoutée avec succès.");

    ui->lineTitreAdd->clear();
    ui->lineResumeAdd->clear();
    ui->lineDomaineAdd->clear();
    ui->lineNumeroBrevetAdd->clear();
    ui->dateDepotAdd->setDate(QDate::currentDate());
    ui->comboTypeBrevetAdd->setCurrentIndex(0);
    ui->comboStatusBrevetAdd->setCurrentIndex(0);
    ui->lineInventeursAdd->setCurrentIndex(0); // si QComboBox

    loadPublications();
    ui->stack_pub->setCurrentIndex(0);
}

void MainWindow::on_btnConfirmEditPub_clicked()
{
    if (idPublicationToEdit.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Aucune publication sélectionnée.");
        return;
    }

    QString titre       = ui->lineTitreEdit->text().trimmed();
    QString inventeurs  = ui->lineInventeursEdit->currentText().trimmed(); // si QComboBox
    QString resume      = ui->lineResumeEdit->text().trimmed();
    QString domaine     = ui->lineDomaineEdit->text().trimmed();
    QString typeBrevet  = ui->comboTypeBrevetEdit->currentText().trimmed();
    QString statut      = ui->comboStatusBrevetEdit->currentText().trimmed();
    QString numText     = ui->lineNumeroBrevetEdit->text().trimmed();
    QDate dateDepot     = ui->dateDepotEdit->date();

    // Reset erreurs visuelles
    clearFieldError(ui->lineTitreEdit);
    clearFieldError(ui->lineInventeursEdit);
    clearFieldError(ui->lineResumeEdit);
    clearFieldError(ui->lineDomaineEdit);
    clearFieldError(ui->lineNumeroBrevetEdit);
    clearFieldError(ui->dateDepotEdit);
    clearFieldError(ui->comboTypeBrevetEdit);
    clearFieldError(ui->comboStatusBrevetEdit);

    bool hasError = false;

    // ===== Validation titre =====
    if (titre.isEmpty()) {
        setFieldError(ui->lineTitreEdit);
        hasError = true;
    } else if (publicationTitleExists(titre, idPublicationToEdit)) {
        setFieldError(ui->lineTitreEdit);
        QMessageBox::warning(this, "Modification",
                             "Erreur : ce titre existe déjà, le titre doit être unique.");
        return;
    }

    // ===== Validation inventeurs =====
    if (inventeurs.isEmpty()) {
        setFieldError(ui->lineInventeursEdit);
        hasError = true;
    }

    // ===== Validation résumé =====
    if (resume.isEmpty()) {
        setFieldError(ui->lineResumeEdit);
        hasError = true;
    }

    // ===== Validation domaine =====
    if (domaine.isEmpty()) {
        setFieldError(ui->lineDomaineEdit);
        hasError = true;
    }

    // ===== Validation type brevet =====
    if (typeBrevet.isEmpty()) {
        setFieldError(ui->comboTypeBrevetEdit);
        hasError = true;
    }

    // ===== Validation statut =====
    if (statut.isEmpty()) {
        setFieldError(ui->comboStatusBrevetEdit);
        hasError = true;
    }

    // ===== Validation numéro brevet =====
    bool okNum = false;
    int numeroBrevet = 0;

    if (numText.isEmpty()) {
        setFieldError(ui->lineNumeroBrevetEdit);
        hasError = true;
    } else {
        numeroBrevet = numText.toInt(&okNum);
        if (!okNum || numeroBrevet <= 0) {
            setFieldError(ui->lineNumeroBrevetEdit);
            hasError = true;
        } else if (publicationNumeroExists(numeroBrevet, idPublicationToEdit)) {
            setFieldError(ui->lineNumeroBrevetEdit);
            QMessageBox::warning(this, "Modification",
                                 "Erreur : ce numéro de brevet existe déjà, le numéro doit être unique.");
            return;
        }
    }

    // ===== Validation date =====
    if (!dateDepot.isValid()) {
        setFieldError(ui->dateDepotEdit);
        hasError = true;
    }

    if (hasError) {
        QMessageBox::warning(this, "Modification", "Veuillez corriger les champs en rouge.");
        return;
    }

    QString idEmp = "7"; // à remplacer par l'id employé connecté si disponible

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

    QMessageBox::information(this, "Succès", "Publication modifiée avec succès.");

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
    if (!ui->tablePublication->item(row, 0)) return;

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
            y += 40; // espace avant le titre "Suite"

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
        auto *it0 = ui->tablePublication->item(i, 0);
        auto *it4 = ui->tablePublication->item(i, 4);
        if (!it0 || !it4) continue;
        QString titre  = it0->text().toLower();
        QString numero = it4->text().toLower();

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
void MainWindow::lancerServeurIA() {
    QString scriptPath = QCoreApplication::applicationDirPath() + "/face_id_vortex.py";
    QFile file(scriptPath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "from flask import Flask, request, jsonify\n"
            << "import cv2\n"
            << "import numpy as np\n"
            << "import os\n\n"
            << "app = Flask(__name__)\n"
            << "face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')\n\n"

            << "@app.route('/enroll', methods=['POST'])\n"
            << "def enroll():\n"
            << "    if 'face' in request.files:\n"
            << "        username = request.form.get('username', 'user')\n"
            << "        img = cv2.imdecode(np.frombuffer(request.files['face'].read(), np.uint8), cv2.IMREAD_COLOR)\n"
            << "        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)\n"
            << "        faces = face_cascade.detectMultiScale(gray, 1.1, 4)\n"
            << "        if len(faces) > 0:\n"
            << "            x, y, w, h = faces[0]\n"
            << "            face_crop = img[y:y+h, x:x+w]\n"
            << "            cv2.imwrite(f'{username}_ref.jpg', face_crop)\n"
            << "            return jsonify({'success': True})\n"
            << "    return jsonify({'success': False})\n\n"

            << "@app.route('/verify', methods=['POST'])\n"
            << "def verify():\n"
            << "    if 'face' in request.files:\n"
            << "        username = request.form.get('username', 'user')\n"
            << "        ref_path = f'{username}_ref.jpg'\n"
            << "        if not os.path.exists(ref_path): return jsonify({'verified': False})\n"
            << "        img_ref = cv2.imread(ref_path, 0)\n"
            << "        img_new = cv2.imdecode(np.frombuffer(request.files['face'].read(), np.uint8), cv2.IMREAD_GRAYSCALE)\n"
            << "        faces = face_cascade.detectMultiScale(img_new, 1.1, 4)\n"
            << "        if len(faces) > 0:\n"
            << "            x, y, w, h = faces[0]\n"
            << "            curr = cv2.resize(img_new[y:y+h, x:x+w], (img_ref.shape[1], img_ref.shape[0]))\n"
            << "            score = cv2.matchTemplate(curr, img_ref, cv2.TM_CCOEFF_NORMED).max()\n"
            << "            return jsonify({'verified': bool(score > 0.7)})\n"
            << "    return jsonify({'verified': False})\n\n"

            << "if __name__ == '__main__':\n"
            << "    app.run(host='127.0.0.1', port=5000)\n";
        file.close();
    }
    if (!processIA) processIA = new QProcess(this);
    processIA->start("python", QStringList() << scriptPath);
}
static void updatePasswordStrengthUiAddEmp(const QString &password, QProgressBar *bar, QLabel *label)
{
    if (!bar || !label)
        return;

    bar->setRange(0, 100);

    if (password.isEmpty()) {
        bar->setValue(0);
        label->setText(QStringLiteral("—"));
        label->setStyleSheet(QStringLiteral("color: #888; font-weight: 600; font-size: 11px;"));
        bar->setStyleSheet(
            QStringLiteral("QProgressBar { border: 1px solid rgba(0,0,0,0.12); border-radius: 6px; background: #ececec; "
                           "min-height: 12px; max-height: 14px; }"
                           "QProgressBar::chunk { border-radius: 5px; background: #bdbdbd; }"));
        return;
    }

    const int percent = Employe::motDePasseForcePourcent(password);
    bar->setValue(percent);

    QString text;
    QString chunk;
    if (percent < 28) {
        text = QStringLiteral("Très faible");
        chunk = QStringLiteral("#c62828");
    } else if (percent < 45) {
        text = QStringLiteral("Faible");
        chunk = QStringLiteral("#e65100");
    } else if (percent < 62) {
        text = QStringLiteral("Moyen");
        chunk = QStringLiteral("#f57f17");
    } else if (percent < 82) {
        text = QStringLiteral("Fort");
        chunk = QStringLiteral("#558b2f");
    } else {
        text = QStringLiteral("Très fort");
        chunk = QStringLiteral("#1b5e20");
    }

    label->setText(text);
    label->setStyleSheet(QStringLiteral("color: %1; font-weight: 700; font-size: 11px;").arg(chunk));
    bar->setStyleSheet(
        QStringLiteral("QProgressBar { border: 1px solid rgba(0,0,0,0.12); border-radius: 6px; background: #f0f0f0; "
                       "min-height: 12px; max-height: 14px; }"
                       "QProgressBar::chunk { border-radius: 5px; background: %1; }")
            .arg(chunk));
}

static void setEmployeComboValue(QComboBox *cb, const QString &val)
{
    const QString t = val.trimmed();
    if (t.isEmpty()) {
        cb->setCurrentIndex(0);
        return;
    }
    int idx = cb->findText(t, Qt::MatchExactly);
    if (idx < 0)
        cb->addItem(t);
    cb->setCurrentText(t);
}

/** Envoi SMTP employé (expéditeur visible rh@… — même paramètres que la vérification). */
static bool envoyerMailServiceRh(const QString &destinataire,
                                 const QString &sujet,
                                 const QString &corps,
                                 QString &erreur)
{
    MailSender sender;
    const QString smtpUser = QStringLiteral("rrayyyrrayyy@gmail.com");
    const QString smtpPass = QStringLiteral("qxel rihn nrrl fgtq");
    const QString expediteurService = QStringLiteral("Service RH — SmartResearchLab");
    const QString expediteurAdresseRh = QStringLiteral("rh@smartresearchlab.tn");
    return sender.envoyerMail(smtpUser, smtpPass, destinataire, sujet, corps, erreur,
                              expediteurService, expediteurAdresseRh);
}

/** Même compte SMTP pour l’envoi ; l’en-tête From affiche rh@… (à aligner sur votre domaine / Gmail « Envoyer au nom de »). */
static bool verifierEmailEmployeParCode(const QString &email, QWidget *parent)
{
    const QString code = QString::number(QRandomGenerator::global()->bounded(100000, 1000000));

    QString err;
    const QString sujet = QStringLiteral("Code de vérification — RH");
    const QString corps = QStringLiteral(
        "Bonjour,\n\n"
        "Ceci est un message automatique du service Ressources humaines (RH).\n\n"
        "Votre code de vérification pour confirmer cette adresse e-mail est :\n\n"
        "%1\n\n"
        "Saisissez ce code dans l’application pour finaliser l’enregistrement.\n"
        "Si vous n’êtes pas à l’origine de cette demande, ignorez ce message.\n"
    ).arg(code);

    if (!envoyerMailServiceRh(email, sujet, corps, err)) {
        QMessageBox::critical(parent, QStringLiteral("Envoi impossible"),
                              QStringLiteral("Impossible d'envoyer le code :\n%1").arg(err));
        return false;
    }

    QMessageBox::information(
        parent,
        QStringLiteral("Étape suivante : vérification e-mail"),
        QStringLiteral("Un code à 6 chiffres vient d’être envoyé à :\n%1\n\n"
                        "Vérifiez votre boîte de réception (et les spams / courrier indésirable si besoin). "
                        "Ensuite, saisissez exactement le code dans la fenêtre suivante.").arg(email));

    bool okDialog = false;
    const QString saisi = QInputDialog::getText(
        parent,
        QStringLiteral("Code de vérification"),
        QStringLiteral("Entrez le code à 6 chiffres reçu par e-mail (sans espace) :"),
        QLineEdit::Normal,
        QString(),
        &okDialog).trimmed();

    if (!okDialog)
        return false;

    if (saisi != code) {
        QMessageBox::warning(parent, QStringLiteral("Code incorrect"),
                             QStringLiteral("Le code ne correspond pas. Réessayez en enregistrant à nouveau pour recevoir un nouveau code."));
        return false;
    }

    return true;
}

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
    // --- 1. RÉCUPÉRATION DES DONNÉES ---
    QString cin         = ui->lineCINAdd->text().trimmed();
    QString username    = ui->lineUsernameAdd->text().trimmed();
    QString password    = ui->linePasswordAdd->text();
    QString email       = ui->lineEmailAdd->text().trimmed();
    QString nom         = ui->lineNomAdd->text().trimmed();
    QString prenom      = ui->linePrenomAdd->text().trimmed();
    QString role        = ui->comboRoleAdd->currentText();
    QString departement = ui->comboDepartementAdd->currentText().trimmed();
    QString poste       = ui->comboPosteAdd->currentText().trimmed();
    QDate dateEmb       = ui->dateEmbaucheAdd->date();
    QString salaireStr  = ui->lineSalaireAdd->text().trimmed();

    // --- 2. CONTRÔLES DE SÉCURITÉ & SAISIE ---

    // A. Vérification des champs vides obligatoires
    if (cin.isEmpty() || username.isEmpty() || password.isEmpty() || nom.isEmpty() || prenom.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Tous les champs obligatoires doivent être remplis.");
        return;
    }

    // B. Contrôle CIN (8 chiffres exactement)
    QRegularExpression rxCin("^[0-9]{8}$");
    if (!rxCin.match(cin).hasMatch()) {
        QMessageBox::warning(this, "Erreur CIN", "Le CIN doit contenir exactement 8 chiffres.");
        ui->lineCINAdd->setFocus();
        return;
    }
    if (Employe::existe(cin)) {
        QMessageBox::critical(this, "Erreur Doublon", "Ce CIN est déjà enregistré dans le système.");
        ui->lineCINAdd->setFocus();
        return;
    }

    // C. Contrôle Nom et Prénom (Lettres uniquement)
    QRegularExpression rxAlpha("^[A-Za-zÀ-ÿ\\s-]+$");
    if (!rxAlpha.match(nom).hasMatch() || !rxAlpha.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Format Nom/Prénom", "Le nom et le prénom ne doivent contenir que des lettres.");
        return;
    }

    // D. Contrôle Email (Format standard)
    QRegularExpression rxEmail("^[\\w\\.-]+@[\\w\\.-]+\\.[a-z]{2,4}$");
    if (!rxEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Format Email", "L'adresse email n'est pas valide.");
        ui->lineEmailAdd->setFocus();
        return;
    }
    if (Employe::emailExiste(email)) {
            QMessageBox::critical(this, "Doublon détecté",
                                   "Cet email est déjà utilisé par un autre employé.\nVeuillez en saisir un autre.");
            ui->lineEmailAdd->setFocus();
            return;
        }

    // E. Contrôle Salaire (Doit être un nombre positif)
    bool okSalaire;
    double salaire = salaireStr.toDouble(&okSalaire);
    if (!okSalaire || salaire < 0) {
        QMessageBox::warning(this, "Erreur Salaire", "Veuillez saisir un salaire valide (nombre positif).");
        ui->lineSalaireAdd->setFocus();
        return;
    }
    // Vérification spécifique pour les menus déroulants
    if (ui->comboRoleAdd->currentIndex() <= 0) { // En supposant que l'index 0 est "Choisir..."
        QMessageBox::warning(this, "Sélection requise", "Veuillez attribuer un rôle à l'employé.");
        ui->comboRoleAdd->setFocus();
        return;
    }

    if (ui->comboDepartementAdd->currentIndex() <= 0) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner un département.");
        ui->comboDepartementAdd->setFocus();
        return;
    }

    if (ui->comboPosteAdd->currentIndex() <= 0) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez définir le poste de l'employé.");
        ui->comboPosteAdd->setFocus();
        return;
    }

    // F. Vérification de la BIOMÉTRIE
    if (this->m_tempFaceEncoding.isEmpty()) {
        QMessageBox::warning(this, "Biométrie manquante", "Veuillez scanner le visage de l'employé avant l'enregistrement.");
        return;
    }

    // --- 3. SYSTÈME DE VÉRIFICATION PAR MAIL (OTP) ---

    int codeGenere = QRandomGenerator::global()->bounded(100000, 999999);
    QString codeStr = QString::number(codeGenere);

    QApplication::setOverrideCursor(Qt::WaitCursor); // Curseur d'attente
    QString errMail;
    bool mailEnvoye = envoyerMailServiceRh(email, "Vérification de sécurité",
                                           "Bonjour " + prenom + ",\n\nVotre code de confirmation est : " + codeStr,
                                           errMail);
    QApplication::restoreOverrideCursor();

    if (!mailEnvoye) {
        QMessageBox::critical(this, "Erreur Mail", "Échec de l'envoi du code à " + email + ".\nErreur : " + errMail);
        return;
    }

    // Demander le code à l'utilisateur
    bool okInput;
    QString codeSaisi = QInputDialog::getText(this, "Vérification Email",
                                              "Un code a été envoyé à : " + email + "\nVeuillez le saisir :",
                                              QLineEdit::Normal, "", &okInput);

    if (!okInput || codeSaisi != codeStr) {
        QMessageBox::warning(this, "Vérification échouée", "Code incorrect ou opération annulée.");
        return;
    }

    // --- 4. TRAITEMENT ET ENREGISTREMENT FINAL ---

    // Hachage du mot de passe
    QString passHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    // Création et insertion
    Employe e(cin, nom, prenom, username, passHash, email, poste, departement, dateEmb, salaire, role, this->m_tempFaceEncoding);

    QString errMsg;
    if (e.ajouter(&errMsg)) {
        QMessageBox::information(this, "Succès", "L'employé " + nom + " a été ajouté avec succès !");

        // RESET
        this->m_tempFaceEncoding.clear();
        loadEmployees();
        ajouterNotification("SYSTÈME", "Nouvel employé : " + username);

        // Vidage des champs
        ui->lineCINAdd->clear();
        ui->lineUsernameAdd->clear();
        ui->linePasswordAdd->clear();
        ui->lineEmailAdd->clear();
        ui->lineNomAdd->clear();
        ui->linePrenomAdd->clear();
        ui->lineSalaireAdd->clear();
        ui->comboRoleAdd->setCurrentIndex(0);
        ui->comboDepartementAdd->setCurrentIndex(0);
        ui->comboPosteAdd->setCurrentIndex(0);

        ui->stack_emp->setCurrentIndex(0); // Retour à la liste
    } else {
        QMessageBox::critical(this, "Erreur Base de Données", "L'ajout a échoué :\n" + errMsg);
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
    if (!item) return;

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
        ajouterNotification("SUPPRESSION", "CIN: " + idEmploye);    }
    else
    {
        QMessageBox::critical(this, "Erreur",
                              "Suppression échouée :\n" + err);
    }
}

void MainWindow::on_btnScanFace_clicked()
{
    QString username = ui->lineUsernameAdd->text().trimmed();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Saisis un username avant de scanner.");
        return;
    }

    QCamera *camera = new QCamera(QMediaDevices::defaultVideoInput(), this);
    QImageCapture *capture = new QImageCapture(this);
    QMediaCaptureSession *session = new QMediaCaptureSession(this);
    session->setCamera(camera);
    session->setImageCapture(capture);
    camera->start();

    QEventLoop loop;
    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    loop.exec();

    capture->capture();

    connect(capture, &QImageCapture::imageCaptured, [=](int id, const QImage &img) {
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        img.save(&buf, "JPG");

        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart namePart;
        namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
        namePart.setBody(username.toUtf8());
        multiPart->append(namePart);

        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"face\"; filename=\"ref.jpg\""));
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        imagePart.setBody(ba);
        multiPart->append(imagePart);

        QNetworkRequest request(QUrl("http://127.0.0.1:5000/enroll"));
        QNetworkReply *reply = networkManager->post(request, multiPart);
        multiPart->setParent(reply);

        connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QJsonObject res = QJsonDocument::fromJson(reply->readAll()).object();
                if (res["success"].toBool()) {
                    this->m_tempFaceEncoding = "VALIDATED"; // Prêt pour l'insertion SQL
                    QMessageBox::information(this, "Succès", "Visage de référence enregistré !");
                }
            }
            camera->stop();
            camera->deleteLater();
            reply->deleteLater();
        });
    });
}
void MainWindow::on_btnModifier_emp_clicked()
{
    int row = ui->TableEmp->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Sélection", "Veuillez sélectionner un employé.");
        return;
    }
    if (!ui->TableEmp->item(row, 0)) return;

    // Remplissage des champs de l'interface de modification
    ui->lineCIN_emp->setText(ui->TableEmp->item(row, 0)->text());
    ui->lineNomEmp->setText(ui->TableEmp->item(row, 1)->text());
    ui->linePrenomEmp->setText(ui->TableEmp->item(row, 2)->text());
    ui->lineUsernameEmp->setText(ui->TableEmp->item(row, 3)->text());
    ui->lineEmailEmp->setText(ui->TableEmp->item(row, 4)->text());
    setEmployeComboValue(ui->comboPosteEmp, ui->TableEmp->item(row, 5)->text());
    setEmployeComboValue(ui->comboDepartementEmp, ui->TableEmp->item(row, 6)->text());
    ui->dateEmbaucheEmp->setDate(QDate::fromString(ui->TableEmp->item(row, 7)->text(), "yyyy-MM-dd"));
    ui->lineSalaireEmp->setText(ui->TableEmp->item(row, 8)->text());
    ui->comboRoleAdd_2->setCurrentText(ui->TableEmp->item(row, 9)->text());
    m_emailEmployeEditOriginal = ui->TableEmp->item(row, 4)->text().trimmed();
    ui->stack_emp->setCurrentIndex(2); // Aller vers la page de modif
}
void MainWindow::on_btnSaveEditEmployee_clicked()
{
    int row = ui->TableEmp->currentRow();
    if (row < 0) return;
    if (!ui->TableEmp->item(row, 0)) return;

    QString idEmploye = ui->TableEmp->item(row, 0)->data(Qt::UserRole).toString();

    // Récupération des saisies
    QString cin      = ui->lineCIN_emp->text().trimmed();
    QString nom      = ui->lineNomEmp->text().trimmed();
    QString prenom   = ui->linePrenomEmp->text().trimmed();
    QString username = ui->lineUsernameEmp->text().trimmed();
    QString email    = ui->lineEmailEmp->text().trimmed();
    QString salaireS = ui->lineSalaireEmp->text().trimmed();
    int index = ui->comboRoleAdd_2->currentIndex();

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
    if (Employe::emailExiste(email, idEmploye)) {
        QMessageBox::warning(this, "Doublon", "Cet e-mail est déjà utilisé par un autre employé.");
        return;
    }

    // 4. Validation : Unicité CIN / username (table affichée)
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
    }
    if (index == 0) {
        // Afficher un message d'alerte
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un rôle avant de continuer.");
        return; // On arrête la fonction ici
    }

    const QString posteEdit = ui->comboPosteEmp->currentText().trimmed();
    const QString deptEdit  = ui->comboDepartementEmp->currentText().trimmed();
    if (ui->comboPosteEmp->currentIndex() == 0 || posteEdit.isEmpty()
        || posteEdit == QStringLiteral("Choisir un poste")) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez choisir un poste dans la liste.");
        ui->comboPosteEmp->setFocus();
        return;
    }
    if (ui->comboDepartementEmp->currentIndex() == 0 || deptEdit.isEmpty()
        || deptEdit == QStringLiteral("Choisir un département")) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez choisir un département dans la liste.");
        ui->comboDepartementEmp->setFocus();
        return;
    }

    if (email.compare(m_emailEmployeEditOriginal, Qt::CaseInsensitive) != 0) {
        if (!verifierEmailEmployeParCode(email, this))
            return;
    }

    // 5. Exécution de l'Update
    Employe e(cin, nom, prenom, username, "", email,
              posteEdit,
              deptEdit,
              ui->dateEmbaucheEmp->date(),
              salaireS.toDouble(),
              ui->comboRoleAdd_2->currentText());

    QString errMsg;
    if (e.modifier(idEmploye, &errMsg)) {
        QMessageBox::information(this, "Succès", "L'employé a été mis à jour.");
        loadEmployees();
        ajouterNotification("MODIFICATION", "Employé: " + nom);
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

    // Sinon : filtrer sur toutes les colonnes affichées (CIN, noms, identifiant, e-mail, etc.)
    for (int row = 0; row < ui->TableEmp->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < ui->TableEmp->columnCount(); ++col) {
            const QTableWidgetItem *item = ui->TableEmp->item(row, col);
            if (item && item->text().toLower().contains(search)) {
                match = true;
                break;
            }
        }
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
void MainWindow::ajouterNotification(const QString &actionType, const QString &cible)
{
    NotifEntry entry;
    entry.actionType = actionType;
    entry.cible      = cible;
    entry.time       = QTime::currentTime().toString("HH:mm");
    entry.user       = Session::instance().getNom();
    entry.role       = Session::instance().getRole();
    entry.read       = false;
    m_notifications.append(entry);
    m_unreadCount++;

    updateNotifBadge();

    // Si le panneau est ouvert, le reconstruire en direct
    if (m_notifPanel && m_notifPanel->isVisible())
        rebuildNotifPanel();
}

// ─────────────────────────────────────────────────────────────────────────────
// setupNotifButton : transforme btnNotif en cloche + crée badge + panneau
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setupNotifButton()
{
    // Bell button
    ui->btnNotif->setText("\U0001F514");
    ui->btnNotif->setFixedSize(40, 40);
    ui->btnNotif->setObjectName("btnNotif");
    ui->btnNotif->setCursor(Qt::PointingHandCursor);
    ui->btnNotif->setFocusPolicy(Qt::NoFocus);
    ui->btnNotif->setToolTip("Notifications");
    connect(ui->btnNotif, &QPushButton::clicked, this, &MainWindow::toggleNotifPanel);

    // Badge rouge (child de topBar, superposé sur btnNotif)
    m_notifBadge = new QLabel(ui->topBar);
    m_notifBadge->setObjectName("notifBadge");
    m_notifBadge->setFixedSize(18, 18);
    m_notifBadge->setAlignment(Qt::AlignCenter);
    m_notifBadge->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_notifBadge->raise();
    m_notifBadge->hide();

    // Panneau de notifications (child du MainWindow, flottant)
    m_notifPanel = new QFrame(this);
    m_notifPanel->setObjectName("notifPanel");
    m_notifPanel->setFixedWidth(360);
    m_notifPanel->hide();
    m_notifPanel->raise();

    // Filtre global pour fermer le panneau au clic extérieur
    qApp->installEventFilter(this);
}

// ─────────────────────────────────────────────────────────────────────────────
// toggleNotifPanel : ouvre / ferme le panneau avec animation
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::toggleNotifPanel()
{
    if (!m_notifPanel) return;

    if (m_notifPanel->isVisible()) {
        // Fermer avec fade-out
        auto *eff = qobject_cast<QGraphicsOpacityEffect*>(m_notifPanel->graphicsEffect());
        if (!eff) {
            eff = new QGraphicsOpacityEffect(m_notifPanel);
            m_notifPanel->setGraphicsEffect(eff);
        }
        auto *fadeOut = new QPropertyAnimation(eff, "opacity", this);
        fadeOut->setDuration(160);
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->setEasingCurve(QEasingCurve::OutQuad);
        connect(fadeOut, &QPropertyAnimation::finished, m_notifPanel, &QFrame::hide);
        fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        // Reconstruire le contenu
        rebuildNotifPanel();

        // Positionner sous btnNotif, aligné à droite
        QPoint gp = ui->btnNotif->mapToGlobal(QPoint(0, ui->btnNotif->height() + 6));
        QPoint lp = this->mapFromGlobal(gp);
        int x = lp.x() + ui->btnNotif->width() - m_notifPanel->width();
        m_notifPanel->move(qMax(x, 8), lp.y());
        m_notifPanel->raise();

        // Ouvrir avec fade-in
        auto *eff = new QGraphicsOpacityEffect(m_notifPanel);
        eff->setOpacity(0.0);
        m_notifPanel->setGraphicsEffect(eff);
        m_notifPanel->show();

        auto *fadeIn = new QPropertyAnimation(eff, "opacity", this);
        fadeIn->setDuration(200);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->setEasingCurve(QEasingCurve::OutQuad);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// rebuildNotifPanel : reconstruit le contenu du panneau
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::rebuildNotifPanel()
{
    // Supprimer l'ancien layout
    if (m_notifPanel->layout()) {
        QLayout *old = m_notifPanel->layout();
        QLayoutItem *item;
        while ((item = old->takeAt(0)) != nullptr) {
            if (item->widget()) item->widget()->deleteLater();
            delete item;
        }
        delete old;
    }

    QVBoxLayout *root = new QVBoxLayout(m_notifPanel);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // ── En-tête ────────────────────────────────────────────────────────────
    QWidget *header = new QWidget;
    header->setObjectName("notifHeader");
    header->setFixedHeight(52);
    QHBoxLayout *hdrL = new QHBoxLayout(header);
    hdrL->setContentsMargins(16, 0, 10, 0);
    hdrL->setSpacing(6);

    QLabel *title = new QLabel(
        m_unreadCount > 0
            ? QString("Notifications <b>(%1)</b>").arg(m_unreadCount)
            : "Notifications");
    title->setObjectName("notifTitle");

    QPushButton *btnMarkAll = new QPushButton("✓ Tout lire");
    btnMarkAll->setObjectName("notifBtnAction");
    btnMarkAll->setFixedHeight(26);
    btnMarkAll->setCursor(Qt::PointingHandCursor);
    btnMarkAll->setFocusPolicy(Qt::NoFocus);
    connect(btnMarkAll, &QPushButton::clicked, this, &MainWindow::markAllNotifRead);

    QPushButton *btnClear = new QPushButton("🗑 Effacer");
    btnClear->setObjectName("notifBtnClear");
    btnClear->setFixedHeight(26);
    btnClear->setCursor(Qt::PointingHandCursor);
    btnClear->setFocusPolicy(Qt::NoFocus);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::clearAllNotif);

    hdrL->addWidget(title, 1);
    hdrL->addWidget(btnMarkAll);
    hdrL->addWidget(btnClear);

    // ── Séparateur ─────────────────────────────────────────────────────────
    QFrame *sep = new QFrame;
    sep->setObjectName("notifSep");
    sep->setFixedHeight(1);

    // ── Zone scrollable ────────────────────────────────────────────────────
    QScrollArea *scroll = new QScrollArea;
    scroll->setObjectName("notifScroll");
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget *content = new QWidget;
    content->setObjectName("notifContent");
    QVBoxLayout *contentL = new QVBoxLayout(content);
    contentL->setContentsMargins(0, 4, 0, 4);
    contentL->setSpacing(0);

    if (m_notifications.isEmpty()) {
        QLabel *empty = new QLabel("Aucune notification");
        empty->setObjectName("notifEmpty");
        empty->setAlignment(Qt::AlignCenter);
        empty->setFixedHeight(80);
        contentL->addWidget(empty);
    } else {
        // Afficher du plus récent au plus ancien
        for (int i = m_notifications.size() - 1; i >= 0; --i) {
            const NotifEntry &n = m_notifications[i];

            // Couleur et icône selon le type
            QString barColor, typeIcon;
            if      (n.actionType == "CONNEXION")   { barColor = "#0ea5e9"; typeIcon = "🔑"; }
            else if (n.actionType == "SUPPRESSION")  { barColor = "#ef4444"; typeIcon = "🗑"; }
            else if (n.actionType == "MODIFICATION") { barColor = "#f59e0b"; typeIcon = "✏"; }
            else if (n.actionType == "SYSTÈME")      { barColor = "#10b981"; typeIcon = "⚙"; }
            else                                     { barColor = "#8b5cf6"; typeIcon = "📌"; }

            // Conteneur de l'item
            QWidget *item = new QWidget;
            item->setObjectName(n.read ? "notifItem" : "notifItemUnread");
            item->setFixedHeight(62);

            QHBoxLayout *itemL = new QHBoxLayout(item);
            itemL->setContentsMargins(0, 0, 12, 0);
            itemL->setSpacing(0);

            // Barre colorée gauche
            QFrame *bar = new QFrame;
            bar->setFixedWidth(4);
            bar->setStyleSheet(
                QString("background: %1; border-radius: 2px;").arg(barColor));

            // Zone texte
            QWidget *textZone = new QWidget;
            QVBoxLayout *textL = new QVBoxLayout(textZone);
            textL->setContentsMargins(12, 6, 0, 6);
            textL->setSpacing(2);

            QLabel *msg = new QLabel(typeIcon + " " + n.cible);
            msg->setObjectName("notifMsg");

            QLabel *meta = new QLabel(
                QString("%1 — %2 (%3)").arg(n.time, n.user, n.role));
            meta->setObjectName("notifMeta");

            textL->addWidget(msg);
            textL->addWidget(meta);

            itemL->addWidget(bar);
            itemL->addWidget(textZone, 1);

            // Pastille non-lu
            if (!n.read) {
                QLabel *dot = new QLabel;
                dot->setFixedSize(8, 8);
                dot->setObjectName("notifDot");
                dot->setStyleSheet(
                    QString("background:%1; border-radius:4px;").arg(barColor));
                itemL->addWidget(dot);
                itemL->setAlignment(dot, Qt::AlignVCenter);
            }

            contentL->addWidget(item);

            // Séparateur fin entre items
            if (i > 0) {
                QFrame *isep = new QFrame;
                isep->setObjectName("notifItemSep");
                isep->setFixedHeight(1);
                contentL->addWidget(isep);
            }
        }
    }
    contentL->addStretch();
    scroll->setWidget(content);

    root->addWidget(header);
    root->addWidget(sep);
    root->addWidget(scroll, 1);

    // Ajuster la hauteur du panneau
    int visItems = qMin(m_notifications.size(), 5);
    int panelH = 52 + 1 + qMax(visItems * 63 + 8, 88);
    m_notifPanel->setFixedHeight(panelH);
}

// ─────────────────────────────────────────────────────────────────────────────
// updateNotifBadge : met à jour le badge rouge
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::updateNotifBadge()
{
    if (!m_notifBadge) return;

    if (m_unreadCount > 0) {
        m_notifBadge->setText(m_unreadCount > 9 ? "9+" : QString::number(m_unreadCount));
        m_notifBadge->show();
        m_notifBadge->raise();

        // Petite animation pulse à l'apparition
        auto *eff = qobject_cast<QGraphicsOpacityEffect*>(m_notifBadge->graphicsEffect());
        if (!eff) {
            eff = new QGraphicsOpacityEffect(m_notifBadge);
            m_notifBadge->setGraphicsEffect(eff);
        }
        auto *pulse = new QPropertyAnimation(eff, "opacity", m_notifBadge);
        pulse->setDuration(500);
        pulse->setStartValue(0.3);
        pulse->setEndValue(1.0);
        pulse->setEasingCurve(QEasingCurve::OutCubic);
        pulse->setLoopCount(2);
        pulse->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        m_notifBadge->hide();
    }

    // Repositionner le badge
    const int tw = ui->topBar->width();
    const int th = ui->topBar->height();
    const int bx = tw - ui->btnNotif->width() - 10;
    const int by = (th - ui->btnNotif->height()) / 2;
    m_notifBadge->move(bx + ui->btnNotif->width() - 10, by - 5);
}

// ─────────────────────────────────────────────────────────────────────────────
// markAllNotifRead / clearAllNotif
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::markAllNotifRead()
{
    for (auto &n : m_notifications) n.read = true;
    m_unreadCount = 0;
    updateNotifBadge();
    rebuildNotifPanel();
}

void MainWindow::clearAllNotif()
{
    m_notifications.clear();
    m_unreadCount = 0;
    updateNotifBadge();
    rebuildNotifPanel();
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::notifierConnexion()
{
    // On récupère le nom et le rôle depuis ta classe Session
    QString nom = Session::instance().getNom();
    QString role = Session::instance().getRole();

    // On envoie la notification à la cloche
    // Format : [HEURE] 👤 Nom (Role) a effectué : CONNEXION sur Session Active
    ajouterNotification("CONNEXION", "Session de travail ouverte");
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
    ui->aff_montant->setReadOnly(true);
    ui->aff_montant_paye->setReadOnly(true);
    ui->aff_reste->setReadOnly(true);
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

    ui->TableLabs_2->setColumnCount(12);
        ui->TableLabs_2->setHorizontalHeaderLabels({
            "IDLABO", "Nom Laboratoire", "Responsable", "Numéro",
            "Localisation", "Disponibilité", "Spécialité", "Résultat", "Paiement",
            "Montant (DT)", "Montant Payé (DT)", "Reste (DT)"
        });
    // Masquer IDLABO dans l'interface (l'ID reste exploitable en interne).
    ui->TableLabs_2->hideColumn(0);
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

        // Colonnes financières — tri numérique correct
        auto *itMontant = new QTableWidgetItem();
        itMontant->setData(Qt::DisplayRole, r.montant);
        ui->TableLabs_2->setItem(i, 9, itMontant);

        auto *itMontantPaye = new QTableWidgetItem();
        itMontantPaye->setData(Qt::DisplayRole, r.montantPaye);
        ui->TableLabs_2->setItem(i, 10, itMontantPaye);

        auto *itReste = new QTableWidgetItem();
        itReste->setData(Qt::DisplayRole, r.reste);
        // Colorier en rouge si reste > 0
        if (r.reste > 0.0)
            itReste->setForeground(QBrush(QColor(220, 50, 50)));
        else
            itReste->setForeground(QBrush(QColor(39, 174, 96)));
        ui->TableLabs_2->setItem(i, 11, itReste);
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

    // Responsables autorisés: Admin / Responsable_Labos.
    auto loadLabsResponsables = [this]() {
        ui->LabResponsible_3->clear();
        ui->LabResponsible_5->clear();
        ui->LabResponsible_3->addItem("Choisir un responsable");
        ui->LabResponsible_5->addItem("Choisir un responsable");

        QSqlQuery q;
        q.prepare("SELECT NOM, PRENOM "
                  "FROM EMPLOYES "
                  "WHERE ROLE IN ('Admin', 'Responsable_Labos') "
                  "ORDER BY NOM, PRENOM");

        if (!q.exec()) {
            qDebug() << "[LABS] Chargement responsables échoué:" << q.lastError().text();
            return;
        }

        while (q.next()) {
            const QString fullName = (q.value(0).toString().trimmed() + " " +
                                      q.value(1).toString().trimmed()).simplified();
            if (!fullName.isEmpty()) {
                ui->LabResponsible_3->addItem(fullName);
                ui->LabResponsible_5->addItem(fullName);
            }
        }
    };
    loadLabsResponsables();

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
    connect(ui->btnLabReserveProduct, &QPushButton::clicked, this, &MainWindow::on_btnLabReserveProduct_clicked);
    connect(ui->btnLabReserveValidate, &QPushButton::clicked, this, &MainWindow::on_btnLabReserveValidate_clicked);
    connect(ui->btnLabReserveBack, &QPushButton::clicked, this, &MainWindow::on_btnLabReserveBack_clicked);

    // Numéro labo: exactement 8 chiffres.
    auto *numValidator = new QRegularExpressionValidator(QRegularExpression("^\\d{0,8}$"), this);
    ui->LabNumber_3->setValidator(numValidator);
    ui->LabNumber_5->setValidator(numValidator);
    ui->LabNumber_3->setMaxLength(8);
    ui->LabNumber_5->setMaxLength(8);

    // Champs financiers (Ajouter/Modifier): QDoubleSpinBox.
    for (QDoubleSpinBox *sb : {ui->LabMontant_3, ui->LabMontantPaye_3, ui->LabMontant_5, ui->LabMontantPaye_5}) {
        sb->setDecimals(3);
        sb->setRange(0.0, 999999999.999);
        sb->setSingleStep(1.0);
    }

    ui->LabReste_3->setReadOnly(true);
    ui->LabReste_5->setReadOnly(true);

    auto recalcReste = [](QDoubleSpinBox *montantEdit, QDoubleSpinBox *payeEdit, QLineEdit *resteEdit) {
        const double m = montantEdit->value();
        const double p = payeEdit->value();
        resteEdit->setText(QString::number(m - p, 'f', 3));
    };

    connect(ui->LabMontant_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double) {
        recalcReste(ui->LabMontant_3, ui->LabMontantPaye_3, ui->LabReste_3);
    });
    connect(ui->LabMontantPaye_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double) {
        recalcReste(ui->LabMontant_3, ui->LabMontantPaye_3, ui->LabReste_3);
    });
    connect(ui->LabMontant_5, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double) {
        recalcReste(ui->LabMontant_5, ui->LabMontantPaye_5, ui->LabReste_5);
    });
    connect(ui->LabMontantPaye_5, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double) {
        recalcReste(ui->LabMontant_5, ui->LabMontantPaye_5, ui->LabReste_5);
    });

    // Réservation produits inventaire (stacked_L page index 6)
    ui->TableLabReserveProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableLabReserveProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableLabReserveProducts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableLabReserveProducts->verticalHeader()->setVisible(false);
    ui->TableLabReserveProducts->setColumnCount(5);
    ui->TableLabReserveProducts->setHorizontalHeaderLabels({
        QStringLiteral("ID"), QStringLiteral("SKU"), QStringLiteral("Nom"),
        QStringLiteral("Qt stock"), QStringLiteral("Qt réservée (inchangée)")});
    ui->TableLabReserveProducts->hideColumn(0);
    ui->TableLabReserveProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->spinLabReserveQty->setRange(1, 999999);
    connect(ui->TableLabReserveProducts, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::updateLabReserveSpinMax);

}

// ====================== Réservation produit (labs → inventaire) ======================
void MainWindow::on_btnLabReserveProduct_clicked()
{
    ui->stacked_L->setCurrentIndex(6);
    loadLabReserveProductTable();
}

void MainWindow::loadLabReserveProductTable()
{
    QVector<Inventory::Row> rows;
    QString err;
    if (!Inventory::chargerTout(rows, QStringLiteral("NAME"), &err)) {
        QMessageBox::critical(this, "Inventaire", err);
        return;
    }
    ui->TableLabReserveProducts->setSortingEnabled(false);
    ui->TableLabReserveProducts->setRowCount(0);
    for (int i = 0; i < rows.size(); ++i) {
        const auto &row = rows[i];
        ui->TableLabReserveProducts->insertRow(i);
        auto *idIt = new QTableWidgetItem(row.idProduct);
        idIt->setData(Qt::UserRole, row.idProduct);
        ui->TableLabReserveProducts->setItem(i, 0, idIt);
        ui->TableLabReserveProducts->setItem(i, 1, new QTableWidgetItem(row.sku));
        ui->TableLabReserveProducts->setItem(i, 2, new QTableWidgetItem(row.name));
        ui->TableLabReserveProducts->setItem(i, 3, new QTableWidgetItem(QString::number(row.qtAv)));
        ui->TableLabReserveProducts->setItem(i, 4, new QTableWidgetItem(QString::number(row.qtRs)));
    }
    ui->TableLabReserveProducts->setSortingEnabled(false);
    if (ui->TableLabReserveProducts->rowCount() > 0)
        ui->TableLabReserveProducts->selectRow(0);
    updateLabReserveSpinMax();
}

void MainWindow::updateLabReserveSpinMax()
{
    const int r = ui->TableLabReserveProducts->currentRow();
    if (r < 0) {
        ui->spinLabReserveQty->setMaximum(999999);
        return;
    }
    QTableWidgetItem *it = ui->TableLabReserveProducts->item(r, 0);
    if (!it) return;
    const QString id = it->data(Qt::UserRole).toString();
    if (id.isEmpty()) return;

    QSqlQuery q;
    q.prepare(QStringLiteral("SELECT NVL(QT_AV,0) FROM PRODUCT WHERE ID_PRODUCT = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    if (!q.exec() || !q.next())
        return;
    const int qtAv = q.value(0).toInt();
    if (qtAv <= 0) {
        ui->spinLabReserveQty->setMaximum(1);
        ui->spinLabReserveQty->setValue(1);
    } else {
        ui->spinLabReserveQty->setMaximum(qtAv);
        if (ui->spinLabReserveQty->value() > qtAv)
            ui->spinLabReserveQty->setValue(qtAv);
    }
}

void MainWindow::on_btnLabReserveValidate_clicked()
{
    const int r = ui->TableLabReserveProducts->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Réservation", "Sélectionnez un produit dans la liste.");
        return;
    }
    QTableWidgetItem *idItem = ui->TableLabReserveProducts->item(r, 0);
    if (!idItem) return;
    const QString id = idItem->data(Qt::UserRole).toString();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Réservation", "ID produit introuvable.");
        return;
    }
    const int qty = ui->spinLabReserveQty->value();
    if (qty < 1) {
        QMessageBox::warning(this, "Réservation", "Indiquez une quantité d’au moins 1.");
        return;
    }

    QSqlQuery q0;
    q0.prepare(QStringLiteral("SELECT NVL(QT_AV,0) FROM PRODUCT WHERE ID_PRODUCT = :id"));
    q0.bindValue(QStringLiteral(":id"), id);
    if (!q0.exec() || !q0.next()) {
        QMessageBox::critical(this, "Réservation", "Produit introuvable en base.");
        return;
    }
    const int qtAv = q0.value(0).toInt();
    if (qty > qtAv) {
        QMessageBox::warning(this, "Stock insuffisant",
                             QStringLiteral("Stock disponible : %1 (la quantité allouée aux labs diminue le stock, QT_RS n’est pas modifié).")
                                 .arg(qtAv));
        return;
    }

    QSqlQuery ensureUse;
    ensureUse.exec(QStringLiteral("ALTER TABLE PRODUCT ADD USE_COUNT NUMBER DEFAULT 0"));

    QSqlQuery q1;
    q1.prepare(
        QStringLiteral(
            "UPDATE PRODUCT SET "
            "QT_AV = NVL(QT_AV,0) - :qty, "
            "USE_COUNT = NVL(USE_COUNT,0) + :qty2 "
            "WHERE ID_PRODUCT = :id AND NVL(QT_AV,0) >= :need"));
    q1.bindValue(QStringLiteral(":qty"), qty);
    q1.bindValue(QStringLiteral(":qty2"), qty);
    q1.bindValue(QStringLiteral(":id"), id);
    q1.bindValue(QStringLiteral(":need"), qty);
    if (!q1.exec()) {
        QMessageBox::critical(this, "Réservation", q1.lastError().text());
        return;
    }
    const int nAff = q1.numRowsAffected();
    if (nAff == 0) {
        QMessageBox::warning(this, "Réservation",
                             QStringLiteral("Aucune ligne mise à jour (stock insuffisant ou conflit). Réessayez après actualisation."));
        loadLabReserveProductTable();
        return;
    }

    QString syncErr;
    if (!syncInventoryStatsFromProduct(&syncErr)) {
        QMessageBox::critical(this, "Réservation",
                              QStringLiteral("Mise à jour partielle. Statistiques : %1").arg(syncErr));
        return;
    }

    QMessageBox::information(this, "Réservation",
                             QStringLiteral("Allocation enregistrée : %1 unité(s). Stock (QT_AV) diminué, USE_COUNT mis à jour pour les statistiques (QT_RS inchangé).")
                                 .arg(qty));
    loadLabReserveProductTable();
    loadInventory();
}

void MainWindow::on_btnLabReserveBack_clicked()
{
    ui->stacked_L->setCurrentIndex(0);
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
    ui->LabResponsible_3->setCurrentIndex(0);
    ui->LabNumber_3->clear();
    ui->LabLocation_3->clear();
    ui->LabSpec_3->setCurrentIndex(0);
    ui->LabCap_3->setCurrentIndex(0);
    ui->LabSpec_4->setCurrentIndex(0);
    ui->LabCap_4->setCurrentIndex(0);
    ui->LabMontant_3->setValue(0.0);
    ui->LabMontantPaye_3->setValue(0.0);
    ui->LabReste_3->setText("0.000");
}
void MainWindow::on_BtnPopupSaveLabs_3_clicked()
{
    const QString nomLabo       = ui->LabName_3->text().trimmed();
    const QString responsable   = ui->LabResponsible_3->currentText().trimmed();
    const QString numero        = ui->LabNumber_3->text().trimmed();
    const QString localisation  = ui->LabLocation_3->text().trimmed();
    const QString specialite    = ui->LabSpec_3->currentText();
    const QString disponibilite = ui->LabCap_3->currentText();
    const QString resultat      = ui->LabSpec_4->currentText();
    const QString paiement      = ui->LabCap_4->currentText();
    const double montant     = ui->LabMontant_3->value();
    const double montantPaye = ui->LabMontantPaye_3->value();

    if (nomLabo.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom du laboratoire est obligatoire.");
        return;
    }
    if (responsable.isEmpty() || responsable.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir un responsable valide.");
        return;
    }
    if (numero.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le numéro du laboratoire est obligatoire.");
        return;
    }
    if (localisation.isEmpty()) {
        QMessageBox::warning(this, "Validation", "La localisation du laboratoire est obligatoire.");
        return;
    }
    if (numero.size() != 8) {
        QMessageBox::warning(this, "Validation", "Le numéro doit contenir exactement 8 chiffres.");
        return;
    }
    if (specialite.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir une spécialité valide.");
        return;
    }
    if (disponibilite.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir une disponibilité valide.");
        return;
    }
    if (resultat.toLower().contains("choisir") || resultat.toLower().contains("modifier")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir un résultat valide.");
        return;
    }
    if (paiement.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir un état de paiement valide.");
        return;
    }
    if (montant < 0.0) {
        QMessageBox::warning(this, "Validation", "Le montant total ne peut pas être négatif.");
        return;
    }
    if (montantPaye < 0.0) {
        QMessageBox::warning(this, "Validation", "Le montant payé ne peut pas être négatif.");
        return;
    }
    if (montantPaye > montant) {
        QMessageBox::warning(this, "Validation",
                             QString("Le montant payé (%1 DT) ne peut pas dépasser le montant total (%2 DT).")
                                 .arg(montantPaye, 0, 'f', 3).arg(montant, 0, 'f', 3));
        return;
    }

    Labs lab(nomLabo, responsable, numero, localisation, specialite, disponibilite,
             resultat, paiement, montant, montantPaye, "1");
    QString err;
    if (!lab.ajouter(&err)) {
        QMessageBox::critical(this, "Échec de l'ajout", "Impossible d'ajouter le laboratoire :\n" + err);
        return;
    }

    QMessageBox::information(this, "Succès",
                             QString("Laboratoire ajouté avec succès !\n"
                                     "Montant : %1 DT | Payé : %2 DT | Reste : %3 DT")
                                 .arg(montant, 0, 'f', 3)
                                 .arg(montantPaye, 0, 'f', 3)
                                 .arg(montant - montantPaye, 0, 'f', 3));
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
    setComboValue(ui->LabResponsible_5, r.responsable);
    ui->LabNumber_5->setText(r.numero);
    ui->LabLocation_5->setText(r.localisation);
    setComboValue(ui->LabCap_5,  r.disponibilite);
    setComboValue(ui->LabSpec_5, r.specialite);
    setComboValue(ui->LabSpec_6, r.resultat);
    setComboValue(ui->LabCap_6,  r.paiement);
    ui->LabMontant_5->setValue(r.montant);
    ui->LabMontantPaye_5->setValue(r.montantPaye);
    ui->LabReste_5->setText(QString::number(r.reste, 'f', 3));
}
void MainWindow::on_BtnPopupSaveLabs_5_clicked()
{
    if (idLabsToEdit.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun laboratoire sélectionné pour modification.");
        return;
    }

    const QString nomLabo       = ui->LabName_5->text().trimmed();
    const QString responsable   = ui->LabResponsible_5->currentText().trimmed();
    const QString numero        = ui->LabNumber_5->text().trimmed();
    const QString localisation  = ui->LabLocation_5->text().trimmed();
    const QString specialite    = ui->LabSpec_5->currentText();
    const QString disponibilite = ui->LabCap_5->currentText();
    const QString resultat      = ui->LabSpec_6->currentText();
    const QString paiement      = ui->LabCap_6->currentText();
    const double montant     = ui->LabMontant_5->value();
    const double montantPaye = ui->LabMontantPaye_5->value();

    if (nomLabo.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom du laboratoire est obligatoire.");
        return;
    }
    if (responsable.isEmpty() || responsable.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir un responsable valide.");
        return;
    }
    if (numero.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le numéro du laboratoire est obligatoire.");
        return;
    }
    if (localisation.isEmpty()) {
        QMessageBox::warning(this, "Validation", "La localisation du laboratoire est obligatoire.");
        return;
    }
    if (numero.size() != 8) {
        QMessageBox::warning(this, "Validation", "Le numéro doit contenir exactement 8 chiffres.");
        return;
    }
    if (specialite.toLower().contains("choisir") || specialite.toLower().contains("modifier")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir une spécialité valide.");
        return;
    }
    if (disponibilite.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir une disponibilité valide.");
        return;
    }
    if (resultat.toLower().contains("choisir") || resultat.toLower().contains("modifier")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir un résultat valide.");
        return;
    }
    if (paiement.toLower().contains("choisir")) {
        QMessageBox::warning(this, "Validation", "Veuillez choisir un état de paiement valide.");
        return;
    }
    if (montant < 0.0) {
        QMessageBox::warning(this, "Validation", "Le montant total ne peut pas être négatif.");
        return;
    }
    if (montantPaye < 0.0) {
        QMessageBox::warning(this, "Validation", "Le montant payé ne peut pas être négatif.");
        return;
    }
    if (montantPaye > montant) {
        QMessageBox::warning(this, "Validation",
                             QString("Le montant payé (%1 DT) ne peut pas dépasser le montant total (%2 DT).")
                                 .arg(montantPaye, 0, 'f', 3).arg(montant, 0, 'f', 3));
        return;
    }

    QString err;
    if (!Labs::modifier(idLabsToEdit, nomLabo, responsable, numero, localisation,
                        specialite, disponibilite, resultat, paiement,
                        montant, montantPaye, &err)) {
        QMessageBox::critical(this, "Erreur de modification", err);
        return;
    }

    QMessageBox::information(this, "Succès",
                             QString("Laboratoire modifié avec succès !\n"
                                     "Montant : %1 DT | Payé : %2 DT | Reste : %3 DT")
                                 .arg(montant, 0, 'f', 3)
                                 .arg(montantPaye, 0, 'f', 3)
                                 .arg(montant - montantPaye, 0, 'f', 3));
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
    if (!ui->TableLabs_2->item(row, 0)) return;

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
    if (!ui->TableLabs_2->item(r, 0)) return;

    ui->LabName_5->setText(ui->TableLabs_2->item(r, 1)->text());
    setComboValue(ui->LabResponsible_5, ui->TableLabs_2->item(r, 2)->text());
    ui->LabNumber_5->setText(ui->TableLabs_2->item(r, 3)->text());
    ui->LabLocation_5->setText(ui->TableLabs_2->item(r, 4)->text());

    setComboValue(ui->LabCap_5,  ui->TableLabs_2->item(r, 5)->text()); // Disponibilité
        setComboValue(ui->LabSpec_5, ui->TableLabs_2->item(r, 6)->text()); // Spécialité
        setComboValue(ui->LabSpec_6, ui->TableLabs_2->item(r, 7)->text()); // Résultat
        setComboValue(ui->LabCap_6,  ui->TableLabs_2->item(r, 8)->text()); // Paiement

        // Montants financiers depuis le tableau (colonnes 9, 10, 11)
        if (ui->TableLabs_2->item(r, 9))
            ui->LabMontant_5->setValue(
                ui->TableLabs_2->item(r, 9)->data(Qt::DisplayRole).toDouble());
        if (ui->TableLabs_2->item(r, 10))
            ui->LabMontantPaye_5->setValue(
                ui->TableLabs_2->item(r, 10)->data(Qt::DisplayRole).toDouble());
        if (ui->TableLabs_2->item(r, 11))
            ui->LabReste_5->setText(QString::number(
                ui->TableLabs_2->item(r, 11)->data(Qt::DisplayRole).toDouble(), 'f', 3));

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
    if (!ui->TableLabs_2->item(r, 0)) return;

    ui->aff1->setText(ui->TableLabs_2->item(r, 1)->text()); // Nom
        ui->aff5->setText(ui->TableLabs_2->item(r, 2)->text()); // Responsable
        ui->aff6->setText(ui->TableLabs_2->item(r, 3)->text()); // Numéro
        ui->aff2->setText(ui->TableLabs_2->item(r, 4)->text()); // Localisation

        setComboValue(ui->aff7,   ui->TableLabs_2->item(r, 5)->text()); // Disponibilité
        setComboValue(ui->aff3,   ui->TableLabs_2->item(r, 6)->text()); // Spécialité
        setComboValue(ui->aff3_2, ui->TableLabs_2->item(r, 7)->text()); // Résultat
        setComboValue(ui->aff7_2, ui->TableLabs_2->item(r, 8)->text()); // Paiement

        // Montants financiers en lecture seule sur la page d'affichage
        if (ui->TableLabs_2->item(r, 9))
            ui->aff_montant->setText(QString::number(
                ui->TableLabs_2->item(r, 9)->data(Qt::DisplayRole).toDouble(), 'f', 3) + " DT");
        if (ui->TableLabs_2->item(r, 10))
            ui->aff_montant_paye->setText(QString::number(
                ui->TableLabs_2->item(r, 10)->data(Qt::DisplayRole).toDouble(), 'f', 3) + " DT");
        if (ui->TableLabs_2->item(r, 11)) {
            double reste = ui->TableLabs_2->item(r, 11)->data(Qt::DisplayRole).toDouble();
            ui->aff_reste->setText(QString::number(reste, 'f', 3) + " DT");
            // Couleur indicative
            ui->aff_reste->setStyleSheet(
                reste > 0.0 ? "color: #DC3232; font-weight: bold;"
                            : "color: #27AE60; font-weight: bold;");
        }

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
    setupInventoryChoicePage();
    
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
    ui->InventoryStatus->addItem(QStringLiteral("-- Tous les statuts --"), QString());
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
    ui->InventoryZone->addItem(QStringLiteral("-- Toutes les zones --"), QString());
    ui->InventoryZone->addItem("Zone A", "A");
    ui->InventoryZone->addItem("Zone B", "B");
    ui->InventoryZone->addItem("Zone C", "C");
    ui->InventoryZone->addItem("Zone D", "D");

    // Type filter : types distincts en base (liste prédéfinie en secours)
    refreshInventoryTypeFilter();

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

    // SKU hint visible for users when opening add/edit forms
    ui->Sku->setInputMask(QString());
    ui->Sku_2->setInputMask(QString());
    ui->Sku->setPlaceholderText("ABC-123");
    ui->Sku_2->setPlaceholderText("ABC-123");
    ui->Sku->setMaxLength(7);
    ui->Sku_2->setMaxLength(7);

    connect(ui->Sku, &QLineEdit::textChanged, this, [this](const QString &text) {
        const QString normalized = normalizeSkuInput(text);
        if (normalized != text) {
            ui->Sku->setText(normalized);
        }
    });
    connect(ui->Sku_2, &QLineEdit::textChanged, this, [this](const QString &text) {
        const QString normalized = normalizeSkuInput(text);
        if (normalized != text) {
            ui->Sku_2->setText(normalized);
        }
    });

    // Name Validation: Uppercase Letters, Numbers and Spaces only
    QRegularExpression nameRegex("^[A-Z0-9 ]*$");
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->Name->setValidator(nameValidator);
    ui->Name_2->setValidator(nameValidator);

    setupTableInventory();

    // --- MANUAL CONNECTIONS (Fixing Navigation Issues) ---
    connect(ui->BtnInventoryAdd,    &QPushButton::clicked, this, &MainWindow::handleInventoryAdd);
    connect(ui->BtnInventoryAdd_2,  &QPushButton::clicked, this, &MainWindow::handleInventoryView);
    connect(ui->BtnInventoryEdit,   &QPushButton::clicked, this, &MainWindow::handleInventoryEdit);
    connect(ui->BtnInventoryAdd_5,  &QPushButton::clicked, this, &MainWindow::handleInventoryStats);
    connect(ui->BtnInventoryDelete, &QPushButton::clicked, this, &MainWindow::handleInventoryDelete);
    connect(ui->BtnInventoryExport, &QPushButton::clicked, this, &MainWindow::handleInventoryExportPdf);
    connect(ui->BtnInventoryDetailExportPdf, &QPushButton::clicked, this, &MainWindow::handleInventoryDetailExportPdf);

    // Form buttons (manual connections for reliability)
    connect(ui->BtnPopupAutoSaveInventory, &QPushButton::clicked, this, &MainWindow::on_BtnPopupAutoSaveInventory_clicked);
    connect(ui->BtnPopupSaveInventory,   &QPushButton::clicked, this, &MainWindow::on_BtnPopupSaveInventory_clicked);
    connect(ui->BtnPopupResetInventory,  &QPushButton::clicked, this, &MainWindow::on_BtnPopupResetInventory_clicked);
    connect(ui->BtnPopupCancelInventory, &QToolButton::clicked,   this, &MainWindow::on_BtnPopupCancelInventory_clicked);

    connect(ui->BtnPopupSaveInventory_2,  &QPushButton::clicked, this, &MainWindow::on_BtnPopupSaveInventory_2_clicked);
    connect(ui->BtnPopupResetInventory_2, &QPushButton::clicked, this, &MainWindow::on_BtnPopupResetInventory_2_clicked);
    connect(ui->BtnPopupCancelInventory_2,&QToolButton::clicked,   this, &MainWindow::on_BtnPopupCancelInventory_2_clicked);

    // Apply/filter button — explicit connect (auto-connect fails for nested widgets)
    connect(ui->BtnInventoryApply, &QPushButton::clicked, this, &MainWindow::applyInventoryFilter);
    connect(ui->BtnInventoryReset, &QPushButton::clicked, this, &MainWindow::resetInventoryFilters);

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
    ui->TableInventory->setSortingEnabled(false); // Rely on SQL order

    // Keep placeholder visible instead of masking input
    ui->Sku->setInputMask(QString());
    ui->Sku_2->setInputMask(QString());
    ui->Sku->setPlaceholderText("ABC-123");
    ui->Sku_2->setPlaceholderText("ABC-123");


    // Hide ID input fields from Admin (automated)
    ui->IdProduct->setVisible(false);
    ui->IdProduct_2->setVisible(false);
    ui->LblIdProduct->setVisible(false);
    ui->LblIdProduct_2->setVisible(false);
}

void MainWindow::fillTableInventoryRow(int r, const Inventory::Row &row)
{
    // col 0 - ID_PRODUCT (hidden PK stored in UserRole)
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
    auto *priceItem = new QTableWidgetItem(QString::number(row.price, 'f', 2));
    priceItem->setData(Qt::EditRole, row.price); // numeric so sortItems works correctly
    ui->TableInventory->setItem(r, 3, priceItem);
    ui->TableInventory->setItem(r, 4, new QTableWidgetItem(QString::number(row.qtAv)));
    ui->TableInventory->setItem(r, 5, new QTableWidgetItem(row.status));
}

void MainWindow::loadInventory()
{
    // Recalcul automatique des statuts
    QString syncErr;
    syncInventoryStatsFromProduct(&syncErr);
    ui->TableInventory->setSortingEnabled(false);
    ui->TableInventory->setRowCount(0);

    QVector<Inventory::Row> rows;
    QString err;
    const int sortIdx = ui->InventorySort->currentIndex();
    QString orderBy = "SKU";
    if (sortIdx == 1)      orderBy = "NAME ASC";
    else if (sortIdx == 2) orderBy = "PRICE ASC";
    else if (sortIdx == 3) orderBy = "PRICE DESC";

    if (!Inventory::chargerTout(rows, orderBy, &err)) {
        QMessageBox::critical(this, "Erreur SQL - Inventaire", err);
        return;
    }

    int r = 0;
    for (const auto &row : std::as_const(rows)) {
        ui->TableInventory->insertRow(r);
        fillTableInventoryRow(r, row);
        ++r;
    }
    // Keep sorting disabled so SQL ORDER BY is preserved

}


// ── UI CHOICE PAGE ────────────────────────────────────────────────────────────
void MainWindow::setupInventoryChoicePage() {
    m_pageChoixAjoutInv = new QWidget();
    m_pageChoixAjoutInv->setObjectName("pageChoixAjoutInv");
    QVBoxLayout *layout = new QVBoxLayout(m_pageChoixAjoutInv);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *lblTitle = new QLabel("Choix de la méthode d'ajout", m_pageChoixAjoutInv);
    QFont fTitle = lblTitle->font();
    fTitle.setPointSize(24);
    fTitle.setBold(true);
    lblTitle->setFont(fTitle);
    lblTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblTitle);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(40);

    QPushButton *btnManual = new QPushButton("Ajout\nManuel", m_pageChoixAjoutInv);
    btnManual->setFixedSize(280, 180);
    btnManual->setCursor(Qt::PointingHandCursor);
    QFont fBtn = btnManual->font();
    fBtn.setPointSize(18);
    fBtn.setBold(true);
    btnManual->setFont(fBtn);
    connect(btnManual, &QPushButton::clicked, this, &MainWindow::goInventoryAddManual);

    QPushButton *btnAuto = new QPushButton("Ajout\nAutomatique", m_pageChoixAjoutInv);
    btnAuto->setFixedSize(280, 180);
    btnAuto->setCursor(Qt::PointingHandCursor);
    btnAuto->setFont(fBtn);
    connect(btnAuto, &QPushButton::clicked, this, &MainWindow::goInventoryAddAuto);

    btnLayout->addStretch();
    btnLayout->addWidget(btnManual);
    btnLayout->addWidget(btnAuto);
    btnLayout->addStretch();
    
    layout->addLayout(btnLayout);
    layout->addSpacing(40);

    QPushButton *btnCancel = new QPushButton("Retour", m_pageChoixAjoutInv);
    btnCancel->setFixedSize(150, 45);
    btnCancel->setCursor(Qt::PointingHandCursor);
    QFont fCancel = btnCancel->font();
    fCancel.setPointSize(14);
    fCancel.setBold(true);
    btnCancel->setFont(fCancel);
    connect(btnCancel, &QPushButton::clicked, this, [this](){ ui->stacked_I->setCurrentIndex(0); });
    
    QHBoxLayout *cancelLayout = new QHBoxLayout();
    cancelLayout->addStretch();
    cancelLayout->addWidget(btnCancel);
    cancelLayout->addStretch();
    
    layout->addLayout(cancelLayout);
    
    ui->stacked_I->addWidget(m_pageChoixAjoutInv);
}

void MainWindow::goInventoryAddManual() {
    ui->LblZone->setVisible(true);
    ui->Zone->setVisible(true);
    ui->LblShelf->setVisible(true);
    ui->Shelf->setVisible(true);
    ui->LblStatus->setVisible(true);
    ui->Status->setVisible(true);
    
    ui->BtnPopupSaveInventory->setVisible(true);
    ui->BtnPopupAutoSaveInventory->setVisible(false);
    
    ui->stacked_I->setCurrentIndex(1); // Page d'ajout
}

void MainWindow::goInventoryAddAuto() {
    ui->LblZone->setVisible(false);
    ui->Zone->setVisible(false);
    ui->LblShelf->setVisible(false);
    ui->Shelf->setVisible(false);
    ui->LblStatus->setVisible(false);
    ui->Status->setVisible(false);
    
    ui->BtnPopupSaveInventory->setVisible(false);
    ui->BtnPopupAutoSaveInventory->setVisible(true);
    
    ui->stacked_I->setCurrentIndex(1); // Page d'ajout
}

// ── CREATE ────────────────────────────────────────────────────────────────────

void MainWindow::on_BtnPopupAutoSaveInventory_clicked()
{
    // Auto-calculate missing fields
    const int qtAv = ui->QtAv->value();
    const int threshold = ui->Threshold->value();
    const QString unit = ui->Unit->currentData().toString();
    const QString type = ui->Type->currentData().toString();
    
    // Calculate Status
    QString calcStatus;
    if (qtAv == 0) {
        calcStatus = "stock out";
    } else if (qtAv <= threshold * 3) {
        calcStatus = "limited";
    } else {
        calcStatus = "on hand";
    }
    
    // Calculate Shelf
    QString calcShelf;
    if (unit == "kg") calcShelf = "1st floor";
    else if (unit == "m") calcShelf = "2nd floor";
    else if (unit == "L") calcShelf = "3rd floor";
    else calcShelf = "RDC";
    
    // Calculate Zone
    QString calcZone;
    if (type == "Matière première" || type == "Composant") calcZone = "A";
    else if (type == "Produit fini" || type == "Produit semi-fini") calcZone = "B";
    else if (type == "Outil" || type == "Équipement") calcZone = "C";
    else if (type == "Consommable" || type == "Pièce de rechange") calcZone = "D";
    else calcZone = "A";
    
    // Update the UI combos
    int statusIdx = ui->Status->findData(calcStatus);
    if(statusIdx >= 0) ui->Status->setCurrentIndex(statusIdx);
    
    int shelfIdx = ui->Shelf->findData(calcShelf);
    if(shelfIdx >= 0) ui->Shelf->setCurrentIndex(shelfIdx);
    
    int zoneIdx = ui->Zone->findData(calcZone);
    if(zoneIdx >= 0) ui->Zone->setCurrentIndex(zoneIdx);

    // Proceed to standard save logic
    on_BtnPopupSaveInventory_clicked();
}

void MainWindow::on_BtnPopupSaveInventory_clicked()
{
    // Auto-uppercase for consistency
    const QString name      = ui->Name->text().trimmed().toUpper();
    const QString sku       = normalizeSkuInput(ui->Sku->text().trimmed());

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

    // Validation: Name
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom du produit ne peut pas être vide.");
        return;
    }

    // Validation stricte SKU: ABC-123
    static const QRegularExpression skuRegex(QStringLiteral("^[A-Z]{3}-[0-9]{3}$"));
    if (!skuRegex.match(sku).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le SKU doit respecter le format ABC-123.");
        ui->Sku->setFocus();
        ui->Sku->selectAll();
        return;
    }
    if (inventorySkuExists(sku)) {
        QMessageBox::warning(this, "Validation", "Ce SKU existe deja. Veuillez saisir un SKU unique.");
        ui->Sku->setFocus();
        ui->Sku->selectAll();
        return;
    }

    if (status.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Veuillez sélectionner un statut.");
        return;
    }

    Inventory inv(name, sku, type, qtAv, qtRs, threshold, unit, price, status, zone, shelf, desc);
    QString err;
    if (!inv.ajouter(&err)) {
        QMessageBox::critical(this, "Erreur de Sauvegarde",
                              "Impossible d'ajouter le produit.\n\n"
                              "Détail technique : " + err + "\n\n"
                              "Vérifiez que vous avez au moins un employé enregistré.");
        return;
    }


    QMessageBox::information(this, "Inventaire", "Produit ajouté avec succès.");
    ui->stacked_I->setCurrentIndex(0);
    refreshInventoryTypeFilter();
    loadInventory();
}

void MainWindow::on_BtnPopupResetInventory_clicked()
{
    ui->IdProduct->clear();
    ui->Name->clear();
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
// ── UPDATE ────────────────────────────────────────────────────────────────────

// ====================== MODIFICATION ======================

void MainWindow::handleInventoryEdit()
{
    qDebug() << "[INVENTORY] handleInventoryEdit: Navigating to Index 2 (modifieri)";
    const int r = ui->TableInventory->currentRow();
    if (r < 0) {
        QMessageBox::warning(this, "Modifier", "Veuillez sélectionner un produit dans le tableau.");
        return;
    }
    QTableWidgetItem *itId = ui->TableInventory->item(r, 0);
    if (!itId) return;

    idProductToEdit = itId->data(Qt::UserRole).toString();

    // Fill the Edit form (index 2)
    ui->IdProduct_2->setText(itId->text());
    ui->Sku_2->setText(ui->TableInventory->item(r, 1)->text());
    ui->Name_2->setText(ui->TableInventory->item(r, 2)->text());
    ui->Price_2->setValue(ui->TableInventory->item(r, 3)->text().toDouble());
    ui->QtAv_2->setValue(ui->TableInventory->item(r, 4)->text().toInt());
    
    // Values from UserRole
    ui->QtRs_2->setValue(itId->data(Qt::UserRole + 6).toInt());
    ui->Threshold_2->setValue(itId->data(Qt::UserRole + 7).toInt());
    ui->Description_2->setPlainText(itId->data(Qt::UserRole + 5).toString());

    // Combos: use findData or findText
    auto setC = [](QComboBox *cb, const QString &val) {
        int idx = cb->findData(val);
        if (idx < 0) idx = cb->findText(val);
        cb->setCurrentIndex(idx >= 0 ? idx : 0);
    };

    setC(ui->Status_2, ui->TableInventory->item(r, 5)->text());
    setC(ui->Type_2,   itId->data(Qt::UserRole + 4).toString());
    setC(ui->Unit_2,   itId->data(Qt::UserRole + 3).toString());
    setC(ui->Zone_2,   itId->data(Qt::UserRole + 1).toString());
    setC(ui->Shelf_2,  itId->data(Qt::UserRole + 2).toString());

    ui->stacked_I->setCurrentIndex(2); // "modifieri" page (Index 2)
}

void MainWindow::applyInventoryFilter()
{
    // Filtre + tri en SQL : évite sortItems + setRowHidden (indices de lignes
    // et la visibilité se désynchronisent après un tri → lignes “perdues”).
    const QString kwRaw = ui->InventorySearch->text().trimmed();
    const int sortIdx   = ui->InventorySort->currentIndex();

    // Valeurs filtre = userData des combos (remplies dans setupInventoryCombos).
    // Ne pas utiliser currentText() : « -- Toutes zones -- » ne contient pas « Tous »
    // (T-o-u-t-e-s ≠ sous-chaîne T-o-u-s), ce qui envoyait ZONE = '-- TOUTES ZONES --' en SQL → 0 ligne.
    const QString zoneSql   = ui->InventoryZone->currentData().toString().trimmed();
    const QString statusSql = ui->InventoryStatus->currentData().toString().trimmed();
    const QString typeSql   = ui->InventoryType->currentData().toString().trimmed();

    QString orderBy = QStringLiteral("SKU");
    if (sortIdx == 1)      orderBy = QStringLiteral("NAME ASC");
    else if (sortIdx == 2) orderBy = QStringLiteral("PRICE ASC");
    else if (sortIdx == 3) orderBy = QStringLiteral("PRICE DESC");

    QVector<Inventory::Row> rows;
    QString err;
    if (!Inventory::chercher(rows, kwRaw, zoneSql, statusSql, typeSql, orderBy, &err)) {
        QMessageBox::critical(this, QStringLiteral("Erreur SQL - Inventaire"), err);
        return;
    }

    QTableWidget *t = ui->TableInventory;
    t->setSortingEnabled(false);
    t->setRowCount(0);

    int r = 0;
    for (const auto &row : std::as_const(rows)) {
        t->insertRow(r);
        fillTableInventoryRow(r, row);
        ++r;
    }

    qDebug() << "[INVENTORY] Apply filter done. sortIdx=" << sortIdx
             << "kw=" << kwRaw << "zoneSql=" << zoneSql << "statusSql=" << statusSql
             << "typeSql=" << typeSql << "rows=" << rows.size();
}

void MainWindow::refreshInventoryTypeFilter()
{
    const QString prev = ui->InventoryType->currentData().toString();
    ui->InventoryType->clear();
    ui->InventoryType->addItem(QStringLiteral("-- Tous les types --"), QString());

    QVector<QString> types;
    if (Inventory::typesDistincts(types, nullptr)) {
        for (const QString &t : types) {
            if (t.trimmed().isEmpty()) continue;
            ui->InventoryType->addItem(t, t);
        }
    } else {
        const QStringList presetTypes = {
            QStringLiteral("Matière première"),
            QStringLiteral("Composant"),
            QStringLiteral("Produit fini"),
            QStringLiteral("Produit semi-fini"),
            QStringLiteral("Outil"),
            QStringLiteral("Équipement"),
            QStringLiteral("Consommable"),
            QStringLiteral("Pièce de rechange"),
        };
        for (const QString &t : presetTypes)
            ui->InventoryType->addItem(t, t);
    }

    const int idx = ui->InventoryType->findData(prev);
    ui->InventoryType->setCurrentIndex(idx >= 0 ? idx : 0);
}

void MainWindow::resetInventoryFilters()
{
    ui->InventorySearch->clear();
    ui->InventoryType->setCurrentIndex(0);
    ui->InventoryZone->setCurrentIndex(0);
    ui->InventoryStatus->setCurrentIndex(0);
    ui->InventorySort->setCurrentIndex(0);
    loadInventory();
}

void MainWindow::handleInventoryExportPdf()
{
    QTableWidget *t = ui->TableInventory;
    QVector<int> visibleRows;
    visibleRows.reserve(t->rowCount());
    for (int r = 0; r < t->rowCount(); ++r) {
        if (!t->isRowHidden(r))
            visibleRows.append(r);
    }
    if (visibleRows.isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("Export PDF"),
                             QStringLiteral("Aucune ligne à exporter. Vérifiez le tableau ou les filtres."));
        return;
    }

    // Export "Top 10" selon l'ordre actuel du tableau (après tri / filtre).
    const int topN = 10;
    if (visibleRows.size() > topN)
        visibleRows.resize(topN);

    QString fileName = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("Exporter l'inventaire en PDF"),
        QStringLiteral("Inventaire.pdf"),
        QStringLiteral("PDF Files (*.pdf)"));
    if (fileName.isEmpty())
        return;
    if (!fileName.endsWith(QStringLiteral(".pdf"), Qt::CaseInsensitive))
        fileName += QStringLiteral(".pdf");

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Portrait);
    pdf.setResolution(300);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, QStringLiteral("Erreur"),
                              QStringLiteral("Impossible de créer le fichier PDF."));
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    const int margin = 35;
    const int pageWidth = pdf.width();
    const int pageHeight = pdf.height();
    const int tableWidth = qMax(0, pageWidth - 2 * margin);

    static const int exportCols[] = {1, 2, 3, 4, 5};
    constexpr int nExportCols = 5;

    QStringList headerLabels;
    for (int c : exportCols) {
        QTableWidgetItem *hi = t->horizontalHeaderItem(c);
        headerLabels << (hi ? hi->text() : QString());
    }

    QVector<int> colWidths(nExportCols);
    {
        const int parts[] = {20, 38, 14, 12, 16};
        int sum = 0;
        for (int i = 0; i < nExportCols; ++i) {
            colWidths[i] = tableWidth * parts[i] / 100;
            sum += colWidths[i];
        }
        colWidths[nExportCols - 1] += (tableWidth - sum);
    }

    QFont titleFont(QStringLiteral("Arial"), 16, QFont::Bold);
    QFont headerFont(QStringLiteral("Arial"), 9, QFont::Bold);
    QFont cellFont(QStringLiteral("Arial"), 7);
    QFont metaFont(QStringLiteral("Arial"), 9);

    const int rowHeight = 36;
    const int headerRowHeight = 38;
    const int titleBlock = 45;
    const int metaLine = 28;

    // Couleurs (style “propre”, proche des exports UI)
    const QColor orangeTitle(QStringLiteral("#F59E0B"));      // orange
    const QColor headerBg(QStringLiteral("#D9E8FF"));          // bleu clair
    const QColor headerBorder(QStringLiteral("#2563EB"));     // bleu
    const QColor borderColor(QStringLiteral("#CBD5E1"));      // gris
    const QColor evenRowBg(Qt::white);
    const QColor oddRowBg(QStringLiteral("#F3F7FF"));          // bleu très clair
    const QColor textColor(QStringLiteral("#0F172A"));        // bleu nuit

    auto drawTableHeader = [&](int yHeader) {
        painter.setFont(headerFont);
        int x = margin;
        for (int i = 0; i < nExportCols; ++i) {
            QRect rect(x, yHeader, colWidths[i], headerRowHeight);
            painter.setPen(QPen(headerBorder, 1));
            painter.setBrush(headerBg);
            painter.drawRect(rect);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(textColor, 1));
            painter.drawText(rect.adjusted(8, 0, -8, 0),
                             Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap,
                             headerLabels.at(i));
            x += colWidths[i];
        }
        return yHeader + headerRowHeight;
    };

    int y = margin;
    painter.setFont(titleFont);
    // Titre en orange (fond blanc)
    const QRect titleRect(margin, y, tableWidth, titleBlock - 10);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(orangeTitle, 2));
    painter.drawText(titleRect.adjusted(16, 0, -16, 0),
                     Qt::AlignVCenter | Qt::AlignLeft,
                     QStringLiteral("Exportation de l'inventaire"));
    // petit trait de séparation
    painter.setPen(QPen(orangeTitle, 1));
    painter.drawLine(margin, y + titleBlock - 12, margin + qMax(0, tableWidth), y + titleBlock - 12);
    y += titleBlock;
    painter.setPen(QPen(textColor, 1));

    painter.setFont(metaFont);
    const QString dateStr = QDate::currentDate().toString(QStringLiteral("dd/MM/yyyy"));
    const QString timeStr = QTime::currentTime().toString(QStringLiteral("hh:mm:ss"));

    const QString ctx = QStringLiteral("Tri par : %1 - Top %2 produit(s) - ordre du tableau actuel")
                            .arg(ui->InventorySort->currentText())
                            .arg(visibleRows.size());
    painter.drawText(QRect(margin, y, qMax(0, tableWidth), metaLine * 2),
                      Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap,
                      ctx);
    y += metaLine * 2 + 8;

    painter.setFont(cellFont);
    const QFontMetrics fmCell(cellFont);
    y = drawTableHeader(y);

    // Pied de page (date + heure) en bas de page
    const int footerHeight = 46;
    const int footerTopY = pageHeight - margin - footerHeight;
    const int footerLabelOffset = 95;
    auto drawFooter = [&]() {
        painter.setFont(metaFont);

        painter.setPen(QPen(orangeTitle, 1));
        painter.drawText(margin, footerTopY + 12, QStringLiteral("Date :"));
        painter.setPen(QPen(textColor, 1));
        painter.drawText(margin + footerLabelOffset, footerTopY + 12, dateStr);

        painter.setPen(QPen(orangeTitle, 1));
        painter.drawText(margin, footerTopY + 28, QStringLiteral("Heure :"));
        painter.setPen(QPen(textColor, 1));
        painter.drawText(margin + footerLabelOffset, footerTopY + 28, timeStr);
    };

    for (int rowIndex = 0; rowIndex < visibleRows.size(); ++rowIndex) {
        const int vr = visibleRows[rowIndex];
        const QColor rowBg = (rowIndex % 2 == 0) ? evenRowBg : oddRowBg;
        if (y + rowHeight > pageHeight - margin - footerHeight) {
            drawFooter();
            pdf.newPage();
            y = margin;
            painter.setFont(titleFont);
            // Titre “suite” en orange (fond blanc)
            const QRect suiteRect(margin, y, tableWidth, 32);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(orangeTitle, 2));
            painter.drawText(suiteRect.adjusted(16, 0, -16, 0),
                             Qt::AlignVCenter | Qt::AlignLeft,
                             QStringLiteral("Suite - export inventaire"));
            y += suiteRect.height();
            painter.setPen(QPen(textColor, 1));
            painter.setFont(cellFont);
            y = drawTableHeader(y); // header coloré
        }

        int x = margin;
        for (int ci = 0; ci < nExportCols; ++ci) {
            const int c = exportCols[ci];
            QRect rect(x, y, colWidths[ci], rowHeight);
            painter.setPen(QPen(borderColor, 1));
            painter.setBrush(rowBg);
            painter.drawRect(rect);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(textColor, 1));
            QString text;
            if (QTableWidgetItem *it = t->item(vr, c))
                text = it->text();
            text = fmCell.elidedText(text, Qt::ElideRight, rect.width() - 12);
            painter.drawText(rect.adjusted(6, 0, -6, 0),
                             Qt::AlignLeft | Qt::AlignVCenter,
                             text);
            x += colWidths[ci];
        }
        y += rowHeight;
    }

    drawFooter();
    painter.end();
    QMessageBox::information(this, QStringLiteral("Export PDF"),
                             QStringLiteral("Le PDF de l'inventaire a été généré."));
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void MainWindow::handleInventoryDetailExportPdf()
{
    // ==================== VÉRIFICATION DE LA SÉLECTION ====================
    const int currentRow = ui->TableInventory->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, tr("Exporter PDF"),
                             tr("Veuillez sélectionner un produit à exporter."));
        return;
    }

    QTableWidgetItem *itemId = ui->TableInventory->item(currentRow, 0);
    if (!itemId) {
        QMessageBox::warning(this, tr("Exporter PDF"),
                             tr("Produit introuvable dans le tableau."));
        return;
    }

    // ==================== RÉCUPÉRATION DES DONNÉES ====================
    // Depuis UserRole
    const QString idProduct  = itemId->data(Qt::UserRole).toString();
    const QString zone       = itemId->data(Qt::UserRole + 1).toString();
    const QString shelf      = itemId->data(Qt::UserRole + 2).toString();
    const QString unit       = itemId->data(Qt::UserRole + 3).toString();
    const QString type       = itemId->data(Qt::UserRole + 4).toString();
    const QString desc       = itemId->data(Qt::UserRole + 5).toString();
    const int qtReserved     = itemId->data(Qt::UserRole + 6).toInt();
    const int threshold      = itemId->data(Qt::UserRole + 7).toInt();

    // Depuis le tableau
    const QString sku   = ui->TableInventory->item(currentRow, 1) ? ui->TableInventory->item(currentRow, 1)->text() : "";
    const QString name  = ui->TableInventory->item(currentRow, 2) ? ui->TableInventory->item(currentRow, 2)->text() : "";
    const double price  = ui->TableInventory->item(currentRow, 3) ? ui->TableInventory->item(currentRow, 3)->data(Qt::EditRole).toDouble() : 0.0;
    const int quantity  = ui->TableInventory->item(currentRow, 4) ? ui->TableInventory->item(currentRow, 4)->text().toInt() : 0;
    const QString status = ui->TableInventory->item(currentRow, 5) ? ui->TableInventory->item(currentRow, 5)->text() : "";

    // ==================== NOM DU FICHIER ====================
    QString defaultFileName = QStringLiteral("Fiche_produit_%1.pdf").arg(sku.isEmpty() ? idProduct : sku);
    defaultFileName.replace(QChar('/'), '_');
    defaultFileName.replace(QChar('\\'), '_');

    QString filePath = QFileDialog::getSaveFileName(this, tr("Exporter la fiche produit"),
                                                    defaultFileName, tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) return;
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) filePath += ".pdf";

    // ==================== CRÉATION DU PDF ====================
    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Portrait);
    pdf.setResolution(300);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de créer le fichier PDF."));
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    // ==================== COULEURS ====================
    const QColor colorHeaderBg   = QColor("#004D40");   // Vert foncé
    const QColor colorAccent     = QColor("#00CED1");   // Turquoise
    const QColor colorLight      = QColor("#7FFFD4");   // Aquamarine
    const QColor colorTextDark   = QColor("#1E2A2A");
    const QColor colorTextLight  = QColor("#FFFFFF");
    const QColor colorBorder     = QColor("#CBD5E1");
    const QColor colorSectionBg  = QColor("#F8FAFC");

    // ==================== POLICES ====================
    QFont fontHeader("Segoe UI", 24, QFont::Bold);
    QFont fontSubHeader("Segoe UI", 16);
    QFont fontSection("Segoe UI", 18, QFont::Bold);
    QFont fontLabel("Segoe UI", 16, QFont::Bold);
    QFont fontValue("Segoe UI", 16);
    QFont fontDesc("Segoe UI", 14);
    QFont fontFooter("Segoe UI", 12);

    const int margin = 40;
    const int pageWidth = pdf.width();
    const int pageHeight = pdf.height();
    const int contentWidth = pageWidth - (2 * margin);
    const int col1X = margin;           // Colonne 1 (labels)
    const int col2X = margin + 500;     // Colonne 2 (valeurs)
    const int col3X = margin + 1500;     // Colonne 3 (labels)
    const int col4X = margin + 2000;     // Colonne 4 (valeurs)

    int y = margin;

    // ==================== EN-TÊTE ====================
    QRect headerRect(0, 0, pageWidth, 85);
    painter.fillRect(headerRect, colorHeaderBg);

    painter.setPen(colorTextLight);
    painter.setFont(fontHeader);
    painter.drawText(margin, 75, "FICHE PRODUIT");

    painter.setFont(fontSubHeader);
    painter.setPen(colorLight);
    painter.drawText(margin, 200, "Document d'inventaire détaillé");

    y = 600;

    // ==================== SECTION 1 : INFORMATIONS GÉNÉRALES ====================
    painter.setPen(colorHeaderBg);
    painter.setFont(fontSection);
    painter.drawText(margin, y, "INFORMATIONS GÉNÉRALES");
    y += 20;
    painter.setPen(QPen(colorAccent, 10));
    painter.drawLine(margin, y, margin + contentWidth, y);
    y += 130;

    // Ligne 1 : Nom + SKU
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Nom :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col2X, y, name.isEmpty() ? "---" : name);

    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col3X, y, "SKU :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col4X, y, sku.isEmpty() ? "---" : sku);
    y += 90;

    // Ligne 2 : Type + Statut
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Type :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col2X, y, type.isEmpty() ? "---" : type);

    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col3X, y, "Statut :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col4X, y, status.isEmpty() ? "---" : status);
    y += 90;

    // Ligne 3 : Prix + ID
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Prix :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    // Le champ "unit" est une caractéristique (affichée à part), pas un suffixe du prix.
    painter.drawText(col2X, y, QString::number(price, 'f', 2));

    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col3X, y, "ID Produit :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col4X, y, idProduct);
    y += 500;

    // ==================== SECTION 2 : GESTION DE STOCK ====================
    painter.setFont(fontSection);
    painter.setPen(colorHeaderBg);
    painter.drawText(margin, y, "GESTION DE STOCK");
    y += 20;
    painter.setPen(QPen(colorAccent, 10));
    painter.drawLine(margin, y, margin + contentWidth, y);
    y += 130;

    // Stock disponible avec indicateur visuel
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Qt Av :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    // "unit" est affiché séparément comme caractéristique.
    painter.drawText(col2X, y, QString::number(quantity));

    // Barre de progression
    int stockPercent = (threshold > 0) ? qMin(100, (quantity * 100) / threshold) : 100;
    QColor stockColor = (quantity <= threshold) ? QColor("#EF4444") : colorAccent;

    int barWidth = 180;
    int barHeight = 10;
    QRect barBg(col2X + 80, y - 12, barWidth, barHeight);
    painter.fillRect(barBg, QColor("#E2E8F0"));
    QRect barFill(col2X + 80, y - 12, (barWidth * quantity) / qMax(1, threshold), barHeight);
    painter.fillRect(barFill, stockColor);
    y += 90;

    // Ligne 2 : Qté réservée + Seuil
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Qt Rs :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col2X, y, QString::number(qtReserved));

    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col3X, y, "Seuil :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col4X, y, QString::number(threshold));

    // Ajout : afficher l'unité comme caractéristique (pas comme suffixe)
    y += 45;
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Unité :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col2X, y, unit.isEmpty() ? "---" : unit);
    y += 45;

    // Ligne 3 : Zone + Étagère
    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col1X, y, "Zone :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col2X, y, zone.isEmpty() ? "---" : zone);

    painter.setFont(fontLabel);
    painter.setPen(colorHeaderBg);
    painter.drawText(col3X, y, "Étagère :");
    painter.setFont(fontValue);
    painter.setPen(colorTextDark);
    painter.drawText(col4X, y, shelf.isEmpty() ? "---" : shelf);
    y += 500;

    // ==================== SECTION 3 : DESCRIPTION ====================
    painter.setFont(fontSection);
    painter.setPen(colorHeaderBg);
    painter.drawText(margin, y, "DESCRIPTION");
    y += 20;
    painter.setPen(QPen(colorAccent, 10));
    painter.drawLine(margin, y, margin + contentWidth, y);
    y += 80;

    // Fond clair pour la description
    QRect descBgRect(margin, y, contentWidth, 70);
    painter.fillRect(descBgRect, colorSectionBg);

    painter.setFont(fontDesc);
    painter.setPen(colorTextDark);
    QRect descRect(margin + 10, y + 10, contentWidth - 20, 70);
    QString descText = desc.isEmpty() ? "Aucune description disponible pour ce produit." : desc;
    painter.drawText(descRect, Qt::TextWordWrap, descText);
    y += 90;

    // ==================== PIED DE PAGE ====================
    painter.setPen(QPen(colorBorder, 10));
    painter.drawLine(margin, pageHeight - 110, margin + contentWidth, pageHeight - 110);

    painter.setFont(fontFooter);
    painter.setPen(colorHeaderBg);

    QString dateStr = QDate::currentDate().toString("dd/MM/yyyy");
    QString timeStr = QTime::currentTime().toString("HH:mm");

    painter.drawText(margin, pageHeight - 130, "Document généré le : " + dateStr + " à " + timeStr);
    painter.setPen(colorAccent);
    painter.drawText(pageWidth - margin - 450, pageHeight - 130, "SmartResearch v1.0");

    painter.end();

    // ==================== CONFIRMATION ====================
    QMessageBox::information(this, tr("Export PDF"),
                             tr("La fiche produit a été exportée avec succès.\n\n"
                                "Fichier : %1").arg(filePath));
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::on_BtnPopupSaveInventory_2_clicked()
{
    // Auto-uppercase for consistency
    const QString name      = ui->Name_2->text().trimmed().toUpper();
    const QString sku       = normalizeSkuInput(ui->Sku_2->text().trimmed());

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

    // Validation: Name
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom du produit ne peut pas être vide.");
        return;
    }

    // Validation stricte SKU: ABC-123
    static const QRegularExpression skuRegex(QStringLiteral("^[A-Z]{3}-[0-9]{3}$"));
    if (!skuRegex.match(sku).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le SKU doit respecter le format ABC-123.");
        ui->Sku_2->setFocus();
        ui->Sku_2->selectAll();
        return;
    }
    if (inventorySkuExists(sku, idProductToEdit)) {
        QMessageBox::warning(this, "Validation", "Ce SKU existe deja. Veuillez saisir un SKU unique.");
        ui->Sku_2->setFocus();
        ui->Sku_2->selectAll();
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
    refreshInventoryTypeFilter();
    loadInventory();
}

void MainWindow::on_BtnPopupResetInventory_2_clicked()
{
    const int r = ui->TableInventory->currentRow();
    if (r < 0) return;
    if (!ui->TableInventory->item(r, 0)) return;

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

void MainWindow::handleInventoryDelete()
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
    refreshInventoryTypeFilter();
    loadInventory();
}

// ── SEARCH / FILTER ───────────────────────────────────────────────────────────


//end















