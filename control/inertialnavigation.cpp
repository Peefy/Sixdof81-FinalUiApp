
#include "stdafx.h"
#include "inertialnavigation.h"
#include "Com.h"
#include "pid.h"

#define JUDGE_IS_START   if(IsRS422Start == false) return;
#define JUDGE_IS_RECIEVE if(IsRecievedData == false) return;

InertialNavigation::InertialNavigation()
{
	DataInit();
}

InertialNavigation::~InertialNavigation()
{
	if (disposed == false)
	{
		Dispose();                           
	}
}

string InertialNavigation::GetIntroduction()
{
	return "POS-GX7100";
}

bool InertialNavigation::Open()
{
	IsRS422Start = OpenCOMDevice(RS422_PORT_NUMBER, RS422_PORT_BAUDRATE) == 0;
	return IsRS422Start;
}

bool InertialNavigation::Close()
{
	CloseCOMDevice();
	IsRS422Start = false;
	return IsRS422Start;
}

void InertialNavigation::RenewData()
{
	static char chrTemp[RS422_BUFFER_LENGTH];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;
	if (IsRS422Start == false)
	{
		return;
	}
	auto nowlength = CollectUARTData(RS422_PORT_NUMBER, chrTemp);
	usRxLength += nowlength;
	while (usRxLength >= RS422_DATA_PACKAGE_LEGNTH)
	{
		if (chrTemp[0] != RS422_DATA_HEAD_ONE)
		{
			usRxLength--;
			memcpy(&chrTemp[0], &chrTemp[1], usRxLength);                        
			continue;
		}
		if(chrTemp[1] == RS422_DATA_HEAD_TWO)
		{
			memcpy(&data, &chrTemp[0], RS422_DATA_PACKAGE_LEGNTH);
		}
		usRxLength -= RS422_DATA_PACKAGE_LEGNTH;
		memcpy(&chrTemp[0], &chrTemp[RS422_DATA_PACKAGE_LEGNTH], usRxLength);    
		DecodeData();
		IsRecievedData = true;
	}
}

int InertialNavigation::GetBufferLength()
{
	return sizeof(RS422DataPackage);
}

void InertialNavigation::SetDefaultAlignment(double lat, double lon, double height)
{
	JUDGE_IS_START;
	RS422SendString("$set gpslever " + to_string(lat) + " " + 
		to_string(lon) + " " + to_string(height) + "*");
}

void InertialNavigation::SetGpsPoleLength(double x, double y, double z)
{
	JUDGE_IS_START;
	RS422SendString("$set gpslever " + to_string(x) + " " + 
		to_string(y) + " " + to_string(z) + "*");
}

void InertialNavigation::SetAngleError(double pitch, double roll, double yaw)
{
	JUDGE_IS_START;
	RS422SendString("$set misali " + to_string(pitch) + " " +  
		to_string(roll) + " " + to_string(yaw) + "*");
}

void InertialNavigation::SetAccOffset(double x, double y, double z)
{
	JUDGE_IS_START;
	RS422SendString("$set acc " + to_string(x) + " " + 
		to_string(y) + " " + to_string(z) + "*");
}

void InertialNavigation::SetGyroOffset(double x, double y, double z)
{
	JUDGE_IS_START;
	RS422SendString("$set gyro " + to_string(x) + " " + 
		to_string(y) + " " + to_string(z) + "*");
}

void InertialNavigation::SetDataRefreshFreq(DataRefreshFreq freq)
{
	JUDGE_IS_START;
	RS422SendString("$set fre " + to_string((int)freq) + "*");
}

void InertialNavigation::SetRS422BaudRate(RS422BaudRate bps)
{
	JUDGE_IS_START;
	RS422SendString("$set bps " + to_string((int)bps) + "*");
}

void InertialNavigation::StartSwing()
{
	JUDGE_IS_START;
	RS422SendString("$align swing*");
}

void InertialNavigation::StartGps()
{
	JUDGE_IS_START;
	RS422SendString("$nav gps*");
}

void InertialNavigation::StartSins()
{
	JUDGE_IS_START;
	RS422SendString("$nav sins*");
}

void InertialNavigation::Dispose()
{
	disposed = true;	
}

void InertialNavigation::RS422SendString(string strs)
{
	SendUARTMessageLength(RS422_PORT_NUMBER, strs.c_str(), strs.length());
}

void InertialNavigation::DecodeData()
{
	Roll = data.Roll * ANGLE_SCALE / 3600.0;
	Yaw = data.Yaw * ANGLE_SCALE / 3600.0;
	Pitch = data.Pitch * ANGLE_SCALE / 3600.0;
	Lon = data.Longitude * LATLON_SCALE / 3600.0;
	Lan = data.Latitude * LATLON_SCALE / 3600.0;
	IsGyroError = STATUS_BIT_GET(data.StateByte, GYRO_ERR_BIT);
	IsAccError = STATUS_BIT_GET(data.StateByte, ACC_ERR_BIT);
	IsCpuError = STATUS_BIT_GET(data.StateByte, CPU_ERR_BIT);
	IsSatelliteDataError = STATUS_BIT_GET(data.StateByte, SATELLITE_DATA_ERR_BIT);
	IsAlignment = STATUS_BIT_GET(data.StateByte, ALIGNMENT_BIT);
	IsInertialError = STATUS_BIT_GET(data.StateByte, INERTIAL_ERR_BIT);
	IsNavigationError = STATUS_BIT_GET(data.StateByte, NAVIGATION_ERR_BIT);
}

void InertialNavigation::DataInit()
{
	Roll = 0;
	Yaw = 0;
	Pitch = 0;
	IsRecievedData = false;
	IsGyroError = false;
	IsAccError = false;
	IsCpuError = false;
	IsSatelliteDataError = false;
	IsAlignment = false;
	IsInertialError = false;
	IsNavigationError = false;
	IsRS422Start = false;
}

void InertialNavigation::PidOut(double * roll, double *yaw, double * pitch)
{
	const double p = 0.0001;
	const double i = 0.00001;
	const double d = 0.0;
	const double finalRoll = 0;
	const double finalPitch = 0;
	const double finalYaw = 0;
	static double initRoll = 0;
	static double initPitch = 0;
	static double initYaw = 0;
	static PID_Type rollPid = {p, i, d};
	static PID_Type pitchPid = {p, i, d};
	static PID_Type yawPid = {p, i, d};
	JUDGE_IS_RECIEVE;
	*roll = MyDeltaPIDWithNoDelta(&rollPid, Roll, finalRoll);
	//*yaw = MyDeltaPIDWithNoDelta(&yawPid, Yaw, finalYaw);
	*pitch = MyDeltaPIDWithNoDelta(&pitchPid, Pitch, finalPitch);
}
