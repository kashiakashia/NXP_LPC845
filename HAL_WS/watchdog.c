#include "watchdog.h"
#include "..\TIME\time.h"


#define IWDG_KEY_RELOAD               ((uint32_t)0xAAAAU)                       //  IWDG Reload Counter Enable   
#define IWDG_KEY_ENABLE               ((uint32_t)0xCCCCU)                       //  IWDG Peripheral Enable       
#define IWDG_KEY_WRITE_ACCESS_ENABLE  ((uint32_t)0x5555U)                       //  IWDG KR Write Access Enable  
#define IWDG_KEY_WRITE_ACCESS_DISABLE ((uint32_t)0x0000U)                       //  IWDG KR Write Access Disable 


void Watchdog_Init (uint16_t reload, uint16_t presc)                            //  init watchdog for period <period_ms>
{
uint32_t k = 0;

    RCC->CSR |= RCC_CSR_LSION;                                                  //  enable LSI clock
         
  /* (6) Refresh counter */
    
    IWDG->KR = IWDG_KEY_ENABLE;                                                 //  Activate IWDG (not needed if done in option bytes)     
    IWDG->KR = IWDG_KEY_WRITE_ACCESS_ENABLE;                                    //  Enable write access to IWDG registers 
    IWDG->PR = presc;                                                           //  load prescaler
    IWDG->RLR = reload;                                                         //  Set reload value
    
//  wait for status == 0 -> add time out here for a robust application 
    
    while (IWDG->SR)   {                                                        
        k++;
        if (k > 10000)
            break;
    }   
    
    Watchdog_Refresh ();
}


void Watchdog_Refresh (void)                                                    //  refersh watchdog counter
{
    //return; //!!!
  
    IWDG->KR = IWDG_KEY_RELOAD;                                                 //  reload watchdog    
}


