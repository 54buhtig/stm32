#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"
#include <string.h>


int main(void)
{
   
	OLED_Init();  //初始化OLED
	LED_Init();
	KEY_Init();
	Serial_Init(); //初始化串口
	
	OLED_ShowString(1,1,"TxPacket");
	OLED_ShowString(3,1,"RxPacket");
	



	while(1)  
	{
		if(Serial_RxFlag ==1)
		{
			OLED_ShowString(4,1,"                ");
			OLED_ShowString(4,1,Serial_RxPacket);
			
			if(strcmp(Serial_RxPacket,"Family")==0)
			{
				LED2_On();
				Serial_SendString("Family_Nice\r\n");
				OLED_ShowString(2,1,"                ");
			    OLED_ShowString(2,1,"Family_Nice\r\n");
			}
			else if(strcmp(Serial_RxPacket,"LED_OFF")==0)
			{
				LED2_Off();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2,1,"                ");
			    OLED_ShowString(2,1,"LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2,1,"                ");
			    OLED_ShowString(2,1,"ERROR_COMMAND");
			}
			Serial_RxFlag = 0;   //等待数据包接收后将标志位清零

		}

		
		
		//数据包接收速度慢可能会造成数据错位，利用RxFlag
	}
}

