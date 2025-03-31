#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "usart.h" 
#include "esp8266.h"
#include "onenet.h"


#include <string.h>
#include <stdio.h>

int main(void)
{
   
	unsigned short timeCount = 0;	//发送间隔变量
	unsigned char *dataPtr = NULL;	
	 
	
	Usart2_Init(115200);     //串口2初始化为115200
	
	ESP8266_Init();	 
 
	while(OneNet_DevLink())			//接入OneNET
	Delay_ms(500);	

	while(1)
	{	    	    
		
		//DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值
		//delay_ms(100);
		
		if(++timeCount >= 50)									//发送间隔5s
				{		
//					data_len=MqttOnenet_Savedata(send_jason,temperature, humidity);
					OneNet_SendData();									//发送数据
					
					timeCount = 0;
					ESP8266_Clear();
				}				
			  dataPtr = ESP8266_GetIPD(0);
			  if(dataPtr != NULL)
				OneNet_RevPro(dataPtr);

	}
}

