#include "stm32f10x.h"                  // Device header


/**
   * @brief  初始化光敏器
   * @param  无
   * @retval 无
   */
void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //时钟使能
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;   //引脚A1 和引脚A2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //引脚速度对于输入没有影响
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

/**
   * @brief  将端口的电平读出
   * @param  无
   * @retval 无
   */
uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}



