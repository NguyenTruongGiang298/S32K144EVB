/**
 * @file uart.h
 * @author Nguyễn Trường Giang
 * @brief Define functions for LPUART implementation
 * @version 0.1
 * @date 2025-11-13
 * @copyright Copyright (c) 2025
 */
#include "uart.h"
#include "S32K144.h"

void UART_Init_WithFIFO(void)
{
    IP_PCC->PCCn[PCC_LPUART1_INDEX] &=~PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(6)| PCC_PCCn_CGC_MASK;

    /* PTC6 as LPUART1_TX */
	IP_PORTC->PCR[6] = PORT_PCR_MUX(2);
	/* PTC7 as LPUART1_RX */
    IP_PORTC->PCR[7] = PORT_PCR_MUX(2);

    /* SOFTWARE RESET = 1*/
    IP_LPUART1->GLOBAL = LPUART_GLOBAL_RST(1);
    /* SOFTWARE RESET = 0*/
    IP_LPUART1->GLOBAL = 0;
    /* Clock Source Option = 6 (SPLL2_DIV2_CLK = 80 Mhz) */
    IP_LPUART1->BAUD = LPUART_BAUD_OSR(10) | LPUART_BAUD_SBR(63); /* 80Mhz / ((OSR+1)*SBR) */

    /* Setup FIFO */
    /* RXFIFOSIZE = 2: Receive FIFO Buffer Depth 8 Bytes */
    /* TXFIFOSIZE = 0 */
    /* RXFE = 1: Receive FIFO Enable */
    /* TXFE = 0: Transmit FIFO disable*/
    IP_LPUART1->FIFO = LPUART_FIFO_RXFE(1) | LPUART_FIFO_RXFIFOSIZE(2);
    /* RXWATER = 1: Receive Watermark compares at 4 bytes */
    IP_LPUART1->WATER = LPUART_WATER_RXCOUNT(1);
    IP_LPUART1->CTRL = LPUART_CTRL_RIE (1) | LPUART_CTRL_TE(1) |  LPUART_CTRL_RE(1);
}
void UART_Init(void)
{
    IP_PCC->PCCn[PCC_LPUART1_INDEX] &=~PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(6)| PCC_PCCn_CGC_MASK;

    /* PTC6 as LPUART1_TX */
	IP_PORTC->PCR[6] = PORT_PCR_MUX(2);
	/* PTC7 as LPUART1_RX */
    IP_PORTC->PCR[7] = PORT_PCR_MUX(2);

    /* SOFTWARE RESET = 1*/
    IP_LPUART1->GLOBAL = LPUART_GLOBAL_RST(1);
    /* SOFTWARE RESET = 0*/
    IP_LPUART1->GLOBAL = 0;
    /* Clock Source Option = 6 (SPLL2_DIV2_CLK = 80 Mhz) */
    IP_LPUART1->BAUD = LPUART_BAUD_OSR(10) | LPUART_BAUD_SBR(63); /* 80Mhz / ((OSR+1)*SBR) */

    /*  Transmission Complete Interrupt Enable TCIE = 1, buffer is empty and transmit completes  */
    /*  Receiver Interrupt Enable RIE = 1  */
    /*  Transmit Interrupt Enable TIE = 1, buffer is empty, but shift register is uncompleted */
    /*  Transmit Enable TE = 1  */
    /*  Receive Enable RE = 1   */
    IP_LPUART1->CTRL = LPUART_CTRL_RIE (1) | LPUART_CTRL_TE(1) |  LPUART_CTRL_RE(1);

    /*  Enables STAT[TDRE]  */
    /* PE, PT = 0: No hardware parity generation or checking */
    /* M7, M, R8T9, R9T8 = 0: 8-bit data characters */
    /* DOZEEN = 0: LPUART disable in Doze mode */
    /* TxDIR = 0: TxD pin is input if in single-wire mode */
    /* TXINV = 0: Transmit data not inverted */
    /* RWU, WAKE = 0: Normal operation; receiver not in standby */
    /* IDLCFG = 0: One idle character */
    /* ILT = 0: Idle char bit count starts after start bit */
    /* SBK = 0: Normal transmitter operation - no break char */
    /* LOOPS, RSRC = 0: No loop back */
}

/* FLAG */
/* RAF(READ): Receiver Active Flag, use to monitor the receiver detect idle + start bit */
/* TC(READ): Transmission Complete Flag, use to guarantee data transference completely */
/* TDRE(READ): Transmit Data Register Empty Flag, 0 full 1 empty  */
/* RDRF(READ) : Receive Data Register Full Flag, 0 empty 1 full */
void UARTTransmitChar(char send)
{
	while (!(IP_LPUART1->STAT & LPUART_STAT_TDRE_MASK));
    IP_LPUART1->DATA=send;
}

void UARTTransmitString(char data_string[])
{
    uint32_t i=0;
    while(data_string[i] != '\0')
    {
        UARTTransmitChar(data_string[i]);
        i++;
    }
}
char LPUART1_receive_char(void)
{
    return IP_LPUART1->DATA;;
}
