#ifndef TILEMAPWIDGET_H
#define TILEMAPWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QPixmap>
#include <QPoint>
#include <QHash>
#include <QSet>

// ── Clé unique pour identifier une tuile OSM ─────────────────────────────────
struct TileKey {
    int z, x, y;
    bool operator==(const TileKey &o) const { return z==o.z && x==o.x && y==o.y; }
};
inline size_t qHash(const TileKey &k, size_t seed = 0) {
    return qHash(k.z, seed) ^ qHash(k.x, seed+1) ^ qHash(k.y, seed+2);
}

// ── Widget de carte de tuiles OpenStreetMap ───────────────────────────────────
class TileMapWidget : public QWidget
{
    Q_OBJECT
public:
    enum Mode { ViewMode, PickMode };

    explicit TileMapWidget(Mode mode = ViewMode, QWidget *parent = nullptr);

    void setCenter(double lat, double lng, int zoom = 12);
    void setMarker(double lat, double lng);    // Pose un marqueur (ViewMode)
    void clearMarker();

    bool    hasSelection()   const { return m_hasMark; }
    double  selectedLat()    const { return m_markLat; }
    double  selectedLng()    const { return m_markLng; }
    QString selectedCoords() const;

signals:
    void markerPlaced(double lat, double lng);  // émis en PickMode après clic

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;

private:
    // ── Conversion coordonnées ────────────────────────────────────────────────
    static double lngToTileX(double lng, int zoom);
    static double latToTileY(double lat, int zoom);
    static double tileXToLng(double tx, int zoom);
    static double tileYToLat(double ty, int zoom);

    QPointF geoToWidget(double lat, double lng) const;
    void    widgetToGeo(QPointF p, double &lat, double &lng) const;

    // ── Tuiles ────────────────────────────────────────────────────────────────
    void requestTile(int z, int x, int y);
    void drawAttribution(QPainter &p);
    void drawMarker(QPainter &p);

    QNetworkAccessManager          *m_nam;
    QHash<TileKey, QPixmap>         m_cache;
    QSet<TileKey>                   m_pending;
    QSet<TileKey>                   m_failed;

    // ── État de la vue ────────────────────────────────────────────────────────
    double  m_centerLat = 36.8065;
    double  m_centerLng = 10.1815;
    int     m_zoom      = 6;

    // ── Panoramique ──────────────────────────────────────────────────────────
    bool    m_dragging  = false;
    QPoint  m_dragStart;
    double  m_dragLat   = 0;
    double  m_dragLng   = 0;

    // ── Marqueur ─────────────────────────────────────────────────────────────
    Mode    m_mode;
    bool    m_hasMark   = false;
    double  m_markLat   = 0;
    double  m_markLng   = 0;

    static constexpr int    TILE_SIZE = 256;
    static constexpr int    MIN_ZOOM  = 2;
    static constexpr int    MAX_ZOOM  = 19;
    static constexpr double LAT_MAX   = 85.0511;
};

#endif // TILEMAPWIDGET_H
