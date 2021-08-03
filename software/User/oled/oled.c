#include "oled.h"
#include "oledfont.h" 
#include "bmp.h"

void OLED_Init_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  //DC�������RST��λ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//��OLEDд���ֽں���
//����1����д����ֽ�
//����2������/���ݣ���0���������1�����ݣ�
void OLED_W_Byte(u8 dat,u8 cd)
{
	if(cd)
		OLED_DC_Set();//1������
	else
		OLED_DC_Clr();//0������
	OLED_CS_Clr();//CSƬѡ����ѡ��Ƭѡ����Ϊֻ��һƬ������Ҳ����ֱ�ӽӵ�
	SPI_I2S_SendData(SPI1, dat);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET); //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	OLED_DC_Set();
	OLED_CS_Set();
}

//��������
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_W_Byte(0xb0+i,cmd);//����ҳ���ַ��0~7��
		OLED_W_Byte(0x00,cmd);//������ʾλ��1�е͵�ַ
		OLED_W_Byte(0x10,cmd);//������ʾλ��1�иߵ�ַ
		for(n=0;n<128;n++)
		{
			OLED_W_Byte(0,data);
		}
	}
}

//���õ�ǰ����
void OLED_Set_Pos(unsigned char x,unsigned char y)
{
	OLED_W_Byte(0xb0+y,cmd);
	OLED_W_Byte(((x&0xf0)>>4)|0x10,cmd);
	OLED_W_Byte((x&0x0f)|0x01,cmd);
}

//���� OLED��ʾ
void OLED_Display_On(void)
{
	OLED_W_Byte(0X8D,cmd); //SET DCDC ����
	OLED_W_Byte(0X14,cmd); //DCDC ON
	OLED_W_Byte(0XAF,cmd); //Display ON
}

//�ر� OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_W_Byte(0X8D,cmd); //SET DCDC ����
	OLED_W_Byte(0X10,cmd); //DCDC OFF
	OLED_W_Byte(0XAE,cmd); //Display OFF
}

//��ʼ��OLED����
void OLED_Init(void)
{
	OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(200);
	OLED_RST_Set(); 
					  
	OLED_W_Byte(0xAE,cmd);//--turn off oled panel
	OLED_W_Byte(0x00,cmd);//---set low column address
	OLED_W_Byte(0x10,cmd);//---set high column address
	OLED_W_Byte(0x40,cmd);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_W_Byte(0x81,cmd);//--set contrast control register
	OLED_W_Byte(0xCF,cmd); // Set SEG Output Current Brightness
	OLED_W_Byte(0xA1,cmd);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_W_Byte(0xC8,cmd);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_W_Byte(0xA6,cmd);//--set normal display
	OLED_W_Byte(0xA8,cmd);//--set multiplex ratio(1 to 64)
	OLED_W_Byte(0x3f,cmd);//--1/64 duty
	OLED_W_Byte(0xD3,cmd);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_W_Byte(0x00,cmd);//-not offset
	OLED_W_Byte(0xd5,cmd);//--set display clock divide ratio/oscillator frequency
	OLED_W_Byte(0x80,cmd);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_W_Byte(0xD9,cmd);//--set pre-charge period
	OLED_W_Byte(0xF1,cmd);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_W_Byte(0xDA,cmd);//--set com pins hardware configuration
	OLED_W_Byte(0x12,cmd);
	OLED_W_Byte(0xDB,cmd);//--set vcomh
	OLED_W_Byte(0x40,cmd);//Set VCOM Deselect Level
	OLED_W_Byte(0x20,cmd);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_W_Byte(0x02,cmd);//
	OLED_W_Byte(0x8D,cmd);//--set Charge Pump enable/disable
	OLED_W_Byte(0x14,cmd);//--set(0x10) disable
	OLED_W_Byte(0xA4,cmd);// Disable Entire Display On (0xa4/0xa5)
	OLED_W_Byte(0xA6,cmd);// Disable Inverse Display On (0xa6/a7) 
	OLED_W_Byte(0xAF,cmd);//--turn on oled panel
	
	OLED_W_Byte(0xAF,cmd); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}

//��ָ��λ����ʾ 1 ���ַ������������ַ�
//x:0~127;y:0~63
//chr:��Ҫ��ʾ���ַ�
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_W_Byte(F8X16[c*16+i],data);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_W_Byte(F8X16[c*16+i+8],data);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_W_Byte(F6x8[c][i],data);
				
			}
}

//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

//��ʾ����
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_W_Byte(Hzk[2*no][t],data);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_W_Byte(Hzk[2*no+1][t],data);
				adder+=1;
      }					
}

//������������ʾ��ʾBMPͼƬ
//128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_W_Byte(BMP[j++],data);	    	
	    }
	}
}





