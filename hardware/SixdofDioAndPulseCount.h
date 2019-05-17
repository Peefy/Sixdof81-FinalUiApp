
#ifndef _SIXDOF_DIO_AND_PULSE_COUNT_H_
#define _SIXDOF_DIO_AND_PULSE_COUNT_H_

#include <memory>

// 包含硬件3块板卡的头文件
#include "UserPCI1723.h"
#include "UserPCI1750.h"
#include "UserPCI2394.h"

using namespace std;

// PCI2394脉冲采集卡个数
#define SIXDOF_PCI2394_NUM 2
// 六自由度平台电机个数
#define SXIDOF_MOTION_NUM 6

// 六自由度平台数字量IO，编码器计数，模拟量控制电机包装类(不保证线程安全)
class SixdofDioAndCount
{
public:
	SixdofDioAndCount();
	~SixdofDioAndCount();
	// 初始化板卡
	bool Init();
	// 初始化板卡的默认IO
	void InitStatus();
	// 关闭板卡
	bool Close();
	// 测试所有板卡
	bool Test();
	// 读取所有电机编码器脉冲读数
	ULONG * ReadPulseCount();
	// 所有电机编码器读数清零
	void ClearPulseCount();
	// 设置电机抱闸开关
	void SetMotionLockBit(int index, bool bit);
	// 设置电机抱闸开关
	void SetMotionLockBit(bool* bits);
	// 设置电机使能开关
	void SetMotionEnableBit(int index, bool bit);
	// 设置电机使能开关
	void SetMotionEnableBit(bool* bits);
	// 读取接近开关状态
	void ReadKBit(int index, bool* bit);
	// 读取接近开关状态
	void ReadKBit(bool* bits);
	// 设置电机速度
	void SetMotionVel(double * vels);
	// 设置电机速度
	void SetMotionVel(int index, double vel);
	// 使能所有电机
    void EnableAllMotor(bool isEnable);
	// 仅两块板卡控制模式 - 使能电机
	void BigMotionEnable(int index, bool bit);
	// 仅两块板卡控制模式 - 使能所有电机
	void BigMotionEnable(bool* bits);
	// 仅两块板卡控制模式 - 读取接近开关状态
	void BigMotionReadKBit(int index, bool* bit);
	// 仅两块板卡控制模式 - 读取接近开关状态
	void BigMotionReadKBit(bool* bits);
	// 仅两块板卡控制模式 - 使能所有电机
	void BigMotionEnableAllMotor(bool isEnable);
	// 仅两块板卡控制模式 - 读取是否报警
	bool BigMotionReadAlarm();
	// 仅两块板卡控制模式 - 开启控制
	void Start(bool isStart);
	// 仅两块板卡控制模式 - 关闭控制
	void CheckStart(bool isStart);
	// 仅两块板卡控制模式 - 
	bool BigMotionTest();

private:
	// 是否释放所有资源
	bool disposed;
	// 电机编码器读数
	ULONG pulseCounts[SXIDOF_MOTION_NUM];	
	// PCI2394
	UserPCI2394 pci2394Cards[SIXDOF_PCI2394_NUM];
	// PCI1723
	UserPCI1723 pci1723Card;
	// PCI1750
	UserPCI1750 pci1750Card;
	// 数据初始化
	void DataInit();
};

#endif
