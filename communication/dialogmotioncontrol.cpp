
#include "stdafx.h"

#include <math.h>

#include "dialogmotioncontrol.h"
#include "../Sixdofdll2010.h"

#include "../config/inihelper.h"
#include "../control/pid.h"

#define RANGE_V(x, min, max)    (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))
#define ASSERT_INDEX(index) 	if (index < 0 && index >= AXES_COUNT) return;

#if IS_BIG_MOTION
// ƽ̨���й���PID���Ʋ���-P
#define MOTION_P 0.0001��
// ƽ̨���й���PID���Ʋ���-I
#define MOTION_I 0.0000001
// ƽ̨���й���PID���Ʋ���-D
#define MOTION_D 0.0
// ƽ̨���й��̵�������ٶ�
#define MAX_VEL  2.5
// ƽ̨��������PID���Ʋ���-P
#define RISE_MOTION_P 0.00004
// ƽ̨��������PID���Ʋ���-I
#define RISE_MOTION_I 0.0000002
// ƽ̨��������PID���Ʋ���-D
#define RISE_MOTION_D 0.0
// ƽ̨�������̵�������ٶ�
#define RISE_MAX_VEL  0.3
#else
// ƽ̨���й���PID���Ʋ���-P
#define MOTION_P 0.0001
// ƽ̨���й���PID���Ʋ���-I
#define MOTION_I 0.0000001
// ƽ̨���й���PID���Ʋ���-D
#define MOTION_D 0.0
// ƽ̨���й��̵�������ٶ�
#define MAX_VEL  4.0
// ƽ̨��������PID���Ʋ���-P
#define RISE_MOTION_P 0.00004
// ƽ̨��������PID���Ʋ���-I
#define RISE_MOTION_I 0.0000002
// ƽ̨��������PID���Ʋ���-D
#define RISE_MOTION_D 0.0
// ƽ̨�������̵�������ٶ�
#define RISE_MAX_VEL  0.3

#endif // IS_BIG_MOTION

static double last_pulse[AXES_COUNT] = { 0, 0, 0, 0, 0, 0 };
static double now_vel[AXES_COUNT] = { 0, 0, 0, 0, 0, 0 };
static double last_str_vel[AXES_COUNT] = { 0, 0, 0, 0, 0, 0 };
static double speed_scale = 100;
static ULONG last_pulses[AXES_COUNT] = {0};

// ���й������������PID������
static PID_Type MotionLocationPidControler[AXES_COUNT] = 
{
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL }
};

// �����������������PID������
static PID_Type MotionRisePidControler[AXES_COUNT] = 
{
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL }
};

// ���캯��
DialogMotionControl::DialogMotionControl()
{
	disposed = false; 
	for (int i = 0; i < AXES_COUNT; ++i)
	{
		NowPluse[i] = 0;
		pos[i] = 0;
	}
	AvrPulse = 0;
	InitCard();
}

// ��������
DialogMotionControl::~DialogMotionControl()
{
	if (this->disposed == false)
	{
		
	}
}

// ��ʼ������Ӳ���忨
bool DialogMotionControl::InitCard()
{
	return sixdofDioAndCount.Init();
}

// �ر����а忨��������ƽ̨״̬
void DialogMotionControl::Close(SixDofPlatformStatus laststatus)
{
	RenewNowPulse();
	if (lockobj.try_lock())
	{
		config::RecordStatusAndPulse(nullptr, laststatus, NowPluse);
		lockobj.unlock();
	}
	this->disposed = true;
}

// ���õ���������ٶ�
void DialogMotionControl::SetMotionVeloctySingle(int index, double velocity)
{
	ASSERT_INDEX(index);
	velocity = RANGE_V(velocity, -MAX_VEL, MAX_VEL);
	sixdofDioAndCount.SetMotionVel(index, velocity);
}

// ���ö��������ٶ�
void DialogMotionControl::SetMotionVelocty(double* velocity, int axexnum)
{
	sixdofDioAndCount.SetMotionVel(velocity);
}
 
// �������е���Ƿ�բ
bool DialogMotionControl::ServoAllOnOff(bool isOn)
{
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnableAllMotor(isOn);
#else
	sixdofDioAndCount.EnableAllMotor(isOn);
#endif
	return true;
}

// ���������˶�
void DialogMotionControl::SingleUp(int index)
{
	UnlockServo(index);
	SetMotionVeloctySingle(index, RISE_VEL);
}

// ���������˶�
void DialogMotionControl::SingleDown(int index)
{
	UnlockServo(index);
	SetMotionVeloctySingle(index, -DOWN_VEL);
}

// ���и����ϲ����˶�
void DialogMotionControl::AllTestUp()
{
	double vel = RISE_VEL;
	double vels[AXES_COUNT] = {vel, vel, vel, vel, vel, vel};
	UnlockServo();
	SetMotionVelocty(vels, AXES_COUNT);
}

// ���и����²����˶�
void DialogMotionControl::AllTestDown()
{
	double vel = -DOWN_VEL;
	double vels[AXES_COUNT] = {vel, vel, vel, vel, vel, vel};
	UnlockServo();
	SetMotionVelocty(vels, AXES_COUNT);
}

// ��������������
bool DialogMotionControl::ResetStatus()
{
	if (lockobj.try_lock())
	{
		sixdofDioAndCount.ClearPulseCount();
		for (int i = 0;i < AXES_COUNT;++i)
		{
			NowPluse[i] = 0;
		}
		AvrPulse = 0;
		lockobj.unlock();
	}
	return true;
}

// ���е���򿪱�բ��ʹ��
void DialogMotionControl::EnableServo()
{
	bool bits[AXES_COUNT] = {MOTION_ENABLE_LEVEL};
	for (int i = 0;i < AXES_COUNT;++i)
	{
		bits[i] = MOTION_ENABLE_LEVEL;
	}
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnable(bits);
#else
	sixdofDioAndCount.SetMotionEnableBit(bits);
#endif
	
}

// ���е���رձ�բ���ر�ʹ��
void DialogMotionControl::LockServo()
{
	bool bits[AXES_COUNT] = {MOTION_LOCK_LEVEL};
	for (int i = 0;i < AXES_COUNT;++i)
	{
		bits[i] = MOTION_LOCK_LEVEL;
	}
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnable(bits);
#else
	sixdofDioAndCount.SetMotionEnableBit(bits);
	sixdofDioAndCount.SetMotionLockBit(bits);
#endif
	isrising = false;
	isfalling = false;
	enableMove = false;
}

// ���е���򿪱�բ����ʹ��
void DialogMotionControl::UnlockServo()
{
	bool bits[AXES_COUNT] = {!MOTION_LOCK_LEVEL};
	for (int i = 0;i < AXES_COUNT;++i)
	{
		bits[i] = !MOTION_LOCK_LEVEL;
	}
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnable(bits);
#else
	sixdofDioAndCount.SetMotionEnableBit(bits);
	sixdofDioAndCount.SetMotionLockBit(bits);
#endif
}

// �������ʹ��
void DialogMotionControl::EnableServo(int index)
{
	ASSERT_INDEX(index);
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnable(index, MOTION_ENABLE_LEVEL);
#else
	sixdofDioAndCount.SetMotionEnableBit(index, MOTION_ENABLE_LEVEL);
	sixdofDioAndCount.SetMotionLockBit(index, MOTION_ENABLE_LEVEL);
#endif
}

// �����������
void DialogMotionControl::LockServo(int index)
{
	ASSERT_INDEX(index);
	enableMove = false;
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnable(index, MOTION_LOCK_LEVEL);
#else
	sixdofDioAndCount.SetMotionEnableBit(index, MOTION_LOCK_LEVEL);
	sixdofDioAndCount.SetMotionLockBit(index, MOTION_LOCK_LEVEL);
#endif
}

// �����������
void DialogMotionControl::UnlockServo(int index)
{
	ASSERT_INDEX(index);
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnable(index, !MOTION_LOCK_LEVEL);
#else
	sixdofDioAndCount.SetMotionEnableBit(index, !MOTION_LOCK_LEVEL);
	sixdofDioAndCount.SetMotionLockBit(index, !MOTION_LOCK_LEVEL);
#endif
}

// ����
void DialogMotionControl::Rise()
{
	LockServo();
	for (int i = 0;i < AXES_COUNT;++i)
	{
		MyPidParaInit(MotionRisePidControler);
	}
	Sleep(10);
	isrising = true;
	Sleep(10);
	isfalling = false;
	enableMove = false;
	UnlockServo();
}

// �½�
void DialogMotionControl::Down()
{
#if IS_PID_DOWN
	LockServo();
	Sleep(10);
	isfalling = true;
	isrising = false;
	enableMove = false;
	UnlockServo();
#else
	AllTestDown();
#endif	
}

// ����λ�ÿ���
void DialogMotionControl::Csp(double * pulse)
{	
	for (auto i = 0; i < AXES_COUNT; ++i)
	{
		pulse[i] = RANGE_V(pulse[i], 0, MAX_POS);
		auto re = (pulse[i] - last_pulse[i]) * speed_scale;
		now_vel[i] = re;
		now_vel[i] = RANGE_V(now_vel[i], -4, 4);
		last_pulse[i] = pulse[i];
		last_str_vel[i] = now_vel[i];
	}
	SetMotionVelocty(now_vel, AXES_COUNT);
}

// ����λ�ÿ���(PID����)
void DialogMotionControl::PidCsp(double * pulse)
{
	if (lockobj.try_lock())
	{	
		for (auto i = 0; i < AXES_COUNT; ++i)
		{
			pulse[i] = pulse[i] + MIDDLE_POS;
			pulse[i] = RANGE_V(pulse[i], HALF_RPM_POS, MAX_POS - HALF_RPM_POS);
			now_vel[i] = MyDeltaPID_Real(&MotionLocationPidControler[i], \
				NowPluse[i], pulse[i]);
		}
		lockobj.unlock();
	}
	SetMotionVelocty(now_vel, AXES_COUNT);
}

// ����������λ�ÿ���(PID����)
void DialogMotionControl::SlowPidCsp(double * pulse)
{
	if (lockobj.try_lock())
	{	
		for (auto i = 0; i < AXES_COUNT; ++i)
		{
			pulse[i] = pulse[i] + MIDDLE_POS;
			pulse[i] = RANGE_V(pulse[i], 0, MAX_POS);
			now_vel[i] = MyDeltaPID_Real(&MotionRisePidControler[i], \
				NowPluse[i], pulse[i]);
		}
		lockobj.unlock();
	}

	SetMotionVelocty(now_vel, AXES_COUNT);
}

// ��ȡ���е�������������ƽ��ֵ
double DialogMotionControl::GetMotionAveragePulse()
{
	double pulse_num = 0;
	if (lockobj.try_lock())
	{
		for(auto i = 0; i < AXES_COUNT; ++i)
		{
			auto actual_pos = NowPluse[i];
			pulse_num += actual_pos;
		}
		lockobj.unlock();
	}

	double avr_pulse = pulse_num / (double)AXES_COUNT;
	AvrPulse = avr_pulse;
	return avr_pulse;
}

// �������е������������
void DialogMotionControl::RenewNowPulse()
{
	if(lockobj.try_lock())
	{
		auto pulses = sixdofDioAndCount.ReadPulseCount();
#if IS_PULSE_CARD_REVERSE
		NowPluse[0] = pulses[3];
		NowPluse[1] = pulses[4];
		NowPluse[2] = pulses[5];
		NowPluse[3] = pulses[0];
		NowPluse[4] = pulses[1];
		NowPluse[5] = pulses[2];
#else
		for (int i = 0; i < AXES_COUNT ;++i)
		{
			NowPluse[i] = pulses[i];
		}
#endif
		lockobj.unlock();
	}
}

// ��ȡ��λ���쳤����
double* DialogMotionControl::GetNowPoleLength()
{
	if (lockobj.try_lock())
	{
		memcpy(polelenthmm, NowPluse, sizeof(double) * AXES_COUNT);
		lockobj.unlock();
	}
	for (int i = 0;i < AXES_COUNT;++i)
	{
		polelenthmm[i] = (polelenthmm[i] - MIDDLE_POS) * PULSE_COUNT_TO_MM_SCALE; 
	}
	return polelenthmm;
}

// �˶�ѧ�����ȡ��̬ x y z roll pitch yaw
double* DialogMotionControl::GetNowPoseFromLength()
{
	if (lockobj.try_lock())
	{
		memcpy(polelenthmm, NowPluse, sizeof(double) * AXES_COUNT);
		lockobj.unlock();
	}
	for (int i = 0;i < AXES_COUNT;++i)
	{
		polelenthmm[i] = (polelenthmm[i] - MIDDLE_POS) * PULSE_COUNT_TO_MM_SCALE; 
	}
	auto pose = FromLengthToPose(polelenthmm);
	memcpy(posefromlength, pose, sizeof(double) * AXES_COUNT);
	return posefromlength;
}

// ��������½���PID���ƺ���
void DialogMotionControl::DDAControlThread()
{
	while (true)
	{
		double eps = AXES_COUNT * AXES_COUNT;
		if (isrising == true)
		{
			RenewNowPulse();
			double pulses[AXES_COUNT] = {0};
			SlowPidCsp(pulses);
			for (int i = 0; i < AXES_COUNT; ++i)
			{
				if (abs(NowPluse[i] - MIDDLE_POS) <= eps)
				{
					ServoSingleStop(i);
					LockServo(i);
				}
			}
		}
		if(isfalling == true)
		{
			RenewNowPulse();
			double pulses[AXES_COUNT] = {-MIDDLE_POS,-MIDDLE_POS,-MIDDLE_POS,-MIDDLE_POS,-MIDDLE_POS,-MIDDLE_POS};
			SlowPidCsp(pulses);
			for (int i = 0; i < AXES_COUNT; ++i)
			{
				if (abs(NowPluse[i] - 0) <= 1)
				{
					//ServoSingleStop(i);
					//LockServo(i);
				}
			}
		}
		if(enableMove == true)
		{
			RenewNowPulse();
			double pulses[AXES_COUNT] = {0};
			double sum = 0;
			memcpy(pulses, pos, sizeof(double) * AXES_COUNT);
			SlowPidCsp(pulses);
			for (int i = 0; i < AXES_COUNT; ++i)
			{
				sum += abs(pulses[i] - NowPluse[i]); 
			}
			if (sum <= eps * AXES_COUNT)
			{
				ServoStop();
			}	
		}
		ReadAllSwitchStatus();
		Sleep(DDA_CONTROL_THREAD_DELAY);
	}
}

// �����˶������
void DialogMotionControl::MoveToZeroPulseNumber()
{
	for (int i = 0;i < AXES_COUNT;++i)
	{
		MyPidParaInit(&MotionRisePidControler[i]);
	}
	Sleep(10);
	isrising = true;
	UnlockServo();
}

// PID��������ʼ��
void DialogMotionControl::PidControllerInit()
{
	for (int i = 0;i < AXES_COUNT;++i)
	{
		MyPidParaInit(&MotionLocationPidControler[i]);
	}
}

// ���е��ͣת
bool DialogMotionControl::ServoStop()
{
	StopRiseDownMove();
	LockServo();
	return true;
}

// �������ͣת
bool DialogMotionControl::ServoSingleStop(int index)
{
	enableMove = false;
	double vel = 0;
	SetMotionVeloctySingle(index, vel);
	return true;
}

// ֹͣ���������½���PID����
void DialogMotionControl::StopRiseDownMove()
{
	enableMove = false;
	isrising = false;
	isfalling = false;
	double vel[AXES_COUNT];
	memset(vel, 0, sizeof(double) * AXES_COUNT);
	SetMotionVelocty(vel, AXES_COUNT);
}

// ���и��Ƿ�λ�ڵײ�
bool DialogMotionControl::IsAllAtBottom()
{
	for (auto i = 0; i < AXES_COUNT; ++i)
	{
		auto isAtBottom = IsAtBottoms[i];
		if (isAtBottom == false)
		{
			return false;
		}
	}
	return true;
}

// ��ȡ���нӽ�����״̬
void DialogMotionControl::ReadAllSwitchStatus()
{

#if IS_BIG_MOTION
	bool kbits[SXIDOF_MOTION_NUM] = { true,true,true,true,true,true };
	sixdofDioAndCount.BigMotionReadKBit(kbits);
#endif
	for (int i = 0;i < AXES_COUNT;++i)
	{
		
#if IS_BIG_MOTION
		IsAtBottoms[i] = !kbits[i];
#else
		sixdofDioAndCount.ReadKBit(i, &IsAtBottoms[i]);
#endif
		if (IsAtBottoms[i] == true && isrising == false)
		{
			ServoSingleStop(i);
			LockServo(i);
		}
	}
}

// ��������ɶ�ƽ̨״̬
bool DialogMotionControl::CheckStatus(SixDofPlatformStatus& status)
{
	char* str = SixDofStatusText[status];
	double pulse = 0;
	ReadAllSwitchStatus();
	switch (status)
	{
	case SIXDOF_STATUS_BOTTOM:
		break;
	case SIXDOF_STATUS_READY:
		break;
	case SIXDOF_STATUS_MIDDLE:
		break;
	case SIXDOF_STATUS_RUN:
		break;
	case SIXDOF_STATUS_ISRISING:
		pulse = GetMotionAveragePulse();
		if (pulse >= (RISE_R - 1) * PULSE_COUNT_RPM)
		{
			status = SIXDOF_STATUS_READY;
		}			
		break;
	case SIXDOF_STATUS_ISFALLING:			
		if (IsAllAtBottom() == true)
		{
			status = SIXDOF_STATUS_BOTTOM;
		}
		break;
	default:
		break;
	}
	str = SixDofStatusText[status];
	Status = status;
	return true;
}

// �����ɶ�ƽ̨�����Լ�
bool DialogMotionControl::PowerOnSelfTest(SixDofPlatformStatus laststatus, double * lastpulse)
{
	if(isSelfTest == true)
		return false;
	switch (laststatus)
	{
	case SIXDOF_STATUS_BOTTOM:
		//AllTestDown();
		break;
	case SIXDOF_STATUS_READY:
		//�½�
		AllTestDown();
		break;
	case SIXDOF_STATUS_MIDDLE:
		AllTestDown();
		break;
	case SIXDOF_STATUS_RUN:
		//����
		//MoveToLocation(lastpulse, AXES_COUNT, false);
		//�½�
		AllTestDown();
		break;
	case SIXDOF_STATUS_ISRISING:
		//�½�
		AllTestDown();
		break;
	case SIXDOF_STATUS_ISFALLING:
		//�½�
		AllTestDown();
		break;
	default:
		break;
	}
	isSelfTest = true;
	return true;
}

// ��������Ӳ��
void DialogMotionControl::TestHardware()
{
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionTest();
#else
	sixdofDioAndCount.Test();
#endif
}
