/**
 * @file gpio.c
 * @author Nguyễn Trường Giang
 * @brief Define a GPIO Initialization Function
 * @version 0.1
 * @date 2025-11-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "gpio.h"
#include "S32K144.h"

void PORTC_Init(void)
{
    IP_PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC(1);
    IP_PORTC->PCR[0]|=PORT_PCR_MUX(3); /* Port B17: MUX = ALT3, LPSPI2_SIN */
    IP_PORTC->PCR[1]|=PORT_PCR_MUX(3); /* Port B14: MUX = ALT3, LPSPI1_SOUT */
    IP_PORTC->PCR[15]|=PORT_PCR_MUX(3); /* Port B15: MUX = ALT3, LPSPI2_SCK */
    IP_PORTC->PCR[14]|=PORT_PCR_MUX(3); /* Port B16: MUX = ALT3, LPSPI2_PSC0 */
}
void PORTB_Init(void)
{
    IP_PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC(1);
    IP_PORTB->PCR[3]|=PORT_PCR_MUX(3); /* Port B3: MUX = ALT3, LPSPI0_SIN */
    IP_PORTB->PCR[4]|=PORT_PCR_MUX(3); /* Port B4: MUX = ALT3, LPSPI0_SOUT */
    IP_PORTB->PCR[2]|=PORT_PCR_MUX(3); /* Port B2: MUX = ALT3, LPSPI0_SCK */
    IP_PORTB->PCR[0]|=PORT_PCR_MUX(3); /* Port B0: MUX = ALT3, LPSPI0_PSC0 */
}
