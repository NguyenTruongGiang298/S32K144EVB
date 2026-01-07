/**
 * @file w25q16.c
 * @author Nguyễn Trường Giang
 * @brief Declare functions for W25Q16 Driver
 * @version 0.1
 * @date 2025-11-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "w25q16.h"
#include "lpspi.h"
#include "S32K144.h"


 uint8_t W25Q_ReadStatus(void)
 {
     uint8_t status;

     LPSPI0_Transmit_8bits(W25Q_READ_STATUS);
     LPSPI0_Transmit_8bits(0x00);
     LPSPI0_Receive_8bits();
     while(!(IP_LPSPI0->SR & LPSPI_SR_TCF_MASK));
     LPSPI0_Transmit_8bits(0x00);
     status = LPSPI0_Receive_8bits();
     return status;
 }
 void W25Q_WaitBusy(void)
 {
	 Turn_On_ContinousTransfer();
     while(W25Q_ReadStatus() & 0x01);
     Turn_Off_ContinousTransfer();
 }
void W25Q_Read(uint32_t addr, uint8_t *buf, uint16_t len)
{
	Turn_On_ContinousTransfer();
    LPSPI0_Transmit_8bits(W25Q_READ_DATA);
    LPSPI0_Receive_8bits();

    LPSPI0_Transmit_8bits((addr >> 16) & 0xFF);
    LPSPI0_Receive_8bits();

    LPSPI0_Transmit_8bits((addr >> 8)  & 0xFF);
    LPSPI0_Receive_8bits();
    LPSPI0_Transmit_8bits(addr & 0xFF);
    LPSPI0_Receive_8bits();

//    for (uint16_t i = 0; i < len; i++)
//    {
//    	if(len-1 ==i)
//		{
//			Turn_Off_ContinousTransfer();
////			while(!(IP_LPSPI0->SR & LPSPI_SR_TCF_MASK));
//		}
//    	LPSPI0_Transmit_8bits(0x00);
//        buf[i] = LPSPI0_Receive_8bits();
//
//    }
//    while (IP_LPSPI0->SR & LPSPI_SR_MBF_MASK);

    for (uint16_t i = 0; i < len; i++)
    {
        LPSPI0_Transmit_8bits(0x00);
        buf[i] = LPSPI0_Receive_8bits();
    }
    Turn_Off_ContinousTransfer();
    while (IP_LPSPI0->SR & LPSPI_SR_MBF_MASK);
}
void W25Q_WritePage(uint32_t addr, uint8_t *data, uint16_t len)
{
    W25Q_WriteEnable();
    Turn_On_ContinousTransfer();
    LPSPI0_Transmit_8bits(W25Q_PAGE_PROGRAM);
    LPSPI0_Receive_8bits();
    LPSPI0_Transmit_8bits((addr >> 16) & 0xFF);
    LPSPI0_Receive_8bits();
    LPSPI0_Transmit_8bits((addr >> 8)  & 0xFF);
    LPSPI0_Receive_8bits();
    LPSPI0_Transmit_8bits(addr & 0xFF);
    LPSPI0_Receive_8bits();
    for (uint16_t i = 0; i < len; i++)
    {
    	if(len-1 == i)
    	{
    		Turn_Off_ContinousTransfer();
    	}
    	LPSPI0_Transmit_8bits(data[i]);
    	LPSPI0_Receive_8bits();
    }
}
void W25Q_EraseSector(uint32_t addr)
{
    W25Q_WriteEnable();
    LPSPI0_Transmit_8bits(W25Q_SECTOR_ERASE);
    LPSPI0_Transmit_8bits((addr >> 16) & 0xFF);
    LPSPI0_Transmit_8bits((addr >> 8)  & 0xFF);
    LPSPI0_Transmit_8bits(addr & 0xFF);
    while (W25Q_ReadStatus() & 0x01);
}
void W25Q_ReadID(uint8_t *id)
{
	LPSPI0_Transmit_8bits(W25Q_READ_ID);
	LPSPI0_Transmit_8bits(0x00);
	LPSPI0_Receive_8bits();
	for(int i=0; i< 3;i++)
	{
	    if(i == 2)
		{
	    	/* Turn of countinous transfer / PSC0 =1 */
	    	Turn_Off_ContinousTransfer();
		}
		LPSPI0_Transmit_8bits(0x00);
		*id = LPSPI0_Receive_8bits();
		id++;
	}
}
void W25Q_WriteEnable(void)
{
	Turn_Off_ContinousTransfer();
	LPSPI0_Transmit_8bits(W25Q_WRITE_ENABLE);
}
