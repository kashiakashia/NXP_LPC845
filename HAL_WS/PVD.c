#include "PVD.h"
#include "..\TIME\time.h"

#include "..\HAL_WS\NVIC.h"
#include "..\HAL_WS\EXTI.h"


void    PVD_IRQHandler (void)                                                   //  przerwanie od modu³u PVD gdy napiêcie spada poni¿ej 2.5 V
{ 
    PVD_Service (1);
    EXTI->PR = PWR_EXTI_LINE_PVD;                                               //  clear interrupt flag
}



short   Set_PVD_Level (short level)                                             //  set PVD voltage detector, returns result
{
#define     V_MASK     ~(7 << 5)
        
        
    PWR->CR &= V_MASK;                                                          //  clear previous setting
    PWR->CR |= level ;                                                          //  set voltage detector 
     
    PWR->CR |= 0x10;                                                            //  0x10 = enable PVD
    Delay_ms (4);                                                               //  wait for 3 ms  2018-11-12
    
    return ((PWR->CSR & 4) > 0);
}


      
void    PVD_config (IRQn_Type IRQn, uint32_t priority)                          //  konfiguracja modu³u PVD
{    
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;                                          //  enable clock for PWR module
    
    NVIC_Set_Priority (IRQn, priority);
    NVIC_Enable_IRQ (IRQn);    

    EXTI_Config_PVD ();
    
    Set_PVD_Level (PWR_PVDLEVEL_3);
}


            
uint16_t   *PVD_Service (uint16_t pvd_alarm)                                    //  service for PVD event
{
static  uint16_t    pvd_cnt;
    
    if (pvd_alarm && (pvd_cnt < 100))
        pvd_cnt++;
    
//  if PVDO flag is active, set bit 15
    
    if (PWR->CSR & PWR_CSR_PVDO_Msk)                                            
        pvd_cnt |= 0x8000;
    else
        pvd_cnt &= ~0x8000;
        
    return (&pvd_cnt);
}
    
    
      

