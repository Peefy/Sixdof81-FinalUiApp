
#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <stdint.h>

#include "../communication/SerialPort.h"
#include "Com.h"
#include "JY901.h"

// 传感器串口端口号
#define SENSOR_PORT1 4
#define SENSOR_PORT2 5
#define SENSOR_PORT3 6
// 传感器串口波特率
#define SENSOR_BAUD 115200

// 角度个数
#define ANGLE_COUNT 3

// 传感器个数
#define SENSOR_COUNT 3

// 自由度个数
#define FREEDOM_NUM 6

// 传感器信息个数
#define SENSOR_INFO_NUM 9

// 传感器轴个数
#define SENSOR_AXES_NUM 3

// 重力加速度
#define GRAVITY_ACC 9.8

//单位 米每名平方秒
#define MPU6050_MAX_ACC 16 * GRAVITY_ACC

// 传感器接收数据真实AD值
#define SENSOR_MAX_AD_VAL 32768.0

// 最大角速率 单位 度每秒
#define MPU6050_MAX_GYRO 2000.0

//最大角度 单位 度
#define MPU6050_MAX_ANGLE 180.0

// 加速度计和陀螺仪数据X方向索引
#define ACC_GYRO_X_INDEX 0
// 加速度计和陀螺仪数据Y方向索引
#define ACC_GYRO_Y_INDEX 1
// 加速度计和陀螺仪数据Z方向索引
#define ACC_GYRO_Z_INDEX 2

// 传感器接收缓存数据长度
#define SENSOR_BUFFER_LENGTH 10240

// 传感器数据结构
typedef struct
{
	// 横滚角
	double Roll;
	// 俯仰角
	double Pitch;
	// 偏航角
	double Yaw;
	// 陀螺仪数据
	double Gyro[SENSOR_AXES_NUM];
	// 加速度数据
	double Accel[SENSOR_AXES_NUM];
}SensorInfo_t;

class Sensor
{
public:
	Sensor(int port);
	Sensor();
	~Sensor();
	// 更新传感器数据
	SensorInfo_t GatherData();
	// 传感器是否正常
	bool IsReady();
	// 传感器串口是否打开
	bool isStart;
	// 传感器串口端口号
	int port;
	// 传感器打开串口
	bool openPort(int i, int baud = SENSOR_BAUD);
	// 传感器关闭串口
	bool closePort();
	// 校正传感器零飘
	void UpdateOffset();
private:
	// 更新数据
	SensorInfo_t ProvideSensorInfo();
	// 传感器数据
	SensorInfo_t info;
	SensorInfo_t offsetinfo;
	SensorInfo_t readInfo;
	SensorInfo_t lastinfo;
	CJY901 hardware;
	//CSerialPort serialPort;
	CCOM serialPort;
	void init(SensorInfo_t* info);
};

// 计算多个传感器的均值
SensorInfo_t GetAverageSenrorValue(SensorInfo_t* infos, size_t infonum, bool* isReady);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
