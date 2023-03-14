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

uint16_t 		BuffLength0;
uint16_t 		BuffLength1;
uint16_t 		BuffLength2;
uint16_t 		BuffLength3;
uint16_t 		BuffLength4;
uint8_t*    ptrBuffer0;
uint8_t*    ptrBuffer1;
uint8_t*    ptrBuffer2;
uint8_t*    ptrBuffer3;
uint8_t*    ptrBuffer4;

uint8_t 		Buffer0[] =
{ "This is the UART0 at 9600 bps\n\r" };
uint8_t 		Buffer1[] =
{ "This is the UART1 at 14400 bps\n\r" };
uint8_t 		Buffer2[] =
{ "This is the UART2 at 38400 bps\n\r" };
uint8_t 		Buffer3[] =
{ "This is the UART3 at 57600 bps\n\r" };
uint8_t 		Buffer4[] =
{ "This is the UART4 at 115200 bps\n\r" };





/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

void UartCtrl_2ms( void )
{

}

void UartCtrl_50ms( void )
{

}

void UartCtrl_100ms( void )
{
  /*Call to Uart Trigger*/
	UartCtrl_TriggerEvent();
}

void UartCtrl_TriggerEvent( void )
{
  //Initializing/reseting buffer of UART0 for testing
	ptrBuffer0 = &Buffer0[0];
	BuffLength0 = sizeof(Buffer0);
	Uart_EnableInt(UART_CFG_PHY_CHANNEL0, UART_MASK_TXRDY, 1);
  
  //Initializing/reseting buffer of UART1 for testing
	ptrBuffer1 = &Buffer1[0];
	BuffLength1 = sizeof(Buffer1);
	Uart_EnableInt(UART_CFG_PHY_CHANNEL1, UART_MASK_TXRDY, 1);
  
  //Initializing/reseting buffer of UART2 for testing
	ptrBuffer2 = &Buffer2[0];
	BuffLength2 = sizeof(Buffer2);
	Uart_EnableInt(UART_CFG_PHY_CHANNEL2, UART_MASK_TXRDY, 1);
  
  //Initializing/reseting buffer of UART3 for testing
	ptrBuffer3 = &Buffer3[0];
	BuffLength3 = sizeof(Buffer3);
	Uart_EnableInt(UART_CFG_PHY_CHANNEL3, UART_MASK_TXRDY, 1);
  
	//Initializing/reseting buffer of UART4 for testing
	ptrBuffer4 = &Buffer4[0];
	BuffLength4 = sizeof(Buffer4);
	Uart_EnableInt(UART_CFG_PHY_CHANNEL4, UART_MASK_TXRDY, 1);

}


void vfnSerialCtrl_Transfer0(void)
{
	if (BuffLength0 > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(UART_CFG_PHY_CHANNEL0, *ptrBuffer0);
		/* point to next element */
		ptrBuffer0++;
		/* update number of pending bytes to transfer */
		BuffLength0--;
	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(UART_CFG_PHY_CHANNEL0, UART_MASK_TXRDY, 0);
	}
}

void vfnSerialCtrl_Transfer1(void)
{
	if (BuffLength1 > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(UART_CFG_PHY_CHANNEL1, *ptrBuffer1);
		/* point to next element */
		ptrBuffer1++;
		/* update number of pending bytes to transfer */
		BuffLength1--;
	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(UART_CFG_PHY_CHANNEL1, UART_MASK_TXRDY, 0);
	}
}

void vfnSerialCtrl_Transfer2(void)
{
	if (BuffLength2 > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(UART_CFG_PHY_CHANNEL2, *ptrBuffer2);
		/* point to next element */
		ptrBuffer2++;
		/* update number of pending bytes to transfer */
		BuffLength2--;
	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(UART_CFG_PHY_CHANNEL2, UART_MASK_TXRDY, 0);
	}
}

void vfnSerialCtrl_Transfer3(void)
{
	if (BuffLength3 > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(UART_CFG_PHY_CHANNEL3, *ptrBuffer3);
		/* point to next element */
		ptrBuffer3++;
		/* update number of pending bytes to transfer */
		BuffLength3--;
	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(UART_CFG_PHY_CHANNEL3, UART_MASK_TXRDY, 0);
	}
}

void vfnSerialCtrl_Transfer4(void)
{
	if (BuffLength4 > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(UART_CFG_PHY_CHANNEL4, *ptrBuffer4);

		/* point to next element */
		ptrBuffer4++;
		/* update number of pending bytes to transfer */
		BuffLength4--;

	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(UART_CFG_PHY_CHANNEL4, UART_MASK_TXRDY, 0);  
  }
}



/*******************************************************************************/
