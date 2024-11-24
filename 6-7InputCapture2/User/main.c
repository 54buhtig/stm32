#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"




int main(void)
{
   
	OLED_Init();  //初始化OLED	
	PWM_Init();  //初始化PWM
	IC_Init();
	
	PWM_SetPerscaler(720-1);       //Freq = 72M /(PSC+1)/(ARR+1)
	PWM_SetCompare1(80);           //Duty = CCR / (ARR+1) 
	
	OLED_ShowString(1,1,"Freq:00000Hz");
	OLED_ShowString(2,1,"Duty:000%");
	

	
	while(1)  
	{
		OLED_ShowNum(1,6,IC_GetFreq(),5);
		OLED_ShowNum(2,6,IC_GetDuty(),3);
	}
}

