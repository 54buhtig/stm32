#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "esp8266.h"
#include "LED.h"
#include "onenet.h"
#include "stdio.h"
#include "Serial.h"

int main(void)
 {	

	unsigned char *dataPtr = NULL;
	 
	
	Serial_Init();
//	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();			     //LED端口初始化

	OLED_Init();			//初始化OLED   
	OLED_Clear();
	Serial_Printf("OK\r\n");	 
	 

	 

	 
	ESP8266_Init();					//初始化ESP8266
	 
	while(OneNet_DevLink())			//接入OneNET
	Delay_ms(500);
	
	while(1) 
	{		
		
				

		dataPtr = ESP8266_GetIPD(0);//获取平台返回的数据
		if(dataPtr != NULL)//如果返回数据不为空
			OneNet_RevPro(dataPtr);//平台返回数据检测
		
		Delay_ms(10);
		
	}

}


