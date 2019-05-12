
#ifndef _INERTIAL_NAVIGATION_H_
#define _INERTIAL_NAVIGATION_H_

#include "stdint.h"

#include <string>
#include <algorithm>

#include "../communication/SerialPort.h"
#include "Com.h"

using namespace std;

// 战术技术指标 Tactical Technical Indicators

// 卫星组合导航 位置精度 (RMS) 单位 m
#define SATELLITE_POSITION_ACCURACY   20.0

// 卫星组合导航 速度精度 (RMS) 单位 m/s
#define SATELLITE_VELOCITY_ACCURACY   0.2

// 卫星组合导航 姿态精度 (RMS) 单位 ′
#define SATELLITE_POSTURE_ACCURACY    3.0

// 卫星组合导航 航向精度 (RMS) 单位 ′secL
#define SATELLITE_COURSE_ACCURACY     6.0

// 纯惯性导航 位置精度 (RMS) 单位 m
#define INERTIA_POSITION_ACCURACY     200

// 纯惯性导航 速度精度 (RMS) 单位 m/s
#define INERTIA_VELOCITY_ACCURACY     2.0

// 纯惯性导航 姿态精度 (RMS) 单位 ′
#define INERTIA_POSTURE_ACCURACY      3.0

// 纯惯性导航 航向精度 (RMS) 单位 ′secL
#define INERTIA_COURSE_ACCURACY       6.0

// 角速率精度 单位 °/s
#define ANGULAR_RATE_ACCURACY         0.05

// 角速率测量范围 单位 °/s
#define ANGULAR_RATE_MAX              300.0

// 海上对准时间 单位 分钟min
#define SEA_CALIBRATION_TIME          25.0

// 码头对准时间 单位 分钟min
#define SHORE_CALIBRATION_TIME        10.0

// 卫星频点
#define SATELLITE_FREQ                "BDS:B1//B3"

// 卫星通道数
#define SATELLITE_RNSS_NUM            16

// 卫星通道数
#define SATELLITE_RDSS_NUM            10

// 设备数据范围
#define RDSS_EIRP_INFO                "方位角0-360, 仰角20-90"
// 设备数据最小信噪比
#define RDSS_EIRP_dBW_MIN             6
// 设备数据最大信噪比
#define RDSS_EIRP_dBW_MAX             16

// 工作范围
#define WORK_EARTH_RANGE     "75S-75N"
// 工作温度范围
#define WORK_TEM_RANGE       "-40℃-+60℃"

// 设备编号
#define DEVICE_NUMBER        "POS-GX7100"
// 设备物理层种类
#define COM_INTERFACE_TYPE   "RS422"
// 设备电气接口
#define EE_INTERFACE         "J599/24KE35PN"
// 设备标准
#define STADARD              "GJB4000-2000"
// 设备名称
#define DEVICE_NAME          "光纤捷联惯性导航系统"
// 设备公司名称
#define COMPANY_NAME         "北京航天控制仪器研究所"

// 设备安装提示
#define DEVICE_TODO   "纵向轴为Y向,垂向轴为Z向,横向轴为X向(符合左手定则),安装时,应确保捷联惯导方位轴为Y轴指示方向"

// 可靠性：小时
#define MTBF_HOURS    20000.0
// 可靠性：分钟
#define MTTR_MINUTES  30.0

// 串口422端口端口号
#define RS422_PORT_NUMBER          5
// 串口422端口波特率
#define RS422_PORT_BAUDRATE        115200
// 串口422端口数据帧包头1
#define RS422_DATA_HEAD_ONE        0x10
// 串口422端口数据帧包头2
#define RS422_DATA_HEAD_TWO        0x2A
// 串口422端口数据帧包尾1
#define RS422_DATA_TAIL_ONE        0x10
// 串口422端口数据帧包尾2
#define RS422_DATA_TAIL_TWO        0x03
// 串口422端口数据帧包长度
#define RS422_DATA_PACKAGE_LEGNTH  83

// 经纬度数据缩放系数
#define LATLON_SCALE      0.01
// 高度数据缩放系数
#define HEIGHT_SCALE      1.0
// 角速度数据缩放系数
#define SPEED_SCALE       0.01
// 加速度数据缩放系数
#define ACC_SCLAE         0.001
// 角度数据缩放系数
#define ANGLE_SCALE       0.01
// 角速率数据缩放系数
#define ANGLE_RATE_SCALE  0.001

// 惯导状态字陀螺仪故障索引
#define GYRO_ERR_BIT           0
// 惯导状态字加速度计故障索引
#define ACC_ERR_BIT            1
// 惯导状态字CPU故障索引
#define CPU_ERR_BIT            2
// 惯导状态字卫星数据故障索引
#define SATELLITE_DATA_ERR_BIT 3
// 惯导状态字数据对齐故障索引
#define ALIGNMENT_BIT          5
// 惯导状态字惯性故障索引
#define INERTIAL_ERR_BIT       6
// 惯导状态字导航故障索引
#define NAVIGATION_ERR_BIT     7

// 状态字获取
#define STATUS_BIT_GET(var, n)     (((var) >> (n)) & 0x01)  

// 串口读取数据缓冲长度
#define RS422_BUFFER_LENGTH    10240

// 校验字节索引
#define CHECK_BYTE_INDEX 80
// 校验字节开始索引
#define CHECK_BYTE_CAL_START_INDEX  2
// 校验字节结束索引
#define CHECK_BYTE_CAL_END_INDEX  79

// 默认偏航角数据零点
#define YAW_OFFSET 305.686

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;         // 1. 数据包头1
	uint8_t HeadTwo;         // 2. 数据包头2
	uint32_t UtcTime;        // 3. UTC时间 1ms
	uint8_t FrameNumber;     // 4. 数据帧数量
	int32_t Latitude;        // 5. 经度数据 0.01
	int32_t Longitude;       // 6. 纬度数据 0.01
	int32_t Height;          // 7. 高度 1.0
	int32_t EastSpeed;       // 8. 东北天东角速度 0.01
	int32_t NorthSpeed;      // 8. 东北天北角速度 0.01
	int32_t VerticalSpeed;   // 9. 东北天垂向角速度 0.01
	int32_t XAcc;            // 10. X方向线加速度 0.001
	int32_t YAcc;            // 11. Y方向线加速度 0.001
	int32_t ZAcc;            // 12. Z方向线加速度 0.001
	int32_t Yaw;             // 13. 偏航角 单位为分 0.01
	int32_t Pitch;           // 14. 俯仰角 单位为分 0.01
	int32_t Roll;            // 15. 横滚角 单位为分 0.01
	int32_t XNECoorAngularRate;    //16. 0.001
	int32_t YNECoorAngularRate;    //17. 0.001
	int32_t ZNECoorAngularRate;    //18. 0.001
	int32_t XCaCoorAngularRate;    //19. 0.001
	int32_t YCaCoorAngularRate;    //20. 0.001
	int32_t ZCaCoorAngularRate;    //21. 0.001
	uint8_t StateByte;       //22. 状态字
	uint8_t CheckByte;       //23. 校验字
	uint8_t TailOne;         //24. 数据包尾1
	uint8_t TailTwo;         //25. 数据包尾2
} RS422DataPackage;
#pragma pack () 

// 惯导数据刷新速率
typedef enum 
{
	DataRefreshFreq_1Hz = 1,
	DataRefreshFreq_2Hz = 2,
	DataRefreshFreq_5Hz = 5,
	DataRefreshFreq_10Hz = 10,
	DataRefreshFreq_20Hz = 20,
	DataRefreshFreq_50Hz = 50,
	DataRefreshFreq_100Hz = 100,
	DataRefreshFreq_200Hz = 200
}DataRefreshFreq;

// 惯导通信波特率
typedef enum 
{
	RS422BaudRate_38400 = 38400,
	RS422BaudRate_57600 = 57600,
	RS422BaudRate_115200 = 115200,
	RS422BaudRate_230400 = 230400,
	RS422BaudRate_460800 = 460800
}RS422BaudRate;

// 惯导数据接口
class InertialNavigation
{
public:
	InertialNavigation();
	~InertialNavigation();
	// 获取文字介绍
	string GetIntroduction() const;
	// 打开串口
	bool Open();
	// 打开串口
	bool Open(int port);
	// 关闭串口
	bool Close();
	// 采集数据
	bool GatherData();
	// 获取数据帧长度
	int GetBufferLength();
	// 校正偏航零点
	void JudgeYawOffset();
	// 设置默认数据对齐
	void SetDefaultAlignment(double lat, double lon, double height);
	// 设置GPS位置
	void SetGpsPoleLength(double x, double y, double z);
	// 设置角度误差
	void SetAngleError(double pitch, double roll, double yaw);
	// 设置加速度计零点
	void SetAccOffset(double x, double y, double z);
	// 设置陀螺仪零点
	void SetGyroOffset(double x, double y, double z);
	// 设置数据刷新速率
	void SetDataRefreshFreq(DataRefreshFreq freq);
	// 设置通信波特率
	void SetRS422BaudRate(RS422BaudRate bps);
	void StartSwing();
	void StartGps();
	void StartSins();
	// 释放
	void Dispose();
	// 惯导稳定PID输出
	void PidOut(double * roll, double * yaw, double * pitch);
	// 惯导稳定PID控制器初始化
	void PidInit();
	// 横滚角
	double Roll;
	// 偏航角
	double Yaw;
	// 俯仰角
	double Pitch;
	// 经度
	double Lon;
	// 纬度
	double Lan;
	// 偏航零点
	double YawOffset;
	// 是否收到数据
	bool IsRecievedData;
	// 是否陀螺仪故障
	bool IsGyroError;
	// 是否加速度计故障
	bool IsAccError;
	// 是否CPU故障
	bool IsCpuError;
	// 是否卫星数据故障
	bool IsSatelliteDataError;
	// 是否数据对齐故障
	bool IsAlignment;
	// 是否惯性故障
	bool IsInertialError;
	// 是否导航故障
	bool IsNavigationError;
	// 是否串口打开
	bool IsRS422Start;
private:
	// 更新数据
	void RenewData();
	// 解码数据
	void DecodeData();
	// 串口数据包
	RS422DataPackage data;
	// 是否释放
	bool disposed;
	// 数据初始化
	void DataInit();
	// 串口
	CSerialPort serialPort;
	//CCOM serialPort;
protected:
	// 判断校验是否成功
	bool JudgeCheckByte(char * chars);
	// 串口发送字符串
	void RS422SendString(string strs);
};

#endif
