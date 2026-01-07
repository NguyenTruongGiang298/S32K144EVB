#include <Hal_GPIO.h>
#include <stdint.h>
#include "GPIO_Types.h"
#include "S32K144.h"

void GPIO_SetUp(ARM_GPIO_Pin_t pin)
{
	IP_PORTD->PCR[pin]= PORT_PCR_MUX(1);
	IP_PORTC->PCR[pin]= PORT_PCR_MUX(1);
}
int32_t GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction)
{
	if (ARM_GPIO_OUTPUT==direction)
	{
	    IP_PTD->PDDR |= (1 << pin);
	}
	else
	{
	    IP_PTC->PDDR &= ~(1 << pin);
	}
	return ARM_GPIO_OK;
}

int32_t GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode)
{
	switch(mode)
	{
		case ARM_GPIO_PUSH_PULL:
		{
			/* Do nothing*/
			break;
		}
		case ARM_GPIO_OPEN_DRAIN:
		{
			/* Do nothing*/
			break;
		}
		default:
		{
			break;
		}
	}
	return ARM_GPIO_OK;
}
int32_t GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor)
{
	uint32_t pcr = IP_PORTC->PCR[pin];
	pcr &= ~(1<<15);
	pcr |= (1<<1);
    switch (resistor)
    {
        case ARM_GPIO_PULL_DOWN:
        {
        	pcr &= ~PORT_PCR_PS_MASK;
            break;
        }
        case ARM_GPIO_PULL_UP:
        {
        	pcr |= PORT_PCR_PS_MASK;
            break;
        }
        default:
        {
        	break;
        }
    }
    IP_PORTC->PCR[pin] = pcr;
    return ARM_GPIO_OK;
}

void GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val)
{
	if((1<<pin) & IP_PTD->PDDR)
	{
		if(1 == val)
		{
			IP_PTD->PSOR|=(1<<pin);
		}
		else
		{
			IP_PTD->PCOR|=(1<<pin);
		}
	}
}
int32_t GPIO_GetInput(ARM_GPIO_Pin_t pin)
{
	int32_t res;
    if (IP_PTC->PDDR & (1<<pin))
    {
        res = ARM_GPIO_ERROR;
    }
    else
    {
    	res = (IP_PTC->PDIR & (1<<pin)) ? 1 : 0;
    }
    return res;
}
int32_t GPIO_SetEventTrigger(ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger)
{
	int32_t res;
	if(((1<<pin) & IP_PTC->PDDR) || pin >=32)
	{
		res = ARM_GPIO_ERROR;
	}
	else
	{
		res = ARM_GPIO_OK;
		switch(trigger)
		{
			case ARM_GPIO_EVENT_RISING_EDGE:
			{
				IP_PORTC->PCR[pin] &= ~PORT_PCR_IRQC_MASK;
				IP_PORTC->PCR[pin]|= PORT_PCR_IRQC(ARM_GPIO_EVENT_RISING_EDGE);
				break;
			}
			case ARM_GPIO_EVENT_FALLING_EDGE:
			{
				IP_PORTC->PCR[pin] &= ~PORT_PCR_IRQC_MASK;
				IP_PORTC->PCR[pin]|= PORT_PCR_IRQC(ARM_GPIO_EVENT_FALLING_EDGE);
				break;
			}
			case ARM_GPIO_EVENT_EITHER_EDGE:
			{
				IP_PORTC->PCR[pin] &= ~PORT_PCR_IRQC_MASK;
				IP_PORTC->PCR[pin]|= PORT_PCR_IRQC(ARM_GPIO_EVENT_EITHER_EDGE);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return res;
}
