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
#include "Driver_PORT.h"
#include "Driver_GPIO.h"
#include "S32K144.h"
#include "GPIO_Types.h"
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

#define GPIO_PIN0       0U
#define GPIO_PIN15      15U
#define GPIO_PIN12      12U
#define GPIO_PIN13      13U

extern ARM_DRIVER_GPIO             Driver_GPIO;
static ARM_DRIVER_GPIO *GPIOdrv = &Driver_GPIO;

int counter, accumulator = 0, limit_value = 1000000;

void delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 3000; j++);
}

void GPIO_Init(void)
{
	GPIOdrv->Setup          (GPIO_PIN0, NULL);
	GPIOdrv->Setup          (GPIO_PIN15, NULL);
	GPIOdrv->Setup          (GPIO_PIN12, NULL);
	GPIOdrv->Setup          (GPIO_PIN13, NULL);

	GPIOdrv->SetDirection   (GPIO_PIN0, ARM_GPIO_OUTPUT);
	GPIOdrv->SetDirection   (GPIO_PIN15, ARM_GPIO_OUTPUT);
	GPIOdrv->SetOutputMode  (GPIO_PIN15, ARM_GPIO_PUSH_PULL);
	GPIOdrv->SetOutputMode  (GPIO_PIN15, ARM_GPIO_PUSH_PULL);

	GPIOdrv->SetDirection   (GPIO_PIN12, ARM_GPIO_INPUT);
	GPIOdrv->SetDirection   (GPIO_PIN13, ARM_GPIO_INPUT);
	GPIOdrv->SetPullResistor(GPIO_PIN12, ARM_GPIO_PULL_DOWN);
	GPIOdrv->SetPullResistor(GPIO_PIN13, ARM_GPIO_PULL_DOWN);

}

int main(void) {

	Port_Init();
	GPIO_Init();
	if(GPIOdrv->GetInput(GPIO_PIN12)) GPIOdrv->SetOutput(GPIO_PIN16, 0U);
	else GPIOdrv->SetOutput(GPIO_PIN16, 1U);
	if(GPIOdrv->GetInput(GPIO_PIN13)) GPIOdrv->SetOutput(GPIO_PIN15, 0U);
	else GPIOdrv->SetOutput(GPIO_PIN15, 1U);

//    counter = 0;
//
//    for (;;) {
//        counter++;
//
//        if (counter >= limit_value) {
//            __asm volatile ("svc 0");
//            counter = 0;
//        }
//    }
    /* to avoid the warning message for GHS and IAR: statement is unreachable*/
    __NO_RETURN
    return 0;
}

__INTERRUPT_SVC void SVC_Handler() {
    accumulator += counter;
    printf("counter is 0x%08x, accumulator is 0x%08x\n", counter, accumulator);
}
