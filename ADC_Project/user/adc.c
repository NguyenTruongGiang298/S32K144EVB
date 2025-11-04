/**
 * @file adc.c
 * @author Nguyễn Trường Giang
 * @brief Define initialization functions for ADC module
 * @version 0.1
 * @date 2025-11-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "adc.h"
#include "S32K144.h"
#include "stdint.h"

void ADCInit(void)
{
    IP_PCC->PCCn[PCC_ADC0_INDEX] = PCC_PCCn_CGC(0);
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1) | PCC_PCCn_CGC(1);
    IP_ADC0->CFG1   = ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(2) | ADC_CFG1_MODE(1);
    IP_ADC0->SC2      = 0x00000000;

    IP_ADC0->SC3  = ADC_SC3_AVGE(1) | ADC_SC3_AVGS(3);
    IP_ADC0->CLPS = 0x00000000;
    IP_ADC0->CLP3 = 0x00000000;
    IP_ADC0->CLP2 = 0x00000000;
    IP_ADC0->CLP1 = 0x00000000;
    IP_ADC0->CLP0 = 0x00000000;
    IP_ADC0->CLPX = 0x00000000;
    IP_ADC0->CLP9 = 0x00000000;
    IP_ADC0->SC3   |= ADC_SC3_CAL(1);                /* calibration */
    while(ADConversionCompleted() == 0);

    IP_ADC0->SC1[0] = ADC_SC1_ADCH(0X1F) | ADC_SC1_AIEN(0);
    IP_ADC0->CFG1   = ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(1);
    IP_ADC0->CFG2     = ADC_CFG2_SMPLTS(12);
    IP_ADC0->SC3 |= ADC_SC3_ADCO(1) |  ADC_SC3_CAL(0) | ADC_SC3_AVGE(0) | ADC_SC3_AVGS(0);
}
void ADCChannelConversion(uint16_t ADC_Channel)
{
  IP_ADC0->SC1[0]&=~ADC_SC1_ADCH_MASK;
  IP_ADC0->SC1[0] = ADC_SC1_ADCH(ADC_Channel);
}

uint32_t ReadADC(void)
{
    uint16_t u16_ADC_result = IP_ADC0->R[0];
    return (uint32_t)(u16_ADC_result * 5000 / 0xFFF);
}

uint8_t ADConversionCompleted(void)
{
    return ((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT);
}
