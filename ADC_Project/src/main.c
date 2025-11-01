/* Copyright 2023 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"
#include "clocks.h"
#include "adc.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

#if defined (__ghs__)
    #define __INTERRUPT_SVC  __interrupt
    #define __NO_RETURN _Pragma("ghs nowarning 111")
#elif defined (__ICCARM__)
    #define __INTERRUPT_SVC  __svc
    #define __NO_RETURN _Pragma("diag_suppress=Pe111")
#elif defined (__GNUC__)
    #define __INTERRUPT_SVC  __attribute__ ((interrupt ("SVC")))
    #define __NO_RETURN
#else
    #define __INTERRUPT_SVC
    #define __NO_RETURN
#endif
#define PTD0  0U
#define PTD15 15U
#define PTD16 16U
#define ADC_CHANNEL 2U
int counter, accumulator = 0, limit_value = 1000000;
uint32_t u32_gAdc_Value;

int main(void) {
	SOSCInit_8Mhz();   			/* Initialize system oscillator for 8 MHz xtal					*/
	SPLLInit_160Mhz();			/* Initialize SPLL to 160 MHz with 8 MHz SOSC 					*/
	SetNormalRUNMode_80MHz(); 	/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash 	*/
	PORTInit();     			/* Init port clocks and gpio outputs 							*/
	ADCInit(ADC_CHANNEL);		/* Init ADC_init(); 											*/

	for(;;) {
	    while(ADConversionCompleted()==0){}   		/* Wait for conversion complete flag */
	    u32_gAdc_Value = ReadADC();   				/* Get channel's conversion results  */
	    if (u32_gAdc_Value > 3750) {
	    	IP_PTD->PSOR |= (1<<PTD0) | (1<<PTD16);
	      	IP_PTD->PCOR |= (1<<PTD15);
	    }
	    else if (u32_gAdc_Value > 2500) {
	    	IP_PTD->PSOR |= (1<<PTD0) | (1<<PTD15);
	    	IP_PTD->PCOR |= (1<<PTD16);
	    }
	    else if (u32_gAdc_Value >1250) {
	    	IP_PTD->PSOR |= (1<<PTD15) | (1<<PTD16);
	      	IP_PTD->PCOR |= (1<<PTD0);
	    }
	    else {
	    	IP_PTD->PSOR |= (1<<PTD0) | (1<< PTD15) | (1<<PTD16);
	    }
	  }


    counter = 0;
    for (;;) {
        counter++;

        if (counter >= limit_value) {
            __asm volatile ("svc 0");
            counter = 0;
        }
    }
    /* to avoid the warning message for GHS and IAR: statement is unreachable*/
    __NO_RETURN
    return 0;
}

__INTERRUPT_SVC void SVC_Handler() {
    accumulator += counter;
    printf("counter is 0x%08x, accumulator is 0x%08x\n", counter, accumulator);
}
