#include "stm32f10x.h"                  // Device header


int16_t Counter = 0;

/**
   * @brief    ����ת���������г�ʼ������Ϊ5��
   * @param    ��
   * @retval   ��
   */
void EnCoder_Init(void)
{
	//��1������ʼ��rcc��EXTI��NVIC�����ʼ��,�ں��������迪��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	
	//��2������GPIO�˿ڳ�ʼ������ģʽ��ʹ�õ���PB0��PB1
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //�������룬����Ĭ������ߵ�ƽ
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//��3����AFIO��EXTI����������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
	//��4����EXTI
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXIT_InitStructure.EXTI_LineCmd = ENABLE;
	EXIT_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //�ж���Ӧ
	EXIT_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�����ش����ж�
	EXTI_Init(&EXIT_InitStructure);
	
	
	//��5����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //���鷽ʽ�ڳ����ж���ֻ��ִ��һ�Σ��˴�ִ�к��������̶������ַ���ģʽ
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//���ⲿ�ж�1��������
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	//���ⲿ�ж�2��������
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
}

/**
   * @brief    �õ��жϺ����õ��ı仯ֵ
   * @param    ��
   * @retval   ���ر仯ֵ
   */
int16_t EnCoder_Get(void)
{
	int16_t temp = 0;
	temp = Counter;
	Counter = 0;
	return temp; 	
}


/**
   * @brief   �����ⲿ�ж�0���жϺ���
   * @param   ��
   * @retval  ��
   */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)   //�����ؽ����ж�
	{
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)  //��ת������B�ڵĵ�ƽ���ڸߵ�ƽ
		{
			Counter ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}
}

/**
   * @brief �����ⲿ�ж�1���жϺ���
   * @param  ��
   * @retval ��
   */
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)   //�����ؽ����ж�
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1)   //��ת������A�ڵĵ�ƽ���ڸߵ�ƽ
		{
			Counter --;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);	
	}
}


