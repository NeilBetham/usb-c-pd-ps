/**
 * @brief Handle the implementation and management of the USB PD protocol
 */

#include "ptn5110.h"

#pragma once


class USBPDController : public AlertDelegate {
public:
  USBPDController(PTN5110& phy) : _phy(phy) {
    _phy.set_delegate(this);
  };
  ~USBPDController() {
    _phy.set_delegate(NULL);
  }


  void init();

  // AlertDelegate
  void handle_alert();

private:
  PTN5110& _phy;

};
