/**
 * @file clocks.h
 * @author Nguyễn Trường Giang
 * @brief Declare Clock configuration functions for S32K144
 * @version 0.1
 * @date 2025-11-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CLOCKS_H
#define CLOCKS_H

void SOSCInit_8Mhz(void);
void SPLLInit_160Mhz(void);
void SetNormalRUNMode_80MHz(void);

#endif /* CLOCKS_H */
