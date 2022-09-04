#include "i2c.h"

#include "registers/i2c.h"
#include "registers/rcc.h"

void I2C::init() {
  // First set the base address for accessing the different registers
  switch(_i2c_number) {
  case 1:
    _base_addr = I2C_1_BASE;
    break;
  case 2:
    _base_addr = I2C_2_BASE;
    break;
  case 3:
    _base_addr = I2C_3_BASE;
    break;
  }

  // Setup the clock source
  switch(_i2c_number) {
  case 1:
    RCC_CCIPR &= ~(BIT_12 | BIT_13);
    RCC_CCIPR |= BIT_13;
    break;
  case 2:
    // In this case the PLL is the source of the I2C2 clock
    break;
  case 3:
    RCC_CCIPR &= ~(BIT_16 | BIT_17);
    RCC_CCIPR |= BIT_17;
    break;
  }

  // Enable the clock to the I2C peripheral
  switch(_i2c_number) {
  case 1:
    RCC_APB1ENR |= BIT_21;
    break;
  case 2:
    RCC_APB1ENR |= BIT_22;
    break;
  case 3:
    RCC_APB1ENR |= BIT_30;
    break;
  }

  // Setup the prescaler and hold times
  switch(_i2c_number) {
  case 1:
    // Assumes a 16 mhz clock source
    I2C_1_TIMINGR &= (BIT_27 | BIT_26 | BIT_25 | BIT_24);
    I2C_1_TIMINGR |= 0x4;  // SCLL
    I2C_1_TIMINGR |= 0x2 << 8; // SCLH
    I2C_1_TIMINGR |= 0x2 << 20l; // SCLDEL
    break;
  case 2:
    // Assumes a 16 mhz clock source
    I2C_2_TIMINGR &= (BIT_27 | BIT_26 | BIT_25 | BIT_24);
    I2C_2_TIMINGR |= 0x4;  // SCLL
    I2C_2_TIMINGR |= 0x2 << 8; // SCLH
    I2C_2_TIMINGR |= 0x2 << 20l; // SCLDEL
    break;
  case 3:
    // Assumes a 16 mhz clock source
    I2C_3_TIMINGR &= (BIT_27 | BIT_26 | BIT_25 | BIT_24);
    I2C_3_TIMINGR |= 0x4;  // SCLL
    I2C_3_TIMINGR |= 0x2 << 8; // SCLH
    I2C_3_TIMINGR |= 0x2 << 20l; // SCLDEL
    break;
  }

  // Set 7 bit address mode
  switch(_i2c_number) {
  case 1:
    I2C_1_CR2 &= ~(BIT_11);
    break;
  case 2:
    I2C_2_CR2 &= ~(BIT_11);
    break;
  case 3:
    I2C_3_CR2 &= ~(BIT_11);
    break;
  }

  // Enable the peripheral
  switch(_i2c_number) {
  case 1:
    I2C_1_CR1 &= ~(BIT_0);
    break;
  case 2:
    I2C_2_CR1 &= ~(BIT_0);
    break;
  case 3:
    I2C_3_CR1 &= ~(BIT_0);
    break;
  }
}

int I2C::write_to(uint8_t addr, uint8_t reg, const uint8_t* data, uint32_t len) {
  return 0;
}

int I2C::read_from(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len) {
  return 0;
}


