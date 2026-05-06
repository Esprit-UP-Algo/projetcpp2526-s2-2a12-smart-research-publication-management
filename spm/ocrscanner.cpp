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
#include <QInputDialog>
#include <QSslConfiguration>
#include <QPdfDocument>

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
    QSettings themeSettings("SmartResearchLab", "Theme");
    const bool isDark = themeSettings.value("darkMode", false).toBool();

    const QString dlgBg     = isDark ? "#0f172a" : "#f2ebe4";
    const QString cardBg    = isDark ? "#1e293b" : "#ffffff";
    const QString cardBord  = isDark ? "#334155" : "#e0be9c";
    const QString textPri   = isDark ? "#f1f5f9" : "#2c1e16";
    const QString textSec   = isDark ? "#94a3b8" : "#8b6655";
    const QString inputBg   = isDark ? "#0f172a" : "#ffffff";
    const QString statusClr = isDark ? "#10b981" : "#27ae60"; // Vert vif

    QString ss = QString("QDialog { background: %1; font-family:'Segoe UI'; }").arg(dlgBg);
    ss += QString("QLabel#title { font-size:18px; font-weight:900; color:%1; padding:10px 0 4px 0; }").arg(textPri);
    ss += QString("QLabel#subtitle { font-size:11px; color:%1; padding-bottom:6px; }").arg(textSec);
    ss += QString("QFrame#card { background:%1; border:1.5px solid %2; border-radius:16px; padding:6px; }").arg(cardBg, cardBord);
    ss += QString("QLabel#sectionTitle { font-size:12px; font-weight:800; color:%1; padding:6px 0 2px 0; text-transform: uppercase; }").arg(textSec);
    ss += QString("QLabel#resultKey { font-size:11px; color:%1; font-weight:700; }").arg(textSec);
    ss += QString("QLabel#resultVal { font-size:11px; color:%1; font-weight:700; }").arg(textPri);
    ss += QString("QLabel#statusOk { color:%1; font-size:11px; font-weight:700; }").arg(statusClr);
    ss += QString("QLabel#statusErr { color:#e53e3e; font-size:11px; }");
    ss += QString("QLabel#statusInfo { color:%1; font-size:11px; }").arg(textSec);
    ss += QString("QLineEdit { border:1.5px solid %1; border-radius:10px; padding:8px 12px; font-size:12px; background:%2; color:%3; }").arg(cardBord, inputBg, textPri);
    ss += QString("QLineEdit:focus { border-color:#d1a97d; }");
    ss += QString("QPushButton#btnBrowse { background:%1; color:%2; border:1.5px solid %3; border-radius:10px; padding:8px 16px; font-size:12px; font-weight:700; }").arg(inputBg, textPri, cardBord);
    ss += QString("QPushButton#btnBrowse:hover { background: rgba(240, 206, 170, 0.2); }");
    ss += "QPushButton#btnAnalyze { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f0ceaa, stop:1 #e0be9c); color:#2c1e16; border:none; border-radius:12px; font-size:14px; font-weight:800; padding:10px 24px; min-height:42px; }";
    ss += "QPushButton#btnAnalyze:hover { background:#ebc49a; }";
    ss += "QPushButton#btnAnalyze:disabled { background:#dcdcdc; color:#999; }";
    ss += QString("QPushButton#btnAccept { background:#2c1e16; color:#f2ebe4; border:none; border-radius:12px; font-size:13px; font-weight:800; padding:10px 24px; min-height:42px; }");
    ss += QString("QPushButton#btnAccept:hover { background:#4a3728; }");
    ss += QString("QPushButton#btnAccept:disabled { background:#dcdcdc; color:#999; }");
    ss += QString("QPushButton#btnCancel { background: transparent; color:%1; border:1.5px solid %2; border-radius:12px; font-size:13px; font-weight:700; padding:10px 24px; min-height:42px; }").arg(textSec, cardBord);
    ss += QString("QPushButton#btnCancel:hover { background: rgba(240, 206, 170, 0.2); color:%1; }").arg(textPri);
    ss += QString("QTextEdit { border:1.5px solid %1; border-radius:12px; font-size:11px; font-family:'Consolas','Courier New',monospace; background:%2; padding:6px; color:%3; }").arg(cardBord, inputBg, textPri);
    ss += QString("QProgressBar { background:%1; border:1px solid %2; border-radius:6px; text-align:center; font-size:10px; max-height:12px; }").arg(dlgBg, cardBord);
    ss += "QProgressBar::chunk { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f0ceaa, stop:1 #e0be9c); border-radius:5px; }";
    setStyleSheet(ss);

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
        "border:1.5px solid #e0be9c; border-radius:10px; background:#ffffff; color:#8b6655;");
    m_lblPreview->setText("🖼");
    m_lblPreview->setFont(QFont("Segoe UI", 20));

    fileLayout->addWidget(m_lblPreview);
    fileLayout->addWidget(m_editPath, 1);
    fileLayout->addWidget(m_btnBrowse);
    root->addWidget(cardFile);

    // ── Sélecteur de langue + bouton clé API ────────────────────────────────
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

    auto *btnKey = new QPushButton("🔑", this);
    btnKey->setObjectName("btnBrowse");
    btnKey->setFixedSize(32, 30);
    btnKey->setToolTip("Configurer la clé API OCR.Space\n"
                       "Clé gratuite sur : ocr.space/ocrapi/freekey");
    connect(btnKey, &QPushButton::clicked, this, &OcrScannerDialog::onConfigureApiKey);

    langRow->addWidget(lblLang);
    langRow->addWidget(m_comboLang, 1);
    langRow->addWidget(btnKey);
    root->addLayout(langRow);

    // ── Bouton analyser + barre de progression ───────────────────────────────
    m_progress = new QProgressBar(this);
    m_progress->setRange(0, 0);   // indéterminé
    m_progress->setVisible(false);

    m_btnAnalyze = new QPushButton("🔍  Analyser le reçu", this);
    m_btnAnalyze->setObjectName("btnAnalyze");
    m_btnAnalyze->setEnabled(false);
    connect(m_btnAnalyze, &QPushButton::clicked, this, &OcrScannerDialog::onAnalyze);

    auto *btnDemo = new QPushButton("🎭  Mode démonstration", this);
    btnDemo->setObjectName("btnBrowse");
    btnDemo->setToolTip("Remplit avec des données exemple (sans appel API)");
    connect(btnDemo, &QPushButton::clicked, this, [this]() {
        OcrResult demo;
        demo.amount    = 247.50;
        demo.hasAmount = true;
        demo.date      = QDate(2026, 4, 8);
        demo.hasDate   = true;
        demo.type      = "Depense";
        demo.category  = "Fournitures";
        demo.description = "FACTURE INTERNE — DEP-ESP-2026";
        demo.rawText   = "FACTURE INTERNE\nDate : 08/04/2026\nMontant TTC : 247,50 DT\nType : Dépense\nCatégorie : Fournitures";
        demo.success   = true;
        m_result = demo;
        m_txtRaw->setPlainText(demo.rawText);
        displayResult(demo);
        m_lblStatus->setObjectName("statusOk");
        m_lblStatus->setText("✔  Données de démonstration chargées — cliquez sur « Remplir ».");
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
        m_btnAccept->setEnabled(true);
    });

    m_lblStatus = new QLabel("Sélectionnez une image pour commencer.", this);
    m_lblStatus->setObjectName("statusInfo");
    m_lblStatus->setAlignment(Qt::AlignCenter);

    auto *analyzeRow = new QHBoxLayout();
    analyzeRow->setSpacing(8);
    analyzeRow->addWidget(m_btnAnalyze, 3);
    analyzeRow->addWidget(btnDemo, 1);

    root->addLayout(analyzeRow);
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

    QString apiKey = m_settings.value("ocrApiKey", "K87415250588957").toString();
    if (apiKey.isEmpty() || apiKey == "helloworld")
        apiKey = "K87415250588957";

    // ── Prétraitement : redimensionner si l'image dépasse 800 KB ─────────────
    QByteArray imageData;
    QString    mimeType = "image/jpeg";
    QString    filename = QFileInfo(filePath).fileName();

    const QString ext = QFileInfo(filePath).suffix().toLower();
    if (ext == "pdf") {
        // PDF → rendu de la 1ère page en JPEG via QPdfDocument::render() (synchrone)
        QPdfDocument pdfDoc;
        const QPdfDocument::Error err = pdfDoc.load(filePath);
        if (err != QPdfDocument::Error::None) {
            setAnalyzing(false);
            m_lblStatus->setObjectName("statusErr");
            m_lblStatus->setText(QString("Impossible d'ouvrir le PDF (erreur %1).").arg(int(err)));
            m_lblStatus->style()->unpolish(m_lblStatus);
            m_lblStatus->style()->polish(m_lblStatus);
            return;
        }
        // Rendu à 150 DPI (A4 ≈ 1240 × 1754 px)
        const QSizeF pageSizePt = pdfDoc.pagePointSize(0);
        const qreal  dpi        = 150.0;
        const QSize  renderSize(
            qRound(pageSizePt.width()  / 72.0 * dpi),
            qRound(pageSizePt.height() / 72.0 * dpi));

        const QImage pageImg = pdfDoc.render(0, renderSize);
        if (pageImg.isNull()) {
            setAnalyzing(false);
            m_lblStatus->setObjectName("statusErr");
            m_lblStatus->setText("Échec du rendu PDF.");
            m_lblStatus->style()->unpolish(m_lblStatus);
            m_lblStatus->style()->polish(m_lblStatus);
            return;
        }
        QBuffer buf(&imageData);
        buf.open(QIODevice::WriteOnly);
        pageImg.save(&buf, "JPEG", 85);
        mimeType = "image/jpeg";
        filename = QFileInfo(filePath).baseName() + "_p1.jpg";
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
    // Engine 1 (Tesseract) = gratuit. Engine 2/3 = PRO uniquement.
    const QByteArray engineParam = "1";

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
    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setProtocol(QSsl::TlsV1_2OrLater);
    request.setSslConfiguration(ssl);

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
        const int httpCode = reply->attribute(
            QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QByteArray body = reply->readAll();

        QString msg;
        if (httpCode == 401 || httpCode == 403) {
            msg = QString("⚠  Clé API invalide ou expirée (HTTP %1).\n"
                          "Cliquez sur 🔑 pour entrer votre clé gratuite : ocr.space/ocrapi/freekey")
                      .arg(httpCode);
        } else if (httpCode > 0) {
            msg = QString("⚠  Erreur HTTP %1 — %2").arg(httpCode).arg(QString::fromUtf8(body).left(120));
        } else {
            msg = "⚠  Pas de connexion au serveur OCR. Vérifiez votre réseau.";
        }
        m_lblStatus->setObjectName("statusErr");
        m_lblStatus->setText(msg);
        m_lblStatus->setWordWrap(true);
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
        if (!body.isEmpty()) m_txtRaw->setPlainText(QString::fromUtf8(body));
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
    for (const auto &kw : std::as_const(revenuKw)) {
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
    for (const auto &entry : std::as_const(catMap)) {
        for (const auto &kw : std::as_const(entry.kws)) {
            if (lower.contains(kw)) { result.category = entry.cat; break; }
        }
        if (!result.category.isEmpty()) break;
    }

    // ── 5. DESCRIPTION (première ligne significative) ─────────────────────────
    const QStringList lines = text.split('\n', Qt::SkipEmptyParts);
    for (const auto &line : std::as_const(lines)) {
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
void OcrScannerDialog::onConfigureApiKey()
{
    const QString current = m_settings.value("ocrApiKey", "K87415250588957").toString();
    bool ok = false;
    const QString key = QInputDialog::getText(
        this,
        "Clé API OCR.Space",
        "Entrez votre clé API gratuite\n(inscription sur ocr.space/ocrapi/freekey) :",
        QLineEdit::Normal,
        current,
        &ok);
    if (ok && !key.trimmed().isEmpty()) {
        m_settings.setValue("ocrApiKey", key.trimmed());
        m_lblStatus->setObjectName("statusOk");
        m_lblStatus->setText("✔  Clé API enregistrée. Vous pouvez relancer l'analyse.");
        m_lblStatus->style()->unpolish(m_lblStatus);
        m_lblStatus->style()->polish(m_lblStatus);
    }
}

void OcrScannerDialog::setAnalyzing(bool busy)
{
    m_btnAnalyze->setEnabled(!busy);
    m_btnBrowse->setEnabled(!busy);
    m_progress->setVisible(busy);
    m_btnAccept->setEnabled(false);
}
