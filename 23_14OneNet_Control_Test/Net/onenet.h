#ifndef _ONENET_H_
#define _ONENET_H_





_Bool OneNet_DevLink(void);

void OneNet_SendData(void);
void OneNet_SendCmd(void);
void OneNet_RevPro(unsigned char *cmd);
void OneNET_Subscribe(void);
void OneNET_Publish(const char *topic, const char *msg);


#endif
