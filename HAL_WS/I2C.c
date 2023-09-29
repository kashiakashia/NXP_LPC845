#include "I2C.h"
#include "GPIO.h"
#include "GPIO_const.h"
#include "..\Code-ARM\TIME\time.h"


void        I2C_Init (void)                                                     //  init pins and i2C registers
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;                                          //  enable clock for PORTB
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;                                         //  enable clock for I2C(2) 

    Init_Pin_GPIO (ALT_OD_PU + ALT4 + 1, 10, GPIOB);
    Init_Pin_GPIO (ALT_OD_PU + ALT4 + 1, 11, GPIOB);
    
    I2C2->CR2 |= 2;                                                             //  clock req. 2 MHz
    I2C2->CCR |= 0x0A;                                                          //  speed
    I2C2->TRISE = 3;                                                            //  edge rise time
    I2C2->OAR1 = 0x4000;                                                        //  bit 14 must be '1'
    I2C2->CR1 |= 1;                                                             //  enable I2C module
}


uint8_t     I2C_Mem_Read (uint16_t DevAddress, uint16_t MemAddress, uint32_t Timeout)
{
    uint32_t Timestart=Time_Service(0);
    
    if(!Wait_flag_reset(&(I2C2->SR2),0x0002,Timeout,Timestart))                 //wait busy flag reset
    return 0;
    
    I2C2->CR1 &= 0xF7FF;                                                        //clear POS 
    
    I2C2->CR1 |= 0x0400;                                                        //eneable Ackonwledge
    I2C2->CR1 |= 0x0100;                                                        //generate start
    if(!Wait_flag_set(&(I2C2->SR1),0x0001,Timeout,Timestart))
    return 0;
        
    I2C2->DR = DevAddress & (~I2C_OAR1_ADD0);                                   //send slave addres
                                                       
    if(!Wait_flag_set(&(I2C2->SR1),0x0002,Timeout,Timestart))                   //wait ADDR flag set
    return 0;

     Clear_addr_flag ();                                                           //clear ADDR flag
                                                                                //wait TXE flag set
    if(!Wait_flag_set(&(I2C2->SR1),0x0080,Timeout,Timestart))
    return 0;

    I2C2->DR = MemAddress&0x00FF;                                               //send memory addres
                                                                                //wait TXE flag set
    if(!Wait_flag_set(&(I2C2->SR1),0x0080,Timeout,Timestart))
    return 0;
    
    I2C2->CR1 |= 0x0100;                                                        //generate (re) start
                                                                                //wait SB flag
    if(!Wait_flag_set(&(I2C2->SR1),0x0001,Timeout,Timestart))
    return 0;
    
    I2C2->DR = DevAddress | (I2C_OAR1_ADD0);                                    //send slave addres
                                                                                //wait ADDR flag set
    if(!Wait_flag_set(&(I2C2->SR1),0x0002,Timeout,Timestart))
    return 0;
    
    I2C2->CR1 &= 0xFBFF; //disable Acknowledge
        
     Clear_addr_flag ();                                                          //clear ADDR flag
    
    I2C2->CR1 |= 0x0200;                                                        //generate stop
    
                                                                                //wait RXNE flag set
        if(!Wait_flag_set(&(I2C2->SR1),0x0040,Timeout,Timestart))
    return 0;
    
    return (uint8_t) I2C2->DR ;  
}


uint8_t I2C_Mem_Write (uint16_t DevAddress, uint16_t MemAddress, uint8_t pData, uint32_t Timeout)
{   
    uint32_t Timestart=Time_Service(0);
   
    if(!Wait_flag_reset(&(I2C2->SR2),0x0002,Timeout,Timestart))                 //wait busy flag reset
    return 0;
   
     I2C2->CR1 &= 0xF7FF;                                                       //clear POS 
     I2C2->CR1 |= 0x0100;                                                       //generate start
                                                                                //wait SB flag
    if(!Wait_flag_set(&(I2C2->SR1),0x0001,Timeout,Timestart))
    return 0;
    
    I2C2->DR = DevAddress & (~I2C_OAR1_ADD0);                                   //send slave addres
                                                                                //wait ADDR flag set
    if(!Wait_flag_set(&(I2C2->SR1),0x0002,Timeout,Timestart))
    return 0;
    
     Clear_addr_flag ();                                                        //clear ADDR flag                                                          //clear ADDR flag
                                                                                //wait TXE flag set
    if(!Wait_flag_set(&(I2C2->SR1),0x0080,Timeout,Timestart))
    return 0;
    
    I2C2->DR = MemAddress&0x00FF;                                               //send memory addres
    
                                                                                //wait TXE flag set
    if(!Wait_flag_set(&(I2C2->SR1),0x0080,Timeout,Timestart))
    return 0;
    I2C2->DR = pData;
                                                                                //wait BTF flag set   
    if(!Wait_flag_set(&(I2C2->SR1),0x0004,Timeout,Timestart))
    return 0;
    
    I2C2->CR1 |= 0x0200;
    return 1;
}
uint8_t Wait_flag_set (uint32_t volatile *pointer, uint16_t state,uint32_t Timeout, uint32_t Timestart)
{
     while (!((*pointer)&state))                                                  
    {
        if(Time_Service(0)-Timestart>Timeout)
        return 0;
    }
    return 1;
}
uint8_t Wait_flag_reset (uint32_t volatile *pointer, uint16_t state,uint32_t Timeout, uint32_t Timestart)
{
     while ((*pointer)&state)                                                  
    {
        if(Time_Service(0)-Timestart>Timeout)
        return 0;
    }
    return 1;
}    
 
void Clear_addr_flag (void)
{
      uint32_t tmpreg = 0x00U;                  
      tmpreg = I2C2->SR2;     
      UNUSED (tmpreg); 
}
