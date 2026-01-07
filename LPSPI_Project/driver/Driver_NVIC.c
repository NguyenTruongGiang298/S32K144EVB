/**
 * @file Driver_NVIC.c
 * @author Nguyễn Trường Giang
 * @brief Define api for NVIC driver
 * @version 0.1
 * @date 2025-11-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Driver_NVIC.h"
#include "stdint.h"

void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    if(IRQn <= 122)
    {
        __NVIC_ClearPendingIRQ(IRQn);
    }
}
void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    if(IRQn <= 122)
    {
        __NVIC_DisableIRQ(IRQn);
    }
}
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if(IRQn <= 122)
    {
        __NVIC_EnableIRQ(IRQn);
    }
}

uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
    if(IRQn > 122)
    {
        return OUT_OF_VECTOR_TABLE;
    }
    return __NVIC_GetActive(IRQn);
}
uint32_t NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
    if(IRQn > 122)
    {
        return OUT_OF_VECTOR_TABLE;
    }
    return __NVIC_GetEnableIRQ(IRQn);
}
uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    if(IRQn > 122)
    {
        return OUT_OF_VECTOR_TABLE;
    }
    return __NVIC_GetPendingIRQ(IRQn);
}
uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{
    if(IRQn > 122)
    {
        return OUT_OF_VECTOR_TABLE;
    }
    return __NVIC_GetPriority(IRQn);
}

uint32_t NVIC_GetVector(IRQn_Type IRQn)
{
    if(IRQn > 122)
    {
        return OUT_OF_VECTOR_TABLE;
    }
    return __NVIC_GetVector(IRQn);
}
void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    if(IRQn <= 122)
    {
        __NVIC_SetPendingIRQ(IRQn);
    }
}
void NVIC_SetPriority(IRQn_Type IRQn,uint32_t priority)
{
    if(IRQn <= 122)
    {
        __NVIC_SetPriority(IRQn,priority);
    }
}
void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
    if(IRQn <= 122)
    {
        __NVIC_SetVector(IRQn,vector);
    }
}
void NVIC_SystemReset(void)
{
    __NVIC_SystemReset();
}
