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

// #define PCC_PORTD_INDEX 76 ~ id of port D

#define PTD0 0 // BLUE
#define PTD15 15 // RED
#define PTD16 16 // GREEN
#define PCC_PORTD_INDEX 76



// delay function
void delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 3000; j++);  //
}




int counter, accumulator = 0, limit_value = 1000000;

int main(void) {

	IP_PCC-> PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;  // clock Port D

	IP_PORTD->PCR[PTD0]  = PORT_PCR_MUX(1);   // set PD0 as GPIO
	IP_PORTD->PCR[PTD15] = PORT_PCR_MUX(1);   // set PD15 as GPIO
	IP_PORTD->PCR[PTD16] = PORT_PCR_MUX(1);   // set PD16 as GPIO


	IP_PTD->PDDR |= (1<<PTD0); // setup output for PTD0
	IP_PTD->PDDR |= (1<<PTD15); //  setup output for PTD15
	IP_PTD->PDDR |= (1<<PTD16); // setup output for PTD16


	while(1){

		IP_PTD -> PTOR |= (1<<PTD15); // toggle for pin PD0
		delay_ms(3000); // delay 3s

		IP_PTD  -> PTOR |= (1<<PTD16); // toggle for pin PD0
		delay_ms(3000);

		IP_PTD  -> PTOR |= (1<<PTD0); // toggle for pin PD0
		delay_ms(3000);


	}



//    counter = 0;
//
//    for (;;) {
//        counter++;
//
//        if (counter >= limit_value) {
//            __asm volatile ("svc 0");
//            counter = 0;
//        }

    /* to avoid the warning message for GHS and IAR: statement is unreachable*/
    __NO_RETURN
    return 0;
}

__INTERRUPT_SVC void SVC_Handler() {
    accumulator += counter;
    printf("counter is 0x%08x, accumulator is 0x%08x\n", counter, accumulator);
}
