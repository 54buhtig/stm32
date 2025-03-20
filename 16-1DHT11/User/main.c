#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "Serial.h"

/*���ݸ�ʽ��8bitʪ����������+8bitʪ��С������
+8bit�¶���������+8bit�¶�С������
 +8bitУ���*/

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
	
	
			OLED_ShowCN(1,1,0);//��
			OLED_ShowCN(1,2,5);//��
			OLED_ShowChar(1,5,':');
			OLED_ShowChar(1,8,'.');//С����
			OLED_ShowCN(1,6,10);//��
			OLED_ShowCN(2,1,1);//ʪ
			OLED_ShowCN(2,2,5);//��
			OLED_ShowChar(2,5,':');
			OLED_ShowChar(2,8,'.');//С����
			OLED_ShowString(2,11,"%RH");//%RH
			OLED_ShowCN(3,1,2);//��
			OLED_ShowCN(3,2,3);//��
			OLED_ShowCN(3,3,4);//ǿ
			OLED_ShowCN(3,4,5);//��
			OLED_ShowChar(3,9,':');
			OLED_ShowCN(4,1,6);//��
			OLED_ShowCN(4,2,7);//��
			OLED_ShowCN(4,3,8);//��
			OLED_ShowCN(4,4,9);//��
			OLED_ShowChar(4,9,':');
	
	while(1)  
	{
		
		Delay_s(1);
		DHT11_REC_Data(); //�����¶Ⱥ�ʪ�ȵ�����
		
	    OLED_ShowNum(1,6,rec_data[2],2);
		OLED_ShowNum(1,9,rec_data[3],1);
		OLED_ShowNum(2,6,rec_data[0],2);
		OLED_ShowNum(2,9,rec_data[1],2);
     
//		Serial_Printf("�¶ȣ�%d\r\n",rec_data[2]);
//		Serial_Printf("ʪ�ȣ�%d\r\n",rec_data[0]);
//		Serial_Printf("\r\n\n");
	}
}

