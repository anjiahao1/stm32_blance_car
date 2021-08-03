#include "pwm.h"
void GPIO_init(void);
void Tim4_PWM_Init(u16 arr,u16 psc)

{

GPIO_InitTypeDef GPIO_InitStructure;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_OCInitTypeDef TIM_OCInitStructure;

 

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能 TIMx 外设

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能 PB 时钟

TIM_DeInit(TIM4);

 

  //设置该引脚为复用输出功能,输出 TIM4 CH1 的 PWM 脉冲波形

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9; //TIM4_CH1

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能输出

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIO

 

TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载周期值

TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值 不分频

TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim

TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数

TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化 TIMx

TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2 模式

TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能

TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;

TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值



TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值

TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 高电平有效

TIM_OC3Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设 TIMx

TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH3 预装载使能

TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值

TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 高电平有效

TIM_OC4Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设 TIMx

TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4 预装载使能

TIM_ARRPreloadConfig(TIM4, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器

// TIM_CtrlPWMOutputs(TIM4,ENABLE);  //MOE 主输出使能,高级定时器必须开启

TIM_Cmd(TIM4, ENABLE); //使能 TIMx
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