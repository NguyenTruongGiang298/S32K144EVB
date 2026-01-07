#include "S32K144.h"
#include "clocks.h"
#include "uart.h"
#include "gpio.h"
#include "nvic.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define RX_BUF_SIZE 128
#define TX_BUF_SIZE 128

char Rx_buf[RX_BUF_SIZE];
char Tx_buf[TX_BUF_SIZE];

uint8_t g_rx_idx = 0;
uint8_t g_tx_idx = 0;
volatile  uint8_t g_rx_done = 0;

void String_Append(uint8_t *idx, char* buffer,uint8_t buffer_size,const uint8_t ch)
{
	 if(*idx < buffer_size-1)
	 {
		 buffer[*idx]=ch;
		 (*idx)++;
		 buffer[*idx]='\0';
	 }
}
void UART_SendString_IT(char* str)
{
	g_tx_idx=0;
	memset(Tx_buf,(char)0,TX_BUF_SIZE);
	strncpy(Tx_buf, str, TX_BUF_SIZE);
	Tx_buf[TX_BUF_SIZE-1] = '\0';
    IP_LPUART1->CTRL |= LPUART_CTRL_TIE(1);
}
void LPUART1_RxTx_IRQHandler(void)
{
    uint32_t status = IP_LPUART1->STAT;
	if (status & LPUART_STAT_RDRF_MASK)
	{
		char ch = LPUART1_receive_char();
		if (ch == '\n')
		{
			Rx_buf[g_rx_idx] = '\n';
			g_rx_done = 1;
		}
		else
		{
			String_Append(&g_rx_idx, Rx_buf, sizeof(Rx_buf), ch);
		}
	}
	if (status & LPUART_STAT_TDRE_MASK)
	{
		if (Tx_buf[g_tx_idx] != '\0')
		{
			UARTTransmitChar(Tx_buf[g_tx_idx++]);
		}
		else
		{
			/* disable interrupt */
			IP_LPUART1->CTRL &=~LPUART_CTRL_TIE_MASK;
		}
	}
}
int main(void)
{
	FIRCInit_48Mhz();
    SPLLInit_160Mhz();
    SetNormalRUNMode_80MHz();
    NVIC_Init();
    PORT_Init();
    Gpio_Init();
    //UART_Init();
    UART_Init_WithFIFO();
    while (1)
    {
		if (g_rx_done)
		{
		    UART_SendString_IT(Rx_buf);
		    g_rx_idx = 0;
		    g_rx_done = 0;
			memset(Rx_buf,(char)0,RX_BUF_SIZE);
		}
    }
    return 0;
}



