/*******************************************************************************/
/**
\file       Uart_Types.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

#ifndef UART_TYPES
#define UART_TYPES

  /** Standard Types */
  #include "Std_Types.h"
  
  /* UartStatusType example */
  typedef struct
  {
    uint8_t ChannelId;

  }UartStatusType;
  
  /*These errors provide the occurred error to upper layers through callback notifications*/
  typedef enum {
      UART_ERROR_OVERRUN,
      UART_ERROR_FRAMING,
      UART_ERROR_PARITY
  }UartErrorType;

  /*Function pointer for Uart TXand RX notifications to be used as part of the configuration containers*/
  typedef void(*UartNotification)(void);
  /*Function pointer for Uart error notifications to be used as part of the configuration containers*/
  typedef void(*UartErrorNotification)(UartErrorType Error);

/*============================================================================*/
#endif /* UART_TYPES */
