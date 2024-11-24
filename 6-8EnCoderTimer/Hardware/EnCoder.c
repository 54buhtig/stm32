#include "stm32f10x.h"                  // Device header


/**
   * @brief ��������ʼ��,����CNT�������Լ�
   * @param ��
   * @retval ��
   */
void Encoder_Init(void)
{
	//��1��:����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //����ʱ��3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //����ʱ��ʹ��		


	//��2��:���ų�ʼ��

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //ѡ��������ģʽ,��������������������������ƽ,��ͨ������ģʽ�������ݼĴ��������ƽ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;   //����A6��A7    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	
	//��3��:����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;        //ARRֵȡ���ֵ,
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1-1;      //PSCֵΪ0,����Ƶ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	
	
	
	//��4��:��ʼ��ͨ��1��ͨ��2�����벶��Ԫ
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);  //���ṹ�帳��ʼֵ
	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;   //ͨ��1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;       //�˲���
	TIM_ICInit(TIM3,&TIM_ICInitStructure);   //��ͨ��1����Ԫ��ʼ��
	
	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;   //ͨ��2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;       //�˲���
	TIM_ICInit(TIM3,&TIM_ICInitStructure);   //��ͨ��1����Ԫ��ʼ��
	

	//��5��:���ñ������ӿ�
	//ע�����������Ӧ����ICInit֮��,����ICInit�Ḳ�ǵ�������������
	//�޸���һ���Կ����Զ��ı�����������ת�������,ͬʱ�޸����������򱣳ֲ���
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);


	//����TIM3
	TIM_Cmd(TIM3,ENABLE);
}


/**
   * @brief   ��ȡ��������ֵ,����������λ��/�����������ٶ�	
   * @param   ��
   * @retval  CNTֵ int16_t,���������Զ���CNTת��Ϊ�з�����
   */
//uint16_t Encoder_Get(void)
//{
//	return TIM_GetCounter(TIM3);  //����CNTֵ
//}
//int16_t Encoder_Get(void)
//{
//	return TIM_GetCounter(TIM3);  //����CNTֵ
//}
int16_t Encoder_Get(void)
{
	int16_t Temp;	//����һ����ʱ����
	Temp = TIM_GetCounter(TIM3);     //��ȡCNTֵ��������ʱ����
	TIM_SetCounter(TIM3,0);   //����CNT
	return Temp;  //����CNTֵ
}


