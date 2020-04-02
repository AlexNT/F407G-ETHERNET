/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_13
#define LED4_GPIO_Port GPIOD
#define LED5_Pin GPIO_PIN_14
#define LED5_GPIO_Port GPIOD
#define LED6_Pin GPIO_PIN_15
#define LED6_GPIO_Port GPIOD

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
