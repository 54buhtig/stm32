#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"



int main(void)
{
   
	OLED_Init();  //初始化OLED

	KEY_Init();
	
	OLED_ShowString(1,1,"WWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST)==SET)  //获取窗口看门狗的状态位	
	{

		OLED_ShowString(2,1,"WWDGRST");  
		Delay_ms(500); 
		OLED_ShowString(2,1,"       ");  
		Delay_ms(100); 
		RCC_ClearFlag(); //清除标志位
	}
	else
	{
		OLED_ShowString(3,1,"RST");  
		Delay_ms(500); 
		OLED_ShowString(3,1,"   ");  
		Delay_ms(100); 	
	}
	
	
	//第1步:开启PCLK1时钟，也就是APB1总线的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	
	//第2步:配置预分频和窗口值
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);   //窗口时间30ms
	
	//第3步：进行WWDG使能
	WWDG_Enable(0x40 | 54);  //超时时间50ms

	
	while(1)  
	{
		
		
		Key_GetNum();
		
		
		
//		OLED_ShowString(4,1,"FEED");
//		Delay_ms(20);
//		OLED_ShowString(4,1,"    ");
		Delay_ms(49);
	
		WWDG_SetCounter(0x40 |54);

	}
}

