
#ifndef _PHASE_MOTION_CONTROL_H_
#define _PHASE_MOTION_CONTROL_H_

#include <memory>
#include <vector>
#include <deque>
#include <mutex>

#include "sixdof.h"
#include "../hardware/SixdofDioAndPulseCount.h"

using namespace std;

#define DDA_CONTROL_THREAD_DELAY 5

#define IS_BIG_MOTION 1

#define IS_PULSE_CARD_REVERSE 1

#if IS_BIG_MOTION
//缸的最大行程
#define MAX_MM 700.0
// 单位mm
#define MM_RPM 25.0
// 电机转一圈编码器读数 2500
#define PULSE_COUNT_RPM 2500

#define PlaneAboveHingeLength       229.907
#define PlaneAboveBottomLength      2050.0
#define CircleTopRadius             855.85
#define CircleBottomRadius          1220.85
#define DistanceBetweenHingeTop     200.0
#define DistanceBetweenHingeBottom  300.0

// 上升到中立位电机需要转动的圈数
#define RISE_R 14.0

// 单位mm/s
#define RISE_VEL 0.1
// 单位mm/s
#define DOWN_VEL 0.05

//平台运动最大角度
#define MAX_DEG 28
#define DEG_SCALE 0.01
//平台运动最大位移
#define MAX_XYZ 600
#define XYZ_SCALE 0.1
// 平台运动最大频率
#define MAX_HZ 5
#define MAX_PHASE 360

#define MAX_XYZ_X      150
#define MAX_XYZ_Y      150
#define MAX_XYZ_Z      150
#define MAX_DEG_PITCH  15
#define MAX_DEG_ROLL   15
#define MAX_DEG_YAW    15

#else
//缸的最大行程
#define MAX_MM 700.0
// 单位mm
#define MM_RPM 20
// 电机转一圈编码器读数 1024
#define PULSE_COUNT_RPM 1024.0

#define PlaneAboveHingeLength       225.0
#define PlaneAboveBottomLength      2133.5
#define CircleTopRadius             880.7
#define CircleBottomRadius          1519.0
#define DistanceBetweenHingeTop     200.0
#define DistanceBetweenHingeBottom  300.0

// 上升到中立位电机需要转动的圈数
#define RISE_R 17.5

// 单位mm/s
#define RISE_VEL 0.1
// 单位mm/s
#define DOWN_VEL 0.1

//平台运动最大角度
#define MAX_DEG 28
#define DEG_SCALE 0.01
//平台运动最大位移
#define MAX_XYZ 600
#define XYZ_SCALE 0.1
// 平台运动最大频率
#define MAX_HZ 5
#define MAX_PHASE 360

#define MAX_XYZ_X      600
#define MAX_XYZ_Y      550
#define MAX_XYZ_Z      300
#define MAX_DEG_PITCH  25
#define MAX_DEG_ROLL   25
#define MAX_DEG_YAW    28

#endif

#define MAX_POS (PULSE_COUNT_RPM * MAX_MM / MM_RPM)
#define MIDDLE_POS (PULSE_COUNT_RPM * RISE_R)
#define ZERO_POS 0

#define MAX_POLE_LENGTH (MAX_MM / 2.0)

#define MM_TO_PULSE_COUNT_SCALE (PULSE_COUNT_RPM / MM_RPM)

#define MOTION_LOCK_LEVEL   false
#define SWITCH_BOTTOM_LEVEL true
#define MOTION_ENABLE_LEVEL true

#define IS_PID_DOWN 0

using namespace std;

class PhaseMotionControl
{
public:
	PhaseMotionControl();
	~PhaseMotionControl();
	bool InitCard();
	void Close(SixDofPlatformStatus laststatus);
	void SetMotionVeloctySingle(int index, double velocity);
	void SetMotionVelocty(double* velocity, int axexnum);
	bool ServoAllOnOff(bool isOn);
	void SingleUp(int index);
	void SingleDown(int index);
	void AllTestUp();
	void AllTestDown();
	bool ResetStatus();
	void EnableServo();
	void LockServo();
	void UnlockServo();
	void EnableServo(int index);
	void LockServo(int index);
	void UnlockServo(int index);
	void MoveToZeroPulseNumber();
	void PidControllerInit();
	bool ServoStop();
	bool ServoSingleStop(int index);
	void StopRiseDownMove();
	void Rise();
	void Down();
	void Csp(double * pulse);
	void PidCsp(double * pulse);
	void SlowPidCsp(double * pulse);
	double GetMotionAveragePulse();
	double* GetMotionNowEncoderVelocity();
	void RenewNowPulse();
	void SetDDAPositions(double* positions);
	int GetDDAPositionsCount();
	void DDAControlThread();
	//Sixdof
	double NowPluse[AXES_COUNT];
	double EncoderVelocity[AXES_COUNT];
	double AvrPulse;
	SixDofPlatformStatus Status;
	bool IsAtBottoms[AXES_COUNT];
	bool IsAllAtBottom();
	void ReadAllSwitchStatus();
	bool CheckStatus(SixDofPlatformStatus& status);
	bool PowerOnSelfTest(SixDofPlatformStatus laststatus, double * lastpulse);
	void Test();
private:
	bool isrising;
	bool isfalling;
	bool isSelfTest;
	bool enableMove;
	bool disposed;
	double pos[AXES_COUNT];
	SixdofDioAndCount sixdofDioAndCount;
	deque<double*> pulses;
protected:
	mutex lockobj;
};



#endif
