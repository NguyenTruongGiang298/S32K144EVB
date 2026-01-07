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
#include <nvic.h>
#include "Driver_NVIC.h"
#include "S32K144.h"

void NVIC_Init(void)
{
	NVIC_ClearPendingIRQ(LPUART1_RxTx_IRQn);
	NVIC_EnableIRQ(LPUART1_RxTx_IRQn);
	NVIC_SetPriority(LPUART1_RxTx_IRQn,2);
}
