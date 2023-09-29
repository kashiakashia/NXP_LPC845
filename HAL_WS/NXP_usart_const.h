//#include "stm32f0xx_hal.h"
#include <stdint.h>


#ifndef USART_CONST_
    #define USART_CONST_

    /*******************************************************************************
        Transmit and receive buffer size
    *******************************************************************************/

    #define     Rx_BUF_SIZE                             100
    #define     Tx_BUF_SIZE                             100

    #define     GET_RxD_ADDR                            0                       //  return pointer to Wisol RxD buffer
    #define     CLEAR_RxD_BUF                           1                       //  clear Wisol RxD buffer
    #define     STORE_RxD_CHAR                          2                       //  store char into Wisol RxD buffer

    #define     GET_TxD_ADDR                            0                       //  return pointer to Wisol RxD buffer
    #define     CLEAR_TxD_BUF                           1                       //  clear Wisol RxD buffer
    #define     STORE_TxD_CHAR                          2                       //  store char into Wisol RxD buffer

    #define     RX_LOCK                                 0xA5                    //  if 1'st chr in buffer == RX_LOCK, no write operations are enabled
#endif


