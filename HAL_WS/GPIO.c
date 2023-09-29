#include "GPIO.h"

uint16_t  GPIO_ReadBit (GPIO_TypeDef* GPIOx, uint16_t nr)                       //  read GPIO bit
{
    return (GPIOx->IDR & nr);
}


void GPIO_ResetBits  (GPIO_TypeDef* GPIOx, uint16_t nr)                         //  clear GPIO bit
{
    GPIOx->ODR &= ~nr;    
}


void GPIO_SetBits  (GPIO_TypeDef* GPIOx, uint16_t nr)                           //  set GPIO bit
{
    GPIOx->ODR |= nr;    
}


void Init_PULLS_GPIO (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx)         //  init pulls up / down for pin <nr> port GPIOx according to config
{
nr *= 2;
uint32_t mask_2_bit = 0x03 << nr;


//  set pull up / down

    config &= 0xFF;
    config = (config >> 2) & 3;
    
    GPIOx->PUPDR &= ~mask_2_bit;
    GPIOx->PUPDR |= config << nr;    
}


void Init_MODE_GPIO (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx)          //  set mode of pin <nr>
{
nr *= 2;
uint32_t mask_2_bit = 0x03 << nr;


//  set pull up / down

    config &= 0xFF;
    config = (config >> 4) & 3;
    
    GPIOx->MODER &= ~mask_2_bit;
    if(nr>30)
    {
        nr=0;
    }
    GPIOx->MODER |= config << nr;    
}


void Init_Speed_GPIO (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx)         //  set speed of pin <nr>
{
nr *= 2;
uint32_t mask_2_bit = 0x03 << nr;


//  set pull up / down

    config &= 0xFF;
    config = (config >> 6) & 3;
    
    GPIOx->OSPEEDR &= ~mask_2_bit;
    GPIOx->OSPEEDR |= config << nr;    
}


void Init_ALT_Fun (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx)            //  init alternate function
{
uint16_t ndx = 0;
uint32_t mask = 0;

//  if there is no ATL config, exit

    config = config >> 8;
    if (!config)
        return;
    
    config &= 0x0F;                                                             //  ALT0 is 16, now it is changed to 0
    
//  evaluate index

    if (nr > 7)   {
        ndx++;
        nr -= 8;
    }

    mask = 0xF << (4 * nr);
    
    GPIOx->AFR [ndx] &= ~mask;
    GPIOx->AFR [ndx] |= config << (4 * nr);                                     //  alternate function register
    
}


void Init_Pin_GPIO (uint16_t config, uint8_t nr, GPIO_TypeDef* GPIOx)           //  init pin <nr> port GPIOx according to <config>
{
    if (config == NO_CHANGE)
        return;
        
    Init_Speed_GPIO (config, nr,  GPIOx);                                       //  set speed of pin <nr>
    
//  set output register
//  ---------------------- zmiana 2019-03-10 -------------------------------
//  GPIOx->ODR &= ~(1 << nr);
//  GPIOx->ODR |= (config & 1) << nr;
        
    if (!(config & 1))
        GPIOx->ODR &= ~(1 << nr);
    else
        GPIOx->ODR |= (config & 1) << nr;
//  ------------------------------------------------------------------------
//  set output type - push pull or oper drain

    GPIOx->OTYPER &= ~(1 << nr);
    GPIOx->OTYPER |= ((config >> 1) & 1) << nr;    
    
    Init_PULLS_GPIO (config, nr, GPIOx);                                        //  set pull up / down    
    Init_MODE_GPIO (config, nr,  GPIOx);                                        //  set mode of pin <nr>
    Init_ALT_Fun (config, nr,  GPIOx);                                          //  set alternate signal
}


void Init_GPIOA (void)                                                          //  init port GPIOA
{    
const uint16_t port_A [16] = {  
    
//  pin 0                   pin 1                   pin 2                   pin 3              
//  LED1                    LED2                    CYF2                    SW3
//  --------------------------------------------------------------------------------------------
    OUT_PP_NP,              OUT_PP_NP,              OUT_PP_NP,              INPUT_DIG_PU,                          
                                                                                
//  pin 4                   pin 5                   pin 6                   pin 7
//  CYF1                    A                       F                       B
//  --------------------------------------------------------------------------------------------
    OUT_PP_NP,              OUT_PP_NP,              OUT_PP_NP,              OUT_PP_NP,                       

//  pin 8                   pin 9                   pin 10                  pin 11
//  ALARM                   NC                      NC                      NC
//  --------------------------------------------------------------------------------------------
    OUT_PP_NP,              NO_CHANGE,              NO_CHANGE,              NO_CHANGE,                          
    
//  pin 12                  pin 13                  pin 14                  pin 15
//  NC                      RX_JTMS A13_Pin         TX_JTCK A14_Pin         NC
//  --------------------------------------------------------------------------------------------
    NO_CHANGE,              NO_CHANGE,              NO_CHANGE,              NO_CHANGE, 
};        
            
//  GPIO Ports Clock Enable 
        
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    
//  init all pins
    
    for (int i = 0;  i < 16;   i++)
        Init_Pin_GPIO (port_A [i], i, GPIOA);        
}



void Init_GPIOB (void)                                                          //  init port GPIOB
{
const uint16_t port_B [16] = {  
    
//  pin 0                   pin 1                   pin 2                   pin 3              
//  E                       SW2                     SW1                     DOUT              
//  --------------------------------------------------------------------------------------------
    OUT_PP_NP,              INPUT_DIG_PU,           INPUT_DIG_PU,           INPUT_DIG_PU,                          
        
//  pin 4                   pin 5                   pin 6                   pin 7
//  PD_SCK                  NC                      KLUCZ                   NC
//  --------------------------------------------------------------------------------------------
    OUT_PP_NP,              NO_CHANGE,              OUT_PP_NP,              NO_CHANGE,                          

//  pin 8                   pin 9                   pin 10                  pin 11
//  NC                      NC                      D                       G                    
//  --------------------------------------------------------------------------------------------
    NO_CHANGE,              NO_CHANGE,              OUT_PP_NP,              OUT_PP_NP,
    
//  pin 12                  pin 13                  pin 14                  pin 15
//  C                       H                       RELAY 1                 RELAY 2                   
//  --------------------------------------------------------------------------------------------
    OUT_PP_NP,              OUT_PP_NP,              OUT_PP_NP,              OUT_PP_NP,
};        
            
//  GPIO Ports Clock Enable 
        
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
    
//  init all pins
    
    for (int i = 0;  i < 16;   i++)
        Init_Pin_GPIO (port_B [i], i, GPIOB);           
}


void Init_GPIOC (void)                                                          //  init port GPIOC
{            
//  GPIO Ports Clock Enable 
        
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

    //CYF3
    Init_Pin_GPIO (OUT_PP_NP, 13, GPIOC);   
    //CYF4
    Init_Pin_GPIO (OUT_PP_NP, 14, GPIOC);  
    //SW4
    Init_Pin_GPIO (INPUT_DIG_PU, 15, GPIOC);
}


void Init_GPIOH (void)                                                          //  init port GPIOC
{            
//  GPIO Ports Clock Enable 
        
    RCC->IOPENR |= RCC_IOPENR_GPIOHEN;

    //kalib
    Init_Pin_GPIO (INPUT_DIG_PU, 0, GPIOH);
    //rozdz
    Init_Pin_GPIO (INPUT_DIG_PU, 1, GPIOH);
}




