#include "stm32f10x.h"                  // Device header
#include "Delay.h"


int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��APB2ʱ��
	
	
	
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ԭAPB2ʱ�ӣ�������

	
	//����GPIO�ṹ��Ĳ���
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0;

	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);  //��ʼ��GPIO�ṹ��

	
	GPIO_SetBits(GPIOA,GPIO_Pin_0);   //�͵�ƽ��ͨLED��ǰ���Ǹ�������AO��
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);  //�ߵ�ƽ����ͨLED��ǰ���Ǹ�������AO��

	
//	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);   //�͵�ƽ����ͨLED��ǰ������������AO��
//	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);  //�ߵ�ƽ��ͨLED��ǰ������������AO��
	
	
	while(1)
	{
//		//ʵ�ֵ���˸
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
//		Delay_ms(500);               //ͨ��SYSclk��ʵ�ֵ�
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
//		Delay_ms(500);

		
		//ʵ����ˮ��
//		GPIO_Write(GPIOA,~0x0001);     //~ȡ�����͵�ƽ��ͨ  ��������8λ����������������Ĵ����ĵ�8λ
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

