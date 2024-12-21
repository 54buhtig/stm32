#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"



int main(void)
{
   
	OLED_Init();  //��ʼ��OLED

	KEY_Init();
	
	OLED_ShowString(1,1,"IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET)  //��ȡ�������Ź���״̬λ	
	{

		OLED_ShowString(2,1,"IWDGRST");  
		Delay_ms(500); 
		OLED_ShowString(2,1,"       ");  
		Delay_ms(100); 
		RCC_ClearFlag();  //�����־λ
	}
	else
	{
		OLED_ShowString(3,1,"RST");  
		Delay_ms(500); 
		OLED_ShowString(3,1,"   ");  
		Delay_ms(100); 	
	}
	
	
	//��1��:����LSIʱ��,��STMǿ�ƿ���,�����������
	//��2��:���д����
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	
	//��3��:����Ԥ��Ƶ����װֵ
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);    //1000ms
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	while(1)  
	{
		
		
		Key_GetNum();
		
		IWDG_ReloadCounter();
		
		OLED_ShowString(4,1,"FEED");
		Delay_ms(200);
		OLED_ShowString(4,1,"    ");
		Delay_ms(600);
		
	}
}

