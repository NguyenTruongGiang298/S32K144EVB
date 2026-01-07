#include "S32K144.h"
#include "clocks.h"
#include "adc.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

#define PTD0  0U
#define PTD15 15U
#define PTD16 16U
#define ADC_CHANNEL 2U

uint32_t g_AdcValue;

int main(void)
{
	/* Initialize system oscillator for 8 MHz xtal					*/
	SOSCInit_8Mhz();
	/* Initialize SPLL to 160 MHz with 8 MHz SOSC 					*/
	SPLLInit_160Mhz();
	/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash 	*/
	SetNormalRUNMode_80MHz();
	/* Init port clocks and gpio outputs 							*/
	PORTInit();
	/* Init ADC_init(); 											*/
	ADCInit();
	/* Start ADC channel */
    ADCChannelConversion(ADC_CHANNEL);
	while(1)
	{
		/* Wait for conversion complete flag */
        while(ADConversionCompleted()==0){}

	    /* Get channel's conversion results  */
	    g_AdcValue = ReadADC();

	    if (g_AdcValue > 3750)
	    {
	    	IP_PTD->PSOR |= (1<<PTD0) | (1<<PTD16);
	      	IP_PTD->PCOR |= (1<<PTD15);
	    }
	    else if (g_AdcValue > 2500)
	    {
	    	IP_PTD->PSOR |= (1<<PTD0) | (1<<PTD15);
	    	IP_PTD->PCOR |= (1<<PTD16);
	    }
	    else if (g_AdcValue >1250)
	    {
	    	IP_PTD->PSOR |= (1<<PTD15) | (1<<PTD16);
	      	IP_PTD->PCOR |= (1<<PTD0);
	    }
	    else
	    {
	    	IP_PTD->PSOR |= (1<<PTD0) | (1<< PTD15) | (1<<PTD16);
	    }
	  }
    return 0;
}
