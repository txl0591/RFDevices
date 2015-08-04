/*********************************************************
  Copyright (C), 2013-2016
  File name:	Uart.c
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
#include "Include.h"

#define RECV_DEBUG     0  

#define S2RI            0x01
#define S2TI            0x02
#define RECV_TIMEOUT    3

static INT8U mUartRecvState = 0;
static INT8U mUartSendState = 0;
UART_FRAME mUartRecvBuf[UART_RECV_BUF];
UART_FRAME mUartSendBuf[UART_SEND_BUF];
static INT8U mUartRecvIndex = 0;
static INT8S mUartSendIndex = -1;
static INT8U mUartSwitchTime = 0;
static INT16U mUartSendCount = 0;

/*************************************************
  Function:		SendByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void SendByte(unsigned char SendData)
{
  	TI = 0;
  	SBUF = SendData;
}

/*************************************************
  Function:		SendByteCom2
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void SendByteCom2(unsigned char SendData)
{
  	S2CON &= ~S2TI;
  	S2BUF = SendData;
}

/*************************************************
  Function:		UartFindSendIndex
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void UartFindSendIndex(INT8U Com)
{
    INT8U i;
    mUartSendIndex = -1;
    for (i = 0; i < UART_SEND_BUF; i++)
  	{
  		if(mUartSendBuf[i].State == UART_STATE_SEND)
        {
            mUartSendCount = 0;
            mUartSendIndex = i;
            break;
        }    
  	}
    
    if(mUartSendIndex == -1)
    {
        mUartSendState = UART_STATE_NONE;
    }
    else
    {
        mUartSendState = UART_STATE_SEND;
        if(1 == Com)
        {
            SendByte(mUartSendBuf[mUartSendIndex].Buf[0]);    
        }
        else
        {
            SendByteCom2(mUartSendBuf[mUartSendIndex].Buf[0]);  
        }
    }
}

/*************************************************
  Function:		UartSwitchBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void UartSwitchBuf(void)
{
    #if RECV_DEBUG
    int i;
    #endif
    mUartRecvBuf[mUartRecvIndex].State = UART_STATE_RECV;
    mUartRecvBuf[mUartRecvIndex].Len += 1;
    mUartRecvBuf[mUartRecvIndex].Buf[0] = mUartRecvBuf[mUartRecvIndex].Len;
    #if RECV_DEBUG
    for (i = 0 ; i < (mUartRecvBuf[mUartRecvIndex].Len-1); i++)
    {
        UartSendByte(mUartRecvBuf[mUartRecvIndex].Buf[1+i]);
    }
    mUartRecvBuf[mUartRecvIndex].Len = 0;
    mUartRecvBuf[mUartRecvIndex].State = UART_STATE_NONE;
    #endif
	mUartRecvIndex++;
    mUartRecvState = UART_STATE_NONE;
    mUartSwitchTime = 0;
	if(mUartRecvIndex >=  UART_RECV_BUF)
	{
		mUartRecvIndex = 0;
	}
}

/*************************************************
  Function:		UartInterruptReceiveCom1
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartInterruptReceiveCom1(void) interrupt 4 using 1
{
	INT8U ReByte;
	if(RI == 1)
	{
		RI = 0;
		ReByte = SBUF;
        mUartRecvState = UART_STATE_RECV;
        mUartSwitchTime = 0;
        if(mUartRecvBuf[mUartRecvIndex].State == UART_STATE_NONE)
        {
            if(mUartRecvBuf[mUartRecvIndex].Len < UART_DATA_MAX)
            {
                mUartRecvBuf[mUartRecvIndex].Buf[mUartRecvBuf[mUartRecvIndex].Len+1] = ReByte;
                mUartRecvBuf[mUartRecvIndex].Len++;
            }
            else
            {
                UartSwitchBuf();
                mUartRecvBuf[mUartRecvIndex].Len++;
            }
        }
        else
        {
            mUartRecvState = UART_STATE_NONE;
            mUartRecvIndex++;
            if(mUartRecvIndex >=  UART_RECV_BUF)
        	{
        		mUartRecvIndex = 0;
        	}
        }
	}
}

/*************************************************
  Function:		UartReadBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT16U UartReadBuf(INT8U * Buf)
{
    INT16U i,j,ret = 0;

    if(Buf == NULL)
    {
        return 0;
    }
    
    for (i = 0 ; i < UART_RECV_BUF; i++)
    {
        if(mUartRecvBuf[i].State == UART_STATE_RECV)
        {
            UartSendByte(0xFF);
            for (j = 0 ; j < mUartRecvBuf[i].Len-1; j++)
            {
                Buf[j] = mUartRecvBuf[i].Buf[j+1];
            }
            
            ret = mUartRecvBuf[i].Len-1;
            mUartRecvBuf[i].Len = 0;
            mUartRecvBuf[i].State = UART_STATE_NONE;
            break;
        }
    }

    
    
    return ret;
}

/*************************************************
  Function:		UartSendByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartSendByte(unsigned char SendData)
{
  	TI = 0;
  	SBUF = SendData;
  	while(TI == 0);
  	TI = 0;
}

/*************************************************
  Function:		UartSend
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartSend(INT8U Com, unsigned char* Data, unsigned char Len)
{
	INT16U i,j;

    if(Data != NULL && Len > 1)
    {
        for (i = 0; i < UART_SEND_BUF; i++)
      	{
      		if(mUartSendBuf[i].State == UART_STATE_NONE)
            {
               mUartSendBuf[i].Len = Len;
               for (j = 0 ; j < Len; j++)
               {
                   mUartSendBuf[i].Buf[j] = Data[j];
               }
               mUartSendBuf[i].State = UART_STATE_SEND;
               break;
            }    
      	}
    }
    if(mUartSendState == UART_STATE_NONE)
    {
        UartFindSendIndex(Com);
    }

}

/*************************************************
 Function:		UartInterruptReceiveCom2
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void UartInterruptReceiveCom2(void) interrupt 8 using 1
{
    INT8U ReByte;
    if(S2CON & S2RI)
    {
        S2CON &= ~S2RI;
        ReByte = S2BUF;
        mUartRecvState = UART_STATE_RECV;
        mUartSwitchTime = 0;
        if(mUartRecvBuf[mUartRecvIndex].State == UART_STATE_NONE)
        {
            if(mUartRecvBuf[mUartRecvIndex].Len < UART_DATA_MAX)
            {
                mUartRecvBuf[mUartRecvIndex].Buf[mUartRecvBuf[mUartRecvIndex].Len+1] = ReByte;
                mUartRecvBuf[mUartRecvIndex].Len++;
            }
            else
            {
                UartSwitchBuf();
                mUartRecvBuf[mUartRecvIndex].Len++;
            }
        }
        else
        {
            mUartRecvState = UART_STATE_NONE;
            mUartRecvIndex++;
            if(mUartRecvIndex >=  UART_RECV_BUF)
        	{
        		mUartRecvIndex = 0;
        	}
        }
    }
}

/*************************************************
  Function:		UartTimer
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartTimer(void)
{
    if(mUartRecvState == UART_STATE_RECV)
    {
        mUartSwitchTime++;
        if(mUartSwitchTime >=RECV_TIMEOUT)
        {
            UartSwitchBuf();
        }
    }

   if(TI == 1)
   {
        TI = 0;        
        mUartSendCount++;    
        if(mUartSendCount >= mUartSendBuf[mUartSendIndex].Len)
        {
            mUartSendBuf[mUartSendIndex].State = UART_STATE_NONE;
            UartFindSendIndex(1);
        }
        else
        {
            SendByte(mUartSendBuf[mUartSendIndex].Buf[mUartSendCount]);
        }
   }

   #if _UART2_MODULE_ 
   if(S2CON & S2TI)
   {
        S2CON &= ~S2TI;        
        mUartSendCount++;    
        if(mUartSendCount >= mUartSendBuf[mUartSendIndex].Len)
        {
            mUartSendBuf[mUartSendIndex].State = UART_STATE_NONE;
            UartFindSendIndex(1);
        }
        else
        {
            SendByteCom2(mUartSendBuf[mUartSendIndex].Buf[mUartSendCount]);
        }
   } 
   #endif
}

/*************************************************
  Function:		UartProc
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartProc(void)
{
   INT8U buf[UART_RECV_BUF];
   INT8U buflen = 0;
   buflen = UartReadBuf(buf);
   if(buflen > 0)
   {
      hw_wireless_tx_mode();
      hw_wireless_send(buf,buflen);
      hw_wireless_rx_mode();
   }
}

/*************************************************
  Function:		UartInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void UartInit(void)
{   
    INT8U i;
    for (i = 0 ; i < sizeof(mUartRecvBuf); i++)
    {
        mUartRecvBuf[i].State = UART_STATE_NONE;
        mUartRecvBuf[i].Len = 0;
    }

    for (i = 0 ; i < sizeof(mUartSendBuf); i++)
    {
        mUartSendBuf[i].State = UART_STATE_NONE;
        mUartSendBuf[i].Len = 0;
    }
    
    #if (_SYS_TYPE == _STC_15L2K60S2_)
	ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);   
    P_SW1 = ACC;              
    SCON = 0x50;                
    AUXR = 0x40;             
    TMOD = 0x00;               
    TL1 = (65536 - (CHIP_CLK/4/UART_BAUD));   
    TH1 = (65536 - (CHIP_CLK/4/UART_BAUD))>>8;
    TR1 = 1; 

    #if _UART2_MODULE_
    S2CON = 0x50;	
	AUXR |= 0x04;	
	T2L = (65536 - (CHIP_CLK/4/UART_BAUD));  
	T2H = (65536 - (CHIP_CLK/4/UART_BAUD))>>8;		
	AUXR |= 0x10;
    IE2 = 1;
    #endif
    
    ES = 1;    
	#endif
}

