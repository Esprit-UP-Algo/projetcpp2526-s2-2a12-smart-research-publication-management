#ifndef LABHTTPSERVER_H
#define LABHTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

struct LabStatusData {
    int     id            = 0;
    QString nom;
    QString responsable;
    QString numero;
    QString localisation;
    QString disponibilite;
    QString specialite;
};

class LabHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit LabHttpServer(QObject *parent = nullptr);

    bool    start(quint16 port = 8080);
    void    setLab(const LabStatusData &lab);
    QString localUrl()  const;
    QString localIp()   const;
    quint16 port()      const { return m_port; }
    bool    isRunning() const;

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer   *m_server;
    LabStatusData m_lab;
    bool          m_hasLab = false;
    quint16       m_port   = 8080;

    QString buildHtml()      const;
    QString findLocalIp()    const;
};

#endif // LABHTTPSERVER_H
