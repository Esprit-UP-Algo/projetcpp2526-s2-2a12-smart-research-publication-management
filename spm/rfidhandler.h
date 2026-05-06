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
    explicit RfidHandler(Arduino *rfidArduino, QObject *parent = nullptr);
    void attachKeypad(Arduino *keypadArduino);

signals:
    void pointageEffectue(const QString &prenom, const QString &heure);
    void skuRecu(const QString &sku);
    void inputSkuRecu(const QString &input);

private slots:
    void traiter_rfid();
    void traiter_keypad();

private:
    Arduino   *A        = nullptr;  // Arduino RFID
    Arduino   *AKeypad  = nullptr;  // Arduino Keypad
    QByteArray rfidBuffer;
    QByteArray keypadBuffer;
};

#endif // RFIDHANDLER_H
