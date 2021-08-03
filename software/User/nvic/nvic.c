#include "nvic.h"

void NVIC_Init_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; //NVIC_InitTypeDef����ṹ��������misc.h�ļ��п����ҵ�
  /* Configure one bit for preemption priority */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;// USART2�жϺ�
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //����Ϊ��2���ж����÷�ʽ����1bits������ռʽ��3bits������Ӧʽ�����������misc.c�ļ��У������misc.h�ļ���
  /* �����ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռʽ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧʽ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ж�
  NVIC_Init(&NVIC_InitStructure);
}
