	#include "delay.h"	
	#include "led.h" 
	#include "key.h"
	#include "OLED.h"
	#include "dht11.h"
	#include "BH1750.h"
	#include "mq135.h"
	
	extern unsigned int rec_data[4];  //湿度和温度
	float Light = 0; //光照度
	u16 value;   //空气质量
 int main(void)
 {
	u8 t =0;
	u8 l = 0;
	u8 k = 0;
	
	SystemInit();//配置系统时钟为72M
	OLED_Init();           //初始化与OLED显示屏
	OLED_Clear();           //清楚屏幕
	BH1750_Init();          //初始化BH1750
	MQ135_Init();

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
	while(1)
	{
	
	if(t%10==0)			//每100ms读取一次
	{
		l++;
		k++;
		if(k%2==0)
		{
			value = MQ135_GetData(); 
		}
		if(l%10==0)
		{
			DHT11_REC_Data(); //接收温度和湿度的数据
		}
		if (!i2c_CheckDevice(BH1750_Addr))
		{
			Light = LIght_Intensity();//获取光照强度
		}
	}
	Delay_ms(10);
	t++;
	
	OLED_ShowNum(1,6,rec_data[2],2);
	OLED_ShowNum(1,9,rec_data[3],1);
	OLED_ShowNum(2,6,rec_data[0],2);
	OLED_ShowNum(2,9,rec_data[1],2);
	OLED_ShowFNum(3,10,Light);
	OLED_ShowNum(4,10,value,4);
	
	
	}
}


