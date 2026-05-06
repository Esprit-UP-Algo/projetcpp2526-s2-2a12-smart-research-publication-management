#include "labsexporter.h"

#include <QPdfWriter>
#include <QPainter>
#include <QPageLayout>
#include <QPageSize>
#include <QUrl>
#include <QDir>
#include <QDateTime>
#include <QFont>
#include <QColor>
#include <QRect>
#include <QPen>
#include <QRegularExpression>

// ── Constructeur ──────────────────────────────────────────────────────────────
LabsExporter::LabsExporter(QObject *parent)
    : QObject(parent)
{}

// ── Point d'entrée public ─────────────────────────────────────────────────────
QString LabsExporter::exportToPdf(const LabData &data, const QString &outputFolder)
{
    if (data.nomLabo.trimmed().isEmpty())
        return {};

    // Dossier de destination
    QDir().mkpath(outputFolder);
    const QString nomSafe = QString(data.nomLabo)
                                .replace(QRegularExpression("[^a-zA-Z0-9_-]"), "_")
                                .left(30);
    const QString fileName = outputFolder + "/" + nomSafe + "_"
                             + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")
                             + ".pdf";

    // Initialisation du writer PDF
    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    writer.setResolution(96);

    QPainter p(&writer);
    if (!p.isActive())
        return {};

    renderPage(p, writer.pageLayout().paintRectPixels(96).width(), data);
    p.end();

    return fileName;
}

// ── Rendu PDF ─────────────────────────────────────────────────────────────────
void LabsExporter::renderPage(QPainter &p, int W,
                              const LabData &data) const
{
    int y = 0;

    // ── Helpers locaux ────────────────────────────────────────────────────────
    auto hline = [&](int yy, const QColor &c = QColor(210, 210, 210)) {
        p.setPen(QPen(c, 1));
        p.drawLine(0, yy, W, yy);
    };

    auto sectionHeader = [&](const QString &title) {
        p.fillRect(0, y, W, 24, QColor(240, 242, 255));
        p.setFont(QFont("Segoe UI", 10, QFont::Bold));
        p.setPen(QColor(25, 35, 126));
        p.drawText(QRect(6, y, W, 24), Qt::AlignVCenter, "  " + title);
        y += 24;
        hline(y, QColor(25, 35, 126));
        y += 6;
    };

    auto field = [&](const QString &label, const QString &value,
                     const QColor &valueColor = Qt::black) {
        const int rowH = 28;
        p.setFont(QFont("Segoe UI", 9, QFont::Bold));
        p.setPen(QColor(80, 80, 80));
        p.drawText(QRect(0, y, 180, rowH), Qt::AlignVCenter | Qt::AlignLeft, label);
        p.setFont(QFont("Segoe UI", 9));
        p.setPen(valueColor);
        p.drawText(QRect(185, y, W - 185, rowH), Qt::AlignVCenter | Qt::AlignLeft, value);
        y += rowH;
        hline(y - 1, QColor(230, 230, 230));
    };

    // ── Bandeau titre ─────────────────────────────────────────────────────────
    p.fillRect(0, y, W, 60, QColor(25, 35, 126));
    p.setFont(QFont("Segoe UI", 16, QFont::Bold));
    p.setPen(Qt::white);
    p.drawText(QRect(0, y, W, 60), Qt::AlignCenter, "FICHE LABORATOIRE");
    y += 60;

    // Sous-titre date
    p.setFont(QFont("Segoe UI", 8));
    p.setPen(QColor(120, 120, 120));
    p.drawText(QRect(0, y + 4, W, 18), Qt::AlignRight,
               "Exporté le " + QDateTime::currentDateTime().toString("dd/MM/yyyy  HH:mm"));
    y += 26;

    // ── Section informations générales ────────────────────────────────────────
    sectionHeader("Informations générales");
    field("Nom du laboratoire",  data.nomLabo);
    field("Responsable",         data.responsable);
    field("Téléphone",           data.telephone);
    field("Localisation / GPS",  data.localisation);
    field("Disponibilité",       data.disponibilite);
    y += 8;

    // ── Section informations financières ──────────────────────────────────────
    sectionHeader("Informations financières");
    field("Statut paiement",  data.paiement);
    field("Montant total",    data.montant     + " DT");
    field("Montant payé",     data.montantPaye + " DT");

    // Reste à payer coloré
    const double resteVal   = data.reste.toDouble();
    const QColor resteColor = (resteVal > 0) ? QColor(200, 0, 0) : QColor(0, 140, 0);
    const QString resteText = data.reste + " DT"
                              + (resteVal <= 0 ? "  ✓ Soldé" : "");
    {
        const int rowH = 28;
        p.setFont(QFont("Segoe UI", 9, QFont::Bold));
        p.setPen(QColor(80, 80, 80));
        p.drawText(QRect(0, y, 180, rowH), Qt::AlignVCenter | Qt::AlignLeft, "Reste à payer");
        p.setFont(QFont("Segoe UI", 9, QFont::Bold));
        p.setPen(resteColor);
        p.drawText(QRect(185, y, W - 185, rowH), Qt::AlignVCenter | Qt::AlignLeft, resteText);
        y += rowH;
        hline(y - 1, QColor(230, 230, 230));
    }
    y += 16;

    // ── Footer ────────────────────────────────────────────────────────────────
    p.fillRect(0, y, W, 30, QColor(245, 245, 245));
    p.setFont(QFont("Segoe UI", 8));
    p.setPen(QColor(130, 130, 130));
    p.drawText(QRect(0, y, W, 30), Qt::AlignCenter | Qt::AlignVCenter,
               "Document généré par SmartResearchLab  —  "
                   + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"));
}
