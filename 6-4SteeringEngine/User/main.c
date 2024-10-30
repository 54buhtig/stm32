#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"



int main(void)
{
   
	OLED_Init();  //初始化OLED	
	PWM_Init();  //初始化PWM
	
	
	PWM_SetCompare2(500);
	
	while(1)  
	{

	}
}

