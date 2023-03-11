/*******************************************************************************/
/**
\file       Uart_Cfg.c
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

#include "Uart.h"
#include "Uart_Ctrl.h"   /* Callback functions */




//This container contains the configuration parameters of the Uart channel
UartChannelType const UartCh[] = {
	{UART_CFG_CHANNEL4, UART_CFG_INT_TXRDY, UART_CFG_MODE_NORMAL, UART_CFG_PARITY_NO, 115200, vfnSerialCtrl_Transfer, NULL, NULL},
	
};

// Configuration of the UART (Uart driver) module
UartConfigType UartConfig[] = {
	{
		sizeof(UartCh) / sizeof(UartChannelType),
		(uint8_t)UART_CFG_PER_CLK,
		&UartCh[0]
	}
}; 

