#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "EnCoder.h"

int16_t Num;

int main(void)
{
   
	OLED_Init();  //初始化OLED
	EnCoder_Init(); //初始化旋转编码器
	OLED_ShowString(1,1,"Num:"); 	//第1行显示字符串

	while(1)  
	{
		Num+=EnCoder_Get();
//		Num = EnCoder_Get();
		OLED_ShowSignedNum(1,7,Num,5);
	}
}

