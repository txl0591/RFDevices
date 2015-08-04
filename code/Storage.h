/*********************************************************
  Copyright (C), 2013-2016
  File name:	Storage.h
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
#ifndef  __STORAGE_H__
#define  __STORAGE_H__

#include "Config.h"

#define _SOTRAGE_NONE_		0x00
#define _SOTRAGE_CODE_		0x01
#define _SOTRAGE_IAP_		0x02

#if _STORAGE_MODULE_
#if (_SYS_TYPE == _STC_11F32XE_)
#define STORAGE_TYPE 		_SOTRAGE_CODE_
#endif

#if (_SYS_TYPE == _STC_15L2K60S2_)
#define STORAGE_TYPE 		_SOTRAGE_IAP_
#endif

#else
#define STORAGE_TYPE 		_SOTRAGE_NONE_
#endif

#define ADDRESS_RF_SEND	    0x0000
#define ADDRESS_RF_RECV		0x0005

#if _STORAGE_MODULE_
/*************************************************
  Function:		StorageRead
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageReadByte(INT16U addr);

/*************************************************
  Function:		StorageWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageWriteByte(INT16U addr, INT8U buf);

/*************************************************
  Function:		StorageRead
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageRead(INT16U addr, INT8U *buf, INT16U len);

/*************************************************
  Function:		StorageWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT16U StorageWrite(INT16U addr, INT8U *buf, INT16U len);

#endif
/*************************************************
  Function:		StorageReadAddr
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageReadAddr(INT8U *SendAddr, INT8U* RecvAddr);


#endif

