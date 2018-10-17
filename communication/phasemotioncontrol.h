
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
// 电机转一圈编码器读数 2048
#define PULSE_COUNT_RPM 2048.0

#define PlaneAboveHingeLength       245.0
#define PlaneAboveBottomLength      2024.0
#define CircleTopRadius             855.85
#define CircleBottomRadius          1220.85
#define DistanceBetweenHingeTop     200.0
#define DistanceBetweenHingeBottom  300.0

#else
//缸的最大行程
#define MAX_MM 700.0
// 单位mm
#define MM_RPM 7.5
// 电机转一圈编码器读数 1024
#define PULSE_COUNT_RPM 1024.0

#define PlaneAboveHingeLength       100.0
#define PlaneAboveBottomLength      700.0
#define CircleTopRadius             680.0
#define CircleBottomRadius          840.0
#define DistanceBetweenHingeTop     190.0
#define DistanceBetweenHingeBottom  190.0

#endif

// 单位mm/s
#define RISE_VEL 0.1
// 单位mm/s
#define DOWN_VEL 0.05
// 单位ms
#define RISE_TIME 500.0
#define FALL_TIME 400.0
// 上升到中立位电机需要转动的圈数
#define RISE_R 14.0

#define MAX_POS (PULSE_COUNT_RPM * MAX_MM / MM_RPM)
#define MIDDLE_POS (PULSE_COUNT_RPM * RISE_R)
#define ZERO_POS 0

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
	void MoveToLocationSingle(int index, double location, bool isAbs);
	void MoveToLocation(double* location, int axexnum, bool isAbs);
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
	bool ServoStop();
	bool ServoSingleStop(int index);
	void Rise();
	void Down();
	void Csp(double * pulse);
	void PidCsp(double * pulse);
	void SlowPidCsp(double * pulse);
	void ForwardCsp(double x, double y, double z, double roll, double yaw, double pitch);
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
