/**
 * @brief I2C Control Registers
 */

#include "registers/helpers.h"

#pragma once


#define I2C_1_BASE 0x40005400
#define I2C_2_BASE 0x40005800
#define I2C_3_BASE 0x40007800

#define I2C_CR1_OFFSET      0x00000000
#define I2C_CR2_OFFSET      0x00000004
#define I2C_OAR1_OFFSET     0x00000008
#define I2C_OAR2_OFFSET     0x0000000C
#define I2C_TIMINGR_OFFSET  0x00000010
#define I2C_TIMEOUTR_OFFSET 0x00000014
#define I2C_ISR_OFFSET      0x00000018
#define I2C_ICR_OFFSET      0x0000001C
#define I2C_PECR_OFFSET     0x00000020
#define I2C_RXDR_OFFSET     0x00000024
#define I2C_TXDR_OFFSET     0x00000028


#define I2C_1_CR1      REGISTER(I2C_1_BASE + I2C_CR1_OFFSET)
#define I2C_1_CR2      REGISTER(I2C_1_BASE + I2C_CR2_OFFSET)
#define I2C_1_OAR1     REGISTER(I2C_1_BASE + I2C_OAR1_OFFSET)
#define I2C_1_OAR2     REGISTER(I2C_1_BASE + I2C_OAR1_OFFSET)
#define I2C_1_TIMINGR  REGISTER(I2C_1_BASE + I2C_TIMINGR_OFFSET)
#define I2C_1_TIMEOUTR REGISTER(I2C_1_BASE + I2C_TIMEOUTR_OFFSET)
#define I2C_1_ISR      REGISTER(I2C_1_BASE + I2C_ISR_OFFSET)
#define I2C_1_ICR      REGISTER(I2C_1_BASE + I2C_ICR_OFFSET)
#define I2C_1_PECR     REGISTER(I2C_1_BASE + I2C_PECR_OFFSET)
#define I2C_1_RXDR     REGISTER(I2C_1_BASE + I2C_RXDR_OFFSET)
#define I2C_1_TXDR     REGISTER(I2C_1_BASE + I2C_TXDR_OFFSET)


#define I2C_2_CR1      REGISTER(I2C_2_BASE + I2C_CR1_OFFSET)
#define I2C_2_CR2      REGISTER(I2C_2_BASE + I2C_CR2_OFFSET)
#define I2C_2_OAR1     REGISTER(I2C_2_BASE + I2C_OAR1_OFFSET)
#define I2C_2_OAR2     REGISTER(I2C_2_BASE + I2C_OAR1_OFFSET)
#define I2C_2_TIMINGR  REGISTER(I2C_2_BASE + I2C_TIMINGR_OFFSET)
#define I2C_2_TIMEOUTR REGISTER(I2C_2_BASE + I2C_TIMEOUTR_OFFSET)
#define I2C_2_ISR      REGISTER(I2C_2_BASE + I2C_ISR_OFFSET)
#define I2C_2_ICR      REGISTER(I2C_2_BASE + I2C_ICR_OFFSET)
#define I2C_2_PECR     REGISTER(I2C_2_BASE + I2C_PECR_OFFSET)
#define I2C_2_RXDR     REGISTER(I2C_2_BASE + I2C_RXDR_OFFSET)
#define I2C_2_TXDR     REGISTER(I2C_2_BASE + I2C_TXDR_OFFSET)


#define I2C_3_CR1      REGISTER(I2C_3_BASE + I2C_CR1_OFFSET)
#define I2C_3_CR2      REGISTER(I2C_3_BASE + I2C_CR2_OFFSET)
#define I2C_3_OAR1     REGISTER(I2C_3_BASE + I2C_OAR1_OFFSET)
#define I2C_3_OAR2     REGISTER(I2C_3_BASE + I2C_OAR1_OFFSET)
#define I2C_3_TIMINGR  REGISTER(I2C_3_BASE + I2C_TIMINGR_OFFSET)
#define I2C_3_TIMEOUTR REGISTER(I2C_3_BASE + I2C_TIMEOUTR_OFFSET)
#define I2C_3_ISR      REGISTER(I2C_3_BASE + I2C_ISR_OFFSET)
#define I2C_3_ICR      REGISTER(I2C_3_BASE + I2C_ICR_OFFSET)
#define I2C_3_PECR     REGISTER(I2C_3_BASE + I2C_PECR_OFFSET)
#define I2C_3_RXDR     REGISTER(I2C_3_BASE + I2C_RXDR_OFFSET)
#define I2C_3_TXDR     REGISTER(I2C_3_BASE + I2C_TXDR_OFFSET)

