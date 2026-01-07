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

volatile  uint8_t count = 0;
uint8_t g_rx_idx = 0;
uint8_t g_tx_idx = 0;

void String_Append(uint8_t *idx, char* buffer,uint8_t buffer_size,const uint8_t ch)
{
	 if(*idx < buffer_size-1)
	 {
		 buffer[*idx]=ch;
		 (*idx)++;
		 buffer[*idx]='\0';
	 }
}
void LPUART1_RxTx_IRQHandler(void)
{
    uint32_t status = IP_LPUART1->STAT;
	if (status & LPUART_STAT_RDRF_MASK)
	{
//		char ch = LPUART1_receive_char();
//		String_Append(&g_rx_idx, Rx_buf, sizeof(Rx_buf), ch);
        count = (IP_LPUART1->WATER & LPUART_WATER_RXCOUNT_MASK) >> LPUART_WATER_RXCOUNT_SHIFT;
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
    UART_Init_WithFIFO();
    while (1)
    {

    }
    return 0;
}



