
#ifndef _ILLUSION_H_ 
#define _ILLUSION_H_ 

#include <string>
#include <stdint.h>
#include <math.h>

#include "udp.h"

using namespace std;

// UDP通信对方的端口号
#define UDP_PORT        9000
// UDP通信对方的IP地址
#define UDP_IP_STRING   "192.168.0.104"
// UDP通信自身的端口号
#define UDP_SELF_PORT   6666
// UDP通信自身的IP地址
#define UDP_SELF_IP_STRING   "192.168.0.123"

// 通信接收缓冲包最大长度
#define ILLUSION_RECIEVE_BUFFER_MAX   1024
// 通信接收缓冲包开始标志
#define ILLUSION_FLAG_START_INT32     999
// 通信接收缓冲包结束标志
#define ILLUSION_FLAG_END_INT32       888

// 错觉视景控制指令：空
#define ILLUSION_CTL_CMD_NONE_INT32        0
// 错觉视景控制指令：开始
#define ILLUSION_CTL_CMD_START_INT32       111000
// 错觉视景控制指令：停止
#define ILLUSION_CTL_CMD_STOP_INT32        777000
// 错觉视景控制指令：联机
#define ILLUSION_CTL_CMD_CONNECT_INT32     222000
// 错觉视景控制指令：脱机
#define ILLUSION_CTL_CMD_DISCONNECT_INT32  333000
// 错觉视景控制指令：暂停
#define ILLUSION_CTL_CMD_PAUSE_INT32       555000
// 错觉视景控制指令：恢复
#define ILLUSION_CTL_CMD_RECOVER_INT32     666000

// 错觉UDP数据帧包缓冲长度
#define ILLUSION_BUFFER_LENGTH  1024

// 错觉数据线位移缩放系数
#define ILLUSION_XYZ_SCALE      0.001
// 错觉数据线加速度缩放系数
#define ILLUSION_ACC_SCALE      0.001
// 错觉数据角度缩放系数
#define ILLUSION_ANGLE_SCALE    0.001
// 错觉数据角速度缩放系数
#define ILLUSION_SPEED_SCALE    (0.002 * 3.1415926 / 180.0)
// 错觉数据其他数据缩放系数
#define ILLUSION_OTHER_SCALE    0.001

// 直控X线加速度缩放系数
#define DIRECT_ACC_X_SCALE        10.0
// 直控Y线加速度缩放系数
#define DIRECT_ACC_Y_SCALE        10.0
// 直控Z线加速度缩放系数
#define DIRECT_ACC_Z_SCALE        10.0
// 直控横滚角速度缩放系数
#define DIRECT_SPEED_ROLL_SCALE   2.0
// 直控俯仰角速度缩放系数
#define DIRECT_SPPED_PITCH_SCALE  2.0
// 直控偏航角速度缩放系数
#define DIRECT_SPEED_YAW_SCALE    2.0
// 直控横滚角缩放系数
#define DIRECT_ANGLE_ROLL_SCALE   2.0
// 直控俯仰角缩放系数
#define DIRECT_ANGLE_PITCH_SCALE  1.0
// 直控偏航角缩放系数
#define DIRECT_ANGLE_YAW_SCALE    2.0

// 错觉数据采样数据周期
#define ILLUSION_DT 0.047

// 错觉数据限幅函数
#define ILLUSION_RANGE(x, min, max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))
// 错觉角度数据最大值
#define ILLUSION_MAX_ANGLE_DEG     180
// 错觉角速度数据最大值
#define ILLUSION_MAX_ANGLE_SPEED   0.12
// 错觉线位移数据最大加速度
#define ILLUSION_MAX_XYZ_ACC       20

// 错觉直控方式指令
#define ILLUSION_IS_DIRECT_CONTROL_INT32   999 

// 地球重力加速度
#define EARTH_G 9.8
// 错觉模型正常加速度
#define ILLUSION_NORMAL_ACC      (0.02 * EARTH_G)

// 起飞抖振最大空速
#define ILLUSION_SHOCK_MAX_AIR_SPEED 100.0
// 起飞抖振最大频率
#define ILLUSION_SHOCK_MAX_HZ        8.0

// 错觉飞行模拟器模型
typedef enum 
{
	// 苏30:默认值
	PLANE_TYPE_SU30 = 0,
	// 苏27
	PLANE_TYPE_SU27 = 1,
	// 歼15
	PLANE_TYPE_J15 = 2,
	// 歼10
	PLANE_TYPE_J10 = 3,
	// 直9
	PLANE_TYPE_Z9 = 4,
	// 苏30
	PLANE_TYPE_S30 = 5
}PlaneType;

// 平台报警代码
typedef enum 
{
	// 正常
	WARING_TYPE_NORMAL = 888,
	// 机械故障
	WARING_TYPE_MECHANICAL = 111,
	// 数据故障
	WARING_TYPE_DATA = 222,
	// 运行故障
	WARING_TYPE_RUN = 333,
	// 逻辑故障
	WARING_TYPE_LOGICAL = 444,
}PlatformWaringType;

// 错觉接收数据帧
#pragma pack (1)
typedef struct
{
	int flagstart;     // 数据包标头(999)
	int zxs;           //1. 飞机在机体轴系Xb方向的线加速度   (+/-3.3f 米/秒2)
	int zxus;          //2. 飞机在机体轴系Xb方向的线加速度   (+/-3.3f 米/秒2)
	int hxs;           //3. 飞机在机体轴系Zb方向的线加速度   (+/-3.3f 米/秒2)
	int hxas;          //4. 飞机横滚角加速度                (+/-3.3f 度/秒2)
	int cxs;           //5. 飞机俯仰角加速度                (+/-3.3f 度/秒2)
	int cxas;          //6. 飞机偏航角加速度                (+/-3.3f 度/秒2)
	int fyjs;          //7. 飞机速度在机体轴系Xb方向的分量   (+/-3.3f 米/秒)
	int fyjas;         //8. 飞机速度在机体轴系Yb方向的分量   (+/-3.3f 米/秒)
	int cqjs;          //9. 飞机速度在机体轴系Zb方向的分量   (+/-3.3f 米/秒)
	int cqjas;         //10. 飞机横滚角速度   (+/-3.3f 度/秒)
	int hxjs;          //11. 飞机俯仰角速度   (+/-3.3f 度/秒)
	int hxjas;         //12. 飞机偏航角速度   (+/-3.3f 度/秒)
	int fyj;           //13. 飞机俯仰角       (+/-3.3f 度)
	int cqj;           //14. 飞机横滚角       (+/-3.3f 度)
	int phj;           //15. 飞机重心离地高度   (+/-3.3f 米)
	int scl;           //16. 飞机前起落架接地点的支反力(垂向)   (+/-3.3f 千kgf)
	int txzt;          //17. 飞机左起落架接地点的支反力(垂向) (+/-3.3f 千kgf)
	int mh;            //18. 飞机右起落架接地点的支反力(垂向) (+/-3.3f 千kgf)
	int percent;       //19. 飞机前起落架接地点的接地速度(垂向) (+/-3.3f 米/秒)
	int hxfl;          //20. 飞机左起落架接地点的接地速度(垂向) (+/-3.3f 米/秒)
	int acxfl;         //21. 飞机右起落架接地点的接地速度(垂向) (+/-3.3f 米/秒)
	int zxrs;          //22. 飞机接地垂向速度 (+/-3.3f 米/秒)
	int hxrs;          //23. 左刹车力        (+/-3.3f 千kgf)
	int cxrs;          //24. 右刹车力        (+/-3.3f 千kgf)
	int by1;           //25. 紊流在机体轴系Xb方向的线扰速度 (+/-3.3f 米/秒)
	int by2;           //26. 紊流在机体轴系Yb方向的线扰速度 (+/-3.3f 米/秒)
	int by3;           //27. 紊流在机体轴系Zb方向的线扰速度 (+/-3.3f 米/秒)
	int by4;           //28. 紊流在机体轴系Xb方向的线扰加速度 (+/-3.3f 度/秒2)
	int by5;           //29. 紊流在机体轴系Yb方向的线扰加速度 (+/-3.3f 度/秒2)
	int by6;           //30. 紊流在机体轴系Zb方向的线扰加速度 (+/-3.3f 度/秒2)
	int by7;           //31. 前起落架支柱压缩量         (+/-3.3f 米)
	int by8;           //32. 左起落架支柱压缩量         (+/-3.3f 米)
	int by9;           //33. 右起落架支柱压缩量         (+/-3.3f 米)
	int by10;          //34. 襟翼位置                  (+/-3.3f 度)
	int by11;          //35. 左发动机转速百分数         (+/-3.3f 0.0-1.0)
	int by12;          //36. 右发动机转速百分数         (+/-3.3f 0.0-1.0)
	int by13;          //37. 前起落架位置               (+/-3.3f 0.0度-90.0度)
	int by14;          //38. 左起落架位置               (+/-3.3f 0.0度-90.0度)
	int by15;          //39. 右起落架位置               (+/-3.3f 0.0度-90.0度)
	int by16;          //40. 飞行系统冻结标志           (+/-3.3f 1.0:冻结;0.0:解冻)
	int by17;          //41. 总冻结标志                 (+/-3.3f 1.0:冻结;0.0:解冻)
	int by18;          //42. 飞机在地面标志             (+/-3.3f 1.0:地面;0.0:空中)
	int by19;          //43. 前起落架收上标志           (+/-3.3f 1.0:收上;0.0:放下)
	int by20;          //44. 左起落架收上标志           (+/-3.3f 1.0:收上;0.0:放下)
	int by21;          //45. 右起落架收上标志           (+/-3.3f 1.0:收上;0.0:放下)
	int by22;          //46. 左发动机点火标志           (+/-3.3f 1.0:点火;0.0:熄火)
	int by23;          //47. 右发动机点火标志           (+/-3.3f 1.0:点火;0.0:熄火)
	int by24;          //48. 运动重置标志               (+/-3.3f 1.0:是;0.0:非)
	int by25;          //49. 请求平飞标志               (+/-3.3f 1.0:是;0.0:非)
	int by26;          //50. 气流冲击                  (冲击为1.0平台启动,其他为0.0)
	int by27;          //51. 扰流板位置
	int by28;          //52. 校正空速
	int by29;          //53. 马赫数
	int by30;          //54. 飞机迎角(度)
	int by31;          //55. 升力系数
	int by32;          //56. 飞机重心位置
	int by33;          //57. 平均缝翼位置(度)
	int by34;          //58. 跑道表面粗糙度
	int by35;          //59. 999.0是裸控数据
	int by36;          //60. 标志(启动111000,停止777000,联机222000,脱机333000,暂停555000,恢复666000)
	int uPlaneType;	   //61. 飞机类型  0:苏30  1：苏27  2：歼15  3：歼10  4:直9
	int uAccebx_deg;   //62. 平台横滚角                      -20.0~ 20.0（度）    (+/-3.3f)
	int uAcceby_deg;   //63. 平台俯仰角                      -20.0~ 20.0（度）    (+/-3.3f)
	int uAccebz_deg;   //64. 平台偏航角                      -20.0~ 20.0（度）    (+/-3.3f)
	int uAccebx_degs;  //65. 平台横滚角速度                  -22.0~ 22.0（度/秒）  (+/-3.3f)
	int uAcceby_degs;  //66. 平台俯仰角速度                  -22.0~ 22.0（度/秒）  (+/-3.3f)
	int uAccebz_degs;  //67. 平台偏航角速度                  -22.0~ 22.0（度/秒）  (+/-3.3f)
	int uAccebx_degss; //68. 平台横滚角加速度                -150.0~ 150.0（度/秒2）  (+/-3.3f)
	int uAcceby_degss; //69. 平台俯仰角加速度                -150.0~ 150.0（度/秒2）  (+/-3.3f)
	int uAccebz_degss; //70. 平台偏航角加速度                -150.0~ 150.0（度/秒2）  (+/-3.3f)
	int uAcceVx_mss;   //71. 平台在机体轴系X方向的线加速度    -0.6 ~ 0.6 （g）      (+/-3.3f)
	int uAcceVy_mss;   //72. 平台在机体轴系Y方向的线加速度    -0.6 ~ 0.6 （g）      (+/-3.3f)
	int uAcceVz_mss;   //73. 平台在机体轴系Z方向的线加速度    -0.6 ~ 0.6 （g）      (+/-3.3f)
	int flagend;       //74. 数据包标尾 (888)
}IllusionPackage;
#pragma pack () 

// 错觉回传数据帧
#pragma pack (1)
typedef struct
{
	int flagstart;     // 数据包标头(999)
	int iswarning;     //1. 平台是否故障 111：故障 0：无故障
	int status;        //2. 平台状态 000:最底部 111:中立位 222:暂停运动 333:正在运动 444:正在上升 555:正在下降
	int x;             //3. 平台x方向线运动位移，单位 0.001mm
	int y;             //4. 平台y方向线运动位移，单位 0.001mm
	int z;             //5. 平台z方向线运动位移，单位 0.001mm
	int roll;          //6. 平台横滚角，单位 0.001度
	int yaw;           //7. 平台偏航角，单位 0.001度
	int pitch;         //8. 平台俯仰角，单位 0.001度
	int cqjs;          //9. 保留
	int cqjas;         //10. 保留
	int hxjs;          //11. 保留
	int hxjas;         //12. 保留
	int fyj;           //13. 保留
	int cqj;           //14. 保留
	int flagend;       // 数据包标尾 (888)
}IllusionSendPackage;
#pragma pack () 

// 错觉数据适配器
class IllusionDataAdapter
{
public:
	IllusionDataAdapter();
	~IllusionDataAdapter();
	// 设置当前飞机姿态
	void SetPoseAngle(double roll, double pitch, double yaw);
	// 接收并更新数据
	void RenewData();
	// 发送数据
	void SendData();
	// 发送数据
	void SendData(bool iswarning, int status, double x, double y, double z, double roll, double yaw, double pitch);
	// 获取平台控制指令
	int GetControlCommand() const;
	// 是否是错觉控制模式
	bool IsIllusionControl() const;
	// 是否允许抖振
	bool IsEanbleShock() const;
	// 获取抖振频率
	double GetShockHz();
	// 是否收到数据
	bool IsRecievedData;
	// 横滚角
	double Roll;
	// 俯仰角
	double Pitch;
	// 偏航角
	double Yaw;
	// X方向线位移
	double X;
	// Y方向线位移
	double Y;
	// Z方向线位移
	double Z;
	// 横滚角速度
	double RollSpeed;
	// 偏航角速度
	double YawSpeed;
	// 俯仰角速度
	double PitchSpeed;
	// X方向线速度
	double XSpeed;
	// Y方向线速度
	double YSpeed;
	// Z方向线速度
	double ZSpeed;
	// 横滚角加速度
	double RollAcc;
	// 偏航角加速度
	double YawAcc;
	// 俯仰角加速度
	double PitchAcc;
	// X方向线加速度
	double XAcc;
	// Y方向线加速度
	double YAcc;
	// Z方向线加速度
	double ZAcc;
	// 是否是直控模式
	bool IsDirectControl;
	// 飞行模型种类
	PlaneType planeType;
private:
	// 平台当前横滚角
	double platformRoll;
	// 平台当前俯仰角
	double platformPitch;
	// 平台当前偏航角
	double platformYaw;
	// 错觉接收数据
	IllusionPackage Data;
	// 错觉发送数据
	IllusionSendPackage SendToData;
	// 错觉接收数据帧长度
	int DataPackageLength;
	// 错觉发送数据帧长度
	int SendDataPackageLength;
	// 更新数据
	void RenewInnerData();
	// 从文件读取IP和端口号
	void ReadIpAndPortFromFile();
	// 从文件读取直控缩放系数
	void ReadDeirectCtlScaleFromFile();
protected:
	// 数据初始化
	void DataInit();
	// 自身UDP通信端口号
	int SelfPort;
	// 自身UDP通信IP
	string SelfIp;
	// 对方UDP通信端口号
	int VisionPort;
	// 对方UDP通信IP
	string VisionIp;
private:
	// 直控X加速度增益
	double directAccXScale;
	// 直控X加速度增益
	double directAccYScale;
	// 直控X加速度增益
	double directAccZScale;
	// 直控横滚角速度增益
	double directSpeedRollScale;
	// 直控俯仰角速度增益
	double directSpeedPitchScale;
	// 直控偏航角速度增益
	double directSpeedYawScale;
	// 直控横滚角增益	
	double directAngleRollScale;
	// 直控俯仰角增益
	double directAnglePitchScale;
	// 直控偏航角增益
	double directAngleYawScale;
};

#endif // !

