#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "Serial.h"

/*数据格式：8bit湿度整数数据+8bit湿度小数数据
+8bit温度整数数据+8bit温度小数数据
 +8bit校验和*/

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
		
		Delay_s(1);
		DHT11_REC_Data(); //接收温度和湿度的数据
		
	    OLED_ShowNum(1,6,rec_data[2],2);
		OLED_ShowNum(1,9,rec_data[3],1);
		OLED_ShowNum(2,6,rec_data[0],2);
		OLED_ShowNum(2,9,rec_data[1],2);
     
//		Serial_Printf("温度：%d\r\n",rec_data[2]);
//		Serial_Printf("湿度：%d\r\n",rec_data[0]);
//		Serial_Printf("\r\n\n");
	}
}

