//#include "..\HAL_Definicje\stm32l0xx_hal.h"


#ifndef STRUCT_GPIO_
    #define STRUCT_GPIO_


//  EXTI interrupt configuration

#define     EXTI_RISING_EDGE    1
#define     EXTI_FALLING_EDGE   2
#define     EXTI_ANY_EDGE       3
    

//  bits for alternate functions

#define     ALT0                       (16 << 8)
#define     ALT1                        (1 << 8)
#define     ALT2                        (2 << 8)
#define     ALT3                        (3 << 8)
#define     ALT4                        (4 << 8)
#define     ALT5                        (5 << 8)
#define     ALT6                        (6 << 8)
#define     ALT7                        (7 << 8)
#define     ALT8                        (8 << 8)
#define     ALT9                        (9 << 8)
#define     ALT10                      (10 << 8)
#define     ALT11                      (11 << 8)
#define     ALT12                      (12 << 8)
#define     ALT13                      (13 << 8)
#define     ALT14                      (14 << 8)
#define     ALT15                      (15 << 8)

//  speed definitions

#define     LOW_SPEED                   0
#define     MEDIUM_SPEED                1
#define     HIGH_SPEED                  2
#define     VERY_HIGH_SPEED             3

//  do not modify pin

#define     NO_CHANGE                   0x00                //  keep previous config

//  all pins medium speed - normal inputs 

#define     INPUT_DIG_NP                0x40                //  digital input   No PULL
#define     INPUT_DIG_PU                0x44                //  digital input   internal pull-up
#define     INPUT_DIG_PD                0x48                //  digital input   internal pull-up
#define     INPUT_AN_NP                 0x70                //  analog input    no pull up / down
#define     INPUT_AN_PU                 0x74                //  analog input    internal pull-up
#define     INPUT_AN_PD                 0x78                //  analog input    internal pull-down

//  all pins medium speed - alternate inputs 

#define     ALT_INP_DIG_NP              0x60                //  alternate digital input
#define     ALT_INP_DIG_PU              0x64                //  alternate digital input   internal pull-up
#define     ALT_INP_DIG_PD              0x68                //  alternate digital input   internal pull-up

//  all pins medium speed - normal outputs

#define     OUT_PP_NP                   0x50                //  output push-pull    no pull-up
#define     OUT_PP_PU                   0x54                //  output push-pull    pull-up
#define     OUT_PP_PD                   0x58                //  output push-pull    pull-down
#define     OUT_OD_NP                   0x52                //  output open drain   no pullup
#define     OUT_OD_PU                   0x56                //  output open drain   pull-up
#define     OUT_OD_PD                   0x5A                //  output open drain   pull-down

//  all pins medium speed - alternate outputs

#define     ALT_PP_NP                   0x60                //  alternate output push-pull    no pull-up
#define     ALT_PP_PU                   0x64                //  alternate output push-pull    pull-up
#define     ALT_PP_PD                   0x68                //  alternate output push-pull    pull-down

#define     ATL_OD_NP                   0x62                //  alternate output open drain   no pullup
#define     ALT_OD_PU                   0x66                //  alternate output open drain   pull-up
#define     ALT_OD_PD                   0x6A                //  alternate output open drain   pull-down


#define     GPIO_PIN_0                 ((uint16_t)0x0001U)  /* Pin 0 selected    */
#define     GPIO_PIN_1                 ((uint16_t)0x0002U)  /* Pin 1 selected    */
#define     GPIO_PIN_2                 ((uint16_t)0x0004U)  /* Pin 2 selected    */
#define     GPIO_PIN_3                 ((uint16_t)0x0008U)  /* Pin 3 selected    */
#define     GPIO_PIN_4                 ((uint16_t)0x0010U)  /* Pin 4 selected    */
#define     GPIO_PIN_5                 ((uint16_t)0x0020U)  /* Pin 5 selected    */
#define     GPIO_PIN_6                 ((uint16_t)0x0040U)  /* Pin 6 selected    */
#define     GPIO_PIN_7                 ((uint16_t)0x0080U)  /* Pin 7 selected    */
#define     GPIO_PIN_8                 ((uint16_t)0x0100U)  /* Pin 8 selected    */
#define     GPIO_PIN_9                 ((uint16_t)0x0200U)  /* Pin 9 selected    */
#define     GPIO_PIN_10                ((uint16_t)0x0400U)  /* Pin 10 selected   */
#define     GPIO_PIN_11                ((uint16_t)0x0800U)  /* Pin 11 selected   */
#define     GPIO_PIN_12                ((uint16_t)0x1000U)  /* Pin 12 selected   */
#define     GPIO_PIN_13                ((uint16_t)0x2000U)  /* Pin 13 selected   */
#define     GPIO_PIN_14                ((uint16_t)0x4000U)  /* Pin 14 selected   */
#define     GPIO_PIN_15                ((uint16_t)0x8000U)  /* Pin 15 selected   */
#define     GPIO_PIN_All               ((uint16_t)0xFFFFU)  /* All pins selected */

/*  struktura GPIO

    GPIOA->OSPEEDR = 0x0C3C00F0;        //  speed register    0x00000000 dla innych portów
                                        //      00  = low speed
                                        //      01  = medium speed
                                        //      10  = high speed
                                        //      11  = very high speed
    
    GPIOA->MODER = 0x2BE9F5F4;          //  mode register   0xFFFFFFFF  dla innych portów
                                        //      00  = input
                                        //      01  = general otput
                                        //      10  = alternate
                                        //      11  = analog
        
    GPIOA->PUPDR = 0x64000000;          //  pull up/down register    0x00000000 dla innych portów
                                        //      00  = no pull
                                        //      01  = pull up
                                        //      10  = pull down
                                        //      11  = reserved
    
    GPIOA->OTYPER = 0;                  //  output type register 0 = PUSH-PULL,  1 = OD
    
//  GPIOA->IDR                          //  input port
    
    GPIOA->ODR = 0;                     //  output port
    
//  GPIOA->BSRR = 0;                    //  bit set / reset register
                                        //      bits 31...16    - '1' resets corresponding ODR bit
                                        //      bits 15...0     - '1' sets corresponding ODR bit
    
//  GPIOA->BRR = 0;                     //  bit reset register
                                        //      bits 15...0     - '1' resets corresponding ODR bit        

*/

#endif

