/*********************************************************
 Copyright (C),2011-2017,Electronic Technology Co.,Ltd.
 File name: 		Interrupt.c
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-6-10
 Description: 		
 History: 			
 					
   1.Date:	 		2014-6-10
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/

#include "include.h"

/*************************************************
  Function:		ExInt0_Interrupt
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void ExInt0_Interrupt() interrupt 0
{
    INT8U buf[DEFAULT_BUF_LEN];
    UartSendByte(0xAB);
    hw_wireless_recv(buf, DEFAULT_BUF_LEN);
}

/*************************************************
  Function:		InitInterrupt
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void InitInterrupt(void)
{
    //NRF_IRQ = 1;
    IT0 = 0;
    EX0 = 1;
}
