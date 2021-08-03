#ifndef __BSP_EXIT_H
#define __BSP_EXIT_H
#include "stm32f10x.h"

#define EXIT_GPIO_Port GPIOB
#define EXIT_GPIO_Pin GPIO_Pin_5
#define EXIT_GPIO_CLK (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define EXIT_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define EXIT_INT_EXTI_PINSOURCE    GPIO_PinSource5
#define EXIT_INT_EXTI_LINE         EXTI_Line5
#define EXIT_INT_EXTI_IRQ          EXTI9_5_IRQn

#define EXIT_IRQHandler            EXTI9_5_IRQHandler
void exit_init(void);

#endif
