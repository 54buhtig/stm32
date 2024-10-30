#include "stm32f10x.h"                  // Device header
#include "Delay.h"


int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能APB2时钟
	
	
	
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);  //复原APB2时钟！！！！

	
	//配置GPIO结构体的参数
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0;

	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);  //初始化GPIO结构体

	
	GPIO_SetBits(GPIOA,GPIO_Pin_0);   //低电平导通LED，前提是负极接入AO口
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);  //高电平不导通LED，前提是负极接入AO口

	
//	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);   //低电平不导通LED，前提是正极接入AO口
//	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);  //高电平导通LED，前提是正极接入AO口
	
	
	while(1)
	{
//		//实现灯闪烁
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
//		Delay_ms(500);               //通过SYSclk来实现的
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
//		Delay_ms(500);

		
		//实现流水灯
//		GPIO_Write(GPIOA,~0x0001);     //~取反，低电平导通  ，操作低8位，操作对象是输出寄存器的低8位
//		Delay_ms(100);
//		GPIO_Write(GPIOA,~0x0002);
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0004);
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0008);
//		Delay_ms(100);
//		GPIO_Write(GPIOA,~0x0010);
//		Delay_ms(100);
//		GPIO_Write(GPIOA,~0x0020);
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0040);
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0080);
//		Delay_ms(100);


	}
}

