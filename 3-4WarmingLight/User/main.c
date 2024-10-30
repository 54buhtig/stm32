#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

int main(void)
{
    
	Buzzer_Init();
	
	while(1)
	{
		
		
//		Buzzer_On();
//		Delay_ms(500);
//		Buzzer_Off();
//		Delay_ms(500);		
		if(LightSensor_Get()==1)
		{
			Buzzer_On();
		}
		else
		{
			Buzzer_Off();
		}	
	}
}

