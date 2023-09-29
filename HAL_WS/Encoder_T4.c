#include "Encoder_T4.h"
#include "GPIO_const.h"
#include "GPIO.h"


void    Encoder_T4_Init_GPIO (void)                                             //  input pins configuration
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;                                         //  Timer 4 module clock enable 
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

//  TIM4 GPIO Configuration    
//      PB6     ------> TIM4_CH1
//      PB7     ------> TIM4_CH2 
        
//    Init_Pin_GPIO (ALT_INP_DIG_NP + ALT2, 6, GPIOB);                          //  czemu te piny s¹ inicjowane jako output?????????
//    Init_Pin_GPIO (ALT_INP_DIG_NP + ALT2, 7, GPIOB);  
    
    Init_Pin_GPIO (ALT_PP_NP + ALT2, 6, GPIOB);
    Init_Pin_GPIO (ALT_PP_NP + ALT2, 7, GPIOB);  
    
}


void    Encoder_T4_Init_Regs (void)                                             //  init T4 registers
{
    Encoder_T4_Init_GPIO ();
    
    TIM4->CR1 = 0x200;                                                          //  clock / 4
    TIM4->ARR = 0x7FFF;                                                         //  timer range 7FFF
    TIM4->PSC = 0;                                                              //  prescaler 0
     
    TIM4->EGR = TIM_EGR_UG;                                                     //  Generate an update event to reload the Prescaler 

    TIM4->CCMR1 = 0xF1F1;
    TIM4->CCER = 0x22;
    TIM4->SMCR = 0x01;
}


void    Encoder_T4_Start (void)                                                 //  start encoder
{
    TIM4->CCER = 0x33; 
    TIM4->CR1 |= 1;                                                             //  enable T4
    TIM4->CNT=0x4000;
}
