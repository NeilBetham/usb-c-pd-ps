#include "registers/rcc.h"
#include "registers/gpio.h"
#include "registers/flash.h"

#include "i2c.h"
#include "ptn5110.h"

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

  // Setup the I2C peripheral
  I2C ptn5110_i2c(1);
  ptn5110_i2c.init();
  PTN5110 ptn5110(ptn5110_i2c, 0x52);

  // Enable IO Port A
  RCC_IOPENR |= 0x0000009F;

  // Setup GPIO A 9/10 for I2C 1
  GPIO_A_AFRH    &= ~(0x000000FF << 4);
  GPIO_A_AFRH     |= (0x00000011 << 4);

  GPIO_A_MODER   &= ~(0x0000000F << 18);
  GPIO_A_MODER    |= (0x0000000A << 18);

  GPIO_A_OSPEEDR &= ~(0x0000000F << 18);
  GPIO_A_OSPEEDR  |= (0x0000000F << 18);

  GPIO_A_PUPDR   &= ~(0x0000000F << 18);
  GPIO_A_PUPDR    |= (0x00000005 << 18);

  GPIO_A_OTYPER   |= (0x00000003 << 9);

  // Setup GPIO for blinken lights
  GPIO_A_MODER  &= ~(0x0000030F);
  GPIO_A_MODER  |= 0x00000105;
  GPIO_A_OTYPER |= 0x00000013;
  GPIO_A_ODR   = 0x00000013;

  if(ptn5110.get_register(0) == 0x1FC9) {
    GPIO_A_ODR &= ~BIT_4;
  }

  if(ptn5110.get_register(2) == 0x5110) {
    GPIO_A_ODR &= ~BIT_1;
  }

  if(ptn5110.get_register(4) == 0x0004) {
    GPIO_A_ODR &= ~BIT_0;
  }

  uint16_t alert_register = ptn5110.get_register(0x10);
  uint16_t pow_stat_register = ptn5110.get_register(0x70);

  return 0;
}
