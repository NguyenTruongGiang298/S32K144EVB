#include "Driver_PORT.h"
Std_ReturnType Port_Init(void)
{
	ClockEnable();
	return ARM_PORT_OK;
}
