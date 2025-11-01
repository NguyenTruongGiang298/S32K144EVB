/*
 * GPIO_MCAL.h
 *
 *  Created on: Oct 23, 2025
 *      Author: truon
 */

#ifndef GPIO_MCAL_H_
#define GPIO_MCAL_H_

#include "GPIO_Types.h"
#include "S32K144.h"
#include <stdint.h>

void GPIO_SetUp(ARM_GPIO_Pin_t pin);

int32_t GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction);

int32_t GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor);

int32_t GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode);

void GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val);

int32_t GPIO_GetInput(ARM_GPIO_Pin_t pin);

#endif /* GPIO_MCAL_H_ */
