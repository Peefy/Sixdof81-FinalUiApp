
#ifndef _LAND_VISION_H_
#define _LAND_VISION_H_

#include "stdint.h"
#include "Com.h"

#define VISION_RECIEVE_HAEDER  'P'
#define VISION_RECIEVE_TAIL    '#'

#define VISION_SEND_HAEDER     'C'
#define VISION_SEND_TAIL       13

#define VISION_XYZ_SCALE    0.1
#define VISION_ACC_SCALE    0.1
#define VISION_ANGLE_SCALE  0.01

#define VISION_PORT        3
#define VISION_BAUDRATE    57600

#define SERVO_COUNT       6

#define POSITIVE_SIGN 0x00
#define NEGATIVE_SIGN 0xFF

#define VISION_BIT_SET(var, n)              (var) |=  (1<<(n))   
#define VISION_BIT_GET(var, n)              (((var)>>(n))&0x01)  
#define VISION_BIT_CLEAN(var, n)            (var) &= ~(1<<(n))   
#define VISION_BIT_SET_VAL(var, n, val)     ( ((val) == (1)) ? VISION_BIT_SET(var,n) : VISION_BIT_CLEAN(var,n) )

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
