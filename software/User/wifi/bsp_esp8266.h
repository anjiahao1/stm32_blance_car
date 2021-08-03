#ifndef _BSP_ESP8266_H
#define _BSP_ESP8266_H
#include "stm32f10x.h"
#include "delay.h"
#include "bsp_led.h"
#define      macESP8266_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macESP8266_CH_PD_CLK                             RCC_APB2Periph_GPIOB  
#define      macESP8266_CH_PD_PORT                            GPIOB
#define      macESP8266_CH_PD_PIN                             GPIO_Pin_15

#define      macESP8266_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      macESP8266_RST_CLK                               RCC_APB2Periph_GPIOB
#define      macESP8266_RST_PORT                              GPIOB
#define      macESP8266_RST_PIN                               GPIO_Pin_14

 

#define      macESP8266_USART_BAUD_RATE                       115200

#define      macESP8266_USARTx                                USART1
#define      macESP8266_USART_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macESP8266_USART_CLK                             RCC_APB2Periph_USART1
#define      macESP8266_USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      macESP8266_USART_GPIO_CLK                        RCC_APB2Periph_GPIOB     
#define      macESP8266_USART_TX_PORT                         GPIOB   
#define      macESP8266_USART_TX_PIN                          GPIO_Pin_6
#define      macESP8266_USART_RX_PORT                         GPIOB
#define      macESP8266_USART_RX_PIN                          GPIO_Pin_7
#define      macESP8266_USART_IRQ                             USART1_IRQn
#define      macESP8266_USART_INT_FUN                         USART1_IRQHandler
void ESP8266_GPIO_Config(void) ;
void ESP8266_init(void);






#endif