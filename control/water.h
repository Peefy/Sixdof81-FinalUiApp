
#ifndef _WATER_H_
#define _WATER_H_

#include "stdint.h"

#include "../communication/SerialPort.h"

#define WATER_SERIAL_NUM   8
#define WATER_SERIAL_BAUD  115200
#define BUFFER_MAX 4096

#define PACKAGE_HEADER1    0XAA
#define PACKAGE_HEADER2    0X55
#define PACKAGE_TAIL1      0XFE
#define PACKAGE_TAIL2      0X5B

#define CRC_UP_INDEX      19
#define CRC_DOWN_INDEX    18

#define WATER_ANGLE_SCALE 1000.0

#define UP_DATA_LENGTH    14
#define DOWN_DATA_LENGTH  13

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
	bool IsRecievedData;
	double Roll;
	double Yaw;
	double Pitch;
	bool Open();
	bool Close();
	void RenewData();
	void TestSendData();
	void SendData(double roll, double yaw, double pitch);
private:
	uint8_t frameNumber;
	CSerialPort serialPort;
protected:
	int UpPackageLength;
	int DownPackageLength;
	void DataInit();
};



#endif 
