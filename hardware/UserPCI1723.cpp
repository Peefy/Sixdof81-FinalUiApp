
#include "stdafx.h"
#include "UserPCI1723.h"

#define CHK_RESULT(ret) {if(BioFailed(ret))break;}
#define ASSERT_CHANNEL(channel) if (channel < 0 || channel > 7) return;
#define ASSERT_RANGE_CHANNEL(channel) if (channel < 0 || channel > 15) return;

const wchar_t* PCI1723DeviceDescription = L"PCI-1723,BID#15";
const wchar_t* PCI1723ProfilePath = L"DemoDevice.xml";

UserPCI1723::UserPCI1723()
{
	instantAoCtrl = InstantAoCtrl::Create();
	instantDoCtrl = InstantDoCtrl::Create();
	instantDiCtrl = InstantDiCtrl::Create();
	Init();
}

UserPCI1723::~UserPCI1723()
{
	if (disposed == false)
	{
		Close();
	}
}

string UserPCI1723::GetIntroduction()
{
	return "D/A卡输出+-10V电压控制信号";
}

bool UserPCI1723::Init()
{
	ErrorCode ret = Success;
	do 
	{
		DeviceInformation devInfo(PCI1723DeviceDescription);
		ret = instantAoCtrl->setSelectedDevice(devInfo);
		CHK_RESULT(ret);
		ret = instantAoCtrl->LoadProfile(PCI1723ProfilePath);
		CHK_RESULT(ret);
		ret = instantDoCtrl->setSelectedDevice(devInfo);
		CHK_RESULT(ret);
		ret = instantDoCtrl->LoadProfile(PCI1723ProfilePath);
		CHK_RESULT(ret);
		ret = instantDiCtrl->setSelectedDevice(devInfo);
		CHK_RESULT(ret);
		ret = instantDiCtrl->LoadProfile(PCI1723ProfilePath);
		CHK_RESULT(ret);
	} while (false);
	return ret == Success;
}

bool UserPCI1723::Close()
{
	instantAoCtrl->Cleanup();
	instantAoCtrl->Dispose();
	instantDiCtrl->Dispose();
	instantDoCtrl->Dispose();
	disposed = true;
	return true;
}

void UserPCI1723::WriteAnalogVotiageData(UserPCI1723_AVO_Channel channel, double value)
{
	ASSERT_CHANNEL(channel);
#if IS_REVERSE_CONTROL
	double rawData[] = {ANALOG_OUT_DIR * -value};
#else
	double rawData[] = {ANALOG_OUT_DIR * value};
#endif
	instantAoCtrl->Write(channel, 1, &rawData[0]);
}

void UserPCI1723::WriteAnalogVotiageData(double* values)
{
	double rawData[AO_V_OUT_CHANNEL_COUNT] = {};
	for (auto i = 0;i < AO_V_OUT_CHANNEL_COUNT; ++i)
	{
#if IS_REVERSE_CONTROL
		rawData[i] = ANALOG_OUT_DIR * -values[i];
#else
		rawData[i] = ANALOG_OUT_DIR * values[i];
#endif
	}
	instantAoCtrl->Write(AO_V_OUT_GROUP_START_INDEX, AO_V_OUT_CHANNEL_COUNT, &rawData[0]);
}

void UserPCI1723::WriteBit(UserPCI1723_DIO_Channel port, bool bit)
{
	ASSERT_RANGE_CHANNEL(port);
	uint8 writeData = bit == true ? 1 : 0;
	int32 writePort = port <= UserPCI1723_DIO_Channel7 ? 0 : 1;
	int32 writeBit = port - writePort * 8;
	instantDoCtrl->WriteBit(writePort, writeBit, writeData);
}

void UserPCI1723::ReadBit(UserPCI1723_DIO_Channel port, bool* bit)
{
	ASSERT_RANGE_CHANNEL(port);
	uint8 readData = 0;
	int32 readPort = port <= UserPCI1723_DIO_Channel7 ? 0 : 1;
	int32 readBit = port - readPort * 8;
	instantDiCtrl->ReadBit(readPort, readBit, &readData);
	*bit = readData == 1 ? true : false;
}

void UserPCI1723::WriteAllBits(bool* bits)
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

void UserPCI1723::ReadAllBits(bool* bits)
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
