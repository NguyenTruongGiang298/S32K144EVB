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
#include "nvic.h"
#include "Driver_NVIC.h"
#include "S32K144.h"

void NVIC_Init(void)
{
	NVIC_ClearPendingIRQ(LPSPI0_IRQn);
	NVIC_EnableIRQ(LPSPI0_IRQn);
	NVIC_SetPriority(LPSPI0_IRQn,2);
}
