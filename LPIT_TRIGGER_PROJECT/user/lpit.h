/**
 * @file lpit.h
 * @author Nguyễn Trường Giang
 * @brief Declare set-up functions for low periodic interrupt timer(LPIT)
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef LPIT_H
#define LPIT_H
#define TIMER_CHANNEL_0 0U
#include <stdint.h>
void LpitInit(uint32_t counter);


#endif /* end LPIT_H */
