#include "stm32f10x.h"
#include "led.h"
#include "Serial.h"
#include "delay.h"
#include "oled.h"
#include "mq135.h"
#include "AD.h"
 
/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	MQ-135��������������ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.8.23
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�mq135.h							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 
**********************BEGIN***********************/
 
u16 value;
u8 buff[30];//������ʾ��������
float ppm;
 
int main(void)
{ 
	
	SystemInit();//����ϵͳʱ��Ϊ72M	
//	delay_init(72);
	LED_Init();
//	LED_On();
	MQ135_Init();
	Serial_Init();//���ڳ�ʼ��
	
	OLED_Init();
	printf("Start \n");
	Delay_ms(1000);
	
	OLED_Clear();
	//��ʾ����������:��
	OLED_ShowCN(1,1,13);
	OLED_ShowCN(1,2,14);
	OLED_ShowCN(1,3,15);
	OLED_ShowCN(1,4,16);

	
	
 
  while (1)
  {
//		LED_Toggle();
		value = MQ135_GetData();  
		
		printf("��������: %d\r\n",value);
		OLED_ShowNum(1,13,value,4);
		
		ppm = MQ135_GetData_PPM();
		sprintf((char*)buff, "%.2fppm    ",ppm);
		OLED_ShowString(2,2,(char*)buff);
		
//		if(value)
//		{
//			OLED_ShowChinese(48,32,4,16,1);	//��
//			OLED_ShowChinese(64,32,6,16,1);	//��
//		}
//		else
//		{
//			OLED_ShowChinese(48,32,5,16,1);	//��
//			OLED_ShowChinese(64,32,6,16,1);	//��
//		}
 
		Delay_ms(200);
 
  }
	
}

