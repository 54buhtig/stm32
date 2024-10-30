#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"


int main(void)
{
   
	OLED_Init();  //��ʼ��OLED
	CounterSensor_Init();  //��ʼ��������䴫����
	OLED_ShowString(1,1,"Count:"); 	//��1����ʾ�ַ���

	while(1)  
	{
		OLED_ShowNum(1,7,Get_CounterSensor(),5);
		
     
	}
}

