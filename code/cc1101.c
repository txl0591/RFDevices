/*********************************************************
 Copyright (C),2011-2017,NewLand Auto-ID Tech.,Ltd.
 File name: 		cc1101.c
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-9-18
 Description: 		
 History: 			
 					
   1.Date:	 		2014-9-18
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/
#include "include.h"

/*************************************************
 Function:		hw_cc1101_read_single
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static unsigned char hw_cc1101_read_single(unsigned char Addr)
{
    INT8U temp, value;
    temp = Addr|READ_SINGLE;
	SPI_CS = 0;
	while (SPI_MISO);
	SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
	SPI_CS = 1;
	return value;
}

/*************************************************
 Function:		hw_cc1101_read
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void hw_cc1101_read(unsigned char Addr,unsigned char *pBuf,unsigned int len)
{
    INT8U i,temp;
	temp = Addr | READ_BURST;		//写入要读的配置寄存器地址和读命令
    SPI_CS = 0;
    while (SPI_MISO);
	SpiTxRxByte(temp);   
    for (i = 0; i < len; i++) 
	{
        pBuf[i] = SpiTxRxByte(0);
    }
    SPI_CS = 1;
    
}

/*************************************************
 Function:		hw_cc1101_write_reg
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void hw_cc1101_write_reg(unsigned char reg)
{
    SPI_CS= 0; 
	while (SPI_MISO);
    SpiTxRxByte(reg); 		
    SPI_CS = 1; 
}

/*************************************************
 Function:		hw_cc1101_write_single
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void hw_cc1101_write_single(unsigned char Addr,unsigned char pBuf)
{
    SPI_CS= 0; 
	while (SPI_MISO);
    SpiTxRxByte(Addr);		
    SpiTxRxByte(pBuf);	
    SPI_CS = 1; 
}

/*************************************************
 Function:		hw_cc1101_write
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void hw_cc1101_write(unsigned char Addr,unsigned char *pBuf,unsigned int len)
{
    INT8U temp = Addr | WRITE_BURST;
    INT8U i;
    
    SPI_CS= 0; 
	while (SPI_MISO);
    SpiTxRxByte(temp);		
    for (i = 0 ; i < len; i++)
    {
        SpiTxRxByte(pBuf[i]);	
    }
    SPI_CS = 1;    
}

/*************************************************
 Function:		hw_cc1101_reset
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void hw_cc1101_reset(void) 
{
    SPI_CS= 0; 
	while (SPI_MISO);
    SpiTxRxByte(CCxxx0_SRES); 	
    while (SPI_MISO);
    SPI_CS = 1; 
}

/*************************************************
 Function:		hw_cc1101_powon
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void hw_cc1101_powon(void) 
{
	SPI_CS = 1; 
	delay_ns(20); 
	SPI_CS = 0; 
	delay_ns(20); 
	SPI_CS = 1; 
	delay_ns(9000); 
}

/*************************************************
  Function:		hw_cc1101_tx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_cc1101_tx_mode(void)
{
    hw_cc1101_write_reg(CCxxx0_STX); 		
}

/*************************************************
  Function:		hw_24G_rx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_cc1101_rx_mode(void)
{
    hw_cc1101_write_reg(CCxxx0_SRX); 		
}

/*************************************************
 Function:		hw_cc1101_recv
 Descroption:	 
 Input: 
	1.buf
	2.len
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U hw_cc1101_recv(INT8U* buf, INT8U len)
{
    INT8U status[2];
    INT8U packetLength;
	INT8U i=(len)*4;  

    hw_cc1101_write_reg(CCxxx0_SRX);
    delay_ns(5);
	while (GDO0)
	{
		delay_ns(20);
		--i;
		if(i < 1)
        {
            return 0;
        }      
	}	 
    if ((hw_cc1101_read_single(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO)) //如果接的字节数不为0
	{
        packetLength = hw_cc1101_read_single(CCxxx0_RXFIFO);
        if (packetLength <= len) 		
		{
            hw_cc1101_read(CCxxx0_RXFIFO, buf, packetLength); 
            hw_cc1101_read(CCxxx0_RXFIFO, status, 2); 	
			hw_cc1101_write_reg(CCxxx0_SFRX);		//清洗接收缓冲区
            if(status[1] & CRC_OK)			//如果校验成功返回接收成功
            {
                UartSendByte(0xAC);
                return packetLength;   
            }
            else
            {
                return 0;
            }
        }
		else 
		{
            hw_cc1101_write_reg(CCxxx0_SFRX);		//清洗接收缓冲区
            return 0;
        }
  
    } 

 	return 0;
}

/*************************************************
 Function:		hw_cc1101_send
 Descroption:	 
 Input: 
	1.buf
	2.len
 Output: 
 Return: 	
 Other:  
*************************************************/
void hw_cc1101_send(INT8U* buf, INT8U len)
{
    INT8U nlen = 0;
    hw_cc1101_write_single(CCxxx0_TXFIFO, len);
    hw_cc1101_write(CCxxx0_TXFIFO, buf, len);	        
    hw_cc1101_write_reg(CCxxx0_STX);		
    // Wait for GDO0 to be set -> sync transmitted
    while (!GDO0);
    // Wait for GDO0 to be cleared -> end of packet
    while (GDO0);
	hw_cc1101_write_reg(CCxxx0_SFTX);
}

/*************************************************
 Function:		hw_cc1101_init
 Descroption:	 
 Input: 
	1.*SendAddr
	2.RecvAddr
 Output: 
 Return: 	
 Other:  
*************************************************/
void hw_cc1101_init(INT8U *SendAddr, INT8U* RecvAddr)
{
    int i;
    INT8U config[35][2] = 
    {
    	{CCxxx0_FSCTRL0,0x00},
        {CCxxx0_FSCTRL1,0x08},   // FSCTRL1   Frequency synthesizer control.
        {CCxxx0_FSCTRL0,0x00},   // FSCTRL0   Frequency synthesizer control.
        {CCxxx0_FREQ2,0x10},   // FREQ2     Frequency control word, high byte.
        {CCxxx0_FREQ1,0xA7},   // FREQ1     Frequency control word, middle byte.
        {CCxxx0_FREQ0, 0x62},   // FREQ0     Frequency control word, low byte.
        {CCxxx0_MDMCFG4, 0x5B},   // MDMCFG4   Modem configuration.
        {CCxxx0_MDMCFG3,0xF8},   // MDMCFG3   Modem configuration.
        {CCxxx0_MDMCFG2,0x03},   // MDMCFG2   Modem configuration.
        {CCxxx0_MDMCFG1, 0x22},   // MDMCFG1   Modem configuration.
        {CCxxx0_MDMCFG0, 0xF8},   // MDMCFG0   Modem configuration.
        {CCxxx0_CHANNR, 0x00},   // CHANNR    Channel number.
        {CCxxx0_DEVIATN,  0x47},   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
        {CCxxx0_FREND1,0xB6},   // FREND1    Front end RX configuration.
        {CCxxx0_FREND0, 0x10},   // FREND0    Front end RX configuration.
        {CCxxx0_MCSM0,  0x18},   // MCSM0     Main Radio Control State Machine configuration.
        {CCxxx0_FOCCFG,0x1D},   // FOCCFG    Frequency Offset Compensation Configuration.
        {CCxxx0_BSCFG,0x1C},   // BSCFG     Bit synchronization Configuration.
        {CCxxx0_AGCCTRL2,0xC7},   // AGCCTRL2  AGC control.
        {CCxxx0_AGCCTRL1,0x00},   // AGCCTRL1  AGC control.
        {CCxxx0_AGCCTRL0,0xB2},   // AGCCTRL0  AGC control.
        {CCxxx0_FSCAL3,0xEA},   // FSCAL3    Frequency synthesizer calibration.
        {CCxxx0_FSCAL2,0x2A},   // FSCAL2    Frequency synthesizer calibration.
        {CCxxx0_FSCAL1,0x00},   // FSCAL1    Frequency synthesizer calibration.
        {CCxxx0_FSCAL0,0x11},   // FSCAL0    Frequency synthesizer calibration.
        {CCxxx0_FSTEST,0x59},   // FSTEST    Frequency synthesizer calibration.
        {CCxxx0_TEST2,0x81},   // TEST2     Various test settings.
        {CCxxx0_TEST1,0x35},   // TEST1     Various test settings.
        {CCxxx0_TEST0,0x09},   // TEST0     Various test settings.
        {CCxxx0_IOCFG2,0x0B},   // IOCFG2    GDO2 output pin configuration.
        {CCxxx0_IOCFG0,0x06},   // IOCFG0D   GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.
        {CCxxx0_PKTCTRL1,0x04},   // PKTCTRL1  Packet automation control.
        {CCxxx0_PKTCTRL0,0x05},   // PKTCTRL0  Packet automation control.
        {CCxxx0_ADDR,0x01},   // ADDR      Device address.
        {CCxxx0_PKTLEN,0x0C}    // PKTLEN    Packet length.
    };

    //INT8U PaTabel[8] = {0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04};  //-30dBm   功率最小
    //INT8U PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};  //0dBm
    INT8U PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};   //10dBm     功率最大

    hw_cc1101_powon();
    hw_cc1101_reset();
    for (i = 0 ; i < 35; i++)
    {
        hw_cc1101_write_single(config[i][0], config[i][1]);
    }
    hw_cc1101_write(CCxxx0_PATABLE, PaTabel, 8);
    hw_cc1101_rx_mode();
}


