/**
 * @file adc.c
 * @author Nguyễn Trường Giang
 * @brief  Define initialization functions for ADC module
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "adc.h"
#include "S32K144.h"
#include "stdint.h"

void ADCInit(void)
{
    IP_PCC->PCCn[PCC_ADC0_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(3) | PCC_PCCn_CGC(1);

    IP_ADC0->SC2 = 0x00000000;
    /* ADIV = 0, Prescaler = 1 */
    /* MODE = 1 12-bit conversion */
    /* ADICLK = 0 Input CLK = ALTCLK1 = SOSCDIV2 */
    IP_ADC0->CFG1   = ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(1);
    /* SMPLTS = 12(default): sample time is 13 ADC clks */
    IP_ADC0->CFG2 = ADC_CFG2_SMPLTS(12);
    /* ADTRG = 1 HW trigger */
    /* ACFE, ACFGT, ACREN = 0: Compare functionality disabled */
    /* DMAEN = 0 DMA disabled */
    /* REFSEL = 0 Voltage reference pins= VREFH, VREEFL */
    IP_ADC0->SC2  = ADC_SC2_ADTRG(1) | ADC_SC2_REFSEL(0) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0);
    /* ADCH = CHANNEL 0, Module is enable for conversions */
    /* AIEN = 1 Interrupts are enabled */
    IP_ADC0->SC1[0] = ADC_SC1_ADCH(CHANNEL_2) | ADC_SC1_AIEN(1);
    IP_ADC0->SC3  =0x00000000;
}

void ADCChannelConvert (uint16_t ADC_Channel)
{
    IP_ADC0 -> SC1[0] &= ~ADC_SC1_ADCH_MASK;
    IP_ADC0 -> SC1[0] =  ADC_SC1_ADCH(ADC_Channel);
}
int32_t ReadADC(void)
{
    uint16_t ADCResult;
	ADCResult = IP_ADC0->R[0];
	return (uint32_t)(ADCResult * 5000 / 0xFFF);
}

uint8_t ADConversionCompleted(void)
{
    return ( (IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK) ? ADC_CONVERSION_COMPLETE : ADC_CONVERSION_INCOMPLETE );
}
