/**
 * @file Hal_NVIC.c
 * @author Nguyễn Trường Giang
 * @brief Define functions to config NVIC in hardware abtraction layer
 * @version 0.1
 * @date 2025-11-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Hal_NVIC.h"
#include "S32K144.h"

void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
	/* This points out ISERx */
    uint8_t index = IRQn/32;

    /* 7 Resigers ISER(ISER0->ISER7) in Cortex-M4, each register has 32 bit */
    if(index <= 7)
    {
    	/* Interrupt Set Enable Register = 1 */
    	/* 5 bits for 32 values: 0x1F = 0001 1111 & interrupt index = correct bit in register ISERx */
    	IP_NVIC->ISER[index] |= (1U << (IRQn & 0x1F));
    }
}
uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
    uint8_t index = IRQn/32;
    uint32_t res;
    if(index <= 7)
    {
    	res = IP_NVIC->ISER[index] & (1U << (IRQn & 0x1F));
    }
    return res;
}
void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
    uint8_t index = IRQn/32;
    if(index <= 7)
    {
    	/* Interrupt clear enable register = 1 */
    	IP_NVIC->ICER[index] |= (1U << (IRQn & 0x1F));
    }
}
uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    uint8_t index = IRQn/32;
    uint32_t res;
    if(index <= 7)
    {
    	res = IP_NVIC->ISPR[index] & (1U << (IRQn & 0x1F));
    }
    return res;
}
void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    uint8_t index = IRQn/32;
    if(index <= 7)
    {
    	/* Interrupt set pending register = 1 */
    	IP_NVIC->ISPR[index] |= (1U << (IRQn & 0x1F));
    }
}
void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    uint8_t index = IRQn/32;
    if(index <= 7)
    {
    	/* Interrupt clear pending register = 1 */
    	IP_NVIC->ICPR[index] |= (1U << (IRQn & 0x1F));
    }
}

/* Check status of Interrupt, Stack frame push, Program counter jumps into Handler */
uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
    uint8_t index = IRQn/32;
    uint32_t res;
    if(index <= 7)
    {
    	/* Interrupt active bit register*/
        res = IP_NVIC->IABR[index] & (1U << (IRQn & 0x1F));
    }
    return res;
}
void __NVIC_SetPriority(IRQn_Type IRQn,uint32_t priority)
{
    /* 1 Priority register for 4 IRQ, at 64 IPR for 256 IRQ*/
    uint8_t index = IRQn / 4;
    /* Nx = 0-3 */
    uint8_t PRI_Nx = IRQn % 4;
    /* Clear priority */
    IP_NVIC->IPR[index] &= ~(0xFF << (PRI_Nx*8));
    /* Cortex - M4 uses 4 bits priority*/
    IP_NVIC->IPR[index] |= ( (priority << (8 - __NVIC_PRIO_BITS)) << (PRI_Nx*8));
}
uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{
    uint8_t index = IRQn / 4;
    uint8_t PRI_Nx = (IRQn % 4) * 8;
    uint32_t priority = (IP_NVIC->IPR[index] >> PRI_Nx) & 0xFF;
    return (priority >> (8 - __NVIC_PRIO_BITS));
}
void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
    uint32_t *vectors = (uint32_t *)IP_SCB->VTOR;
    vectors[IRQn] = vector;
}
uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
    uint32_t *vectors = (uint32_t *)IP_SCB->VTOR;
    return vectors[IRQn];
}
void __NVIC_SystemReset(void)
{
    IP_SCB->AIRCR = (0x5FAUL << 16U) | (IP_SCB->AIRCR & 0x700UL)| (1<<2U);
    while (1);
}
