/*********************************************************
 Copyright (C),2011-2017,Electronic Technology Co.,Ltd.
 File name: 		nrf24l01.h
 Author: 			Tangxl
 Version: 			1.0
 Date: 				2014-6-10
 Description: 		
 History: 			
 					
   1.Date:	 		2014-6-10
 	 Author:	 	Tangxl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _NRF24L01_H_
#define _NRF24L01_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "config.h"

/**********  NRF24L01¼Ä´æÆ÷²Ù×÷ÃüÁî  ***********/
#define RF_READ_REG        0x00  // Define read command to register
#define RF_WRITE_REG       0x20  // Define write command to register
#define RF_RD_RX_PLOAD     0x61  // Define RX payload register address
#define RF_WR_TX_PLOAD     0xA0  // Define TX payload register address
#define RF_FLUSH_TX        0xE1  // Define flush TX register command
#define RF_FLUSH_RX        0xE2  // Define flush RX register command
#define RF_REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define RF_NOP             0xFF  // Define No Operation, might be used to read status register

#define RF_CONFIG          0x00  // 'Config' register address
#define RF_EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define RF_EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define RF_SETUP_AW        0x03  // 'Setup address width' register address
#define RF_SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH              0x05  // 'RF channel' register address
#define RF_SETUP           0x06  // 'RF setup' register address
#define RF_STATUS          0x07  // 'Status' register address
#define RF_OBSERVE_TX      0x08  // 'Observe TX' register address
#define RF_CD              0x09  // 'Carrier Detect' register address
#define RF_RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RF_RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RF_RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RF_RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RF_RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RF_RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define RF_TX_ADDR         0x10  // 'TX address' register address
#define RF_RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RF_RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RF_RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RF_RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RF_RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RF_RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define RF_FIFO_STATUS     0x17  // 'FIFO Status Register' register address
#define RF_STA_MARK_RX     0X40
#define RF_STA_MARK_TX     0X20
#define RF_STA_MARK_MX     0X10	

#define RF_SET_DEFAULT_ADDR(data)	data[0] = 0x00;	data[1] = 0x00; data[2] = 0x00; data[3] = 0x00; data[4] = 0x01

#if (RF_TYPE == RF_24G)
/*************************************************
  Function:		hw_24G_tx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_tx_mode(void);

/*************************************************
  Function:		hw_24G_rx_mode
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_rx_mode(void);

/*************************************************
  Function:		hw_24G_set_address
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_set_tx_addr(INT8U *buf, INT8U len);

/*************************************************
  Function:		hw_24G_set_address
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_set_rx_addr(INT8U ch, INT8U *buf, INT8U len);

/*************************************************
  Function:		hw_24G_send
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_send(INT8U* buf, INT8U len);

/*************************************************
  Function:		hw_24G_recv
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_recv(INT8U* buf, INT8U len);

/*************************************************
  Function:		hw_24G_set_addr
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_set_addr(INT8U* Addr);

/*************************************************
  Function:		hw_24G_init
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void hw_24G_init(INT8U *SendAddr, INT8U* RecvAddr);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _NRF24L01_H_ Edit By Tangxl 2014-6-10 */

