#include "NXP_Sys_Tik.h"
#include "NXP_NVIC.h"


uint32_t Sys_Tick_Config (uint32_t reload)                                      //  SysTik configuration
{
    if ((reload - 1UL) > SysTick_LOAD_RELOAD_Msk) 
        return (1UL);                                                           //  Reload value impossible 
 

    SysTick->LOAD  = (uint32_t)(reload - 1UL);                                  //  set reload register
    NVIC_Set_Priority (SysTick_IRQn, 1);                                        //  set Priority for Systick Interrupt 
    
    SysTick->VAL   = 0UL;                                                       //  Load the SysTick Counter Value 
    
//  Enable SysTick IRQ and SysTick Timer
    
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

    return (0);                                                                 //  Function successful 
}

