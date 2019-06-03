
#ifndef _WATER_H_
#define _WATER_H_

#include "stdint.h"

#include "../communication/SerialPort.h"

// �����Ӿ����ڶ˿ں�
#define WATER_SERIAL_NUM   8
// �����Ӿ����ڲ�����
#define WATER_SERIAL_BAUD  115200
// �����Ӿ��������ݻ��泤��
#define BUFFER_MAX 4096

// �����Ӿ���������֡��ͷ1
#define PACKAGE_HEADER1    0XAA
// �����Ӿ���������֡��ͷ2
#define PACKAGE_HEADER2    0X55
// �����Ӿ���������֡��β1
#define PACKAGE_TAIL1      0XFE
// �����Ӿ���������֡��β2
#define PACKAGE_TAIL2      0X5B

// ��������CRCУ��λ����
#define CRC_UP_INDEX      19
// ��������CRCУ��λ����
#define CRC_DOWN_INDEX    18

// ��������ϵ��
#define WATER_ANGLE_SCALE 1000.0

// �������ݳ���
#define UP_DATA_LENGTH    16
// �������ݳ���
#define DOWN_DATA_LENGTH  13
// �����Ӿ��������ݶ�ȡ���泤��
#define WATER_READ_BUFFER 10240

// �ⲿ���ڿ���ָ��
enum class WaterControlCommandInt8
{
	WATER_CTL_POWER_ON_INT8       =  0,    //����API����ָ���Դ��
	WATER_CTL_POWER_OFF_INT8      =  1,    //����API����ָ���Դ��
	WATER_CTL_CMD_RISE_INT8       =  2,    //����API����ָ�����
	WATER_CTL_CMD_DOWN_INT8       =  3,    //����API����ָ��½�
	WATER_CTL_CMD_CONNECT_INT8    =  6,    //����API����ָ�����
	WATER_CTL_CMD_DISCONNECT_INT8 =  7,    //����API����ָ��Ͽ�
	WATER_CTL_CMD_PAUSE_INT8      =  8,    //����API����ָ���ͣ
	WATER_CTL_CMD_RECOVER_INT8    =  9,    //����API����ָ���ͣ�ָ�
	WATER_CTL_CMD_CHECK_ON_INT8   =  10,   //����API����ָ����޿�
	WATER_CTL_CMD_CHECK_OFF_INT8  =  11,   //����API����ָ����޹�
	WATER_CTL_CMD_NONE_INT8       =  100,  //����API����ָ���
};

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;
	uint8_t HeadTwo;
	uint8_t Length;        
	uint8_t FrameNumber;  
	uint8_t Kind;
	uint8_t State;
	uint8_t InitState;
	uint8_t PlatformState;
	uint8_t PlatformWarning;
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
	// �Ƿ���յ�����
	bool IsRecievedData;
	// �����
	double Roll;
	// ������
	double Pitch;
	// ƫ����
	double Yaw;
	// �ⲿ����ָ��
	WaterControlCommandInt8 ControlCommand;
	// �򿪴���
	bool Open();
	// �رմ���
	bool Close();
	// �ɼ�����
	bool GatherData();
	// ���Ͳ�������
	void TestSendData();
	// ����ƽ̨����
	void SendData(double roll, double yaw, double pitch, 
		uint8_t platformState, uint8_t platformWarning);
private:
	// ����֡����
	uint8_t frameNumber;
	// ����
	CSerialPort serialPort;
protected:
	// ��������֡����
	int UpPackageLength;
	// ��������֡����
	int DownPackageLength;
	// ���ݳ�ʼ��
	void DataInit();
	// ��������
	void RenewData();
};

#endif 
