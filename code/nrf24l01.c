/*********************************************************
 Copyright (C),2011-2017,NewLand Auto-ID Tech.,Ltd.
 File name: 		nrf24l01.c
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-9-9
 Description: 		
 History: 			
 					
   1.Date:	 		2014-9-9
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/
#include "include.h"

#if (RF_TYPE == RF_24G)

#define REG_NUM		16

/*************************************************
  Function:		hw_24G_spi_ce
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void hw_24G_spi_ce(BOOLEAN Buf)
{
	NRF_CE = Buf;
}

/*************************************************
  Function:		hw_24G_spi_writereg
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void hw_24G_spi_writecmd(INT8U addr, INT8U Buf)
{
    SPIWriteByte(addr,Buf);
}

/*************************************************
  Function:		hw_24G_spi_writebyte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void hw_24G_spi_writebyte(INT8U addr, INT8U Buf)
{
    SPIWriteByte(RF_WRITE_REG|addr,Buf);
}

/*************************************************
  Function:		hw_24G_spi_readbyte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static INT8U hw_24G_spi_readbyte(INT8U addr)
{
    INT8U Buf = SPIReadByte(RF_READ_REG|addr);    
	return Buf;
}

/*************************************************
  Function:		hw_24G_spi_writebuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void hw_24G_spi_writebuf(INT8U addr, INT8U* buf, INT16U len)
{
    SPIWriteBuf(RF_WRITE_REG|addr, buf, len);
}

/*************************************************
  Function:		hw_24G_spi_readbuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void hw_24G_spi_readbuf(INT8U addr, INT8U* buf, INT8U len)
{
	SPIReadBuf(addr, buf, len);
}

/*************************************************
  Function:		hw_24G_init_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void hw_24G_init_mode(void)
{
	INT8U i;
	INT8U Reg[REG_NUM][2]=
	{
		{RF_CONFIG,0x0F},
		{RF_EN_AA,0x01},
		{RF_EN_RXADDR,0x01},
		{RF_SETUP_AW,0x03},
		{RF_SETUP_RETR,0x1a},
		{RF_CH,40},
		{RF_SETUP,0X26},
		{RF_STATUS,0xff},
		{RF_OBSERVE_TX,0x00},
		{RF_CD,0x00},

		{RF_RX_PW_P0,DEFAULT_BUF_LEN},
		{RF_RX_PW_P1,DEFAULT_BUF_LEN},
		{RF_RX_PW_P2,DEFAULT_BUF_LEN},
		{RF_RX_PW_P3,DEFAULT_BUF_LEN},
		{RF_RX_PW_P4,DEFAULT_BUF_LEN},
		{RF_RX_PW_P5,DEFAULT_BUF_LEN},
	};

	hw_24G_spi_ce(0);
	for(i = 0; i < REG_NUM; i++)
	{
		hw_24G_spi_writebyte(Reg[i][0], Reg[i][1]);
	}
	hw_24G_spi_ce(1);
}

/*************************************************
  Function:		hw_24G_tx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_tx_mode(void)
{
	INT8U value = 0;
	hw_24G_spi_ce(0);
	hw_24G_spi_writecmd(RF_FLUSH_TX,0);
	value = hw_24G_spi_readbyte(RF_CONFIG);
	value = value|0x02;
	value = value&0xfe;
  	hw_24G_spi_writebyte(RF_CONFIG, value);
	hw_24G_spi_ce(1);
}

/*************************************************
  Function:		hw_24G_rx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_rx_mode(void)
{
	INT8U value = 0;
	hw_24G_spi_ce(0);
	hw_24G_spi_writecmd(RF_FLUSH_RX,0);
	value = hw_24G_spi_readbyte(RF_CONFIG);
	value = value|0x03;
  	hw_24G_spi_writebyte(RF_CONFIG, value);
	hw_24G_spi_ce(1);
}

/*************************************************
  Function:		hw_24G_set_address
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_set_tx_addr(INT8U *buf, INT8U len)
{
	hw_24G_spi_ce(0);
	hw_24G_spi_writebuf(RF_TX_ADDR, buf, len);  
	hw_24G_spi_ce(1);
}

/*************************************************
  Function:		hw_24G_set_address
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_set_rx_addr(INT8U ch, INT8U *buf, INT8U len)
{
	hw_24G_spi_ce(0);
	hw_24G_spi_writebuf(RF_RX_ADDR_P0+ch, buf, len); 
	hw_24G_spi_ce(1);
}

/*************************************************
  Function:		hw_24G_send
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_send(INT8U* buf, INT8U len)
{
    SPIWriteBuf(RF_WR_TX_PLOAD, buf, len);
}

/*************************************************
  Function:		hw_24G_recv
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_recv(INT8U* buf, INT8U len)
{
	SPIReadBuf(RF_RD_RX_PLOAD, buf, len);
}

/*************************************************
  Function:		hw_24G_set_addr
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_set_addr(INT8U* Addr)
{
    hw_24G_set_tx_addr(Addr, 5);
	hw_24G_set_rx_addr(0, Addr, 5);
}

/*************************************************
  Function:		hw_24G_init
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_init(INT8U *SendAddr, INT8U* RecvAddr)
{
	hw_24G_init_mode();
	hw_24G_set_tx_addr(SendAddr, 5);
	hw_24G_set_rx_addr(0, RecvAddr, 5);
	hw_24G_rx_mode();
}

#endif

