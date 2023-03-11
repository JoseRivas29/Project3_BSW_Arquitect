/*******************************************************************************/
/**
\file       Uart_Cfg.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/
#ifndef _UART_CFG_H
#define _UART_CFG_H

	#include "Std_Types.h"
	#include "Uart_Types.h"

	#define UART_CFG_CHANNELS (1)

	#define UART_CFG_CHANNEL0  (0)
	#define UART_CFG_CHANNEL1  (1)
	#define UART_CFG_CHANNEL2  (2)
	#define UART_CFG_CHANNEL3  (3)
	#define UART_CFG_CHANNEL4  (4)

	/*UART CHANNEL CONFIGURATION DEFINITIONS*/
	#define UART_CFG_PHY_CHANNEL0 (0)
	#define UART_CFG_PHY_CHANNEL1 (1)
	#define UART_CFG_PHY_CHANNEL2 (2)
	#define UART_CFG_PHY_CHANNEL3 (3)
	#define UART_CFG_PHY_CHANNEL4 (4)

	/*INTERRUPT CONFIGURATION DEFINITIONS*/
	#define UART_CFG_INT_DISABLED		(0)
	#define UART_CFG_INT_RXRDY			(1)
	#define UART_CFG_INT_TXRDY			(2)
	#define UART_CFG_INT_OVR_ERROR		(32)
	#define UART_CFG_INT_FRAME_ERROR	(64)
	#define UART_CFG_INT_PAR_ERROR		(128)
	#define UART_CFG_INT_TXEMPTY		(512)

	/*MODE CONFIGURATION DEFINES*/
	#define UART_CFG_MODE_NORMAL	(0)
	#define UART_CFG_MODE_AUTO		(1)
	#define UART_CFG_MODE_LOOPBACK	(2)

	/*PARITY CONFIGURATION DEFINES*/
	#define UART_CFG_PARITY_EVEN	(0)
	#define UART_CFG_PARITY_ODD		(1)
	#define UART_CFG_PARITY_SPACE	(2)
	#define UART_CFG_PARITY_MARK	(3)
	#define UART_CFG_PARITY_NO		(4)

	/*CLOCK CONFIGURATION DEFINES*/
	#define UART_CFG_PER_CLK		(0)
	#define	UART_CFG_PMC_CLK		(1)

	typedef struct {
		uint8_t				ChannelId;				// Physical Uart Channel Identifier
		uint8_t				IsrEn;					// Uart Interrupts enable(Transmission, Reception and Error)
		uint8_t				Mode;					// Uart Channel Mode: 0:Normal / 1:Loopback
		uint8_t				Parity;					// Parity Type= 0: Even / 1 : Odd
		uint32_t			Baudrate;				// Specifies the baud rate of the Uart channel in bits per second
		UartNotification	TxNotification;			// End of transmission notification
		UartNotification	RxNotification;			// Data reception notification
		UartErrorNotification ErrorNotification;	// Error notification	
	}UartChannelType;

/*Configuration of the UART (Uart driver) module*/
	typedef struct {
		uint8_t			UartNumberOfChannels;		//Number of channels to be configured
		uint8_t			ClkSrc;						//Clock Source:	0: Peripheral Clock	/ 1 : Programmable Clock
		UartChannelType	*UartCh;				//Configuration of the UART (Uart driver) module
	}UartConfigType;


	extern const UartChannelType UartCh[];
	extern UartConfigType UartConfig[];


#endif /* _UART_CFG_H */