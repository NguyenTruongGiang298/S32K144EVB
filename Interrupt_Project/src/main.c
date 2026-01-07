#include "S32K144.h"
#include "clocks.h"
#include "interrupt.h"
#include "port.h"
#include <stdio.h>

int main(void)
{
    SOSCInit_8Mhz();
    SPLLInit_160Mhz();
    SetNormalRUNMode_80MHz();
    PORTInit();
    NVICInit();
    while(1)
    {

    }
    return 0;
}
void PORTC_IRQHandler(void)
{
    if (IP_PORTC->ISFR & (1 << PTC12))
    {
        IP_PORTC->ISFR |= (1 << PTC12);
        IP_PTD->PSOR |=(1<<PTD16 | 1<<PTD0 | 1<<PTD15);
    }
    else if (IP_PORTC->ISFR & (1 << PTC13))
    {
        IP_PORTC->ISFR |= (1 << PTC13);
        IP_PTD->PCOR |= (1<<PTD16);
        IP_PTD->PSOR |= (1<<PTD0 | 1<<PTD15);
    }
}
