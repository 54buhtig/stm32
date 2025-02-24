#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t  Num;

int main(void)
{
   
	OLED_Init();  //初始化OLED

	Timer_Init();  //初始化定时器
	OLED_ShowString(1,1,"Num:"); 	//第1行显示字符串
	OLED_ShowString(2,1,"CNT:"); 	//第1行显示字符串

	while(1)  
	{
		
		OLED_ShowNum(1,5,Num,5);
		OLED_ShowNum(2,5,Timer_GetCounter(),5); 
	}
}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
