#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino {
public:
    Arduino();

    // Retourne 0 = OK, 1 = non trouvé, 2 = impossible d'ouvrir
    int connect_arduino();

    int close_arduino();

    void       write_to_arduino(QByteArray data);
    QByteArray read_from_arduino();

    QSerialPort* getserial();
    QString      getarduino_port_name();

private:
    QSerialPort *serial;

    // Arduino Uno / Nano CH340 : VID=0x2341 PID=0x0043
    // (pour clone CH340 : VID=0x1A86 PID=0x7523 — à adapter si besoin)
    static const quint16 arduino_uno_vendor_id  = 9025;   // 0x2341
    static const quint16 arduino_uno_product_id = 67;     // 0x0043

    QString    arduino_port_name;
    bool       arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
