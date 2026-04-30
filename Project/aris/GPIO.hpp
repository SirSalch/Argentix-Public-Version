#ifndef _GPIO_HPP_
#define _GPIO_HPP_

#include <stdint.h>
#include <APB.hpp>


// Базовые адреса портов
#define GPIO_0_BASE 0x00084000
#define GPIO_1_BASE 0x00084400
#define GPIO_2_BASE 0x00084800

// Структура регисторв порта GPIO
struct GpioPort {
  volatile uint32_t STATE;
  volatile uint32_t CLEAR;
  volatile uint32_t DIRECTION_OUT;
  volatile uint32_t DIRECTION_IN;
  volatile uint32_t OUTPUT;
  volatile uint32_t CONTROL;
};

// Порты GPIO
#define GPIO_0 ((GpioPort*)GPIO_0_BASE)
#define GPIO_1 ((GpioPort*)GPIO_1_BASE)
#define GPIO_2 ((GpioPort*)GPIO_2_BASE)


// Битовые маски GPIO
enum {
  // Режимы работы
  GPIO_INPUT  = 0,
  GPIO_OUTPUT = 1,
};


namespace Gpio {
  inline void setClocking(const uint32_t clkMask, const bool state) {
    (state ? APB->CLK_PERIPHERY_SET : APB->CLK_PERIPHERY_CLEAR) = clkMask;
  }

  inline void setMode(GpioPort* port, const uint8_t pinNumber ,const uint8_t mode) {
    switch(mode) {
      case GPIO_OUTPUT: port->DIRECTION_OUT = (1 << pinNumber); break;
      case GPIO_INPUT:  port->DIRECTION_IN  = (1 << pinNumber);
    }
  }
  
  inline void setState(GpioPort* port, const uint8_t pinNumber, const bool state) {
    (state ? port->STATE : port->CLEAR) = 1 << pinNumber;
  }
}

#endif /* _GPIO_HPP_ */