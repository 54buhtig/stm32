#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "EnCoder.h"


int16_t  Speed;

int main(void)
{
   
	OLED_Init();  //初始化OLED

	Timer_Init();  //初始化定时器
	OLED_ShowString(1,1,"Speed:"); 	//第1行显示字符串

	Encoder_Init();
	while(1)  
	{
	
		OLED_ShowSignedNum(1,7,Speed,5);
//		Delay_ms(1000);   //闸门时间为1s,电机测速时闸门时间应该设置短一些,防止计数器溢出,加快刷新速度
//		OLED_ShowNum(1,5,Num,3);
//		OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5); 
	}
}



//Delay会阻塞主程序的执行,为了更好的设置闸门时间,利用定时器中断来实现
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Speed = Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
