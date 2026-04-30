#include <ARGENTIX.hpp>

int main(void) {
  Pin led(PIN_1_5, OUTPUT);

  while (1) {
    led.set(HIGH);
    delay(300);
    led.set(LOW);
    delay(300);
  }
}