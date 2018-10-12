
#ifndef _SIXDOF_DIO_AND_PULSE_COUNT_H_
#define _SIXDOF_DIO_AND_PULSE_COUNT_H_

#include <memory>

#include "UserPCI1723.h"
#include "UserPCI1750.h"
#include "UserPCI2394.h"

using namespace std;

#define SIXDOF_PCI2394_NUM 2

#define SXIDOF_MOTION_NUM 6

class SixdofDioAndCount
{
public:
	SixdofDioAndCount();
	~SixdofDioAndCount();
	bool Init();
	void InitStatus();
	bool Close();
	bool Test();
	ULONG * ReadPulseCount();
	void ClearPulseCount();
	void SetMotionLockBit(int index, bool bit);
	void SetMotionLockBit(bool* bits);
	void SetMotionEnableBit(int index, bool bit);
	void SetMotionEnableBit(bool* bits);
	void ReadKBit(int index, bool* bit);
	void ReadKBit(bool* bits);
	void SetMotionVel(double * vels);
	void SetMotionVel(int index, double vel);

    void EnableAllMotor(bool isEnable);

	void BigMotionEnable(int index, bool bit);
	void BigMotionEnable(bool* bits);
	void BigMotionReadKBit(int index, bool* bit);
	void BigMotionReadKBit(bool* bits);
	void BigMotionEnableAllMotor(bool isEnable);
	bool BigMotionReadAlarm();
	void Start(bool isStart);
	void CheckStart(bool isStart);
	bool BigMotionTest();

private:
	bool disposed;
	ULONG pulseCounts[SXIDOF_MOTION_NUM];	
	UserPCI2394 pci2394Cards[SIXDOF_PCI2394_NUM];
	UserPCI1723 pci1723Card;
	UserPCI1750 pci1750Card;
	void DataInit();
};

#endif
