/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Main application (main module)
  \author       Abraham Tezmol Otero, M.S.E.E
  \project      Tau 
  \version      1.0
  \date         12/Jun/2016
   
  Program compiled with  WinIDEA Open Build 9.12.256 (54401), tested on Atmel SAMV71 Xplained Ultra
*/
/****************************************************************************************************/


/*~~~~~~  Headers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Main group of includes for board definitions, chip definitions and type definitions */
#include    "Std_Types.h"
/** Task scheduler definitions */
#include    "SchM.h"
/** LED control definitions */ 
#include    "Led_Ctrl.h"
/** Watchdog control function prototypes definitions */
#include    "Wdg.h"
/** Button Control interfaces */
#include    "Button_Ctrl.h"
/** Uart interfaces */
#include    "Uart.h"



/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
uint8_t 		u8SerialCtrl_TxData[] =
{ "UARTs are transmiting\n\r\n\r" };


/** UART pins (UTXD4 and URXD4) definitions, PD19,18. */
#define PINS_UART1 \
		{PIO_PA5C_URXD1 | PIO_PA6C_UTXD1, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
#define PINS_UART2 \
		{PIO_PD25C_URXD2 | PIO_PD26C_UTXD2, PIOD, ID_PIOD, PIO_PERIPH_C, PIO_DEFAULT}
#define PINS_UART3 \
		{PIO_PD28A_URXD3 | PIO_PD30A_UTXD3, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
const Pin pPins[] = { PINS_UART0, PINS_UART1, PINS_UART2, PINS_UART3, PINS_UART4 };
/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	/* Disable watchdog */
	Wdg_Disable();
	printf( "\n\r-- Scheduler Project %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s --\n\r", __DATE__, __TIME__ , COMPILER_NAME);
	/* Enable I and D cache */
	SCB_EnableICache();
	/* SCB_EnableDCache(); */
	/* Configure LEDs */
	printf( "-- Led Control --\n\r" ) ;
	LedCtrl_Configure();
  
    printf( "-- Button Control --\n\r" ) ;  
    ButtonCtrl_ConfigureSW0Button();
  
	/* Uart Inititalization */
	printf( "-- Uart Initialization --\n\r" ) ;

	PMC_EnablePeripheral(ID_UART0);
	PMC_EnablePeripheral(ID_UART1);
	PMC_EnablePeripheral(ID_UART2);
	PMC_EnablePeripheral(ID_UART3);
	PMC_EnablePeripheral(ID_UART4);
	
	PIO_Configure(pPins, PIO_LISTSIZE(pPins));
	Uart_Init(&UartConfig[0]);

	NVIC_ClearPendingIRQ(UART0_IRQn); //BASE_IRQ is UART4_IRQn
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_ClearPendingIRQ(UART1_IRQn); //BASE_IRQ is UART4_IRQn
	NVIC_SetPriority(UART1_IRQn, 1);
	NVIC_ClearPendingIRQ(UART2_IRQn); //BASE_IRQ is UART4_IRQn
	NVIC_SetPriority(UART2_IRQn, 1);
	NVIC_ClearPendingIRQ(UART3_IRQn); //BASE_IRQ is UART4_IRQn
	NVIC_SetPriority(UART3_IRQn, 1);
	NVIC_ClearPendingIRQ(UART4_IRQn); //BASE_IRQ is UART4_IRQn
	NVIC_SetPriority(UART4_IRQn, 1);

	Uart_SetTxEnable(UART_CFG_PHY_CHANNEL0, 1);
	Uart_SetTxEnable(UART_CFG_PHY_CHANNEL1, 1);
	Uart_SetTxEnable(UART_CFG_PHY_CHANNEL2, 1);
	Uart_SetTxEnable(UART_CFG_PHY_CHANNEL3, 1);  
	Uart_SetTxEnable(UART_CFG_PHY_CHANNEL4, 1);

	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART1_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART3_IRQn);
	NVIC_EnableIRQ(UART4_IRQn); 
	
	/* Scheduler Inititalization */
	printf( "-- Scheduler Initialization --\n\r" ) ;
	SchM_Init(ScheduleConfig);
	
	/* Should never reach this code */
	for(;;)
    {
		printf( "-- Unexpected Error at Scheduler Initialization --\n\r" ) ;
	}
}
