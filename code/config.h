/*********************************************************
  Copyright (C), 2013-2016
  File name:	Config.h
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
#ifndef  __CONFIG_H__
#define  __CONFIG_H__

#define _STC_11L04E_			1
#define _STC_15L2K60S2_			2
#define _STC_11F32XE_           3

#define _SYS_TYPE				_STC_15L2K60S2_

#if (_SYS_TYPE == _STC_11L04E_)
#define _UART_MODULE_			1
#define _RF_MODULE_		    	1
#define _STORAGE_MODULE_        1
#define _UART2_MODULE_          0
#endif

#if (_SYS_TYPE == _STC_15L2K60S2_)
#define _UART_MODULE_			1
#define _RF_MODULE_		    	1
#define _STORAGE_MODULE_        1
#define _UART2_MODULE_          0
#endif

#define RF_NONE                 0
#define RF_24G                  1
#define RF_433M                 2

#if _RF_MODULE_
#define RF_TYPE                 RF_433M
#else
#define RF_TYPE                 RF_NONE
#endif

#define _VERSION_				"RF V1.0"
#define _HW_VERSION_			0x10
#define _SW_VERSION_			0x10

#endif

