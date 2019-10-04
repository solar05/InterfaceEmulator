#ifndef SERIALMESSAGEMC_H
#define SERIALMESSAGEMC_H

#include "stdint.h"


/**
 * @file
 * @namespace SerialMessageMC
 * @brief Неймспейс с функциями и структурами для работы с пакетами на стороне микроконтроллера
 */

namespace SerialMessageMC {


    /**
     * @brief Структура, описывающая заголовок пакета.
     *
     * Состоит из 4 байтов, расположенных в памяти последовательно.
     */
    struct __attribute__((__packed__)) Header {

        /**
         * @brief Интерфейс, куда будут пересылаться данные
         */
        uint8_t type;
        /**
         * @brief Длинна всего пакета
         */
        uint8_t length;
        /**
         * @brief Контрольная сумма
         */
        uint16_t crc;
    };

    /**
     * @brief Список доступных интерфейсов
     */
    enum Interface {
        RS485 = 0,
        CAN = 1,
        PARALLEL = 2
    };

    /**
    * @brief Функция расчета CRC16
    * @param pcBlock Указатель на массив байтов
    * @param len Длинна массива
    * @return Контрольная сумма
    */
    unsigned short int Crc16(unsigned char *pcBlock, unsigned short len); //Для расчета и проверки checksum использовать эту функцию


    /**
     * @brief Получает заголовок из пакета
     * @param packet Указатель на массив байтов, который является пакетом
     * @return Указатель на структуру, содержащую в себе заголовок
     */
    Header*            getHeader(char *packet);

    /**
     * @brief Получает указатель на массив данных из пакета
     * @param packet Указатель на массив байтов, который является пакетом
     * @return Указатель на массив байтов, которые являются данными из пакета
     */
    unsigned char*     getData  (char* packet);

    /**
     * @brief Проверяет соответствие контрольной суммы из пакета расчитанной контрольной сумме
     * @param packet Указатель на массив байтов, который является пакетом
     * @return **True** если контрольная сумма совпала, **False** если нет
     */
    bool               checkCrc (char* packet);

}

#endif // SERIALMESSAGEMC_H
