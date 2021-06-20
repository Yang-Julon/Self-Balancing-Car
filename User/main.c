/******************** (C) COPYRIGHT (2015)BST BALANCECAR **************************
 * �ļ���  ��main.c
**********************************************************************************/
#include "mpu6050.h"
#include "i2c_mpu6050.h"
#include "motor.h"
#include "upstandingcar.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "i2c.h"
#include "timer.h"
#include "UltrasonicWave.h"

float gyz;
int acc;
int acc1;

/*Э�����*/
//extern u8 newLineReceived = 0;

/*
 * ��������main
 * ����  ��������
 */
int main(void)
{	
  SystemInit();                   //=====ϵͳ��ʼ��
	Timerx_Init(5000,7199);				   //��ʱ��TIM1
	UltrasonicWave_Configuration(); 	   //��������ʼ������ IO�ڼ��ж�����			    

	USART1_Config();						//����1��ʼ�� ��λ��
	USART3_Config();						//����3��ʼ�� ������USART3������ͬIO��
	
	TIM2_PWM_Init();					   //PWM�����ʼ��
	MOTOR_GPIO_Config();				  //���IO�ڳ�ʼ��
  LED_GPIO_Config();
	
  TIM3_Encoder_Init();                       //��������ȡ������ PA6 7 
  TIM4_Encoder_Init();                       //��������ȡ������ PB6 7	
	/**********************  DMP  **************************************/
	i2cInit();							   //IIC��ʼ�� ���ڹҿ��������ϵ��豸ʹ��
	delay_nms(10);						   //��ʱ10ms
	MPU6050_Init();						   //MPU6050 DMP�����ǳ�ʼ��
	
	SysTick_Init();						  //SysTick������ʼ��	
	CarUpstandInit();					  //С��ֱ��������ʼ��
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;	 //ʹ�����㷨ʱ��

	while (1)
	{
		MPU6050_Pose();						 //��ȡMPU6050�Ƕ�״̬
		
		/**********************  ���Գ��� ����Ҫʱע�ͼ��� **************************************/
// 		gy0=gyro[0];
// 		UltrasonicWave_StartMeasure();	   //���ó��������ͳ��� ��Trig�� <10us �ߵ�ƽ		 
// 		chaoshengbo();			       //���㳬����������
//    printf("%d",ucBluetoothValue);
//		printf("\t");
//		printf("%f",BST_fSpeedControlOutNew);
//		printf("\t");
//		printf("%f",BST_fCarAngle);
//		printf("\t");
// 		printf("%f",BST_fLeftMotorOut);
//		printf("\t");
//		printf("\n");
		
		if (newLineReceived){
			ProtocolCpyData();
			Protocol();
		}
		/*ͨ��״̬����С��*/
		CarStateOut();
		SendAutoUp(); 
	 }
 								    
}
