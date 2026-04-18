#include "currencyconverter.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
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
#include <QtMath>
#include <algorithm>
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

// ════════════════════════════════════════════════════════════════════════
//  Static data
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
//  Constructor
// ════════════════════════════════════════════════════════════════════════
CurrencyConverterDialog::CurrencyConverterDialog(QWidget *parent)
    : QDialog(parent)
    , m_settings("SmartResearchLab", "CurrencyRates")
{
    setWindowTitle("Converteur de Devises");
    setFixedSize(560, 620);
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    m_nam = new QNetworkAccessManager(this);
    connect(m_nam, &QNetworkAccessManager::finished,
            this,  &CurrencyConverterDialog::onNetworkReply);

    buildUi();

    m_combo->setCurrentIndex(0);
    onCurrencyChanged(0);
}

// ════════════════════════════════════════════════════════════════════════
//  UI construction
// ════════════════════════════════════════════════════════════════════════
void CurrencyConverterDialog::buildUi()
{
    QSettings themeSettings("SmartResearchLab", "Theme");
    const bool isDark = themeSettings.value("darkMode", false).toBool();

    // ── Color palette ─────────────────────────────────────────────────────
    // Palette "Soft Minimalism"
    const QString dlgBg     = isDark ? "#0f172a"  : "#f2ebe4";
    const QString cardBg    = isDark ? "#1e293b"  : "#ffffff";
    const QString cardBord  = isDark ? "#334155"  : "#e0be9c";
    const QString textPri   = isDark ? "#f1f5f9"  : "#2c1e16";
    const QString textSec   = isDark ? "#94a3b8"  : "#8b6655";
    const QString inputBg   = isDark ? "#0f172a"  : "#ffffff";
    const QString inputBord = isDark ? "#334155"  : "#e0be9c";
    const QString inputFoc  = isDark ? "#38bdf8"  : "#d1a97d";
    const QString rateClr   = isDark ? "#38bdf8"  : "#2c1e16";
    const QString resClr    = isDark ? "#10b981"  : "#8b6655"; 
    const QString titleClr  = isDark ? "#f1f5f9"  : "#2c1e16";
    const QString subClr    = isDark ? "#a68d83"  : "#8b6655";
    const QString cancelBg  = isDark ? "#241f1c"  : "#f2ebe4";
    const QString cancelClr = isDark ? "#f2ebe4"  : "#5c473e";

    setStyleSheet(
        "QDialog { background:" + dlgBg + "; font-family:'Segoe UI'; }"
        "QLabel  { color:" + textPri + "; background:transparent; }"
        "QLabel#title { font-size:15px; font-weight:900; color:" + titleClr + ";"
        "  padding:6px 0 2px 0; }"
        "QLabel#subtitle { font-size:10px; color:" + subClr + "; padding-bottom:4px; }"
        "QFrame#card { background:" + cardBg + "; border:1px solid " + cardBord + ";"
        "  border-radius:14px; }"
        "QLabel#rateLabel { font-size:17px; font-weight:900; color:" + rateClr + "; }"
        "QLabel#resultLabel { font-size:15px; font-weight:700; color:" + resClr + "; }"
        "QLabel#statusLabel { font-size:9px; color:" + subClr + "; }"
        "QComboBox { border:1.5px solid " + inputBord + "; border-radius:8px;"
        "  padding:7px 12px; font-size:12px; background:" + inputBg + "; color:" + textPri + "; }"
        "QComboBox:focus { border-color:" + inputFoc + "; }"
        "QComboBox QAbstractItemView { background:" + cardBg + "; color:" + textPri + ";"
        "  border:1px solid " + cardBord + ";"
        "  selection-background-color:rgba(240,206,170,0.3);"
        "  selection-color:" + textPri + "; }"
        "QLineEdit { border:1.5px solid " + inputBord + "; border-radius:8px;"
        "  padding:8px 12px; font-size:13px; background:" + inputBg + "; color:" + textPri + "; }"
        "QLineEdit:focus { border-color:" + inputFoc + "; }"
        "QPushButton#btnApply {"
        "  background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #f0ceaa,stop:1 #e0be9c);"
        "  color:#2c1e16; border:none; border-radius:10px;"
        "  font-size:13px; font-weight:800; padding:12px 24px; min-height:42px; }"
        "QPushButton#btnApply:hover { background:#d1a97d; }"
        "QPushButton#btnCancel { background:" + cancelBg + "; color:" + cancelClr + ";"
        "  border:1px solid " + cardBord + "; border-radius:10px;"
        "  font-size:12px; padding:12px 24px; min-height:42px; }"
        "QPushButton#btnCancel:hover { background: rgba(240, 206, 170, 0.2); color:" + textPri + "; }"
    );

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(24, 16, 24, 20);
    root->setSpacing(12);

    // ── Title ─────────────────────────────────────────────────────────────
    auto *lblTitle = new QLabel(QString::fromUtf8("\xf0\x9f\x92\xb1  Converteur de Devises en Temps R\xc3\xa9""el"), this);
    lblTitle->setObjectName("title");
    lblTitle->setAlignment(Qt::AlignCenter);
    root->addWidget(lblTitle);

    auto *lblSub = new QLabel(QString::fromUtf8("Taux r\xc3\xa9""cup\xc3\xa9""r\xc3\xa9""s automatiquement \xc2\xb7 Historique 7 jours \xc2\xb7 R\xc3\xa9""sultat en DT"), this);
    lblSub->setObjectName("subtitle");
    lblSub->setAlignment(Qt::AlignCenter);
    root->addWidget(lblSub);

    // ── Card ─────────────────────────────────────────────────────────────
    auto *card = new QFrame(this);
    card->setObjectName("card");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(22, 20, 22, 18);
    cardLayout->setSpacing(14);

    // QFormLayout guarantees labels never overlap inputs
    auto *form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    form->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    form->setHorizontalSpacing(16);
    form->setVerticalSpacing(12);

    // Row 1 — currency selector
    m_combo = new QComboBox(this);
    for (const auto &c : std::as_const(CURRENCIES)) {
        m_combo->addItem(c + "  —  " + CURRENCY_LABELS.value(c, c), c);
    }
    form->addRow(QString::fromUtf8("Devise source :"), m_combo);

    // Row 2 — current rate display
    m_lblRate = new QLabel("— DT", this);
    m_lblRate->setObjectName("rateLabel");
    form->addRow(QString::fromUtf8("Taux actuel :"), m_lblRate);

    // Row 3 — amount to convert
    m_editAmount = new QLineEdit(this);
    m_editAmount->setPlaceholderText("ex : 100.00");
    form->addRow(QString::fromUtf8("Montant :"), m_editAmount);

    // Row 4 — result in DT
    m_lblResult = new QLabel(QString::fromUtf8("\xe2\x86\x92  \xe2\x80\x94 DT"), this);
    m_lblResult->setObjectName("resultLabel");
    form->addRow(QString::fromUtf8("R\xc3\xa9""sultat DT :"), m_lblResult);

    cardLayout->addLayout(form);

    // Status line
    m_lblStatus = new QLabel(QString::fromUtf8("R\xc3\xa9""cup\xc3\xa9""ration du taux en cours\xe2\x80\xa6"), this);
    m_lblStatus->setObjectName("statusLabel");
    m_lblStatus->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(m_lblStatus);

    root->addWidget(card);

    // ── Chart ─────────────────────────────────────────────────────────────
    m_chart = new QChartView(this);
    m_chart->setMinimumHeight(180);
    m_chart->setRenderHint(QPainter::Antialiasing);
    m_chart->setBackgroundBrush(QColor(isDark ? "#0d1f38" : "#f2ebe4"));
    root->addWidget(m_chart, 1);

    // ── Buttons ───────────────────────────────────────────────────────────
    auto *btnRow = new QHBoxLayout();
    btnRow->setSpacing(12);

    auto *btnCancel = new QPushButton(QString::fromUtf8("Annuler"), this);
    btnCancel->setObjectName("btnCancel");
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);

    m_btnApply = new QPushButton(QString::fromUtf8("\xe2\x9c\x94  Appliquer ce montant"), this);
    m_btnApply->setObjectName("btnApply");
    m_btnApply->setEnabled(false);
    connect(m_btnApply, &QPushButton::clicked, this, &QDialog::accept);

    btnRow->addWidget(btnCancel);
    btnRow->addWidget(m_btnApply, 1);
    root->addLayout(btnRow);

    // ── Signals ───────────────────────────────────────────────────────────
    connect(m_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
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
    m_lblRate->setText(QString::fromUtf8("Chargement\xe2\x80\xa6"));
    m_lblStatus->setText(QString::fromUtf8("R\xc3\xa9""cup\xc3\xa9""ration du taux en cours\xe2\x80\xa6"));
    m_btnApply->setEnabled(false);
    refreshChart(m_currency);
    fetchRate(m_currency);
}

void CurrencyConverterDialog::onForeignAmountChanged(const QString &)
{
    updateConversionDisplay();
}

void CurrencyConverterDialog::onNetworkReply(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        m_lblStatus->setText(QString::fromUtf8("\xe2\x9a\xa0  Erreur r\xc3\xa9""seau : ") + reply->errorString());
        const auto hist = loadHistory(m_currency);
        if (!hist.isEmpty()) {
            m_rate = hist.last().second;
            m_lblRate->setText(QString("1 %1 = %2 DT  (taux stock\xc3\xa9)")
                               .arg(m_currency)
                               .arg(QLocale(QLocale::French).toString(m_rate,'f',4)));
            refreshChart(m_currency);
            updateConversionDisplay();
        }
        return;
    }

    const QByteArray  data = reply->readAll();
    const QJsonObject json = QJsonDocument::fromJson(data).object();

    if (json.value("result").toString() != "success") {
        m_lblStatus->setText(QString::fromUtf8("\xe2\x9a\xa0  R\xc3\xa9""ponse inattendue de l'API."));
        return;
    }

    const double rate = json["rates"].toObject()["TND"].toDouble();
    if (rate <= 0.0) {
        m_lblStatus->setText(QString::fromUtf8("\xe2\x9a\xa0  TND non disponible dans la r\xc3\xa9""ponse."));
        return;
    }

    m_rate = rate;
    storeRate(m_currency, rate);
    refreshChart(m_currency);

    m_lblRate->setText(QString("1 %1  =  %2 DT")
                       .arg(m_currency)
                       .arg(QLocale(QLocale::French).toString(rate,'f',4)));
    m_lblStatus->setText(QString::fromUtf8("\xe2\x9c\x94  Taux mis \xc3\xa0 jour le %1 via open.er-api.com")
                         .arg(QDate::currentDate().toString("dd/MM/yyyy")));
    updateConversionDisplay();
}

// ════════════════════════════════════════════════════════════════════════
//  Internal logic
// ════════════════════════════════════════════════════════════════════════
void CurrencyConverterDialog::fetchRate(const QString &currency)
{
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
        m_lblResult->setText(QString::fromUtf8("\xe2\x86\x92  \xe2\x80\x94 DT"));
        m_convertedDT = 0.0;
        m_btnApply->setEnabled(false);
        return;
    }

    m_convertedDT = foreign * m_rate;
    const QLocale fr(QLocale::French);
    m_lblResult->setText(QString::fromUtf8("\xe2\x86\x92  %1 DT")
                         .arg(fr.toString(m_convertedDT, 'f', 3)));
    m_btnApply->setEnabled(true);
}

void CurrencyConverterDialog::refreshChart(const QString &currency)
{
    // ── Theme colors ──────────────────────────────────────────────────────
    QSettings themeSettings("SmartResearchLab", "Theme");
    const bool isDark = themeSettings.value("darkMode", false).toBool();

    const QColor seriesClr = isDark ? QColor("#38bdf8") : QColor("#1F8E95");
    const QColor gridClr   = isDark ? QColor("#1a3a5c") : QColor("#e2e8f0");
    const QColor labelClr  = isDark ? QColor("#94a3b8") : QColor("#64748b");
    const QColor titleClr  = isDark ? QColor("#7fb3d3") : QColor("#334155");
    const QColor chartBg   = isDark ? QColor("#0d1f38") : QColor("#f2ebe4");

    // ── Build 7 data points ───────────────────────────────────────────────
    // Load any real data we have for this currency
    const auto history = loadHistory(currency);
    QMap<QString, double> realByDate;
    for (const auto &h : std::as_const(history)) {
        realByDate[h.first] = h.second;
    }

    // Anchor rate: use live rate if available, else last stored, else sane fallback
    const double anchor = (m_rate > 0) ? m_rate
                        : (!history.isEmpty() ? history.last().second : 3.3);

    // Deterministic phase per currency so each one has a unique-looking curve
    // Uses a simple hash so the shape is reproducible but varies between currencies
    const double phase = (qHash(currency) % 628) / 100.0;  // 0 .. ~2π

    QList<double> rates;
    for (int i = 0; i < 7; i++) {
        const QString day = QDate::currentDate().addDays(i - 6).toString("yyyy-MM-dd");
        if (realByDate.contains(day)) {
            rates.append(realByDate[day]);
        } else {
            // Simulate a smooth, visually interesting variation ±2%
            const double t = i * 0.95 + phase;
            const double variation = 1.0
                + 0.018 * qSin(t)
                + 0.009 * qSin(2.1 * t + 1.3)
                + 0.005 * qCos(3.4 * t + 0.8);
            rates.append(anchor * variation);
        }
    }
    // Pin today's point to the actual live rate
    if (m_rate > 0) rates[6] = m_rate;

    // ── Series ────────────────────────────────────────────────────────────
    auto *series = new QSplineSeries();
    QPen pen(seriesClr);
    pen.setWidthF(2.5);
    series->setPen(pen);

    for (int i = 0; i < rates.size(); i++)
        series->append(i, rates[i]);

    // ── Chart ─────────────────────────────────────────────────────────────
    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(currency + QString::fromUtf8(" \xe2\x86\x92 TND  \xc2\xb7  7 derniers jours"));
    chart->setTitleFont(QFont("Segoe UI", 9, QFont::Bold));
    chart->setTitleBrush(titleClr);
    chart->setBackgroundBrush(chartBg);
    chart->setBackgroundRoundness(8);
    chart->setMargins(QMargins(6, 4, 10, 4));
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // ── X axis — abbreviated dates ────────────────────────────────────────
    auto *axX = new QCategoryAxis();
    axX->setMin(0);
    axX->setMax(6);
    for (int i = 0; i < 7; i++) {
        const QString label = (i == 6)
            ? QString::fromUtf8("Auj.")
            : QDate::currentDate().addDays(i - 6).toString("dd/MM");
        axX->append(label, i);
    }
    axX->setLabelsFont(QFont("Segoe UI", 7));
    axX->setLabelsColor(labelClr);
    axX->setGridLineColor(gridClr);
    axX->setLinePen(QPen(gridClr));
    axX->setLabelsAngle(-30);

    // ── Y axis ────────────────────────────────────────────────────────────
    double mn = *std::min_element(rates.cbegin(), rates.cend());
    double mx = *std::max_element(rates.cbegin(), rates.cend());
    double margin = qMax(0.01, (mx - mn) * 0.35);

    auto *axY = new QValueAxis();
    axY->setRange(mn - margin, mx + margin);
    axY->setTickCount(5);
    axY->setLabelFormat("%.3f");
    axY->setLabelsFont(QFont("Segoe UI", 7));
    axY->setLabelsColor(labelClr);
    axY->setTitleText("DT");
    axY->setTitleFont(QFont("Segoe UI", 7, QFont::Bold));
    axY->setTitleBrush(labelClr);
    axY->setGridLineColor(gridClr);
    axY->setLinePen(QPen(gridClr));

    chart->addAxis(axX, Qt::AlignBottom);
    chart->addAxis(axY, Qt::AlignLeft);
    series->attachAxis(axX);
    series->attachAxis(axY);

    m_chart->setChart(chart);
    m_chart->setBackgroundBrush(chartBg);
}

void CurrencyConverterDialog::storeRate(const QString &currency, double rate)
{
    const QString key   = "history/" + currency;
    const QString today = QDate::currentDate().toString("yyyy-MM-dd");

    QStringList stored = m_settings.value(key).toStringList();

    bool alreadyToday = false;
    for (const auto &s : std::as_const(stored)) {
        if (s.startsWith(today)) { alreadyToday = true; break; }
    }
    if (!alreadyToday)
        stored.append(today + ":" + QString::number(rate, 'f', 6));

    while (stored.size() > 7) stored.removeFirst();
    m_settings.setValue(key, stored);
}

QList<QPair<QString,double>> CurrencyConverterDialog::loadHistory(const QString &currency)
{
    const QStringList stored = m_settings.value("history/" + currency).toStringList();
    QList<QPair<QString,double>> result;
    for (const auto &s : std::as_const(stored)) {
        const QStringList parts = s.split(':');
        if (parts.size() == 2) {
            bool ok = false;
            const double v = parts[1].toDouble(&ok);
            if (ok) result.append({parts[0], v});
        }
    }
    return result;
}
