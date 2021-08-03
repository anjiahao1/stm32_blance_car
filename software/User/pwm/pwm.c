#include "pwm.h"
void GPIO_init(void);
void Tim4_PWM_Init(u16 arr,u16 psc)

{

GPIO_InitTypeDef GPIO_InitStructure;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_OCInitTypeDef TIM_OCInitStructure;

 

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�� TIMx ����

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�� PB ʱ��

TIM_DeInit(TIM4);

 

  //���ø�����Ϊ�����������,��� TIM4 CH1 �� PWM ���岨��

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9; //TIM4_CH1

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù������

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�� GPIO

 

TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ������ֵ

TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ ����Ƶ

TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim

TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���

TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��ʼ�� TIMx

TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2 ģʽ

TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��

TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;

TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ



TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ

TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �ߵ�ƽ��Ч

TIM_OC3Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ������ TIMx

TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH3 Ԥװ��ʹ��

TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ

TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �ߵ�ƽ��Ч

TIM_OC4Init(TIM4, &TIM_OCInitStructure); //����ָ���Ĳ�����ʼ������ TIMx

TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4 Ԥװ��ʹ��

TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���

// TIM_CtrlPWMOutputs(TIM4,ENABLE);  //MOE �����ʹ��,�߼���ʱ�����뿪��

TIM_Cmd(TIM4, ENABLE); //ʹ�� TIMx
GPIO_init();
}
void GPIO_init(void)
{
 		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		//GPIO_ResetBits(GPIOA,GPIO_Pin_15);
}