#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"



int main(void)
{
   
	OLED_Init();  //��ʼ��OLED	
	PWM_Init();  //��ʼ��PWM
	
	
	PWM_SetCompare2(500);
	
	while(1)  
	{

	}
}

