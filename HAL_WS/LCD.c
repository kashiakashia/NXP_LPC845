#include "LCD.h"
#include "GPIO_const.h"
#include "GPIO.h"

#include "..\TIME\time.h"


void    LCD_Init_GPIO (void)                                                    //  init GPIO for LCD
{
uint16_t    k;

//  enable clock for LCD ports    
//  clock for  ---------  port A  ----------- port B ------------- port C ------------ port D -------------- port E ---------

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOEEN;

//  init all LCD pins
    
    for (int n = 0;  n < 16;  n++)  {
        k = 1 << n;
        if (k & 0x87CC)                                                         //  init port A for LCD
            Init_Pin_GPIO (ALT_PP_NP | ALT11, n, GPIOA);
        if (k & 0x3303)                                                         //  init port B for LCD
            Init_Pin_GPIO (ALT_PP_NP | ALT11, n, GPIOB);
        if (k & 0x1FFF)                                                         //  init port C for LCD
            Init_Pin_GPIO (ALT_PP_NP | ALT11, n, GPIOC);
        if (k & 0xFC00)                                                         //  init port D for LCD
            Init_Pin_GPIO (ALT_PP_NP | ALT11, n, GPIOD);
        if (k & 0x000F)                                                         //  init port E for LCD
            Init_Pin_GPIO (ALT_PP_NP | ALT11, n, GPIOE);
    }

}

void    LCD_Init_Regs (void)                                                    //  init LCD registers
{
    RCC->APB1ENR |= RCC_APB1ENR_LCDEN;                                          //  enable clock for LCD domain

    LCD->CR &= ~1;                                                              //  disable LCD
        
//  light on all the pixels    
    
    for (int n = 0;  n < LCD_RAM_REGISTER15;  n++)
        LCD->RAM [n] = 0xFFFFFFFF;                                              

    
    LCD->SR |= LCD_SR_UDR;                                                      //  Enable the display request    
//  LCD->FCR    = 0x00BC1130;
//  LCD->FCR    = 0x008C11C0;
    LCD->FCR    = 0x008C0DC0;
    Delay_ms (5);                                                               //  Wait until LCD Frame Control Register Synchronization flag (FCRSF) is set 
  
    LCD->CR     = 0x0000004C;                                                   //  set control register
    Delay_ms (5);                                                               
    LCD->CR |= 1;                                                               //  enable LCD      
}


