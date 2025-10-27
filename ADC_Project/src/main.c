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

void SOSCInit_8Mhz(void)
{
	IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
	IP_SCG->SOSCCFG = SCG_SOSCCFG_EREFS(1) | SCG_SOSCCFG_HGO(0) | SCG_SOSCCFG_RANGE(2);
	while(IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);
	IP_SCG->SOSCCSR = 0x00000001;
	while(((IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)>> SCG_SOSCCSR_SOSCVLD_SHIFT)!=1){}
}
void SPLLInit_160Mhz(void)
{
	while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
	IP_SCG->SPLLCSR = 0x00000000;
	IP_SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(2) | SCG_SPLLDIV_SPLLDIV2(3);
	IP_SCG->SPLLCFG = SCG_SPLLCFG_MULT(8) | SCG_SPLLCFG_PREDIV(0);
	/* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
    /* MULT=24:  Multiply SPLL by 4+24=40 */
    /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
	while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
	IP_SCG->SPLLCSR = 0x00000001;
	while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)>> SCG_SPLLCSR_SPLLVLD_SHIFT)!=1){}
}
void SetNormalRUNMode_80MHz(void)
{
	IP_SCG->RCCR = SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(1) | SCG_RCCR_DIVBUS(2) | SCG_RCCR_DIVSLOW(3);
	while((( IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) !=6){}
}
void delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 3000; j++);
}

void PORTInit(void)
{
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
	IP_PORTD->PCR[PTD0]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD15]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[PTD16]= PORT_PCR_MUX(1);
	IP_PTD->PDDR |= (1<<PTD0 | 1<<PTD15 | 1<<PTD16);
}

void ADCInit(uint16_t ADC_Channel)
{
	IP_PCC->PCCn[PCC_ADC0_INDEX] = PCC_PCCn_CGC(0);
	IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1) | PCC_PCCn_CGC(1);

	IP_ADC0->SC1[0] = ADC_SC1_ADCH(0X1F) | ADC_SC1_AIEN(0);

	IP_ADC0->CFG1   = ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(1);

	IP_ADC0->CFG2 	= ADC_CFG2_SMPLTS(12);

	IP_ADC0->SC2  	= ADC_SC2_ADTRG(0) | ADC_SC2_REFSEL(0);

	IP_ADC0->SC3  	= ADC_SC3_AVGE(1) | ADC_SC3_AVGS(3);
	IP_ADC0->SC3   |= ADC_SC3_CAL(1);                /* calibration */
	while (IP_ADC0->SC3 & ADC_SC3_CAL_MASK);

	IP_ADC0->SC3 |= ADC_SC3_ADCO(1);
	IP_ADC0->SC1[0] = ADC_SC1_ADCH(ADC_Channel);
}

uint32_t ReadADC(void)
{
	uint16_t u16_ADC_result = IP_ADC0->R[0];
	return (uint32_t)(u16_ADC_result * 5000 / 0xFFF);
}

uint8_t ADConversionCompleted(void)
{
	return ((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT);
}
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
