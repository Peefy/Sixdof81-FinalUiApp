
#ifndef _INERTIAL_NAVIGATION_H_
#define _INERTIAL_NAVIGATION_H_

#include "stdint.h"

#include <string>
#include <algorithm>

#include "../communication/SerialPort.h"

using namespace std;

// ս������ָ�� Tactical Technical Indicators

// ������ϵ��� λ�þ��� (RMS) ��λ m
#define SATELLITE_POSITION_ACCURACY   20.0

// ������ϵ��� �ٶȾ��� (RMS) ��λ m/s
#define SATELLITE_VELOCITY_ACCURACY   0.2

// ������ϵ��� ��̬���� (RMS) ��λ ��
#define SATELLITE_POSTURE_ACCURACY    3.0

// ������ϵ��� ���򾫶� (RMS) ��λ ��secL
#define SATELLITE_COURSE_ACCURACY     6.0

// �����Ե��� λ�þ��� (RMS) ��λ m
#define INERTIA_POSITION_ACCURACY     200

// �����Ե��� �ٶȾ��� (RMS) ��λ m/s
#define INERTIA_VELOCITY_ACCURACY     2.0

// �����Ե��� ��̬���� (RMS) ��λ ��
#define INERTIA_POSTURE_ACCURACY      3.0

// �����Ե��� ���򾫶� (RMS) ��λ ��secL
#define INERTIA_COURSE_ACCURACY       6.0

// �����ʾ��� ��λ ��/s
#define ANGULAR_RATE_ACCURACY         0.05

// �����ʲ�����Χ ��λ ��/s
#define ANGULAR_RATE_MAX              300.0

// ���϶�׼ʱ�� ��λ ����min
#define SEA_CALIBRATION_TIME          25.0

// ��ͷ��׼ʱ�� ��λ ����min
#define SHORE_CALIBRATION_TIME        10.0

// ����Ƶ��
#define SATELLITE_FREQ                "BDS:B1//B3"

// ����ͨ����
#define SATELLITE_RNSS_NUM            16

// ����ͨ����
#define SATELLITE_RDSS_NUM            10

#define RDSS_EIRP_INFO                "��λ��0-360, ����20-90"
#define RDSS_EIRP_dBW_MIN             6
#define RDSS_EIRP_dBW_MAX             16

// ������Χ
#define WORK_EARTH_RANGE     "75S-75N"
#define WORK_TEM_RANGE       "-40��-+60��"

#define DEVICE_NUMBER        "POS-GX7100"
#define COM_INTERFACE_TYPE   "RS422"
#define EE_INTERFACE         "J599/24KE35PN"
#define STADARD              "GJB4000-2000"
#define DEVICE_NAME          "���˽������Ե���ϵͳ"
#define COMPANY_NAME         "����������������о���"

#define DEVICE_TODO   "������ΪY��,������ΪZ��,������ΪX��(�������ֶ���),��װʱ,Ӧȷ�������ߵ���λ��ΪY��ָʾ����"

// �ɿ���
#define MTBF_HOURS    20000.0
#define MTTR_MINUTES  30.0

#define RS422_PORT_NUMBER          5
#define RS422_PORT_BAUDRATE        115200
#define RS422_DATA_HEAD_ONE        0x10
#define RS422_DATA_HEAD_TWO        0x2A
#define RS422_DATA_TAIL_ONE        0x10
#define RS422_DATA_TAIL_TWO        0x03
#define RS422_DATA_PACKAGE_LEGNTH  83

#define LATLON_SCALE      0.01
#define HEIGHT_SCALE      1.0
#define SPEED_SCALE       0.01
#define ACC_SCLAE         0.001
#define ANGLE_SCALE       0.01
#define ANGLE_RATE_SCALE  0.001

#define GYRO_ERR_BIT           0
#define ACC_ERR_BIT            1
#define CPU_ERR_BIT            2
#define SATELLITE_DATA_ERR_BIT 3
#define ALIGNMENT_BIT          5
#define INERTIAL_ERR_BIT       6
#define NAVIGATION_ERR_BIT     7

#define STATUS_BIT_GET(var, n)     (((var) >> (n)) & 0x01)  

#define RS422_BUFFER_LENGTH    4096

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;
	uint8_t HeadTwo;
	uint32_t UtcTime;        //1ms
	uint8_t FrameNumber;  
	int32_t Latitude;        //0.01
	int32_t Longitude;       //0.01
	int32_t Height;          //1
	int32_t EastSpeed;       //0.01
	int32_t NorthSpeed;      //0.01
	int32_t VerticalSpeed;   //0.01
	int32_t XAcc;            //0.001
	int32_t YAcc;            //0.001
	int32_t ZAcc;            //0.001
	int32_t Yaw;             //0.01
	int32_t Pitch;           //0.01
	int32_t Roll;            //0.01
	int32_t XNECoorAngularRate;    //0.001
	int32_t YNECoorAngularRate;    //0.001
	int32_t ZNECoorAngularRate;    //0.001
	int32_t XCaCoorAngularRate;    //0.001
	int32_t YCaCoorAngularRate;    //0.001
	int32_t ZCaCoorAngularRate;    //0.001
	uint8_t StateByte;
	uint8_t CheckByte;
	uint8_t TailOne;
	uint8_t TailTwo;
} RS422DataPackage;
#pragma pack () 

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

typedef enum 
{
	RS422BaudRate_38400 = 38400,
	RS422BaudRate_57600 = 57600,
	RS422BaudRate_115200 = 115200,
	RS422BaudRate_230400 = 230400,
	RS422BaudRate_460800 = 460800
}RS422BaudRate;

class InertialNavigation
{
public:
	InertialNavigation();
	~InertialNavigation();
	string GetIntroduction();
	bool Open();
	bool Close();
	void RenewData();
	int GetBufferLength();
	void SetDefaultAlignment(double lat, double lon, double height);
	void SetGpsPoleLength(double x, double y, double z);
	void SetAngleError(double pitch, double roll, double yaw);
	void SetAccOffset(double x, double y, double z);
	void SetGyroOffset(double x, double y, double z);
	void SetDataRefreshFreq(DataRefreshFreq freq);
	void SetRS422BaudRate(RS422BaudRate bps);
	void StartSwing();
	void StartGps();
	void StartSins();
	void Dispose();
	void PidOut(double * roll, double * yaw, double * pitch);
	double Roll;
	double Yaw;
	double Pitch;
	double Lon;
	double Lan;
	bool IsRecievedData;
	bool IsGyroError;
	bool IsAccError;
	bool IsCpuError;
	bool IsSatelliteDataError;
	bool IsAlignment;
	bool IsInertialError;
	bool IsNavigationError;
	bool IsRS422Start;
private:
	void DecodeData();
	RS422DataPackage data;
	bool disposed;
	void DataInit();
	CSerialPort serialPort;
protected:
	void RS422SendString(string strs);
};

#endif
