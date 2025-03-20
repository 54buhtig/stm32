#include "stm32f10x.h"                  // Device header


/**
   * @brief  ��ʼ��LED
   * @param  ��
   * @retval ��
   */
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʱ��ʹ��
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2 ;   //����A1 ������A2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);  //Ĭ�Ϲر�LED��
}


/**
   * @brief ��LED1
   * @param ��
   * @retval ��
   */
void LED1_On(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1 );  //��LED1��
}


/**
   * @brief   �ر�LED1
   * @param   ��
   * @retval  ��
   */
void LED1_Off(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_1 );  //�ر�LED1��
}

/**
   * @brief   ��תLED1��״̬
   * @param   ��
   * @retval  ��
   */
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)  //LED����
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);   //Ϩ��LED
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==1)  //LED����
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1); //��LED
	}
}
 

/**
   * @brief ��LED2
   * @param ��
   * @retval ��
   */
void LED2_On(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2 );  //��LED2��
}

/**
   * @brief   �ر�LED2
   * @param   ��
   * @retval  ��
   */
void LED2_Off(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2 );  //�ر�LED2��

}

/**
   * @brief   ��תLED2��״̬
   * @param   ��
   * @retval  ��
   */
void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)  //LED����
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);   //Ϩ��LED
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==1)  //LED����
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2); //��LED
	}
}

