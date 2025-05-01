#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "Serial.h"


extern unsigned int rec_data[4];


int main(void)
{
	u8 t =0;
	u8 l = 0;
	
	//硬件初始化
	LED_Init();   //LED初始化
	OLED_Init();  //OLED初始化
	LED1_On();
	Serial_Init();

	

	Delay_ms(2500);
	LED2_On();
	Delay_ms(2500);
	LED1_Off();
	Delay_ms(2500);
	LED2_Off();
	Delay_ms(2500);
	

	Serial_Printf("我是我自己！\r\n");
	OLED_ShowCN(1,1,0);//温
	OLED_ShowCN(1,2,5);//度
	OLED_ShowChar(1,5,':');
	OLED_ShowChar(1,8,'.');//小数点
	OLED_ShowCN(1,6,10);//℃
	OLED_ShowCN(2,1,1);//湿
	OLED_ShowCN(2,2,5);//度
	OLED_ShowChar(2,5,':');
	OLED_ShowChar(2,8,'.');//小数点
	OLED_ShowString(2,11,"%RH");//%RH
	OLED_ShowCN(3,1,2);//光
	OLED_ShowCN(3,2,3);//照
	OLED_ShowCN(3,3,4);//强
	OLED_ShowCN(3,4,5);//度
	OLED_ShowChar(3,9,':');
	OLED_ShowCN(4,1,6);//空
	OLED_ShowCN(4,2,7);//气
	OLED_ShowCN(4,3,8);//质
	OLED_ShowCN(4,4,9);//量
	OLED_ShowChar(4,9,':');
	

	OLED_ShowFNum(3,10,4.5);
	while(1)
	{
		if(t%10==0)
		{
			l++;
			if(l%10==0)
			{
				DHT11_REC_Data(); //接收温度和湿度的数据
			}
		}
		Delay_ms(10);
		t++;
		OLED_ShowNum(1,6,rec_data[2],2);
		OLED_ShowNum(1,9,rec_data[3],1);
		OLED_ShowNum(2,6,rec_data[0],2);
		OLED_ShowNum(2,9,rec_data[1],2);

	}
}



