

#ifndef _PCI2394_H_
#define _PCI2394_H_

#include "UserPCICard.h"

#include "../PCI2394.h"

// һ��PCI2394�忨ʹ�õ�ͨ������һ������忨
#define SIXDOF_USE_COUNT_CHANNEL 3

class UserPCI2394 : public UserPCICard
{
public:
	UserPCI2394();
	~UserPCI2394();
	// ��ȡ���
	string GetIntroduction();
	// ��ʼ���忨
	bool Init();
	// ��ʼ��id�İ忨
	bool Init(int deviceID);
	// �رհ忨
	bool Close();
	// ���µ������������
	void RenewCount();
	// �����������������
	void ClearCount();
	// �豸��
	int DeviceID;
	// �忨��������ǰ��ֵ
	ULONG CountValue[SIXDOF_USE_COUNT_CHANNEL]; 
private:
	bool disposed;
	HANDLE hDevice;
	int nChannel;
	char Key;
	PCI2394_PARA_CNT CNTPara[SIXDOF_USE_COUNT_CHANNEL];
};

#endif
