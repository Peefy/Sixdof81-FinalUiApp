
#ifndef _LAND_VISION_H_
#define _LAND_VISION_H_

#include "stdint.h"
#include "../config/inihelper.h"
#include "../communication/SerialPort.h"

// �Ӿ��������ݰ�ͷ
#define VISION_RECIEVE_HAEDER  'P'
// �Ӿ��������ݰ�β
#define VISION_RECIEVE_TAIL    '#'
// �Ӿ��������ݰ�ͷ
#define VISION_SEND_HAEDER     'C'
// �Ӿ��������ݰ�ͷ
#define VISION_SEND_TAIL       13

// �Ӿ���λ����������ϵ��
#define VISION_XYZ_SCALE    0.1
// �Ӿ����ٶ���������ϵ��
#define VISION_ACC_SCALE    0.1
// �Ӿ��Ƕ���������ϵ��
#define VISION_ANGLE_SCALE  0.01

// �Ӿ����ڶ˿ں�
#define VISION_PORT        1
// �Ӿ����ڲ�����
#define VISION_BAUDRATE    57600
// �����ɶ������
#define SERVO_COUNT       6

// ��������������
#define POSITIVE_SIGN 0x00
// ��������������
#define NEGATIVE_SIGN 0xFF

// �Ӿ�����λ������
#define VISION_BIT_SET(var, n)              (var) |=  (1<<(n))   
#define VISION_BIT_GET(var, n)              (((var)>>(n))&0x01)  
#define VISION_BIT_CLEAN(var, n)            (var) &= ~(1<<(n))   
#define VISION_BIT_SET_VAL(var, n, val)     ( ((val) == (1)) ? VISION_BIT_SET(var,n) : VISION_BIT_CLEAN(var,n) )

// ���ڽ������ݻ��泤��
#define COM_BASE_BUFFER_MAX   4096

template <typename T>
class BaseCom
{
public:
	BaseCom(uint8_t headerOne, uint8_t headerTwo);
	~BaseCom();
	// ���ݰ�ͷ1
	uint8_t DefaultPackageHeaderOne;
	// ���ݰ�ͷ2
	uint8_t DefaultPackageHeaderTwo;
	// ���ڶ˿ں�
	int PortNumber;
	// ���ڶ˿ں�
	int BaudRate;
	// �����Ƿ��
	bool IsOpen;
	// �Ƿ���յ�����
	bool IsRecievedData;
	// �򿪴���
	bool Open(int portNumber, int baudRate);
	// �رմ���
	bool Close();
	// ��������
	T GetDataFromCom();
	// ��������
	T GatherDataFromCom();
	// ����
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
	return Data;
}

template <typename T>
T BaseCom<T>::GatherDataFromCom()
{
	if (IsOpen == false)
	{
		return Data;
	}
	// ����֡�������
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
	memcpy(pch, chReadData, uiReceived);    //����������chData[]��
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
	//ƽ��
	RoadTypeFlatLand = 0,
	//ɽ·
	RoadTypeMountain = 11,
	//��ʯ·
	RoadTypeStone = 21,
	//�ݵ�1
	RoadTypeGrass1 = 31,
	//�ݵ�2
	RoadTypeGrass2 = 32,
	//�ݵ�3
	RoadTypeGrass3 = 33,
	//�ݵ�4
	RoadTypeGrass4 = 34,
	//�ݵ�5
	RoadTypeGrass5 = 35,
	//����·
	RoadTypeAsphalt = 41,
	//ˮ��·
	RoadTypeCement = 51
}RoadType;

#pragma pack (1)
typedef struct 
{
	// ��ʼ�ַ�
	uint8_t Header;
	// ��λ0.1mm
	int16_t X;
	// ��λ0.1mm
	int16_t Y;
	// ��λ0.1mm
	int16_t Z;
	// ��λ0.1��/s
	int16_t XAcc;
	// ��λ0.1��/s
	int16_t YAcc;
	// ·������
	uint8_t RoadTypeBefore;
	uint8_t RoadType;
	// ��λ0.01��
	int16_t Pitch;
	// ��λ0.01��
	int16_t Roll;
	// ������
	uint8_t ControlByte;
	uint8_t NoneByte;
	// ����д������
	uint8_t CmdPcDataAcksByte;
	// ����д������
	uint8_t FunctionsByte;
	// Crc16У��
	uint16_t Crc;
	// ֹͣ�ַ�
	uint8_t Tail;
}LandVisionPackage;
#pragma pack () 

#pragma pack (1)
typedef struct 
{
	// ��ʼ�ַ�
	uint8_t Header;
	// ��λ0.1mm
	int16_t PulseCount1;
	// ��λ0.1mm
	int16_t PulseCount2;
	// ��λ0.1mm
	int16_t PulseCount3;
	// ��λ0.1mm
	int16_t PulseCount4;
	// ��λ0.1mm
	int16_t PulseCount5;
	// ��λ0.1mm
	int16_t PulseCount6;
	// ״̬��1
	uint8_t StateByteOne;
	// ״̬��2
	uint8_t StateByteTwo;
	// ״̬��3
	uint8_t StateByteThree;
	// ״̬��4
	uint8_t StateByteFour;
	// Crc16У��
	uint16_t Crc;
	// ֹͣ�ַ�
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
	// ����д������
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
