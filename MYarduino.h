#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino
{
public:
    Arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString getarduino_port_name();
    QByteArray read_keypad();
    void writeString(const QString &data);
    bool verifyIdInDatabase(const QString &id) ;
private:
    QSerialPort * serial ;
    static const quint16 arduino_uno_vender_id=9025 ;
    static const quint16 arduino_uno_producy_id=67 ;
    QString arduino_port_name ;
    bool arduino_is_available ;
    QByteArray data ;
    char last_key ;
};

#endif // ARDUINO_H
