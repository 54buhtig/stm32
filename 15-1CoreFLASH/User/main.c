#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

/*
���δ����������ڲ�FLASH�洢�û�����,���ܻ���ֳ����ļ����û������ص������
�������:��keil��Target�����ó����ļ����ص��׵�ַ����ֹ��ַ
         Debugѡ��ҳ����,����Ч�ʸ�,���Ҳ�������������û�����
*/

uint8_t KeyNum;

int main(void)
{
   
	OLED_Init();  //��ʼ��OLED
	KEY_Init();
	Store_Init();

	
	OLED_ShowString(1,1,"Flag:");
	OLED_ShowString(2,1,"Data:");
	
	while(1)  
	{
		KeyNum = Key_GetNum();
		
		if(KeyNum==1)
		{
			Store_Data[1]++;
			Store_Data[2]+=2;
			Store_Data[3]+=3;
			Store_Data[4]+=4;
			Store_Save();
		}
		if(KeyNum==2)
		{
			Store_Clear();
		}
		
		
		OLED_ShowHexNum(1,7,Store_Data[0],4);
		OLED_ShowHexNum(3,1,Store_Data[1],4);
		OLED_ShowHexNum(3,7,Store_Data[2],4);
		OLED_ShowHexNum(4,1,Store_Data[3],4);
		OLED_ShowHexNum(4,7,Store_Data[4],4);
	}
	
}

