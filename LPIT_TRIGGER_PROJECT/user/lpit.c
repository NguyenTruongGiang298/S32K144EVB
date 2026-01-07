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

void LpitInit(uint32_t counter)
{
    IP_PCC->PCCn[PCC_LPIT_INDEX] &=~ PCC_PCCn_CGC_MASK;
    /* Peripheral functional clock: FIRCDVI2_CLK= 48 MHz*/
    IP_PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC(1) | PCC_PCCn_PCS(3);

    /* MODULE CLOCK REGISTER */
    /* DBG_EN = 0: Timer channels stop in Debug mode */
    /* DOZE_EN = 0: Timer channels are stopped in DOZE mode */
    /* SW_RST = 1: SW RST reset timer channels and registers */
    /* M_CEN = 1: Enable module clock (allows writing other LPIT0 registers) */
    IP_LPIT0->MCR = LPIT_MCR_M_CEN(1);
    /* set counter */
    IP_LPIT0->TMR[TIMER_CHANNEL_0].TVAL =counter;

    /* TIE0 = 1: Timer Interrupt Enabled for Channel 0 */
    IP_LPIT0->MIER = LPIT_MIER_TIE0(1);

    /* CHAIN = 0: Channel chaining is disabled */
    /* Channel 0 Timeout period =  1s */
    /* MODE = 0: 32 Periodic counter mode */
    IP_LPIT0->TMR[TIMER_CHANNEL_0].TCTRL = LPIT_TMR_TCTRL_TRG_SRC(1) |  LPIT_TMR_TCTRL_MODE(0) | LPIT_TMR_TCTRL_TRG_SEL(0);

    /* SET T_EN_0 = 1: Timer channel 0 is enabled */
    IP_LPIT0->SETTEN = LPIT_SETTEN_SET_T_EN_0(1);

    /* T_EN_0 = 1: START TIMER */
    IP_LPIT0->TMR[TIMER_CHANNEL_0].TCTRL |= LPIT_TMR_TCTRL_T_EN(1);
}
