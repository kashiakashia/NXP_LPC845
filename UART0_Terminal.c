/*
===============================================================================
 Name        : UART0_Terminal.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "LPC8xx.h"
#include "syscon.h"
#include "swm.h"
#include "syscon.h"
#include "utilities.h"
#include "uart.h"
#include "chip_setup.h"
#include "peripherals_lib\src\serial.h"
#include "HAL_WS\NXP_USART.h"
#include "HAL_WS\NXP_Sys_Tik.h"

unsigned char rx_buffer_0 [RX_BUFFER_SIZE_0];                                   // bufor RX USART0
unsigned char rx_buffer_1 [RX_BUFFER_SIZE_1];                                   // bufor RX USART1
unsigned char rx_buffer_2 [RX_BUFFER_SIZE_2];                                   // bufor RX USART2
unsigned char rx_buffer_3 [RX_BUFFER_SIZE_3];                                   // bufor RX USART3


const unsigned char thestring[] = "What do you have to say for yourself now?\n\r";


void SysTick_Handler (void);                                                    //  interrupt 1 msec


void SysTick_Handler (void)                                                     //  interrupt 1 msec
{   
static int systick_cnt;                                                         //  systick counter

    if (systick_cnt < 1000 - 1)                                              
        systick_cnt++;
    else    
        systick_cnt = 0;
                                                                  
}



//  Function name:  UART0_IRQHandler
//  Description:    UART0 interrupt service routine.

void UART0_IRQHandler () 
{
    USART0_Handler ();
}


//  Function name:  UART0_IRQHandler
//  Description:    UART0 interrupt service routine.

void UART1_IRQHandler () 
{
    USART1_Handler ();
}


//  Function name:  UART0_IRQHandler
//  Description:    UART0 interrupt service routine.

void UART2_IRQHandler () 
{
    USART2_Handler ();
}


//  Function name:  UART0_IRQHandler
//  Description:    UART0 interrupt service routine.

void UART3_IRQHandler () 
{
    USART3_Handler ();
}



void System_Clock_Config (void)                                                 //  system clock init
{
//  Configure FRG0
    
    LPC_SYSCON->FRG0MULT = 0; 
    LPC_SYSCON->FRG0DIV = 255;

//  Select main_clk as the source for FRG0
    
    LPC_SYSCON->FRG0CLKSEL = FRGCLKSEL_MAIN_CLK;

}


//  Main routine

int main (void) 
{
    for (int i = 0;  i < 10000000;  i++);
        
    System_Clock_Config ();                                                     //  system clock init
    Sys_Tick_Config (SYSTEM_CLOCK / 1000);                                      //  ustaw systick na 1000 Hz

//    while (1);
    
    Config_USART (LPC_USART0, 9600, DBGTXPIN, DBGRXPIN);                        //  config USART0
    Config_USART (LPC_USART1, 19200, P0_0, P0_1);                               //  config USART1
    Config_USART (LPC_USART2, 38400, P0_10, P0_11);                               //  config USART2
    Config_USART (LPC_USART3, 115200, P0_12, P0_13);                              //  config USART3
  
//  Configure the debug uart (see Serial.c)
    
    setup_debug_uart ();

//    while (1);
    
//  main loop
    
    while(1)    {
		
        PutTerminalString (LPC_USART0, (uint8_t *)thestring);
        PutTerminalString (LPC_USART1, (uint8_t *)thestring);
        PutTerminalString (LPC_USART2, (uint8_t *)thestring);
        PutTerminalString (LPC_USART3, (uint8_t *)thestring);

        for (int n = 0;  n < 100000;  n++);
    
    //handshake = false;                                   // Clear handshake flag, will be set by ISR at end of user input
    //while (handshake == false);                          // Wait here for handshake from ISR

    //PutTerminalString(LPC_USART0, rx_buffer);            // Echo received string from the rx_buffer to the terminal if desired. Otherwise comment out.

  };

} // end of main

