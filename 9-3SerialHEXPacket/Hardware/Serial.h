#ifndef __SERIAL__H_
#define __SERIAL__H_


#include <stdio.h>

extern uint8_t  Serial_TxPacket[];   //申明数组不需要加数组长度
extern uint8_t  Serial_RxPacket[];    


void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t* Array, uint16_t Length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t Number,uint8_t Length );
void Serial_Printf(char* format,...);
uint8_t Serial_GetRxFlag(void);
void Serial_SendPacket(void);


#endif
