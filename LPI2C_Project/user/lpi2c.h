/**
 * @file lpsip.h
 * @author Nguyễn Trường Giang
 * @brief Declrare functions for LPI2C module in S32k144
 * @version 0.1
 * @date 2025-11-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LPSPI_H_
#define LPSPI_H_
#include <stdint.h>

#define BUSY 1
#define NOT_BUSY 0

typedef enum
{
    LPI2C_CMD_TX_DATA             = 0b000,   /* Transmit DATA[7:0] */
    LPI2C_CMD_RX_DATA             = 0b001,   /* Receive (DATA + 1) bytes, stores in FIFO*/
    LPI2C_CMD_STOP                = 0b010,   /* Generate STOP condition */
    LPI2C_CMD_RX_DISCARD          = 0b011,   /* Receive and discard (DATA + 1) bytes, dose not store in FIFO*/
    LPI2C_CMD_START_ADDR          = 0b100,   /* START + transmit address (expect ACK) */
    LPI2C_CMD_START_ADDR_NACK     = 0b101,   /* START + transmit address (expect NACK) */
    LPI2C_CMD_START_ADDR_HS       = 0b110,   /* START + address (High-Speed mode, expect ACK) */
    LPI2C_CMD_START_ADDR_HS_NACK  = 0b111    /* START + address (HS mode, expect NACK) */
} LPI2C_Command_t;

void LPI2C0_Init_Master(void);
void LPI2C0_Transmit_8bits(LPI2C_Command_t cmd, uint8_t data);
uint8_t LPI2C0_Receive_8bits (LPI2C_Command_t cmd);


#endif /* LPSPI_H_ */
