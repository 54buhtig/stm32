#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"


int main(void)
{
   
	OLED_Init();  //��ʼ��OLED
	CounterSensor_Init();  //��ʼ��������䴫����
	
	
	//����PWR����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	
	OLED_ShowString(1,1,"Count:"); 	//��1����ʾ�ַ���
	
	
	

	while(1)  
	{
		OLED_ShowNum(1,7,Get_CounterSensor(),5);
		
		
		//����ֹͣģʽ�����������򣬡�Running������������ԭ�������ֹͣģʽ�����������򣬳���
		//��ѡ��HSI��Ϊϵͳʱ��
		OLED_ShowString(2,1,"Running");
		Delay_ms(100);
		OLED_ShowString(2,1,"       ");
		Delay_ms(100);
		
		
		PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);//����ͣ��ģʽ�Ĵ���
		
		SystemInit(); //�ָ�ʱ��
	}
}

