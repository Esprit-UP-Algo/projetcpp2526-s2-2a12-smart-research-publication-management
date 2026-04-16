#include "mapdialog.h"

#include <QVBoxLayout>
#include <QWebEnginePage>
#include <QUrl>

MapDialog::MapDialog(Mode mode, const QString &location, QWidget *parent)
    : QDialog(parent), m_mode(mode)
{
    setWindowTitle(mode == ViewMode
                       ? "Localisation du laboratoire"
                       : "Sélectionner une position sur la carte");
    resize(900, 650);
    setMinimumSize(600, 450);

    m_view   = new QWebEngineView(this);
    m_bridge = new MapBridge(this);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_view);

    if (mode == PickMode) {
        // Enregistrer le bridge JS ↔ Qt
        auto *channel = new QWebChannel(this);
        channel->registerObject(QStringLiteral("bridge"), m_bridge);
        m_view->page()->setWebChannel(channel);

        // Quand JS confirme des coordonnées → fermer le dialog avec le résultat
        connect(m_bridge, &MapBridge::coordinatesSelected, this,
                [this](const QString &coords) {
                    emit coordinatesSelected(coords);
                    accept();
                });

        m_view->setHtml(buildPickHtml(), QUrl(QStringLiteral("qrc:/")));
    } else {
        m_view->setHtml(buildViewHtml(location), QUrl(QStringLiteral("qrc:/")));
    }
}

// ---------------------------------------------------------------------------
// MODE AFFICHAGE : centre la carte sur la localisation donnée
// ---------------------------------------------------------------------------
QString MapDialog::buildViewHtml(const QString &location) const
{
    // Tenter de parser "lat, lng"
    double lat = 36.8065, lng = 10.1815;
    bool   isCoords = false;

    QStringList parts = location.split(QLatin1Char(','));
    if (parts.size() == 2) {
        bool okLat, okLng;
        double tLat = parts[0].trimmed().toDouble(&okLat);
        double tLng = parts[1].trimmed().toDouble(&okLng);
        if (okLat && okLng) {
            lat = tLat;
            lng = tLng;
            isCoords = true;
        }
    }

    // Échapper les apostrophes pour éviter les erreurs JS
    QString escapedLoc = location;
    escapedLoc.replace(QLatin1Char('\''), QLatin1String("\\'"));
    // URL-encoder pour Nominatim
    QString encodedLoc = QString::fromUtf8(QUrl::toPercentEncoding(location));

    // Bloc JS d'initialisation selon le type de localisation
    QString jsInit;
    if (isCoords) {
        jsInit = QString(
            "L.marker([%1,%2]).addTo(map).bindPopup('%3').openPopup();")
                     .arg(lat, 0, 'f', 6)
                     .arg(lng, 0, 'f', 6)
                     .arg(escapedLoc);
    } else {
        jsInit = QString(R"(
fetch('https://nominatim.openstreetmap.org/search?q=%1&format=json&limit=1',
      {headers:{'User-Agent':'SRPM-App/1.0'}})
  .then(function(r){return r.json();})
  .then(function(d){
    if(d && d.length>0){
        var lt=parseFloat(d[0].lat), ln=parseFloat(d[0].lon);
        map.setView([lt,ln],15);
        L.marker([lt,ln]).addTo(map).bindPopup('%2').openPopup();
    } else {
        L.marker([map.getCenter().lat,map.getCenter().lng])
          .addTo(map).bindPopup('%2 (position approx.)').openPopup();
    }
  })
  .catch(function(){});
)").arg(encodedLoc, escapedLoc);
    }

    QString html = QStringLiteral(R"(<!DOCTYPE html>
<html><head>
<meta charset="utf-8"/>
<link rel="stylesheet"
      href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css"
      integrity="sha256-p4NxAoJBhIIN+hmNHrzRCf9tD/miZyoHS5obTRR9BMY="
      crossorigin=""/>
<script
      src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"
      integrity="sha256-20nQCchB9co0qIjJZRGuk2/Z9VM+kNiyxNV/XN2GqHk="
      crossorigin=""></script>
<style>
  body { margin:0; padding:0; }
  #map { width:100%; height:100vh; }
</style>
</head>
<body>
<div id="map"></div>
<script>
var map = L.map('map').setView([LAT, LNG], 15);
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a>',
    maxZoom: 19
}).addTo(map);
JS_INIT
</script>
</body></html>)");

    html.replace(QStringLiteral("LAT"),     QString::number(lat, 'f', 6))
        .replace(QStringLiteral("LNG"),     QString::number(lng, 'f', 6))
        .replace(QStringLiteral("JS_INIT"), jsInit);
    return html;
}

// ---------------------------------------------------------------------------
// MODE SÉLECTION : l'utilisateur clique pour poser un marqueur et confirme
// ---------------------------------------------------------------------------
QString MapDialog::buildPickHtml() const
{
    return QStringLiteral(R"(<!DOCTYPE html>
<html><head>
<meta charset="utf-8"/>
<link rel="stylesheet"
      href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css"
      integrity="sha256-p4NxAoJBhIIN+hmNHrzRCf9tD/miZyoHS5obTRR9BMY="
      crossorigin=""/>
<script
      src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"
      integrity="sha256-20nQCchB9co0qIjJZRGuk2/Z9VM+kNiyxNV/XN2GqHk="
      crossorigin=""></script>
<script src="qrc:///qtwebchannel/qwebchannel.js"></script>
<style>
  * { box-sizing: border-box; }
  body { margin:0; padding:0; font-family: Arial, sans-serif; }
  #map { width:100%; height: calc(100vh - 60px); }
  #bar {
    position: fixed; bottom: 0; left: 0; right: 0; height: 60px;
    background: #1a237e;
    display: flex; align-items: center; gap: 12px; padding: 0 16px;
    box-shadow: 0 -2px 8px rgba(0,0,0,.3);
  }
  #icon { font-size: 22px; }
  #coords { color: #ffffff; flex: 1; font-size: 14px; }
  #btnOk {
    padding: 9px 22px; background: #43a047; color: #fff;
    border: none; border-radius: 5px; font-size: 14px;
    cursor: pointer; transition: background .2s;
  }
  #btnOk:not([disabled]):hover { background: #2e7d32; }
  #btnOk[disabled] { background: #78909c; cursor: default; }
</style>
</head>
<body>
<div id="map"></div>
<div id="bar">
  <span id="icon">📍</span>
  <span id="coords">Cliquez sur la carte pour sélectionner une position…</span>
  <button id="btnOk" onclick="confirmCoords()" disabled>Confirmer</button>
</div>
<script>
var selected = null;
var marker   = null;
var bridge   = null;

// Initialiser le canal Qt ↔ JS
new QWebChannel(qt.webChannelTransport, function(channel) {
    bridge = channel.objects.bridge;
});

var map = L.map('map').setView([36.8065, 10.1815], 12);
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a>',
    maxZoom: 19
}).addTo(map);

map.on('click', function(e) {
    selected = e.latlng.lat.toFixed(6) + ', ' + e.latlng.lng.toFixed(6);
    document.getElementById('coords').textContent = '📌 ' + selected;
    document.getElementById('btnOk').disabled = false;
    if (marker) marker.remove();
    marker = L.marker(e.latlng)
               .addTo(map)
               .bindPopup(selected)
               .openPopup();
});

function confirmCoords() {
    if (selected && bridge) {
        bridge.coordsSelected(selected);
    }
}
</script>
</body></html>)");
}
