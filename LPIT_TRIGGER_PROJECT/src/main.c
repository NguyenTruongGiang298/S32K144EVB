#include "S32K144.h"
#include "clocks.h"
#include "gpio.h"
#include "adc.h"
#include "lpit.h"
#include <stdio.h>
#include <stdint.h>
#include "nvic.h"
#include "trigger.h"

#define ADC_IN2 2U
#define PTD0  0U
#define PTD15 15U
#define PTD16 16U

int counter=0;

//void LPIT0_Ch0_IRQHandler(void)
//{
//    if ((IP_LPIT0 -> MSR & LPIT_MSR_TIF0_MASK) == LPIT_MSR_TIF0_MASK)
//	{
//	    /* Clear LPIT0 Timeout Flag Channel 0 (W1C) */
//		IP_LPIT0 -> MSR |= LPIT_MSR_TIF0_MASK;
//		counter++;
//	}
//}
volatile uint32_t g_Adc_Value;
void ADC0_IRQHandler(void)
{
	/* Wait for conversion complete flag */
	counter++;
	if(ADConversionCompleted())
	{
		/* Get channel's conversion results  */
		g_Adc_Value = ReadADC();
		if (g_Adc_Value > 3750)
		{
			IP_PTD->PSOR |= (1<<PTD0) | (1<<PTD16);
			IP_PTD->PCOR |= (1<<PTD15);
		}
		else if (g_Adc_Value > 2500)
		{
			IP_PTD->PSOR |= (1<<PTD0) | (1<<PTD15);
			IP_PTD->PCOR |= (1<<PTD16);
		}
		else if (g_Adc_Value >1250)
		{
			IP_PTD->PSOR |= (1<<PTD15) | (1<<PTD16);
			IP_PTD->PCOR |= (1<<PTD0);
		}
		else
		{
			IP_PTD->PSOR |= (1<<PTD0) | (1<< PTD15) | (1<<PTD16);
		}
	}
}
int main(void)
{
    FIRC_Init();
    SPLLInit_128Mhz();
    RUNMode_64MHz();
    GpioInit();
    ADCInit();
    TRGMUX_Config();
    LpitInit(144000000);
    NVIC_Init();
    while(1)
    {

	}
    return 0;
}
