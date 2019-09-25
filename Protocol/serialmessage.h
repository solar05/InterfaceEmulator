#ifndef SERIALMESSAGE_H
#define SERIALMESSAGE_H

#include "serialmessagemc.h"
#include <QByteArray>
#include <QString>
#include <string>
#include <stdexcept>

/**
 * @mainpage Interface Emulator Library
 *
 *
 * @section Example
 * @include{lineno} main.cpp
 */

/**
 * @file
 * @class SerialMessage
 * @brief Класс для создание пакета на стороне ПК
 */
class SerialMessage {

public:

    /**
     * @brief  Конструктор по умолчанию.
     */
    SerialMessage();

    /**
     * @brief Конструктор с установкой данных
     * @param s Строка, которая будет передана как данные
     */
    SerialMessage(QString s);

    /**
     * @brief Сеттер для данных.
     * @param s Данные, которые будут переданы
     * @todo Создать сеттеры для данных из QByteArray и unsigned char*
     */
    void        setData(QString &s);


    /**
     * @brief Сеттер для интерфейса назначения см.  SerialMessageMC::Interface
     * @param interface Номер интерфейса
     */
    void        setType(SerialMessageMC::Interface interface);

    /**
     * @brief Создает массив байтов, готовый для передачи.
     * @return Массив байтов созданный из пакета
     */
    QByteArray  getPackedMessage();

    /**
     * @brief Строковое представление пакета.
     * @return Строковое представление пакета
     */
    std::string toString();

private:

    /**
     * @brief Структура заголовка пакета, см. SerialMessageMC::Header
     */
    SerialMessageMC::Header header;

    /**
     * @brief Массив данных для передачи
     */
    char                    data[251];

};

#endif // SERIALMESSAGE_H
