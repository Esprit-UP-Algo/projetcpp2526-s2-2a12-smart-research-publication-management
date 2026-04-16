#include "rfidhandler.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QTime>
#include <QDebug>

RfidHandler::RfidHandler(Arduino *arduino, QObject *parent)
    : QObject(parent), A(arduino)
{
    if (A && A->getserial() && A->getserial()->isOpen()) {
        connect(A->getserial(), SIGNAL(readyRead()), this, SLOT(traiter_rfid()));
        qDebug() << "[RfidHandler] Actif sur" << A->getarduino_port_name()
                 << "— pointage RFID prêt (avant login)";
    } else {
        qDebug() << "[RfidHandler] Arduino non connecté — pointage RFID désactivé";
    }
}

void RfidHandler::traiter_rfid()
{
    if (!A) return;
    rfidBuffer += A->read_from_arduino();

    while (rfidBuffer.contains('\n')) {
        int idx = rfidBuffer.indexOf('\n');
        QByteArray ligne = rfidBuffer.left(idx).trimmed();
        rfidBuffer = rfidBuffer.mid(idx + 1);

        if (ligne.isEmpty()) continue;

        QString message = QString::fromUtf8(ligne);

        // Ignorer les messages de debug Arduino (Version, OK, etc.)
        if (!message.startsWith("UID:")) continue;

        // Parser "UID:<hex_uid>:<id_labo>"
        QStringList parts = message.split(':');
        if (parts.size() < 3) {
            A->write_to_arduino("0\n");
            continue;
        }

        QString uidCarte = parts[1].trimmed().toUpper();
        QString idLabo   = parts[2].trimmed();

        qDebug() << "[RFID] Carte :" << uidCarte << "| Labo :" << idLabo;

        // Vérifier si l'employé a accès à ce labo
        QSqlQuery q;
        q.prepare(
            "SELECT e.ID_EMPLOYE, e.PRENOM "
            "FROM HICHEM.EMPLOYES e "
            "JOIN HICHEM.LABS l ON l.IDEMP = e.ID_EMPLOYE "
            "WHERE e.UID_CARTE = :uid AND l.IDLABO = :labo"
        );
        q.bindValue(":uid",  uidCarte);
        q.bindValue(":labo", idLabo);

        if (!q.exec()) {
            qDebug() << "[RFID] Erreur SQL :" << q.lastError().text();
            A->write_to_arduino("0\n");
            continue;
        }

        if (q.next()) {
            // ── Accès autorisé ───────────────────────────────────────────────
            QString idEmploye = q.value("ID_EMPLOYE").toString();
            QString prenom    = q.value("PRENOM").toString();
            QString heure     = QTime::currentTime().toString("HH:mm");
            QString date      = QDate::currentDate().toString("yyyy-MM-dd");

            QSqlQuery upd;
            upd.prepare(
                "UPDATE HICHEM.EMPLOYES "
                "SET DATE_POINTAGE     = TO_DATE(:d, 'YYYY-MM-DD'), "
                "    HEURE_ARRIVEE     = :h, "
                "    STATUT_JOURNALIER = 'Présent' "
                "WHERE ID_EMPLOYE = :id"
            );
            upd.bindValue(":d",  date);
            upd.bindValue(":h",  heure);
            upd.bindValue(":id", idEmploye);

            if (upd.exec()) {
                qDebug() << "[RFID] Pointage OK :" << prenom << "à" << heure;
                emit pointageEffectue(prenom, heure);
            } else {
                qDebug() << "[RFID] Erreur UPDATE :" << upd.lastError().text();
            }

            QString reponse = QString("1:%1:%2\n").arg(prenom, heure);
            A->write_to_arduino(reponse.toUtf8());

        } else {
            // ── Accès refusé ─────────────────────────────────────────────────
            qDebug() << "[RFID] Accès refusé pour UID" << uidCarte << "labo" << idLabo;
            A->write_to_arduino("0\n");
        }
    }
}
