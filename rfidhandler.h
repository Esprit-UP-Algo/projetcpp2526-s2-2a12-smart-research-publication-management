#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include "arduino.h"

// =============================================================================
//  RfidHandler — gère le pointage RFID indépendamment du login Qt
//  Vit dans main.cpp, actif dès le lancement de l'appli
// =============================================================================
class RfidHandler : public QObject
{
    Q_OBJECT

public:
    explicit RfidHandler(Arduino *arduino, QObject *parent = nullptr);

signals:
    // Émis après un pointage réussi → MainWindow peut rafraîchir le tableau
    void pointageEffectue(const QString &prenom, const QString &heure);

private slots:
    void traiter_rfid();

private:
    Arduino   *A;
    QByteArray rfidBuffer;
};

#endif // RFIDHANDLER_H
