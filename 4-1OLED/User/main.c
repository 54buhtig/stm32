#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"



int main(void)
{
   
	OLED_Init();  //初始化OLED
	OLED_ShowChar(1,1,'C');               //第1行显示字符
	OLED_ShowString(1,3,"Hello World!"); 	//第1行显示字符串
//	OLED_ShowChar(1,1,' ');
	OLED_ShowChar(1,14,' ');
	OLED_ShowNum(2,1,12345,5);            //第2行显示无符号数
	OLED_ShowSignedNum(2,8,-77,2);        //第2行显示符号数
	OLED_ShowHexNum(3,1,0xABCD,4);        //第3行显示16进制
	OLED_ShowBinNum(4,1,0xABCD,16);       //第4行显示二进制
	 OLED_Clear();          //清屏函数
	while(1)  
	{
		
		
     
	}
}

