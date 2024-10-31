#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;   //接收键值
int8_t Speed;     //速度

int main(void)
{
   
	OLED_Init();  //初始化OLED	
	Motor_Init();  //初始化电机
	KEY_Init();
	
	
	OLED_ShowString(1,1,"Speed:");
	
	while(1)  
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			Speed+=20;
			if(Speed>100)
			{
				Speed = -100;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1,7,Speed,3);
	}
}

