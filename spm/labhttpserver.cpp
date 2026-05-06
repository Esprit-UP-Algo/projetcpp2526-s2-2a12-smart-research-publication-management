#include "labhttpserver.h"

#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QDateTime>

LabHttpServer::LabHttpServer(QObject *parent)
    : QObject(parent)
    , m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection,
            this,     &LabHttpServer::onNewConnection);
}

bool LabHttpServer::start(quint16 port)
{
    m_port = port;
    return m_server->listen(QHostAddress::Any, port);
}

bool LabHttpServer::isRunning() const
{
    return m_server->isListening();
}

void LabHttpServer::setLab(const LabStatusData &lab)
{
    m_lab    = lab;
    m_hasLab = true;
}

// ── Trouver l'IP locale (WiFi/LAN) ───────────────────────────────────────────
QString LabHttpServer::findLocalIp() const
{
    for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces()) {
        if (iface.flags() & QNetworkInterface::IsLoopBack)  continue;
        if (!(iface.flags() & QNetworkInterface::IsUp))     continue;
        if (!(iface.flags() & QNetworkInterface::IsRunning))continue;
        for (const QNetworkAddressEntry &entry : iface.addressEntries()) {
            if (entry.ip().protocol() != QAbstractSocket::IPv4Protocol) continue;
            const QString ip = entry.ip().toString();
            if (ip.startsWith("192.") || ip.startsWith("10.") || ip.startsWith("172."))
                return ip;
        }
    }
    return QStringLiteral("127.0.0.1");
}

QString LabHttpServer::localIp()  const { return findLocalIp(); }
QString LabHttpServer::localUrl() const
{
    return QString("http://%1:%2/lab").arg(findLocalIp()).arg(m_port);
}

// ── Connexions entrantes ──────────────────────────────────────────────────────
void LabHttpServer::onNewConnection()
{
    while (m_server->hasPendingConnections()) {
        QTcpSocket *sock = m_server->nextPendingConnection();
        connect(sock, &QTcpSocket::readyRead,
                this, &LabHttpServer::onReadyRead);
        connect(sock, &QTcpSocket::disconnected,
                sock, &QTcpSocket::deleteLater);
    }
}

void LabHttpServer::onReadyRead()
{
    QTcpSocket *sock = qobject_cast<QTcpSocket *>(sender());
    if (!sock) return;

    sock->readAll(); // consommer la requête HTTP

    const QByteArray body     = buildHtml().toUtf8();
    const QByteArray response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: " + QByteArray::number(body.size()) + "\r\n"
        "Cache-Control: no-cache\r\n"
        "Connection: close\r\n"
        "\r\n" + body;

    sock->write(response);
    sock->disconnectFromHost();
}

// ── Page HTML mobile ──────────────────────────────────────────────────────────
QString LabHttpServer::buildHtml() const
{
    if (!m_hasLab) {
        return QStringLiteral(
            "<!DOCTYPE html><html><head><meta charset='utf-8'>"
            "<meta name='viewport' content='width=device-width,initial-scale=1'></head>"
            "<body style='font-family:sans-serif;text-align:center;padding:60px;background:#f0f4f8'>"
            "<h2 style='color:#666'>Aucun laboratoire sélectionné</h2>"
            "<p style='color:#999'>Sélectionnez un laboratoire dans l'application.</p>"
            "</body></html>");
    }

    const bool    dispo    = m_lab.disponibilite.compare(
                                 "Disponible", Qt::CaseInsensitive) == 0;
    const QString bgGrad   = dispo
        ? "linear-gradient(135deg,#1a7a4a 0%,#27ae60 100%)"
        : "linear-gradient(135deg,#a93226 0%,#e74c3c 100%)";
    const QString badgeBg  = dispo ? "#27ae60" : "#e74c3c";
    const QString cardBrd  = dispo ? "#a9dfbf" : "#f5b7b1";
    const QString cardBg   = dispo ? "#eafaf1"  : "#fdedec";
    const QString icon     = dispo ? "&#9989;"  : "&#128308;";
    const QString statusTx = dispo ? "DISPONIBLE" : "OCCUP&Eacute;";
    const QString pulse    = dispo ? "pulse" : "";

    return QString(
R"(<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>%1</title>
  <style>
    *{box-sizing:border-box;margin:0;padding:0}
    body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,sans-serif;
         min-height:100vh;background:%2;
         display:flex;align-items:center;justify-content:center;padding:20px}
    .card{background:#fff;border-radius:24px;padding:36px 28px;
          max-width:400px;width:100%%;
          box-shadow:0 20px 60px rgba(0,0,0,.25)}
    .icon{font-size:64px;margin-bottom:12px}
    h1{font-size:26px;font-weight:800;color:#1a1a2e;margin-bottom:4px}
    .sub{color:#999;font-size:13px;margin-bottom:24px}
    .badge{display:inline-block;background:%3;color:#fff;
           border-radius:50px;padding:14px 32px;
           font-size:20px;font-weight:900;letter-spacing:2px;
           margin-bottom:24px;text-transform:uppercase}
    .info{background:%4;border:2px solid %5;
          border-radius:16px;padding:20px;text-align:left}
    .row{display:flex;justify-content:space-between;align-items:center;
         padding:10px 0;border-bottom:1px solid rgba(0,0,0,.07)}
    .row:last-child{border-bottom:none}
    .lbl{color:#777;font-size:13px}
    .val{font-weight:700;color:#1a1a2e;font-size:13px;text-align:right;max-width:55%%}
    .ts{text-align:center;color:#bbb;font-size:11px;margin-top:20px}
    @keyframes pulse{0%%,100%%{transform:scale(1)}50%%{transform:scale(1.08)}}
    .pulse{animation:pulse 1.8s ease-in-out infinite}
  </style>
</head>
<body>
  <div class="card">
    <div class="icon %6">%7</div>
    <h1>%8</h1>
    <div class="sub">Laboratoire de recherche</div>
    <div class="badge">%9</div>
    <div class="info">
      <div class="row">
        <span class="lbl">&#128205; Localisation</span>
        <span class="val">%10</span>
      </div>
      <div class="row">
        <span class="lbl">&#128290; Num&eacute;ro</span>
        <span class="val">%11</span>
      </div>
      <div class="row">
        <span class="lbl">&#128100; Responsable</span>
        <span class="val">%12</span>
      </div>
      <div class="row">
        <span class="lbl">&#128300; Sp&eacute;cialit&eacute;</span>
        <span class="val">%13</span>
      </div>
    </div>
    <div class="ts">Mis &agrave; jour : %14</div>
  </div>
</body>
</html>)")
        .arg(m_lab.nom.toHtmlEscaped())             // %1  titre
        .arg(bgGrad)                                  // %2  fond dégradé
        .arg(badgeBg)                                 // %3  badge couleur
        .arg(cardBg)                                  // %4  card bg
        .arg(cardBrd)                                 // %5  card border
        .arg(pulse)                                   // %6  classe animation
        .arg(icon)                                    // %7  icône
        .arg(m_lab.nom.toHtmlEscaped())              // %8  nom
        .arg(statusTx)                                // %9  statut texte
        .arg(m_lab.localisation.toHtmlEscaped())     // %10
        .arg(m_lab.numero.toHtmlEscaped())           // %11
        .arg(m_lab.responsable.toHtmlEscaped())      // %12
        .arg(m_lab.specialite.toHtmlEscaped())       // %13
        .arg(QDateTime::currentDateTime()
                 .toString("dd/MM/yyyy  hh:mm:ss")); // %14
}
