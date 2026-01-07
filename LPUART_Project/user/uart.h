/**
 * @file uart.h
 * @author Nguyễn Trường Giang
 * @brief Declare functions for LPUART implementation
 * @version 0.1
 * @date 2025-11-13
 * @copyright Copyright (c) 2025
 */
#ifndef UART_H
#define UART_H

void UART_Init(void);
void UART_Init_WithFIFO(void);
void UARTTransmitChar(char send);
void UARTTransmitString(char data_string[]);
char LPUART1_receive_char(void);
#endif /* UART_H */
