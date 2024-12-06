#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"


#define  MPU6050_ADDRESS  0xD0

/**
   * @brief   带有超时退出机制的CheakEvent函数
   * @param   I2Cx:可以时I2C1和I2C2
   EVENT:可以是如下选项
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED           : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED              : EV1
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED     : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED        : EV1
  *     @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED            : EV1
  *     @arg I2C_EVENT_SLAVE_BYTE_RECEIVED                         : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)      : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)    : EV2
  *     @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)   : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL) : EV3
  *     @arg I2C_EVENT_SLAVE_ACK_FAILURE                           : EV3_2
  *     @arg I2C_EVENT_SLAVE_STOP_DETECTED                         : EV4
  *     @arg I2C_EVENT_MASTER_MODE_SELECT                          : EV5
  *     @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED            : EV6     
  *     @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED               : EV6
  *     @arg I2C_EVENT_MASTER_BYTE_RECEIVED                        : EV7
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING                    : EV8
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED                     : EV8_2
  *     @arg I2C_EVENT_MASTER_MODE_ADDRESS10                       : EV9
   * @retval
   */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout=10000;
	while(I2C_CheckEvent(I2Cx,I2C_EVENT)!=SUCCESS)  //检测EV5事件
	{
		Timeout--;
		if(Timeout==0)
		{
			break;  //跳出循环  简单的计次计时,超时退出的机制
//			return ; //跳出整个函数
			//在工程项目中这里应该加入相应的错误处理操作,比如打印错误日志、系统复位、紧急停机
		}
	}
}




/**
   * @brief     在指定地址写入数据
   * @param     RegAddrss:要写入的寄存器地址
                Data:需要写入的数据
   * @retval    无
   */
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{

	I2C_GenerateSTART(I2C2,ENABLE);  //初始化条件
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);  //检测EV5事件
	
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);//发送从机地址
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);  //检测EV6事件
	
	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);  //检测EV8事件
	
	I2C_SendData(I2C2,Data);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);  //检测EV8_2事件
		
	I2C_GenerateSTOP(I2C2,ENABLE);   //终止条件
	
}



/**
   * @brief     在指定地址读取数据
   * @param     RegAddrss:要读取的寄存器地址
   * @retval    返回读取的数据
   */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;

	I2C_GenerateSTART(I2C2,ENABLE);  //初始化条件
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);  //检测EV5事件
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);//发送从机地址
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);  //检测EV6事件
	
	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);  //检测EV8_2事件

	I2C_GenerateSTART(I2C2,ENABLE);  //重复初始化条件
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);  //检测EV5事件

	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);//发送从机地址
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);  //检测EV6事件


	I2C_AcknowledgeConfig(I2C2,DISABLE);//只接收一个字节时,提前配置Ack,将Ack置0
	I2C_GenerateSTOP(I2C2,ENABLE);   //提前设置停止条件


	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);  //检测EV7事件
	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2,ENABLE);  //将Ack置1,因为默认下Ack就是置1,为了方便指定地址接收多字节
	return Data;
}


/**
   * @brief  MPU6050模块的初始化
   * @param  无
   * @retval 无
   */
void MPU6050_Init(void)
{
		
	//第1步：开启I2C和GPIO引脚的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	//第2步：将引脚设为开漏复用模式
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  //开漏输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_11 ;   //引脚B10 和引脚B11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//第3步:配置I2C内部的参数
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	I2C_InitStructure.I2C_AcknowledgedAddress= I2C_AcknowledgedAddress_7bit;  //7位地址
	I2C_InitStructure.I2C_ClockSpeed= 50000;  //50Khz
	I2C_InitStructure.I2C_DutyCycle= I2C_DutyCycle_2 ; 
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;  //从机地址
	I2C_Init(I2C2,&I2C_InitStructure);
	
	//第4步:使能I2C
	I2C_Cmd(I2C2,ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);   //电源1配置给0x01,选择X轴陀螺仪作为时钟,关闭睡眠模式
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);   //电源2配置给0x00,待机关闭
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);   //采样率分频, 10分频
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);       //MPU6050配置, 外部同步关闭,数字低通滤波给110
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);  //关闭陀螺仪自测, 量程选最大
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18); //关闭加速器自测, 量程选最大,关闭高通滤波
}


uint8_t MPU6050_GetID(void)
{
	return  MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
   * @brief    读取MPU6050加速度和角速度寄存器的数据
   * @param    参数是存放加速度和角速度X,Y,Z轴的数据地址
   * @retval   无
   */
void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,
				     int16_t* GyroX,int16_t* GyroY,int16_t* GyroZ)
{
	uint8_t DataH,DataL;
	
	//加速度X轴
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH<<8)  |  DataL;

	//加速度Y轴
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH<<8)  |  DataL;

	//加速度Z轴
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH<<8)  |  DataL;

	//角速度X轴
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH<<8)  |  DataL;

	//角速度Y轴
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH<<8)  |  DataL;

	//角速度Z轴
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	*GyroZ = (DataH<<8)  |  DataL;

}

















