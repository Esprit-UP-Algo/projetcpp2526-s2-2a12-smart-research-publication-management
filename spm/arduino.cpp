#include "arduino.h"

Arduino::Arduino()
{
    serial               = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name    = "";
}

// ─── Connexion ────────────────────────────────────────────────────────────────
// Retourne :  0  = connecté avec succès
//             1  = Arduino trouvé mais port impossible à ouvrir
//            -1  = aucun Arduino détecté
int Arduino::connect_arduino()
{
    // Afficher tous les ports disponibles pour diagnostic
    qDebug() << "=== Ports série disponibles ===";
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << info.portName()
                 << "VID:" << Qt::hex << info.vendorIdentifier()
                 << "PID:" << Qt::hex << info.productIdentifier()
                 << info.description();
    }
    qDebug() << "================================";

    // Recherche du port : Arduino Uno officiel OU clone CH340/CP2102
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (!serial_port_info.hasVendorIdentifier() || !serial_port_info.hasProductIdentifier())
            continue;

        quint16 vid = serial_port_info.vendorIdentifier();
        quint16 pid = serial_port_info.productIdentifier();

        bool isArduino =
            (vid == 0x2341 && pid == 0x0043) ||  // Arduino Uno officiel
            (vid == 0x2341 && pid == 0x0001) ||  // Arduino Uno officiel (variante)
            (vid == 0x1A86 && pid == 0x7523) ||  // Clone CH340
            (vid == 0x1A86 && pid == 0x55D4) ||  // Clone CH340 (variante)
            (vid == 0x10C4 && pid == 0xEA60);    // Clone CP2102

        if (isArduino) {
            arduino_is_available = true;
            arduino_port_name    = serial_port_info.portName();
            qDebug() << "Arduino detecte :" << serial_port_info.description()
                     << "VID:" << Qt::hex << vid << "PID:" << Qt::hex << pid;
            break;
        }
    }

    qDebug() << "arduino_port_name is :" << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            // Configuration de la communication (débit, bits de données, parité...)
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0; // connexion réussie
        }
        return 1; // Arduino trouvé mais impossible d'ouvrir le port
    }
    return -1; // Arduino non disponible
}

// ─── Déconnexion ──────────────────────────────────────────────────────────────
int Arduino::close_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

// ─── Lecture depuis l'Arduino ─────────────────────────────────────────────────
QByteArray Arduino::read_from_arduino()
{
    if (serial->isReadable()) {
        data = serial->readAll(); // récupérer les données reçues
        return data;
    }
    return QByteArray();
}

// ─── Écriture vers l'Arduino ──────────────────────────────────────────────────
void Arduino::write_to_arduino(QByteArray d)
{
    if (serial->isWritable()) {
        serial->write(d);
        serial->flush();                    // forcer l'envoi immédiat
        serial->waitForBytesWritten(500);   // attendre confirmation (500ms max)
        qDebug() << "[Arduino] Envoyé :" << d.trimmed();
    } else {
        qDebug() << "Couldn't write to serial!";
    }
}

// ─── Accesseurs ───────────────────────────────────────────────────────────────
QSerialPort* Arduino::getserial()
{
    return serial;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}
