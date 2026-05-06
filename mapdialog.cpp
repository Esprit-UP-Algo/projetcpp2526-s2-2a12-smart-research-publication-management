#include "mapdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>

MapDialog::MapDialog(Mode mode, const QString &location, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(mode == ViewMode
                       ? "Localisation du laboratoire"
                       : "Sélectionner une position sur la carte");
    resize(900, 640);
    setMinimumSize(600, 450);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ── Carte ──────────────────────────────────────────────────────────────────
    const TileMapWidget::Mode mapMode =
        (mode == PickMode) ? TileMapWidget::PickMode : TileMapWidget::ViewMode;
    m_map = new TileMapWidget(mapMode, this);
    m_map->setCenter(36.8065, 10.1815, 6);   // Vue initiale : Tunisie
    mainLayout->addWidget(m_map, 1);

    if (mode == PickMode) {
        // ── Barre inférieure (PickMode) ─────────────────────────────────────
        auto *bar = new QFrame(this);
        bar->setFixedHeight(58);
        bar->setStyleSheet("background:#1a237e;");

        auto *barLayout = new QHBoxLayout(bar);
        barLayout->setContentsMargins(14, 0, 14, 0);
        barLayout->setSpacing(10);

        auto *pinIcon = new QLabel("\U0001F4CD", bar);
        pinIcon->setStyleSheet("color:white;font-size:18px;background:transparent;");
        barLayout->addWidget(pinIcon);

        m_coordsLabel = new QLabel("Cliquez sur la carte pour sélectionner une position…", bar);
        m_coordsLabel->setStyleSheet("color:#b0bec5;font-size:13px;background:transparent;");
        barLayout->addWidget(m_coordsLabel, 1);

        m_btnConfirm = new QPushButton("Confirmer", bar);
        m_btnConfirm->setEnabled(false);
        m_btnConfirm->setFixedSize(120, 36);
        m_btnConfirm->setStyleSheet(
            "QPushButton { background:#43a047; color:white; border:none;"
            "              border-radius:5px; font-size:14px; }"
            "QPushButton:hover:!disabled { background:#2e7d32; }"
            "QPushButton:disabled { background:#607d8b; color:#b0bec5; }");
        barLayout->addWidget(m_btnConfirm);

        mainLayout->addWidget(bar);

        // Clic sur la carte → mise à jour des coordonnées dans la barre
        connect(m_map, &TileMapWidget::markerPlaced, this, [this](double lat, double lng) {
            m_coordsLabel->setText(QString("\U0001F4CC  %1,  %2")
                                       .arg(lat, 0, 'f', 6)
                                       .arg(lng, 0, 'f', 6));
            m_coordsLabel->setStyleSheet(
                "color:white;font-size:13px;font-weight:bold;background:transparent;");
            m_btnConfirm->setEnabled(true);
        });

        // Bouton Confirmer → émet le signal et ferme le dialog
        connect(m_btnConfirm, &QPushButton::clicked, this, [this]() {
            if (m_map->hasSelection()) {
                emit coordinatesSelected(m_map->selectedCoords());
                accept();
            }
        });

    } else {
        // ── ViewMode : centrer sur la localisation ──────────────────────────
        if (!location.isEmpty()) {
            // Tenter de parser "lat, lng"
            const QStringList parts = location.split(QLatin1Char(','));
            if (parts.size() == 2) {
                bool okLat, okLng;
                const double lat = parts[0].trimmed().toDouble(&okLat);
                const double lng = parts[1].trimmed().toDouble(&okLng);
                if (okLat && okLng) {
                    m_map->setCenter(lat, lng, 15);
                    m_map->setMarker(lat, lng);
                    return;   // coordonnées directes, pas besoin de géocodage
                }
            }
            geocodeAndCenter(location);
        }
    }
}

// ── Géocodage via Nominatim (pour texte libre en ViewMode) ───────────────────
void MapDialog::geocodeAndCenter(const QString &location)
{
    if (!m_nam) m_nam = new QNetworkAccessManager(this);

    const QUrl url(
        QString("https://nominatim.openstreetmap.org/search?q=%1&format=json&limit=1")
            .arg(QString::fromUtf8(QUrl::toPercentEncoding(location))));

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::UserAgentHeader, "SRPM-Qt-App/1.0 (lab-management)");

    QNetworkReply *reply = m_nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply, location]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) return;

        const QJsonArray arr = QJsonDocument::fromJson(reply->readAll()).array();
        if (arr.isEmpty()) return;

        const QJsonObject obj = arr.first().toObject();
        const double lat = obj.value("lat").toString().toDouble();
        const double lng = obj.value("lon").toString().toDouble();
        m_map->setCenter(lat, lng, 15);
        m_map->setMarker(lat, lng);
    });
}
