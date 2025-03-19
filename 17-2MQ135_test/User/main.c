#include "stm32f10x.h"
#include "led.h"
#include "Serial.h"
#include "delay.h"
#include "OLED.h"
#include "mq135.h"
#include "AD.h"
 

 
u16 value;
u8 buff[30];//参数显示缓存数组
float ppm;
 
int main(void)
{ 
	OLED_Init();
	SystemInit();//配置系统时钟为72M	
//	delay_init(72);
//	LED_Init();
//	LED_On();
	MQ135_Init();
//	Serial_Init();//串口初始化
	
//	OLED_Init();
//	printf("Start \n");
//	Delay_ms(1000);
	
//	OLED_Clear();
	//显示“空气质量:”
			OLED_ShowCN(1,1,0);//温
			OLED_ShowCN(1,2,5);//度
			OLED_ShowChar(1,5,':');
			OLED_ShowCN(2,1,1);//湿
			OLED_ShowCN(2,2,5);//度
			OLED_ShowChar(2,5,':');
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
	
	
 
  while (1)
  {
//		LED_Toggle();
		value = MQ135_GetData();  
		
//		printf("空气质量: %d\r\n",value);  //串口发送
		OLED_ShowNum(4,10,value,4);
		
//		ppm = MQ135_GetData_PPM();
//		sprintf((char*)buff, "%.2fppm    ",ppm);
//		OLED_ShowString(4,10,(char*)buff);
		
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

