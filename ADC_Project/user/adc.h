/**
 * @file adc.h
 * @author your name (you@domain.com)
 * @brief Declare initialization functions for ADC module
 * @version 0.1
 * @date 2025-11-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADCInit(uint16_t ADC_Channel);
uint32_t ReadADC(void);
uint8_t ADConversionCompleted(void);
#endif /* ADC_H */
