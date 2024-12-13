#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"


int main(void)
{
   
	//待机模式唤醒后，程序从头开始执行
	OLED_Init();  //初始化OLED
	MyRTC_Init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//再次开启PWR时钟确保代码独立性，时钟可以重复开启
	
	OLED_ShowString(1,1,"CNT :");
	OLED_ShowString(2,1,"ALR :");
	OLED_ShowString(3,1,"ALRF:");
	
	
	PWR_WakeUpPinCmd(ENABLE);  //初始化唤醒引脚，无需初始化GPIO引脚，引脚被强置为输入下拉配置
	
	uint32_t Alarm = RTC_GetCounter()+10;
	RTC_SetAlarm(Alarm);
	OLED_ShowNum(2,6,Alarm,10);
	
	
	while(1)  
	{	
		
		OLED_ShowNum(1,6,RTC_GetCounter(),10);	
		OLED_ShowNum(3,6,RTC_GetFlagStatus(RTC_FLAG_ALR),1);
		
		
		OLED_ShowString(4,1,"Running");
		Delay_ms(100);
		OLED_ShowString(4,1,"       ");
		Delay_ms(100);
		
		OLED_ShowString(4,9,"STANDBY");
		Delay_ms(1000);
		OLED_ShowString(4,9,"       ");
		Delay_ms(1000);
		
		OLED_Clear();
		PWR_EnterSTANDBYMode();
		
		
//通过DIV的值计算得到毫秒,微妙的值		
//		OLED_ShowNum(4,6,(32767-RTC_GetDivider())/32767.0*999,10); //可以得到毫秒级时间
		
	}
}

