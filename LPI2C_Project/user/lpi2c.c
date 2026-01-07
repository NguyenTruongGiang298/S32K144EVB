/**
 * @file lpspi.c
 * @author Nguyễn Trường Giang
 * @brief Define functions for LPI2C module in S32k144
 * @version 0.1
 * @date 2025-11-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "S32K144.h"
#include <stdint.h>
#include "lpi2c.h"
void LPI2C0_Init_Master(void)
{
    IP_PCC->PCCn[PCC_LPI2C0_INDEX] &=~ PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_LPI2C0_INDEX]= PCC_PCCn_PCS(3) | PCC_PCCn_CGC(1); /* use FIRCDIV2_CLK*/
    IP_LPI2C0->MCR = LPI2C_MCR_RST(1); /* RST = 1 */

    IP_LPI2C0->MDER =0; /* DMA not used */
    IP_LPI2C0->MCFGR0 = 0;
    /* RDM0=0: receive data match only to FIFO as normal*/
    /* CIRFIFO=0; Circular FIFO is disabled             */
    /* HRSEL, HRPOL, HREN=0: Host request disabled      */

    /* Interrupt */
    //IP_LPI2C0->MIER =LPI2C_MIER_RDIE(1) | LPI2C_MIER_TDIE(1);

    IP_LPI2C0->MCFGR1 = LPI2C_MCFGR1_PRESCALE(2);
    /* PINCFG=0: Bi-directional open drain for master and slave        */
    /* MATCFG=0: Match disabled                                        */
    /* TIMECFG=0: Timeout Configuration                                */
    /* IGNACK=0: IGNORE NACK                                           */
    /* AUTOSTOP=0: does not apply for master mode                      */
    /* PRESCALE=4: 2**2 = 4                                            */


    IP_LPI2C0->MCFGR2 = 0;
    /* FILTSDA=0: disable Glitch Filter SDA */
    /* FILTSCL=0: disable Glitch Filter SCL */
    /* BUSIDLE=0: disable Bus Idle Timeout  */

    IP_LPI2C0->MCFGR3 =0;
    /* PINLOW=0: disable PIN LOW TIMEOUT */

    IP_LPI2C0->MFCR = LPI2C_MFCR_TXWATER(3);
    /* RXWATER=0: Rx flags set when Rx FIFO >0      */
    /* TXWATER=3: Tx flags set when Tx FIFO <= 3    */

    IP_LPI2C0->MCCR0 = LPI2C_MCCR0_CLKLO(8) | LPI2C_MCCR0_CLKHI(3) | LPI2C_MCCR0_SETHOLD(6) | LPI2C_MCCR0_DATAVD(3);
    /* SCL_freq = Input_freq / (2^PRESCALER * (CLKLO + CLKHI + 2))*/
    /* 24Mhz/(2**2⋅(9+4+2))=400khz     */
    /* 24Mhz/(2**2⋅(36+22+2))=100khz   */
    /* CLKLO=8: Clock Low Period       */
    /* CLKHI=3: Clock High Period      */
    /* DATAVD=3: Data Valid Delay      */
    /* SHD=6 : Setup Hold Delay        */

    IP_LPI2C0->MCR |=LPI2C_MCR_MEN(1);
}
void LPI2C0_Transmit_8bits(LPI2C_Command_t cmd, uint8_t data)
{
	/* CHECK SIZE OF TX FIFO EMPTY */
    while((IP_LPI2C0->MSR & LPI2C_MSR_TDF_MASK)>>LPI2C_MSR_TDF_SHIFT==0);
    if(cmd == LPI2C_CMD_STOP)
    {
        IP_LPI2C0->MTDR =(cmd<<8);
    }
    else
    {
        IP_LPI2C0->MTDR =(cmd<<8) | data;
    }
}
uint8_t LPI2C0_Receive_8bits (LPI2C_Command_t cmd)
{
	/* CHECK SIZE OF RX FIFO FULLY */
	IP_LPI2C0->MTDR = cmd << 8 | 0x00;
    while(((IP_LPI2C0->MSR & LPI2C_MSR_RDF_MASK)>> LPI2C_MSR_RDF_SHIFT) == 0);
    if(cmd == LPI2C_CMD_RX_DISCARD)
    {
        return -1;
    }
    return (uint8_t)(IP_LPI2C0->MRDR & 0xff);
}
