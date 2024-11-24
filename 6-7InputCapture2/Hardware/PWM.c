#include "stm32f10x.h"                  // Device header

/**
   * @brief  ��ʼ��PWM����
   * @param  ��
   * @retval ��
   */
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  //����ʱ��
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);   //ʱ��ʹ��AFIO	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);    //GPIO�ĸ��ù���
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);   //��PA15��Ϊ��ͨ����,���PA15�ĵ��Թ���

	//���ų�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʱ��ʹ��	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //ѡ��������ģʽ,��������������������������ƽ,��ͨ������ģʽ�������ݼĴ��������ƽ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;   //����A0    GPIO_Pin_15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM2);   //�Ȳ�ʱ����Ϊ��ʱ��2��ʱ��,��ʱ���ϵ�Ĭ��ʹ���ڲ�ʱ��
	
	
	
	
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;        //ARRֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;      //PSCֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	//��ʼ������Ƚϵ�Ԫ
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);   //�ȸ��ṹ�帳��ʼֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity =  TIM_OCPolarity_High ;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;      //CCR��ֵ
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);

	//������ʱ��
	TIM_Cmd(TIM2,ENABLE);

}

/**
   * @brief ����PWM���ε�ռ�ձ�
   * @param ռ�ձ�
   * @retval ��
   */
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

/**
   * @brief   ���ö�ʱ���ķ�Ƶ������ 
   * @param   ��Ƶ����
   * @retval  ��
   */
void PWM_SetPerscaler(uint16_t Perscaler)
{
	TIM_PrescalerConfig(TIM2,Perscaler,TIM_PSCReloadMode_Immediate);   
}




