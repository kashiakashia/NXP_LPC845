#include "AppConf.h"


uint16_t    ADC_Init (void);                                                    //  init ADC module
void        ADC_Select_Channel (uint16_t  channel);                             //  select channel
uint16_t    ADC_Measure_Channel (uint16_t  channel);                            //  measure channel
uint16_t    ADC_Calculate_Vdd (uint16_t adc_res);                               //  convert <adc_res> to voltage [mV]
void        ADC_DeInit (void);                                                  //  disable ADC
