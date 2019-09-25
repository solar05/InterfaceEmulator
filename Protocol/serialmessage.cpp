/**
 * @file
 */

#include "serialmessage.h"

#include <sstream>

/**
 * Создает пустой пакет для RS485 длинной 4 (длина заголовка без данных)
 */
SerialMessage::SerialMessage() {
    this->data[0] = '\0';
    this->header.type = SerialMessageMC::RS485;
    this->header.length = 4;
    this->header.crc = SerialMessageMC::Crc16(reinterpret_cast<unsigned char*>(this->data), 0);
}

SerialMessage::SerialMessage(QString s) {
    this->header.type = SerialMessageMC::RS485;
    QByteArray arr = s.toLatin1();
    strcpy(this->data, arr.data());
    this->header.length = arr.length() + 4;
    this->header.crc = SerialMessageMC::Crc16(reinterpret_cast<unsigned char*> (this->data), this->header.length - 4);

}

/**
 * Устанавливает данные для передачи, расчитывает контрольную сумму и длинну пакета и записывает их в соответсвующие поля заголовка.1
 */
void SerialMessage::setData(QString &s) {
    QByteArray arr = s.toLatin1();
    strcpy(this->data, arr.data());
    this->header.length = arr.length() + 4;
    this->header.crc = SerialMessageMC::Crc16(reinterpret_cast<unsigned char*> (this->data), this->header.length - 4);
}

void SerialMessage::setType(SerialMessageMC::Interface interface) {

    this->header.type = interface;
}

/**
 * Формирует из пакета массив байтов, готовый для того, чтобы посылать его через QSerialPort.write();
 */
QByteArray SerialMessage::getPackedMessage() {
    QByteArray arr;

    arr.append(reinterpret_cast<char *> (&this->header), 4);
    arr.append(this->data);

    return arr;
}

/**
 * Нужно для дебага
 */
std::string SerialMessage::toString() {
    std::stringstream ss;

    ss << "Type:  "  << static_cast<int> (this->header.type)     << std::endl;
    ss << "Len:   "   << static_cast<int> (this->header.length)   << std::endl;
    ss << "Crc16: " << std::hex << this->header.crc             << std::endl;
    ss << "Data:  "  << this->data                               << std::endl;

    return ss.str();
}
