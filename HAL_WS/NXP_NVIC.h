#include "LPC8xx.h"


void NVIC_Set_Priority (IRQn_Type IRQn, uint32_t priority);                     //  Sets the priority of an interrupt.
void NVIC_Enable_IRQ (IRQn_Type IRQn);                                          //  Enables a device-specific interrupt in the NVIC interrupt controller.

