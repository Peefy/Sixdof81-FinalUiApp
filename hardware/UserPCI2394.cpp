
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
	return "计数卡,检测编码器信号记录缸体位置,参与闭环控制";
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
		CNTPara[nChannel].lResetMode = PCI2394_RESETMODE_MIDDLE; // 计数器复位到0x00000000
		CNTPara[nChannel].bOverflowLock = TRUE; // 上溢锁定
		CNTPara[nChannel].bUnderflowLock = TRUE; // 下溢锁定
		CNTPara[nChannel].bDigitFilter = TRUE; // 差分输入是否进行数字滤波(DF) TRUE=过滤
		CNTPara[nChannel].lLatchMode = PCI2394_LATCHMODE_SOFT; // 软件锁存计数器数据 SoftWare
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
		if (CountValue[nChannel] >= (ULONG)(0x80000000))
			CountValue[nChannel] = (ULONG)(0x80000000);
		CountValue[nChannel] = (ULONG)(0x80000000) - CountValue[nChannel];
	}
}

void UserPCI2394::ClearCount()
{
	for(nChannel = 0; nChannel < SIXDOF_USE_COUNT_CHANNEL; nChannel++)
	{
		PCI2394_ResetDeviceCNT(hDevice, nChannel);
	}
}
