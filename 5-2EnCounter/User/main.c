#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "EnCoder.h"

int16_t Num;

int main(void)
{
   
	OLED_Init();  //��ʼ��OLED
	EnCoder_Init(); //��ʼ����ת������
	OLED_ShowString(1,1,"Num:"); 	//��1����ʾ�ַ���

	while(1)  
	{
		Num+=EnCoder_Get();
//		Num = EnCoder_Get();
		OLED_ShowSignedNum(1,7,Num,5);
	}
}

