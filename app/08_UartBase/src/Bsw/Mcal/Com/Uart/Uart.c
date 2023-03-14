/*******************************************************************************/
/**
\file       
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

/** Scheduler function prototypes definitions */
#include "Uart.h"
#include "MemAlloc.h"



/*****************************************************************************************************
* Defines - 
*****************************************************************************************************/

#define UART_CHANNEL_UNDEF (255)

#define UART_CH0  (0) 
#define UART_CH1  (1)
#define UART_CH2  (2)
#define UART_CH3  (3)
#define UART_CH4  (4)

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Uart Status Structure Example */
UartStatusType *UartStatus;
UartConfigType *UartConfInit;
  

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Array of Uart Register Base Address */
static const Uart * UartRegAddr[]={ UART0, UART1, UART2, UART3, UART4 };

/*****************************************************************************************************
* Code of module wide Public FUNCTIONS
*****************************************************************************************************/
uint8_t Uart_GetLogChannel(uint8_t PhyChannel)
{
    uint8_t LogicalChannel = UART_CHANNEL_UNDEF;
    uint8_t LocChIdx = 0; /* LocChIdx represent the logical channel */
    /* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
    do
    {
        if (UartCh[LocChIdx].ChannelId == PhyChannel)
        {
            LogicalChannel = LocChIdx;
        }
        else{
          /*Nothing to do*/
        }
        LocChIdx++;
    } while ((LocChIdx < UART_CFG_CHANNELS));
      //while((UartCh[LocChIdx - 1].ChannelId != PhyChannel) && (LocChIdx < UART_CFG_CHANNELS));
    return (LogicalChannel);
}

/* Interface:  Initialization */
void Uart_Init(const UartConfigType* ChannelConfigure )
{ 
    Uart * LocUartReg;
    uint8_t LocChIdx = 0;  
    /* Memory allocation for all Channel Status example */
    UartStatus = (UartStatusType*) MemAlloc( sizeof(UartStatusType) * UART_CFG_CHANNELS  );  
  
    for (LocChIdx = 0; LocChIdx < UART_CFG_CHANNELS; LocChIdx++)
    {
        /* Point to register address based of physical channel */
        LocUartReg = UartRegAddr[ChannelConfigure->UartCh[LocChIdx].ChannelId];
        /* Access to register for the configured channel with LocUartReg */
        /*Resets Receiver/Transmitter */
        LocUartReg->UART_CR = 
            UART_CR_RSTRX 
            | UART_CR_RSTTX
            | UART_CR_RXDIS 
            | UART_CR_TXDIS 
            | UART_CR_RSTSTA;
        /* Disable all interrupts (1 disables)*/
        LocUartReg->UART_IDR = 0xFFFFFFFF;
        /*Configure channel mode*/
        LocUartReg->UART_MR |= (ChannelConfigure->UartCh[LocChIdx].Mode << 14);
        /*Configure channel parity*/
        LocUartReg->UART_MR |= (UartConfig->UartCh[LocChIdx].Parity << 9);
        /* Configure baudrate */
        if (ChannelConfigure->ClkSrc == UART_CFG_PMC_CLK)
        {
            LocUartReg->UART_MR |= (UART_CFG_PMC_CLK << 12);
        }
        else if (ChannelConfigure->ClkSrc == UART_CFG_PER_CLK)
        {
            LocUartReg->UART_MR |= (UART_CFG_PER_CLK << 12);
        }
        LocUartReg->UART_BRGR = (BOARD_MCK / ChannelConfigure->UartCh[LocChIdx].Baudrate) / 16;

        /* Access to channel status structure with LocChIdx */
        UartStatus[LocChIdx].ChannelId = ChannelConfigure->UartCh[LocChIdx].ChannelId;
    }
}

/*
*	Sets the requested baudrate to the addressed UART channel
*	Param (in)
*		Channel		-	UART Channel to be addressed
*		Baudrate	-	Baudrate to configur
*	Return value Std_ReturnType
*		E_OK:	Command successfully executed
*		E_NOK:	Command could not be executed
*/
Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate) {
    /* The Uart_SetBaudrate function shall support runtime re-configuration of the Uart channel to the specified
    *  baudrate parameter.*/
    Uart* LocUartReg = UartRegAddr[Channel];
    LocUartReg->UART_BRGR = (BOARD_MCK / Baudrate) / 16;
    if (UartRegAddr[Channel]->UART_BRGR != (BOARD_MCK / Baudrate) / 16) {
        return  E_NOT_OK;
    }
    return E_OK;
}

/*
*	Enables or disables the transmitter of the UART module
*	Param (in)
*		Channel		|	 UART Channel to be addressed
*		____________|________________________________
*		Enable		|	Enable/Disable information
*					|	0: Disable
*					|	1: Enable
*/
void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable) {
    /* The Uart_SetTxEnable function shall support runtime enable/disable of the Uart transmitter specified by
    *  the Enable parameter*/
    Uart* LocUartReg = UartRegAddr[Channel];
    if (Enable) {
        //The transmitter is enabled by writing UART_CR with the bit TXEN at 1. 
        LocUartReg->UART_CR = UART_CR_TXEN;
    }
    else {
        //Disable the transmitter by writing UART_CR with the bit TXDIS at 1
        LocUartReg->UART_CR = UART_CR_TXDIS;
    }
}

/*	Enables or disables the receiver of the UART module*/
void Uart_SeRxEnable(uint8_t Channel, uint32_t Enable) {
    /*	The Uart_SetRxEnable function shall support runtime enable/disable of the Uart receiver specified by the Enable
        parameter.*/
    Uart* LocUartReg = UartRegAddr[Channel];
    if (Enable) {
        LocUartReg->UART_CR = UART_CR_RXEN;
    }
    else {
        LocUartReg->UART_CR = UART_CR_RXDIS;
    }
}

/*Sends one packet of data through the specified UART module*/
Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte)
{
    Uart* LocUartReg = UartRegAddr[Channel];
    if (LocUartReg->UART_SR & UART_SR_TXRDY)
    {
        /* Send character*/
        LocUartReg->UART_THR = Byte;
        return E_OK;
    }
    return E_NOT_OK;
}

void Uart_SendByteInt(uint8_t Channel, uint8_t Byte)
{
    Uart* LocUartReg = UartRegAddr[Channel];
    LocUartReg->UART_THR = Byte;       
}

/*  Sends a packet of data through the specified UART channel
*   This is a blocking function*/
Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t* Buffer, uint16_t Length) {
    uint8_t* pData = Buffer;
    uint32_t Len = 0;
    Uart* LocUartReg = UartRegAddr[Channel];
    /* Is the  transmitter to be ready*/
    if (LocUartReg->UART_SR & UART_SR_TXRDY) {
        for (Len = 0; Len < Length; Len++)
        {
            /* Send character*/
            LocUartReg->UART_THR = *pData;
            pData++;
            //wait for data to transmit
            while (!(LocUartReg->UART_SR & UART_SR_TXRDY));
        }
        return  E_OK;
    }
    return E_NOT_OK;
}

/*
*   Reads and returns a character from the UART module
*   Param (in) 
*       Channel     UART Channel to be addressed
*   Return value
*       uint8_t     Data received from the UART bus
*/
uint8_t Uart_GetByte(uint8_t Channel) {

}

/*  Reads and returns the current status of the addressed UART module*/
uint32_t Uart_GetStatus(uint8_t Channel) {
    Uart* LocUartReg = UartRegAddr[Channel];
    return LocUartReg->UART_SR;
}


/*****************************************************************************************************
* Code of module wide Interrupt Handler FUNCTIONS
*****************************************************************************************************/

/*
*   Enable/disable the UART module interrupts 
*   Param (in) 
*       Channel        UART Channel to be addressed
*       IntMode        Interrupt Mode information
*       Enable         Enable/Disable information
*                           0: Disable
*                           1: Enable
*/
void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable) {
    Uart* LocUartReg = UartRegAddr[Channel];
    if (Enable){
        LocUartReg->UART_IER = IntMode;//2
        //UART_CallbackRegister(vfnSerialCtrl_Transfer);
        /* Clear pending IRQs and Set priority of IRQs */
    }else   {
        LocUartReg->UART_IDR = IntMode;
    }
}



void Uart_Isr( uint8_t Channel )
{
    Uart * LocUartReg = UartRegAddr[Channel];
    uint8_t LocUartLogicChannel = Uart_GetLogChannel(Channel);

    if(LocUartReg->UART_SR & UART_SR_TXRDY)
    {
        (*UartCh[LocUartLogicChannel].TxNotification)();
    }
    //More comparations can be included to check for other kinds of interruptions.
} 


void UART0_Handler(void)
{
	Uart_Isr(UART_CH0);
}


void UART1_Handler(void)
{
	Uart_Isr(UART_CH1);
}

void UART2_Handler(void)
{
	Uart_Isr(UART_CH2);
}

void UART3_Handler(void)
{
	Uart_Isr(UART_CH3);
}


void UART4_Handler(void)
{ 
	Uart_Isr(UART_CH4);
}