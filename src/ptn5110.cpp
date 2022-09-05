#include "ptn5110.h"

uint16_t PTN5110::get_register(uint8_t reg) {
  uint16_t buffer = 0;
  _i2c_port.read_from(_device_addr, reg, (uint8_t*)&buffer, 2);
  return buffer;
}

bool PTN5110::set_register(uint8_t reg, uint16_t value) {
  uint16_t buffer = 0;
  _i2c_port.write_to(_device_addr, reg, (uint8_t*)&value, 2);
  _i2c_port.read_from(_device_addr, reg, (uint8_t*)&buffer, 2);
  return buffer = value;
}

bool PTN5110::rx_usb_pd_msg(uint32_t len, uint8_t* buffer) {
return false;
}

bool PTN5110::tx_usb_pd_msg(uint32_t len, const uint8_t* buffer) {
return false;
}

void PTN5110::handle_alert() {
  if(_alert_delegate) {
    _alert_delegate->handle_alert();
  }
}
