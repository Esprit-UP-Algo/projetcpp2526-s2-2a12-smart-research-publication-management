#include "rfidhandler.h"
#include <QSqlQuery>
#include <QSqlDatabase>
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

        if (message.startsWith("SKU:")) {
            QString sku = message.mid(4).trimmed();
            qDebug() << "[Keypad] SKU reçu dans RfidHandler =" << sku;
            emit skuRecu(sku);
            continue;
        }
        if (message.startsWith("INPUT:")) {
            QString input = message.mid(6).trimmed();
            emit inputSkuRecu(input);
            continue;
        }

        //----------------------------------------------------
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

        // Vérifier si l'employé a accès à ce labo et récupérer son état de pointage.
        QSqlQuery q;
        q.prepare(
            "SELECT e.ID_EMPLOYE, e.PRENOM, "
            "       e.HEURE_ARRIVEE, e.HEURE_DEPART, "
            "       TO_CHAR(e.DATE_POINTAGE, 'YYYY-MM-DD') AS DATE_POINTAGE "
            "FROM HICHEM.EMPLOYES e "
            "JOIN HICHEM.LABS l ON l.IDEMP = e.ID_EMPLOYE "
            "WHERE e.UID_CARTE = :uid AND l.IDLABO = :labo"
        );
        q.bindValue(":uid",  uidCarte);
        q.bindValue(":labo", idLabo);

        if (!q.exec()) {
            qDebug() << "[RFID] Erreur SQL SELECT :" << q.lastError().text();
            A->write_to_arduino("0\n");
            continue;
        }

        if (q.next()) {
            // Accès autorisé.
            QString idEmploye    = q.value("ID_EMPLOYE").toString();
            QString prenom       = q.value("PRENOM").toString();
            bool    arriveeNull  = q.value("HEURE_ARRIVEE").isNull();
            bool    departNull   = q.value("HEURE_DEPART").isNull();
            QString hArrivee     = arriveeNull ? "" : q.value("HEURE_ARRIVEE").toString().trimmed();
            QString hDepart      = departNull  ? "" : q.value("HEURE_DEPART").toString().trimmed();
            QString datePointage = q.value("DATE_POINTAGE").toString().trimmed();
            QString heure        = QTime::currentTime().toString("HH:mm");
            QString dateAuj      = QDate::currentDate().toString("yyyy-MM-dd");

            qDebug() << "[RFID] DB —"
                     << "date:" << datePointage
                     << "hArrivee:" << hArrivee << "(null:" << arriveeNull << ")"
                     << "hDepart:"  << hDepart  << "(null:" << departNull  << ")"
                     << "dateAuj:"  << dateAuj;

            // Déjà pointé (arrivée et départ déjà enregistrés aujourd'hui).
            if (datePointage == dateAuj && !hArrivee.isEmpty() && !hDepart.isEmpty()) {
                qDebug() << "[RFID] Déjà pointé (arrivée+départ) :" << prenom;
                A->write_to_arduino(QString("3:%1\n").arg(prenom).toUtf8());
            } else if (datePointage == dateAuj && !hArrivee.isEmpty() && hDepart.isEmpty()) {
                // Enregistrer le départ (deuxième passage du jour).
                QSqlQuery upd;
                upd.prepare(
                    "UPDATE HICHEM.EMPLOYES "
                    "SET HEURE_DEPART = :h "
                    "WHERE ID_EMPLOYE = :id"
                );
                upd.bindValue(":h",  heure);
                upd.bindValue(":id", idEmploye);

                if (upd.exec()) {
                    qDebug() << "[RFID] Départ enregistré pour" << prenom << "à" << heure;
                    emit pointageEffectue(prenom, heure);
                } else {
                    qDebug() << "[RFID] Erreur UPDATE départ :" << upd.lastError().text();
                }
                A->write_to_arduino(QString("2:%1:%2\n").arg(prenom, heure).toUtf8());
            } else {
                // Enregistrer l'arrivée (premier passage du jour).
                QSqlQuery upd;
                upd.prepare(
                    "UPDATE HICHEM.EMPLOYES "
                    "SET DATE_POINTAGE     = TO_DATE(:d, 'YYYY-MM-DD'), "
                    "    HEURE_ARRIVEE     = :h, "
                    "    HEURE_DEPART      = NULL, "
                    "    STATUT_JOURNALIER = 'Présent' "
                    "WHERE ID_EMPLOYE = :id"
                );
                upd.bindValue(":d",  dateAuj);
                upd.bindValue(":h",  heure);
                upd.bindValue(":id", idEmploye);

                if (upd.exec()) {
                    qDebug() << "[RFID] Arrivée enregistrée pour" << prenom << "à" << heure;
                    emit pointageEffectue(prenom, heure);
                } else {
                    qDebug() << "[RFID] Erreur UPDATE arrivée :" << upd.lastError().text();
                }
                A->write_to_arduino(QString("1:%1:%2\n").arg(prenom, heure).toUtf8());
            }
        } else {
            // ── Accès refusé ─────────────────────────────────────────────────
            qDebug() << "[RFID] Accès refusé pour UID" << uidCarte << "labo" << idLabo;
            A->write_to_arduino("0\n");
        }
    }
}
