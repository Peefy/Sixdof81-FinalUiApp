
#ifndef _DIALOG_MOTION_CONTROL_H_
#define _DIALOG_MOTION_CONTROL_H_

#include <memory>
#include <vector>
#include <deque>
// 线程同步锁头文件
#include <mutex>   
// 六自由度平台头文件
#include "sixdof.h"
// 控制板卡头文件
#include "../hardware/SixdofDioAndPulseCount.h"
// 应用配置头文件
#include "../config/appconfig.h"

using namespace std;

//上升下降控制间隔
#define DDA_CONTROL_THREAD_DELAY 5

#if IS_BIG_MOTION
// 缸的最大行程mm
#define MAX_MM 700.0
// 电机丝杠导程单位mm
#define MM_RPM 25.0
// 电机转一圈编码器读数 2500
#define PULSE_COUNT_RPM 2500
// 上平台上表面距离上平台铰链的垂直距离mm
#define PlaneAboveHingeLength       229.907
// 上平台上表面距离地面的垂直距离mm
#define PlaneAboveBottomLength      2050.0
// 上平台圆圈半径mm
#define CircleTopRadius             855.85
// 下平台圆圈半径mm
#define CircleBottomRadius          1220.85
// 上平台同一组两个铰链的中心距离mm
#define DistanceBetweenHingeTop     200.0
// 下平台同一组两个铰链的中心距离mm
#define DistanceBetweenHingeBottom  300.0

// 上升到中立位电机需要转动的圈数
#define RISE_R 14.0

// 单位mm/s
#define RISE_VEL 0.1
// 单位mm/s
#define DOWN_VEL 0.05

// 平台运动最大角度deg
#define MAX_DEG 28
// 角度变为整数缩放系数
#define DEG_SCALE 0.01
// 平台运动最大位移mm
#define MAX_XYZ 600
// 位移变为整数缩放系数
#define XYZ_SCALE 0.1
// 平台运动最大频率Hz
#define MAX_HZ 5
// 平台正弦运动最大相位deg
#define MAX_PHASE 360

// 平台运动最大位移 纵向mm
#define MAX_XYZ_X      150
// 平台运动最大位移 横向mm
#define MAX_XYZ_Y      150
// 平台运动最大位移 垂向mm
#define MAX_XYZ_Z      150
// 平台运动最大角度 俯仰角deg
#define MAX_DEG_PITCH  15
// 平台运动最大角度 横滚角deg
#define MAX_DEG_ROLL   15
// 平台运动最大角度 偏航角deg
#define MAX_DEG_YAW    15
// 平台正弦运动 位移最大零位mm
#define MAX_XYZ_ZERO_POS    30
// 平台正弦运动 角度最大零位deg
#define MAX_DEG_ZERO_POS    3

#else
//缸的最大行程mm
#define MAX_MM 700.0
// 电机丝杠单位mm
#define MM_RPM 20
// 电机转一圈编码器读数 1024
#define PULSE_COUNT_RPM 1024.0
// 上平台上表面距离上平台铰链的垂直距离mm
#define PlaneAboveHingeLength       225.0
// 上平台上表面距离地面的垂直距离mm
#define PlaneAboveBottomLength      2133.5
// 上平台圆圈半径mm
#define CircleTopRadius             880.7
// 下平台圆圈半径mm
#define CircleBottomRadius          1519.0
// 上平台同一组两个铰链的中心距离mm
#define DistanceBetweenHingeTop     200.0
// 下平台同一组两个铰链的中心距离mm
#define DistanceBetweenHingeBottom  300.0

// 上升到中立位电机需要转动的圈数
#define RISE_R 17.5

// 单位mm/s
#define RISE_VEL 0.1
// 单位mm/s
#define DOWN_VEL 0.1

//平台运动最大角度deg
#define MAX_DEG 28
// 角度变为整数缩放系数
#define DEG_SCALE 0.01
//平台运动最大位移mm
#define MAX_XYZ 600
// 位移变为整数缩放系数
#define XYZ_SCALE 0.1
// 平台运动最大频率Hz
#define MAX_HZ 5
// 平台正弦运动最大相位deg
#define MAX_PHASE 360

// 平台运动最大位移 纵向mm
#define MAX_XYZ_X      600
// 平台运动最大位移 横向mm
#define MAX_XYZ_Y      550
// 平台运动最大位移 垂向mm
#define MAX_XYZ_Z      300
// 平台运动最大角度 俯仰角deg
#define MAX_DEG_PITCH  25
// 平台运动最大角度 横滚角deg
#define MAX_DEG_ROLL   25
// 平台运动最大角度 偏航角deg
#define MAX_DEG_YAW    28

// 平台正弦运动 位移最大零位mm
#define MAX_XYZ_ZERO_POS    30
// 平台正弦运动 角度最大零位deg
#define MAX_DEG_ZERO_POS    3

#endif

// 缸最大行程(编码器最大读数)
#define MAX_POS (PULSE_COUNT_RPM * MAX_MM / MM_RPM)
// 缸中位行程(编码器中位读数)
#define MIDDLE_POS (PULSE_COUNT_RPM * RISE_R)
// 缸零点行程(编码器零点读数)
#define ZERO_POS 0
// 缸在中位时运动的最大位移
#define MAX_POLE_LENGTH (MAX_MM / 2.0)
// 缸伸长量mm到编码器位置的转换系数
#define MM_TO_PULSE_COUNT_SCALE (PULSE_COUNT_RPM / MM_RPM)
// 电机抱闸电平
#define MOTION_LOCK_LEVEL   false
// 接近开关接触电平
#define SWITCH_BOTTOM_LEVEL true
// 电机使能电平
#define MOTION_ENABLE_LEVEL true
// 是否采用PID控制平台下降，0为否，1为是，默认为否即可
#define IS_PID_DOWN 0

using namespace std;

class DialogMotionControl
{
public:
	DialogMotionControl();
	~DialogMotionControl();
	// 初始化所有板卡
	bool InitCard();
	// 关闭所有板卡，并保存平台状态
	void Close(SixDofPlatformStatus laststatus);
	// 设置单个电机的速度
	void SetMotionVeloctySingle(int index, double velocity);
	// 设置多个电机的速度
	void SetMotionVelocty(double* velocity, int axexnum);
	// 设置所有电机是否抱闸
	bool ServoAllOnOff(bool isOn);
	// 单缸向上运动
	void SingleUp(int index);
	// 单缸向下运动
	void SingleDown(int index);
	// 所有缸向上测试运动
	void AllTestUp();
	// 所有缸向下测试运动
	void AllTestDown();
	// 编码器读数清零
	bool ResetStatus();
	// 所有电机打开抱闸并使能
	void EnableServo();
	// 所有电机关闭抱闸
	void LockServo();
	// 所有电机打开抱闸
	void UnlockServo();
	// 单个电机使能
	void EnableServo(int index);
	// 单个电机上锁
	void LockServo(int index);
	// 单个电机解锁
	void UnlockServo(int index);
	// 结束运动后回中
	void MoveToZeroPulseNumber();
	// PID控制器初始化
	void PidControllerInit();
	// 所有电机停转
	bool ServoStop();
	// 单个电机停转
	bool ServoSingleStop(int index);
	// 停止上升或者下降的PID控制
	void StopRiseDownMove();
	// 上升
	void Rise();
	// 下降
	void Down();
	// 连续位置控制
	void Csp(double * pulse);
	// 连续位置控制(Pid控制)
	void PidCsp(double * pulse);
	void SlowPidCsp(double * pulse);
	// 获取所有电机编码器脉冲的平均值
	double GetMotionAveragePulse();
	// 更新所有电机编码器读数
	void RenewNowPulse();
	// 电机上升下降的PID控制函数
	void DDAControlThread();
	// 所有缸是否位于底部
	bool IsAllAtBottom();
	// 读取所有接近开关状态
	void ReadAllSwitchStatus();
	// 检查六自由度平台状态
	bool CheckStatus(SixDofPlatformStatus& status);
	// 六自由度平台开机自检
	bool PowerOnSelfTest(SixDofPlatformStatus laststatus, double * lastpulse);
	// 测试所有硬件
	void Test();
public:
	// 电机编码器位置
	double NowPluse[AXES_COUNT];
	// 电机编码器平均位置
	double AvrPulse;
	// 六自由度平台状态
	SixDofPlatformStatus Status;
	// 所有缸是否位于底部
	bool IsAtBottoms[AXES_COUNT];
private:
	// 是否正在下降
	bool isrising;
	// 是否正在上升
	bool isfalling;
	// 是否开机自检过
	bool isSelfTest;
	// 是否允许电机转动
	bool enableMove;
	// 是否释放所有资源
	bool disposed;
	// 电机位置缓冲变量
	double pos[AXES_COUNT];
	// 板卡控制类
	SixdofDioAndCount sixdofDioAndCount;
protected:
	// 线程同步锁
	mutex lockobj;
};



#endif
