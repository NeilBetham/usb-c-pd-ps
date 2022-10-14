#include "output_en.h"

#include "registers/rcc.h"
#include "registers/gpio.h"


namespace output_en {


void init() {
  RCC_IOPENR |= BIT_0;
  GPIO_A_MODER  &= ~(0x00000C00);
  GPIO_A_MODER  |=   0x00000400;
  GPIO_A_OTYPER &= ~(BIT_5);
  GPIO_A_ODR    &= ~(BIT_5);
}

void set_state(bool enabled) {
  if(enabled) {
    GPIO_A_ODR |= BIT_5;
  } else {
    GPIO_A_ODR &= ~(BIT_5);
  }
}



} // namespace output_en
