#include "registers/rcc.h"
#include "registers/gpio.h"
#include "registers/flash.h"

#include "i2c.h"

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
  I2C ptn5110(1);
  ptn5110.init();

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

  // Check the vendor ID for the PTN5110
  const uint8_t ptn5110_addr = 0x52;
  uint8_t buffer[2];

  for(uint8_t index = 0; index < 100; index++);

  ptn5110.read_from(ptn5110_addr, 0, buffer, 2);

  uint8_t alert_mask[2] = {0xFF, 0x7F};
  ptn5110.write_to(ptn5110_addr, 0x12, alert_mask, 2);

  for(uint8_t index = 0; index < 10; index++);

  ptn5110.read_from(ptn5110_addr, 0x12, alert_mask, 2);


  // Setup GPIO for blinken lights
  GPIO_A_MODER  &= ~(0x0000030F);
  GPIO_A_MODER  |= 0x00000105;
  GPIO_A_OTYPER |= 0x00000013;
  GPIO_A_ODR   = 0x00000013;

  if(buffer[0] == 0xC9 && buffer[1] == 0x1F) {
    GPIO_A_ODR &= ~(BIT_3 | BIT_1);
  }

  while(1) {
//    GPIO_A_ODR = (~(GPIO_A_ODR & 0x00000013)) & 0x00000013;
    for(uint32_t i = 0; i < 2000000; i++);
  }

  return 0;
}
