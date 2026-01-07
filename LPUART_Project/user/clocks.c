/**
 * @file clocks.c
 * @author Nguyễn Trường Giang
 * @brief Define functions for clocks and mode
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "clocks.h"
#include "S32K144.h"

void FIRCInit_48Mhz(void)
{
    IP_SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV1(1) | SCG_FIRCDIV_FIRCDIV2(1);    /* 48 Mhz, 24Mhz */
    IP_SCG->FIRCCFG = SCG_FIRCCFG_RANGE(0);
    while(IP_SCG->FIRCCSR & SCG_FIRCCSR_LK_MASK);
    IP_SCG->FIRCCSR = 0x00000001;
    while(((IP_SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK)>> SCG_FIRCCSR_FIRCVLD_SHIFT)!=1){}
}
void SPLLInit_160Mhz(void)
{
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
    IP_SCG->SPLLCSR = 0x00000000;
    IP_SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(1) | SCG_SPLLDIV_SPLLDIV2(2); /*160 Mhz, 80 Mhz */
    IP_SCG->SPLLCFG = 0x00000001;
    IP_SCG->SPLLCFG |= SCG_SPLLCFG_MULT(24) | SCG_SPLLCFG_PREDIV(5) | SCG_SPLLCFG_SOURCE;
    /* PREDIV=5: Divide SOSC_CLK by 6 */
    /* MULT=24:  Multiply SPLL by 40 */
    /* SPLL_CLK = 48MHz / 6 * 40 / 2 = 160 MHz */
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
    IP_SCG->SPLLCSR = 0x00000001;
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)>> SCG_SPLLCSR_SPLLVLD_SHIFT)!=1){}
}
void SetNormalRUNMode_80MHz(void)
{
    IP_SCG->RCCR = SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(1) | SCG_RCCR_DIVBUS(1) | SCG_RCCR_DIVSLOW(2);
    while((( IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) !=6){}
}
