#ifndef __CONTRAL_H
#define __CONTRAL_H

#include "stm32f10x.h"
#include "bsp_exit.h"
#include "mpu6050.h"
#include "encode.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_esp8266.h"
void Set_Pwm(int moto1,int moto2);
int balance(float Angle,float Gyro);
int velocity(int encoder_left,int encoder_right);
void Xianfu_Pwm(void);
int myabs(int a);
void key();
int turn(int encoder_left,int encoder_right,float gyro);
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right);
int Put_Down(float Angle,int encoder_left,int encoder_right);

#endif
