
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

#define IS_BIG_MOTION 0

#define IS_PULSE_CARD_REVERSE 1

#if IS_BIG_MOTION
//�׵�����г�
#define MAX_MM 700.0
// ��λmm
#define MM_RPM 25.0
// ���תһȦ���������� 2500
=======
#define MM_RPM 20.0
// ���תһȦ���������� 2048
#define PULSE_COUNT_RPM 2500

#define PlaneAboveHingeLength       229.907
#define PlaneAboveBottomLength      2050.0
#define CircleTopRadius             858.0
#define CircleBottomRadius          1514.0
#define DistanceBetweenHingeTop     200.0
#define DistanceBetweenHingeBottom  300.0

// ����������λ�����Ҫת����Ȧ��
#define RISE_R 14.0

#else
//�׵�����г�
#define MAX_MM 700.0
// ��λmm
#define MM_RPM 20
// ���תһȦ���������� 1024
#define PULSE_COUNT_RPM 1024.0

#define MM_RPM 20.0
// ���תһȦ���������� 2048
#define PULSE_COUNT_RPM 1024

#define PlaneAboveHingeLength       229.907
#define PlaneAboveBottomLength      2050.0
#define CircleTopRadius             858.0
#define CircleBottomRadius          1514.0
#define DistanceBetweenHingeTop     200.0
#define DistanceBetweenHingeBottom  300.0

// ����������λ�����Ҫת����Ȧ��
#define RISE_R 17.5

#endif

// ��λmm/s
#define RISE_VEL 0.1
// ��λmm/s
#define DOWN_VEL 0.05
// ��λms

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
