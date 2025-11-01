/**
 * @file gpio.c
 * @author your name (you@domain.com)
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
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
	IP_PORTD->PCR[PTD0]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD15]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD16]= PORT_PCR_MUX(1);
	IP_PTD->PDDR |= (1<<PTD0 | 1<<PTD15 | 1<<PTD16);
}