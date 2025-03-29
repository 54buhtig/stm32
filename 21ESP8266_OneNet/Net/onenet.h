#ifndef _ONENET_H_
#define _ONENET_H_
#include "sys.h"  


//#define MQTT_PUBLISH_ID			30

_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

void OneNet_RevPro(unsigned char *cmd);

unsigned char MqttOnenet_Savedata(char *t_payload);

#endif
