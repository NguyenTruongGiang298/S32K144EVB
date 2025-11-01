#include "Driver_PORT.h"

Std_ReturnType Port_Init(void)
{
	SOSCInit_8Mhz();
	SPLLInit_160Mhz();
	SetNormalRUNMode_80MHz();
	ClockEnable();
	return ARM_PORT_OK;
}
