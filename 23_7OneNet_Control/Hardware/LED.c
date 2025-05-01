#include "stm32f10x.h"                  // Device header




/**
   * @brief  初始化LED
   * @param  无
   * @retval 无
   */
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //时钟使能
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_8 |GPIO_Pin_10;   //引脚A1 和引脚A8  引脚A10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_10);  //默认关闭LED灯
}


/**
   * @brief 打开LED1
   * @param 无
   * @retval 无
   */
void LED1_On(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1 );  //打开LED1灯
}


/**
   * @brief   关闭LED1
   * @param   无
   * @retval  无
   */
void LED1_Off(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_1 );  //关闭LED1灯
}

/**
   * @brief   翻转LED1的状态
   * @param   无
   * @retval  无
   */
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)  //LED灯亮
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);   //熄灭LED
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==1)  //LED灯灭
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1); //打开LED
	}
}


/**
   * @brief 打开LED2
   * @param 无
   * @retval 无
   */
void LED2_On(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8 );  //打开LED2灯
}

/**
   * @brief   关闭LED2
   * @param   无
   * @retval  无
   */
void LED2_Off(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_8 );  //关闭LED2灯

}

/**
   * @brief   翻转LED2的状态
   * @param   无
   * @retval  无
   */
void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8)==0)  //LED灯亮
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);   //熄灭LED
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8)==1)  //LED灯灭
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8); //打开LED
	}
}


/**
   * @brief 打开LED2
   * @param 无
   * @retval 无
   */
void LED3_On(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_10 );  //打开LED2灯
}

/**
   * @brief   关闭LED2
   * @param   无
   * @retval  无
   */
void LED3_Off(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_10 );  //关闭LED2灯

}

/**
   * @brief   翻转LED2的状态
   * @param   无
   * @retval  无
   */
void LED3_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10)==0)  //LED灯亮
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_10);   //熄灭LED
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10)==1)  //LED灯灭
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_10); //打开LED
	}
}
