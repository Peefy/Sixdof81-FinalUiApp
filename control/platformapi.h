
#ifndef _PLATFORM_API_H_
#define _PLATFORM_API_H_

#include <stdint.h>
#include "../communication/SerialPort.h"

// ����API���ƶ˿ں�
#define API_PORT_NUMBER          6
// ����API���Ʋ�����
#define API_PORT_BAUDRATE        115200
// ����API����֡��ͷ1
#define API_DATA_HEAD_ONE        0xAA
// ����API����֡��ͷ2
#define API_DATA_HEAD_TWO        0xBB
// ����API����֡��β1
#define API_DATA_TAIL_ONE        0xCC
// ����API����֡��β2
#define API_DATA_TAIL_TWO        0xDD
// ����API����֡����
#define API_DATA_PACKAGE_LEGNTH  80

// ����API��������ϵ�� ������*0.0001=������
#define API_ANGLE_SCALE          0.001

// ƽ̨����ָ��
enum class ApiControlCommandInt32
{
	API_CTL_CMD_NONE             =  0,   //����API����ָ���
	API_CTL_CMD_RISE_INT32       =  11,  //����API����ָ�����
	API_CTL_CMD_DOWN_INT32       =  22,  //����API����ָ��½�
	API_CTL_CMD_CONNECT_INT32    =  33,  //����API����ָ�����
	API_CTL_CMD_DISCONNECT_INT32 =  44,  //����API����ָ��Ͽ�
	API_CTL_CMD_PAUSE_INT32      =  55,  //����API����ָ���ͣ
	API_CTL_CMD_RECOVER_INT32    =  66,  //����API����ָ���ͣ�ָ�
	API_CTL_CMD_POWER_ON_INT32   =  77,  //����API����ָ���Դ��
	API_CTL_CMD_POWER_OFF_INT32  =  88,  //����API����ָ���Դ��
	API_CTL_CMD_CHECK_ON_INT32   =  99,  //����API����ָ����޿�
	API_CTL_CMD_CHECK_OFF_INT32  =  100  //����API����ָ����޹�
};

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;            //1.      ��ͷ 0xAA
	uint8_t HeadTwo;            //2.      ��ͷ 0xBB
	int32_t X;                  //3-6.    X��λ�� 0.001
	int32_t Y;                  //7-10.   Y��λ�� 0.001
	int32_t Z;                  //11-14.  Z��λ�� 0.001
	int32_t Roll;               //15-18.  ����� 0.001
	int32_t Pitch;              //19-22.  ������ 0.001
	int32_t Yaw;                //23-16.  ƫ���� 0.001
	uint32_t ReservedData1[6];  //27-50.  6������λ 0.001  
	uint32_t ReservedData2[6];  //51-74.  6������λ 0.001  
	uint8_t NoneByte;           //75      ���ֽ�
	uint8_t ControlCommand;     //76.     ƽ̨����ָ�� 111���� 222�½� 333���� 444�Ͽ�
	uint8_t StateByte;          //77.     ״̬��
	uint8_t CheckByte;          //78.     ��ǰ���е��ֽڵİ�λ��
	uint8_t TailOne;            //79.     ��β 0xCC
	uint8_t TailTwo;            //80.     ��β 0xDD
} ApiDataPackage;
#pragma pack () 

class ApiControl
{
public:
	ApiControl();
	~ApiControl();
	// �򿪴���
	bool Open();
	// �رմ���
	bool Close();
	// ��������
	void GatherData();
	// �����Ƿ��
	bool IsStart;
	// �����Ƿ��յ�����֡
	bool IsRecievedData;
	// �����յ�������
	ApiDataPackage Data;
	// ƽ̨����ָ��
	ApiControlCommandInt32 ControlCommand;
private:
	// ������
	CSerialPort serialPort;
	bool JudgeCheckByte(UCHAR* pData, UCHAR check, int startindex, int length);
protected:
};

#endif
