/*********************************************************
 Copyright (C),2011-2017,Electronic Technology Co.,Ltd.
 File name: 		main.c
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-6-10
 Description: 		
 History: 			
 					
   1.Date:	 		2014-6-10
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"

/*************************************************
 Function:		main
 Descroption:	Ö÷³ÌÐò
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void main(void)
{ 
    INT8U buf[DEFAULT_BUF_LEN];
    INT8U len;
    HarewareInit();

    while(1)
    {   
       //UartProc();
       
        len = hw_wireless_recv(buf, DEFAULT_BUF_LEN);
        if (len > 0)
        {
            UartSend(1,buf,len);
        }
    }
}

