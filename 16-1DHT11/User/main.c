#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "Serial.h"



extern unsigned int rec_data[4];


int main(void)
{
   
	OLED_Init();  //初始化OLED
//	Serial_Init();   //初始化串口
	
//	OLED_ShowCN(2,1,19);
//	OLED_ShowCN(2,2,20);
//	OLED_ShowCN(1,3,21);
//	OLED_ShowCN(1,4,19);
//	OLED_ShowCN(1,5,20);
//	OLED_ShowCN(1,6,21);
	
	
	OLED_ShowCN(1,1,6);
	OLED_ShowCN(1,2,7);
	OLED_ShowChar(1,6,':');
	
	
	OLED_ShowCN(1,5,10);
	
	
	OLED_ShowCN(3,1,8);
	OLED_ShowCN(3,2,9);
	OLED_ShowChar(3,6,':');
	
	OLED_ShowCN(3,5,11);
	OLED_ShowCN(3,6,12);
	
	while(1)  
	{
		
		Delay_s(1);
		DHT11_REC_Data(); //接收温度和湿度的数据
		
	    OLED_ShowNum(1,7,rec_data[2],2);
		OLED_ShowNum(1,10,rec_data[3],1);
		OLED_ShowNum(3,7,rec_data[0],2);
		OLED_ShowNum(3,10,rec_data[1],2);
     
//		Serial_Printf("温度：%d\r\n",rec_data[2]);
//		Serial_Printf("湿度：%d\r\n",rec_data[0]);
//		Serial_Printf("\r\n\n");
	}
}

