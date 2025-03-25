#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Serial.h"
#include "ESP8266.h"
#include <string.h>
 
uint8_t flag;
 
int main(void)
{ 
	
	SystemInit();//����ϵͳʱ��Ϊ72M	
	LED_Init();
	LED1_On();
	Serial_Init();
	
	
	
	ESP8266_Init ();   //��ʼ��WiFiģ��ʹ�õĽӿں����裨ʹ�ô���2��

	ESP8266_StaTcpClient ();//WiFiģ������
	
	printf("Start \n");
	Delay_ms(1000);
	
 
	while (1)
	{
		switch(flag)
		{
			case 'a': LED1_On();break;//����
			
			case 'c': LED2_Off();break;//�ص�
		}	
		
	}
}



void USART2_IRQHandler(void)
{
    uint8_t ucCh;
    
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        ucCh = USART_ReceiveData(USART2);
        
        if(strEsp8266_Fram_Record.InfBit.FramLength < (RX_BUF_MAX_LEN-1))  // Ԥ��1���ֽ�д������
        {
            strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength++] = ucCh;
        }
    }
    
    if(USART_GetITStatus(USART2, USART_IT_IDLE) == SET)
    {
        // ����֡�������
        strEsp8266_Fram_Record.InfBit.FramFinishFlag = 1;
        ucCh = USART_ReceiveData(USART2);  // �������������жϱ�־λ(�ȶ�USART_SR��Ȼ���USART_DR)
        ucTcpClosedFlag = strstr(strEsp8266_Fram_Record.Data_RX_BUF, "CLOSED\r\n") ? 1 : 0;
        // Usart_SendString(USART1, q);
		LED1_Turn();
    }
        flag = ucCh;
//        USART_SendData(USART1, flag);
}



