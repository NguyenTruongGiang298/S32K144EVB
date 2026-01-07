/**
 * @file Hal_NVIC.h
 * @author Nguyễn Trường Giang
 * @brief Declare functions to config NVIC in hardware abtraction layer
 * @version 0.1
 * @date 2025-11-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef HAL_NVIC_H
#define HAL_NVIC_H
#include "S32K144.h"

#define NVIC_REGISTER_COUNT                      (15u)
#define NVIC_PRIORITY_COUNT                      (124u)
typedef struct
{
    __IO uint32_t ISER[NVIC_REGISTER_COUNT];      /*!< Offset: 0x000 (R/W) Interrupt Set Enable Register */
    __IO uint32_t ICER[NVIC_REGISTER_COUNT];      /*!< Offset: 0x080 (R/W) Interrupt Clear Enable Register */
    __IO uint32_t ISPR[NVIC_REGISTER_COUNT];      /*!< Offset: 0x100 (R/W) Interrupt Set Pending Register */
    __IO uint32_t ICPR[NVIC_REGISTER_COUNT];      /*!< Offset: 0x180 (R/W) Interrupt Clear Pending Register */
    __IO uint32_t IABR[NVIC_REGISTER_COUNT];      /*!< Offset: 0x200 (R/W) Interrupt Active Bit Register */
    __IO uint32_t  IPR[NVIC_PRIORITY_COUNT];       /*!< Offset: 0x300 (R/W) Interrupt Priority Register (8-bit wide) */
} NVIC_Type;

/* System Control Space Address*/
#define SCS_BASE     (0xE000E000UL)
#define IP_NVIC_BASE    (SCS_BASE +  0x0100UL)
#define IP_NVIC         ((NVIC_Type *) IP_NVIC_BASE)

/* System Control Block */
typedef struct
{
  __I  uint32_t CPUID;      /* Offset 0x000: CPUID Base Register */
  __IO uint32_t ICSR;       /* Offset 0x004: Interrupt Control and State */
  __IO uint32_t VTOR;       /* Offset 0x008: Vector Table Offset */
  __IO uint32_t AIRCR;      /* Offset 0x00C: App Interrupt and Reset Control */
  __IO uint32_t SCR;        /* Offset 0x010: System Control */
  __IO uint32_t CCR;        /* Offset 0x014: Configuration Control */
  __IO uint8_t  SHP[12];    /* Offset 0x018: System Handler Priority (4-15) */
  __IO uint32_t SHCSR;      /* Offset 0x024: System Handler Control and State */
  __IO uint32_t CFSR;       /* Offset 0x028: Configurable Fault Status */
  __IO uint32_t HFSR;       /* Offset 0x02C: HardFault Status */
  __IO uint32_t DFSR;       /* Offset 0x030: Debug Fault Status */
  __IO uint32_t MMFAR;      /* Offset 0x034: MemManage Fault Address */
  __IO uint32_t BFAR;       /* Offset 0x038: BusFault Address */
  __IO uint32_t AFSR;       /* Offset 0x03C: Auxiliary Fault Status */
  __I  uint32_t PFR[2];     /* Offset 0x040: Processor Feature */
  __I  uint32_t DFR;        /* Offset 0x048: Debug Feature */
  __I  uint32_t ADR;        /* Offset 0x04C: Auxiliary Feature */
  __I  uint32_t MMFR[4];    /* Offset 0x050: Memory Model Feature */
  __I  uint32_t ISAR[5];    /* Offset 0x060: Instruction Set Attributes */
        uint32_t RESERVED0[5];
  __IO uint32_t CPACR;      /* Offset 0x088: Coprocessor Access Control */
} SCB_Type;


#define IP_SCB_BASE    (SCS_BASE +  0x0D00UL)
#define IP_SCB         ((SCB_Type *) IP_SCB_BASE)

void __NVIC_EnableIRQ(IRQn_Type IRQn);
uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn);
void __NVIC_DisableIRQ(IRQn_Type IRQn);
uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn);
void __NVIC_SetPendingIRQ(IRQn_Type IRQn);
void __NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t __NVIC_GetActive(IRQn_Type IRQn);
void __NVIC_SetPriority(IRQn_Type IRQn,uint32_t priority);
uint32_t __NVIC_GetPriority(IRQn_Type IRQn);
void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector);
uint32_t __NVIC_GetVector(IRQn_Type IRQn);
void __NVIC_SystemReset(void);

#endif /* HAL_NVIC_H */
