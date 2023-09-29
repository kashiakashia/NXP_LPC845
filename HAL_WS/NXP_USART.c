//#include "const.h"
//#include "usart_const.h"
#include "NXP_usart.h"
#include "NXP_NVIC.h"

#include "LPC8xx.h"
#include "swm.h"


void USART0_Handler (void)              
{
static uint32_t rx_char_counter = 0;
unsigned char temp;
	
//  Append the current character to the rx_buffer

    temp = LPC_USART0->RXDAT;
    rx_buffer_0 [rx_char_counter] = temp;        
    
// Increment array index counter.

    rx_char_counter++;       
    
//  If the string overruns the buffer, start from the beginning
    
    if (rx_char_counter == RX_BUFFER_SIZE_0) 
        rx_char_counter = 0;
}


void USART1_Handler (void)              
{
static uint32_t rx_char_counter = 0;
unsigned char temp;
	
//  Append the current character to the rx_buffer

    temp = LPC_USART1->RXDAT;
    rx_buffer_1 [rx_char_counter] = temp;        
    
// Increment array index counter.

    rx_char_counter++;       
    
//  If the string overruns the buffer, start from the beginning
    
    if (rx_char_counter == RX_BUFFER_SIZE_1) 
        rx_char_counter = 0;
}


void USART2_Handler (void)              
{
static uint32_t rx_char_counter = 0;
unsigned char temp;
	
//  Append the current character to the rx_buffer

    temp = LPC_USART2->RXDAT;
    rx_buffer_2 [rx_char_counter] = temp;        
    
// Increment array index counter.

    rx_char_counter++;       
    
//  If the string overruns the buffer, start from the beginning
    
    if (rx_char_counter == RX_BUFFER_SIZE_0) 
        rx_char_counter = 0;
}


void USART3_Handler (void)              
{
static uint32_t rx_char_counter = 0;
unsigned char temp;
	
//  Append the current character to the rx_buffer

    temp = LPC_USART3->RXDAT;
    rx_buffer_3 [rx_char_counter] = temp;        
    
// Increment array index counter.

    rx_char_counter++;       
    
//  If the string overruns the buffer, start from the beginning
    
    if (rx_char_counter == RX_BUFFER_SIZE_1) 
        rx_char_counter = 0;
}





 // Configure UART0 for 9600 baud, 8 data bits, no parity, 1 stop bit.
  // For asynchronous mode (UART mode) the formula is:
  // (BRG + 1) * (1 + (m/256)) * (16 * baudrate Hz.) = FRG_in Hz.
  // We proceed in 2 steps.
  // Step 1: Let m = 0, and round (down) to the nearest integer value of BRG for the desired baudrate.
  // Step 2: Plug in the BRG from step 1, and find the nearest integer value of m, (for the FRG fractional part).
  //
  // Step 1 (with m = 0)
  // BRG = ((FRG_in Hz.) / (16 * baudrate Hz.)) - 1
  //     = (30,000,000/(16 * 9600)) - 1
  //     = 194.3
  //     = 194 (rounded)
  //
  // Step 2.
  // m = 256 * [-1 + {(FRG_in Hz.) / (16 * baudrate Hz.)(BRG + 1)}]
  //   = 256 * [-1 + {(30,000,000) / (16*9600)(195)}]
  //   = 0.002
  //   = 0 (rounded)

void Config_USART (LPC_USART_TypeDef* usart, int baud, int pin_tx,  int pin_rx)     //  data 8 bits, no parity, 1 stop bit
{
uint32_t Ux_TXD, Ux_RXD, us_type = 0;

    LPC_SYSCON->SYSAHBCLKCTRL0 |= SWM;

//  configure USART pins

    if (usart == LPC_USART0)   {
        Ux_TXD = U0_TXD;
        Ux_RXD = U0_RXD;
        
        LPC_SYSCON->UART0CLKSEL = FCLKSEL_FRG0CLK;                              // Select frg0clk as the source for fclk0 (to UART0)
        	
    //  Give USART0 a reset, enable clock
        
        LPC_SYSCON->PRESETCTRL0 &= (UART0_RST_N);                               //  reset enable
        LPC_SYSCON->PRESETCTRL0 |= ~(UART0_RST_N);                              //  reset disable
        LPC_SYSCON->SYSAHBCLKCTRL0 |= UART0;                                    //  Enable clocks to relevant peripherals

    //  Enable the USART0 Interrupt
        
        NVIC_EnableIRQ (UART0_IRQn);
            
        us_type = 1;
    }

    if (usart == LPC_USART1)   {
        Ux_TXD = U1_TXD;
        Ux_RXD = U1_RXD;
        
        LPC_SYSCON->UART1CLKSEL = FCLKSEL_FRG0CLK;                              // Select frg0clk as the source for fclk0 (to UART0)
        	
    //  Give USART0 a reset, enable clock
        
        LPC_SYSCON->PRESETCTRL0 &= (UART1_RST_N);                               //  reset enable
        LPC_SYSCON->PRESETCTRL0 |= ~(UART1_RST_N);                              //  reset disable
        LPC_SYSCON->SYSAHBCLKCTRL0 |= UART1;                                    //  Enable clocks to relevant peripherals
        
    //  Enable the USART0 Interrupt
        
        NVIC_EnableIRQ (UART1_IRQn);
            
        us_type = 1;
    }

    if (usart == LPC_USART2)   {
        Ux_TXD = U2_TXD;
        Ux_RXD = U2_RXD;
        
        LPC_SYSCON->UART2CLKSEL = FCLKSEL_FRG0CLK;                              // Select frg0clk as the source for fclk0 (to UART0)
        	
    //  Give USART0 a reset, enable clock
        
        LPC_SYSCON->PRESETCTRL0 &= (UART2_RST_N);                               //  reset enable
        LPC_SYSCON->PRESETCTRL0 |= ~(UART2_RST_N);                              //  reset disable
        LPC_SYSCON->SYSAHBCLKCTRL0 |= UART2;                                    //  Enable clocks to relevant peripherals
        
    //  Enable the USART0 Interrupt
        
        NVIC_EnableIRQ (UART2_IRQn);
            
        us_type = 1;
    }

    if (usart == LPC_USART3)   {
        Ux_TXD = U3_TXD;
        Ux_RXD = U3_RXD;
        
        LPC_SYSCON->UART3CLKSEL = FCLKSEL_FRG0CLK;                              // Select frg0clk as the source for fclk0 (to UART0)
        	
    //  Give USART0 a reset, enable clock
        
        LPC_SYSCON->PRESETCTRL0 &= (UART3_RST_N);                               //  reset enable
        LPC_SYSCON->PRESETCTRL0 |= ~(UART3_RST_N);                              //  reset disable
        LPC_SYSCON->SYSAHBCLKCTRL0 |= UART3;                                    //  Enable clocks to relevant peripherals
        
    //  Enable the USART0 Interrupt
        
        NVIC_EnableIRQ (UART3_IRQn);
            
        us_type = 1;
    }

//  if usart type OK, connect usart TXD, RXD signals to port pins
    
    if (us_type)    {
        ConfigSWM (Ux_TXD, pin_tx);
        ConfigSWM (Ux_RXD, pin_rx);
    }    
  
    
/*  +-------------------------------------------------------+
    !   BRG = ((FRG_in Hz.) / (16 * baudrate Hz.)) - 1      !
    !       = (30,000,000/(16 * 9600)) - 1                  !
    !       = 194.3                                         !
    +-------------------------------------------------------+    */
    
    usart->BRG = SYSTEM_CLOCK / (16 * baud);                                        // Configure the USART0 baud rate generator

//  Configure the USART0 CFG register:
//  8 data bits, no parity, one stop bit, no flow control, asynchronous mode
    
    usart->CFG = DATA_LENG_8 | PARITY_NONE | STOP_BIT_1;

//  Configure the USART0 CTL register (nothing to be done here)
//  No continuous break, no address detect, no Tx disable, no CC, no CLRCC
    
    usart->CTL = 0;

//  clear pending flags and enable usart
    
    usart->STAT = 0xFFFF;                                                       //  Clear any pending flags, just in case
    usart->CFG |= UART_EN;                                                      //  Enable USART0
    usart->INTENSET = RXRDY;                                                    //  enable RX interrupt
  
}

