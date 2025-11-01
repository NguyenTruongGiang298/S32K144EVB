/*
 * GPIO_Types.h
 *
 *  Created on: Oct 23, 2025
 *      Author: truon
 */

#ifndef GPIO_TYPES_H_
#define GPIO_TYPES_H_
#include <stdint.h>
#define ARM_GPIO_OK 0
#define ARM_GPIO_ERROR -1

typedef uint32_t ARM_GPIO_Pin_t;

typedef enum{
	ARM_GPIO_EVENT_RISING_EDGE =0,
	ARM_GPIO_EVENT_FALLING_EDGE,
	ARM_GPIO_EVENT_EITHER_EDGE
}ARM_GPIO_EVENT;

typedef enum{
	ARM_GPIO_PUSH_PULL=0,
	ARM_GPIO_OPEN_DRAIN
}ARM_GPIO_OUTPUT_MODE;

typedef enum{
	ARM_GPIO_INPUT,
	ARM_GPIO_OUTPUT
}ARM_GPIO_DIRECTION;

typedef enum{
  ARM_GPIO_PULL_NONE ,
  ARM_GPIO_PULL_UP ,
  ARM_GPIO_PULL_DOWN
}ARM_GPIO_PULL_RESISTOR;

#endif /* GPIO_TYPES_H_ */
