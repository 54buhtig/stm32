#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"


int main(void)
{
   
	OLED_Init();  //初始化OLED
	CounterSensor_Init();  //初始化红外对射传感器
	OLED_ShowString(1,1,"Count:"); 	//第1行显示字符串

	while(1)  
	{
		OLED_ShowNum(1,7,Get_CounterSensor(),5);
		
     
	}
}

