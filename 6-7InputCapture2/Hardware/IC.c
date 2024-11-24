#include "stm32f10x.h"                  // Device header


/**
   * @brief   初始化输入捕获电路
   * @param   无
   * @retval  无
   */

void IC_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启时钟使能		


	//引脚初始化

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //选择复用推挽模式,这样边上外设才能在引脚输出电平,普通的推挽模式是由数据寄存器输出电平的
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;   //引脚A6    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM3);   //內部时钟作为定时器2的时钟,定时器上电默认使用内部时钟
	
	
	
	
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;        //ARR值取最大值,
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;      //PSC值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	
	
	
	//第4步:初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF; 
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);  //函数会自动将剩下的通道初始化为相反配置,只能实现通道1和通道2
	
	
	
	//第5步:配置主从模式
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);   //触发源选择
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);    //从模式
	
	
	TIM_Cmd(TIM3,ENABLE);   //启动定时器
	
}


/**
   * @brief   获得测量频率值
   * @param   无
   * @retval  测量频率值
   */
uint32_t IC_GetFreq(void)
{
	return 1000000 / TIM_GetCapture1(TIM3)-1;    //fc/N,单位为Hz
} 



/**
   * @brief 返回PWM的占空比
   * @param 无
   * @retval 返回占空比 0~100
   */
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
//	return TIM_GetCapture2(TIM3)/TIM_GetCapture1(TIM3);
}










