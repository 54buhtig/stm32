#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "Motor.h"


uint8_t  KeyNum;
float Angle;
int8_t Speed=0;     //速度

int main(void)
{
   
	OLED_Init();  //初始化OLED	
//	Servo_Init();  //初始化PWM
	Motor_Init();
	KEY_Init();
	
	OLED_ShowString(1,1,"Angle:");
	
	
	while(1)  
	{
		KeyNum = Key_GetNum();
//		if(KeyNum==2)
//		{
//			Angle+=90;
//			if(Angle > 180)
//			{
//				Angle = 0;
//			}
//		}
//		Servo_SetAngle(Angle);
		if(KeyNum==1)    //虚拟按键
		{
			Speed+=20;
			if(Speed>100)
			{
				Speed = -100;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowNum(1,7,Angle,3);
		OLED_ShowNum(2,7,Speed,3);
	}
}

