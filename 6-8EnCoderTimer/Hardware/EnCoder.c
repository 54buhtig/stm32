#include "stm32f10x.h"                  // Device header


/**
   * @brief 编码器初始化,控制CNT自增或自减
   * @param 无
   * @retval 无
   */
void Encoder_Init(void)
{
	//第1步:开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //开启时钟3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启时钟使能		


	//第2步:引脚初始化

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //选择复用推挽模式,这样边上外设才能在引脚输出电平,普通的推挽模式是由数据寄存器输出电平的
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;   //引脚A6和A7    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	
	//第3步:配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;        //ARR值取最大值,
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1-1;      //PSC值为0,不分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	
	
	
	//第4步:初始化通道1和通道2的输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);  //给结构体赋初始值
	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;   //通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;       //滤波器
	TIM_ICInit(TIM3,&TIM_ICInitStructure);   //将通道1捕获单元初始化
	
	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;   //通道2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;       //滤波器
	TIM_ICInit(TIM3,&TIM_ICInitStructure);   //将通道1捕获单元初始化
	

	//第5步:配置编码器接口
	//注意编码器配置应该在ICInit之后,否则ICInit会覆盖掉编码器的配置
	//修改任一极性可以自动改变编码器检测旋转方向规则,同时修改两个极性则保持不变
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);


	//开启TIM3
	TIM_Cmd(TIM3,ENABLE);
}


/**
   * @brief   获取编码器的值,测量编码器位置/测量编码器速度	
   * @param   无
   * @retval  CNT值 int16_t,编码器会自动将CNT转换为有符号数
   */
//uint16_t Encoder_Get(void)
//{
//	return TIM_GetCounter(TIM3);  //返回CNT值
//}
//int16_t Encoder_Get(void)
//{
//	return TIM_GetCounter(TIM3);  //返回CNT值
//}
int16_t Encoder_Get(void)
{
	int16_t Temp;	//定义一个临时变量
	Temp = TIM_GetCounter(TIM3);     //获取CNT值并赋给临时变量
	TIM_SetCounter(TIM3,0);   //清零CNT
	return Temp;  //返回CNT值
}


