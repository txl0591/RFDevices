/*********************************************************
 Copyright (C),2011-2017,Electronic Technology Co.,Ltd.
 File name: 		Spi.h
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-6-10
 Description: 		
 History: 			
 					
   1.Date:	 		2014-6-10
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _SPI_H_
#define _SPI_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

sbit  SPI_CS = P1^2;
sbit  SPI_CLK = P1^5;
sbit  SPI_MOSI = P1^3;
sbit  SPI_MISO = P1^4;

#define SET_SPI_CS  SPI_CS = 1
#define CLR_SPI_CS  SPI_CS = 0

#define SET_SPI_CK  SPI_CLK = 1
#define CLR_SPI_CK  SPI_CLK = 0

#define SET_SPI_MOSI  SPI_MOSI = 1
#define CLR_SPI_MOSI  SPI_MOSI = 0

#define STU_SPI_MISO  SPI_MISO

/*************************************************
 Function:		SpiTxRxByte
 Descroption:	 
 Input: 
	1.char dat
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char SpiTxRxByte(unsigned char dat);

/*************************************************
  Function:		SPIReadByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
unsigned char SPIRead(void);

/*************************************************
  Function:		SPIWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SPIWrite(unsigned char SPIData);

/*************************************************
  Function:		SPIReadByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
unsigned char SPIReadByte(unsigned char Addr); 

/*************************************************
  Function:		SPIWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SPIWriteByte(unsigned char Addr, unsigned char Data);

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
void SPIReadBuf(unsigned char Addr,unsigned char *pBuf,unsigned int len);

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
void SPIWriteBuf(unsigned char Addr, unsigned char *pBuf, unsigned int len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _SPI_H_ Edit By Tangxl 2014-6-10 */

