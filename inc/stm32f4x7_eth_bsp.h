/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4x7_ETH_BSP_H
#define __STM32F4x7_ETH_BSP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
//#include "stm32f4_discovery_lcd.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define LAN8720_PHY_ADDRESS       0x01 /* Relative to STM324xG-EVAL Board */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void  ETH_BSP_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4x7_ETH_BSP_H */


/*********** Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE****/
