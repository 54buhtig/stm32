#include "stm32f10x.h"                  // Device header


/**
   * @brief  ��ʼ��������
   * @param  ��
   * @retval ��
   */
void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʱ��ʹ��
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;   //����A1 ������A2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //�����ٶȶ�������û��Ӱ��
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

/**
   * @brief  ���˿ڵĵ�ƽ����
   * @param  ��
   * @retval ��
   */
uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}



