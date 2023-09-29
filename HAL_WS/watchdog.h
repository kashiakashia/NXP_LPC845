#include "stm32l0xx_hal.h"


void    Watchdog_Init (uint16_t reload, uint16_t presc);                        //  init watchdog for period <period_ms>
void    Watchdog_Refresh (void);                                                //  refersh watchdog counter


