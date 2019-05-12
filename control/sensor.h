
#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <stdint.h>

#include "../communication/SerialPort.h"
#include "Com.h"
#include "JY901.h"

// ���������ڶ˿ں�
#define SENSOR_PORT1 4
#define SENSOR_PORT2 5
#define SENSOR_PORT3 6
// ���������ڲ�����
#define SENSOR_BAUD 115200

// �Ƕȸ���
#define ANGLE_COUNT 3

// ����������
#define SENSOR_COUNT 3

// ���ɶȸ���
#define FREEDOM_NUM 6

// ��������Ϣ����
#define SENSOR_INFO_NUM 9

// �����������
#define SENSOR_AXES_NUM 3

// �������ٶ�
#define GRAVITY_ACC 9.8

//��λ ��ÿ��ƽ����
#define MPU6050_MAX_ACC 16 * GRAVITY_ACC

// ����������������ʵADֵ
#define SENSOR_MAX_AD_VAL 32768.0

// �������� ��λ ��ÿ��
#define MPU6050_MAX_GYRO 2000.0

//���Ƕ� ��λ ��
#define MPU6050_MAX_ANGLE 180.0

// ���ٶȼƺ�����������X��������
#define ACC_GYRO_X_INDEX 0
// ���ٶȼƺ�����������Y��������
#define ACC_GYRO_Y_INDEX 1
// ���ٶȼƺ�����������Z��������
#define ACC_GYRO_Z_INDEX 2

// ���������ջ������ݳ���
#define SENSOR_BUFFER_LENGTH 10240

// ���������ݽṹ
typedef struct
{
	// �����
	double Roll;
	// ������
	double Pitch;
	// ƫ����
	double Yaw;
	// ����������
	double Gyro[SENSOR_AXES_NUM];
	// ���ٶ�����
	double Accel[SENSOR_AXES_NUM];
}SensorInfo_t;

class Sensor
{
public:
	Sensor(int port);
	Sensor();
	~Sensor();
	// ���´���������
	SensorInfo_t GatherData();
	// �������Ƿ�����
	bool IsReady();
	// �����������Ƿ��
	bool isStart;
	// ���������ڶ˿ں�
	int port;
	// �������򿪴���
	bool openPort(int i, int baud = SENSOR_BAUD);
	// �������رմ���
	bool closePort();
	// У����������Ʈ
	void UpdateOffset();
private:
	// ��������
	SensorInfo_t ProvideSensorInfo();
	// ����������
	SensorInfo_t info;
	SensorInfo_t offsetinfo;
	SensorInfo_t readInfo;
	SensorInfo_t lastinfo;
	CJY901 hardware;
	//CSerialPort serialPort;
	CCOM serialPort;
	void init(SensorInfo_t* info);
};

// �������������ľ�ֵ
SensorInfo_t GetAverageSenrorValue(SensorInfo_t* infos, size_t infonum, bool* isReady);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
