/**
 * @brief Reset and clock control registers
 */

#include "registers/helpers.h"

#pragma once

#define RCC_BASE             0x40021000

#define RCC_CR_OFFSET        0x00000000
#define RCC_ICSCR_OFFSET     0x00000004
#define RCC_CFGR_OFFSET      0x0000000C
#define RCC_CIER_OFFSET      0x00000010
#define RCC_CIFR_OFFSET      0x00000014
#define RCC_CICR_OFFSET      0x00000018
#define RCC_IOPRSTR_OFFSET   0x0000001C
#define RCC_AHBRSTR_OFFSET   0x00000020
#define RCC_APB2RSTR_OFFSET  0x00000024
#define RCC_APB1RSTR_OFFSET  0x00000028
#define RCC_IOPENR_OFFSET    0x0000002C
#define RCC_AHBENR_OFFSET    0x00000030
#define RCC_APB2ENR_OFFSET   0x00000034
#define RCC_APB1ENR_OFFSET   0x00000038
#define RCC_IOPSMENR_OFFSET  0x0000003C
#define RCC_AHBSMENR_OFFSET  0x00000040
#define RCC_APB2SMENR_OFFSET 0x00000044
#define RCC_APB1SMENR_OFFSET 0x00000048
#define RCC_CCIPR_OFFSET     0x0000004C
#define RCC_CSR_OFFSET       0x00000050

#define RCC_CR        REGISTER(RCC_BASE + RCC_CR_OFFSET)
#define RCC_ICSCR     REGISTER(RCC_BASE + RCC_ICSCR_OFFSET)
#define RCC_CFGR      REGISTER(RCC_BASE + RCC_CFGR_OFFSET)
#define RCC_CIER      REGISTER(RCC_BASE + RCC_CIER_OFFSET)
#define RCC_CIFR      REGISTER(RCC_BASE + RCC_CIFR_OFFSET)
#define RCC_CICR      REGISTER(RCC_BASE + RCC_CICR_OFFSET)
#define RCC_IOPRSTR   REGISTER(RCC_BASE + RCC_IOPRSTR_OFFSET)
#define RCC_AHBRSTR   REGISTER(RCC_BASE + RCC_AHBRSTR_OFFSET)
#define RCC_APB2RSTR  REGISTER(RCC_BASE + RCC_APB2RSTR_OFFSET)
#define RCC_APB1RSTR  REGISTER(RCC_BASE + RCC_APB1RSTR_OFFSET)
#define RCC_IOPENR    REGISTER(RCC_BASE + RCC_IOPENR_OFFSET)
#define RCC_AHBENR    REGISTER(RCC_BASE + RCC_AHBENR_OFFSET)
#define RCC_APB2ENR   REGISTER(RCC_BASE + RCC_APB2ENR_OFFSET)
#define RCC_APB1ENR   REGISTER(RCC_BASE + RCC_APB1ENR_OFFSET)
#define RCC_IOPSMENR  REGISTER(RCC_BASE + RCC_IOPSMENR_OFFSET)
#define RCC_AHBSMENR  REGISTER(RCC_BASE + RCC_AHBSMENR_OFFSET)
#define RCC_APB2SMENR REGISTER(RCC_BASE + RCC_APB2SMENR_OFFSET)
#define RCC_APB1SMENR REGISTER(RCC_BASE + RCC_APB1SMENR_OFFSET)
#define RCC_CCIPR     REGISTER(RCC_BASE + RCC_CCIPR_OFFSET)
#define RCC_CSR       REGISTER(RCC_BASE + RCC_CSR_OFFSET)


