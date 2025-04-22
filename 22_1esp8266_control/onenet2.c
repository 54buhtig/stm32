
//单片机头文件
#include "stm32f10x.h"

//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"
#include "mqttkit.h"

//硬件驱动
#include "usart.h"
#include "delay.h"


//C库
#include <string.h>
#include <stdio.h>

void OneNet_RevPro_Cjson(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//协议包
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	char count = 0;  //错误打印次数
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	
	
//	cJSON * json,*json_value;     //CJSON解析,自助添加
//	cJSON * json1,*json_value1;   //CJSON解析,自助添加
	
	type = MQTT_UnPacketRecv(cmd);
	
	
	switch(type)
	{
		case MQTT_PKT_CMD:		//命令下发
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//解出topic和消息体
			if(result == 0)
			{
				
//				//对数据包req_payload进行JSON格式解析,自助添加
//				json = cJSON_Parse(req_payload);
//				
//				
//				if (!json)//如果json内容为空，则打印错误信息
//					count++;
//				else
//				{
//					json_value = cJSON_GetObjectItem(json , "LED0");//提取对应属性的数值
//				//	printf("json_value: [%s]\r\n",json_value->string);//转化为字符串数值
//				//	printf("json_value: [%d]\r\n",json_value->valueint);//转化为数值型数值
//					
//					if((json_value->valueint)==1)
//						LED0=1;
//					else if((json_value->valueint)==0)
//						LED0=0;

//				}
//				//对数据包req_payload进行JSON格式解析,自助添加
//				json1 = cJSON_Parse(req_payload);
//				if (!json1)
//					count++;
//				else
//				{
//					json_value1 = cJSON_GetObjectItem(json1 , "LED1");

//					if((json_value1->valueint)==1)//整数值
//					LED1=1;
//					else if((json_value1->valueint)==0)
//					LED1=0;
//				}
//				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//命令回复组包
				{	
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//回复命令
					MQTT_DeleteBuffer(&mqttPacket);			//删包
				}
				
	//			cJSON_Delete(json);//释放位于堆中cJSON结构体内存
	//			cJSON_Delete(json1);
			}
		
			break;
			
		case MQTT_PKT_PUBACK:			//发送Publish消息，平台回复的Ack
			
			break;
		
		default:
			result = -1;
			break;
	}
	
	ESP8266_Clear();									//清空缓存
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, '}');					//搜索'}'

	if(dataPtr != NULL && result != -1)					//如果找到了
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//转为数值形式
	}

	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
