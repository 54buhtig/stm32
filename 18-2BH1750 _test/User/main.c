//	#include "sys.h"	
	#include "delay.h"	
	#include "led.h" 
	#include "key.h"
	#include "OLED.h"
//	#include "bmp.h"
//	#include "dht11.h"
	#include "BH1750.h"
	
	u8 temperature =0;  	    
	u8 humidity = 0; 
	float Light = 0; //光照度
	
	 int main(void)
	 {
		u8 t =0;
//		delay_init();	    	 //延时函数初始化	  
//		LED_Init();		  	 	//初始化与LED连接的硬件接口
//		KEY_Init();            //初始化与按键连接的硬件接口
		OLED_Init();           //初始化与OLED显示屏
		OLED_Clear();           //清楚屏幕
		 
//		DHT11_Init();          //初始化DHT11
		BH1750_Init();          //初始化BH1750
		  
		while(1)
		{
		
		if(t%10==0)			//每100ms读取一次
			{									  
//				DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值	
				if (!i2c_CheckDevice(BH1750_Addr))
				{
					Light = LIght_Intensity();              //获取光照强度
				}		
	 	   
			}	
			Delay_ms(10);
			t++;
			//OLED显示文字 "温度："
//			OLED_ShowCHinese(0,3,7);//温
//			OLED_ShowCHinese(18,3,8);//度
//			OLED_ShowString(40,4,":",26);//:
//			OLED_ShowNum(50,3,temperature,2,16);//显示ASCII字符的码值 	
			
//			//OLED显示文字 "湿度："
//			OLED_ShowCHinese(0,6,9);//湿
//			OLED_ShowCHinese(18,6,8);//度
//			OLED_ShowString(40,7,":",26);//:
//			OLED_ShowNum(50,6,humidity,2,16);//显示ASCII字符的码值
			 
			//OLED显示文字 "光照强度"
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
			OLED_ShowFNum(3,10,Light);
			OLED_ShowCN(4,1,6);//空
			OLED_ShowCN(4,2,7);//气
			OLED_ShowCN(4,3,8);//质
			OLED_ShowCN(4,4,9);//量
			OLED_ShowChar(4,9,':');
//			if(Light<50)//光照强度小于50，LED1灯亮
//			{
//				LED1 = 0;
//			
//			}
//			else
//			{
//				LED1=1;
//			
//			}
			
		}
		
	}


