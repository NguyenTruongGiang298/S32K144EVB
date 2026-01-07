/**
 * @file port.c
 * @author Nguyễn Trường Giang
 * @brief Define functions for port initialization
 * @version 0.1
 * @date 2025-11-03
 *
 * @copyright Copyright (c) 2025
 */
#include "port.h"
#include "S32K144.h"
void PORTInit(void)
{
    IP_PCC->PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC(1);
    IP_PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC(1);

	IP_PORTD->PCR[PTD0]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD15]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD16]= PORT_PCR_MUX(1);
    IP_PTD->PDDR |= (1<<PTD0 | 1<<PTD15 | 1<<PTD16);

	IP_PORTC->PCR[PTC12]= PORT_PCR_MUX(1) | PORT_PCR_IRQC(9) | PORT_PCR_PFE(1);
	IP_PORTC->PCR[PTC13]= PORT_PCR_MUX(1) | PORT_PCR_IRQC(9) | PORT_PCR_PFE(1);
	IP_PTC->PDDR &= ~(1<<PTC12 | 1<<PTC13);
}
