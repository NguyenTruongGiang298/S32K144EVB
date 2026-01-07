#ifndef GPIO_MCAL_H_
#define GPIO_MCAL_H_

#include "GPIO_Types.h"
#include <stdint.h>

void GPIO_SetUp(ARM_GPIO_Pin_t pin);

int32_t GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction);

int32_t GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor);

int32_t GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode);

void GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val);

int32_t GPIO_GetInput(ARM_GPIO_Pin_t pin);

int32_t GPIO_SetEventTrigger(ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger);

#endif /* GPIO_MCAL_H_ */
