#include "Driver_GPIO.h"
#include "S32K144.h"
#include "GPIO_Types.h"
#include <stdio.h>
#include "Driver_NVIC.h"
#include "Driver_PORT.h"
#include "clocks.h"

#define GPIO_PIN16      16U
#define GPIO_PIN0       0U
#define GPIO_PIN15      15U
#define GPIO_PIN12      12U
#define GPIO_PIN13      13U

extern ARM_DRIVER_GPIO             Driver_GPIO;
static ARM_DRIVER_GPIO *GPIOdrv = &Driver_GPIO;

void NVIC_Init(void)
{
	NVIC_ClearPendingIRQ(PORTC_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);
	NVIC_SetPriority(PORTC_IRQn,3);
}

void ARM_GPIO_SignalEvent(ARM_GPIO_Pin_t pin, uint32_t event)
{
	if(GPIO_PIN12==pin && event == ARM_GPIO_EVENT_RISING_EDGE)
	{
		GPIOdrv->SetOutput(GPIO_PIN0, 0U);
		GPIOdrv->SetOutput(GPIO_PIN15, 1U);
		GPIOdrv->SetOutput(GPIO_PIN16, 1U);

	}
	else if(GPIO_PIN13==pin  && event == ARM_GPIO_EVENT_RISING_EDGE)
	{
		GPIOdrv->SetOutput(GPIO_PIN0, 1U);
		GPIOdrv->SetOutput(GPIO_PIN15, 1U);
		GPIOdrv->SetOutput(GPIO_PIN16, 1U);
	}
}

void GPIO_Init(void)
{
	GPIOdrv->Setup          (GPIO_PIN16, NULL);
	GPIOdrv->Setup          (GPIO_PIN0, NULL);
	GPIOdrv->Setup          (GPIO_PIN15, NULL);
	GPIOdrv->Setup          (GPIO_PIN12, ARM_GPIO_SignalEvent);
	GPIOdrv->Setup          (GPIO_PIN13, ARM_GPIO_SignalEvent);

	GPIOdrv->SetDirection   (GPIO_PIN16, ARM_GPIO_OUTPUT);
	GPIOdrv->SetDirection   (GPIO_PIN0, ARM_GPIO_OUTPUT);
	GPIOdrv->SetDirection   (GPIO_PIN15, ARM_GPIO_OUTPUT);
	GPIOdrv->SetOutputMode  (GPIO_PIN16, ARM_GPIO_PUSH_PULL);
	GPIOdrv->SetOutputMode  (GPIO_PIN15, ARM_GPIO_PUSH_PULL);
	GPIOdrv->SetOutputMode  (GPIO_PIN0, ARM_GPIO_PUSH_PULL);

	GPIOdrv->SetDirection   (GPIO_PIN12, ARM_GPIO_INPUT);
	GPIOdrv->SetDirection   (GPIO_PIN13, ARM_GPIO_INPUT);
	GPIOdrv->SetPullResistor(GPIO_PIN12, ARM_GPIO_NO_PULL);
	GPIOdrv->SetPullResistor(GPIO_PIN13, ARM_GPIO_NO_PULL);
	GPIOdrv->SetEventTrigger(GPIO_PIN12,ARM_GPIO_EVENT_RISING_EDGE);
	GPIOdrv->SetEventTrigger(GPIO_PIN13,ARM_GPIO_EVENT_RISING_EDGE);
}

int main(void)
{
	SOSCInit_8Mhz();
	SPLLInit_160Mhz();
	SetNormalRUNMode_80MHz();
	Port_Init();
	GPIO_Init();
	NVIC_Init();
	GPIOdrv->SetOutput(GPIO_PIN0, 1U);
	GPIOdrv->SetOutput(GPIO_PIN15, 1U);
	GPIOdrv->SetOutput(GPIO_PIN16, 1U);
	while(1)
	{

	}
    return 0;
}
