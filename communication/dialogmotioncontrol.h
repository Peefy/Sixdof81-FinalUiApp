
#ifndef _DIALOG_MOTION_CONTROL_H_
#define _DIALOG_MOTION_CONTROL_H_

#include <memory>
#include <vector>
#include <deque>
// �߳�ͬ����ͷ�ļ�
#include <mutex>   
// �����ɶ�ƽ̨ͷ�ļ�
#include "sixdof.h"
// ���ư忨ͷ�ļ�
#include "../hardware/SixdofDioAndPulseCount.h"
// Ӧ������ͷ�ļ�
#include "../config/appconfig.h"

using namespace std;

//�����½����Ƽ��
#define DDA_CONTROL_THREAD_DELAY 5

#if IS_BIG_MOTION
// �׵�����г�mm
#define MAX_MM 700.0
// ���˿�ܵ��̵�λmm
#define MM_RPM 25.0
// ���תһȦ���������� 2500
#define PULSE_COUNT_RPM 2500
// ��ƽ̨�ϱ��������ƽ̨�����Ĵ�ֱ����mm
#define PlaneAboveHingeLength       229.907
// ��ƽ̨�ϱ���������Ĵ�ֱ����mm
#define PlaneAboveBottomLength      2050.0
// ��ƽ̨ԲȦ�뾶mm
#define CircleTopRadius             855.85
// ��ƽ̨ԲȦ�뾶mm
#define CircleBottomRadius          1220.85
// ��ƽ̨ͬһ���������������ľ���mm
#define DistanceBetweenHingeTop     200.0
// ��ƽ̨ͬһ���������������ľ���mm
#define DistanceBetweenHingeBottom  300.0

// ����������λ�����Ҫת����Ȧ��
#define RISE_R 14.0

// ��λmm/s
#define RISE_VEL 0.1
// ��λmm/s
#define DOWN_VEL 0.05

// ƽ̨�˶����Ƕ�deg
#define MAX_DEG 28
// �Ƕȱ�Ϊ��������ϵ��
#define DEG_SCALE 0.01
// ƽ̨�˶����λ��mm
#define MAX_XYZ 600
// λ�Ʊ�Ϊ��������ϵ��
#define XYZ_SCALE 0.1
// ƽ̨�˶����Ƶ��Hz
#define MAX_HZ 5
// ƽ̨�����˶������λdeg
#define MAX_PHASE 360

// ƽ̨�˶����λ�� ����mm
#define MAX_XYZ_X      150
// ƽ̨�˶����λ�� ����mm
#define MAX_XYZ_Y      150
// ƽ̨�˶����λ�� ����mm
#define MAX_XYZ_Z      150
// ƽ̨�˶����Ƕ� ������deg
#define MAX_DEG_PITCH  15
// ƽ̨�˶����Ƕ� �����deg
#define MAX_DEG_ROLL   15
// ƽ̨�˶����Ƕ� ƫ����deg
#define MAX_DEG_YAW    15
// ƽ̨�����˶� λ�������λmm
#define MAX_XYZ_ZERO_POS    30
// ƽ̨�����˶� �Ƕ������λdeg
#define MAX_DEG_ZERO_POS    3

#else
//�׵�����г�mm
#define MAX_MM 700.0
// ���˿�ܵ�λmm
#define MM_RPM 20
// ���תһȦ���������� 1024
#define PULSE_COUNT_RPM 1024.0
// ��ƽ̨�ϱ��������ƽ̨�����Ĵ�ֱ����mm
#define PlaneAboveHingeLength       225.0
// ��ƽ̨�ϱ���������Ĵ�ֱ����mm
#define PlaneAboveBottomLength      2133.5
// ��ƽ̨ԲȦ�뾶mm
#define CircleTopRadius             880.7
// ��ƽ̨ԲȦ�뾶mm
#define CircleBottomRadius          1519.0
// ��ƽ̨ͬһ���������������ľ���mm
#define DistanceBetweenHingeTop     200.0
// ��ƽ̨ͬһ���������������ľ���mm
#define DistanceBetweenHingeBottom  300.0

// ����������λ�����Ҫת����Ȧ��
#define RISE_R 17.5

// ��λmm/s
#define RISE_VEL 0.1
// ��λmm/s
#define DOWN_VEL 0.1

//ƽ̨�˶����Ƕ�deg
#define MAX_DEG 28
// �Ƕȱ�Ϊ��������ϵ��
#define DEG_SCALE 0.01
//ƽ̨�˶����λ��mm
#define MAX_XYZ 600
// λ�Ʊ�Ϊ��������ϵ��
#define XYZ_SCALE 0.1
// ƽ̨�˶����Ƶ��Hz
#define MAX_HZ 5
// ƽ̨�����˶������λdeg
#define MAX_PHASE 360

// ƽ̨�˶����λ�� ����mm
#define MAX_XYZ_X      600
// ƽ̨�˶����λ�� ����mm
#define MAX_XYZ_Y      550
// ƽ̨�˶����λ�� ����mm
#define MAX_XYZ_Z      300
// ƽ̨�˶����Ƕ� ������deg
#define MAX_DEG_PITCH  25
// ƽ̨�˶����Ƕ� �����deg
#define MAX_DEG_ROLL   25
// ƽ̨�˶����Ƕ� ƫ����deg
#define MAX_DEG_YAW    28

// ƽ̨�����˶� λ�������λmm
#define MAX_XYZ_ZERO_POS    30
// ƽ̨�����˶� �Ƕ������λdeg
#define MAX_DEG_ZERO_POS    3

#endif

// ������г�(������������)
#define MAX_POS (PULSE_COUNT_RPM * MAX_MM / MM_RPM)
// ����λ�г�(��������λ����)
#define MIDDLE_POS (PULSE_COUNT_RPM * RISE_R)
// ������г�(������������)
#define ZERO_POS 0
// ������λʱ�˶������λ��
#define MAX_POLE_LENGTH (MAX_MM / 2.0)
// ���쳤��mm��������λ�õ�ת��ϵ��
#define MM_TO_PULSE_COUNT_SCALE (PULSE_COUNT_RPM / MM_RPM)
// �����բ��ƽ
#define MOTION_LOCK_LEVEL   false
// �ӽ����ؽӴ���ƽ
#define SWITCH_BOTTOM_LEVEL true
// ���ʹ�ܵ�ƽ
#define MOTION_ENABLE_LEVEL true
// �Ƿ����PID����ƽ̨�½���0Ϊ��1Ϊ�ǣ�Ĭ��Ϊ�񼴿�
#define IS_PID_DOWN 0

using namespace std;

class DialogMotionControl
{
public:
	DialogMotionControl();
	~DialogMotionControl();
	// ��ʼ�����а忨
	bool InitCard();
	// �ر����а忨��������ƽ̨״̬
	void Close(SixDofPlatformStatus laststatus);
	// ���õ���������ٶ�
	void SetMotionVeloctySingle(int index, double velocity);
	// ���ö��������ٶ�
	void SetMotionVelocty(double* velocity, int axexnum);
	// �������е���Ƿ�բ
	bool ServoAllOnOff(bool isOn);
	// ���������˶�
	void SingleUp(int index);
	// ���������˶�
	void SingleDown(int index);
	// ���и����ϲ����˶�
	void AllTestUp();
	// ���и����²����˶�
	void AllTestDown();
	// ��������������
	bool ResetStatus();
	// ���е���򿪱�բ��ʹ��
	void EnableServo();
	// ���е���رձ�բ
	void LockServo();
	// ���е���򿪱�բ
	void UnlockServo();
	// �������ʹ��
	void EnableServo(int index);
	// �����������
	void LockServo(int index);
	// �����������
	void UnlockServo(int index);
	// �����˶������
	void MoveToZeroPulseNumber();
	// PID��������ʼ��
	void PidControllerInit();
	// ���е��ͣת
	bool ServoStop();
	// �������ͣת
	bool ServoSingleStop(int index);
	// ֹͣ���������½���PID����
	void StopRiseDownMove();
	// ����
	void Rise();
	// �½�
	void Down();
	// ����λ�ÿ���
	void Csp(double * pulse);
	// ����λ�ÿ���(Pid����)
	void PidCsp(double * pulse);
	void SlowPidCsp(double * pulse);
	// ��ȡ���е�������������ƽ��ֵ
	double GetMotionAveragePulse();
	// �������е������������
	void RenewNowPulse();
	// ��������½���PID���ƺ���
	void DDAControlThread();
	// ���и��Ƿ�λ�ڵײ�
	bool IsAllAtBottom();
	// ��ȡ���нӽ�����״̬
	void ReadAllSwitchStatus();
	// ��������ɶ�ƽ̨״̬
	bool CheckStatus(SixDofPlatformStatus& status);
	// �����ɶ�ƽ̨�����Լ�
	bool PowerOnSelfTest(SixDofPlatformStatus laststatus, double * lastpulse);
	// ��������Ӳ��
	void Test();
public:
	// ���������λ��
	double NowPluse[AXES_COUNT];
	// ���������ƽ��λ��
	double AvrPulse;
	// �����ɶ�ƽ̨״̬
	SixDofPlatformStatus Status;
	// ���и��Ƿ�λ�ڵײ�
	bool IsAtBottoms[AXES_COUNT];
private:
	// �Ƿ������½�
	bool isrising;
	// �Ƿ���������
	bool isfalling;
	// �Ƿ񿪻��Լ��
	bool isSelfTest;
	// �Ƿ�������ת��
	bool enableMove;
	// �Ƿ��ͷ�������Դ
	bool disposed;
	// ���λ�û������
	double pos[AXES_COUNT];
	// �忨������
	SixdofDioAndCount sixdofDioAndCount;
protected:
	// �߳�ͬ����
	mutex lockobj;
};



#endif
