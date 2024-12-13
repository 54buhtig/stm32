#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"


int main(void)
{
   
	OLED_Init();  //初始化OLED
	CounterSensor_Init();  //初始化红外对射传感器
	
	
	//开启PWR外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	
	OLED_ShowString(1,1,"Count:"); 	//第1行显示字符串
	
	
	

	while(1)  
	{
		OLED_ShowNum(1,7,Get_CounterSensor(),5);
		
		
		//进入停止模式后再启动程序，“Running”程序会变慢，原因就在于停止模式结束后进入程序，程序
		//会选择HSI作为系统时钟
		OLED_ShowString(2,1,"Running");
		Delay_ms(100);
		OLED_ShowString(2,1,"       ");
		Delay_ms(100);
		
		
		PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);//进入停机模式的代码
		
		SystemInit(); //恢复时钟
	}
}

