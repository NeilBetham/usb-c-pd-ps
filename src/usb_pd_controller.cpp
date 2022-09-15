#include "usb_pd_controller.h"

// PD Control Message Types
#define PD_MSG_TYPE_GOODCRC     0b0001
#define PD_MSG_TYPE_GOTOMIN     0b0010
#define PD_MSG_TYPE_ACCEPT      0b0011
#define PD_MSG_TYPE_REJECT      0b0100
#define PD_MSG_TYPE_PING        0b0101
#define PD_MSG_TYPE_PS_RDY      0b0110
#define PD_MSG_TYPE_GET_SRC_CAP 0b0111
#define PD_MSG_TYPE_GET_SNK_CAP 0b1000
#define PD_MSG_TYPE_DR_SWAP     0b1001
#define PD_MSG_TYPE_PR_SWAP     0b1010
#define PD_MSG_TYPE_VCONN_SWAP  0b1011
#define PD_MSG_TYPE_WAIT        0b1100
#define PD_MSG_TYPE_SOFT_RESET  0b1101

// PD Data Message Types
#define PD_MSG_TYPE_SRC_CAPS 0b0001
#define PD_MSG_TYPE_REQUEST  0b0010
#define PD_MSG_TYPE_BIST     0b0011
#define PD_MSG_TYPE_SNK_CAPS 0b0100
#define PD_MSG_TYPE_VND_DEF  0b1111

struct PACKED PDMsgHeader  {
  uint8_t message_type: 4;
  uint8_t : 1;
  uint8_t port_data_role: 1;
  uint8_t spec_rev: 2;
  uint8_t power_port_role: 1;
  uint8_t message_id: 3;
  uint8_t num_data_obj: 3;
  uint8_t : 1;
};


// Capability Defs
#define PD_CAP_TYPE_FIXED 0b00
#define PD_CAP_TYPE_BATT  0b01
#define PD_CAP_TYPE_VAR   0b10

struct PACKED SourceCapsFixedPDO {
  uint16_t max_current_10ma: 10;
  uint16_t voltage_50mv: 10;
  uint8_t peak_current: 2;
  uint8_t : 3;
  uint8_t dual_role_data: 1;
  uint8_t usb_comm_cap: 1;
  uint8_t uncon_power: 1;
  uint8_t suspend_sup: 1;
  uint8_t dual_role_power: 1;
  uint8_t supply_type: 2;
};

struct PACKED SourceCapsBattPDO {
  uint16_t max_power_250mw: 10;
  uint16_t min_voltage_50mv: 10;
  uint16_t max_voltage_50mv: 10;
  uint8_t  supply_type: 2;
};

struct PACKED SourceCapsVarPDO {
  uint16_t max_current_10ma: 10;
  uint16_t min_voltage_50mv: 10;
  uint16_t max_voltage_50mv: 10;
  uint8_t  supply_type: 2;
};

// Request Defs
struct PACKED RequestFixVarPDO {
  uint16_t max_current_10ma: 10;
  uint16_t op_current_10ma: 10;
  uint8_t : 4;
  uint8_t no_usb_sus: 1;
  uint8_t usb_comm_cap: 1;
  uint8_t cap_missmatch: 1;
  uint8_t give_back: 1;
  uint8_t object_pos: 3;
  uint8_t :1;
};

struct PACKED RequestBattPDO {
  uint16_t max_power_250mw: 10;
  uint16_t op_power_250mw: 10;
  uint8_t : 4;
  uint8_t no_usb_sus: 1;
  uint8_t usb_comm_cap: 1;
  uint8_t cap_missmatch: 1;
  uint8_t give_back: 1;
  uint8_t object_pos: 3;
  uint8_t :1;
};

// Phy Register Defines
#define PHY_REG_VENDOR_ID           0x00
#define PHY_REG_PROD_ID             0x02
#define PHY_REG_DEV_ID              0x04
#define PHY_REG_TC_REV              0x06
#define PHY_REG_PD_REV              0x08
#define PHY_REG_PD_INTER_REV        0x0A
#define PHY_REG_ALERT               0x10
#define PHY_REG_ALERT_MASK          0x12
#define PHY_REG_POWER_STAT_MASK     0x14
#define PHY_REG_FAULT_STAT_MASK     0x15
#define PHY_REG_EXT_STAT_MASK       0x16
#define PHY_REG_ALERT_EXT_STAT_MASK 0x17
#define PHY_REG_CONF_STD_OUTPUT     0x18
#define PHY_REG_TCPC_CTL            0x19
#define PHY_REG_ROLE_CTL            0x1A
#define PHY_REG_FAULT_CTL           0x1B
#define PHY_REG_POWER_CTL           0x1C
#define PHY_REG_CC_STAT             0x1D
#define PHY_REG_POWER_STAT          0x1E
#define PHY_REG_FAULT_STAT          0x1F
#define PHY_REG_EXT_STAT            0x20
#define PHY_REG_ALERT_EXT_STAT      0x21
#define PHY_REG_COMMAND             0x23
#define PHY_REG_DEVICE_CAPS_1       0x24
#define PHY_REG_DEVICE_CAPS_2       0x26
#define PHY_REG_STD_IN_CAPS         0x28
#define PHY_REG_STD_OUT_CAPS        0x29
#define PHY_REG_CONF_EXT_1          0x2A
#define PHY_REG_GEN_TIMER           0x2C
#define PHY_REG_MSG_HDR_INFO        0x2E
#define PHY_REG_RECV_DETECT         0x2F
#define PHY_REG_READ_BYTE_COUNT     0x30
#define PHY_REG_TRANSMIT            0x50
#define PHY_REG_I2C_WRITE_COUNT     0x51
#define PHY_REG_VBUS_VOLTAGE        0x70
#define PHY_REG_VBUS_SNK_DISCON_THR 0x72
#define PHY_REG_VBUS_STOP_DISCH_THR 0x74
#define PHY_REG_VBUS_V_ALRM_HI_CONF 0x76
#define PHY_REG_VBUS_V_ALRM_LO_CONF 0x78
#define PHY_REG_VBUS_HV_TARGET      0x7A
#define PHY_REG_EXT_CFG_ID          0x80
#define PHY_REG_EXT_ALERT           0x82
#define PHY_REG_EXT_ALERT_MASK      0x84
#define PHY_REG_EXT_CONF            0x86
#define PHY_REG_EXT_FAULT_CONF      0x88
#define PHY_REG_EXT_CTL             0x8E
#define PHY_REG_EXT_STAT            0x90
#define PHY_REG_EXT_GPIO_CONF       0x92
#define PHY_REG_EXT_GPIO_CTL        0x93
#define PHY_REG_EXT_GPIO_ALERT_CONF 0x94
#define PHY_REG_EXT_GPIO_STAT       0x96
#define PHY_REG_SRC_HV_MB4B_TIME    0x97
#define PHY_REG_ADC_FILT_CTL_1      0x9A
#define PHY_REG_ADC_FILT_CTL_2      0x9B
#define PHY_REG_VCONN_CONF          0x9C
#define PHY_REG_VCONN_FLT_DEBNC     0x9D
#define PHY_REG_VCONN_FLT_RECOV     0x9E
#define PHY_REG_VCONN_FLT_ATTMP     0x9F


void USBPDController::init() {
  // Perform an initial checkin with the PHY and clear any alerts
  uint16_t alert_status = _phy.get_register(PHY_REG_ALERT);
  uint16_t cc_status    = _phy.get_register(PHY_REG_CC_STAT);
  _phy.set_register(PHY_REG_ALERT, 0xFFFF);

  if(alert_status & BIT_2) {
    // A message was received and needs to be processed
  }

  // Configure the PHY
  _phy.set_register(PHY_REG_ROLE_CTL, 0x2A);  // Sink only @ 3A
  _phy_set_register(PHY_REG_RECV_DETECT, BIT_0 | BIT_5);


}
