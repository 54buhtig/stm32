#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"



int main(void)
{
   
	OLED_Init();  //��ʼ��OLED
	OLED_ShowChar(1,1,'C');               //��1����ʾ�ַ�
	OLED_ShowString(1,3,"Hello World!"); 	//��1����ʾ�ַ���
//	OLED_ShowChar(1,1,' ');
	OLED_ShowChar(1,14,' ');
	OLED_ShowNum(2,1,12345,5);            //��2����ʾ�޷�����
	OLED_ShowSignedNum(2,8,-77,2);        //��2����ʾ������
	OLED_ShowHexNum(3,1,0xABCD,4);        //��3����ʾ16����
	OLED_ShowBinNum(4,1,0xABCD,16);       //��4����ʾ������
	 OLED_Clear();          //��������
	while(1)  
	{
		
		
     
	}
}

