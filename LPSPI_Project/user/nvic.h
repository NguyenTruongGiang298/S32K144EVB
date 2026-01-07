/**
 * @file interrupt.h
 * @author Nguyễn Trường Giang
 * @brief Define functions for interrupt and GPIO configuration
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef NVIC_H_
#define NVIC_H_

#define PTD0  0U
#define PTD15 15U
#define PTD16 16U
#define PTC12 12U
#define PTC13 13U

void NVIC_Init(void);
#endif /* NVIC_H_ */
