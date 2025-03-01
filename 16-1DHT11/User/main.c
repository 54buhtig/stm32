#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "Serial.h"



extern unsigned int rec_data[4];


int main(void)
{
   
	OLED_Init();  //��ʼ��OLED
//	Serial_Init();   //��ʼ������
	
//	OLED_ShowCN(2,1,19);
//	OLED_ShowCN(2,2,20);
//	OLED_ShowCN(1,3,21);
//	OLED_ShowCN(1,4,19);
//	OLED_ShowCN(1,5,20);
//	OLED_ShowCN(1,6,21);
	
	
	OLED_ShowCN(1,1,6);
	OLED_ShowCN(1,2,7);
	OLED_ShowChar(1,6,':');
	
	
	OLED_ShowCN(1,5,10);
	
	
	OLED_ShowCN(3,1,8);
	OLED_ShowCN(3,2,9);
	OLED_ShowChar(3,6,':');
	
	OLED_ShowCN(3,5,11);
	OLED_ShowCN(3,6,12);
	
	while(1)  
	{
		
		Delay_s(1);
		DHT11_REC_Data(); //�����¶Ⱥ�ʪ�ȵ�����
		
	    OLED_ShowNum(1,7,rec_data[2],2);
		OLED_ShowNum(1,10,rec_data[3],1);
		OLED_ShowNum(3,7,rec_data[0],2);
		OLED_ShowNum(3,10,rec_data[1],2);
     
//		Serial_Printf("�¶ȣ�%d\r\n",rec_data[2]);
//		Serial_Printf("ʪ�ȣ�%d\r\n",rec_data[0]);
//		Serial_Printf("\r\n\n");
	}
}

