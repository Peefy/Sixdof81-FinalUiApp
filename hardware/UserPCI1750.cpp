
#include "stdafx.h"
#include "UserPCI1750.h"

#define CHK_RESULT(ret) {if(BioFailed(ret))break;}
#define ASSERT_PORT(port) if (port < 0 || port > 15) return;

const wchar_t* PCI1750DeviceDescription = L"PCI-1750,BID#0";
const wchar_t* PCI1750ProfilePath = L"DemoDevice.xml";

UserPCI1750::UserPCI1750()
{
	instantDoCtrl = InstantDoCtrl::Create();
	instantDiCtrl = InstantDiCtrl::Create();
	Init();
}

UserPCI1750::~UserPCI1750()
{
	if (disposed == false)
	{
		Close();
	}
}

string UserPCI1750::GetIntroduction()
{
	return "IO卡采集:接近开关信号,控制继电器开合,以及电机使能";
}

bool UserPCI1750::Init()
{
	ErrorCode ret = Success;
	do 
	{
		DeviceInformation devInfo(PCI1750DeviceDescription);
		ret = instantDoCtrl->setSelectedDevice(devInfo);
		CHK_RESULT(ret);
		ret = instantDoCtrl->LoadProfile(PCI1750ProfilePath);
		CHK_RESULT(ret);
		ret = instantDiCtrl->setSelectedDevice(devInfo);
		CHK_RESULT(ret);
		ret = instantDiCtrl->LoadProfile(PCI1750ProfilePath);//Loads a profile to initialize the device.
		CHK_RESULT(ret);
	} while (false);
	return ret == Success;
}

bool UserPCI1750::Close()
{
	instantDiCtrl->Dispose();
	instantDoCtrl->Dispose();
	disposed = true;
	return true;
}

void UserPCI1750::WriteBit(UserPCI1750_OutputPort port, bool bit)
{
	ASSERT_PORT(port);
	uint8 writeData = bit == true ? 1 : 0;
	int32 writePort = port <= UserPCI1750_IDO7 ? 0 : 1;
	int32 writeBit = port - writePort * 8;
	instantDoCtrl->WriteBit(writePort, writeBit, writeData);
}

void UserPCI1750::ReadBit(UserPCI1750_InputPort port, bool* bit)
{
	ASSERT_PORT(port);
	uint8 readData = 0;
	int32 readPort = port <= UserPCI1750_IDI7 ? 0 : 1;
	int32 readBit = port - readPort * 8;
	instantDiCtrl->ReadBit(readPort, readBit, &readData);
	*bit = readData == 1 ? true : false;
}

void UserPCI1750::WriteAllBits(bool* bits)
{
	byte datas[DO_GROUP_PORT_COUNT] = {0};
	auto groupincount = DO_BIT_PORT_COUNT / DO_GROUP_PORT_COUNT;
	for (auto i = 0; i < DO_BIT_PORT_COUNT ;++i)
	{
		auto groupIndex = i / groupincount;
		auto bitIndex = i % groupincount;
		if (bits[i] == true)
			VAR_BIT_SETONE(datas[groupIndex], bitIndex);
		else
			VAR_BIT_CLEAN(datas[groupIndex], bitIndex);
	}
	instantDoCtrl->Write(DO_GROUP_PORT_START_INDEX, DO_GROUP_PORT_COUNT, datas);
}

void UserPCI1750::ReadAllBits(bool* bits)
{
	byte datas[DI_GROUP_PORT_COUNT] = {0};
	instantDiCtrl->Read(DI_GROUP_PORT_START_INDEX, DI_GROUP_PORT_COUNT, datas);
	auto groupincount = DO_BIT_PORT_COUNT / DO_GROUP_PORT_COUNT;
	for (auto i = 0;i < DI_GROUP_PORT_COUNT;++i)
	{
		for (auto j = 0;j < groupincount;++j)
		{
			int readBit = VAR_BIT_GET(datas[i], j);
			bool dataBit = readBit == 1 ? true : false;
			bits[i * groupincount + j] = dataBit;
		}	
	}
}
