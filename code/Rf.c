/*********************************************************
 Copyright (C),2011-2017,NewLand Auto-ID Tech.,Ltd.
 File name: 		Rf.c
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-9-18
 Description: 		
 History: 			
 					
   1.Date:	 		2014-9-18
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"

/*************************************************
  Function:		hw_wireless_tx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_wireless_tx_mode(void)
{
    #if (RF_TYPE == RF_24G)
    hw_24G_tx_mode();
    #endif

    #if (RF_TYPE == RF_433M)
    hw_cc1101_tx_mode();
    #endif
}

/*************************************************
  Function:		hw_24G_rx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_wireless_rx_mode(void)
{
    #if (RF_TYPE == RF_24G)
    hw_24G_rx_mode();
    #endif

    #if (RF_TYPE == RF_433M)
    hw_cc1101_rx_mode();
    #endif
}

/*************************************************
 Function:		hw_wireless_recv
 Descroption:	 
 Input: 
	1.buf
	2.len
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U hw_wireless_recv(INT8U* buf, INT8U len)
{
    #if (RF_TYPE == RF_24G)
    hw_24G_recv(buf, len);
    return len;
    #endif

    #if (RF_TYPE == RF_433M)
    return hw_cc1101_recv(buf, len);
    #endif
}

/*************************************************
 Function:		hw_wireless_send
 Descroption:	 
 Input: 
	1.buf
	2.len
 Output: 
 Return: 	
 Other:  
*************************************************/
void hw_wireless_send(INT8U* buf, INT8U len)
{
    #if (RF_TYPE == RF_24G)
    hw_24G_send(buf, len);
    #endif

    #if (RF_TYPE == RF_433M)
    hw_cc1101_send(buf, len);
    #endif
}

/*************************************************
 Function:		hw_wireless_init
 Descroption:	 
 Input: 
	1.*SendAddr
	2.RecvAddr
 Output: 
 Return: 	
 Other:  
*************************************************/
void hw_wireless_init(INT8U *SendAddr, INT8U* RecvAddr)
{
    #if (RF_TYPE == RF_24G)
    hw_24G_init(SendAddr, RecvAddr);
    #endif

    #if (RF_TYPE == RF_433M)
    hw_cc1101_init(SendAddr, RecvAddr);
    #endif
}

