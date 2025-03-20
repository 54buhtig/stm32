#include "stm32f10x.h"                  // Device header

/**
   * @brief  ��ʼ��Buzzer
   * @param  ��
   * @retval ��
   */
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʱ��ʹ��
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;   //����12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);  //Ĭ�Ϲر�Buzzer
}


/**
   * @brief ��Buzzer
   * @param ��
   * @retval ��
   */
void Buzzer_On(void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12 );  //��Buzzer
}


/**
   * @brief   �ر�Buzzer
   * @param   ��
   * @retval  ��
   */
void Buzzer_Off(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_12 );  //�ر�Buzzer
}

/**
   * @brief   ��תBuzzer��״̬
   * @param   ��
   * @retval  ��
   */
void Buzzer_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)  //Buzzer��
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);   //�ر�Buzzer
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_12)==1)  //Buzzer����
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12); //��Buzzer
	}
}




