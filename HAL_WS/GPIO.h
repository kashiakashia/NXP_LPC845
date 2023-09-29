#include "GPIO_const.h"


void Init_GPIOA (void);                                                         //  init port GPIOA
void Init_GPIOB (void);                                                         //  init port GPIOB
void Init_GPIOC (void);                                                         //  init port GPIOB
void Init_GPIOH (void); 

void Init_PULLS_GPIO (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx);        //  init pulls up / down for pin <nr> port GPIOx according to config
void Init_MODE_GPIO (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx);         //  set mode of pin <nr>
void Init_Speed_GPIO (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx);        //  set speed of pin <nr>
void Init_ALT_Fun (uint32_t config, uint8_t nr, GPIO_TypeDef* GPIOx);           //  init alternate function

void Init_Pin_GPIO (uint16_t config, uint8_t nr, GPIO_TypeDef* GPIOx);          //  init pin <nr> port GPIOx according to <config>

void GPIO_ResetBits  (GPIO_TypeDef* GPIOx, uint16_t nr);                        //  clear GPIO bit
void GPIO_SetBits  (GPIO_TypeDef* GPIOx, uint16_t nr);                          //  set GPIO bit
uint16_t  GPIO_ReadBit (GPIO_TypeDef* GPIOx, uint16_t nr);                      //  read GPIO bit


