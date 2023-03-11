/****************************************************************************************************/
/**
\file       Uart_Ctrl.c
\brief      MCU abstraction level - Uart control
\author     Francisco Martinez
\version    1.0
\date       25/Sep/2018
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include  "Uart_Ctrl.h"
#include "Uart_Cfg.h"
#include "Std_Types.h"
#include "Uart.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
uint8_t*    pu8SerialCtrl_RxDataPtr;
uint16_t 		BuffLength;
uint8_t*    ptrBuffer;

uint8_t 		Buffer[] =
{ "This is the UART4 at 115200 bps\n\r" };




/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

void UartCtrl_2ms( void )
{
  /* Example Code, need to be removed */
  /* Uart Logic Channel 0 */
//  Uart_Send(0);
}

void UartCtrl_50ms( void )
{
  /* Example Code, need to be removed */
  /* Uart Logic Channel 1 */
//  Uart_Send(1);
}

void UartCtrl_100ms( void )
{
	UartCtrl_TriggerEvent();
}

void UartCtrl_TriggerEvent( void )
{
	//Initializing/reseting buffer of UART4 for testing
	ptrBuffer = &Buffer[0];
	BuffLength = sizeof(Buffer);
	Uart_EnableInt(UART_CFG_PHY_CHANNEL4, UART_MASK_TXRDY, 1);

}


void vfnSerialCtrl_Transfer(void)
{
	if (BuffLength > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(UART_CFG_PHY_CHANNEL4, *ptrBuffer);

		/* point to next element */
		ptrBuffer++;
		/* update number of pending bytes to transfer */
		BuffLength--;
	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(UART_CFG_PHY_CHANNEL4, UART_MASK_TXRDY, 0);  
  }
}



/*******************************************************************************/
