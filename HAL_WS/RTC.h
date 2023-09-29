#include "stm32l1xx_hal.h"

void LSE_Config (void);                                                         //  config LSE 32 kHz external clock
void RTC_Auto_Reload_Timer_Config (uint16_t reload_value, uint16_t priority);   //  config auto-reload timer for wakeup from STOP mode

void RTC_WKUP_IRQHandler (void);                                                //  RTC wake-up timer interrupt
