#include "ocrscanner.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QFileDialog>
#include <QPixmap>
#include <QFont>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QImage>
#include <QBuffer>
#include <QTemporaryFile>
#include <QScrollArea>
#include <QStyle>

// ════════════════════════════════════════════════════════════════════════════
//  Constructeur / UI
// ════════════════════════════════════════════════════════════════════════════
OcrScannerDialog::OcrScannerDialog(QWidget *parent)
    : QDialog(parent)
    , m_settings("SmartResearchLab", "OcrScanner")
{
    setWindowTitle("📷  Scanner de Reçu — Extraction OCR");
    setMinimumSize(600, 560);
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    m_nam = new QNetworkAccessManager(this);
    connect(m_nam, &QNetworkAccessManager::finished,
            this,  &OcrScannerDialog::onNetworkReply);
    buildUi();
}

// ════════════════════════════════════════════════════════════════════════════
//  Construction de l'interface
// ════════════════════════════════════════════════════════════════════════════
void OcrScannerDialog::buildUi()
{
    setStyleSheet(R"(
        QDialog { background:#f7fafc; font-family:'Segoe UI'; }

        QLabel#title {
            font-size:15px; font-weight:900; color:#0d5a5f;
            padding:10px 0 4px 0;
        }
        QLabel#subtitle { font-size:10px; color:#718096; padding-bottom:6px; }

        QFrame#card {
            background:white; border:1px solid #e2e8f0;
            border-radius:12px; padding:4px;
        }
        QLabel#sectionTitle {
            font-size:11px; font-weight:700; color:#1F8E95;
            padding:6px 0 2px 0;
        }
        QLabel#resultKey   { font-size:11px; color:#4a5568; font-weight:600; }
        QLabel#resultVal   { font-size:11px; color:#1a202c; font-weight:700; }
        QLabel#statusOk    { color:#27ae60; font-size:10px; font-weight:700; }
        QLabel#statusErr   { color:#e53e3e; font-size:10px; }
        QLabel#statusInfo  { color:#718096; font-size:10px; }

        QLineEdit {
            border:1.5px solid #cbd5e0; border-radius:7px;
            padding:6px 10px; font-size:11px; background:white;
        }
        QLineEdit:focus { border-color:#1F8E95; }

        QPushButton#btnBrowse {
            background:#edf2f7; color:#2d3748; border:1px solid #cbd5e0;
            border-radius:7px; padding:6px 14px; font-size:11px;
        }
        QPushButton#btnBrowse:hover { background:#e2e8f0; }

        QPushButton#btnAnalyze {
            background:qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #1F8E95, stop:1 #2ecc71);
            color:white; border:none; border-radius:9px;
            font-size:13px; font-weight:800; padding:10px 22px; min-height:38px;
        }
        QPushButton#btnAnalyze:hover  { background:#17727a; }
        QPushButton#btnAnalyze:disabled { background:#a0aec0; }

        QPushButton#btnAccept {
            background:#27ae60; color:white; border:none; border-radius:9px;
            font-size:12px; font-weight:700; padding:10px 22px; min-height:38px;
        }
        QPushButton#btnAccept:hover    { background:#219a52; }
        QPushButton#btnAccept:disabled { background:#a0aec0; }

        QPushButton#btnCancel {
            background:#edf2f7; color:#4a5568; border:none; border-radius:9px;
            font-size:12px; padding:10px 22px; min-height:38px;
        }
        QPushButton#btnCancel:hover { background:#e2e8f0; }

        QTextEdit {
            border:1px solid #e2e8f0; border-radius:7px;
            font-size:10px; font-family:'Consolas','Courier New',monospace;
            background:#f8f9fa; padding:4px;
        }
        QProgressBar {
            border:none; border-radius:4px; background:#e2e8f0;
            text-align:center; font-size:9px; max-height:8px;
        }
        QProgressBar::chunk { background:#1F8E95; border-radius:4px; }
    )");

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 12, 20, 16);
    root->setSpacing(10);

    // ── Titre ────────────────────────────────────────────────────────────────
    auto *lblTitle = new QLabel("📷  Scanner de Reçu / Facture", this);
    lblTitle->setObjectName("title");
    lblTitle->setAlignment(Qt::AlignCenter);
    auto *lblSub = new QLabel(
        "Importez une image → extraction automatique du montant, de la date et de la catégorie", this);
    lblSub->setObjectName("subtitle");
    lblSub->setAlignment(Qt::AlignCenter);
    root->addWidget(lblTitle);
    root->addWidget(lblSub);

    // ── Zone sélection image ─────────────────────────────────────────────────
    auto *cardFile = new QFrame(this);
    cardFile->setObjectName("card");
    auto *fileLayout = new QHBoxLayout(cardFile);
    fileLayout->setContentsMargins(12, 8, 12, 8);
    fileLayout->setSpacing(8);

    m_editPath = new QLineEdit(this);
    m_editPath->setPlaceholderText("Chemin de l'image (JPG, PNG, PDF…)");
    m_editPath->setReadOnly(true);

    m_btnBrowse = new QPushButton("Parcourir…", this);
    m_btnBrowse->setObjectName("btnBrowse");
    connect(m_btnBrowse, &QPushButton::clicked, this, &OcrScannerDialog::onBrowse);

    // Aperçu miniature
    m_lblPreview = new QLabel(this);
    m_lblPreview->setFixedSize(64, 64);
    m_lblPreview->setAlignment(Qt::AlignCenter);
    m_lblPreview->setStyleSheet(
        "border:1px solid #e2e8f0; border-radius:6px; background:#f0f0f0;");
    m_lblPreview->setText("🖼");
    m_lblPreview->setFont(QFont("Segoe UI", 20));

    fileLayout->addWidget(m_lblPreview);
    fileLayout->addWidget(m_editPath, 1);
    fileLayout->addWidget(m_btnBrowse);
    root->addWidget(cardFile);

    // ── Sélecteur de langue ──────────────────────────────────────────────────
    auto *langRow = new QHBoxLayout();
    langRow->setSpacing(10);
    auto *lblLang = new QLabel("🌐  Langue du document :", this);
    lblLang->setObjectName("resultKey");
    m_comboLang = new QComboBox(this);
    m_comboLang->addItem("🔍  Détection auto  (recommandé)", "auto");
    m_comboLang->addItem("🇬🇧  English",   "eng");
    m_comboLang->addItem("🇫🇷  Français",  "fre");
    m_comboLang->addItem("🇸🇦  العربية",   "ara");
    m_comboLang->setFixedHeight(30);
    langRow->addWidget(lblLang);
    langRow->addWidget(m_comboLang, 1);
    root->addLayout(langRow);

    // ── Bouton analyser + barre de progression ───────────────────────────────
    m_progress = new QProgressBar(this);
    m_progress->setRange(0, 0);   // indéterminé
    m_progress->setVisible(false);

    m_btnAnalyze = new QPushButton("🔍  Analyser le reçu", this);
    m_btnAnalyze->setObjectName("btnAnalyze");
    m_btnAnalyze->setEnabled(false);
    connect(m_btnAnalyze, &QPushButton::clicked, this, &OcrScannerDialog::onAnalyze);

    m_lblStatus = new QLabel("Sélectionnez une image pour commencer.", this);
    m_lblStatus->setObjectName("statusInfo");
    m_lblStatus->setAlignment(Qt::AlignCenter);

    root->addWidget(m_btnAnalyze);
    root->addWidget(m_progress);
    root->addWidget(m_lblStatus);

    // ── Carte résultats ──────────────────────────────────────────────────────
    auto *cardRes = new QFrame(this);
    cardRes->setObjectName("card");
    auto *resLayout = new QGridLayout(cardRes);
    resLayout->setContentsMargins(16, 10, 16, 10);
    resLayout->setHorizontalSpacing(16);
    resLayout->setVerticalSpacing(6);

    auto makeKey = [&](const QString &txt) {
        auto *l = new QLabel(txt, this); l->setObjectName("resultKey"); return l;
    };
    auto makeVal = [&](QLabel **ptr, const QString &def = "—") {
        *ptr = new QLabel(def, this); (*ptr)->setObjectName("resultVal"); return *ptr;
    };

    resLayout->addWidget(new QLabel("📊  Données extraites", this), 0, 0, 1, 4);
    {   // make the section title bold teal
        auto *l = resLayout->itemAtPosition(0,0)->widget();
        l->setObjectName("sectionTitle");
    }

    resLayout->addWidget(makeKey("💰 Montant (DT)"),  1, 0);
    resLayout->addWidget(makeVal(&m_lblAmount),         1, 1);
    resLayout->addWidget(makeKey("📅 Date"),            1, 2);
    resLayout->addWidget(makeVal(&m_lblDate),            1, 3);
    resLayout->addWidget(makeKey("🔖 Type"),            2, 0);
    resLayout->addWidget(makeVal(&m_lblType),            2, 1);
    resLayout->addWidget(makeKey("🏷 Catégorie"),      2, 2);
    resLayout->addWidget(makeVal(&m_lblCat),             2, 3);

    root->addWidget(cardRes);

    // ── Texte brut OCR (repliable) ───────────────────────────────────────────
    auto *lblRaw = new QLabel("📄  Texte brut extrait :", this);
    lblRaw->setObjectName("sectionTitle");
    root->addWidget(lblRaw);

    m_txtRaw = new QTextEdit(this);
    m_txtRaw->setReadOnly(true);
    m_txtRaw->setMaximumHeight(90);
    m_txtRaw->setPlaceholderText("Le texte reconnu par l'OCR apparaîtra ici…");
    root->addWidget(m_txtRaw);

    // ── Boutons finaux ───────────────────────────────────────────────────────
    auto *btnRow = new QHBoxLayout();
    btnRow->setSpacing(10);

    auto *btnCancel = new QPushButton("Annuler", this);
    btnCancel->setObjectName("btnCancel");
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);

    m_btnAccept = new QPushButton("✔  Remplir le formulaire", this);
    m_btnAccept->setObjectName("btnAccept");
    m_btnAccept->setEnabled(false);
    connect(m_btnAccept, &QPushButton::clicked, this, &QDialog::accept);

    btnRow->addWidget(btnCancel);
    btnRow->addStretch();
    btnRow->addWidget(m_btnAccept);
    root->addLayout(btnRow);
}

// ════════════════════════════════════════════════════════════════════════════
//  Slots UI
// ════════════════════════════════════════════════════════════════════════════
void OcrScannerDialog::onBrowse()
{
    const QString last = m_settings.value("lastDir", QDir::homePath()).toString();
    const QString path = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un reçu / facture",
        last,
        "Images (*.jpg *.jpeg *.png *.bmp *.tif *.tiff *.pdf *.gif)");
    if (path.isEmpty()) return;

    m_settings.setValue("lastDir", QFileInfo(path).absolutePath());
    m_editPath->setText(path);

    // Aperçu miniature
    QPixmap px(path);
    if (!px.isNull()) {
        m_lblPreview->setPixmap(px.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_lblPreview->setText("");
    } else {
        m_lblPreview->setPixmap(QPixmap());
        m_lblPreview->setText("📄");
    }

    m_btnAnalyze->setEnabled(true);
    m_lblStatus->setObjectName("statusInfo");
    m_lblStatus->setText("Image prête. Cliquez sur « Analyser » pour extraire les données.");
    m_lblStatus->style()->unpolish(m_lblStatus);
    m_lblStatus->style()->polish(m_lblStatus);
}

void OcrScannerDialog::onAnalyze()
{
    const QString path = m_editPath->text().trimmed();
    if (path.isEmpty()) return;
    sendOcrRequest(path);
}

// ════════════════════════════════════════════════════════════════════════════
//  Envoi de la requête OCR (OCR.Space gratuit)
// ════════════════════════════════════════════════════════════════════════════
void OcrScannerDialog::sendOcrRequest(const QString &filePath)
{
    setAnalyzing(true);
    m_lblStatus->setObjectName("statusInfo");
    m_lblStatus->setText("Préparation de l'image…");
    m_lblStatus->style()->unpolish(m_lblStatus);
    m_lblStatus->style()->polish(m_lblStatus);

    const QString apiKey = m_settings.value("ocrApiKey", "helloworld").toString();

    // ── Prétraitement : redimensionner si l'image dépasse 800 KB ─────────────
    QByteArray imageData;
    QString    mimeType = "image/jpeg";
    QString    filename = QFileInfo(filePath).fileName();

    const QString ext = QFileInfo(filePath).suffix().toLower();
    if (ext == "pdf") {
        // PDF : envoyer directement (taille vérifiée)
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly)) {
            setAnalyzing(false);
            m_lblStatus->setObjectName("statusErr");
            m_lblStatus->setText("Impossible d'ouvrir le fichier.");
            m_lblStatus->style()->unpolish(m_lblStatus);
            m_lblStatus->style()->polish(m_lblStatus);
            return;
        }
        imageData = f.readAll();
        mimeType  = "application/pdf";
    } else {
        // Image : charger, redimensionner si nécessaire
        QImage img(filePath);
        if (img.isNull()) {
            setAnalyzing(false);
            m_lblStatus->setObjectName("statusErr");
            m_lblStatus->setText("Format d'image non reconnu.");
            m_lblStatus->style()->unpolish(m_lblStatus);
            m_lblStatus->style()->polish(m_lblStatus);
            return;
        }

        // Réduire si trop grande (max 1800px de large pour OCR optimal)
        if (img.width() > 1800 || img.height() > 1800)
            img = img.scaled(1800, 1800, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Convertir en JPEG compressé dans un buffer mémoire
        QBuffer buf(&imageData);
        buf.open(QIODevice::WriteOnly);
        int quality = 85;
        img.save(&buf, "JPEG", quality);

        // Si encore > 900 KB, recompresser
        while (imageData.size() > 900 * 1024 && quality > 40) {
            imageData.clear();
            buf.seek(0);
            quality -= 15;
            img.save(&buf, "JPEG", quality);
        }
        mimeType = "image/jpeg";
        filename  = QFileInfo(filePath).baseName() + ".jpg";
    }

    m_lblStatus->setText(
        QString("Envoi au service OCR (%1 KB)…").arg(imageData.size() / 1024));
    m_lblStatus->style()->unpolish(m_lblStatus);
    m_lblStatus->style()->polish(m_lblStatus);

    // ── Construction de la requête multipart ─────────────────────────────────
    auto *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    auto addField = [&](const QByteArray &name, const QByteArray &value) {
        QHttpPart p;
        p.setHeader(QNetworkRequest::ContentDispositionHeader,
                    QVariant("form-data; name=\"" + name + "\""));
        p.setBody(value);
        multiPart->append(p);
    };

    // Langue sélectionnée par l'utilisateur
    const QString langCode = m_comboLang->currentData().toString();
    // "auto" → on envoie "eng,fre,ara" pour couvrir les 3 langues
    const QByteArray langParam = (langCode == "auto")
                                     ? QByteArray("eng")
                                     : langCode.toUtf8();
    // L'arabe est mieux géré par le moteur 1 (Tesseract/RTL)
    const QByteArray engineParam = (langCode == "ara") ? "1" : "2";

    addField("language",           langParam);
    addField("isOverlayRequired",  "false");
    addField("detectOrientation",  "true");
    addField("scale",              "true");
    addField("isTable",            "true");
    addField("OCREngine",          engineParam);

    // Champ image
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mimeType));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(QString("form-data; name=\"file\"; filename=\"%1\"")
                                     .arg(filename)));
    imagePart.setBody(imageData);
    multiPart->append(imagePart);

    QNetworkRequest request(QUrl("https://api.ocr.space/parse/image"));
    request.setRawHeader("apikey", apiKey.toUtf8());
    request.setHeader(QNetworkRequest::UserAgentHeader, "SmartResearchLab-OCR/1.0");

    QNetworkReply *reply = m_nam->post(request, multiPart);
    multiPart->setParent(reply);
}

// ════════════════════════════════════════════════════════════════════════════
//  Réception de la réponse OCR
// ════════════════════════════════════════════════════════════════════════════
void OcrScannerDialog::onNetworkReply(QNetworkReply *reply)
{
    reply->deleteLater();
    setAnalyzing(false);

    if (reply->error() != QNetworkReply::NoError) {
        m_lblStatus->setObjectName("statusErr");
        m_lblStatus->setText("⚠  Erreur réseau : " + reply->errorString());
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
        return;
    }

    const QByteArray data = reply->readAll();
    const QJsonObject json = QJsonDocument::fromJson(data).object();

    // exitCode 1 = succès complet, 2 = succès partiel — les deux sont utilisables
    const int exitCode = json.value("OCRExitCode").toInt();
    if (exitCode > 2) {
        // Récupérer le message d'erreur depuis plusieurs emplacements possibles
        QString errMsg = json.value("ErrorMessage").toString();
        if (errMsg.isEmpty()) errMsg = json.value("ErrorDetails").toString();
        if (errMsg.isEmpty()) {
            // Chercher dans ParsedResults
            const QJsonArray pr = json.value("ParsedResults").toArray();
            if (!pr.isEmpty())
                errMsg = pr.at(0).toObject().value("ErrorMessage").toString();
        }
        if (errMsg.isEmpty())
            errMsg = QString("Code %1 — vérifiez la qualité de l'image.").arg(exitCode);

        m_lblStatus->setObjectName("statusErr");
        m_lblStatus->setText("⚠  OCR échoué : " + errMsg);
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
        // Afficher la réponse brute pour debug
        m_txtRaw->setPlainText(QString::fromUtf8(data));
        return;
    }

    const QJsonArray parsedResults = json.value("ParsedResults").toArray();
    if (parsedResults.isEmpty()) {
        m_lblStatus->setObjectName("statusErr");
        m_lblStatus->setText("⚠  Aucun texte reconnu dans l'image.");
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
        return;
    }

    const QJsonObject firstResult = parsedResults.at(0).toObject();
    if (firstResult.value("FileParseExitCode").toInt() != 1) {
        const QString e = firstResult.value("ErrorMessage").toString("Image illisible.");
        m_lblStatus->setObjectName("statusErr");
        m_lblStatus->setText("⚠  " + e);
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
        return;
    }

    const QString rawText = firstResult.value("ParsedText").toString().trimmed();

    m_txtRaw->setPlainText(rawText);
    m_result = parseReceiptText(rawText);
    displayResult(m_result);

    m_lblStatus->setObjectName("statusOk");
    m_lblStatus->setText("✔  Analyse terminée ! Vérifiez les données puis cliquez sur « Remplir ».");
    m_lblStatus->style()->unpolish(m_lblStatus);
    m_lblStatus->style()->polish(m_lblStatus);
    m_btnAccept->setEnabled(m_result.success);
}

// ════════════════════════════════════════════════════════════════════════════
//  Parseur de texte de reçu
// ════════════════════════════════════════════════════════════════════════════
OcrResult OcrScannerDialog::parseReceiptText(const QString &text)
{
    OcrResult result;
    result.rawText = text;
    result.success = !text.isEmpty();

    const QString lower = text.toLower();

    // ── 1. MONTANT ───────────────────────────────────────────────────────────
    // Cherche "Total", "Montant", "Net à payer", "TTC", "À payer" suivi d'un nombre
    QRegularExpression reAmountKw(
        R"((?:total(?:\s+ttc)?|montant(?:\s+total)?|net\s+[àa]\s+payer|[àa]\s+payer|ttc|net\s+a\s+payer|amount|sous[\s\-]total)\s*[:\s=]*\s*([\d\s]{1,8}[,\.][\d]{1,3}))",
        QRegularExpression::CaseInsensitiveOption);
    auto m = reAmountKw.match(lower);
    if (m.hasMatch()) {
        QString s = m.captured(1).remove(' ').replace(',', '.');
        bool ok; double v = s.toDouble(&ok);
        if (ok && v > 0.0) { result.amount = v; result.hasAmount = true; }
    }

    // Fallback : cherche la valeur numérique la plus grande (souvent le total)
    if (!result.hasAmount) {
        QRegularExpression reNum(R"(\b(\d{1,6}[,\.]\d{1,3})\b)");
        auto it = reNum.globalMatch(text);
        double maxVal = 0.0;
        while (it.hasNext()) {
            auto nm = it.next();
            double v = nm.captured(1).replace(',', '.').toDouble();
            if (v > maxVal && v < 1000000.0) maxVal = v;
        }
        if (maxVal > 0.0) { result.amount = maxVal; result.hasAmount = true; }
    }

    // ── 2. DATE ──────────────────────────────────────────────────────────────
    QRegularExpression reDate(R"((\d{1,2})[/\-\.](\d{1,2})[/\-\.](\d{2,4}))");
    auto dm = reDate.match(text);
    if (dm.hasMatch()) {
        int d = dm.captured(1).toInt();
        int mo = dm.captured(2).toInt();
        int y  = dm.captured(3).toInt();
        if (y < 100) y += 2000;
        QDate dt(y, mo, d);
        if (!dt.isValid()) { dt = QDate(y, d, mo); }  // essai inversé
        if (dt.isValid() && dt.year() >= 2000 && dt <= QDate::currentDate().addDays(1)) {
            result.date    = dt;
            result.hasDate = true;
        }
    }

    // ── 3. TYPE ──────────────────────────────────────────────────────────────
    result.type = "Depense";  // défaut : les reçus sont des dépenses
    static const QStringList revenuKw = {
        "remboursement", "virement recu", "salaire", "encaissement",
        "avoir", "credit note", "note de crédit"
    };
    for (const auto &kw : revenuKw) {
        if (lower.contains(kw)) { result.type = "Revenu"; break; }
    }

    // ── 4. CATÉGORIE ─────────────────────────────────────────────────────────
    struct CatKw { QString cat; QStringList kws; };
    static const QList<CatKw> catMap = {
        { "Restauration",  {"restaurant","café","cafe","pizza","burger","snack","traiteur","fast food"} },
        { "Transport",     {"taxi","uber","lyft","carburant","essence","gasoil","parking","station"} },
        { "Fournitures",   {"papeterie","fournitures","bureau","paper","cartouche","encre"} },
        { "IT & Matériel", {"informatique","ordinateur","laptop","clavier","souris","câble","cable","electronic"} },
        { "Santé",         {"pharmacie","medecin","médecin","clinique","médical","medical","sante","sante"} },
        { "Formation",     {"formation","cours","séminaire","seminaire","conference","conférence","atelier"} },
        { "Loyer",         {"loyer","location","bail","immobilier","gérance"} },
        { "Énergie",       {"electricite","électricité","sonede","steg","eau","gaz"} },
        { "Communication", {"telecom","telephone","internet","mobile","abonnement","operateur"} },
        { "Divers",        {"achat","vente","commerce","magasin","boutique","store"} },
    };
    for (const auto &entry : catMap) {
        for (const auto &kw : entry.kws) {
            if (lower.contains(kw)) { result.category = entry.cat; break; }
        }
        if (!result.category.isEmpty()) break;
    }

    // ── 5. DESCRIPTION (première ligne significative) ─────────────────────────
    const QStringList lines = text.split('\n', Qt::SkipEmptyParts);
    for (const auto &line : lines) {
        const QString t = line.trimmed();
        if (t.length() >= 4 && !t.contains(QRegularExpression(R"(^\d+[\s,\.]*$)"))) {
            result.description = t.left(80);
            break;
        }
    }

    return result;
}

// ════════════════════════════════════════════════════════════════════════════
//  Affichage du résultat dans les labels
// ════════════════════════════════════════════════════════════════════════════
void OcrScannerDialog::displayResult(const OcrResult &r)
{
    m_lblAmount->setText(r.hasAmount
        ? QString("<b style='color:#1F8E95'>%1 DT</b>").arg(r.amount, 0, 'f', 2)
        : "<span style='color:#a0aec0'>Non détecté</span>");

    m_lblDate->setText(r.hasDate
        ? QString("<b>%1</b>").arg(r.date.toString("dd/MM/yyyy"))
        : "<span style='color:#a0aec0'>Non détecté</span>");

    m_lblType->setText(!r.type.isEmpty()
        ? QString("<b>%1</b>").arg(r.type == "Depense" ? "Dépense" : "Revenu")
        : "<span style='color:#a0aec0'>—</span>");

    m_lblCat->setText(!r.category.isEmpty()
        ? QString("<b>%1</b>").arg(r.category)
        : "<span style='color:#a0aec0'>Non détecté</span>");

    m_lblAmount->setTextFormat(Qt::RichText);
    m_lblDate->setTextFormat(Qt::RichText);
    m_lblType->setTextFormat(Qt::RichText);
    m_lblCat->setTextFormat(Qt::RichText);
}

// ════════════════════════════════════════════════════════════════════════════
//  Helpers
// ════════════════════════════════════════════════════════════════════════════
void OcrScannerDialog::setAnalyzing(bool busy)
{
    m_btnAnalyze->setEnabled(!busy);
    m_btnBrowse->setEnabled(!busy);
    m_progress->setVisible(busy);
    m_btnAccept->setEnabled(false);
}
