/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4x7_eth_bsp.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USE_LCD        /* enable LCD  */  
//#define USE_DHCP   
 
/* MAC ADDRESS*/
#define MAC_ADDR0   0x00
#define MAC_ADDR1   0x80
#define MAC_ADDR2   0xE1
#define MAC_ADDR3   0x01
#define MAC_ADDR4   0x02
#define MAC_ADDR5   0x03
 
/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   100
   
/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1  

/* MII and RMII mode selection, for STM324xG-EVAL Board(MB786) RevB ***********/
#define RMII_MODE

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void Time_Update(void);
void Delay(uint32_t nCount);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


/*********** Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE****/


