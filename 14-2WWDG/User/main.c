#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"



int main(void)
{
   
	OLED_Init();  //��ʼ��OLED

	KEY_Init();
	
	OLED_ShowString(1,1,"WWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST)==SET)  //��ȡ���ڿ��Ź���״̬λ	
	{

		OLED_ShowString(2,1,"WWDGRST");  
		Delay_ms(500); 
		OLED_ShowString(2,1,"       ");  
		Delay_ms(100); 
		RCC_ClearFlag(); //�����־λ
	}
	else
	{
		OLED_ShowString(3,1,"RST");  
		Delay_ms(500); 
		OLED_ShowString(3,1,"   ");  
		Delay_ms(100); 	
	}
	
	
	//��1��:����PCLK1ʱ�ӣ�Ҳ����APB1���ߵ�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	
	//��2��:����Ԥ��Ƶ�ʹ���ֵ
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);   //����ʱ��30ms
	
	//��3��������WWDGʹ��
	WWDG_Enable(0x40 | 54);  //��ʱʱ��50ms

	
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

