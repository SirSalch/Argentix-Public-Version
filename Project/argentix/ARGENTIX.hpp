#ifndef _ARGENTIX_HPP_
#define _ARGENTIX_HPP_

// Подключение Драйверов ARIS (Argentix RISC-V Interface Standard)
#include <EEPROM.hpp>
#include <APB.hpp>
#include <GPIO.hpp>
#include <SYS_TIMER.hpp>

// Подключение стандартных библиотек ARGENTIX
#include <Pin.hpp>


inline void delay(const uint32_t time) {
  SysTimer::start();
  while (SYS_TIMER->VALUE < (time * 32000));
}

#endif /* _ARGENTIX_HPP_ */