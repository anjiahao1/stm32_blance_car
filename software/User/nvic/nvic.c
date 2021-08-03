#include "nvic.h"

void NVIC_Init_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; //NVIC_InitTypeDef这个结构体我们在misc.h文件中可以找到
  /* Configure one bit for preemption priority */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;// USART2中断号
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //配置为第2种中端配置方式，即1bits配置抢占式，3bits配置响应式，这个函数在misc.c文件中，组别在misc.h文件中
  /* 配置中断源 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占式优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应式优先级0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能中断
  NVIC_Init(&NVIC_InitStructure);
}
