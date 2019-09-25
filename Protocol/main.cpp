#include <iostream>
#include <QDebug>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include "serialmessage.h"

using namespace std;

int main()
{

    QSerialPort port("COM1");
    QSerialPort rec ("COM2");

    port.setBaudRate(QSerialPort::Baud9600);
    rec .setBaudRate(QSerialPort::Baud9600);

    port.setDataBits(QSerialPort::Data8);
    rec .setDataBits(QSerialPort::Data8);

    port.setStopBits(QSerialPort::OneStop);
    rec .setStopBits(QSerialPort::OneStop);

    port.open(QSerialPort::ReadWrite);
    rec .open(QSerialPort::ReadWrite);

    QString str("ABCDEF");

    SerialMessage msg(str);

    msg.setType(SerialMessageMC::Interface::CAN);

    cout << "Message to send: " << endl
         << msg.toString()      << endl;

    port.write(msg.getPackedMessage());

    port.waitForBytesWritten();

    rec.waitForReadyRead();

    QByteArray res = rec.readAll();

    char *gotPacket = res.data();

    SerialMessageMC::Header* gotHeader = SerialMessageMC::getHeader(gotPacket);

    unsigned char* gotData             = SerialMessageMC::getData  (gotPacket);

    int computedCrc                    = SerialMessageMC::Crc16    (gotData, gotHeader->length - 4);

    cout << "Got message:"                                                                   << endl
         << "\tType:         " << static_cast<int> (gotHeader->type)                         << endl
         << "\tLen:          " << static_cast<int> (gotHeader->length)                       << endl
         << "\tCrc:          " << hex << gotHeader->crc                                      << endl
         << "\tComputed crc: " << computedCrc                                                << endl
         << "\tIsEq:         " << (SerialMessageMC::checkCrc(res.data()) ? "True" : "False") << endl
         << "\tData:         " << gotData                                                    << endl;


    return 0;
}
