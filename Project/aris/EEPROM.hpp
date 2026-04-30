#ifndef _EEPROM_HPP_
#define _EEPROM_HPP_

#include <stdint.h>


#define EEPROM_BASE  0x00070400              // Базовый адресс ЕЕПРОМ микроконтроллера

// Карта регистров ЕЕПРОМ
struct EEPROM_Regs {
  volatile uint32_t EEDAT;
  volatile uint32_t EEA;
  volatile uint32_t EECON;
  volatile uint32_t EESTA;
  volatile uint32_t EERB;
  volatile uint32_t EEADJ;
  volatile uint32_t NCYCRL;
  volatile uint32_t NCYCEP1;
  volatile uint32_t NCYCEP2;
};

#define EEPROM ((EEPROM_Regs*)EEPROM_BASE)  // Структура регистров


// Битовые Маски
enum {
  // Маски регистра EESTA
  EESTA_BSY_ByteMask = 1,

  // Маски регистра EECON
  EECON_EX_ByteMask  = 1,
  EECON_OP_Read  = 0b00 << 1,
  EECON_OP_Erase = 0b01 << 1,
  EECON_OP_Write = 0b10 << 1,
  EECON_BWE_ByteMask = 1 << 7,
};


// Пространство имен ЕЕПРОМ
namespace Eeprom {
  inline void write(const uint32_t address, const uint32_t data) {
    while (EEPROM->EESTA & EESTA_BSY_ByteMask); // Ожидаем готовность EEPROM
    EEPROM->EECON = EECON_BWE_ByteMask;        // Разрешаем запись в буфер
    EEPROM->EEA   = address;                  // Загружаем записываемый адрес в буфер
    EEPROM->EEDAT = data;                    // Загружаем записываемые данные в буфер
    EEPROM->EECON =                         // Запускаем процедуру с режимом записи
      EECON_EX_ByteMask | EECON_OP_Write | EECON_BWE_ByteMask;                  
  }

  inline void erase(const uint32_t address) {
    while (EEPROM->EESTA & EESTA_BSY_ByteMask); // Ожидаем готовность EEPROM
    EEPROM->EECON = EECON_BWE_ByteMask;        // Разрешаем запись в буфер
    EEPROM->EEA   = address;                  // Загружаем адресс стриаемой памяти в буфер
    EEPROM->EEDAT = 0x00;                    // Загружаем пустые данные в буфер
    EEPROM->EECON =                         // Запускаем процедуру с режимом очистки
      EECON_EX_ByteMask | EECON_OP_Erase | EECON_BWE_ByteMask;  
  }

  inline uint32_t read(const uint32_t address) {
    EEPROM->EEA = address;                       // Загружаем считываемый адрес в буфер
    while (EEPROM->EESTA & EESTA_BSY_ByteMask); // Ожидаем получения данных
    return EEPROM->EEDAT;                      // Возвращаем данные
  }
}

#endif /* _EEPROM_HPP_ */