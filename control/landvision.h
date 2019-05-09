
#ifndef _LAND_VISION_H_
#define _LAND_VISION_H_

#include "stdint.h"
#include "../config/inihelper.h"
#include "../communication/SerialPort.h"

#define VISION_RECIEVE_HAEDER  'P'
#define VISION_RECIEVE_TAIL    '#'

#define VISION_SEND_HAEDER     'C'
#define VISION_SEND_TAIL       13

#define VISION_XYZ_SCALE    0.1
#define VISION_ACC_SCALE    0.1
#define VISION_ANGLE_SCALE  0.01

#define VISION_PORT        1
#define VISION_BAUDRATE    57600

#define SERVO_COUNT       6

#define POSITIVE_SIGN 0x00
#define NEGATIVE_SIGN 0xFF

#define VISION_BIT_SET(var, n)              (var) |=  (1<<(n))   
#define VISION_BIT_GET(var, n)              (((var)>>(n))&0x01)  
#define VISION_BIT_CLEAN(var, n)            (var) &= ~(1<<(n))   
#define VISION_BIT_SET_VAL(var, n, val)     ( ((val) == (1)) ? VISION_BIT_SET(var,n) : VISION_BIT_CLEAN(var,n) )

#define COM_BASE_BUFFER_MAX   4096

template <typename T>
class BaseCom
{
public:
	BaseCom(uint8_t headerOne, uint8_t headerTwo);
	~BaseCom();
	uint8_t DefaultPackageHeaderOne;
	uint8_t DefaultPackageHeaderTwo;
	int PortNumber;
	int BaudRate;
	bool IsOpen;
	bool IsRecievedData;
	bool IsNotConnect;
	bool Open(int portNumber, int baudRate);
	bool Close();
	T GetDataFromCom();
	T GatherDataFromCom();
	T Data;
private:
	BaseCom();
	CSerialPort serialPort;
	int NotConnectCount;
};

template <typename T>
BaseCom<T>::BaseCom()
{
	DefaultPackageHeaderOne = 0x55;
	DefaultPackageHeaderTwo = 0xAA;
}

template <typename T>
BaseCom<T>::BaseCom(uint8_t headerOne, uint8_t headerTwo)
{
	DefaultPackageHeaderOne = headerOne;
	DefaultPackageHeaderTwo = headerTwo;
	NotConnectCount = 0;
	IsRecievedData = false;
}

template <typename T>
BaseCom<T>::~BaseCom()
{

}

template <typename T>
bool BaseCom<T>::Open(int portNumber, int baudRate)
{
	bool result;
	int baud;
	int portnum;
	config::ReadAll(result, baud, portnum);
	PortNumber = portnum;
	BaudRate = baud;
	IsOpen = serialPort.InitPort(portnum, baud) == true;
	return IsOpen;
}

template <typename T>
bool BaseCom<T>::Close()
{
	return true;
}

template <typename T>
T BaseCom<T>::GetDataFromCom()
{
	static char uchrTemp[COM_BASE_BUFFER_MAX];
	static unsigned char chrTemp[COM_BASE_BUFFER_MAX];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;
	static int length = sizeof(T);
	auto nowlength = serialPort.GetBytesInCOM();
	unsigned char cRecved;
	for (int i = 0; i < nowlength; ++i)
	{
		serialPort.ReadChar(cRecved);
		uchrTemp[i] = cRecved;
	}
	//auto nowlength = CollectUARTData(PortNumber, uchrTemp);
	memcpy(chrTemp, uchrTemp, sizeof(unsigned char) * COM_BASE_BUFFER_MAX);
	usRxLength += nowlength;
	while (usRxLength >= length)
	{
		if (chrTemp[0] != DefaultPackageHeaderOne)
		{
			usRxLength--;
			memcpy(&chrTemp[0], &chrTemp[1], usRxLength);                        
			continue;
		}
		memcpy(&Data, &chrTemp[0], length);
		usRxLength -= length;
		memcpy(&chrTemp[0], &chrTemp[length], usRxLength);    
		IsRecievedData = true;
	}
	if (++NotConnectCount > 20)
	{
		NotConnectCount = 0;
		IsRecievedData = false;
	}
	return Data;
}

template <typename T>
T BaseCom<T>::GatherDataFromCom()
{
	if (IsOpen == false)
	{
		return Data;
	}
	// 数据帧处理相关
	static int uiRemainLength = 0;
	static unsigned long ulFrameNum = 0;
	static unsigned long ulFrameErr = 0;
	static int length = sizeof(T);
	static UCHAR chData[COM_BASE_BUFFER_MAX * 11] = {0};
	static UCHAR *pch = chData;
	int i;
	UCHAR chReadData[COM_BASE_BUFFER_MAX] = {0};
	unsigned int uiReceived = serialPort.GetBytesInCOM();
	unsigned char cRecved = 0;
	for (int i = 0; i < uiReceived; ++i)
	{
		serialPort.ReadChar(cRecved);
		chReadData[i] = cRecved;
	}
	if(uiReceived == 0)
	{
		return Data;		
	}
	memcpy(pch, chReadData, uiReceived);    //将数据置于chData[]中
	i = 0;
	int j = uiRemainLength + uiReceived - length;
	while(i <= j)
	{
		UCHAR *pData = &chData[i];
		if((pData[0] == DefaultPackageHeaderOne))
		{       	
			ulFrameNum++;
			memcpy(&Data, &pData[0], length);
			IsRecievedData = true;
			i += length;		
			continue;
		}
		else
		{
			i += 1;
		}
	}
	uiRemainLength += uiReceived - i;
	if(uiRemainLength != 0)
	{
		memcpy(chReadData, &chData[i], uiRemainLength);
		memcpy(chData, chReadData, uiRemainLength);
	}
	pch = &chData[uiRemainLength];
	return Data;
}

typedef enum 
{
	//平地
	RoadTypeFlatLand = 0,
	//山路
	RoadTypeMountain = 11,
	//卵石路
	RoadTypeStone = 21,
	//草地1
	RoadTypeGrass1 = 31,
	//草地2
	RoadTypeGrass2 = 32,
	//草地3
	RoadTypeGrass3 = 33,
	//草地4
	RoadTypeGrass4 = 34,
	//草地5
	RoadTypeGrass5 = 35,
	//柏油路
	RoadTypeAsphalt = 41,
	//水泥路
	RoadTypeCement = 51
}RoadType;

#pragma pack (1)
typedef struct 
{
	// 起始字符
	uint8_t Header;
	// 单位0.1mm
	int16_t X;
	// 单位0.1mm
	int16_t Y;
	// 单位0.1mm
	int16_t Z;
	// 单位0.1度/s
	int16_t XAcc;
	// 单位0.1度/s
	int16_t YAcc;
	// 路面类型
	uint8_t RoadTypeBefore;
	uint8_t RoadType;
	// 单位0.01度
	int16_t Pitch;
	// 单位0.01度
	int16_t Roll;
	// 控制字
	uint8_t ControlByte;
	uint8_t NoneByte;
	// 数据写入脉冲
	uint8_t CmdPcDataAcksByte;
	// 功能写入脉冲
	uint8_t FunctionsByte;
	// Crc16校验
	uint16_t Crc;
	// 停止字符
	uint8_t Tail;
}LandVisionPackage;
#pragma pack () 

#pragma pack (1)
typedef struct 
{
	// 起始字符
	uint8_t Header;
	// 单位0.1mm
	int16_t PulseCount1;
	// 单位0.1mm
	int16_t PulseCount2;
	// 单位0.1mm
	int16_t PulseCount3;
	// 单位0.1mm
	int16_t PulseCount4;
	// 单位0.1mm
	int16_t PulseCount5;
	// 单位0.1mm
	int16_t PulseCount6;
	// 状态字1
	uint8_t StateByteOne;
	// 状态字2
	uint8_t StateByteTwo;
	// 状态字3
	uint8_t StateByteThree;
	// 状态字4
	uint8_t StateByteFour;
	// Crc16校验
	uint16_t Crc;
	// 停止字符
	uint8_t Tail;
}LandVisionSendPackage;
#pragma pack () 

typedef struct 
{
	bool IsConsoleInitial;
	bool IsConsoleZero;
	bool IsServoAck;
	bool IsAlaAck;
	bool IsShockOn;
	bool IsShockOff;
	bool IsPwrOn;
	bool IsPwrOff;
	uint8_t CmdPcDataAcksByte;
	// 功能写入脉冲
	uint8_t FunctionsByte;

	inline bool GetCmdDataAck(int index)
	{
		return VISION_BIT_GET(CmdPcDataAcksByte, index) == 1;
	}

	inline bool GetFunction(int index)
	{
		return VISION_BIT_GET(FunctionsByte, index) == 1;
	}

}LandVisionRecieveState;

typedef struct 
{
	uint16_t PoleLength[SERVO_COUNT];
	bool IsServoAlarm[SERVO_COUNT];
	bool IsServoFitRange[SERVO_COUNT];
	bool IsDeclination[SERVO_COUNT];
	bool IsServoInit[SERVO_COUNT];
	bool IsLengthAlarm;
	bool IsTotalAlarm;
	bool IsServoShrinkAlarm;
	bool IsEMAlarm;
	bool IsAlarmNormal;
	bool IsAlarmHeavy;
	bool IsLockAlarm;
	bool IsServoPowerAlarm;
}LandVisionSendState;

class LandVision : public BaseCom<LandVisionPackage>
{
public:
	LandVision();
	~LandVision();
	void RenewVisionData();
	void SendVisionData();
	bool GetIsShock();
	double GetShockHzFromRoadType();
	double GetShockValFromRoadType();
	double X;
	double Y;
	double Z;
	double XAcc;
	double YAcc;
	double ZAcc;
	double Roll;
	double Yaw;
	double Pitch;	
	RoadType NowRoadType;
	// Recieve State
	LandVisionRecieveState RecieveState;
	// Send State
	LandVisionSendState SendState;
private:
	void DataInit();
protected:
	size_t RecievePackageLength;
	size_t SendPackageLength;
};



#endif 
