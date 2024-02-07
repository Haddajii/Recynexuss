#include "MYarduino.h"
#include "QSqlQuery"
#include <QSqlError>


Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}




int Arduino::connect_arduino()
{

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vender_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600);
                serial->setDataBits(QSerialPort::Data8);
                serial->setParity(QSerialPort::NoParity);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}




int Arduino::close_arduino(){
    if(serial->isOpen()){
        serial->close();
        return 0 ;
    }
  return 1 ;
}


QByteArray Arduino::read_from_arduino(){
    if(serial->isReadable()){
        data += serial->readAll();

        // Check for the delimiter "|" to determine the end of the ID
        int delimiterIndex = data.indexOf("|");
        if (delimiterIndex != -1) {
            // Extract the ID part before the delimiter
            QByteArray idData = data.left(delimiterIndex);
            data.remove(0, delimiterIndex + 1);  // Remove the processed data

            // Print the received ID for debugging


            return idData;
        }
    }

    return QByteArray();  // Return an empty QByteArray if the ID is not complete
}



int Arduino::write_to_arduino(QByteArray d ){
    if(serial->isWritable()){
        serial->write(d);
    }
    else{
        qDebug() << "couldn't write to serial";
    }
    return 0 ;
}



QByteArray Arduino::read_keypad()
{
    QByteArray data;

    while (serial->isReadable()) {
        QByteArray keyData = serial->readAll();
        if (!keyData.isEmpty()) {
            data = keyData;
        }
    }

    return data;
}



void Arduino::writeString(const QString &data)
{
    QByteArray byteArray = data.toUtf8();
    serial->write(byteArray);
}


bool Arduino::verifyIdInDatabase(const QString &id) {
    // Implement the logic to check if the entered ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT disponibilite FROM produit WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // ID exists, display disponibilite value on the LCD
        QString disponibilite = query.value(0).toString();

        writeString(disponibilite);
        qDebug() << "ID verification result: true";
        return true;
    } else {
        // ID does not exist, display a message on the LCD
        writeString("ID Not Found");
        qDebug() << "ID verification result: false";
        return false;
    }
}










