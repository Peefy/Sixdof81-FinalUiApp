

#ifndef _PCI2394_H_
#define _PCI2394_H_

#include "UserPCICard.h"

#include "../PCI2394.h"

#define SIXDOF_USE_COUNT_CHANNEL 3

class UserPCI2394 : public UserPCICard
{
public:
	UserPCI2394();
	~UserPCI2394();
	string GetIntroduction();
	bool Init();
	bool Init(int deviceID);
	bool Close();
	void RenewCount();
	void ClearCount();
	int DeviceID;
	ULONG CountValue[SIXDOF_USE_COUNT_CHANNEL]; // 计数器当前新值
private:
	bool disposed;
	HANDLE hDevice;
	int nChannel;
	char Key;
	PCI2394_PARA_CNT CNTPara[SIXDOF_USE_COUNT_CHANNEL];
};

#endif
