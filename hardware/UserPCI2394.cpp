
#include "stdafx.h"
#include "UserPCI2394.h"

UserPCI2394::UserPCI2394()
{
	
}

UserPCI2394::~UserPCI2394()
{
	if (disposed == false)
	{
		Close();
	}
}

string UserPCI2394::GetIntroduction()
{
	return "������,���������źż�¼����λ��,����ջ�����";
}

bool UserPCI2394::Init()
{
	return Init(1);
}

bool UserPCI2394::Init(int deviceID)
{
	DeviceID = deviceID;
	hDevice = PCI2394_CreateDevice(DeviceID);
	for(nChannel = 0; nChannel < SIXDOF_USE_COUNT_CHANNEL; nChannel++)
	{
		CNTPara[nChannel].lCNTMode = PCI2394_CNTMODE_1_PULSE;
		CNTPara[nChannel].lResetMode = PCI2394_RESETMODE_MIDDLE; // ��������λ��0x00000000
		CNTPara[nChannel].bOverflowLock = TRUE; // ��������
		CNTPara[nChannel].bUnderflowLock = TRUE; // ��������
		CNTPara[nChannel].bDigitFilter = TRUE; // ��������Ƿ���������˲�(DF) TRUE=����
		CNTPara[nChannel].lLatchMode = PCI2394_LATCHMODE_SOFT; // ���������������� SoftWare
		CNTPara[nChannel].lIndexReset = 0;
		auto err = PCI2394_InitDeviceCNT(hDevice, &CNTPara[nChannel], nChannel);
	}
	ClearCount();
	return true;
}

bool UserPCI2394::Close()
{
	PCI2394_ReleaseDevice(hDevice);
	disposed = true;
	return true;
}

void UserPCI2394::RenewCount()
{
	for(nChannel = 0; nChannel < SIXDOF_USE_COUNT_CHANNEL; nChannel++)
	{
		auto err = PCI2394_GetDeviceCNT(hDevice, &CountValue[nChannel], nChannel);
#if IS_REVERSE_CONTROL
		if (CountValue[nChannel] <= (ULONG)(0x80000000))
			CountValue[nChannel] = (ULONG)(0x80000000);
		CountValue[nChannel] =  CountValue[nChannel] - (ULONG)(0x80000000);
#else
		if (CountValue[nChannel] >= (ULONG)(0x80000000))
			CountValue[nChannel] = (ULONG)(0x80000000);
		CountValue[nChannel] = (ULONG)(0x80000000) - CountValue[nChannel];
#endif
		
	}
}

void UserPCI2394::ClearCount()
{
	for(nChannel = 0; nChannel < SIXDOF_USE_COUNT_CHANNEL; nChannel++)
	{
		PCI2394_ResetDeviceCNT(hDevice, nChannel);
	}
}
