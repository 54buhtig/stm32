#include "stm32f10x.h"                  // Device header


uint16_t CounterSensor_Count = 0;

/**
   * @brief 红外对射计数器进行初始化，总共分5步
   * @param 无
   * @retval 无
   */


void CounterSensor_Init(void)
{
	//第1步：初始化rcc，EXTI和NVIC无需初始化,内核外设无需开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	
	//第2步：将GPIO端口初始化输入模式
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //上拉输入
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//第3步：AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

	
	//第4步：EXTI
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line = EXTI_Line14;
	EXIT_InitStructure.EXTI_LineCmd = ENABLE;
	EXIT_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //中断响应
	EXIT_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿触发中断
	EXTI_Init(&EXIT_InitStructure);
	
	
	//第5步：NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //分组方式在程序中都是只需执行一次，此处执行后整个工程都是这种分组模式
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
}

/**
   * @brief   得到计次次数
   * @param   无
   * @retval  计次次数，类型为uint16_t
   */
uint16_t Get_CounterSensor(void)
{
	return CounterSensor_Count;
}



/**
   * @brief 中断函数，名称固定，在这个中断函数中进行计次
   * @param  无
   * @retval 无
   */
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14));  //为了防止计数两次做的电平判断
		CounterSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);   //一定在中断函数清除中断标志位，否则程序会卡在中断函数里
	}
}

