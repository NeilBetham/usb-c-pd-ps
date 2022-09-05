/**
 * @brief Manages a connected PTN5110 USB C PD PHY
 */

#include "i2c.h"

#pragma once


class PTN5110 {
public:
  PTN5110(I2C& i2c_port): _i2c_port(i2c_port) {};

  void init();

  uint16_t get_register(uint8_t reg);
  bool set_register(uint8_t reg, uint16_t mask);

  bool rx_usb_pd_msg(uint32_t len, uint8_t* buffer);
  bool tx_usb_pd_msg(uint32_t len, const uint8_t* buffer);

  // This should be called from an ISR
  void handle_alert();

private:
  I2C& _i2c_port;
  uint8_t _message_counter = 0;
};
