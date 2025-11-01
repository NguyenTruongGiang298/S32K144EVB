/*
 * GPIO_Driver.h
 *
 *  Created on: Oct 19, 2025
 *      Author: truon
 */

#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include "GPIO_Types.h"
#include "GPIO_MCAL.h"
#include <stdint.h>


void ARM_GPIO_SignalEvent(ARM_GPIO_Pin_t pin, uint32_t event);
typedef void(*ARM_GPIO_SignalEvent_t )(ARM_GPIO_Pin_t pin, uint32_t event);

int32_t ARM_GPIO_Setup(ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event);

int32_t ARM_GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction);

int32_t ARM_GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor);

void ARM_GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val);

uint32_t ARM_GPIO_GetInput(ARM_GPIO_Pin_t pin);

int32_t ARM_GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode);

typedef struct
{
	int32_t(* Setup) (ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event);
	int32_t(* SetDirection )(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction);
	int32_t(* SetOutputMode )(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode);
	int32_t(* SetPullResistor )(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor);
	void(* SetOutput )(ARM_GPIO_Pin_t pin, uint32_t val);
	uint32_t(* GetInput )(ARM_GPIO_Pin_t pin);
}ARM_DRIVER_GPIO;


#endif /* GPIO_DRIVER_H_ */
