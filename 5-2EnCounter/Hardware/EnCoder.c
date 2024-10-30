#include "stm32f10x.h"                  // Device header


int16_t Counter = 0;

/**
   * @brief    给旋转编码器进行初始化，分为5步
   * @param    无
   * @retval   无
   */
void EnCoder_Init(void)
{
	//第1步：初始化rcc，EXTI和NVIC无需初始化,内核外设无需开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	
	//第2步：将GPIO端口初始化输入模式，使用的是PB0和PB1
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入，引脚默认输出高电平
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//第3步：AFIO给EXTI输入线设置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
	//第4步：EXTI
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXIT_InitStructure.EXTI_LineCmd = ENABLE;
	EXIT_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //中断响应
	EXIT_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //上升沿触发中断
	EXTI_Init(&EXIT_InitStructure);
	
	
	//第5步：NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //分组方式在程序中都是只需执行一次，此处执行后整个工程都是这种分组模式
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//对外部中断1进行配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	//对外部中断2进行配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
}

/**
   * @brief    得到中断函数得到的变化值
   * @param    无
   * @retval   返回变化值
   */
int16_t EnCoder_Get(void)
{
	int16_t temp = 0;
	temp = Counter;
	Counter = 0;
	return temp; 	
}


/**
   * @brief   触发外部中断0的中断函数
   * @param   无
   * @retval  无
   */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)   //上升沿进入中断
	{
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)  //旋转编码器B口的电平处于高电平
		{
			Counter ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}
}

/**
   * @brief 触发外部中断1的中断函数
   * @param  无
   * @retval 无
   */
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)   //上升沿进入中断
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1)   //旋转编码器A口的电平处于高电平
		{
			Counter --;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);	
	}
}


