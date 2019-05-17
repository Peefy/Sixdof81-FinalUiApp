

#ifndef _PCI2394_H_
#define _PCI2394_H_

#include "UserPCICard.h"

#include "../PCI2394.h"

// 一块PCI2394板卡使用的通道数，一共两块板卡
#define SIXDOF_USE_COUNT_CHANNEL 3

class UserPCI2394 : public UserPCICard
{
public:
	UserPCI2394();
	~UserPCI2394();
	// 获取简介
	string GetIntroduction();
	// 初始化板卡
	bool Init();
	// 初始化id的板卡
	bool Init(int deviceID);
	// 关闭板卡
	bool Close();
	// 更新电机编码器读数
	void RenewCount();
	// 电机编码器读数清零
	void ClearCount();
	// 设备号
	int DeviceID;
	// 板卡计数器当前新值
	ULONG CountValue[SIXDOF_USE_COUNT_CHANNEL]; 
private:
	bool disposed;
	HANDLE hDevice;
	int nChannel;
	char Key;
	PCI2394_PARA_CNT CNTPara[SIXDOF_USE_COUNT_CHANNEL];
};

#endif
