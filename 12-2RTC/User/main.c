#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"


int main(void)
{
   
	OLED_Init();  //初始化OLED
	MyRTC_Init();
	
	
	OLED_ShowString(1,1,"Data:XXXX-XX-XX");
	OLED_ShowString(2,1,"Time:XX:XX:XX");
	OLED_ShowString(3,1,"CNT: ");
	OLED_ShowString(3,1,"DIV: ");
	
	while(1)  
	{
		MyRTC_ReadTime();
		
		
		OLED_ShowNum(1,6,MyRTC_Time[0],4);
		OLED_ShowNum(1,11,MyRTC_Time[1],2);
		OLED_ShowNum(1,14,MyRTC_Time[2],2);
		OLED_ShowNum(2,6,MyRTC_Time[3],2);
		OLED_ShowNum(2,9,MyRTC_Time[4],2);
		OLED_ShowNum(2,12,MyRTC_Time[5],2);


		OLED_ShowNum(3,6,RTC_GetCounter(),10);	
		OLED_ShowNum(4,6,RTC_GetDivider(),10);
		

//通过DIV的值计算得到毫秒,微妙的值		
//		OLED_ShowNum(4,6,(32767-RTC_GetDivider())/32767.0*999,10); //可以得到毫秒级时间
		
	}
}

