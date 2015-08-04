/*********************************************************
 Copyright (C),2011-2017,NewLand Auto-ID Tech.,Ltd.
 File name: 		Rf.h
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-9-18
 Description: 		
 History: 			
 					
   1.Date:	 		2014-9-18
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _RF_H_
#define _RF_H_

#include "config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (RF_TYPE == RF_24G)
#include "nrf24l01.h"
#endif
#if (RF_TYPE == RF_433M)
#include "cc1101.h"
#endif

sbit NRF_CE   = P1^6;
sbit NRF_IRQ  = P3^2;

#define DEFAULT_BUF_LEN    16  

/*************************************************
  Function:		hw_wireless_tx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_wireless_tx_mode(void);

/*************************************************
  Function:		hw_24G_rx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_wireless_rx_mode(void);

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
INT8U hw_wireless_recv(INT8U* buf, INT8U len);

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
void hw_wireless_send(INT8U* buf, INT8U len);

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
void hw_wireless_init(INT8U *SendAddr, INT8U* RecvAddr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _RF_H_ Edit By Tangxl 2014-9-18 */

