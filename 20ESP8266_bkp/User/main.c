#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{
   
	OLED_Init();  //初始化OLED

	OLED_ShowString(1,1,"RxData:");
	Serial_Init(); //初始化串口
	

	while(1)  
	{
		//采用查询的方法接收数据
//		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
//		{
//			RxData = USART_ReceiveData(USART1);
//			OLED_ShowChar(1,1,RxData);
//		}
		
		//采用中断的方法接收数据
		if(Serial_GetRxFlag()==1)
		{
			RxData  =  Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
		}
	}
}

