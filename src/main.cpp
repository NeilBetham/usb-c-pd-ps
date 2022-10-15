#include "registers/rcc.h"
#include "registers/gpio.h"
#include "registers/flash.h"
#include "registers/exti.h"
#include "registers/syscfg.h"
#include "registers/core.h"

#include "i2c.h"
#include "ptn5110.h"
#include "usb_pd_controller.h"
#include "status_light.h"
#include "output_en.h"

I2C ptn5110_i2c(1);
PTN5110 ptn5110(ptn5110_i2c, 0x52);
USBPDController controller(ptn5110);
bool read_pending = false;

void ExternInterrupt_15_4_ISR(void) {
  read_pending = true;
  NVIC_ICPR |= BIT_7;
  EXTI_PR |= BIT_7;
}


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
  ptn5110_i2c.init();

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

  // Init status light
  status_light::init();
  status_light::set_color(1, 1, 1);

  // Init the output enable line
  output_en::init();

  // Setup alert GPIO interrupt
  RCC_APB2ENR |= BIT_0;
  GPIO_A_MODER &= ~(0x0000C000); // PA7 Input mode
  EXTI_IMR |= BIT_7;  // Unmask EXTI line 7
  EXTI_FTSR |= BIT_7;  // Falling edge detection
  SYSCFG_EXTICR2 &= ~(0x0000F000);  // Interrupt 7 reads from PA7
  NVIC_ISER |= BIT_7;
  asm("CPSIE i");

  controller.init();

  while(true) {
    asm("WFE");

    if(read_pending)  {
      controller.handle_alert();
      read_pending = false;
    }
  }

  return 0;
}
