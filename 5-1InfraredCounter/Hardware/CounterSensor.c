#include "stm32f10x.h"                  // Device header


uint16_t CounterSensor_Count = 0;

/**
   * @brief ���������������г�ʼ�����ܹ���5��
   * @param ��
   * @retval ��
   */


void CounterSensor_Init(void)
{
	//��1������ʼ��rcc��EXTI��NVIC�����ʼ��,�ں��������迪��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	
	//��2������GPIO�˿ڳ�ʼ������ģʽ
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //��������
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//��3����AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

	
	//��4����EXTI
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line = EXTI_Line14;
	EXIT_InitStructure.EXTI_LineCmd = ENABLE;
	EXIT_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //�ж���Ӧ
	EXIT_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½��ش����ж�
	EXTI_Init(&EXIT_InitStructure);
	
	
	//��5����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //���鷽ʽ�ڳ����ж���ֻ��ִ��һ�Σ��˴�ִ�к��������̶������ַ���ģʽ
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
}

/**
   * @brief   �õ��ƴδ���
   * @param   ��
   * @retval  �ƴδ���������Ϊuint16_t
   */
uint16_t Get_CounterSensor(void)
{
	return CounterSensor_Count;
}



/**
   * @brief �жϺ��������ƹ̶���������жϺ����н��мƴ�
   * @param  ��
   * @retval ��
   */
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14));  //Ϊ�˷�ֹ�����������ĵ�ƽ�ж�
		CounterSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);   //һ�����жϺ�������жϱ�־λ���������Ῠ���жϺ�����
	}
}

