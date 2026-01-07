/*
 * PORT_MCAL.c
 *
 *  Created on: Oct 23, 2025
 *      Author: truon
 */

#include <Hal_PORT.h>
#include "S32K144.h"
void ClockEnable(void)
{
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
	IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1);
}
