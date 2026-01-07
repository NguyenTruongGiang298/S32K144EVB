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

void PORTInit(void)
{
	/* GPIO Section: Enable clock for PORTC */
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
	IP_PORTD->PCR[PTD0]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD15]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD16]= PORT_PCR_MUX(1);
	IP_PTD->PDDR |= (1<<PTD0 | 1<<PTD15 | 1<<PTD16);
    /* UART Section: Enable clock for PORTC */
	IP_PCC->PCCn[PCC_PORTC_INDEX ]|=PCC_PCCn_CGC_MASK;
    IP_PORTC->PCR[6]|=PORT_PCR_MUX(2);	/* Port C6: MUX = ALT2, UART1 RX */
    IP_PORTC->PCR[7]|=PORT_PCR_MUX(2);
}
