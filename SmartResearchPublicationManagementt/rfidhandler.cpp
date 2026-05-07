#include "rfidhandler.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDate>
#include <QTime>
#include <QDebug>

RfidHandler::RfidHandler(Arduino *rfidArduino, QObject *parent)
    : QObject(parent), A(rfidArduino)
{
    if (A && A->getserial() && A->getserial()->isOpen()) {
        connect(A->getserial(), SIGNAL(readyRead()), this, SLOT(traiter_rfid()));
        qDebug() << "[RfidHandler] RFID actif sur" << A->getarduino_port_name();
    } else {
        qDebug() << "[RfidHandler] Arduino RFID non connecté";
    }
}

void RfidHandler::attachKeypad(Arduino *keypadArduino)
{
    AKeypad = keypadArduino;
    if (AKeypad && AKeypad->getserial() && AKeypad->getserial()->isOpen()) {
        connect(AKeypad->getserial(), SIGNAL(readyRead()), this, SLOT(traiter_keypad()));
        qDebug() << "[RfidHandler] Keypad actif sur" << AKeypad->getarduino_port_name();
    } else {
        qDebug() << "[RfidHandler] Arduino Keypad non connecté";
    }
}

void RfidHandler::reconnectKeypad(Arduino *keypadArduino)
{
    // Déconnecter l'ancien signal si présent
    if (AKeypad && AKeypad->getserial())
        disconnect(AKeypad->getserial(), SIGNAL(readyRead()), this, SLOT(traiter_keypad()));

    AKeypad = keypadArduino;
    keypadBuffer.clear();

    if (AKeypad && AKeypad->getserial() && AKeypad->getserial()->isOpen()) {
        connect(AKeypad->getserial(), SIGNAL(readyRead()), this, SLOT(traiter_keypad()));
        qDebug() << "[RfidHandler] Keypad reconnecté sur" << AKeypad->getarduino_port_name();
    }
}

void RfidHandler::traiter_keypad()
{
    if (!AKeypad) return;
    keypadBuffer += AKeypad->read_from_arduino();

    while (keypadBuffer.contains('\n')) {
        int idx = keypadBuffer.indexOf('\n');
        QByteArray ligne = keypadBuffer.left(idx).trimmed();
        keypadBuffer = keypadBuffer.mid(idx + 1);

        if (ligne.isEmpty()) continue;

        QString msg = QString::fromUtf8(ligne);

        if (msg.startsWith("SKU:")) {
            emit skuRecu(msg.mid(4).trimmed());
        } else if (msg.startsWith("INPUT:")) {
            emit inputSkuRecu(msg.mid(6).trimmed());
        } else {
            qDebug() << "[Keypad]" << msg;
        }
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

        // Ignorer tout ce qui n'est pas un UID RFID
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

            qDebug() << "—"
                     << "date:" << datePointage
                     << "hArrivee:" << hArrivee << "(null:" << arriveeNull << ")"
                     << "hDepart:"  << hDepart  << "(null:" << departNull  << ")"
                     << "dateAuj:"  << dateAuj;

            // Déjà pointé (arrivée et départ déjà enregistrés aujourd'hui).
            if (datePointage == dateAuj && !hArrivee.isEmpty() && !hDepart.isEmpty()) {
                qDebug() << "Employée a deja pointe (arrivee+depart) :" << prenom;
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
                    QSqlDatabase::database().commit();  // ← COMMIT Oracle obligatoire
                    qDebug() << "Depart enregistre pour" << prenom << "à" << heure;
                    emit pointageEffectue(prenom, heure);
                } else {
                    QSqlDatabase::database().rollback();
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
                    QSqlDatabase::database().commit();  // ← COMMIT Oracle obligatoire
                    qDebug() << "Arrivee enregistree pour" << prenom << "a" << heure;
                    emit pointageEffectue(prenom, heure);
                } else {
                    QSqlDatabase::database().rollback();
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
