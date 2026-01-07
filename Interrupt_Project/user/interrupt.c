/**
 * @file interrupt.c
 * @author Nguyễn Trường Giang
 * @brief Declare functions for interrupt and GPIO configuration
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "interrupt.h"
#include "Driver_NVIC.h"
#include "S32K144.h"

void NVICInit(void)
{
	NVIC_ClearPendingIRQ(PORTC_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);
	NVIC_SetPriority(PORTC_IRQn,5);
}
