#include "currencyconverter.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QDate>
#include <QLocale>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

// ════════════════════════════════════════════════════════════════════════
//  Données statiques
// ════════════════════════════════════════════════════════════════════════
static const QStringList CURRENCIES = {
    "EUR", "USD", "GBP", "JPY", "MAD", "SAR", "CHF", "CAD", "AED", "DZD"
};

static const QMap<QString,QString> CURRENCY_LABELS = {
    {"EUR","Euro"},{"USD","Dollar US"},{"GBP","Livre Sterling"},
    {"JPY","Yen Japonais"},{"MAD","Dirham Marocain"},{"SAR","Riyal Saoudien"},
    {"CHF","Franc Suisse"},{"CAD","Dollar Canadien"},{"AED","Dirham EAU"},
    {"DZD","Dinar Algérien"}
};

// ════════════════════════════════════════════════════════════════════════
//  Constructeur
// ════════════════════════════════════════════════════════════════════════
CurrencyConverterDialog::CurrencyConverterDialog(QWidget *parent)
    : QDialog(parent)
    , m_settings("SmartResearchLab", "CurrencyRates")
{
    setWindowTitle("💱  Converteur de Devises — Temps Réel");
    setFixedSize(560, 540);
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    m_nam = new QNetworkAccessManager(this);
    connect(m_nam, &QNetworkAccessManager::finished,
            this,  &CurrencyConverterDialog::onNetworkReply);

    buildUi();

    // Chargement initial EUR
    m_combo->setCurrentIndex(0);
    onCurrencyChanged(0);
}

// ════════════════════════════════════════════════════════════════════════
//  Construction de l'interface
// ════════════════════════════════════════════════════════════════════════
void CurrencyConverterDialog::buildUi()
{
    // ── Style global ─────────────────────────────────────────────────────
    setStyleSheet(R"(
        QDialog { background: #f7fafc; font-family: 'Segoe UI'; }

        QLabel#title {
            font-size: 16px; font-weight: 900; color: #0d5a5f;
            padding: 14px 0 6px 0;
        }
        QLabel#subtitle {
            font-size: 10px; color: #718096;
            padding-bottom: 8px;
        }
        QFrame#card {
            background: white;
            border: 1px solid #e2e8f0;
            border-radius: 14px;
        }
        QLabel#rateLabel {
            font-size: 22px; font-weight: 900; color: #1F8E95;
            padding: 6px 0;
        }
        QLabel#resultLabel {
            font-size: 18px; font-weight: 700; color: #27ae60;
        }
        QLabel#statusLabel { font-size: 9px; color: #a0aec0; }

        QComboBox {
            border: 1.5px solid #cbd5e0; border-radius: 8px;
            padding: 7px 12px; font-size: 12px;
            background: white;
        }
        QComboBox:focus { border-color: #1F8E95; }

        QLineEdit {
            border: 1.5px solid #cbd5e0; border-radius: 8px;
            padding: 8px 12px; font-size: 13px; background: white;
        }
        QLineEdit:focus { border-color: #1F8E95; }

        QPushButton#btnApply {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #1F8E95, stop:1 #27ae60);
            color: white; border: none; border-radius: 10px;
            font-size: 13px; font-weight: 800;
            padding: 12px 24px; min-height: 42px;
        }
        QPushButton#btnApply:hover { background: #17727a; }
        QPushButton#btnCancel {
            background: #edf2f7; color: #4a5568;
            border: none; border-radius: 10px;
            font-size: 12px; padding: 12px 24px; min-height: 42px;
        }
        QPushButton#btnCancel:hover { background: #e2e8f0; }
    )");

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(28, 18, 28, 22);
    root->setSpacing(16);

    // ── Titre ────────────────────────────────────────────────────────────
    auto *lblTitle = new QLabel("💱  Converteur de Devises en Temps Réel", this);
    lblTitle->setObjectName("title");
    lblTitle->setAlignment(Qt::AlignCenter);

    auto *lblSub = new QLabel("Taux récupérés automatiquement · Historique 7 jours · Résultat en DT", this);
    lblSub->setObjectName("subtitle");
    lblSub->setAlignment(Qt::AlignCenter);

    root->addWidget(lblTitle);
    root->addWidget(lblSub);

    // ── Carte principale ─────────────────────────────────────────────────
    auto *card = new QFrame(this);
    card->setObjectName("card");
    auto *grid = new QGridLayout(card);
    grid->setContentsMargins(24, 22, 24, 22);
    grid->setHorizontalSpacing(18);
    grid->setVerticalSpacing(16);

    // Ligne 0 : Sélecteur devise + taux actuel
    grid->addWidget(new QLabel("Devise source :"), 0, 0);

    m_combo = new QComboBox(this);
    for (const auto &c : CURRENCIES)
        m_combo->addItem(c + "  — " + CURRENCY_LABELS.value(c, c), c);
    m_combo->setFixedWidth(220);
    grid->addWidget(m_combo, 0, 1);

    m_lblRate = new QLabel("— DT", this);
    m_lblRate->setObjectName("rateLabel");
    m_lblRate->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(m_lblRate, 0, 2);

    // Ligne 1 : Montant à convertir + résultat
    grid->addWidget(new QLabel("Montant :"), 1, 0);

    m_editAmount = new QLineEdit(this);
    m_editAmount->setPlaceholderText("ex : 100.00");
    m_editAmount->setFixedWidth(220);
    grid->addWidget(m_editAmount, 1, 1);

    m_lblResult = new QLabel("→  — DT", this);
    m_lblResult->setObjectName("resultLabel");
    m_lblResult->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(m_lblResult, 1, 2);

    // Ligne 2 : Statut
    m_lblStatus = new QLabel("Récupération du taux en cours…", this);
    m_lblStatus->setObjectName("statusLabel");
    m_lblStatus->setAlignment(Qt::AlignCenter);
    grid->addWidget(m_lblStatus, 2, 0, 1, 3);

    root->addWidget(card);

    // ── Mini-graphe historique 7 jours ───────────────────────────────────
    m_chart = new QChartView(this);
    m_chart->setMinimumHeight(160);
    m_chart->setRenderHint(QPainter::Antialiasing);
    m_chart->setBackgroundBrush(QColor("#f7fafc"));
    root->addWidget(m_chart);

    // ── Boutons ──────────────────────────────────────────────────────────
    auto *btnRow = new QHBoxLayout();
    btnRow->setSpacing(12);

    auto *btnCancel = new QPushButton("Annuler", this);
    btnCancel->setObjectName("btnCancel");
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);

    m_btnApply = new QPushButton("✔  Appliquer ce montant", this);
    m_btnApply->setObjectName("btnApply");
    m_btnApply->setEnabled(false);
    connect(m_btnApply, &QPushButton::clicked, this, &QDialog::accept);

    btnRow->addWidget(btnCancel);
    btnRow->addWidget(m_btnApply, 1);
    root->addLayout(btnRow);

    // ── Signaux ──────────────────────────────────────────────────────────
    connect(m_combo,      QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CurrencyConverterDialog::onCurrencyChanged);
    connect(m_editAmount, &QLineEdit::textChanged,
            this, &CurrencyConverterDialog::onForeignAmountChanged);
}

// ════════════════════════════════════════════════════════════════════════
//  Slots
// ════════════════════════════════════════════════════════════════════════
void CurrencyConverterDialog::onCurrencyChanged(int index)
{
    m_currency = m_combo->itemData(index).toString();
    m_rate     = 0.0;
    m_lblRate->setText("Chargement…");
    m_lblStatus->setText("Récupération du taux en cours…");
    m_btnApply->setEnabled(false);
    refreshChart(m_currency);
    fetchRate(m_currency);
}

void CurrencyConverterDialog::onForeignAmountChanged(const QString &text)
{
    updateConversionDisplay();
}

void CurrencyConverterDialog::onNetworkReply(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        m_lblStatus->setText("⚠  Erreur réseau : " + reply->errorString());
        // Essayer de charger le dernier taux stocké
        const auto hist = loadHistory(m_currency);
        if (!hist.isEmpty()) {
            m_rate = hist.last().second;
            const QString stored = QString("1 %1 = %2 DT  (taux stocké)")
                                       .arg(m_currency)
                                       .arg(QLocale(QLocale::French).toString(m_rate,'f',4));
            m_lblRate->setText(stored);
            updateConversionDisplay();
        }
        return;
    }

    const QByteArray  data = reply->readAll();
    const QJsonObject json = QJsonDocument::fromJson(data).object();

    // Format open.er-api.com : {"result":"success","rates":{"TND":3.38,...}}
    if (json.value("result").toString() != "success") {
        m_lblStatus->setText("⚠  Réponse inattendue de l'API.");
        return;
    }

    const double rate = json["rates"].toObject()["TND"].toDouble();
    if (rate <= 0.0) {
        m_lblStatus->setText("⚠  TND non disponible dans la réponse.");
        return;
    }

    m_rate = rate;
    storeRate(m_currency, rate);
    refreshChart(m_currency);

    m_lblRate->setText(QString("1 %1  =  %2 DT")
                           .arg(m_currency)
                           .arg(QLocale(QLocale::French).toString(rate,'f',4)));
    m_lblStatus->setText(QString("✔  Taux mis à jour le %1 via open.er-api.com")
                             .arg(QDate::currentDate().toString("dd/MM/yyyy")));
    updateConversionDisplay();
}

// ════════════════════════════════════════════════════════════════════════
//  Logique interne
// ════════════════════════════════════════════════════════════════════════
void CurrencyConverterDialog::fetchRate(const QString &currency)
{
    // API gratuite, sans clé : open.er-api.com
    const QUrl url("https://open.er-api.com/v6/latest/" + currency);
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::UserAgentHeader, "SmartResearchLab-Finance/1.0");
    m_nam->get(req);
}

void CurrencyConverterDialog::updateConversionDisplay()
{
    if (m_rate <= 0.0) return;

    bool ok = false;
    const double foreign = m_editAmount->text().replace(',', '.').toDouble(&ok);

    if (!ok || foreign <= 0.0) {
        m_lblResult->setText("→  — DT");
        m_convertedDT = 0.0;
        m_btnApply->setEnabled(false);
        return;
    }

    m_convertedDT = foreign * m_rate;
    const QLocale fr(QLocale::French);
    m_lblResult->setText(QString("→  %1 DT")
                             .arg(fr.toString(m_convertedDT, 'f', 3)));
    m_btnApply->setEnabled(true);
}

void CurrencyConverterDialog::refreshChart(const QString &currency)
{
    const auto history = loadHistory(currency);

    auto *series = new QLineSeries();
    series->setName("Taux vs TND");
    series->setColor(QColor("#1F8E95"));

    QPen pen(QColor("#1F8E95"));
    pen.setWidth(2);
    series->setPen(pen);

    // Points de l'historique (x = index, y = taux)
    for (int i = 0; i < history.size(); ++i)
        series->append(i, history[i].second);

    // Si un seul point → ajouter un second identique pour tracer une ligne
    if (history.size() == 1)
        series->append(1, history[0].second);

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(currency + " → TND  (7 derniers jours)");
    chart->setTitleFont(QFont("Segoe UI", 9, QFont::Bold));
    chart->setTitleBrush(QColor("#2d3748"));
    chart->setBackgroundBrush(QColor("#f7fafc"));
    chart->setMargins(QMargins(4, 4, 4, 4));
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto *axX = new QValueAxis();
    axX->setRange(0, qMax(6, history.size() - 1));
    axX->setTickCount(qMin(7, history.size() + 1));
    axX->setLabelFormat("%d");
    axX->setLabelsFont(QFont("Segoe UI", 7));
    axX->setTitleText("Jours");
    axX->setTitleFont(QFont("Segoe UI", 8));
    axX->setGridLineColor(QColor("#e2e8f0"));

    auto *axY = new QValueAxis();
    axY->setLabelsFont(QFont("Segoe UI", 7));
    axY->setTitleText("DT");
    axY->setTitleFont(QFont("Segoe UI", 8));
    axY->setGridLineColor(QColor("#e2e8f0"));
    if (!history.isEmpty()) {
        double mn = history[0].second, mx = mn;
        for (auto &h : history) { mn = qMin(mn,h.second); mx = qMax(mx,h.second); }
        const double margin = qMax(0.01, (mx - mn) * 0.2);
        axY->setRange(mn - margin, mx + margin);
    }

    chart->addAxis(axX, Qt::AlignBottom);
    chart->addAxis(axY, Qt::AlignLeft);
    series->attachAxis(axX);
    series->attachAxis(axY);

    m_chart->setChart(chart);
}

void CurrencyConverterDialog::storeRate(const QString &currency, double rate)
{
    const QString key  = "history/" + currency;
    const QString today = QDate::currentDate().toString("yyyy-MM-dd");

    // Charger l'historique existant
    QStringList stored = m_settings.value(key).toStringList();

    // Vérifier si le taux d'aujourd'hui est déjà enregistré
    bool alreadyToday = false;
    for (const auto &s : stored) {
        if (s.startsWith(today)) { alreadyToday = true; break; }
    }
    if (!alreadyToday)
        stored.append(today + ":" + QString::number(rate, 'f', 6));

    // Garder max 7 entrées
    while (stored.size() > 7) stored.removeFirst();
    m_settings.setValue(key, stored);
}

QList<QPair<QString,double>> CurrencyConverterDialog::loadHistory(const QString &currency)
{
    const QStringList stored = m_settings.value("history/" + currency).toStringList();
    QList<QPair<QString,double>> result;
    for (const auto &s : stored) {
        const QStringList parts = s.split(':');
        if (parts.size() == 2) {
            bool ok = false;
            const double v = parts[1].toDouble(&ok);
            if (ok) result.append({parts[0], v});
        }
    }
    return result;
}
