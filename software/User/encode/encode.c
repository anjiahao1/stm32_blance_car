#include "encode.h"
int encode1=0;
int encode2=0;
void encode_init_tim1(void)
{
		
		GPIO_InitTypeDef G;
		TIM_TimeBaseInitTypeDef T;
		TIM_ICInitTypeDef       TI;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		G.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
		G.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&G);
		T.TIM_ClockDivision=TIM_CKD_DIV2;
		T.TIM_CounterMode=TIM_CounterMode_Up ;
		T.TIM_Period=65535;
		T.TIM_Prescaler=0X0;
		T.TIM_RepetitionCounter=0;
		TIM_TimeBaseInit(TIM1,&T);
		TIM_ICStructInit(&TI);
		TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12 ,
                               TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
		TI.TIM_ICFilter=10;;
	TIM_ICInit(TIM1,&TI);
		TIM_ClearFlag(TIM1,TIM_FLAG_Update);
		TIM_ITConfig(TIM1,TIM_IT_Update, ENABLE);
		TIM_SetCounter(TIM1,0);
		TIM_Cmd(TIM1, ENABLE); 
}
 void Encoder_Init_TIM2(void)
{
		GPIO_InitTypeDef G;
		TIM_TimeBaseInitTypeDef T;
		TIM_ICInitTypeDef       TI;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		G.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
		G.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&G);
		T.TIM_ClockDivision=TIM_CKD_DIV1;
		T.TIM_CounterMode=TIM_CounterMode_Up ;
		T.TIM_Period=65535;
		T.TIM_Prescaler=0X0;
		T.TIM_RepetitionCounter=0;
		TIM_TimeBaseInit(TIM2,&T);
		TIM_ICStructInit(&TI);
		TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12 ,
                               TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
		TIM_ICInit(TIM2,&TI);
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		TI.TIM_ICFilter=6;
		TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
		TIM_SetCounter(TIM2,0);
		TIM_Cmd(TIM2, ENABLE); 
 }
void TIM1_IRQHandler(void)
 {                                       
     if(TIM1->SR&0X0001)//溢出中断
     {                                                        
     }                   
     TIM1->SR&=~(1<<0);//清除中断标志位         
 }
 void TIM2_IRQHandler(void)
 {                                       
     if(TIM2->SR&0X0001)//溢出中断
     {                                                        
     }                   
     TIM2->SR&=~(1<<0);//清除中断标志位         
 }