#include "ADC.h"
#include "stm32l0xx_hal.h"

#include "..\TIME\time.h"

uint16_t    ADC_Init (void)                                                     //  init ADC module
{
uint32_t    status;
uint16_t    n;

    RCC->APB2ENR |= 1 << 9;                                                     //  enable clock to ADC module
    ADC1->CFGR2 = 1 << 30;                                                      //  bits 31, 30 == 01 -> synchronous clock mode / 2
    ADC1->CFGR1 = 3 << 15;                                                      //  discontinuous mode, auto-off mode
    ADC1->SMPR = 2;                                                             //  ADC sampling time = 7.5 ADC clocks
    ADC->CCR = 0x91 << 18;                                                      //  enable VREFINT (bit 22) and Low Freq Enable bit 25, resc/ / 2
    
    
//  ADC calibration 

    ADC1->CR = (uint32_t) ((1 << 28) | 1);                                      //  enable ADC voltage regulator, enable ADC
    ADC1->CR |= (uint32_t) (1 << 31);                                           //  start calibration
    
    n = 0;
    do   {                                                                      //  wait until calibration is complete
        status = ADC1->ISR;
        if (status & (1 << 11))
            break;
        
        wait_31us (100);
        n++;
    }   while (n < 10);
    
    return (n < 9);                                                             //  return success (1) or error (0)
}

void        ADC_Select_Channel (uint16_t  channel)                              //  select channel
{
    ADC1->CHSELR |= 1 << channel;
}


void        ADC_DeInit (void)                                                   //  disable ADC
{
    RCC->APB2RSTR = 1 << 9;
}


uint16_t    ADC_Measure_Channel (uint16_t  channel)                             //  measure channel
{
uint16_t result, status, n;

    ADC_Select_Channel (channel);

    ADC1->ISR = 0xFF;                                                           //  clear 
    ADC1->CR |= 5;                                                              //  start conversion

//  wait until conversion is ready
    
    n = 0;
    do   {                                                                   
        status = ADC1->ISR;
        if (status & 0x08)
            break;
        
        wait_31us (10);
        n++;
    }   while (n < 10);
    
    result = ADC1->DR;
    return (result);
}


uint16_t ADC_Calculate_Vdd (uint16_t adc_res)                                   //  convert <adc_res> to voltage [mV]
{
uint16_t *ref_ptr = (uint16_t*) 0x1FF80078;
uint16_t Vdd, Vref_cal;

    Vref_cal = *ref_ptr;
    Vdd = (3000 * Vref_cal) / adc_res;                                          //  Vref is calibrated for Vdd == 3V (3000 mV)

    return (Vdd);                                                               //  result unit is [mV]
}
