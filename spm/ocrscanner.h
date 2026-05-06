#ifndef OCRSCANNER_H
#define OCRSCANNER_H

#include <QDialog>
#include <QDate>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QProgressBar>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>

// ─── Résultat d'une analyse OCR ─────────────────────────────────────────────
struct OcrResult {
    double  amount    = 0.0;
    QDate   date;
    QString type;        // "Depense" | "Revenu" | ""
    QString category;
    QString description;
    QString rawText;
    bool    hasAmount = false;
    bool    hasDate   = false;
    bool    success   = false;
};

// ─── Dialogue Scanner OCR ────────────────────────────────────────────────────
class OcrScannerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OcrScannerDialog(QWidget *parent = nullptr);
    OcrResult result() const { return m_result; }

private slots:
    void onBrowse();
    void onAnalyze();
    void onNetworkReply(QNetworkReply *reply);
    void onConfigureApiKey();

private:
    void buildUi();
    void sendOcrRequest(const QString &filePath);
    OcrResult parseReceiptText(const QString &text);
    void displayResult(const OcrResult &r);
    void setAnalyzing(bool busy);

    // ── Widgets ──────────────────────────────────────────────────────────────
    QLabel       *m_lblPreview  = nullptr;
    QLabel       *m_lblStatus   = nullptr;
    QLineEdit    *m_editPath    = nullptr;
    QPushButton  *m_btnBrowse   = nullptr;
    QPushButton  *m_btnAnalyze  = nullptr;
    QPushButton  *m_btnAccept   = nullptr;
    QTextEdit    *m_txtRaw      = nullptr;
    QComboBox    *m_comboLang   = nullptr;
    QLabel       *m_lblAmount   = nullptr;
    QLabel       *m_lblDate     = nullptr;
    QLabel       *m_lblType     = nullptr;
    QLabel       *m_lblCat      = nullptr;
    QProgressBar *m_progress    = nullptr;

    // ── Réseau ───────────────────────────────────────────────────────────────
    QNetworkAccessManager *m_nam = nullptr;

    // ── État ─────────────────────────────────────────────────────────────────
    OcrResult m_result;
    QSettings m_settings;
};

#endif // OCRSCANNER_H
