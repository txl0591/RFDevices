/*********************************************************
  Copyright (C), 2013-2016
  File name:	Uart.h
  Author:   	
  Version:   	1.0
  Date: 		13.11.23
  Description:  
  History:                   
    1. Date:
       Author:
       Modification:
    2. ...
*********************************************************/
#ifndef _UART_H_
#define _UART_H_

#define S1_S0 						0x40              //P_SW1.6
#define S1_S1 						0x80              //P_SW1.7

#define UART_SEND_BUF       5
#define UART_RECV_BUF       5
#define UART_DATA_MAX       32

#define UART_STATE_NONE     0
#define UART_STATE_RECV     1
#define UART_STATE_SEND     2

typedef struct 
{
	INT8U State;
	INT16U Len;
	INT8U Buf[UART_DATA_MAX+1];
}UART_FRAME,*PUART_FRAME;

/*************************************************
  Function:		UartProc
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartProc(void);
/*************************************************
  Function:		UartReadBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT16U UartReadBuf(INT8U * Buf);

/*************************************************
  Function:		UartSendByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartSendByte(unsigned char SendData);

/*************************************************
  Function:		UartSend
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartSend(INT8U Com, unsigned char* Data, unsigned char Len);

/*************************************************
  Function:		UartTimer
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartTimer(void);

/*************************************************
  Function:		UartInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartInit(void);


#endif
