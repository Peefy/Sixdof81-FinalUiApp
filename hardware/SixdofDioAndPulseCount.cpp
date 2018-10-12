
#include "stdafx.h"
#include "SixdofDioAndPulseCount.h"

#define ASSERT_INDEX(index) if (index < 0 || index >= SXIDOF_MOTION_NUM) return;

UserPCI1750_OutputPort MotionLockOutPorts[SXIDOF_MOTION_NUM] = 
{
	UserPCI1750_IDO0,
	UserPCI1750_IDO2,
	UserPCI1750_IDO4,
	UserPCI1750_IDO6,
	UserPCI1750_IDO8,
	UserPCI1750_IDO10,
};

UserPCI1750_OutputPort MotionEnableOutPorts[SXIDOF_MOTION_NUM] = 
{
	UserPCI1750_IDO1,
	UserPCI1750_IDO3,
	UserPCI1750_IDO5,
	UserPCI1750_IDO7,
	UserPCI1750_IDO9,
	UserPCI1750_IDO11,
};

UserPCI1750_InputPort SwitchInPorts[SXIDOF_MOTION_NUM] = 
{
	UserPCI1750_IDI0,
	UserPCI1750_IDI2,
	UserPCI1750_IDI4,
	UserPCI1750_IDI6,
	UserPCI1750_IDI8,
	UserPCI1750_IDI10,
};

UserPCI1723_AVO_Channel MotionAnalogVotiageOutPorts[SXIDOF_MOTION_NUM] = 
{
	UserPCI1723_AVO_Channel0,
	UserPCI1723_AVO_Channel1,
	UserPCI1723_AVO_Channel2,
	UserPCI1723_AVO_Channel3,
	UserPCI1723_AVO_Channel4,
	UserPCI1723_AVO_Channel5,
};

UserPCI1723_DIO_Channel BigMotionSwitchInPorts[SXIDOF_MOTION_NUM] =
{
	UserPCI1723_DIO_Channel8,
	UserPCI1723_DIO_Channel9,
	UserPCI1723_DIO_Channel10,
	UserPCI1723_DIO_Channel11,
	UserPCI1723_DIO_Channel12,
	UserPCI1723_DIO_Channel13,
};

UserPCI1723_DIO_Channel BigMotionAlarmInPort = UserPCI1723_DIO_Channel14;
UserPCI1723_DIO_Channel BigMotionBeiYongInPort = UserPCI1723_DIO_Channel15;

UserPCI1723_DIO_Channel BigMotionEnableOutPort[SXIDOF_MOTION_NUM] = 
{
	UserPCI1723_DIO_Channel0,
	UserPCI1723_DIO_Channel1,
	UserPCI1723_DIO_Channel2,
	UserPCI1723_DIO_Channel3,
	UserPCI1723_DIO_Channel4,
	UserPCI1723_DIO_Channel5,
};

UserPCI1723_DIO_Channel BigMotionStartOutPort = UserPCI1723_DIO_Channel6;
UserPCI1723_DIO_Channel BigMotionCheckStartOutPort = UserPCI1723_DIO_Channel7;

SixdofDioAndCount::SixdofDioAndCount()
{
	DataInit();
	Init();
}

SixdofDioAndCount::~SixdofDioAndCount()
{
	if (disposed == false)
	{
		Close();
	}
}

void SixdofDioAndCount::DataInit()
{
	for (auto i = 0; i < SXIDOF_MOTION_NUM; ++i)
	{
		pulseCounts[i] = 0;
	}
}

bool SixdofDioAndCount::Init()
{
	bool result = true;
	for (int i = 0; i < SIXDOF_PCI2394_NUM ;++i)
	{
		result = result && pci2394Cards[i].Init(i);
	}
	result = result && pci1723Card.Init();
	result = result && pci1750Card.Init();
	InitStatus();
	return result;
}

void SixdofDioAndCount::InitStatus()
{
	double vels[6] = {0, 0, 0, 0, 0, 0};
	SetMotionVel(vels);
	for (int i = 0; i < SXIDOF_MOTION_NUM; i++)
	{
		BigMotionEnable(0, false);
		SetMotionLockBit(i, false);
		SetMotionEnableBit(i, false);
	}
	Start(false);
	CheckStart(false);
}

bool SixdofDioAndCount::Close()
{
	try
	{	
		InitStatus();
		
		for (auto i = 0; i < SIXDOF_PCI2394_NUM ;++i)
		{
			pci2394Cards[i].Close();
		}
		pci1723Card.Close();
		pci1750Card.Close();
	}
	catch (exception* e)
	{
		printf(e->what());
		return false;
	}
	return true;
}

bool SixdofDioAndCount::Test()
{
	bool bit = true;
	for (int i = 0; i < SXIDOF_MOTION_NUM; i++)
	{
		SetMotionEnableBit(i, 1);
		SetMotionLockBit(i, 1);	
	}
	auto r = bit;
	
	r = bit;
	bool kbits[SXIDOF_MOTION_NUM] = { true,true,true,true,true,true };
	ReadKBit(kbits);
	r = bit;
	Sleep(1000);
	double vels[6] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
	SetMotionVel(vels);
	double vels0[6] = {0, 0, 0, 0, 0, 0};
	SetMotionVel(vels0);
	r = bit;
	auto count = ReadPulseCount();
	ULONG count0 = count[0];
	ULONG count1 = count[1];
	ULONG count2 = count[2];
	ULONG count3 = count[3];
	ULONG count4 = count[4];
	ULONG count5 = count[5];
	r = bit;
	for (int i = 0; i < SXIDOF_MOTION_NUM; i++)
	{
		SetMotionEnableBit(i, 0);
		SetMotionLockBit(i, 0);
	}
	return true;
}

ULONG * SixdofDioAndCount::ReadPulseCount()
{
	for (auto i = 0; i < SIXDOF_PCI2394_NUM; ++i)
	{
		pci2394Cards[i].RenewCount();
		auto pulses = pci2394Cards[i].CountValue;
		auto offset = SXIDOF_MOTION_NUM / SIXDOF_PCI2394_NUM;
		memcpy(pulseCounts + i * offset, pulses, sizeof(ULONG) * offset);
	}
	return pulseCounts;
}

void SixdofDioAndCount::ClearPulseCount()
{
	for (auto i = 0; i < SIXDOF_PCI2394_NUM; ++i)
	{
		pci2394Cards[i].ClearCount();
	}
}

void SixdofDioAndCount::SetMotionLockBit(int index, bool bit)
{
	ASSERT_INDEX(index);
	pci1750Card.WriteBit(MotionLockOutPorts[index], bit);
}

void SixdofDioAndCount::SetMotionLockBit(bool* bits)
{
	for (auto i = 0;i < SXIDOF_MOTION_NUM;++i)
	{
		pci1750Card.WriteBit(MotionLockOutPorts[i], bits[i]);
	}
}

void SixdofDioAndCount::SetMotionEnableBit(int index, bool bit)
{
	ASSERT_INDEX(index);
	pci1750Card.WriteBit(MotionEnableOutPorts[index], bit);
}

void SixdofDioAndCount::SetMotionEnableBit(bool* bits)
{
	for (auto i = 0;i < SXIDOF_MOTION_NUM; ++i)
	{
		pci1750Card.WriteBit(MotionEnableOutPorts[i], bits[i]);
	}
}

void SixdofDioAndCount::ReadKBit(int index, bool* bit)
{
	ASSERT_INDEX(index);
	pci1750Card.ReadBit(SwitchInPorts[index], bit);
}

void SixdofDioAndCount::ReadKBit(bool* bits)
{
	bool allBits[DI_BIT_PORT_COUNT];
	pci1750Card.ReadAllBits(allBits);
	for (auto i = 0;i < SXIDOF_MOTION_NUM;++i)
	{
		bits[i] = allBits[SwitchInPorts[i]];
	}
}

void SixdofDioAndCount::SetMotionVel(double * vels)
{
	double setV[AO_V_OUT_CHANNEL_COUNT] = {0};
	for (auto i = 0;i < SXIDOF_MOTION_NUM; ++i)
	{
		setV[(int)MotionAnalogVotiageOutPorts[i]] = vels[i];
	}
	pci1723Card.WriteAnalogVotiageData(setV);
}

void SixdofDioAndCount::SetMotionVel(int index, double vel)
{
	ASSERT_INDEX(index);
	pci1723Card.WriteAnalogVotiageData(MotionAnalogVotiageOutPorts[index], vel);
}

void SixdofDioAndCount::EnableAllMotor(bool isEnable)
{
    for (int i = 0; i < SXIDOF_MOTION_NUM; i++)
    {     
        SetMotionEnableBit(i, isEnable);
		SetMotionEnableBit(i, isEnable);
    }
	//SetMotionLockBit(3, isEnable);
}

void SixdofDioAndCount::BigMotionEnable(int index, bool bit)
{
	ASSERT_INDEX(index);
	pci1723Card.WriteBit(BigMotionEnableOutPort[index], bit);
}

void SixdofDioAndCount::BigMotionEnable(bool* bits)
{
	for (auto i = 0;i < SXIDOF_MOTION_NUM; ++i)
	{
		pci1723Card.WriteBit(BigMotionEnableOutPort[i], bits[i]);
	}
}

void SixdofDioAndCount::BigMotionReadKBit(int index, bool* bit)
{
	ASSERT_INDEX(index);
	pci1723Card.ReadBit(BigMotionSwitchInPorts[index], bit);
}

void SixdofDioAndCount::BigMotionReadKBit(bool* bits)
{
	bool allBits[DI_BIT_PORT_COUNT];
	pci1723Card.ReadAllBits(allBits);
	for (auto i = 0;i < SXIDOF_MOTION_NUM;++i)
	{
		bits[i] = allBits[BigMotionSwitchInPorts[i]];
	}
}

void SixdofDioAndCount::BigMotionEnableAllMotor(bool isEnable)
{
	for (int i = 0; i < SXIDOF_MOTION_NUM; i++)
	{
		BigMotionEnable(i, isEnable);
	}
}

bool SixdofDioAndCount::BigMotionReadAlarm()
{
	bool bit = false;
	pci1723Card.ReadBit(BigMotionAlarmInPort, &bit);
	return bit;
}

void SixdofDioAndCount::Start(bool isStart)
{
	pci1723Card.WriteBit(BigMotionStartOutPort, isStart);
}

void SixdofDioAndCount::CheckStart(bool isStart)
{
	pci1723Card.WriteBit(BigMotionCheckStartOutPort, isStart);
}

bool SixdofDioAndCount::BigMotionTest()
{
	Start(true);
	CheckStart(true);
	bool bit = true;
	for (int i = 0;i < 6 ;++i)
	{
		BigMotionEnable(i, 1);
	}
	auto r = bit;
	bool kbits[SXIDOF_MOTION_NUM] = { true,true,true,true,true,true };
	BigMotionReadKBit(kbits);
	r = bit;
	double vels[6] = {0.05, 0, 0, 0.1, 0, 0};
	SetMotionVel(vels);
	double vels0[6] = {0, 0, 0, 0, 0, 0};
	SetMotionVel(vels0);
	r = bit;
	auto count = ReadPulseCount();
	long count0 = count[3];
	r = bit;
	for (int i = 0;i < 6 ;++i)
	{
		BigMotionEnable(i, 0);
	}
	r = bit;
	Start(false);
	CheckStart(false);
	return true;
}
