#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  //开启时钟
	


	//引脚初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //时钟使能	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //选择复用推挽模式,这样边上外设才能在引脚输出电平,普通的推挽模式是由数据寄存器输出电平的
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;   //引脚A2    GPIO_Pin_15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM2);   //內部时钟作为定时器2的时钟,定时器上电默认使用内部时钟
	
	
	
	
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;        //ARR值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36-1;      //PSC值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);   //先给结构体赋初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity =  TIM_OCPolarity_High ;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;      //CCR的值
	
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);    //通道3初始化
   
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);

}


void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2,Compare);
}





