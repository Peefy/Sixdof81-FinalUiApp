
#include "stdafx.h"
#include "illusion.h"

#include <time.h>
#include <fstream>
#include <stdio.h>

#include "../config/inihelper.h"

#define IS_USE_WASHOUT 0
#define IS_FILE_RECORD 0

UdpClient udpClient = UdpClient(UDP_SELF_PORT);
#if IS_USE_WASHOUT
WashoutAlgorithm flightwashout;
#endif

#if IS_FILE_RECORD
char filename[100] = "";
#endif

IllusionDataAdapter::IllusionDataAdapter()
{
	DataPackageLength = sizeof(IllusionPackage);
	SendDataPackageLength = sizeof(IllusionSendPackage);
	SendToData.flagstart = ILLUSION_FLAG_START_INT32;
	SendToData.flagend = ILLUSION_FLAG_END_INT32;
	DataInit();
	ReadIpAndPortFromFile();
}

IllusionDataAdapter::~IllusionDataAdapter()
{

}

void IllusionDataAdapter::DataInit()
{
	SelfPort = UDP_SELF_PORT;
	VisionPort = UDP_PORT;
	SelfIp = UDP_SELF_IP_STRING;
	VisionIp = UDP_IP_STRING;
	IsDirectControl = false;
#if IS_FILE_RECORD
	time_t currtime = time(NULL);
	struct tm* p = gmtime(&currtime);
	sprintf_s(filename, "./datas/illusiondata%d-%d-%d-%d-%d-%d.txt", p->tm_year + 1990, p->tm_mon + 1,
		p->tm_mday, p->tm_hour + 8, p->tm_min, p->tm_sec);
#endif

}

void IllusionDataAdapter::RenewData()
{
	static char recieveBuffer[ILLUSION_RECIEVE_BUFFER_MAX];
	static int length = sizeof(IllusionPackage);
	static unsigned short usRxLength = 0;
	int nowlength = udpClient.RecieveFrom(recieveBuffer);
	usRxLength += nowlength;
	while (usRxLength >= length)
	{
		auto lastData = Data;
		memcpy(&Data, &recieveBuffer[0], length);
		if (Data.flagstart != ILLUSION_FLAG_START_INT32 || 
			Data.flagend != ILLUSION_FLAG_END_INT32)
		{
			Data = lastData;
		}
		else
		{
			RenewInnerData();
		}
		usRxLength -= length; 
		IsRecievedData = true;
	}
}

void IllusionDataAdapter::SendData()
{
	static char buffer[ILLUSION_BUFFER_LENGTH];
	static const char * ip = VisionIp.c_str();
	memcpy(buffer, &SendToData, SendDataPackageLength);
	udpClient.SendTo(VisionPort, ip, buffer, SendDataPackageLength);
}

void IllusionDataAdapter::SendData(bool iswarning, int status, double x, double y, double z, double roll, double yaw, double pitch)
{
	SendToData.iswarning = iswarning == true ? 111 : 0;
	SendToData.status = status * 111;
	SendToData.x = (int)(x / ILLUSION_XYZ_SCALE);
	SendToData.y = (int)(y / ILLUSION_XYZ_SCALE);
	SendToData.z = (int)(z / ILLUSION_XYZ_SCALE);
	SendToData.roll = (int)(roll / ILLUSION_ANGLE_SCALE);
	SendToData.yaw = (int)(yaw / ILLUSION_ANGLE_SCALE);
	SendToData.pitch = (int)(pitch / ILLUSION_ANGLE_SCALE);
	SendData();
}

int IllusionDataAdapter::GetControlCommand() const
{
	return Data.by36;
}

bool IllusionDataAdapter::IsIllusionControl() const
{
	return Data.by35 == 999;
}

void IllusionDataAdapter::SetPoseAngle(double roll, double pitch, double yaw)
{
	platformRoll = roll;
	platformPitch = pitch;
	platformYaw = yaw;
}

void IllusionDataAdapter::RenewInnerData()
{
	// 是否是直控模式
	IsDirectControl = Data.by35 == ILLUSION_IS_DIRECT_CONTROL_INT32;
	planeType = (PlaneType)Data.uPlaneType;
	//角度
	Yaw = 0 * ILLUSION_ANGLE_SCALE;
	Pitch = ILLUSION_RANGE(Data.fyj * ILLUSION_ANGLE_SCALE, -ILLUSION_MAX_ANGLE_DEG, ILLUSION_MAX_ANGLE_DEG);
	Roll = ILLUSION_RANGE(Data.cqj * ILLUSION_ANGLE_SCALE, -ILLUSION_MAX_ANGLE_DEG, ILLUSION_MAX_ANGLE_DEG);
	X = 0;
	Y = 0;
	Z = 0;
	//速度 
	PitchSpeed = ILLUSION_RANGE(Data.hxjs * ILLUSION_SPEED_SCALE, -ILLUSION_MAX_ANGLE_SPEED, ILLUSION_MAX_ANGLE_SPEED);
	YawSpeed = ILLUSION_RANGE(Data.hxjas * ILLUSION_SPEED_SCALE, -ILLUSION_MAX_ANGLE_SPEED, ILLUSION_MAX_ANGLE_SPEED);
	RollSpeed = ILLUSION_RANGE(Data.cqjas * ILLUSION_SPEED_SCALE, -ILLUSION_MAX_ANGLE_SPEED, ILLUSION_MAX_ANGLE_SPEED);
	XSpeed = Data.fyjs * ILLUSION_SPEED_SCALE;
	YSpeed = Data.fyjas * ILLUSION_SPEED_SCALE;
	ZSpeed = Data.cqjs * ILLUSION_SPEED_SCALE;
	//加速度 
	YawAcc = Data.cxas * ILLUSION_ACC_SCALE;
	PitchAcc = Data.cxs * ILLUSION_ACC_SCALE;
	RollAcc = Data.hxas * ILLUSION_ACC_SCALE;
	XAcc = ILLUSION_RANGE(Data.zxs * ILLUSION_ACC_SCALE, -ILLUSION_MAX_XYZ_ACC, ILLUSION_MAX_XYZ_ACC);
	YAcc = ILLUSION_RANGE(Data.zxus * ILLUSION_ACC_SCALE, -ILLUSION_MAX_XYZ_ACC, ILLUSION_MAX_XYZ_ACC);
	ZAcc = ILLUSION_RANGE(Data.hxs * ILLUSION_ACC_SCALE, -ILLUSION_MAX_XYZ_ACC, ILLUSION_MAX_XYZ_ACC);
#if IS_FILE_RECORD
	config::RecordData(filename, XAcc, YAcc, ZAcc, RollSpeed, PitchSpeed, YawSpeed, Roll, Pitch, Yaw, Data.uPlaneType);
#endif
#if IS_USE_WASHOUT
	if (IsDirectControl == true)
	{
		// 直控模式是在飞控模式的基础上增加运动
		XAcc += Data.uAcceVx_mss * EARTH_G * ILLUSION_ACC_SCALE * DIRECT_ACC_SCALE;
		YAcc += Data.uAcceVy_mss * EARTH_G * ILLUSION_ACC_SCALE * DIRECT_ACC_SCALE;
		ZAcc += Data.uAcceVz_mss * EARTH_G * ILLUSION_ACC_SCALE * DIRECT_ACC_SCALE;
		RollSpeed += Data.uAccebx_degs * ILLUSION_SPEED_SCALE;
		PitchSpeed += Data.uAcceby_degs * ILLUSION_SPEED_SCALE;
		YawSpeed += Data.uAccebz_degs * ILLUSION_SPEED_SCALE;
	}
	flightwashout.Do(XAcc, YAcc, ZAcc, RollSpeed, PitchSpeed, YawSpeed, platformRoll, platformYaw, platformPitch);
	Yaw = flightwashout.WashYaw;     //deg
	Pitch = flightwashout.WashPitch; //deg
	Roll = flightwashout.WashRoll;   //deg
	X = flightwashout.WashX;         //mm
	Y = flightwashout.WashY;         //mm
	Z = flightwashout.WashZ;         //mm
#endif
	if (IsDirectControl == true)
	{
		Roll += Data.uAccebx_deg * ILLUSION_ANGLE_SCALE;
		Pitch += Data.uAcceby_deg * ILLUSION_ANGLE_SCALE;
		Yaw += Data.uAccebz_deg * ILLUSION_ANGLE_SCALE;
	}
}

void IllusionDataAdapter::ReadIpAndPortFromFile()
{
	VisionIp = config::ParseStringJsonFromFile(JSON_FILE_NAME, JSON_UDP_IP_KEY);
	SelfIp = config::ParseStringJsonFromFile(JSON_FILE_NAME, JSON_UDP_SELF_IP_KEY);
	int result = config::ParseIntJsonFromFile(JSON_FILE_NAME, JSON_UDP_PORT_KEY);
	if (result != NULL)
	{
		VisionPort = result;
	}
	result = config::ParseIntJsonFromFile(JSON_FILE_NAME, JSON_UDP_SELF_PORT_KEY);
	if (result != NULL)
	{
		SelfPort = result;
	}
	udpClient.SetPortAndBind(SelfPort);
}


