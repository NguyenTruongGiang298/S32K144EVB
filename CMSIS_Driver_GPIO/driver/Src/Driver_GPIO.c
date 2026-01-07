#include "Driver_GPIO.h"
#include "GPIO_Types.h"
#include "S32K144.h"

static ARM_GPIO_SignalEvent_t gpio_cb[NUM_PINS] = {(void*)0};
void PORTC_IRQHandler(void)
{
	 /* Read isr flag in pin */
	 uint32_t flags = IP_PORTC->ISFR;
	 for(int i=0;i<NUM_PINS;i++)
	 {
		  if (flags & (1 << i))
		 {
			 if (gpio_cb[i])
			 {
				/* clear flag */
				IP_PORTC->ISFR |= (1 << i);
				/*read trigger edge */
				uint32_t trigger = (IP_PORTC->PCR[i]>>16) &0x000F;
				/*callback function */
				gpio_cb[i](i,trigger);
			 }
		 }
	 }

}
int32_t ARM_GPIO_Setup(ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event)
{
	GPIO_SetUp(pin);
	if(cb_event)
	{
		gpio_cb[pin] = cb_event;
	}

	return ARM_GPIO_OK;
}

int32_t ARM_GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction)
{
	GPIO_SetDirection(pin, direction);
	return ARM_GPIO_OK;
}

int32_t ARM_GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode)
{
	GPIO_SetOutputMode(pin, mode);
	return ARM_GPIO_OK;
}

int32_t ARM_GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor)
{
	GPIO_SetPullResistor(pin, resistor);
	return ARM_GPIO_OK;
}

void ARM_GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val)
{
	GPIO_SetOutput(pin, val);
}
uint32_t ARM_GPIO_GetInput(ARM_GPIO_Pin_t pin)
{
	return GPIO_GetInput(pin);
}
int32_t ARM_GPIO_SetEventTrigger(ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger)
{
    return GPIO_SetEventTrigger(pin,trigger);
}

ARM_DRIVER_GPIO Driver_GPIO = {
  .Setup          = ARM_GPIO_Setup,
  .SetDirection   = ARM_GPIO_SetDirection,
  .SetOutput      = ARM_GPIO_SetOutput,
  .SetPullResistor= ARM_GPIO_SetPullResistor,
  .SetOutput 	  = ARM_GPIO_SetOutput,
  .GetInput		  = ARM_GPIO_GetInput,
  .SetOutputMode  = ARM_GPIO_SetOutputMode,
  .SetEventTrigger = ARM_GPIO_SetEventTrigger
};
