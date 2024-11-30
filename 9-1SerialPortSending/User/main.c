#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"



int main(void)
{
   
	OLED_Init();  //初始化OLED

	Serial_Init(); //初始化串口
	
//	Serial_SendByte(0x51);
	
	
//	uint8_t MyArray[] = {0x4C,0x6A,0x70};
//	
//	Serial_SendArray(MyArray,3);
	
	
//	Serial_SendString("Ljp:HelloWorld!\r\n");
	
	
//	Serial_SendNumber(12345,5);
	
//	char String[100];
//	
//	printf("Num=%d\r\n",666);
//	sprintf(String ,"Ljp is Happy %d Day \r\n",4);
//	Serial_SendString(String); 

//	Serial_Printf("Num=%d,Ljp move up\r\n",888);
	
	printf("你好，世界\r\n");
	while(1)  
	{
		
		
     
	}
}

