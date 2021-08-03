#include "spi1.h"

void SPI1_Init_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//SCLK��MOSI��GPIO����
	//����ģʽ�����Բ�������MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//CSƬѡ����
	//SPI��Ƭѡ�źűȽϼ򵥣����Թٷ�Ҳ�Ƽ����ⲿ�������Ƭѡ������ʹ��Ӳ������
	//����ѡ���GPIOA_4,Ҳ����ѡ������GPIO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;//����˫��ֻ����
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//���ݳ��� 8 λ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //ʱ��SCLK����ʱΪ�ߵ�ƽ
	//ʱ�ӿ���ʱΪ�ߵ�ƽ�������Ϊ�͵�ƽ����
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //SPI_CPHA = SPI_CPHA_2Edge��ʾ�ڶ������ؿ�ʼ����
	//�������ʾ�����ؿ�ʼ�������½��ش���
	//SPI_CPOL��SPI_CPHA�����ñ���������֧�ֵĴ��䷽ʽһ��
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//�ⲿ���Ƭѡ//��˼���ǲ�ͨ��Ӳ��Ƭѡ����������ѡ��GPIO��
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//�� 1 λΪ��λ
	SPI_Init(SPI1,&SPI_InitStructure); //����SPI1
	SPI_Cmd(SPI1,ENABLE);// ʹ��SPI1
}





