/**
 * @file w25q16.h
 * @author Nguyễn Trường Giang
 * @brief Define functions for W25Q16 Driver
 * @version 0.1
 * @date 2025-11-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef W25Q16_H
#define W25Q16_H_
#include "stdint.h"
#define W25Q_READ_ID       0x9F
#define W25Q_READ_DATA     0x03
#define W25Q_WRITE_ENABLE  0x06
#define W25Q_PAGE_PROGRAM  0x02
#define W25Q_SECTOR_ERASE  0x20
#define W25Q_READ_STATUS   0x05

 uint8_t W25Q_ReadStatus(void);
 void W25Q_WaitBusy(void);
void W25Q_Read(uint32_t addr, uint8_t *buf, uint16_t len);
void W25Q_WritePage(uint32_t addr, uint8_t *data, uint16_t len);
void W25Q_EraseSector(uint32_t addr);
void W25Q_ReadID(uint8_t *id);
void LPSPI2_IRQHandler(void);
void W25Q_WriteEnable(void);

#endif /* W25Q16_C_ */
