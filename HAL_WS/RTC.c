#include "RTC.h"
#include "NVIC.h"
#include "..\TIME\time.h"


void RTC_WKUP_IRQHandler (void)                                                 //  RTC wake-up timer interrupt
{
    RTC->ISR &= ~(RTC_FLAG_WUTF);                                               //  clear RTC_FLAG_WUTF flag
    EXTI->PR = RTC_EXTI_LINE_WAKEUPTIMER_EVENT;                                 //  Clear the EXTI's line Flag for RTC WakeUpTimer   
    
    Time_Service (1);   
}


void LSE_Config (void)                                                          //  config LSE 32 kHz external clock
{
uint32_t    temp;

//  32 kHz LSE oscillator setup and start
    
    RCC->APB1ENR |= 1 << 28;                                                    //  enable clock to PWR module (set PWREN bit)
    PWR->CR |= 1 << 8;                                                          //  enable write access to Backup domain 

    while (!(PWR->CR & (1 << 8)));
    
    temp = RCC->CSR & ~(3 << 16);                                               //  save content of CSR
    RCC->CSR |= 1 << 23;                                                        //  reset RTC domain
    RCC->CSR &= ~(1 << 23);
    RCC->CSR = temp;                                                            //  restore content of CSR
    
    RCC->CSR |= 1 << 16;                                                        //  choose LSE clock for RTC
    RCC->CSR |= 1 << 22;                                                        //  enable RTC clock
    RCC->CSR |= 1 << 8;                                                         //  enable LSE (set bit LSEON)
    while (!(RCC->CSR & (1 << 9)));                                             //  wait for LSE start
    
    PWR->CR &= ~(1 << 8);                                                       //  disable write access to Backup domain 
//  RCC->APB1ENR &= ~(1 << 28);                                                 //  disable clock to PWR module (set PWREN bit)
}


void RTC_Auto_Reload_Timer_Config (uint16_t reload_value, uint16_t priority)    //  config auto-reload timer for wakeup from STOP mode
{
    PWR->CR |= 1 << 8;                                                          //  enable write access to Backup domain 
    
//  unlock access to RTC registers    
    
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    
    RTC->CR = 0;
    RTC->CR &= ~RTC_CR_WUTE;                                                    //  disable wake-up timer
    RTC->ISR = ~RTC_FLAG_WUTF;                                                  //  clear wake-up flag  !!!!!!!!!!!!!!!!!
        
//  RTC->CR |= 0x4403;                                                          //  enable wake-up timer & interrupt from wake-up timer
                                                                                //  select prescaler / 2
    RTC->WUTR = reload_value;
    RTC->CR &= (uint32_t)~RTC_CR_WUCKSEL;                                       //  Clear the Wakeup Timer clock source bits in CR register 
    RTC->CR |= (uint32_t) RTC_WAKEUPCLOCK_RTCCLK_DIV2;                          //  Configure the clock source
        
//  RTC WakeUpTimer Interrupt Configuration: EXTI configuration 
    
    EXTI->IMR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT;                               //  Enable interrupt on the RTC WakeUp Timer associated Exti line
    EXTI->RTSR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT;                              //  Enable rising edge trigger on the RTC WakeUp Timer associated Exti line

//  NVIC configuration
    
    NVIC_Enable_IRQ (RTC_WKUP_IRQn);
    NVIC_Set_Priority (RTC_WKUP_IRQn, priority);
    
//  enable wake-up timer & enable interrupt
    
    RTC->CR |= RTC_IT_WUT;                                                      //  Configure the Interrupt in the RTC_CR register 
    RTC->CR |= RTC_CR_WUTE;                                                     //  enable wake-up timer
      
    RTC->WPR = 0xFF;                                                            //  lock access to RTC registers        
}






