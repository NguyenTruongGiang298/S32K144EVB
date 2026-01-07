#include "S32K144.h"
#include "clocks.h"
#include <stdio.h>
#include "gpio.h"
#include "lpspi.h"
#include "nvic.h"
#include "w25q16.h"
#include <string.h>

uint8_t id[3];
uint8_t tx_data[16] = "HELLO";
uint8_t rx_data[16];

int main(void)
{
	FIRCInit_48Mhz();
    SPLLInit_160Mhz();
    SetNormalRUNMode_80MHz();
    LPSPI0_Init_Master();
    PORTB_Init();
    NVIC_Init();
    W25Q_ReadID(id);
    W25Q_WritePage(0x001122, tx_data,strlen("HELLO"));
    W25Q_WaitBusy();
    W25Q_Read(0x001122, rx_data, 16);
    while(1)
    {

    }
    return 0;
}

