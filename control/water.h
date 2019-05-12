
#ifndef _WATER_H_
#define _WATER_H_

#include "stdint.h"

#include "../communication/SerialPort.h"

// 海船视景串口端口号
#define WATER_SERIAL_NUM   8
// 海船视景串口波特率
#define WATER_SERIAL_BAUD  115200
// 海船视景串口数据缓存长度
#define BUFFER_MAX 4096

// 海船视景串口数据帧包头1
#define PACKAGE_HEADER1    0XAA
// 海船视景串口数据帧包头2
#define PACKAGE_HEADER2    0X55
// 海船视景串口数据帧包尾1
#define PACKAGE_TAIL1      0XFE
// 海船视景串口数据帧包尾2
#define PACKAGE_TAIL2      0X5B

// 发送数据CRC校验位索引
#define CRC_UP_INDEX      19
// 接收数据CRC校验位索引
#define CRC_DOWN_INDEX    18

// 数据缩放系数
#define WATER_ANGLE_SCALE 1000.0

// 发送数据长度
#define UP_DATA_LENGTH    14
// 接收数据长度
#define DOWN_DATA_LENGTH  13
// 海船视景串口数据读取缓存长度
#define WATER_READ_BUFFER 10240

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;
	uint8_t HeadTwo;
	uint8_t Length;        //1ms
	uint8_t FrameNumber;  
	uint8_t Kind;
	uint8_t State;
	uint8_t InitState;
	int32_t Yaw;
	int32_t Pitch;
	int32_t Roll;
	int8_t  Crc;
	uint8_t TailOne;
	uint8_t TailTwo;
} WaterUpDataPackage;
#pragma pack () 

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;
	uint8_t HeadTwo;
	uint8_t Length;        
	uint8_t FrameNumber;  
	uint8_t Kind;
	uint8_t Control;
	int32_t Yaw;
	int32_t Pitch;
	int32_t Roll;
	int8_t  Crc;
	uint8_t TailOne;
	uint8_t TailTwo;
} WaterDownDataPackage;
#pragma pack () 

class Water
{
public:
	Water();
	~Water();
	// 是否接收到数据
	bool IsRecievedData;
	// 横滚角
	double Roll;
	// 俯仰角
	double Pitch;
	// 偏航角
	double Yaw;
	// 打开串口
	bool Open();
	// 关闭串口
	bool Close();
	// 采集数据
	bool GatherData();
	// 发送测试数据
	void TestSendData();
	// 发送平台数据
	void SendData(double roll, double yaw, double pitch);
private:
	// 数据帧个数
	uint8_t frameNumber;
	// 串口
	CSerialPort serialPort;
protected:
	// 发送数据帧长度
	int UpPackageLength;
	// 接收数据帧长度
	int DownPackageLength;
	// 数据初始化
	void DataInit();
	// 更新数据
	void RenewData();
};

#endif 
