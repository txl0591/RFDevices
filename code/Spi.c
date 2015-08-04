/*********************************************************
  Copyright (C), 2013-2016
  File name:	spi.c
  Author:   	txl
  Version:   	1.0
  Date: 		13.11.23
  Description:  
  History:            
*********************************************************/
#include "Include.h"

/*************************************************
  Function:		SPIReadByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
unsigned char SPIRead(void)
{
	unsigned char SPICount;                               
	unsigned char SPIData; 
	                 
	SPIData = 0;
	for (SPICount = 0; SPICount < 8; SPICount++)          
	{
		SPIData <<=1;                                     
		CLR_SPI_CK;
		_nop_();_nop_();
		if(STU_SPI_MISO)
		{
 			SPIData|=0x01;
		}
		SET_SPI_CK;
		_nop_();_nop_();
	}              
	return (SPIData);
} 

/*************************************************
  Function:		SPIWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SPIWrite(unsigned char SPIData)
{
	unsigned char SPICount;                     
	for (SPICount = 0; SPICount < 8; SPICount++)
	{
		if (SPIData & 0x80)
		{
			SET_SPI_MOSI;
		}
		else
		{
			CLR_SPI_MOSI;
		} 
		_nop_();
		CLR_SPI_CK;_nop_();_nop_();
		SET_SPI_CK;_nop_();_nop_();
		SPIData <<= 1;
	}         	
}

/*************************************************
 Function:		SpiTxRxByte
 Descroption:	 
 Input: 
	1.char dat
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char SpiTxRxByte(unsigned char dat)
{
	unsigned char i,temp;
	temp = 0;
	
	CLR_SPI_CK;
	for(i = 0; i < 8; i++)
	{
		if(dat & 0x80)
		{
			SET_SPI_MOSI;
		}
		else 
        {   
            CLR_SPI_MOSI;
        }
		dat <<= 1;
		SET_SPI_CK;
		_nop_();
		_nop_();
        _nop_();
		_nop_();
		temp <<= 1;
		if(STU_SPI_MISO) 
        {
            temp++;
        }
		CLR_SPI_CK;
		_nop_();
		_nop_();	
        _nop_();
		_nop_();
	}
    
	return temp;
}

/*************************************************
  Function:		SPIReadByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
unsigned char SPIReadByte(unsigned char Addr)
{
    unsigned char ucResult=0;
	CLR_SPI_CS;
	SPIWrite(Addr);
	ucResult=SPIRead();
	SET_SPI_CS;
	return ucResult;
} 

/*************************************************
  Function:		SPIWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SPIWriteByte(unsigned char Addr, unsigned char Data)
{
	CLR_SPI_CS;
	SPIWrite(Addr);
	SPIWrite(Data);
	SET_SPI_CS;
}

/*************************************************
 Function:		SPIReadBuf
 Descroption:	SPI 读数据
 Input: 
	1.Addr
	2.*pBuf
	3.len
 Output: 
 Return: 	
 Other:  
*************************************************/
void SPIReadBuf(unsigned char Addr,unsigned char *pBuf,unsigned int len)
{
    unsigned int i;

    CLR_SPI_CS;
  	SPIWrite(Addr);		
    for (i = 0 ; i < len; i++)
    {
      pBuf[i] = SPIRead();
    }
	SET_SPI_CS;
}

/*************************************************
 Function:		SPIWriteBuf
 Descroption:	SPI 写数据
 Input: 
	1.Addr
	2.*pBuf
	3.len
 Output: 
 Return: 	
 Other:  
*************************************************/
void SPIWriteBuf(unsigned char Addr, unsigned char *pBuf, unsigned int len)
{
    unsigned int i;
	CLR_SPI_CS;
  	SPIWrite(Addr);		
    for (i = 0 ; i < len; i++)
    {
       SPIWrite(*pBuf++);
    }
	SET_SPI_CS;
}

