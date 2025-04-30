#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "esp.h"

int main(void)
{

	LED_Init();
	LED1_On();
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
//	uart_init(115200);	 


	esp_Init();
	while(1)  
	{
//		 LED1_On();
//		 Delay_ms(2000);
//		 LED1_Off();
//		 Delay_ms(2000);

////		 alertLED = 0;
////		 delay_ms(2000);
////		 alertLED = 1;
////		 delay_ms(2000);	
//		
//		esp_Get_Data();
	}
}

