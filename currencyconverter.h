#ifndef CURRENCYCONVERTER_H
#define CURRENCYCONVERTER_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

class QComboBox;
class QLineEdit;
class QLabel;
class QPushButton;

/**
 * Dialog de conversion de devises en temps réel.
 * API gratuite (sans clé) : open.er-api.com
 * Historique 7 jours stocké localement via QSettings.
 */
class CurrencyConverterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CurrencyConverterDialog(QWidget *parent = nullptr);

    /** Retourne le montant converti en DT après que l'utilisateur clique "Appliquer". */
    double convertedAmountDT() const { return m_convertedDT; }

private slots:
    void onCurrencyChanged(int index);
    void onForeignAmountChanged(const QString &text);
    void onNetworkReply(QNetworkReply *reply);

private:
    void buildUi();
    void fetchRate(const QString &currency);
    void updateConversionDisplay();
    void refreshChart(const QString &currency);
    void storeRate(const QString &currency, double rate);
    QList<QPair<QString,double>> loadHistory(const QString &currency);

    // ── Widgets ──────────────────────────────────────────
    QComboBox  *m_combo      = nullptr;
    QLineEdit  *m_editAmount = nullptr;
    QLabel     *m_lblRate    = nullptr;
    QLabel     *m_lblResult  = nullptr;
    QLabel     *m_lblStatus  = nullptr;
    QChartView *m_chart      = nullptr;
    QPushButton *m_btnApply  = nullptr;

    // ── Réseau ───────────────────────────────────────────
    QNetworkAccessManager *m_nam = nullptr;

    // ── État ─────────────────────────────────────────────
    double  m_rate        = 0.0;
    double  m_convertedDT = 0.0;
    QString m_currency;

    // ── Persistance (historique local) ───────────────────
    QSettings m_settings;
};

#endif // CURRENCYCONVERTER_H
