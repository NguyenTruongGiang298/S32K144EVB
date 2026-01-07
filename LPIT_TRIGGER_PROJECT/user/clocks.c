/**
 * @file   clocks_and_mode.c
 * @author Nguyễn Trường Giang
 * @brief  Define Clock configuration functions for S32K144
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "clocks.h"
#include "S32K144.h"

/* 48Mhz */
void FIRC_Init(void)
{
    IP_SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV1(1) | SCG_FIRCDIV_FIRCDIV2(1);
    IP_SCG->FIRCCFG = SCG_FIRCCFG_RANGE(0);
    while(IP_SCG->FIRCCSR & SCG_FIRCCSR_LK_MASK);
    IP_SCG->FIRCCSR = 0x00000001;
    while(((IP_SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK)>> SCG_FIRCCSR_FIRCVLD_SHIFT)!=1){}
}
void SPLLInit_128Mhz(void)
{
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
    IP_SCG->SPLLCSR = 0x00000000;
    IP_SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(0) | SCG_SPLLDIV_SPLLDIV2(3);
    IP_SCG->SPLLCFG = SCG_SPLLCFG_MULT(16) | SCG_SPLLCFG_PREDIV(5) | SCG_SPLLCFG_SOURCE;
    /* PREDIV=5: Divide FIRC_CLK by 6 */
    /* MULT=16:  Multiply SPLL by 32 */
    /* VCO_CLK = 48MHz /6 * 32 = 256 MHz, SPLL_CLK = 128 MHz */
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
    IP_SCG->SPLLCSR = 0x00000001;
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)>> SCG_SPLLCSR_SPLLVLD_SHIFT)!=1){}
}
void RUNMode_64MHz(void)
{
    IP_SCG->RCCR = SCG_RCCR_SCS(3) | SCG_RCCR_DIVCORE(1) | SCG_RCCR_DIVBUS(3) | SCG_RCCR_DIVSLOW(5);
    while((( IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) !=3){}    /* Enable */
}
