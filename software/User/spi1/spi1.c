#include "spi1.h"

void SPI1_Init_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//SCLK与MOSI的GPIO配置
	//单线模式，所以不用配置MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//CS片选配置
	//SPI的片选信号比较简单，所以官方也推荐由外部软件控制片选而不是使用硬件配置
	//这里选择的GPIOA_4,也可以选择任意GPIO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;//单线双向只发送
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//主机模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//数据长度 8 位
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //时钟SCLK空闲时为高电平
	//时钟空闲时为高电平，则采样为低电平触发
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //SPI_CPHA = SPI_CPHA_2Edge表示第二个边沿开始采样
	//则总体表示上升沿开始采样，下降沿触发
	//SPI_CPOL与SPI_CPHA的设置必须与外设支持的传输方式一致
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//外部软件片选//意思就是不通过硬件片选，可以任意选择GPIO口
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//第 1 位为高位
	SPI_Init(SPI1,&SPI_InitStructure); //设置SPI1
	SPI_Cmd(SPI1,ENABLE);// 使能SPI1
}





