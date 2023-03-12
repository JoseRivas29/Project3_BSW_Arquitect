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


#define UART_CTRL_MAX_CONFIG_CHANNELS	5

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
uint8_t*    pu8SerialCtrl_RxDataPtr;
uint16_t 		BuffLength;
uint16_t 		BuffLength0;
uint16_t 		BuffLength1;
uint16_t 		BuffLength2;
uint16_t 		BuffLength3;
uint16_t 		BuffLength4;
uint8_t*    ptrBuffer;
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

Uart_Ctrl_parameters_type Uart_Ctrl_parameters[UART_CTRL_MAX_CONFIG_CHANNELS] = 
{
	{UART_CFG_PHY_CHANNEL0, &Buffer0[0], sizeof(Buffer0)},
	{UART_CFG_PHY_CHANNEL1, &Buffer1[0], sizeof(Buffer1)},
	{UART_CFG_PHY_CHANNEL2, &Buffer2[0], sizeof(Buffer2)},
	{UART_CFG_PHY_CHANNEL3, &Buffer3[0], sizeof(Buffer3)},
	{UART_CFG_PHY_CHANNEL4, &Buffer4[0], sizeof(Buffer4)}
};



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
	UartCtrl_TriggerEvent( &Uart_Ctrl_parameters[0]);
}

void UartCtrl_TriggerEvent( Uart_Ctrl_parameters_type * Uart_Ctrl_param_ptr )
{
	uint8_t channel_idx = 0;

	for(channel_idx = 0 ; channel_idx < UART_CTRL_MAX_CONFIG_CHANNELS ; channel_idx++ ){
		Uart_Ctrl_param_ptr[channel_idx].Buffer_len = sizeof(Uart_Ctrl_param_ptr[channel_idx].ptr2Buffer);
		Uart_EnableInt(Uart_Ctrl_param_ptr[channel_idx].channel, UART_MASK_TXRDY, 1);
	}
}

void vfnSerialCtrl_Transfer(Uart_Ctrl_parameters_type * Uart_Ctrl_ref_ptr)
{
	Uart_Ctrl_parameters_type local_parameters;

	local_parameters.channel = Uart_Ctrl_ref_ptr->channel;
	local_parameters.ptr2Buffer = (uint8_t *)Uart_Ctrl_ref_ptr->ptr2Buffer;
	local_parameters.Buffer_len = Uart_Ctrl_ref_ptr->Buffer_len;

	if (local_parameters.Buffer_len > 0)
	{
		/* Send out one byte at a time */
		Uart_SendByteInt(local_parameters.channel, *local_parameters.ptr2Buffer);
		/* point to next element */
		local_parameters.ptr2Buffer++;
		/* update number of pending bytes to transfer */
		local_parameters.Buffer_len--;
	}
	else
	{
		//Disable the interruption once that done
		Uart_EnableInt(local_parameters.channel, UART_MASK_TXRDY, 0);
	}
}

Uart_Ctrl_parameters_type *vfnSerialCtrl_GetChannel_Parameters_Ptr(uint8_t channel)
{
	return &Uart_Ctrl_parameters[channel];
};


void vfnSerialCtrl_Transfer0(void)
{
	vfnSerialCtrl_Transfer((Uart_Ctrl_parameters_type *) vfnSerialCtrl_GetChannel_Parameters_Ptr(UART_CFG_PHY_CHANNEL0));
}

void vfnSerialCtrl_Transfer1(void)
{
	vfnSerialCtrl_Transfer((Uart_Ctrl_parameters_type *) vfnSerialCtrl_GetChannel_Parameters_Ptr(UART_CFG_PHY_CHANNEL1));
}

void vfnSerialCtrl_Transfer2(void)
{
	vfnSerialCtrl_Transfer((Uart_Ctrl_parameters_type *) vfnSerialCtrl_GetChannel_Parameters_Ptr(UART_CFG_PHY_CHANNEL2));
}

void vfnSerialCtrl_Transfer3(void)
{
	vfnSerialCtrl_Transfer((Uart_Ctrl_parameters_type *) vfnSerialCtrl_GetChannel_Parameters_Ptr(UART_CFG_PHY_CHANNEL3));
}

void vfnSerialCtrl_Transfer4(void)
{
	vfnSerialCtrl_Transfer((Uart_Ctrl_parameters_type *) vfnSerialCtrl_GetChannel_Parameters_Ptr(UART_CFG_PHY_CHANNEL4));
}



/*******************************************************************************/
