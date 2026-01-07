#include "S32K144.h"
#include "clocks.h"
#include "gpio.h"
#include <stdio.h>
#include "lpi2c.h"

#define ADDRESS_WRITE (0xA0)
#define ADDRESS_READ (0xA1)
uint8_t g_FristAddress=0x12;
uint8_t g_SecondAddress=0x34;
uint8_t data=99;
uint8_t rx;

void Delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 8000; j++)
        {
            __asm("nop");
        }
    }
}
int main(void)
{
    FIRCInit_48Mhz();
    SPLLInit_160Mhz();
    SetNormalRUNMode_80MHz();
    PORTInit();
    LPI2C0_Init_Master();
    LPI2C0_Transmit_8bits(LPI2C_CMD_START_ADDR,ADDRESS_WRITE);
    LPI2C0_Transmit_8bits(LPI2C_CMD_TX_DATA,g_FristAddress);
    LPI2C0_Transmit_8bits(LPI2C_CMD_TX_DATA,g_SecondAddress);
    LPI2C0_Transmit_8bits(LPI2C_CMD_TX_DATA,data);
    LPI2C0_Transmit_8bits(LPI2C_CMD_STOP,0);
    Delay_ms(5);
    LPI2C0_Transmit_8bits(LPI2C_CMD_START_ADDR,ADDRESS_WRITE);
    LPI2C0_Transmit_8bits(LPI2C_CMD_TX_DATA,g_FristAddress);
    LPI2C0_Transmit_8bits(LPI2C_CMD_TX_DATA,g_SecondAddress);
    LPI2C0_Transmit_8bits(LPI2C_CMD_START_ADDR,ADDRESS_READ);
    rx = LPI2C0_Receive_8bits(LPI2C_CMD_RX_DATA);
    LPI2C0_Transmit_8bits(LPI2C_CMD_STOP,0);
    while(1)
    {

    }
    return 0;
}
