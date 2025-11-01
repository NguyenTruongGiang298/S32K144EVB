/**
 * @file lpit.c
 * @author your name (you@domain.com)
 * @brief Define set-up functions for low periodic interrupt timer(LPIT)
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "lpit.h"
#include "S32K144.h"
#include "stdint.h"
static void delay_us(uint32_t us)
{
    uint32_t cycles = 64/ 4; /* 4 machine cycles for 1 for-loop */
    for (volatile uint32_t i = 0; i < us * cycles; i++);
}

void LpitInit(void)
{
    IP_PCC->PCCn[PCC_LPIT_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_CGC(1) | PCC_PCCn_PCS(3);
    IP_LPIT0->MCR = LPIT_MCR_M_CEN(1) | LPIT_MCR_SW_RST(1);
    delay_us(4);
    IP_LPIT0->TMR[TIMER_CHANNEL0].TCTRL = LPIT_TMR_TCTRL_TRG_SRC(1);
    IP_LPIT0->SETTEN = LPIT_SETTEN_SET_T_EN_0(1);
    IP_LPIT0->TMR[TIMER_CHANNEL0].TVAL = LPIT_TMR_TVAL_TMR_VAL(31999999);   /* set counter */
    // IP_LPIT0->MSR = LPIT_MSR_TIF0(1);
    IP_LPIT0->MIER = LPIT_MIER_TIE0(1);
    IP_LPIT0->TMR[TIMER_CHANNEL0].TCTRL = LPIT_TMR_TCTRL_T_EN(1);
    // IP_LPIT0->CLRTEN = LPIT_CLRTEN_CLR_T_EN_0(1);
}
