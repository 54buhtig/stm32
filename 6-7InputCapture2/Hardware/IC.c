#include "stm32f10x.h"                  // Device header


/**
   * @brief   ��ʼ�����벶���·
   * @param   ��
   * @retval  ��
   */

void IC_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //����ʱ��ʹ��		


	//���ų�ʼ��

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //ѡ��������ģʽ,��������������������������ƽ,��ͨ������ģʽ�������ݼĴ��������ƽ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;   //����A6    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM3);   //�Ȳ�ʱ����Ϊ��ʱ��2��ʱ��,��ʱ���ϵ�Ĭ��ʹ���ڲ�ʱ��
	
	
	
	
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;        //ARRֵȡ���ֵ,
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;      //PSCֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	
	
	
	//��4��:��ʼ�����벶��Ԫ
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF; 
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);  //�������Զ���ʣ�µ�ͨ����ʼ��Ϊ�෴����,ֻ��ʵ��ͨ��1��ͨ��2
	
	
	
	//��5��:��������ģʽ
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);   //����Դѡ��
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);    //��ģʽ
	
	
	TIM_Cmd(TIM3,ENABLE);   //������ʱ��
	
}


/**
   * @brief   ��ò���Ƶ��ֵ
   * @param   ��
   * @retval  ����Ƶ��ֵ
   */
uint32_t IC_GetFreq(void)
{
	return 1000000 / TIM_GetCapture1(TIM3)-1;    //fc/N,��λΪHz
} 



/**
   * @brief ����PWM��ռ�ձ�
   * @param ��
   * @retval ����ռ�ձ� 0~100
   */
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
//	return TIM_GetCapture2(TIM3)/TIM_GetCapture1(TIM3);
}










