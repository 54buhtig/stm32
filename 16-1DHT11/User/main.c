#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"

extern unsigned int rec_data[4];


int main(void)
{
   
	OLED_Init();  //初始化OLED

	while(1)  
	{
		Delay_s(1);
		DHT11_REC_Data(); //接收温度和湿度的数据
		
	    OLED_ShowNum(1,7,rec_data[2],2);
		OLED_ShowNum(1,10,rec_data[3],1);
		OLED_ShowNum(3,7,rec_data[0],2);
		OLED_ShowNum(3,10,rec_data[1],2);
     
	}
}

