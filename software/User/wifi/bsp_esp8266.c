#include "bsp_esp8266.h"
#include "string.h"
static void ESP8266_USART_NVIC_Configuration ( void );

	static void ESP8266_USART_Config ( void );
	void wifi_printf(char *a);
	u8 up_flag=0,donw_flag=0,left_flag=0,right_flag=0;
void ESP8266_init(void)
{

	ESP8266_USART_Config ();
	ESP8266_USART_NVIC_Configuration ();
	wifi_printf("AT+CIPMUX=1\r\n");
	delay_ms(500);
	wifi_printf("AT+CIPSERVER=1,8899\r\n");
	delay_ms(500);
}
 void ESP8266_GPIO_Config ( void )
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* 配置 CH_PD 引脚*/
	macESP8266_CH_PD_APBxClock_FUN ( macESP8266_CH_PD_CLK, ENABLE ); 
											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_CH_PD_PIN;	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	GPIO_Init ( macESP8266_CH_PD_PORT, & GPIO_InitStructure );	 
GPIO_SetBits(macESP8266_CH_PD_PORT,macESP8266_CH_PD_PIN);
	
	/* 配置 RST 引脚*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_RST_CLK, ENABLE ); 
											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_RST_PIN;	

	GPIO_Init ( macESP8266_RST_PORT, & GPIO_InitStructure );	 
GPIO_SetBits(macESP8266_RST_PORT,macESP8266_RST_PIN);

}
static void ESP8266_USART_Config ( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	
	/* config USART clock */
	macESP8266_USART_APBxClock_FUN ( macESP8266_USART_CLK, ENABLE );
	macESP8266_USART_GPIO_APBxClock_FUN ( macESP8266_USART_GPIO_CLK, ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/* USART GPIO config */
	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  macESP8266_USART_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(macESP8266_USART_TX_PORT, &GPIO_InitStructure);  
  
	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = macESP8266_USART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	GPIO_Init(macESP8266_USART_RX_PORT, &GPIO_InitStructure);
	ESP8266_USART_NVIC_Configuration ();
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = macESP8266_USART_BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(macESP8266_USARTx, &USART_InitStructure);
	

USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, ENABLE ); //使能串口接收中断 	
	
	USART_Cmd(macESP8266_USARTx, ENABLE);
	
	
}
static void ESP8266_USART_NVIC_Configuration ( void )
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_InitStructure.NVIC_IRQChannel = macESP8266_USART_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
void wifi_printf(char *a)
{
	while(*a!='\0')
	{	
		
		USART_SendData(USART1,*a);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		a++;
		
	}
}


char rcv[1000];

void macESP8266_USART_INT_FUN (void)
{
//		uint8_t ucCh;
//	
//	
//	if ( USART_GetITStatus ( macESP8266_USARTx, USART_IT_RXNE ) != RESET )
//	{
//		ucCh  = USART_ReceiveData( macESP8266_USARTx );
//		LED1_TOGGLE	;
//		if(ucCh==0x01){up_flag=0;donw_flag=0;left_flag=0;right_flag=0;}
//		if(ucCh==0x02){up_flag=1;donw_flag=0;left_flag=0;right_flag=0;}
//		if(ucCh==0x03){up_flag=0;donw_flag=1;left_flag=0;right_flag=0;}
//		if(ucCh==0x04){up_flag=0;donw_flag=0;left_flag=1;right_flag=0;}
//		if(ucCh==0x05){up_flag=0;donw_flag=0;left_flag=0;right_flag=1;}
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//	 	 
	uint8_t *ucCh;
	static u8 i=0;
	
	if ( USART_GetITStatus ( macESP8266_USARTx, USART_IT_RXNE ) != RESET )
	{
		 rcv[i] = USART_ReceiveData( macESP8266_USARTx );
		if(rcv[i++]=='\n')
		{		i=0;
			if(ucCh=strstr(rcv,"CMD_")){
						LED1_TOGGLE	;
		if(*(ucCh+4)=='1'){up_flag=0;donw_flag=0;left_flag=0;right_flag=0;}
		if(*(ucCh+4)=='2'){up_flag=1;donw_flag=0;left_flag=0;right_flag=0;}
		if(*(ucCh+4)=='3'){up_flag=0;donw_flag=1;left_flag=0;right_flag=0;}
		if(*(ucCh+4)=='4'){up_flag=0;donw_flag=0;left_flag=1;right_flag=0;}
		if(*(ucCh+4)=='5'){up_flag=0;donw_flag=0;left_flag=0;right_flag=1;}
	}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
	 	 

}