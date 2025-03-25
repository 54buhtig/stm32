#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Serial.h"
#include "ESP8266.h"

 
uint8_t flag;
 
int main(void)
{ 
	
	SystemInit();//配置系统时钟为72M	
	LED_Init();
	LED1_On();
	Serial_Init();
	
	ESP8266_Init ();   //初始化WiFi模块使用的接口和外设（使用串口2）
	ESP8266_StaTcpClient ();//WiFi模块设置
	
	printf("Start \n");
	Delay_ms(1000);
	
 
	while (1)
	{
		switch(flag)
		{
			case 'a': LED1_On();break;//开灯
			
			case 'c': LED2_Off();break;//关灯
		}	
	}
}
