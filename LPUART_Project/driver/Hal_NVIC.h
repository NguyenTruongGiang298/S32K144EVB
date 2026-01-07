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

#define SCS_BASE     (0xE000E000UL)
#define IP_NVIC_BASE    (SCS_BASE +  0x0100UL)
#define IP_NVIC         ((NVIC_Type *) IP_NVIC_BASE)

typedef struct
{
  __IO uint32_t VTOR;
  __IO uint32_t AIRCR;
}SCB_Type;
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
void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t __NVIC_GetPriorityGrouping(void);
void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector);
uint32_t __NVIC_GetVector(IRQn_Type IRQn);
void __NVIC_SystemReset(void);

#endif /* HAL_NVIC_H */