#include "stm32l1xx_hal.h"


void I2C_Init (void);                                                           //  init pins and i2C registers
uint8_t I2C_Mem_Read( uint16_t DevAddress, uint16_t MemAddress, uint32_t Timeout);
uint8_t I2C_Mem_Write (uint16_t DevAddress, uint16_t MemAddress, uint8_t pData, uint32_t Timeout);

uint8_t Wait_flag_set(uint32_t volatile *pointer, uint16_t state,uint32_t Timeout, uint32_t Timestart);
uint8_t Wait_flag_reset(uint32_t volatile *pointer, uint16_t state,uint32_t Timeout, uint32_t Timestart);
void Clear_addr_flag (void);

