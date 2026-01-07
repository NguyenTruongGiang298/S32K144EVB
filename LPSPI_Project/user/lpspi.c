/**
 * @file lpspi.c
 * @author Nguyễn Trường Giang
 * @brief Define functions for initialization Low Power Serial Peripheral Interface module
 * @version 0.1
 * @date 2025-11-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "S32K144.h"
#include <stdint.h>
#include "lpspi.h"
void LPSPI0_Init_Master (void)
{
    IP_PCC->PCCn[PCC_LPSPI0_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_LPSPI0_INDEX]= PCC_PCCn_PCS(3) | PCC_PCCn_CGC(1);
    //* Disable module for configuration 			*/
    IP_LPSPI0->CR = 0;
    /* DMA not used */
    IP_LPSPI0->DER =0;
    /* RDM0=0: receive data match only to FIFO as normal*/
    /* CIRFIFO=0; Circular FIFO is disabled 		  */
    /* HRSEL, HRPOL, HREN=0: Host request disabled */
    IP_LPSPI0->CFGR0 = 0;
    /* Enable interrupt */
    //IP_LPSPI0->IER =LPSPI_IER_RDIE(1);

    IP_LPSPI0->CFGR1 = LPSPI_CFGR1_MASTER(1);
    /* PCSCFG=0: Chip select / 1 = half duplex 4 bit transfer       */
    /* OUTCFG=0: Output data retains last value when CS negated	    */
    /* PINCFG=0: SIN is input, SOUT is output 						*/
    /* MATCFG=0: Match disabled 									*/
    /* PCSPOL=0: PCS is active low 								    */
    /* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full 			*/
    /* AUTOPCS=0: does not apply for master mode 					*/
    /* SAMPLE=0: input data sampled on SCK edge 					*/
    /* MASTER=1: Master mode 										*/

    IP_LPSPI0->TCR = LPSPI_TCR_PRESCALE(2) | LPSPI_TCR_CPHA(0) | LPSPI_TCR_CPOL(0) | LPSPI_TCR_PCS(0) | LPSPI_TCR_FRAMESZ(7)
                      | LPSPI_TCR_CONT(1) |LPSPI_TCR_CONTC(1) ;
    /* CPOL=0: SCK inactive state is low 							*/
    /* CPHA=0: Change data on SCK leading, capture on following edge*/
    /* PRESCALE=2: Functional clock divided by 2**2 = 4 			*/
    /* PCS=0: Transfer using PCS3 									*/
    /* LSBF=0: Data is transfered MSB first 						*/
    /* BYSW=0: Byte swap disabled 									*/
    /* CONT, CONTC=0: Continuous transfer disabled 				    */
    /* RXMSK=0: Normal transfer: rx data stored in rx FIFO 		    */
    /* TXMSK=0: Normal transfer: data loaded from tx FIFO 			*/
    /* WIDTH=0: Single bit transfer 								*/
    /* FRAMESZ=7: bits in frame = 7+1=8   						    */

    IP_LPSPI0->CCR = LPSPI_CCR_PCSSCK(5) |  LPSPI_CCR_SCKDIV(4) | LPSPI_CCR_SCKPCS(2) | LPSPI_CCR_DBT(4);
	/* Clock dividers based on prescaled function clk of 100 nsec 	*/
	/* SCKPCS=2: SCK to PCS delay = 2+1 = 3 (500 nsec) 			    */
	/* PCSSCK=5: PCS to SCK delay = 5+1 = 6 (1 usec) 				*/
	/* DBT=4: Delay between Transfers = 4+2 = 6 (1 usec) 			*/
	/* SCKDIV=4: SCK divider =2+4=6 (baud rate: 24 /6*4= 1 Mhz) 	*/

    IP_LPSPI0->FCR   = LPSPI_FCR_TXWATER(3) | LPSPI_FCR_RXWATER(0);
    /* RXWATER=0: Rx flags set when Rx FIFO >0 	 */
    /* TXWATER=3: Tx flags set when Tx FIFO <= 3 */

    IP_LPSPI0->CR |=LPSPI_CR_MEN(1) | LPSPI_CR_DBGEN_MASK;;
}
void Turn_Off_ContinousTransfer(void)
{
	/* Turn of countinous transfer / PSC0 =1 */
	IP_LPSPI0->TCR &= ~(LPSPI_TCR_CONT_MASK | LPSPI_TCR_CONTC_MASK);
}
void Turn_On_ContinousTransfer(void)
{
	IP_LPSPI0->TCR |= LPSPI_TCR_CONT_MASK | LPSPI_TCR_CONTC_MASK;
}
uint8_t LPSPI0_Check_Status(void)
{
    return (((IP_LPSPI0->SR & LPSPI_SR_MBF_MASK)>>LPSPI_SR_MBF_SHIFT) ? BUSY : NOT_BUSY);
}
void Reset_FIFO_Memory(void)
{
    IP_LPSPI0->CR = LPSPI_CR_RRF(1) | LPSPI_CR_RTF(1);
}
void LPSPI0_Transmit_8bits(uint8_t data)
{
	/* CHECK TX FIFO EMPTY OR NOT */
    while((IP_LPSPI0->SR & LPSPI_SR_TDF_MASK)>>LPSPI_SR_TDF_SHIFT==0);
    IP_LPSPI0->TDR = data;
}
uint8_t LPSPI0_Receive_8bits (void)
{
	/* CHECK SIZE OF RX FIFO FULLY */
    while((IP_LPSPI0->SR & LPSPI_SR_RDF_MASK)>>LPSPI_SR_RDF_SHIFT==0);
    return IP_LPSPI0->RDR;
}
void LPSPI0_4bitMode_enable (void)
{
	/* Transmit data DMA request enable */
	IP_LPSPI0 -> DER = LPSPI_DER_TDDE_MASK;

	/* Configurations: Master Mode */
	IP_LPSPI0 -> CFGR1 |= LPSPI_CFGR1_MASTER(1) |  LPSPI_CFGR1_NOSTALL(1) |  LPSPI_CFGR1_PCSCFG(1);
	/* MASTER = 1: Master Mode */
	/* NOSTALL = 1: No Stall if Tx FIFO is empty or Rx FIFO is full */
	/* PCSCFG = 1: PCS[3:2] are enabled. Half - duplex 4-bit transfer */
	/* OUTCFG = 0: Output data retains last value when CS negated */
	/* PINCFG = 0: SIN is input, SOUT is output */
    /* MATCFG = 0: Match disabled */
    /* PCSPOL = 0: PCS is active low */
    /* AUTOPCS = 0: Does not apply for master mode */
	/* SAMPLE = 0: Input data sampled on SCK edge */
}
