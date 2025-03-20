	#include "delay.h"	
	#include "led.h" 
	#include "key.h"
	#include "OLED.h"
	#include "dht11.h"
	#include "BH1750.h"
	#include "mq135.h"
	
	extern unsigned int rec_data[4];  //ʪ�Ⱥ��¶�
	float Light = 0; //���ն�
	u16 value;   //��������
 int main(void)
 {
	u8 t =0;
	u8 l = 0;
	u8 k = 0;
	
	SystemInit();//����ϵͳʱ��Ϊ72M
	OLED_Init();           //��ʼ����OLED��ʾ��
	OLED_Clear();           //�����Ļ
	BH1750_Init();          //��ʼ��BH1750
	MQ135_Init();

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
	
	if(t%10==0)			//ÿ100ms��ȡһ��
	{
		l++;
		k++;
		if(k%2==0)
		{
			value = MQ135_GetData(); 
		}
		if(l%10==0)
		{
			DHT11_REC_Data(); //�����¶Ⱥ�ʪ�ȵ�����
		}
		if (!i2c_CheckDevice(BH1750_Addr))
		{
			Light = LIght_Intensity();//��ȡ����ǿ��
		}
	}
	Delay_ms(10);
	t++;
	
	OLED_ShowNum(1,6,rec_data[2],2);
	OLED_ShowNum(1,9,rec_data[3],1);
	OLED_ShowNum(2,6,rec_data[0],2);
	OLED_ShowNum(2,9,rec_data[1],2);
	OLED_ShowFNum(3,10,Light);
	OLED_ShowNum(4,10,value,4);
	
	
	}
}


