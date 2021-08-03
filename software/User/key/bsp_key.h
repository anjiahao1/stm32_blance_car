#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"



#define KEY_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY_GPIO_PIN		GPIO_Pin_10			        /* 连接到SCL时钟线的GPIO */
void KEY_GPIO_Config(void);
u8 click_N_Double (u8 time);
#endif
