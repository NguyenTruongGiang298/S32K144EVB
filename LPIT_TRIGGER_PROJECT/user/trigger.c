/**
 * @file trigger.c
 * @author Nguyễn Trường Giang
 * @brief  Define hardware trigger functions via PDB module
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "S32K144.h"
void TRGMUX_Config(void)
{
    IP_SIM->ADCOPT = SIM_ADCOPT_ADC0PRETRGSEL(1) | SIM_ADCOPT_ADC0TRGSEL(1);
    IP_TRGMUX->TRGMUXn[TRGMUX_ADC0_INDEX] &=~TRGMUX_TRGMUXn_LK_MASK;
    /* choose Trigger MUX Input 0 Source Select = LPIT0_CH0, we can choose other source inputs for SEL1, SEL2, SEL3*/
    IP_TRGMUX->TRGMUXn[TRGMUX_ADC0_INDEX] |= TRGMUX_TRGMUXn_SEL0(17) | TRGMUX_TRGMUXn_LK(1);
}
//void PDB_Config(void)
//{
//    /* Trigger via PDB OR TRGMUX*/
//	IP_SIM->ADCOPT = SIM_ADCOPT_ADC0TRGSEL(0);
//	/* TRGMUX routes PDB trigger */
//    IP_TRGMUX->TRGMUXn[TRGMUX_PDB0_INDEX] &=~TRGMUX_TRGMUXn_LK_MASK;
//    IP_TRGMUX->TRGMUXn[TRGMUX_PDB0_INDEX] |= TRGMUX_TRGMUXn_SEL0(17) | TRGMUX_TRGMUXn_LK(1);
//
//	IP_PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_CGC(1);
//    IP_PDB0->SC = PDB_SC_LDMOD(0) |PDB_SC_PDBEIE(1) | PDB_SC_PRESCALER(7) | PDB_SC_MULT(3) | PDB_SC_CONT(0);
//}
