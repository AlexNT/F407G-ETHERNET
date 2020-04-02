#ifndef NET_H_
#define NET_H_
//-----------------------------------------------
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "lwip.h"
#include "lwip/tcp.h"

#define PORT 	2000

//-----------------------------------------------
void tcp_server_init(void);
//-----------------------------------------------
#endif /* NET_H_ */
