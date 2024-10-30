#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  //����ʱ��
	
	
	TIM_InternalClockConfig(TIM2);   //�Ȳ�ʱ����Ϊ��ʱ��2��ʱ��,��ʱ���ϵ�Ĭ��ʹ���ڲ�ʱ��
	
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update); 
	//����TIM_TimeBaseInit����ÿ�γ�ʼ�����жϱ�־λ��1��
	//���Գ��������ʱ�ͽ����жϣ�Ϊ�˷�ֹ�жϲ�������TIM_TimeBaseInit֮���жϿ�ʼǰ���жϱ�־λ����
	
	//ʹ���ж�
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //NVIC���ȼ�����
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //ѡ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	//������ʱ��
	TIM_Cmd(TIM2,ENABLE);

}

/*
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
*/

