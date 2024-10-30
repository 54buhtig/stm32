#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"



uint8_t KeyNum=0;


int main(void)
{
    

	LED_Init();
	KEY_Init();
	
	while(1)
	{

		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
				LED1_Turn();
		}
		else if(KeyNum == 2)
		{
				LED2_Turn();
		}

	}
}

