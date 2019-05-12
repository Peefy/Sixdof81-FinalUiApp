
#ifndef _INERTIAL_NAVIGATION_H_
#define _INERTIAL_NAVIGATION_H_

#include "stdint.h"

#include <string>
#include <algorithm>

#include "../communication/SerialPort.h"
#include "Com.h"

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

// �豸���ݷ�Χ
#define RDSS_EIRP_INFO                "��λ��0-360, ����20-90"
// �豸������С�����
#define RDSS_EIRP_dBW_MIN             6
// �豸������������
#define RDSS_EIRP_dBW_MAX             16

// ������Χ
#define WORK_EARTH_RANGE     "75S-75N"
// �����¶ȷ�Χ
#define WORK_TEM_RANGE       "-40��-+60��"

// �豸���
#define DEVICE_NUMBER        "POS-GX7100"
// �豸���������
#define COM_INTERFACE_TYPE   "RS422"
// �豸�����ӿ�
#define EE_INTERFACE         "J599/24KE35PN"
// �豸��׼
#define STADARD              "GJB4000-2000"
// �豸����
#define DEVICE_NAME          "���˽������Ե���ϵͳ"
// �豸��˾����
#define COMPANY_NAME         "����������������о���"

// �豸��װ��ʾ
#define DEVICE_TODO   "������ΪY��,������ΪZ��,������ΪX��(�������ֶ���),��װʱ,Ӧȷ�������ߵ���λ��ΪY��ָʾ����"

// �ɿ��ԣ�Сʱ
#define MTBF_HOURS    20000.0
// �ɿ��ԣ�����
#define MTTR_MINUTES  30.0

// ����422�˿ڶ˿ں�
#define RS422_PORT_NUMBER          5
// ����422�˿ڲ�����
#define RS422_PORT_BAUDRATE        115200
// ����422�˿�����֡��ͷ1
#define RS422_DATA_HEAD_ONE        0x10
// ����422�˿�����֡��ͷ2
#define RS422_DATA_HEAD_TWO        0x2A
// ����422�˿�����֡��β1
#define RS422_DATA_TAIL_ONE        0x10
// ����422�˿�����֡��β2
#define RS422_DATA_TAIL_TWO        0x03
// ����422�˿�����֡������
#define RS422_DATA_PACKAGE_LEGNTH  83

// ��γ����������ϵ��
#define LATLON_SCALE      0.01
// �߶���������ϵ��
#define HEIGHT_SCALE      1.0
// ���ٶ���������ϵ��
#define SPEED_SCALE       0.01
// ���ٶ���������ϵ��
#define ACC_SCLAE         0.001
// �Ƕ���������ϵ��
#define ANGLE_SCALE       0.01
// ��������������ϵ��
#define ANGLE_RATE_SCALE  0.001

// �ߵ�״̬�������ǹ�������
#define GYRO_ERR_BIT           0
// �ߵ�״̬�ּ��ٶȼƹ�������
#define ACC_ERR_BIT            1
// �ߵ�״̬��CPU��������
#define CPU_ERR_BIT            2
// �ߵ�״̬���������ݹ�������
#define SATELLITE_DATA_ERR_BIT 3
// �ߵ�״̬�����ݶ����������
#define ALIGNMENT_BIT          5
// �ߵ�״̬�ֹ��Թ�������
#define INERTIAL_ERR_BIT       6
// �ߵ�״̬�ֵ�����������
#define NAVIGATION_ERR_BIT     7

// ״̬�ֻ�ȡ
#define STATUS_BIT_GET(var, n)     (((var) >> (n)) & 0x01)  

// ���ڶ�ȡ���ݻ��峤��
#define RS422_BUFFER_LENGTH    10240

// У���ֽ�����
#define CHECK_BYTE_INDEX 80
// У���ֽڿ�ʼ����
#define CHECK_BYTE_CAL_START_INDEX  2
// У���ֽڽ�������
#define CHECK_BYTE_CAL_END_INDEX  79

// Ĭ��ƫ�����������
#define YAW_OFFSET 305.686

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;         // 1. ���ݰ�ͷ1
	uint8_t HeadTwo;         // 2. ���ݰ�ͷ2
	uint32_t UtcTime;        // 3. UTCʱ�� 1ms
	uint8_t FrameNumber;     // 4. ����֡����
	int32_t Latitude;        // 5. �������� 0.01
	int32_t Longitude;       // 6. γ������ 0.01
	int32_t Height;          // 7. �߶� 1.0
	int32_t EastSpeed;       // 8. �����춫���ٶ� 0.01
	int32_t NorthSpeed;      // 8. �����챱���ٶ� 0.01
	int32_t VerticalSpeed;   // 9. �����촹����ٶ� 0.01
	int32_t XAcc;            // 10. X�����߼��ٶ� 0.001
	int32_t YAcc;            // 11. Y�����߼��ٶ� 0.001
	int32_t ZAcc;            // 12. Z�����߼��ٶ� 0.001
	int32_t Yaw;             // 13. ƫ���� ��λΪ�� 0.01
	int32_t Pitch;           // 14. ������ ��λΪ�� 0.01
	int32_t Roll;            // 15. ����� ��λΪ�� 0.01
	int32_t XNECoorAngularRate;    //16. 0.001
	int32_t YNECoorAngularRate;    //17. 0.001
	int32_t ZNECoorAngularRate;    //18. 0.001
	int32_t XCaCoorAngularRate;    //19. 0.001
	int32_t YCaCoorAngularRate;    //20. 0.001
	int32_t ZCaCoorAngularRate;    //21. 0.001
	uint8_t StateByte;       //22. ״̬��
	uint8_t CheckByte;       //23. У����
	uint8_t TailOne;         //24. ���ݰ�β1
	uint8_t TailTwo;         //25. ���ݰ�β2
} RS422DataPackage;
#pragma pack () 

// �ߵ�����ˢ������
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

// �ߵ�ͨ�Ų�����
typedef enum 
{
	RS422BaudRate_38400 = 38400,
	RS422BaudRate_57600 = 57600,
	RS422BaudRate_115200 = 115200,
	RS422BaudRate_230400 = 230400,
	RS422BaudRate_460800 = 460800
}RS422BaudRate;

// �ߵ����ݽӿ�
class InertialNavigation
{
public:
	InertialNavigation();
	~InertialNavigation();
	// ��ȡ���ֽ���
	string GetIntroduction() const;
	// �򿪴���
	bool Open();
	// �򿪴���
	bool Open(int port);
	// �رմ���
	bool Close();
	// �ɼ�����
	bool GatherData();
	// ��ȡ����֡����
	int GetBufferLength();
	// У��ƫ�����
	void JudgeYawOffset();
	// ����Ĭ�����ݶ���
	void SetDefaultAlignment(double lat, double lon, double height);
	// ����GPSλ��
	void SetGpsPoleLength(double x, double y, double z);
	// ���ýǶ����
	void SetAngleError(double pitch, double roll, double yaw);
	// ���ü��ٶȼ����
	void SetAccOffset(double x, double y, double z);
	// �������������
	void SetGyroOffset(double x, double y, double z);
	// ��������ˢ������
	void SetDataRefreshFreq(DataRefreshFreq freq);
	// ����ͨ�Ų�����
	void SetRS422BaudRate(RS422BaudRate bps);
	void StartSwing();
	void StartGps();
	void StartSins();
	// �ͷ�
	void Dispose();
	// �ߵ��ȶ�PID���
	void PidOut(double * roll, double * yaw, double * pitch);
	// �ߵ��ȶ�PID��������ʼ��
	void PidInit();
	// �����
	double Roll;
	// ƫ����
	double Yaw;
	// ������
	double Pitch;
	// ����
	double Lon;
	// γ��
	double Lan;
	// ƫ�����
	double YawOffset;
	// �Ƿ��յ�����
	bool IsRecievedData;
	// �Ƿ������ǹ���
	bool IsGyroError;
	// �Ƿ���ٶȼƹ���
	bool IsAccError;
	// �Ƿ�CPU����
	bool IsCpuError;
	// �Ƿ��������ݹ���
	bool IsSatelliteDataError;
	// �Ƿ����ݶ������
	bool IsAlignment;
	// �Ƿ���Թ���
	bool IsInertialError;
	// �Ƿ񵼺�����
	bool IsNavigationError;
	// �Ƿ񴮿ڴ�
	bool IsRS422Start;
private:
	// ��������
	void RenewData();
	// ��������
	void DecodeData();
	// �������ݰ�
	RS422DataPackage data;
	// �Ƿ��ͷ�
	bool disposed;
	// ���ݳ�ʼ��
	void DataInit();
	// ����
	CSerialPort serialPort;
	//CCOM serialPort;
protected:
	// �ж�У���Ƿ�ɹ�
	bool JudgeCheckByte(char * chars);
	// ���ڷ����ַ���
	void RS422SendString(string strs);
};

#endif
