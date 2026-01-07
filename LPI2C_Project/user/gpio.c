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
    IP_PCC->PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC(1);
    IP_PORTA->PCR[2]|=PORT_PCR_MUX(3); /* Port B17: MUX = ALT3, LPI2C0_SDA */
    IP_PORTA->PCR[3]|=PORT_PCR_MUX(3); /* Port B14: MUX = ALT3, LPI2C0_SCL */
}
