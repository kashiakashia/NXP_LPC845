#include "EXTI.h"
#include "EXTI_const.h"
#include "NVIC.h"
#include "PVD.h"
#include "GPIO.h"


void    Water_Detect_Pins_Config (void)                                         //  konfiguracja przerwania od detekcji wody
{   
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;                                          //  enable clock for PWR module
    
//  set priority and enable IRQ for PA8
        
    NVIC_Set_Priority (EXTI4_15_IRQn, 3);                                       //  priorytet 3 dla przerwania od pinu PA8
    NVIC_Enable_IRQ (EXTI4_15_IRQn);    
    
//  konfiguracja portu A i EXTI od czujnika poziomu wody
    
    EXTI_Config_Pin (8, GPIOA);                                                 //  enable interrupt for pin 8 port B
    EXTI_Config_Interrupt (8, EXTI_FALLING_EDGE);                               //  configure interrupt for pin 8

//  set priority and enable IRQ for PB1
    
    NVIC_Set_Priority (EXTI0_1_IRQn, 3);                                        //  priorytet 3 dla przerwania od pinu PB1
    NVIC_Enable_IRQ (EXTI0_1_IRQn);    
    
//  konfiguracja portu B i EXTI od czujnika poziomu wody
    
    EXTI_Config_Pin (1, GPIOB);                                                 //  enable interrupt for pin 1 port B
    EXTI_Config_Interrupt (1, EXTI_FALLING_EDGE);                               //  configure interrupt for pin 1
    
}



void EXTI_Config_Pin (uint8_t nr, GPIO_TypeDef* GPIOx)                          //  config pin <nr> port <GPIOx> for EXTI interrupt
{
uint16_t k, mask, config, shift, adres;

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                                       //  enable clock for SYSCONFIG module
        
    adres = nr / 4;                                                             //  ka¿dy port ma 16 pinów. Numer pinu / 4 to adres rejestru.
    shift = (nr & 3) * 4;                                                       //  Numer pinu % 4 okreœla 4 bity wybieraj¹ce port generuj¹cy przerwanie
    
//  wybór portu
    
    if (GPIOx == GPIOA)
        config = 0;
    if (GPIOx == GPIOB)
        config = 1;
    if (GPIOx == GPIOC)
        config = 2;
    if (GPIOx == GPIOH)
        config = 3;
        
//  modyfikuj odpowiednie 4 bity
    
    mask = 0x0F << shift;
    k = SYSCFG->EXTICR [adres] & ~mask;
    k |= config << shift;
    SYSCFG->EXTICR [adres] = k;
}


void EXTI_Config_Interrupt (uint8_t nr, uint8_t edge)                           //  enable EXTI interrupt and set priority for pin <nr> port <GPIOx> 
{
uint16_t    mask = 1 << nr;

    EXTI->IMR |= mask;                                                          //  enable interrupt in mask register
    
    if (edge & EXTI_RISING_EDGE)                                                //  enable interrupt from rising edge
        EXTI->RTSR |= mask;
    
    if (edge & EXTI_FALLING_EDGE)                                               //  enable interrupt from Falling edge
        EXTI->FTSR |= mask;
}


#define EXTI_IMR_MR16_Pos                   (16U)                              
#define EXTI_IMR_MR16_Msk                   (0x1U << EXTI_IMR_MR16_Pos)        /*!< 0x00010000 */
#define EXTI_IMR_MR16                       EXTI_IMR_MR16_Msk                  /*!< Interrupt Mask on line 16 */

#define PWR_EXTI_LINE_PVD                   ((uint32_t)EXTI_IMR_MR16)  /*!< External interrupt line 16 Connected to the PVD EXTI Line */


void EXTI_Config_PVD (void)                                                     //  config EXTI for PVD interrupt
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                                       //  enable clock for SYSCONFIG module
    
    EXTI->IMR |= PWR_EXTI_LINE_PVD;                                             //  enable interrupt in mask register
    EXTI->RTSR |= PWR_EXTI_LINE_PVD;                                            //  enable interrupt from rising edgr
}


