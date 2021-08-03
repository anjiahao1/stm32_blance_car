#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "math.h"
#define q30  1073741824.0f
#define DEFAULT_MPU_HZ  (200)
short gyro[3], accel[3], sensors;
float Pitch,Roll; 
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}


static  unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
		
    }
}
void i2c_init(void)
{
		GPIO_InitTypeDef G;
		I2C_InitTypeDef I;
		MPU6050_I2C_GPIO_APBxClock_FUN(MPU6050_I2C_GPIO_CLK,ENABLE);
		MPU6050_I2C_APBxClock_FUN(MPU6050_I2C_CLK,ENABLE);
		G.GPIO_Mode=GPIO_Mode_AF_OD;
		G.GPIO_Pin=MPU6050_I2C_SDA_PIN;
		G.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(MPU6050_I2C_SDA_PORT,&G);
		G.GPIO_Mode=GPIO_Mode_AF_OD;
		G.GPIO_Pin=MPU6050_I2C_SCL_PIN;
		GPIO_Init(MPU6050_I2C_SCL_PORT,&G);
		I.I2C_ClockSpeed=I2C_Speed;
		I.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
		I.I2C_DutyCycle=I2C_DutyCycle_16_9;
		I.I2C_Mode=I2C_Mode_I2C;
		I.I2C_Ack=I2C_Ack_Enable;
		I.I2C_OwnAddress1=I2Cx_OWN_ADDRESS7;
		I2C_Init(MPU6050_I2Cx,&I);
		I2C_Cmd(MPU6050_I2Cx,ENABLE);
}
int mpu6050_Write(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{		int i;
		I2C_GenerateSTART(MPU6050_I2Cx,ENABLE);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
		I2C_Send7bitAddress(MPU6050_I2Cx,addr<<1,I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
		I2C_SendData(MPU6050_I2Cx,reg);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	for(i=0;i<len;i++){
		I2C_SendData(MPU6050_I2Cx,buf[i]);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
		I2C_GenerateSTOP(MPU6050_I2Cx,ENABLE);
	return 0;
}
int mpu6050_read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
		while(I2C_GetFlagStatus(MPU6050_I2Cx,I2C_FLAG_BUSY));
	I2C_GenerateSTART(MPU6050_I2Cx,ENABLE);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
		I2C_Send7bitAddress(MPU6050_I2Cx,addr<<1, I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
		I2C_SendData(MPU6050_I2Cx,reg);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	
		I2C_GenerateSTART(MPU6050_I2Cx,ENABLE);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
		I2C_Send7bitAddress(MPU6050_I2Cx,addr<<1, I2C_Direction_Receiver);
		while(!I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		while(len)
		{
			if(len==1)
			{
				 I2C_AcknowledgeConfig(MPU6050_I2Cx, DISABLE);
				I2C_GenerateSTOP(MPU6050_I2Cx, ENABLE);
			}
			while(I2C_CheckEvent(MPU6050_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED)==0);
			*buf=I2C_ReceiveData(MPU6050_I2Cx);
			buf++;
			len--;
		}
		I2C_AcknowledgeConfig(MPU6050_I2Cx, ENABLE);
		return 0;
}

void mpu6050_init(void)
{
	u8 a;
	a=0x00;	
	mpu6050_Write(0x68,MPU6050_RA_PWR_MGMT_1,1,&a);
	a=0x04;
	mpu6050_Write(0x68,MPU6050_RA_SMPLRT_DIV,1,&a);
	a=0x06;
	mpu6050_Write(0x68,MPU6050_RA_CONFIG,1,&a);
	a=0x01;
	mpu6050_Write(0x68,MPU6050_RA_ACCEL_CONFIG,1,&a);
	a=0x18;
	mpu6050_Write(0x68,MPU6050_RA_GYRO_CONFIG,1,&a);
		a=0x1C;
	mpu6050_Write(0x68,MPU6050_RA_INT_PIN_CFG,1,&a);
		a=0x01;
	mpu6050_Write(0x68,MPU6050_RA_INT_ENABLE ,1,&a);
	
}
u8 DMP_Init(void)
{ 
   u8 temp[1]={0};
	 u8 res;
   mpu6050_read(0x68,0x75,1,temp);

	if(temp[0]!=0x68)NVIC_SystemReset();
	 res=mpu_init();
if(!res)	//初始化MPU6050
	{	__disable_irq();
		res=mpu_set_sensors(INV_XYZ_GYRO|INV_XYZ_ACCEL);//设置所需要的传感器
		if(res)return 1; 
		res=mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);//设置FIFO
		if(res)return 2; 
		res=mpu_set_sample_rate(DEFAULT_MPU_HZ);	//设置采样率
		if(res)return 3; 
		
		res=dmp_load_motion_driver_firmware();		//加载dmp固件
		if(res)return 4; 
		res=dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));//设置陀螺仪方向
		if(res)return 5; 
		res=dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT|DMP_FEATURE_TAP|	//设置dmp功能
		    DMP_FEATURE_ANDROID_ORIENT|DMP_FEATURE_SEND_RAW_ACCEL|DMP_FEATURE_SEND_CAL_GYRO|
		    DMP_FEATURE_GYRO_CAL);
		if(res)return 6; 
		res=dmp_set_fifo_rate(DEFAULT_MPU_HZ);	//设置DMP输出速率(最大不超过200Hz)
		if(res)return 7; 
		//delay_us(2);
		run_self_test();		//自检
		if(res)return 8;    
		res=mpu_set_dmp_state(1);	//使能DMP
		if(res)return 9;
		__enable_irq();
	}
	return 0;
}
void Read_DMP(void)
{	
	  unsigned long sensor_timestamp;
		unsigned char more;
		long quat[4];

				dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);		
				if (sensors & INV_WXYZ_QUAT )
				{    
					 q0=quat[0] / q30;
					 q1=quat[1] / q30;
					 q2=quat[2] / q30;
					 q3=quat[3] / q30;
					 Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; 	
					 Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
				}

}
