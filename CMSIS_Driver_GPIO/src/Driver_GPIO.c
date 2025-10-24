/*
 * GPIO_Driver.c
 *
 *  Created on: Oct 19, 2025
 *      Author: truon
 */
#include "Driver_GPIO.h"
#include "GPIO_Types.h"
/* GPIO driver instance */


int32_t ARM_GPIO_Setup(ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event)
{
	GPIO_SetUp(pin);
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

ARM_DRIVER_GPIO Driver_GPIO = {
  .Setup          = ARM_GPIO_Setup,
  .SetDirection   = ARM_GPIO_SetDirection,
  .SetOutput      = ARM_GPIO_SetOutput,
  .SetPullResistor= ARM_GPIO_SetPullResistor,
  .SetOutput 	  = ARM_GPIO_SetOutput,
  .GetInput		  = ARM_GPIO_GetInput,
  .SetOutputMode  = ARM_GPIO_SetOutputMode
};
