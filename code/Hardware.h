/*********************************************************
  Copyright (C), 2013-2016
  File name:	Hardware.h
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
#ifndef  __HARDWARE_H__
#define  __HARDWARE_H__

#include "config.h"
#include "Spi.h"
#include "IAP.h"
#include "Rf.h"
#include "Uart.h"
#include "Storage.h"
#include "Timer.h"
#include "Interrupt.h"

#define CHIP_CLK_11059200 11059200L
#define CHIP_CLK_18432000 18432000L
#define CHIP_CLK_22118400 22118400L

#define	UART_BAUD	115200

#if(_SYS_TYPE == _STC_11L04E_)
#define	CHIP_CLK	CHIP_CLK_11059200
#endif

#if(_SYS_TYPE == _STC_15L2K60S2_)
#define	CHIP_CLK	CHIP_CLK_22118400
#endif

/*************************************************
  Function:		HarewareInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareInit(void);

#endif

