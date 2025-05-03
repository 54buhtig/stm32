#include "stm32f10x.h"                  // Device header
#include "PWM2.h"

void Servo_Init(void)
{
	PWM2_Init();
	
}




//0  500
//180  2500

void Servo_SetAngle(float Angle)
{
	PWM2_SetCompare2(Angle/180*2000+500);     
}


