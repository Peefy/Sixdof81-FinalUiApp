
#ifndef _ILLUSION_H_ 
#define _ILLUSION_H_ 

#include <string>
#include <stdint.h>
#include <math.h>

#include "udp.h"

using namespace std;

// UDPͨ�ŶԷ��Ķ˿ں�
#define UDP_PORT        9000
// UDPͨ�ŶԷ���IP��ַ
#define UDP_IP_STRING   "192.168.0.104"
// UDPͨ������Ķ˿ں�
#define UDP_SELF_PORT   6666
// UDPͨ�������IP��ַ
#define UDP_SELF_IP_STRING   "192.168.0.123"

// ͨ�Ž��ջ������󳤶�
#define ILLUSION_RECIEVE_BUFFER_MAX   1024
// ͨ�Ž��ջ������ʼ��־
#define ILLUSION_FLAG_START_INT32     999
// ͨ�Ž��ջ����������־
#define ILLUSION_FLAG_END_INT32       888

// ����Ӿ�����ָ���
#define ILLUSION_CTL_CMD_NONE_INT32        0
// ����Ӿ�����ָ���ʼ
#define ILLUSION_CTL_CMD_START_INT32       111000
// ����Ӿ�����ָ�ֹͣ
#define ILLUSION_CTL_CMD_STOP_INT32        777000
// ����Ӿ�����ָ�����
#define ILLUSION_CTL_CMD_CONNECT_INT32     222000
// ����Ӿ�����ָ��ѻ�
#define ILLUSION_CTL_CMD_DISCONNECT_INT32  333000
// ����Ӿ�����ָ���ͣ
#define ILLUSION_CTL_CMD_PAUSE_INT32       555000
// ����Ӿ�����ָ��ָ�
#define ILLUSION_CTL_CMD_RECOVER_INT32     666000

// ���UDP����֡�����峤��
#define ILLUSION_BUFFER_LENGTH  1024

// ���������λ������ϵ��
#define ILLUSION_XYZ_SCALE      0.001
// ��������߼��ٶ�����ϵ��
#define ILLUSION_ACC_SCALE      0.001
// ������ݽǶ�����ϵ��
#define ILLUSION_ANGLE_SCALE    0.001
// ������ݽ��ٶ�����ϵ��
#define ILLUSION_SPEED_SCALE    (0.002 * 3.1415926 / 180.0)
// �������������������ϵ��
#define ILLUSION_OTHER_SCALE    0.001

// ֱ��X�߼��ٶ�����ϵ��
#define DIRECT_ACC_X_SCALE        10.0
// ֱ��Y�߼��ٶ�����ϵ��
#define DIRECT_ACC_Y_SCALE        10.0
// ֱ��Z�߼��ٶ�����ϵ��
#define DIRECT_ACC_Z_SCALE        10.0
// ֱ�غ�����ٶ�����ϵ��
#define DIRECT_SPEED_ROLL_SCALE   2.0
// ֱ�ظ������ٶ�����ϵ��
#define DIRECT_SPPED_PITCH_SCALE  2.0
// ֱ��ƫ�����ٶ�����ϵ��
#define DIRECT_SPEED_YAW_SCALE    2.0
// ֱ�غ��������ϵ��
#define DIRECT_ANGLE_ROLL_SCALE   2.0
// ֱ�ظ���������ϵ��
#define DIRECT_ANGLE_PITCH_SCALE  1.0
// ֱ��ƫ��������ϵ��
#define DIRECT_ANGLE_YAW_SCALE    2.0

// ������ݲ�����������
#define ILLUSION_DT 0.047

// ��������޷�����
#define ILLUSION_RANGE(x, min, max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))
// ����Ƕ��������ֵ
#define ILLUSION_MAX_ANGLE_DEG     180
// ������ٶ��������ֵ
#define ILLUSION_MAX_ANGLE_SPEED   0.12
// �����λ�����������ٶ�
#define ILLUSION_MAX_XYZ_ACC       20

// ���ֱ�ط�ʽָ��
#define ILLUSION_IS_DIRECT_CONTROL_INT32   999 

// �����������ٶ�
#define EARTH_G 9.8
// ���ģ���������ٶ�
#define ILLUSION_NORMAL_ACC      (0.02 * EARTH_G)

// ��ɶ���������
#define ILLUSION_SHOCK_MAX_AIR_SPEED 100.0
// ��ɶ������Ƶ��
#define ILLUSION_SHOCK_MAX_HZ        8.0

// �������ģ����ģ��
typedef enum 
{
	// ��30:Ĭ��ֵ
	PLANE_TYPE_SU30 = 0,
	// ��27
	PLANE_TYPE_SU27 = 1,
	// ��15
	PLANE_TYPE_J15 = 2,
	// ��10
	PLANE_TYPE_J10 = 3,
	// ֱ9
	PLANE_TYPE_Z9 = 4,
	// ��30
	PLANE_TYPE_S30 = 5
}PlaneType;

// ƽ̨��������
typedef enum 
{
	// ����
	WARING_TYPE_NORMAL = 888,
	// ��е����
	WARING_TYPE_MECHANICAL = 111,
	// ���ݹ���
	WARING_TYPE_DATA = 222,
	// ���й���
	WARING_TYPE_RUN = 333,
	// �߼�����
	WARING_TYPE_LOGICAL = 444,
}PlatformWaringType;

// �����������֡
#pragma pack (1)
typedef struct
{
	int flagstart;     // ���ݰ���ͷ(999)
	int zxs;           //1. �ɻ��ڻ�����ϵXb������߼��ٶ�   (+/-3.3f ��/��2)
	int zxus;          //2. �ɻ��ڻ�����ϵXb������߼��ٶ�   (+/-3.3f ��/��2)
	int hxs;           //3. �ɻ��ڻ�����ϵZb������߼��ٶ�   (+/-3.3f ��/��2)
	int hxas;          //4. �ɻ�����Ǽ��ٶ�                (+/-3.3f ��/��2)
	int cxs;           //5. �ɻ������Ǽ��ٶ�                (+/-3.3f ��/��2)
	int cxas;          //6. �ɻ�ƫ���Ǽ��ٶ�                (+/-3.3f ��/��2)
	int fyjs;          //7. �ɻ��ٶ��ڻ�����ϵXb����ķ���   (+/-3.3f ��/��)
	int fyjas;         //8. �ɻ��ٶ��ڻ�����ϵYb����ķ���   (+/-3.3f ��/��)
	int cqjs;          //9. �ɻ��ٶ��ڻ�����ϵZb����ķ���   (+/-3.3f ��/��)
	int cqjas;         //10. �ɻ�������ٶ�   (+/-3.3f ��/��)
	int hxjs;          //11. �ɻ��������ٶ�   (+/-3.3f ��/��)
	int hxjas;         //12. �ɻ�ƫ�����ٶ�   (+/-3.3f ��/��)
	int fyj;           //13. �ɻ�������       (+/-3.3f ��)
	int cqj;           //14. �ɻ������       (+/-3.3f ��)
	int phj;           //15. �ɻ�������ظ߶�   (+/-3.3f ��)
	int scl;           //16. �ɻ�ǰ����ܽӵص��֧����(����)   (+/-3.3f ǧkgf)
	int txzt;          //17. �ɻ�������ܽӵص��֧����(����) (+/-3.3f ǧkgf)
	int mh;            //18. �ɻ�������ܽӵص��֧����(����) (+/-3.3f ǧkgf)
	int percent;       //19. �ɻ�ǰ����ܽӵص�Ľӵ��ٶ�(����) (+/-3.3f ��/��)
	int hxfl;          //20. �ɻ�������ܽӵص�Ľӵ��ٶ�(����) (+/-3.3f ��/��)
	int acxfl;         //21. �ɻ�������ܽӵص�Ľӵ��ٶ�(����) (+/-3.3f ��/��)
	int zxrs;          //22. �ɻ��ӵش����ٶ� (+/-3.3f ��/��)
	int hxrs;          //23. ��ɲ����        (+/-3.3f ǧkgf)
	int cxrs;          //24. ��ɲ����        (+/-3.3f ǧkgf)
	int by1;           //25. �����ڻ�����ϵXb����������ٶ� (+/-3.3f ��/��)
	int by2;           //26. �����ڻ�����ϵYb����������ٶ� (+/-3.3f ��/��)
	int by3;           //27. �����ڻ�����ϵZb����������ٶ� (+/-3.3f ��/��)
	int by4;           //28. �����ڻ�����ϵXb��������ż��ٶ� (+/-3.3f ��/��2)
	int by5;           //29. �����ڻ�����ϵYb��������ż��ٶ� (+/-3.3f ��/��2)
	int by6;           //30. �����ڻ�����ϵZb��������ż��ٶ� (+/-3.3f ��/��2)
	int by7;           //31. ǰ�����֧��ѹ����         (+/-3.3f ��)
	int by8;           //32. �������֧��ѹ����         (+/-3.3f ��)
	int by9;           //33. �������֧��ѹ����         (+/-3.3f ��)
	int by10;          //34. ����λ��                  (+/-3.3f ��)
	int by11;          //35. �󷢶���ת�ٰٷ���         (+/-3.3f 0.0-1.0)
	int by12;          //36. �ҷ�����ת�ٰٷ���         (+/-3.3f 0.0-1.0)
	int by13;          //37. ǰ�����λ��               (+/-3.3f 0.0��-90.0��)
	int by14;          //38. �������λ��               (+/-3.3f 0.0��-90.0��)
	int by15;          //39. �������λ��               (+/-3.3f 0.0��-90.0��)
	int by16;          //40. ����ϵͳ�����־           (+/-3.3f 1.0:����;0.0:�ⶳ)
	int by17;          //41. �ܶ����־                 (+/-3.3f 1.0:����;0.0:�ⶳ)
	int by18;          //42. �ɻ��ڵ����־             (+/-3.3f 1.0:����;0.0:����)
	int by19;          //43. ǰ��������ϱ�־           (+/-3.3f 1.0:����;0.0:����)
	int by20;          //44. ����������ϱ�־           (+/-3.3f 1.0:����;0.0:����)
	int by21;          //45. ����������ϱ�־           (+/-3.3f 1.0:����;0.0:����)
	int by22;          //46. �󷢶�������־           (+/-3.3f 1.0:���;0.0:Ϩ��)
	int by23;          //47. �ҷ���������־           (+/-3.3f 1.0:���;0.0:Ϩ��)
	int by24;          //48. �˶����ñ�־               (+/-3.3f 1.0:��;0.0:��)
	int by25;          //49. ����ƽ�ɱ�־               (+/-3.3f 1.0:��;0.0:��)
	int by26;          //50. �������                  (���Ϊ1.0ƽ̨����,����Ϊ0.0)
	int by27;          //51. ������λ��
	int by28;          //52. У������
	int by29;          //53. �����
	int by30;          //54. �ɻ�ӭ��(��)
	int by31;          //55. ����ϵ��
	int by32;          //56. �ɻ�����λ��
	int by33;          //57. ƽ������λ��(��)
	int by34;          //58. �ܵ�����ֲڶ�
	int by35;          //59. 999.0���������
	int by36;          //60. ��־(����111000,ֹͣ777000,����222000,�ѻ�333000,��ͣ555000,�ָ�666000)
	int uPlaneType;	   //61. �ɻ�����  0:��30  1����27  2����15  3����10  4:ֱ9
	int uAccebx_deg;   //62. ƽ̨�����                      -20.0~ 20.0���ȣ�    (+/-3.3f)
	int uAcceby_deg;   //63. ƽ̨������                      -20.0~ 20.0���ȣ�    (+/-3.3f)
	int uAccebz_deg;   //64. ƽ̨ƫ����                      -20.0~ 20.0���ȣ�    (+/-3.3f)
	int uAccebx_degs;  //65. ƽ̨������ٶ�                  -22.0~ 22.0����/�룩  (+/-3.3f)
	int uAcceby_degs;  //66. ƽ̨�������ٶ�                  -22.0~ 22.0����/�룩  (+/-3.3f)
	int uAccebz_degs;  //67. ƽ̨ƫ�����ٶ�                  -22.0~ 22.0����/�룩  (+/-3.3f)
	int uAccebx_degss; //68. ƽ̨����Ǽ��ٶ�                -150.0~ 150.0����/��2��  (+/-3.3f)
	int uAcceby_degss; //69. ƽ̨�����Ǽ��ٶ�                -150.0~ 150.0����/��2��  (+/-3.3f)
	int uAccebz_degss; //70. ƽ̨ƫ���Ǽ��ٶ�                -150.0~ 150.0����/��2��  (+/-3.3f)
	int uAcceVx_mss;   //71. ƽ̨�ڻ�����ϵX������߼��ٶ�    -0.6 ~ 0.6 ��g��      (+/-3.3f)
	int uAcceVy_mss;   //72. ƽ̨�ڻ�����ϵY������߼��ٶ�    -0.6 ~ 0.6 ��g��      (+/-3.3f)
	int uAcceVz_mss;   //73. ƽ̨�ڻ�����ϵZ������߼��ٶ�    -0.6 ~ 0.6 ��g��      (+/-3.3f)
	int flagend;       //74. ���ݰ���β (888)
}IllusionPackage;
#pragma pack () 

// ����ش�����֡
#pragma pack (1)
typedef struct
{
	int flagstart;     // ���ݰ���ͷ(999)
	int iswarning;     //1. ƽ̨�Ƿ���� 111������ 0���޹���
	int status;        //2. ƽ̨״̬ 000:��ײ� 111:����λ 222:��ͣ�˶� 333:�����˶� 444:�������� 555:�����½�
	int x;             //3. ƽ̨x�������˶�λ�ƣ���λ 0.001mm
	int y;             //4. ƽ̨y�������˶�λ�ƣ���λ 0.001mm
	int z;             //5. ƽ̨z�������˶�λ�ƣ���λ 0.001mm
	int roll;          //6. ƽ̨����ǣ���λ 0.001��
	int yaw;           //7. ƽ̨ƫ���ǣ���λ 0.001��
	int pitch;         //8. ƽ̨�����ǣ���λ 0.001��
	int cqjs;          //9. ����
	int cqjas;         //10. ����
	int hxjs;          //11. ����
	int hxjas;         //12. ����
	int fyj;           //13. ����
	int cqj;           //14. ����
	int flagend;       // ���ݰ���β (888)
}IllusionSendPackage;
#pragma pack () 

// �������������
class IllusionDataAdapter
{
public:
	IllusionDataAdapter();
	~IllusionDataAdapter();
	// ���õ�ǰ�ɻ���̬
	void SetPoseAngle(double roll, double pitch, double yaw);
	// ���ղ���������
	void RenewData();
	// ��������
	void SendData();
	// ��������
	void SendData(bool iswarning, int status, double x, double y, double z, double roll, double yaw, double pitch);
	// ��ȡƽ̨����ָ��
	int GetControlCommand() const;
	// �Ƿ��Ǵ������ģʽ
	bool IsIllusionControl() const;
	// �Ƿ�������
	bool IsEanbleShock() const;
	// ��ȡ����Ƶ��
	double GetShockHz();
	// �Ƿ��յ�����
	bool IsRecievedData;
	// �����
	double Roll;
	// ������
	double Pitch;
	// ƫ����
	double Yaw;
	// X������λ��
	double X;
	// Y������λ��
	double Y;
	// Z������λ��
	double Z;
	// ������ٶ�
	double RollSpeed;
	// ƫ�����ٶ�
	double YawSpeed;
	// �������ٶ�
	double PitchSpeed;
	// X�������ٶ�
	double XSpeed;
	// Y�������ٶ�
	double YSpeed;
	// Z�������ٶ�
	double ZSpeed;
	// ����Ǽ��ٶ�
	double RollAcc;
	// ƫ���Ǽ��ٶ�
	double YawAcc;
	// �����Ǽ��ٶ�
	double PitchAcc;
	// X�����߼��ٶ�
	double XAcc;
	// Y�����߼��ٶ�
	double YAcc;
	// Z�����߼��ٶ�
	double ZAcc;
	// �Ƿ���ֱ��ģʽ
	bool IsDirectControl;
	// ����ģ������
	PlaneType planeType;
private:
	// ƽ̨��ǰ�����
	double platformRoll;
	// ƽ̨��ǰ������
	double platformPitch;
	// ƽ̨��ǰƫ����
	double platformYaw;
	// �����������
	IllusionPackage Data;
	// �����������
	IllusionSendPackage SendToData;
	// �����������֡����
	int DataPackageLength;
	// �����������֡����
	int SendDataPackageLength;
	// ��������
	void RenewInnerData();
	// ���ļ���ȡIP�Ͷ˿ں�
	void ReadIpAndPortFromFile();
	// ���ļ���ȡֱ������ϵ��
	void ReadDeirectCtlScaleFromFile();
protected:
	// ���ݳ�ʼ��
	void DataInit();
	// ����UDPͨ�Ŷ˿ں�
	int SelfPort;
	// ����UDPͨ��IP
	string SelfIp;
	// �Է�UDPͨ�Ŷ˿ں�
	int VisionPort;
	// �Է�UDPͨ��IP
	string VisionIp;
private:
	// ֱ��X���ٶ�����
	double directAccXScale;
	// ֱ��X���ٶ�����
	double directAccYScale;
	// ֱ��X���ٶ�����
	double directAccZScale;
	// ֱ�غ�����ٶ�����
	double directSpeedRollScale;
	// ֱ�ظ������ٶ�����
	double directSpeedPitchScale;
	// ֱ��ƫ�����ٶ�����
	double directSpeedYawScale;
	// ֱ�غ��������	
	double directAngleRollScale;
	// ֱ�ظ���������
	double directAnglePitchScale;
	// ֱ��ƫ��������
	double directAngleYawScale;
};

#endif // !

