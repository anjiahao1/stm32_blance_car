//#include "contral.h"
//#define ZHONGZHI -2
//extern int encode1;
//extern int encode2;
//extern float Pitch,Roll; 
//extern short gyro[3], accel[3], sensors;
//extern u8 up_flag,donw_flag,left_flag,right_flag;
//int Moto1,Moto2,Balance_Pwm,Velocity_Pwm,turn_pwm;
//u8 Flag_Target=0;

//int EXIT_IRQHandler(void)
//{		if(EXTI_GetFlagStatus(EXIT_INT_EXTI_LINE  ) != RESET)
//		{		 EXTI_ClearITPendingBit(EXIT_INT_EXTI_LINE );

//		Read_DMP();                                             //===������̬	



//			
//		encode1=-Read_Encoder(1);
//		encode2=Read_Encoder(2);
//		Balance_Pwm =balance(Pitch,gyro[1]); 
//		Velocity_Pwm=velocity(encode1,encode2);
//		turn_pwm=turn(encode1,encode2,gyro[2]);
//			Moto1=Balance_Pwm-Velocity_Pwm+turn_pwm;   
// 	  	Moto2=Balance_Pwm-Velocity_Pwm-turn_pwm;
//			//if(Pick_Up(accel[2],Pitch,encode1,encode2))//===����Ƿ�С��������
//			//GPIO_ResetBits(GPIOA,GPIO_Pin_15);                                                      //===���������͹رյ��
//			if(Put_Down(Pitch,encode1,encode2))              //===����Ƿ�С��������
//			GPIO_SetBits(GPIOA,GPIO_Pin_15); 
//			Xianfu_Pwm();
//			Set_Pwm(Moto1,Moto2);
//			key();
//		}

//        return 0;
//}
//int Read_Encoder(u8 TIMX)
//{
//     int Encoder_TIM;    
//    switch(TIMX)
//			{		 case 1:Encoder_TIM= (short)TIM1 -> CNT;  TIM1 -> CNT=0;break;
//         case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
//         case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;    
//         case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;    
//         default:  Encoder_TIM=0;
//     }
//     return Encoder_TIM;
// }
//void Set_Pwm(int moto1,int moto2)
//{
//    	if(moto2<0)	
//			{
//				GPIO_SetBits(GPIOB,GPIO_Pin_4);
//				GPIO_ResetBits(GPIOB,GPIO_Pin_3);
//			}
//			else
//			{
//				GPIO_SetBits(GPIOB,GPIO_Pin_3);
//				GPIO_ResetBits(GPIOB,GPIO_Pin_4);
//			} 	         
//			TIM4->CCR4=myabs(moto2);
//    	if(moto1<0)	
//			{
//				GPIO_SetBits(GPIOA, GPIO_Pin_12);
//				GPIO_ResetBits( GPIOA,GPIO_Pin_11);
//			}
//			else
//			{
//				GPIO_SetBits(GPIOA,GPIO_Pin_11);
//				GPIO_ResetBits(GPIOA,GPIO_Pin_12);
//			} 	         
//			TIM4->CCR3=myabs(moto1);
//}
//int balance(float Angle,float Gyro)
//{  
//   float Bias,kp=-300,kd=-0.8;
//	 int balance;
//	 Bias=Angle-ZHONGZHI;       //===���ƽ��ĽǶ���ֵ �ͻ�е���
//	 balance=kp*Bias+Gyro*kd;   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
//	 return balance;
//}
//int velocity(int encoder_left,int encoder_right)
//{  
//     static float Velocity,Encoder_Least,Encoder,Movement;
//	  static float Encoder_Integral,Target_Velocity;
//	  float kp=360;
//		float ki=kp/200;
//			if(up_flag)Target_Velocity++;
//			if(donw_flag)Target_Velocity--;
//			if(Target_Velocity>=10&&up_flag)Target_Velocity=10;
//			if(Target_Velocity<=-10&&donw_flag)Target_Velocity=-10;
//			if((up_flag==0)&&(donw_flag==0))Target_Velocity=0;

//   //=============�ٶ�PI������=======================//	
//		Encoder_Least =(encoder_left+ encoder_right)-Target_Velocity;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
//		Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
//		Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
//		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
//		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
//		if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===�����޷�	
//		Velocity=Encoder*kp+Encoder_Integral*ki;                          //===�ٶȿ���	
//	  return Velocity;
//}
//int turn(int encoder_left,int encoder_right,float gyro)//ת�����
//{
//	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
//	  float Kp=-0.7,Kd=0.7;    
//		int Bias;
//	
//		if((left_flag==0)&&(right_flag==0))Turn_Target=0;
//		if(left_flag)Turn_Target=Turn_Target+3;
//		if(right_flag)Turn_Target=Turn_Target-3;
//		if(Turn_Target>=2000)Turn_Target=2000;
//	if(Turn_Target<=-2000)Turn_Target=-2000;
//		if(left_flag||right_flag)Kp=0;
//		else Kp=-0.7;
//		Bias=gyro-23;
//		Turn=Kp*Bias+Kd*Turn_Target;                
//	  return Turn;
//}
//void Xianfu_Pwm(void)
//{	
//	  int Amplitude=6900;   

//    if(Moto1<-Amplitude) Moto1=-Amplitude;	
//		if(Moto1>Amplitude)  Moto1=Amplitude;	
//	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
//		if(Moto2>Amplitude)  Moto2=Amplitude;		
//	
//}
//int myabs(int a)
//{ 		   
//	  int temp;
//		if(a<0)  temp=-a;  
//	  else temp=a;
//	  return temp;
//}
//void key()
//{
//	u8 tmp=click_N_Double (50);
//	if(tmp==1)LED1_ON;
//	if(tmp==2)LED1_OFF;

//}
//int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right)
//{ 		   
//	 static u16 flag,count0,count1,count2;
//	if(flag==0)                                                                   //��һ��
//	 {
//	      if(myabs(encoder_left)+myabs(encoder_right)<30)                         //����1��С���ӽ���ֹ
//				count0++;
//        else 
//        count0=0;		
//        if(count0>10)				
//		    flag=1,count0=0; 
//	 } 
//	 if(flag==1)                                                                  //����ڶ���
//	 {
//		    if(++count1>200)       count1=0,flag=0;                                 //��ʱ���ٵȴ�2000ms
//	      if(Acceleration>26000&&(Angle>(-20+ZHONGZHI))&&(Angle<(20+ZHONGZHI)))   //����2��С������0�ȸ���������
//		    flag=2; 
//	 } 
//	 if(flag==2)                                                                  //������
//	 {
//		  if(++count2>100)       count2=0,flag=0;                                   //��ʱ���ٵȴ�1000ms
//	    if(myabs(encoder_left+encoder_right)>35)                                 //����3��С������̥��Ϊ�������ﵽ����ת��   
//      {
//				flag=0;                                                                                     
//				return 1;                                                               //��⵽С��������
//			}
//	 }
//	return 0;
//}
///**************************************************************************
//�������ܣ����С���Ƿ񱻷���
//��ڲ�����int
//����  ֵ��unsigned int
//**************************************************************************/
//int Put_Down(float Angle,int encoder_left,int encoder_right)
//{ 		   
//	 static u16 flag,count;	                
//	 if(flag==0)                                               
//	 {
//	      if(Angle>(-10+ZHONGZHI)&&Angle<(10+ZHONGZHI)&&encoder_left==0&&encoder_right==0)         //����1��С������0�ȸ�����
//		    flag=1; 
//	 } 
//	 if(flag==1)                                               
//	 {
//		  if(++count>50)                                          //��ʱ���ٵȴ� 500ms
//		  {
//				count=0;flag=0;
//		  }
//	    if(encoder_left>3&&encoder_right>3&&encoder_left<25&&encoder_right<25)                //����2��С������̥��δ�ϵ��ʱ����Ϊת��  
//      {
//				flag=0;
//				flag=0;
//				return 1;                                             //��⵽С��������
//			}
//	 }
//	return 0;
//}
#include "contral.h"
#define ZHONGZHI -2
extern int encode1;
extern int encode2;
extern float Pitch,Roll; 
extern short gyro[3], accel[3], sensors;
extern u8 up_flag,donw_flag,left_flag,right_flag;
int Moto1,Moto2,Balance_Pwm,Velocity_Pwm,turn_pwm;
u8 Flag_Target=0;

int EXIT_IRQHandler(void)
{		if(EXTI_GetFlagStatus(EXIT_INT_EXTI_LINE  ) != RESET)
		{		 EXTI_ClearITPendingBit(EXIT_INT_EXTI_LINE );

		Read_DMP();                                             //===������̬	



			
		encode1=-Read_Encoder(1);
		encode2=Read_Encoder(2);
		Balance_Pwm =balance(Pitch,gyro[1]); 
		Velocity_Pwm=velocity(encode1,encode2);
		turn_pwm=turn(encode1,encode2,gyro[2]);
			Moto1=Balance_Pwm-Velocity_Pwm+turn_pwm;   
 	  	Moto2=Balance_Pwm-Velocity_Pwm-turn_pwm;
			//if(Pick_Up(accel[2],Pitch,encode1,encode2))//===����Ƿ�С��������
			//GPIO_ResetBits(GPIOA,GPIO_Pin_15);                                                      //===���������͹رյ��
			if(Put_Down(Pitch,encode1,encode2))              //===����Ƿ�С��������
			GPIO_SetBits(GPIOA,GPIO_Pin_15); 
			Xianfu_Pwm();
			Set_Pwm(Moto1,Moto2);
			key();
		}

        return 0;
}
int Read_Encoder(u8 TIMX)
{
     int Encoder_TIM;    
    switch(TIMX)
			{		 case 1:Encoder_TIM= (short)TIM1 -> CNT;  TIM1 -> CNT=0;break;
         case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
         case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;    
         case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;    
         default:  Encoder_TIM=0;
     }
     return Encoder_TIM;
 }
void Set_Pwm(int moto1,int moto2)
{
    	if(moto2<0)	
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_4);
				GPIO_ResetBits(GPIOB,GPIO_Pin_3);
			}
			else
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_3);
				GPIO_ResetBits(GPIOB,GPIO_Pin_4);
			} 	         
			TIM4->CCR4=myabs(moto2);
    	if(moto1<0)	
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_12);
				GPIO_ResetBits( GPIOA,GPIO_Pin_11);
			}
			else
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_11);
				GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			} 	         
			TIM4->CCR3=myabs(moto1);
}
int balance(float Angle,float Gyro)
{  
   float Bias,kp=-400,kd=-0.8;
	 int balance;
	 Bias=Angle-ZHONGZHI;       //===���ƽ��ĽǶ���ֵ �ͻ�е���
	 balance=kp*Bias+Gyro*kd;   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	 return balance;
}
int velocity(int encoder_left,int encoder_right)
{  
     static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Encoder_Integral,Target_Velocity;
	  float kp=450;
		float ki=kp/200;
			if(up_flag)Target_Velocity++;
			if(donw_flag)Target_Velocity--;
			if(Target_Velocity>=3&&up_flag)Target_Velocity=3;
			if(Target_Velocity<=-3&&donw_flag)Target_Velocity=-3;
			if((up_flag==0)&&(donw_flag==0))Target_Velocity=0;

   //=============�ٶ�PI������=======================//	
		Encoder_Least =(encoder_left+ encoder_right)-Target_Velocity;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
		Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
		if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===�����޷�	
		Velocity=Encoder*kp+Encoder_Integral*ki;                          //===�ٶȿ���	
	  return Velocity;
}
int turn(int encoder_left,int encoder_right,float gyro)//ת�����
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Kp=-0.7,Kd=0.7;    
		int Bias;
	
		if((left_flag==0)&&(right_flag==0))Turn_Target=0;
		if(left_flag)Turn_Target=Turn_Target+3;
		if(right_flag)Turn_Target=Turn_Target-3;
		if(Turn_Target>=2000)Turn_Target=2000;
	if(Turn_Target<=-2000)Turn_Target=-2000;
		if(left_flag||right_flag)Kp=0;
		else Kp=-0.7;
		Bias=gyro-23;
		Turn=Kp*Bias+Kd*Turn_Target;                
	  return Turn;
}
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;   

    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
void key()
{
	u8 tmp=click_N_Double (50);
	if(tmp==1)LED1_ON;
	if(tmp==2)LED1_OFF;

}
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count0,count1,count2;
	if(flag==0)                                                                   //��һ��
	 {
	      if(myabs(encoder_left)+myabs(encoder_right)<30)                         //����1��С���ӽ���ֹ
				count0++;
        else 
        count0=0;		
        if(count0>10)				
		    flag=1,count0=0; 
	 } 
	 if(flag==1)                                                                  //����ڶ���
	 {
		    if(++count1>200)       count1=0,flag=0;                                 //��ʱ���ٵȴ�2000ms
	      if(Acceleration>26000&&(Angle>(-20+ZHONGZHI))&&(Angle<(20+ZHONGZHI)))   //����2��С������0�ȸ���������
		    flag=2; 
	 } 
	 if(flag==2)                                                                  //������
	 {
		  if(++count2>100)       count2=0,flag=0;                                   //��ʱ���ٵȴ�1000ms
	    if(myabs(encoder_left+encoder_right)>35)                                 //����3��С������̥��Ϊ�������ﵽ����ת��   
      {
				flag=0;                                                                                     
				return 1;                                                               //��⵽С��������
			}
	 }
	return 0;
}
/**************************************************************************
�������ܣ����С���Ƿ񱻷���
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int Put_Down(float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count;	                
	 if(flag==0)                                               
	 {
	      if(Angle>(-10+ZHONGZHI)&&Angle<(10+ZHONGZHI)&&encoder_left==0&&encoder_right==0)         //����1��С������0�ȸ�����
		    flag=1; 
	 } 
	 if(flag==1)                                               
	 {
		  if(++count>50)                                          //��ʱ���ٵȴ� 500ms
		  {
				count=0;flag=0;
		  }
	    if(encoder_left>3&&encoder_right>3&&encoder_left<25&&encoder_right<25)                //����2��С������̥��δ�ϵ��ʱ����Ϊת��  
      {
				flag=0;
				flag=0;
				return 1;                                             //��⵽С��������
			}
	 }
	return 0;
}
