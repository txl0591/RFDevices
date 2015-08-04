/*********************************************************
  Copyright (C), 2013-2016
  File name:	Hardware.c
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

/*************************************************
  Function:		PortInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void PortInit(void)
{
	#if(_SYS_TYPE == _STC_11L04E_)
	#endif
    
    #if(_SYS_TYPE == _STC_15L2K60S2_)
	#endif
}

/*************************************************
  Function:		HarewareInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareInit(void)
{
    INT8U SendAddr[5] = {0,0,0,0,1};
    INT8U RecvAddr[5] = {0,0,0,0,1};

	EA = 0;
	PortInit();
    TimerInit(); 
    //StorageReadAddr(SendAddr,RecvAddr);
    UartInit();
    hw_wireless_init(SendAddr, RecvAddr);
    InitInterrupt();
    EA = 1; 
    TimerStart();    
}

