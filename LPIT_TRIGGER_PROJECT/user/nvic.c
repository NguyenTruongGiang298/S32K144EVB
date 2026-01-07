/**
 * @file nvic.c
 * @author Nguyễn Trường Giang
 * @brief  Define initialization functions for NVIC
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "nvic.h"
#include "Driver_NVIC.h"
#include "S32K144.h"
void NVIC_Init(void)
{
//	NVIC_ClearPendingIRQ(LPIT0_Ch0_IRQn);
//	NVIC_EnableIRQ(LPIT0_Ch0_IRQn);
//	NVIC_SetPriority(LPIT0_Ch0_IRQn,3);
	NVIC_ClearPendingIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(ADC0_IRQn);
	NVIC_SetPriority(ADC0_IRQn,3);
}
