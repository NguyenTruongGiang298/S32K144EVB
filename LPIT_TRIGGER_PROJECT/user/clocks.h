/**
 * @file   clocks_and_mode.h
 * @author Nguyễn Trường Giang
 * @brief  Declare Clock configuration functions for S32K144
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CLOCKS_H
#define CLOCKS_H

#define SCG_SPLLCFG_SOURCE (1<<0)
void FIRC_Init(void);        /* 48 Mhz */
void SPLLInit_128Mhz(void);  /* 128 Mhz */
void RUNMode_64MHz(void);    /* 64 Mhz */

#endif /* end CLOCKS_H */
