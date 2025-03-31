#include "stm32f10x.h"                  // Device header

/**
   * @brief  初始化Buzzer
   * @param  无
   * @retval 无
   */
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //时钟使能
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;   //引脚12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);  //默认关闭Buzzer
}


/**
   * @brief 打开Buzzer
   * @param 无
   * @retval 无
   */
void Buzzer_On(void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12 );  //打开Buzzer
}


/**
   * @brief   关闭Buzzer
   * @param   无
   * @retval  无
   */
void Buzzer_Off(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_12 );  //关闭Buzzer
}

/**
   * @brief   翻转Buzzer的状态
   * @param   无
   * @retval  无
   */
void Buzzer_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)  //Buzzer响
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);   //关闭Buzzer
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_12)==1)  //Buzzer不响
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12); //打开Buzzer
	}
}




