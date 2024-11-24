#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "EnCoder.h"


int16_t  Speed;

int main(void)
{
   
	OLED_Init();  //��ʼ��OLED

	Timer_Init();  //��ʼ����ʱ��
	OLED_ShowString(1,1,"Speed:"); 	//��1����ʾ�ַ���

	Encoder_Init();
	while(1)  
	{
	
		OLED_ShowSignedNum(1,7,Speed,5);
//		Delay_ms(1000);   //բ��ʱ��Ϊ1s,�������ʱբ��ʱ��Ӧ�����ö�һЩ,��ֹ���������,�ӿ�ˢ���ٶ�
//		OLED_ShowNum(1,5,Num,3);
//		OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5); 
	}
}



//Delay�������������ִ��,Ϊ�˸��õ�����բ��ʱ��,���ö�ʱ���ж���ʵ��
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Speed = Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
