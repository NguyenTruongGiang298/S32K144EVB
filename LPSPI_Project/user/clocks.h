/**
 * @file clocks.h
 * @author Nguyễn Trường Giang
 * @brief Declare functions for clocks and mode
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef CLOCKS_H_
#define CLOCKS_H_

#define SCG_SPLLCFG_SOURCE (1<<0)
void FIRCInit_48Mhz(void);
void SPLLInit_160Mhz(void);
void SetNormalRUNMode_80MHz(void);

#endif /* CLOCKS_H_ */
