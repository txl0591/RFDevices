/*********************************************************
  Copyright (C), 2013-2016
  File name:	Storage.c
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

#if _STORAGE_MODULE_
/*************************************************
  Function:		StorageReadByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageReadByte(INT16U addr)
{
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	return IAPReadByte(addr);
	#endif
}

/*************************************************
  Function:		StorageWriteByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageWriteByte(INT16U addr, INT8U buf)
{
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	IAPWriteByte(addr,buf);
	#endif
}

/*************************************************
  Function:		StorageRead
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageRead(INT16U addr, INT8U *buf, INT16U len)
{
	int i,nlen = 0;
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	for(i = 0; i < len; i++)
	{
		buf[i] = StorageReadByte(addr+i);
		nlen++;
	}
	#endif
	return nlen;
}

/*************************************************
  Function:		StorageWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT16U StorageWrite(INT16U addr, INT8U *buf, INT16U len)
{
	int i,nlen = 0;
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	for(i = 0; i < len; i++)
	{
		StorageWriteByte(addr+i,buf[i]);
		nlen++;
	}
	#endif
	return nlen;
}
#endif

/*************************************************
  Function:		StorageReadAddr
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageReadAddr(INT8U *SendAddr, INT8U* RecvAddr)
{
    StorageRead(ADDRESS_RF_SEND, SendAddr, 5);
    StorageRead(ADDRESS_RF_RECV, RecvAddr, 5);
}

