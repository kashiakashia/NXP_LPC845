#include "stm32l0xx_hal.h"

short       Set_PVD_Level (short level);                                        //  set PVD voltage detector
void        PVD_config (IRQn_Type IRQn, uint32_t priority);                     // konfiguracja modu³u PVD
uint16_t    *PVD_Service (uint16_t pvd_alarm);                                  //  service for PVD event

void        PVD_IRQHandler (void);                                              //  przerwanie od modu³u PVD gdy napiêcie spada poni¿ej 2.5 V

//  definition of PVD treshold registers

#ifndef     PVD_
    #define     PVD_

#define     PVD_THRE_0_1V9      0                                               //  (0x00000000U)   in HAL: PWR_PVDLEVEL_0
#define     PVD_THRE_1_2V1      1                                               //  (0x00000020U)   in HAL: PWR_PVDLEVEL_1
#define     PVD_THRE_2_2V3      2                                               //  (0x00000040U)   in HAL: PWR_PVDLEVEL_2
#define     PVD_THRE_3_2V5      3                                               //  (0x00000060U)   in HAL: PWR_PVDLEVEL_3
#define     PVD_THRE_4_2V7      4                                               //  (0x00000080U)   in HAL: PWR_PVDLEVEL_4
#define     PVD_THRE_5_2V9      5                                               //  (0x000000A0U)   in HAL: PWR_PVDLEVEL_5
#define     PVD_THRE_6_3V1      6                                               //  (0x000000C0U)   in HAL: PWR_PVDLEVEL_6
    
#define     PVD_EXT_INPUT       7
    
#endif

