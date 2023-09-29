#include "SPI.h"
#include "GPIO.h"
#include "GPIO_const.h"
#include "main.h"

//#include "..\Src\AppConf.h"




#define     RFM69_SET_CS_0      (GPIOA->BSRR = (GPIO_PIN_4 << 16))              //  ustaw pin CS\ w 0
#define     RFM69_SET_CS_1      (GPIOA->BSRR = GPIO_PIN_4)                      //  ustaw pin CS\ w 1


uint16_t    HW_SPI_InOut (uint16_t txData, SPI_TypeDef *SPI)                    //  transmisja po 1 bajtu po SPI
{
#define     BUSY            0x80                                                //  bit 7 of SPI->SR, if set, transmitter busy
#define     TXE             2                                                   //  bit 1 of SPI->SR, if set, transmitter is ready 
#define     RXNE            1                                                   //  bit 0 of SPI->SR, if set, receiver has data to read
 
uint32_t    n = 0;

//  send character with timeout

    SPI->DR = txData;
    
    while ((SPI->SR & BUSY) && (n < 100))
        n++;
    
//  return read data
    
    return (SPI->DR);
}



void    Init_SPI (SPI_TypeDef *SPI)                                              //  konfiguracja kana³u SPI
{
//  init GPIO's

    Init_Pin_GPIO (OUT_PP_NP,        4, GPIOA);                                 //  pin CS\ for SPI
//    Init_Pin_GPIO (ALT_PP_NP + ALT0, 4, GPIOA);                                 //  pin CS\ for SPI
    Init_Pin_GPIO (ALT_PP_NP + ALT0, 5, GPIOA);                                 //  SCK     for SPI
    Init_Pin_GPIO (ALT_PP_NP + ALT0, 6, GPIOA);                                 //  MISO    for SPI
    Init_Pin_GPIO (ALT_PP_NP + ALT0, 7, GPIOA);                                 //  MOSI    for SPI
    
    for (int k = 4;  k < 8;  k++)
        Init_Speed_GPIO (VERY_HIGH_SPEED, k, GPIOA);
    
//  init SPI registers
     
    if (SPI == SPI1)                                                            //  enable clock for SPI2
        RCC->APB2ENR |= 1 << 12;                                                
    if (SPI == SPI2)                                                            //  enable clock for SPI2
        RCC->APB1ENR |= 1 << 14;                                                
    
 
    SPI1->CR1 = 0x304;                                                          //  bit 9 SSM   slave management enabled
//  SPI1->CR1 = 0x004;                                                          //  bit 9 SSM   slave management enabled
                                                                                //  bit 8 SSI   internal slave select
                                                                                //  bit 5..3    baud rate fclk / 2
                                                                                //  bit 2       master select
    
//    SPI1->CR2 |= 0xF08;                                                         //  enable hardware CS control, Motorola mode
    SPI1->CR1 |= 0x40;                                                          //  enable SPI

}


void    RFM69_WriteBuffer (uint8_t addr, uint8_t *buffer, uint8_t size)         //  wpisz blok danych do bufora
{
    RFM69_SET_CS_0;                                                             //  ustaw pin CS\ w 0
    HW_SPI_InOut (addr | 0x80, SPI1);                                           //  wyœlij adres z ustawionym 7-mym bitem - pewnie ten bit ustawia tryb WRITE
    
//  wyœlij blok danych
    
    for (short i = 0; i < size; i++)
        HW_SPI_InOut (buffer [i], SPI1);

    RFM69_SET_CS_1;                                                             //  ustaw pin CS\ w 1
}
                                                      

void    RFM69_ReadBuffer (uint8_t addr, uint8_t *buffer, uint8_t size)          //  czytaj blok danych z RFM69
{
    RFM69_SET_CS_0;                                                             //  ustaw pin CS\ w 0
    HW_SPI_InOut (addr & 0x7F, SPI1);                                           //  wyœlij adres ze zgaszonym 7-mym bitem - ten bit ustawia tryb READ

//  czytaj blok danych (wysy³aj cokolwiek, tutaj wysy³amy zera)
    
    for (short i = 0; i < size; i++)
        buffer[i] = HW_SPI_InOut (0, SPI1);

    RFM69_SET_CS_1;                                                             //  ustaw pin CS\ w 1
} 


void    RFM69_Write_Single_Byte (uint16_t addr_data)                            //  wpisz 1 bajt do RFM69
{
uint16_t n = 0;
uint16_t k;
    
//  swap bytes in <addr_data>

    k = addr_data << 8;
    k |= addr_data >> 8;
    
//  send character with timeout
    
    SPI1->DR = k | 0x80;                                                        //  send data << 16 | addr (16 bits)
    while ((SPI1->SR & BUSY) && (n++ < 100));
}


uint16_t    RFM69_Read_Single_Byte (uint16_t addr)                              //  czytaj 1 bajt z RFM69
{
uint16_t n = 0;

    RFM69_SET_CS_0;                                                             //  ustaw pin CS\ w 0

//  send character with timeout

    SPI1->DR = addr;                                                            //  send addr 8 bits then next 8 clocks to read data
    while ((SPI1->SR & 0x80) && (n++ < 100));
    
    n = SPI1->DR;                                                               //  wyrzuæ poprzeni¹ dan¹    
    RFM69_SET_CS_1;                                                             //  ustaw pin CS\ w 1

    return (n >> 8);
}


void RFM69_WriteFifo (uint8_t *buffer, uint8_t size)                            //  wpisz blok danych do FIFO
{
    RFM69_WriteBuffer (0, buffer, size);                                        //  wpisz dane pod adres 0
}


void RFM69_ReadFifo (uint8_t *buffer, uint8_t size)                             //  czytaj blok danych z FIFO
{
    RFM69_ReadBuffer (0, buffer, size);                                         //  czytaj dane z adresu 0
} 






