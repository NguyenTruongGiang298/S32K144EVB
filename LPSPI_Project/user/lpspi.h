/**
 * @file lpsip.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-11-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LPSPI_H_
#define LPSPI_H_
#include <stdint.h>

#define BUSY 1
#define NOT_BUSY 0
void LPSPI0_Init_Master (void);
uint8_t LPSPI0_Check_Status(void);
void Reset_FIFO_Memory(void);
void LPSPI0_Transmit_8bits(uint8_t data);
uint8_t LPSPI0_Receive_8bits (void);
void LPSPI0_4bitMode_enable (void);
void Turn_Off_ContinousTransfer(void);
void Turn_On_ContinousTransfer(void);

#endif /* LPSPI_H_ */
