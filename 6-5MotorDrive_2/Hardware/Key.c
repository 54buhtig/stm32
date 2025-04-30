#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
   * @brief 初始化按键
   * @param 无
   * @retval 无
   */
void KEY_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU ;             //上拉输入模式
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/**
   * @brief 得到按键值
   * @param 无
   * @retval uint8_t
   */
uint8_t  Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		Delay_ms(20);
		KeyNum = 1;  //按键1
		
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		Delay_ms(20);
		KeyNum = 2;  //按键2
		
	}
	return KeyNum;
}


