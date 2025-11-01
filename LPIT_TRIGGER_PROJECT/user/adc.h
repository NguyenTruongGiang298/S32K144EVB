/**
 * @file adc.h
 * @author Nguyễn Trường Giang
 * @brief  Declare initialization functions for ADC module
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ADC_H
#define ADC_H
#include <stdint.h>
#define ADC_IN2 2U
#define ADC_CONVERSION_COMPLETE 1U
#define ADC_CONVERSION_INCOMPLETE 0U
#define ADC_CONVERT_ERROR 0U

void ADCInit(uint16_t ADC_Channel);
void HardwareTriggerADCConfig(void);
uint32_t ReadADC(void);
uint8_t ADConversionCompleted(void);

#endif /* end ADC_H */