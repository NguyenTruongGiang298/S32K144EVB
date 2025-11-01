/*
 * PORT_MCAL.h
 *
 *  Created on: Oct 23, 2025
 *      Author: truon
 */

#ifndef PORT_MCAL_H_
#define PORT_MCAL_H_
#include "S32K144.h"


void SOSCInit_8Mhz(void);
void SPLLInit_160Mhz(void);
void SetNormalRUNMode_80MHz(void);
void ClockEnable();

#endif /* PORT_MCAL_H_ */
