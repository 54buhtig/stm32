#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

/*
本次代码是利用内部FLASH存储用户数据,可能会出现程序文件与用户数据重叠的情况
解决方法:在keil的Target中设置程序文件下载的首地址和终止地址
         Debug选择页擦除,下载效率高,而且不会容易清除掉用户数据
*/

uint8_t KeyNum;

int main(void)
{
   
	OLED_Init();  //初始化OLED
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

