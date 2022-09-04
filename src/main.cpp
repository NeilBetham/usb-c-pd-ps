#include "registers/rcc.h"
#include "registers/gpio.h"
#include "registers/flash.h"

int main() {
  // Up main clock frequency
  // Turn off PLL and wait for it be ready
  RCC_CR &= ~(BIT_24);
  while(RCC_CR & BIT_25);

  // Enable the high speed interal oscillator
  RCC_CR |= BIT_0;
  while(RCC_CR & BIT_2);

  // Set pll source, multiplier and divisior
  RCC_CFGR &= ~BIT_16;
  RCC_CFGR &= ~(0xF << 18);
  RCC_CFGR |= (0x1 << 18);
  RCC_CFGR &= ~(0x3 << 22);
  RCC_CFGR |= (0x1 << 22);

  // Set flash wait states
  FLASH_ACR |= 0x1;

  // Enable PLL
  RCC_CR |= BIT_24;
  while(RCC_CR & BIT_25);

  // Switch system clock to PLL
  RCC_CFGR |= (0x3 << 0);

  // Setup GPIO for blinken lights
  RCC_IOPENR |= 0x0000009F;
  GPIO_A_MODER  = 0xEB555505;
  GPIO_A_OTYPER |= 0x00000013;
  GPIO_A_ODR   = 0x00000013;

  while(1) {
    GPIO_A_ODR = (~(GPIO_A_ODR & 0x00000013)) & 0x00000013;
    for(uint32_t i = 0; i < 500000; i++);
  }

  return 0;
}
