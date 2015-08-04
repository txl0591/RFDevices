/*********************************************************
  Copyright (C), 2013-2016
  File name:	common.c
  Author:   	txl
  Version:   	1.0
  Date: 		13.11.23
  Description:  
  History:            
*********************************************************/
#include "Include.h"

/*************************************************
  Function:		delay_ns
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void delay_ns(unsigned int ns)
{
	unsigned int i;
	for(i = 0; i < ns;i++)
	{
		_nop_();
	}
}

/*************************************************
  Function:		delay_ms
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void delay_ms(unsigned int tm)
{
	unsigned int i, tms = tm;
	#if (_SYS_TYPE == _STC_11L04E_)
	unsigned int j;
    while( tms-- )
    {
    	_nop_();
    	i = 11;
    	j = 190;
    	do
    	{
    		while (--j);
    	} while (--i);
    }
	#endif

    #if (_SYS_TYPE == _STC_11F32XE_)
	unsigned int j;
	while( tms-- )
	{
		i = 18;
		j = 235;
		do
		{
			while (--j);
		} while (--i);
  	}
	#endif
	
	#if (_SYS_TYPE == _STC_15L2K60S2_)
	unsigned int j;
	while( tms-- )
	{
		i = 18;
		j = 235;
		do
		{
			while (--j);
		} while (--i);
  	}	
	#endif
}

