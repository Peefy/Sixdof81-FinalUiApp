
#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <stdint.h>

#include "Com.h"
#include "JY901.h"

#define SENSOR_PORT1 4
#define SENSOR_PORT2 5
#define SENSOR_PORT3 6
#define SENSOR_BAUD 9600

#define ANGLE_COUNT 3

#define SENSOR_COUNT 3

#define FREEDOM_NUM 6

#define SENSOR_INFO_NUM 9

#define SENSOR_AXES_NUM 3

#define GRAVITY_ACC 9.8

//单位 米每名平方秒
#define MPU6050_MAX_ACC 16 * GRAVITY_ACC

#define SENSOR_MAX_AD_VAL 32768.0

//单位 度每秒
#define MPU6050_MAX_GYRO 2000.0

//单位 度
#define MPU6050_MAX_ANGLE 180.0

#define ACC_GYRO_X_INDEX 0
#define ACC_GYRO_Y_INDEX 1
#define ACC_GYRO_Z_INDEX 2

typedef struct
{
	double Roll;
	double Pitch;
	double Yaw;
	double Gyro[SENSOR_AXES_NUM];
	double Accel[SENSOR_AXES_NUM];
}SensorInfo_t;

class Sensor
{
public:
	Sensor(int port);
	~Sensor();
	SensorInfo_t ProvideSensorInfo();
	bool IsReady();
	bool isStart;
	int port;
	bool openPort(int i, int baud = SENSOR_BAUD);
	bool closePort();
	void UpdateOffset();
private:
	Sensor();
	SensorInfo_t info;
	SensorInfo_t offsetinfo;
	SensorInfo_t readInfo;
	SensorInfo_t lastinfo;
	CJY901 hardware;
	char chrBuffer[2000];
	void init(SensorInfo_t* info);
};

SensorInfo_t GetAverageSenrorValue(SensorInfo_t* infos, size_t infonum, bool* isReady);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
