#include "stm32l0xx_hal.h"


//  ********************************************************************
//  **************   GPIOx for EXTI interrupt **************************

void EXTI_Config_Pin (uint8_t nr, GPIO_TypeDef* GPIOx);                         //  config pin <nr> port <GPIOx> for EXTI interrupt
void EXTI_Config_Interrupt (uint8_t nr, uint8_t edge);                          //  enable EXTI interrupt and set priority for pin <nr> port <GPIOx> 
void EXTI_Config_PVD (void);                                                    //  config EXTI for PVD interrupt

void    Water_Detect_Pins_Config (void);                                        //  konfiguracja przerwania od detekcji wody

