#ifndef _PIN_HPP_
#define _PIN_HPP_

#include <GPIO.hpp>
#include <APB.hpp>


struct PinStruct {
  GpioPort* port;
  uint8_t   pinNumber;
  uint32_t  clkMask;
};


enum {
  // Состояния пина
  LOW  = 0,
  HIGH = 1,

  // Режимы работы
  OUTPUT = 1,
  INPUT  = 0
};


class Pin {
public:
  inline Pin(PinStruct pin, const uint8_t mode) : _pin(pin) {
    Gpio::setClocking(_pin.clkMask, true);
    Gpio::setMode(_pin.port, _pin.pinNumber, mode);
  }

  inline void set(const uint8_t state) {
    Gpio::setState(_pin.port, _pin.pinNumber, state);
  }

private:
  PinStruct _pin;
};


// Пины порта №0
static const PinStruct PIN_0_0  = { GPIO_0, 0,  CLK_GPIO_0 };
static const PinStruct PIN_0_1  = { GPIO_0, 1,  CLK_GPIO_0 };
static const PinStruct PIN_0_2  = { GPIO_0, 2,  CLK_GPIO_0 };
static const PinStruct PIN_0_3  = { GPIO_0, 3,  CLK_GPIO_0 };
static const PinStruct PIN_0_4  = { GPIO_0, 4,  CLK_GPIO_0 };
static const PinStruct PIN_0_5  = { GPIO_0, 5,  CLK_GPIO_0 };
static const PinStruct PIN_0_6  = { GPIO_0, 6,  CLK_GPIO_0 };
static const PinStruct PIN_0_7  = { GPIO_0, 7,  CLK_GPIO_0 };
static const PinStruct PIN_0_8  = { GPIO_0, 8,  CLK_GPIO_0 };
static const PinStruct PIN_0_9  = { GPIO_0, 9,  CLK_GPIO_0 };
static const PinStruct PIN_0_10 = { GPIO_0, 10, CLK_GPIO_0 };
static const PinStruct PIN_0_11 = { GPIO_0, 11, CLK_GPIO_0 };
static const PinStruct PIN_0_12 = { GPIO_0, 12, CLK_GPIO_0 };
static const PinStruct PIN_0_13 = { GPIO_0, 13, CLK_GPIO_0 };
static const PinStruct PIN_0_14 = { GPIO_0, 14, CLK_GPIO_0 };


// Пины порта №1
static const PinStruct PIN_1_0  = { GPIO_1, 0,  CLK_GPIO_1 };
static const PinStruct PIN_1_1  = { GPIO_1, 1,  CLK_GPIO_1 };
static const PinStruct PIN_1_2  = { GPIO_1, 2,  CLK_GPIO_1 };
static const PinStruct PIN_1_3  = { GPIO_1, 3,  CLK_GPIO_1 };
static const PinStruct PIN_1_4  = { GPIO_1, 4,  CLK_GPIO_1 };
static const PinStruct PIN_1_5  = { GPIO_1, 5,  CLK_GPIO_1 };
static const PinStruct PIN_1_6  = { GPIO_1, 6,  CLK_GPIO_1 };
static const PinStruct PIN_1_7  = { GPIO_1, 7,  CLK_GPIO_1 };
static const PinStruct PIN_1_8  = { GPIO_1, 8,  CLK_GPIO_1 };
static const PinStruct PIN_1_9  = { GPIO_1, 9,  CLK_GPIO_1 };
static const PinStruct PIN_1_10 = { GPIO_1, 10, CLK_GPIO_1 };
static const PinStruct PIN_1_11 = { GPIO_1, 11, CLK_GPIO_1 };
static const PinStruct PIN_1_12 = { GPIO_1, 12, CLK_GPIO_1 };


// Пины порта №2
static const PinStruct PIN_2_3  = { GPIO_2, 3,  CLK_GPIO_2 };
static const PinStruct PIN_2_4  = { GPIO_2, 4,  CLK_GPIO_2 };
static const PinStruct PIN_2_5  = { GPIO_2, 5,  CLK_GPIO_2 };
static const PinStruct PIN_2_6  = { GPIO_2, 6,  CLK_GPIO_2 };
static const PinStruct PIN_2_7  = { GPIO_2, 7,  CLK_GPIO_2 };

#endif /* _PIN_HPP_ */