#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Serial.h"
#include "ESP8266.h"

 
uint8_t flag;
 
int main(void)
{ 
	
	SystemInit();//����ϵͳʱ��Ϊ72M	
	LED_Init();
	LED1_On();
	Serial_Init();
	
	ESP8266_Init ();   //��ʼ��WiFiģ��ʹ�õĽӿں����裨ʹ�ô���2��
	ESP8266_StaTcpClient ();//WiFiģ������
	
	printf("Start \n");
	Delay_ms(1000);
	
 
	while (1)
	{
		switch(flag)
		{
			case 'a': LED1_On();break;//����
			
			case 'c': LED2_Off();break;//�ص�
		}	
	}
}
