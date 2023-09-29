#include "NXP_NVIC.h"

//  IRQn            Interrupt number.
//  priority        Priority to set.

void NVIC_Set_Priority (IRQn_Type IRQn, uint32_t priority)                      //  Sets the priority of an interrupt.
{
uint16_t    nr      = IRQn >> 2;                                                //  IRQn / 4
uint16_t    shift   = IRQn & 3;                                                 //  IRQn % 4
uint32_t    mask    = ~(0xFF << shift);

    NVIC->IP [nr] &= mask;
    NVIC->IP [nr] |= (priority << 6) & 0xFF;    
}


//  priority        Priority to set.

void NVIC_Enable_IRQ (IRQn_Type IRQn)                                           //  Enables a device-specific interrupt in the NVIC interrupt controller.
{
    NVIC->ISER [0] = 1 << IRQn;
}

