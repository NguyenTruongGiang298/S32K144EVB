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
    IP_PCC->PCCn[PCC_ADC0_INDEX] = PCC_PCCn_PCS(3) | PCC_PCCn_CGC(1);
    IP_ADC0->CFG1 = ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(1) | ADC_CFG1_MODE(1);
    IP_ADC0->SC2      = 0x00000000;

    IP_ADC0->SC3  = ADC_SC3_AVGE(1) | ADC_SC3_AVGS(3);
    IP_ADC0->CLPS = 0x00000000;
    IP_ADC0->CLP3 = 0x00000000;
    IP_ADC0->CLP2 = 0x00000000;
    IP_ADC0->CLP1 = 0x00000000;
    IP_ADC0->CLP0 = 0x00000000;
    IP_ADC0->CLPX = 0x00000000;
    IP_ADC0->CLP9 = 0x00000000;
    IP_ADC0->SC3 = ADC_SC3_CAL(1);                /* calibration */
    while(ADConversionCompleted() == 0);

    IP_ADC0->SC1[0] = ADC_SC1_ADCH(0X1F) | ADC_SC1_AIEN(1); /* ADCH = 1F Module is disabled for conversions */
                                                            /* AIEN = 1 Interrupts are enabled */
    IP_ADC0->CFG1   = ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(1);
                                                                /* ADIV = 0 Prescaler = 1 */
                                                                /* MODE = 1 12-bit conversion */
                                                                /* ADICLK = 0 Input CLK = ALTCLK1 = SOSCDIV2 */
    IP_ADC0->CFG2 = ADC_CFG2_SMPLTS(12);     /* SMPLTS = 12(default): sample time is 13 ADC clks */

    /* ADTRG = 1 HW trigger */
    /* ACFE, ACFGT, ACREN = 0: Compare functionality disabled */
    /* DMAEN = 0 DMA disabled */
    /* REFSEL = 0 Voltage reference pins= VREFH, VREEFL */
    IP_ADC0->SC2  = ADC_SC2_ADTRG(1) | ADC_SC2_REFSEL(0) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0);

    IP_ADC0->SC3  = 0x00000000;;



}
void HardwareTriggerADCConfig(void)
{
    IP_SIM->ADCOPT = SIM_ADCOPT_ADC0PRETRGSEL(1) | SIM_ADCOPT_ADC0TRGSEL(1);
    IP_TRGMUX->TRGMUXn[TRGMUX_ADC0_INDEX] &=~TRGMUX_TRGMUXn_LK_MASK;
    IP_TRGMUX->TRGMUXn[TRGMUX_ADC0_INDEX] = TRGMUX_TRGMUXn_SEL0(17) | TRGMUX_TRGMUXn_LK(1);
}
void ADCChannelConvert (uint16_t ADC_Channel)
{
    IP_ADC0 -> SC1[0] &= ~ADC_SC1_ADCH_MASK;
    IP_ADC0 -> SC1[0] =  ADC_SC1_ADCH(ADC_Channel);
}
uint32_t ReadADC(void)
{
    uint8_t trigger_num =(IP_ADC0->SC2 & ADC_SC2_TRGPRNUM_MASK)>>ADC_SC2_TRGPRNUM_SHIFT;
    uint8_t trigger_err =((IP_ADC0->SC2 & ADC_SC2_TRGSTERR_MASK)>>ADC_SC2_TRGSTERR_SHIFT);
    uint16_t u16_ADC_result;
    while(((IP_ADC0->SC2 & ADC_SC2_TRGSTLAT_MASK)>>ADC_SC2_TRGSTLAT_SHIFT) !=0){}
    if(trigger_num == 0 && trigger_err ==0)
    {
        u16_ADC_result = IP_ADC0->R[0];
        return (uint32_t)(u16_ADC_result * 5000 / 0xFFF);
    }
    else
    {
        return ADC_CONVERT_ERROR;
    }
}

uint8_t ADConversionCompleted(void)
{
    return ( (IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK) ? ADC_CONVERSION_COMPLETE : ADC_CONVERSION_INCOMPLETE );
}