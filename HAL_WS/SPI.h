#include "LPC8xx.h"

uint16_t    HW_SPI_InOut (uint16_t txData, SPI_TypeDef *SPI);                   //  transmisja po 1 bajtu po SPI
void        Init_SPI (SPI_TypeDef *SPI);                                        //  konfiguracja kana³u SPI
void        SPI_Set_CS_Mode (uint16_t mode);                                    //  set CS\ as GPIO or ALT-FUN


void        RFM69_WriteBuffer (uint8_t addr, uint8_t *buffer, uint8_t size);    //  wpisz blok danych do bufora
void        RFM69_ReadBuffer (uint8_t addr, uint8_t *buffer, uint8_t size);     //  czytaj blok danych z SX1276

void        RFM69_Write_Single_Byte (uint16_t addr_data);                       //  wpisz 1 bajt do RFM69
uint16_t    RFM69_Read_Single_Byte (uint16_t addr);                             //  czytaj 1 bajt z RFM69




