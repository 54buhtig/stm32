#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Servo.h"

uint8_t KeyNum;   //接收键值
int8_t Speed=100;     //速度
float Angle;
int8_t CounterWise = 0;
int main(void)
{
   
	OLED_Init();  //初始化OLED	
	Motor_Init();  //初始化电机
	KEY_Init();
	Servo_Init();
	
	OLED_ShowString(1,1,"Speed:");
	
	while(1)  
	{
		KeyNum = Key_GetNum();
		
		if(KeyNum==1)    //虚拟按键
		{
			Speed-=20;
			if(Speed<0)
			{
				Speed = 100;
				if(CounterWise)
					CounterWise = 0;
				else CounterWise = 1;
			}
			Delay_ms(1000);
		}
		Motor_SetSpeed(CounterWise,Speed);
		if(KeyNum==2)
		{
			Angle+=90;
			if(Angle > 180)
			{
				Angle = 0;
			}
			Servo_SetAngle(Angle);
			Delay_ms(500);
		}
		

		OLED_ShowNum(1,7,Angle,3);
		OLED_ShowNum(2,7,Speed,3);
	}
}

