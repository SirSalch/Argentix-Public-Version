#ifndef _SYSTEM_TIMER_
#define _SYSTEM_TIMER_

#include <stdint.h>
#include <APB.hpp>


// Базовый адрес системного таймера
#define SYS_TIMER_BASE 0x00050800

// Структура регисторв системного таймера
struct SysTimer_Regs {
  volatile uint32_t VALUE;
  volatile uint32_t TOP;
  volatile uint32_t PRESCALER;
  volatile uint32_t CONTROL;
  volatile uint32_t ENABLE;
  volatile uint32_t INT_MASK;
  volatile uint32_t INT_CLEAR;
  volatile uint32_t INT_FLAG;
};

// Системный таймер
#define SYS_TIMER ((SysTimer_Regs*)SYS_TIMER_BASE)


namespace SysTimer {
  inline void setClocking(const bool state) {
    (state ? APB->CLK_MAIN_SET : APB->CLK_MAIN_CLEAR) = CLK_SYS_TIMER;
  }

  inline void start() {
    SYS_TIMER->ENABLE = (1 << 0) | (1 << 1);
  }

  inline void reset() {
    SYS_TIMER->ENABLE = 1 << 1;
  }

  inline const uint32_t getValue() {
    return SYS_TIMER->VALUE;
  }
}

#endif /* _SYSTEM_TIMER_ */