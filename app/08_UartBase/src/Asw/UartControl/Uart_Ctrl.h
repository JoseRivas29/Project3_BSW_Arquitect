/****************************************************************************************************/
/**
\file       Uart_Ctrl.h
\brief      MCU abstraction level - Uart control
\author     Francisco Martinez
\version    1.0
\date       25/Sep/2018
*/
/****************************************************************************************************/

#ifndef __UART_CTRL_H        /*prevent duplicated includes*/
#define __UART_CTRL_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Standard Types */
#include "Std_Types.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

typedef struct Uart_Ctrl_parameters_t
{
    uint8_t channel;
    uint8_t* ptr2Buffer;
    uint16_t Buffer_len;
}Uart_Ctrl_parameters_type;

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Uart Control Exported Functions */
extern void UartCtrl_2ms( void );
extern void UartCtrl_50ms( void );
extern void UartCtrl_100ms( void );
extern void UartCtrl_TriggerEvent( Uart_Ctrl_parameters_type * Uart_Ctrl_param_ptr );
extern void vfnSerialCtrl_Transfer( Uart_Ctrl_parameters_type * Uart_Ctrl_ref_ptr );
extern Uart_Ctrl_parameters_type  *vfnSerialCtrl_GetChannel_Parameters_Ptr(uint8_t channel);
extern void vfnSerialCtrl_Transfer0();
extern void vfnSerialCtrl_Transfer1();
extern void vfnSerialCtrl_Transfer2();
extern void vfnSerialCtrl_Transfer3();
extern void vfnSerialCtrl_Transfer4();


/**************************************************************************************************/

#endif /* __UART_CTRL_H */