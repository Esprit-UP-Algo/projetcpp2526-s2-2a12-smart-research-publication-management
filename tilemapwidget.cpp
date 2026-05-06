#include "tilemapwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtMath>
#include <cmath>

// ── Constructeur ──────────────────────────────────────────────────────────────
TileMapWidget::TileMapWidget(Mode mode, QWidget *parent)
    : QWidget(parent), m_mode(mode)
{
    m_nam = new QNetworkAccessManager(this);
    setMouseTracking(false);
    setCursor(Qt::OpenHandCursor);
    setMinimumSize(300, 200);
}

// ── API publique ──────────────────────────────────────────────────────────────
void TileMapWidget::setCenter(double lat, double lng, int zoom)
{
    m_centerLat = qBound(-LAT_MAX, lat, LAT_MAX);
    m_centerLng = lng;
    m_zoom      = qBound(MIN_ZOOM, zoom, MAX_ZOOM);
    update();
}

void TileMapWidget::setMarker(double lat, double lng)
{
    m_hasMark = true;
    m_markLat = lat;
    m_markLng = lng;
    update();
}

void TileMapWidget::clearMarker()
{
    m_hasMark = false;
    update();
}

QString TileMapWidget::selectedCoords() const
{
    if (!m_hasMark) return {};
    return QString("%1, %2")
        .arg(m_markLat, 0, 'f', 6)
        .arg(m_markLng, 0, 'f', 6);
}

// ── Conversions coordonnées ───────────────────────────────────────────────────
double TileMapWidget::lngToTileX(double lng, int zoom)
{
    return (lng + 180.0) / 360.0 * (1 << zoom);
}

double TileMapWidget::latToTileY(double lat, int zoom)
{
    lat = qBound(-LAT_MAX, lat, LAT_MAX);
    const double latRad = qDegreesToRadians(lat);
    return (1.0 - std::log(std::tan(latRad) + 1.0 / std::cos(latRad)) / M_PI) / 2.0 * (1 << zoom);
}

double TileMapWidget::tileXToLng(double tx, int zoom)
{
    return tx / (1 << zoom) * 360.0 - 180.0;
}

double TileMapWidget::tileYToLat(double ty, int zoom)
{
    const double n = M_PI - 2.0 * M_PI * ty / (1 << zoom);
    return qRadiansToDegrees(std::atan(std::sinh(n)));
}

// Coordonnées géo → pixel widget (par rapport au centre du widget)
QPointF TileMapWidget::geoToWidget(double lat, double lng) const
{
    const double cPx = lngToTileX(m_centerLng, m_zoom) * TILE_SIZE;
    const double cPy = latToTileY(m_centerLat, m_zoom) * TILE_SIZE;
    const double px  = lngToTileX(lng, m_zoom)          * TILE_SIZE;
    const double py  = latToTileY(lat, m_zoom)           * TILE_SIZE;
    return QPointF(width() / 2.0 + (px - cPx), height() / 2.0 + (py - cPy));
}

// Pixel widget → coordonnées géo
void TileMapWidget::widgetToGeo(QPointF p, double &lat, double &lng) const
{
    const double cPx = lngToTileX(m_centerLng, m_zoom) * TILE_SIZE;
    const double cPy = latToTileY(m_centerLat, m_zoom) * TILE_SIZE;
    const double px  = cPx + (p.x() - width()  / 2.0);
    const double py  = cPy + (p.y() - height() / 2.0);
    lng = tileXToLng(px / TILE_SIZE, m_zoom);
    lat = tileYToLat(py / TILE_SIZE, m_zoom);
}

// ── Affichage ─────────────────────────────────────────────────────────────────
void TileMapWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    const int  n     = 1 << m_zoom;
    const double cPx = lngToTileX(m_centerLng, m_zoom) * TILE_SIZE;
    const double cPy = latToTileY(m_centerLat, m_zoom) * TILE_SIZE;

    // Coin supérieur gauche en pixels monde
    const double leftPx = cPx - width()  / 2.0;
    const double topPx  = cPy - height() / 2.0;

    // Tuiles à dessiner
    const int tx0 = (int)std::floor(leftPx / TILE_SIZE);
    const int ty0 = (int)std::floor(topPx  / TILE_SIZE);
    const int tx1 = (int)std::floor((leftPx + width())  / TILE_SIZE);
    const int ty1 = (int)std::floor((topPx  + height()) / TILE_SIZE);

    for (int ty = ty0; ty <= ty1; ++ty) {
        if (ty < 0 || ty >= n) continue;
        for (int tx = tx0; tx <= tx1; ++tx) {
            const int wx = ((tx % n) + n) % n;   // Wrap longitude
            const TileKey key{m_zoom, wx, ty};

            const double drawX = tx * TILE_SIZE - leftPx;
            const double drawY = ty * TILE_SIZE - topPx;
            const QRectF rect(drawX, drawY, TILE_SIZE, TILE_SIZE);

            if (m_cache.contains(key)) {
                p.drawPixmap(rect.toRect(), m_cache[key]);
            } else {
                // Placeholder gris pendant le chargement
                p.fillRect(rect, QColor(210, 210, 210));
                p.setPen(QColor(190, 190, 190));
                p.drawRect(rect.adjusted(0, 0, -1, -1));
                requestTile(m_zoom, wx, ty);
            }
        }
    }

    // Marqueur
    if (m_hasMark) drawMarker(p);

    // Attribution OSM (obligatoire selon les conditions d'utilisation)
    drawAttribution(p);
}

void TileMapWidget::drawMarker(QPainter &p)
{
    const QPointF pos = geoToWidget(m_markLat, m_markLng);
    const int R = 11;

    // Ombre portée
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 70));
    p.drawEllipse(pos + QPointF(3, R + 3), R, 5);

    // Corps du repère (cercle)
    p.setPen(QPen(Qt::white, 2.5));
    p.setBrush(QColor(220, 53, 69));
    p.drawEllipse(pos - QPointF(R, 2 * R), 2 * R, 2 * R);

    // Pointe vers le bas
    QPolygonF tip;
    tip << pos - QPointF(R * 0.55, R * 0.4)
        << pos - QPointF(-R * 0.55, R * 0.4)
        << pos;
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(220, 53, 69));
    p.drawPolygon(tip);

    // Point blanc intérieur
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawEllipse(pos - QPointF(R * 0.35, 2 * R - R * 0.35), R * 0.7, R * 0.7);

    // Étiquette de coordonnées
    const QString label = QString("  %1, %2  ")
                              .arg(m_markLat, 0, 'f', 5)
                              .arg(m_markLng, 0, 'f', 5);
    QFont f = font();
    f.setPointSize(9);
    f.setBold(true);
    p.setFont(f);
    QFontMetrics fm(f);
    const int tw = fm.horizontalAdvance(label);
    const QRectF lr(pos.x() - tw / 2.0, pos.y() - 3 * R - fm.height() - 6,
                    tw, fm.height() + 6);
    p.setBrush(QColor(0, 0, 0, 170));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(lr, 4, 4);
    p.setPen(Qt::white);
    p.drawText(lr, Qt::AlignCenter, label);
}

void TileMapWidget::drawAttribution(QPainter &p)
{
    const QString text = " © OpenStreetMap contributors ";
    QFont f = font();
    f.setPointSize(8);
    p.setFont(f);
    QFontMetrics fm(f);
    const QRect r(width() - fm.horizontalAdvance(text) - 4,
                  height() - fm.height() - 6,
                  fm.horizontalAdvance(text) + 4,
                  fm.height() + 4);
    p.fillRect(r, QColor(255, 255, 255, 210));
    p.setPen(Qt::black);
    p.drawText(r, Qt::AlignVCenter, text);
}

// ── Téléchargement des tuiles ─────────────────────────────────────────────────
void TileMapWidget::requestTile(int z, int x, int y)
{
    const TileKey key{z, x, y};
    if (m_pending.contains(key) || m_failed.contains(key)) return;
    m_pending.insert(key);

    static const char *subs[] = {"a", "b", "c"};
    const char *sub = subs[(x + y) % 3];

    const QUrl url(QString("https://%1.tile.openstreetmap.org/%2/%3/%4.png")
                       .arg(sub).arg(z).arg(x).arg(y));

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::UserAgentHeader, "SRPM-Qt-App/1.0 (lab-management)");
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                     QNetworkRequest::NoLessSafeRedirectPolicy);

    QNetworkReply *reply = m_nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply, key]() {
        m_pending.remove(key);
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap pix;
            if (pix.loadFromData(reply->readAll()) && !pix.isNull()) {
                m_cache.insert(key, pix);
                update();
            } else {
                m_failed.insert(key);
            }
        } else {
            m_failed.insert(key);
        }
        reply->deleteLater();
    });
}

// ── Événements souris ─────────────────────────────────────────────────────────
void TileMapWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_dragging  = true;
        m_dragStart = e->pos();
        m_dragLat   = m_centerLat;
        m_dragLng   = m_centerLng;
        setCursor(Qt::ClosedHandCursor);
    }
}

void TileMapWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_dragging) return;
    const QPoint delta = e->pos() - m_dragStart;

    // Déplacement en longitude
    const double scale = (double)TILE_SIZE * (1 << m_zoom);
    m_centerLng = m_dragLng - delta.x() / scale * 360.0;

    // Déplacement en latitude (Mercator)
    const double cy = latToTileY(m_dragLat, m_zoom);
    const double ny = cy - (double)delta.y() / TILE_SIZE;
    m_centerLat = qBound(-LAT_MAX, tileYToLat(ny, m_zoom), LAT_MAX);

    update();
}

void TileMapWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) return;

    const bool wasDrag = (e->pos() - m_dragStart).manhattanLength() > 5;
    m_dragging = false;
    setCursor(Qt::OpenHandCursor);

    // En PickMode, un simple clic (pas un drag) pose le marqueur
    if (!wasDrag && m_mode == PickMode) {
        double lat, lng;
        widgetToGeo(e->pos(), lat, lng);
        m_hasMark = true;
        m_markLat = lat;
        m_markLng = lng;
        update();
        emit markerPlaced(lat, lng);
    }
}

void TileMapWidget::wheelEvent(QWheelEvent *e)
{
    // Récupérer les coordonnées géo sous le curseur avant zoom
    double geoLat, geoLng;
    widgetToGeo(e->position(), geoLat, geoLng);

    const int newZoom = qBound(MIN_ZOOM, m_zoom + (e->angleDelta().y() > 0 ? 1 : -1), MAX_ZOOM);
    if (newZoom == m_zoom) return;
    m_zoom = newZoom;

    // Recalculer le centre pour garder le point sous curseur fixe
    const double mPx = lngToTileX(geoLng, m_zoom) * TILE_SIZE;
    const double mPy = latToTileY(geoLat, m_zoom) * TILE_SIZE;
    const double newCPx = mPx - (e->position().x() - width()  / 2.0);
    const double newCPy = mPy - (e->position().y() - height() / 2.0);

    m_centerLng = tileXToLng(newCPx / TILE_SIZE, m_zoom);
    m_centerLat = qBound(-LAT_MAX, tileYToLat(newCPy / TILE_SIZE, m_zoom), LAT_MAX);

    update();
}
