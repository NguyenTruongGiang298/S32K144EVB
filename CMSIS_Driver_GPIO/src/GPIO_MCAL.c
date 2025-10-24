/*
 * GPIO_MCAL.c
 *
 *  Created on: Oct 23, 2025
 *      Author: truon
 */

#include "GPIO_MCAL.h"
#include <stdint.h>
#include "GPIO_Types.h"

void GPIO_SetUp(ARM_GPIO_Pin_t pin)
{
	IP_PORTD->PCR[pin]= PORT_PCR_MUX(1);
	IP_PORTC->PCR[pin]= PORT_PCR_MUX(1);
}
int32_t GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction)
{
	if(direction == ARM_GPIO_OUTPUT)
	{
		IP_PTD->PDDR |= (1<<pin);
	}
	else
	{
		IP_PTC->PDDR |=(0<<pin);
	}
	return ARM_GPIO_OK;
}

int32_t GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode)
{
	switch(mode)
	{
		case ARM_GPIO_PUSH_PULL:
			IP_PTD->PDDR |=  (1 << pin);
			IP_PTD->PCOR  =  (1 << pin);
			break;
		case ARM_GPIO_OPEN_DRAIN:
			IP_PTD->PDDR &=~(1 << pin);
			break;
		default:
			break;
	}
	return ARM_GPIO_OK;
}

int32_t GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor)
{
    uint32_t pcr;
    pcr = IP_PORTD->PCR[pin];
    while(!(IP_PORTD->PCR[pin] & PORT_PCR_LK_MASK))
    pcr = PORT_PCR_PE(0);
    switch (resistor)
    {
        case ARM_GPIO_PULL_NONE:
            break;

        case ARM_GPIO_PULL_DOWN:
            pcr |= (1UL << 1) | ~(1UL << 0);
            break;
        case ARM_GPIO_PULL_UP:
            pcr |= (1UL << 1) | (1UL << 0);
            break;
        default:
            return ARM_GPIO_ERROR;
    }
    IP_PORTD->PCR[pin] = pcr;
    return ARM_GPIO_OK;
}

void GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val)
{
	if(val ==1)
	{
		IP_PTD->PSOR|=(1<<pin);
	}
	else
	{
		IP_PTD->PCOR|=(0<<pin);
	}
}
int32_t GPIO_GetInput(ARM_GPIO_Pin_t pin)
{
	if(!(IP_PTC->PIDR & pin)) return IP_PTC->PDIR & pin;
	return ARM_GPIO_ERROR;
}
