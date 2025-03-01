#include "stm32f10x.h"
#include "led.h"
#include "Serial.h"
#include "delay.h"
#include "oled.h"
#include "mq135.h"
#include "AD.h"
 
/*****************辰哥单片机设计******************
											STM32
 * 项目			:	MQ-135空气质量传感器实验                     
 * 版本			: V1.0
 * 日期			: 2024.8.23
 * MCU			:	STM32F103C8T6
 * 接口			:	参看mq135.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 
**********************BEGIN***********************/
 
u16 value;
u8 buff[30];//参数显示缓存数组
float ppm;
 
int main(void)
{ 
	
	SystemInit();//配置系统时钟为72M	
//	delay_init(72);
	LED_Init();
//	LED_On();
	MQ135_Init();
	Serial_Init();//串口初始化
	
	OLED_Init();
	printf("Start \n");
	Delay_ms(1000);
	
	OLED_Clear();
	//显示“空气质量:”
	OLED_ShowCN(1,1,13);
	OLED_ShowCN(1,2,14);
	OLED_ShowCN(1,3,15);
	OLED_ShowCN(1,4,16);

	
	
 
  while (1)
  {
//		LED_Toggle();
		value = MQ135_GetData();  
		
		printf("空气质量: %d\r\n",value);
		OLED_ShowNum(1,13,value,4);
		
		ppm = MQ135_GetData_PPM();
		sprintf((char*)buff, "%.2fppm    ",ppm);
		OLED_ShowString(2,2,(char*)buff);
		
//		if(value)
//		{
//			OLED_ShowChinese(48,32,4,16,1);	//异
//			OLED_ShowChinese(64,32,6,16,1);	//常
//		}
//		else
//		{
//			OLED_ShowChinese(48,32,5,16,1);	//正
//			OLED_ShowChinese(64,32,6,16,1);	//常
//		}
 
		Delay_ms(200);
 
  }
	
}

