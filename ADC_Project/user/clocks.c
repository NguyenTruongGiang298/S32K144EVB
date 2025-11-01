/**
 * @file clocks.c
 * @author your name (you@domain.com)
 * @brief Define Clock configuration functions for S32K144
 * @version 0.1
 * @date 2025-11-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "S32K144.h"

void SOSCInit_8Mhz(void)
{
    IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
    IP_SCG->SOSCCFG = SCG_SOSCCFG_EREFS(1) | SCG_SOSCCFG_HGO(0) | SCG_SOSCCFG_RANGE(2);
    while(IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);
    IP_SCG->SOSCCSR = 0x00000001;
    while(((IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)>> SCG_SOSCCSR_SOSCVLD_SHIFT)!=1){}
}
void SPLLInit_160Mhz(void)
{
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
    IP_SCG->SPLLCSR = 0x00000000;
    IP_SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(2) | SCG_SPLLDIV_SPLLDIV2(3);
    IP_SCG->SPLLCFG = SCG_SPLLCFG_MULT(8) | SCG_SPLLCFG_PREDIV(0);
    /* PREDIV=0: Divide SOSC_CLK by 1+1=2 */
    /* MULT=24:  Multiply SPLL by 16+24=40 */
    /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
    IP_SCG->SPLLCSR = 0x00000001;
    while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)>> SCG_SPLLCSR_SPLLVLD_SHIFT)!=1){}
}
void SetNormalRUNMode_80MHz(void)
{
    IP_SCG->RCCR = SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(1) | SCG_RCCR_DIVBUS(2) | SCG_RCCR_DIVSLOW(3);
    while((( IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) !=6){}
}