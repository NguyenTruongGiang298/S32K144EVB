/**
 * @file Driver_NVIC.h
 * @author Nguyễn Trường Giang
 * @brief Declare api for NVIC driver
 * @version 0.1
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef DRIVER_NVIC_H
#define DRIVER_NVIC_H

#include "stdint.h"
#include "Hal_NVIC.h"

#define OUT_OF_VECTOR_TABLE 123
void NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t NVIC_ClearTargetState(IRQn_Type IRQn);
void NVIC_DecodePriority(uint32_t Priority,uint32_t PriorityGroup,uint32_t * pPreemptPriority,uint32_t * pSubPriority);
void NVIC_DisableIRQ(IRQn_Type IRQn);
void NVIC_EnableIRQ(IRQn_Type IRQn);
uint32_t NVIC_EncodePriority(uint32_t PriorityGroup,uint32_t PreemptPriority,uint32_t SubPriority);
uint32_t NVIC_GetActive(IRQn_Type IRQn);
uint32_t NVIC_GetEnableIRQ(IRQn_Type IRQn);
uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn);
uint32_t NVIC_GetPriority(IRQn_Type IRQn);
uint32_t NVIC_GetPriorityGrouping(void );
uint32_t NVIC_GetTargetState(IRQn_Type IRQn);
uint32_t NVIC_GetVector(IRQn_Type IRQn);
void NVIC_SetPendingIRQ(IRQn_Type IRQn);
void NVIC_SetPriority(IRQn_Type IRQn,uint32_t priority);
void NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t NVIC_SetTargetState(IRQn_Type IRQn);
void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector);
void NVIC_SystemReset(void);


#endif /* DRIVER_NVIC_H */
