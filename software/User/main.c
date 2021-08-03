/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "bsp_led.h"
#include "stdio.h"
#include "bsp_SysTick.h"
#include <oled.h>
#include <delay.h>
#include <spi1.h>
#include "mpu6050.h"
#include "bsp_exit.h"
#include "encode.h"
#include "pwm.h"
#include "bsp_key.h"
#include "bsp_esp8266.h"
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
	u8 res1;
extern float Pitch,Roll; 
extern short gyro[3], accel[3], sensors;
extern int encode1;
extern int encode2;
int main(void)
{	 
	/* LED 端口初始化 */
	char a[20];
	delay_init();

	KEY_GPIO_Config();
	LED_GPIO_Config();
	
ESP8266_GPIO_Config();
	SPI1_Init_Config();
	OLED_Init_Config();
	OLED_Init();
	OLED_ShowString(0,0, "ok");
	encode_init_tim1();
	Encoder_Init_TIM2();
	i2c_init();
	mpu6050_init();
	res1=DMP_Init();
	exit_init();
	OLED_Clear();	
	delay_ms(2000);
		ESP8266_init();
	Tim4_PWM_Init(7199,0);
	
	while(1)		
	{	
		sprintf(a,"%.2f  ",Pitch);
		OLED_ShowString(0,2, a);
				sprintf(a,"%.2f  ",Roll);
		OLED_ShowString(0,4, a);
			sprintf(a,"%d  ",encode1);
		OLED_ShowString(0,6, a);
					sprintf(a,"%d  ",encode2);
		OLED_ShowString(0,0, a);
					sprintf(a,"%d  ",gyro[2]);
		OLED_ShowString(64,0, a);
	}
}


