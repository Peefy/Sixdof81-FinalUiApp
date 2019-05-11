
#include "stdafx.h"

#include <math.h>

#include "dialogmotioncontrol.h"
#include "../Sixdofdll2010.h"

#include "../config/inihelper.h"
#include "../control/pid.h"

#define RANGE_V(x, min, max)    (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))
#define ASSERT_INDEX(index) 	if (index < 0 && index >= AXES_COUNT) return;

#if IS_BIG_MOTION
// 平台运行过程PID控制参数-P
#define MOTION_P 0.0001、
// 平台运行过程PID控制参数-I
#define MOTION_I 0.0000001
// 平台运行过程PID控制参数-D
#define MOTION_D 0.0
// 平台运行过程当中最大速度
#define MAX_VEL  2.5
// 平台上升过程PID控制参数-P
#define RISE_MOTION_P 0.00004
// 平台上升过程PID控制参数-I
#define RISE_MOTION_I 0.0000002
// 平台上升过程PID控制参数-D
#define RISE_MOTION_D 0.0
// 平台上升过程当中最大速度
#define RISE_MAX_VEL  0.3
#else
// 平台运行过程PID控制参数-P
#define MOTION_P 0.0001
// 平台运行过程PID控制参数-I
#define MOTION_I 0.0000001
// 平台运行过程PID控制参数-D
#define MOTION_D 0.0
// 平台运行过程当中最大速度
#define MAX_VEL  4.0
// 平台上升过程PID控制参数-P
#define RISE_MOTION_P 0.00004
// 平台上升过程PID控制参数-I
#define RISE_MOTION_I 0.0000002
// 平台上升过程PID控制参数-D
#define RISE_MOTION_D 0.0
// 平台上升过程当中最大速度
#define RISE_MAX_VEL  0.3

#endif // IS_BIG_MOTION

static double last_pulse[AXES_COUNT] = { 0, 0, 0, 0, 0, 0 };
static double now_vel[AXES_COUNT] = { 0, 0, 0, 0, 0, 0 };
static double last_str_vel[AXES_COUNT] = { 0, 0, 0, 0, 0, 0 };
static double speed_scale = 100;
static ULONG last_pulses[AXES_COUNT] = {0};

// 运行过程六个电机的PID控制器
static PID_Type MotionLocationPidControler[AXES_COUNT] = 
{
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL },
	{ MOTION_P, MOTION_I, MOTION_D, -MAX_VEL, MAX_VEL }
};

// 上升过程六个电机的PID控制器
static PID_Type MotionRisePidControler[AXES_COUNT] = 
{
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL },
	{ RISE_MOTION_P, RISE_MOTION_I, RISE_MOTION_D, -RISE_MAX_VEL, RISE_MAX_VEL }
};

// 构造函数
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

// 析构函数
DialogMotionControl::~DialogMotionControl()
{
	if (this->disposed == false)
	{
		
	}
}

// 初始化所有硬件板卡
bool DialogMotionControl::InitCard()
{
	return sixdofDioAndCount.Init();
}

// 关闭所有板卡，并保存平台状态
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

// 设置单个电机的速度
void DialogMotionControl::SetMotionVeloctySingle(int index, double velocity)
{
	ASSERT_INDEX(index);
	velocity = RANGE_V(velocity, -MAX_VEL, MAX_VEL);
	sixdofDioAndCount.SetMotionVel(index, velocity);
}

// 设置多个电机的速度
void DialogMotionControl::SetMotionVelocty(double* velocity, int axexnum)
{
	sixdofDioAndCount.SetMotionVel(velocity);
}
 
// 设置所有电机是否抱闸
bool DialogMotionControl::ServoAllOnOff(bool isOn)
{
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionEnableAllMotor(isOn);
#else
	sixdofDioAndCount.EnableAllMotor(isOn);
#endif
	return true;
}

// 单缸向上运动
void DialogMotionControl::SingleUp(int index)
{
	UnlockServo(index);
	SetMotionVeloctySingle(index, RISE_VEL);
}

// 单缸向下运动
void DialogMotionControl::SingleDown(int index)
{
	UnlockServo(index);
	SetMotionVeloctySingle(index, -DOWN_VEL);
}

// 所有缸向上测试运动
void DialogMotionControl::AllTestUp()
{
	double vel = RISE_VEL;
	double vels[AXES_COUNT] = {vel, vel, vel, vel, vel, vel};
	UnlockServo();
	SetMotionVelocty(vels, AXES_COUNT);
}

// 所有缸向下测试运动
void DialogMotionControl::AllTestDown()
{
	double vel = -DOWN_VEL;
	double vels[AXES_COUNT] = {vel, vel, vel, vel, vel, vel};
	UnlockServo();
	SetMotionVelocty(vels, AXES_COUNT);
}

// 编码器读数清零
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

// 所有电机打开抱闸并使能
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

// 所有电机关闭抱闸并关闭使能
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

// 所有电机打开抱闸并打开使能
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

// 单个电机使能
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

// 单个电机上锁
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

// 单个电机解锁
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

// 上升
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

// 下降
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

// 连续位置控制
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

// 连续位置控制(PID控制)
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

// 缓慢的连续位置控制(PID控制)
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

// 获取所有电机编码器脉冲的平均值
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

// 更新所有电机编码器读数
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

// 获取中位缸伸长长度
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

// 运动学正解获取姿态 x y z roll pitch yaw
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

// 电机上升下降的PID控制函数
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

// 结束运动后回中
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

// PID控制器初始化
void DialogMotionControl::PidControllerInit()
{
	for (int i = 0;i < AXES_COUNT;++i)
	{
		MyPidParaInit(&MotionLocationPidControler[i]);
	}
}

// 所有电机停转
bool DialogMotionControl::ServoStop()
{
	StopRiseDownMove();
	LockServo();
	return true;
}

// 单个电机停转
bool DialogMotionControl::ServoSingleStop(int index)
{
	enableMove = false;
	double vel = 0;
	SetMotionVeloctySingle(index, vel);
	return true;
}

// 停止上升或者下降的PID控制
void DialogMotionControl::StopRiseDownMove()
{
	enableMove = false;
	isrising = false;
	isfalling = false;
	double vel[AXES_COUNT];
	memset(vel, 0, sizeof(double) * AXES_COUNT);
	SetMotionVelocty(vel, AXES_COUNT);
}

// 所有缸是否位于底部
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

// 读取所有接近开关状态
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

// 检查六自由度平台状态
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

// 六自由度平台开机自检
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
		//下降
		AllTestDown();
		break;
	case SIXDOF_STATUS_MIDDLE:
		AllTestDown();
		break;
	case SIXDOF_STATUS_RUN:
		//回中
		//MoveToLocation(lastpulse, AXES_COUNT, false);
		//下降
		AllTestDown();
		break;
	case SIXDOF_STATUS_ISRISING:
		//下降
		AllTestDown();
		break;
	case SIXDOF_STATUS_ISFALLING:
		//下降
		AllTestDown();
		break;
	default:
		break;
	}
	isSelfTest = true;
	return true;
}

// 测试所有硬件
void DialogMotionControl::TestHardware()
{
#if IS_BIG_MOTION
	sixdofDioAndCount.BigMotionTest();
#else
	sixdofDioAndCount.Test();
#endif
}
