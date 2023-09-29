#include "SPI.h"
#include <stdint.h>
#include "swm.h"

//#include "..\Src\AppConf.h"




#define     RFM69_SET_CS_0              (GPIOA->BSRR = (GPIO_PIN_4 << 16))      //  ustaw pin CS\ w 0
#define     RFM69_SET_CS_1              (GPIOA->BSRR = GPIO_PIN_4)              //  ustaw pin CS\ w 1

#define     CS_SOFT_MODE_CONTROL        1                                       //  pin CS\ jako GPIO
#define     CS_HARDWARE_MODE_CONTROL    0                                       //  pin CS\ jako ALT FUNCT


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

    Init_Pin_GPIO (ALT_PP_NP + ALT0, 5, GPIOA);                                 //  SCK     for SPI
    Init_Pin_GPIO (ALT_PP_NP + ALT0, 6, GPIOA);                                 //  MISO    for SPI
    Init_Pin_GPIO (ALT_PP_NP + ALT0, 7, GPIOA);                                 //  MOSI    for SPI
    
//  init SPI registers
     
    if (SPI == SPI1)                                                            //  enable clock for SPI2
        RCC->APB2ENR |= 1 << 12;                                                
    if (SPI == SPI2)                                                            //  enable clock for SPI2
        RCC->APB1ENR |= 1 << 14;                                                
     
    SPI_Set_CS_Mode (CS_HARDWARE_MODE_CONTROL);
}


void    SPI_Set_CS_Mode (uint16_t mode)                                         //  set CS\ as GPIO or ALT-FUN
{
    SPI1->CR1 = 0x304;                                                          //  disable SPI, master mode
    
    if (mode == CS_SOFT_MODE_CONTROL)   {
        
    //  ustaw software sterowanie CS\
        
        SPI1->CR2 = 0x700;                                                      //  transmission 8 bits, TI mode
        SPI1->CR1 |= 0x40;                                                      //  enable SPI

        Init_Pin_GPIO (OUT_PP_NP, 4, GPIOA);                                    //  pin CS\ for SPI as GPIO
        return;
    }
    
//  przywróæ konfiguracjê sprzêtowego sterowania CS\
        
    SPI1->CR2 = 0xF08;                                                          //  transmission 16 bits, enable hardware control    
    SPI1->CR1 |= 0x40;                                                          //  enable SPI
    
    Init_Pin_GPIO (ALT_PP_NP + 1 + ALT0, 4, GPIOA);                             //  pin CS\ for SPI as alternate funct.
}


void    RFM69_WriteBuffer (uint8_t addr, uint8_t *buffer, uint8_t size)         //  wpisz blok danych do bufora
{
//  ustaw software sterowanie CS\
    
    SPI_Set_CS_Mode (CS_SOFT_MODE_CONTROL);
    
    RFM69_SET_CS_0;                                                             //  ustaw pin CS\ w 0    
    HW_SPI_InOut ((addr | 0x80) | (buffer [0] << 8), SPI1);                     //  wyœlij adres z ustawionym 7-mym bitem - ten bit ustawia tryb WRITE
                                                                                //  dodaj do adresu pierwszy bajt danych
//  wyœlij blok danych
    
    for (short i = 1; i < size; i += 2)
        HW_SPI_InOut ((buffer [i] << 8) | buffer [i + 1], SPI1);

    RFM69_SET_CS_1;                                                             //  ustaw pin CS\ w 1

//  przywróæ konfiguracjê sprzêtowego sterowania CS\
    
    SPI_Set_CS_Mode (CS_HARDWARE_MODE_CONTROL);    
}
                                                      

void    RFM69_ReadBuffer (uint8_t addr, uint8_t *buffer, uint8_t size)          //  czytaj blok danych z RFM69
{
uint16_t k;
    
//  ustaw software sterowanie CS\
    
    SPI_Set_CS_Mode (CS_SOFT_MODE_CONTROL);
    
    RFM69_SET_CS_0;                                                             //  ustaw pin CS\ w 0
    k = HW_SPI_InOut (addr & 0x7F, SPI1);                                       //  wyœlij adres ze zgaszonym 7-mym bitem - ten bit ustawia tryb READ
    *buffer = k & 0xFF;                                                         //  pobierz 1 - wszy bajt
    
//  czytaj blok danych (wysy³aj cokolwiek, tutaj wysy³amy zera)
        
    for (short i = 1; i < size; i += 2)   {
        k = HW_SPI_InOut (0, SPI1);
        buffer [i] = k >> 8;
        buffer [i + 1] = k & 0xFF;
    }
    
    RFM69_SET_CS_1;                                                             //  ustaw pin CS\ w 1

//  przywróæ konfiguracjê sprzêtowego sterowania CS\
    
    SPI_Set_CS_Mode (CS_HARDWARE_MODE_CONTROL);    
} 


void    RFM69_Write_Single_Byte (uint16_t addr_data)                            //  wpisz 1 bajt do RFM69
{
uint16_t n = 0;
    
    SPI1->DR = addr_data | 0x8000;                                              //  send (addr << 16) | data (16 bits)
    while ((SPI1->SR & BUSY) && (n++ < 100));
    
    n = SPI1->DR;                                                               //  read and skip data from slave
}


uint16_t    RFM69_Read_Single_Byte (uint16_t addr)                              //  czytaj 1 bajt z RFM69
{
uint16_t n = 0;

//  send character with timeout

    SPI1->DR = addr << 8;                                                       //  send addr 8 bits then next 8 clocks to read data
    while ((SPI1->SR & 0x80) && (n++ < 100));
    
    return (SPI1->DR);                                                          //  podaj odczyt
}






