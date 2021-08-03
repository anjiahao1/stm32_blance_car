#include "bsp_exit.h"
void exit_init(void)
{
  
	EXTI_InitTypeDef EXITSturct;
	GPIO_InitTypeDef GPIOSturct;
	NVIC_InitTypeDef NVICSturct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVICSturct.NVIC_IRQChannel= EXIT_INT_EXTI_IRQ;
	NVICSturct.NVIC_IRQChannelPreemptionPriority=0;
	NVICSturct.NVIC_IRQChannelSubPriority=1;
	NVICSturct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVICSturct);
	RCC_APB2PeriphClockCmd( EXIT_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE);
	GPIOSturct.GPIO_Pin=EXIT_GPIO_Pin;
	GPIOSturct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(EXIT_GPIO_Port, &GPIOSturct);
//------------------------------
	GPIO_EXTILineConfig(EXIT_INT_EXTI_PORTSOURCE,EXIT_INT_EXTI_PINSOURCE);
	EXITSturct.EXTI_Line=EXIT_INT_EXTI_LINE ;
	EXITSturct.EXTI_LineCmd=ENABLE;
	EXITSturct.EXTI_Mode= EXTI_Mode_Interrupt;
	EXITSturct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXITSturct);

}
