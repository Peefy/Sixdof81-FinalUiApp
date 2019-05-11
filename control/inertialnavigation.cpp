
#include "stdafx.h"
#include "inertialnavigation.h"
#include "pid.h"
#include "../config/inihelper.h"

#define JUDGE_IS_START   if(IsRS422Start == false) return;
#define JUDGE_IS_RECIEVE if(IsRecievedData == false) return;

#define IS_USE_DELTA_PID 0

#define FRAME_LENGTH 83
#define DATA_NUM 21

static double p = 0.001;
static double i = 0.0001;
static double d = 0.000001;
static double maxAngle = 10.0;
static double minAngle = -10.0;
static PID_Type rollPid = {p, i, d, minAngle, maxAngle};
static PID_Type pitchPid = {p, i, d, minAngle, maxAngle};
static PID_Type yawPid = {p, i, d, minAngle, maxAngle};

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

string InertialNavigation::GetIntroduction() const
{
	return "POS-GX7100";
}

bool InertialNavigation::Open()
{
	IsRS422Start = serialPort.InitPort(RS422_PORT_NUMBER, RS422_PORT_BAUDRATE) == true;
	//IsRS422Start = OpenCOMDevice(RS422_PORT_NUMBER, RS422_PORT_BAUDRATE) == 0;
	//IsRS422Start = serialPort.InitCOM(RS422_PORT_NUMBER, RS422_PORT_BAUDRATE, 1, 0, 8);
	return IsRS422Start;
}

bool InertialNavigation::Open(int port)
{
	IsRS422Start = serialPort.InitPort(port, RS422_PORT_BAUDRATE) == true;
	//IsRS422Start = OpenCOMDevice(port, RS422_PORT_BAUDRATE) == 0;
	//IsRS422Start = serialPort.InitCOM(port, RS422_PORT_BAUDRATE, 1, 0, 8);
	return IsRS422Start;
}

bool InertialNavigation::Close()
{
	//CloseCOMDevice();
	//serialPort.closeCOM();
	IsRS422Start = false;
	return IsRS422Start;
}

bool InertialNavigation::JudgeCheckByte(char* chars)
{
	unsigned char checkbyte = 0;
	for (int i = CHECK_BYTE_CAL_START_INDEX;i <= CHECK_BYTE_CAL_END_INDEX;++i)
	{
		checkbyte += chars[i];
	}
	return checkbyte == chars[CHECK_BYTE_INDEX];
}

void InertialNavigation::RenewData()
{
	static unsigned char chrTemp[RS422_BUFFER_LENGTH] = {0}; 
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;
	if (IsRS422Start == false)
	{
		return;
	}
	auto nowlength = serialPort.GetBytesInCOM();
	unsigned char cRecved = 0;
	for (int i = 0; i < nowlength; ++i)
	{
		serialPort.ReadChar(cRecved);
		chrTemp[i] = cRecved;
	}
	//auto nowlength = CollectUARTData(RS422_PORT_NUMBER, chrTemp);
	//auto nowlength = serialPort.GetCOMData(chrTemp);
	usRxLength += nowlength;
	while (usRxLength >= RS422_DATA_PACKAGE_LEGNTH)
	{
		if (chrTemp[0] != RS422_DATA_HEAD_ONE)
		{
			usRxLength--;
			memcpy(&chrTemp[0], &chrTemp[1], usRxLength);                        
			continue;
		}
		if(chrTemp[1] == RS422_DATA_HEAD_TWO && chrTemp[RS422_DATA_PACKAGE_LEGNTH - 1] == RS422_DATA_TAIL_TWO &&
			chrTemp[RS422_DATA_PACKAGE_LEGNTH - 2] == RS422_DATA_TAIL_ONE //&&
			)//JudgeCheckByte(chrTemp) == true)
		{
			memcpy(&data, &chrTemp[0], RS422_DATA_PACKAGE_LEGNTH);
		}
		usRxLength -= RS422_DATA_PACKAGE_LEGNTH;
		memcpy(&chrTemp[0], &chrTemp[RS422_DATA_PACKAGE_LEGNTH], usRxLength);    
		DecodeData();
		IsRecievedData = true;
	}
}

bool InertialNavigation::GatherData()
{
	if (IsRS422Start == false)
	{
		return false;
	}
	// ����֡�������
	static int uiRemainLength = 0;
	static unsigned long ulFrameNum = 0;
	static unsigned long ulFrameErr = 0;
	static UCHAR chData[READBUFFER + 102400] = {0};
	static UCHAR *pch = chData;
	int i;
	UCHAR chReadData[READBUFFER] = {0};
	//unsigned int uiReceived = (int)serialPort.GetCOMData(chReadData);
	unsigned int uiReceived = serialPort.GetBytesInCOM();
	unsigned char cRecved = 0;
	for (int i = 0; i < uiReceived; ++i)
	{
		serialPort.ReadChar(cRecved);
		chReadData[i] = cRecved;
	}
	if(uiReceived == 0)
	{
		return false;		
	}
	memcpy(pch, chReadData, uiReceived);    //����������chData[]��
	i = 0;
	int j = uiRemainLength + uiReceived - FRAME_LENGTH;
	while(i <= j)
	{
		UCHAR *pData = &chData[i];
		if((pData[0] == RS422_DATA_HEAD_ONE) && 
			(pData[1] == RS422_DATA_HEAD_TWO) && 
			(pData[FRAME_LENGTH - 2] == RS422_DATA_TAIL_ONE) && 
			(pData[FRAME_LENGTH - 1] == RS422_DATA_TAIL_TWO))
		{       	
			ulFrameNum++;
			memcpy(&data, &pData[0], FRAME_LENGTH);
			DecodeData();
			IsRecievedData = true;
			i += FRAME_LENGTH;		
			continue;
		}
		else
		{
			i += 1;
		}
	}
	uiRemainLength += uiReceived - i;
	if(uiRemainLength != 0)
	{
		memcpy(chReadData, &chData[i], uiRemainLength);
		memcpy(chData, chReadData, uiRemainLength);
	}
	pch = &chData[uiRemainLength];
	return true;
}

int InertialNavigation::GetBufferLength()
{
	return sizeof(RS422DataPackage);
}

void InertialNavigation::SetDefaultAlignment(double lat, double lon, double height)
{
	JUDGE_IS_START;
	RS422SendString("$set gpslever " + to_string((long long)lat) + " " + 
		to_string((long long)lon) + " " + to_string((long long)height) + "*");
}

void InertialNavigation::SetGpsPoleLength(double x, double y, double z)
{
	JUDGE_IS_START;
	RS422SendString("$set gpslever " + to_string((long long)x) + " " + 
		to_string((long long)y) + " " + to_string((long long)z) + "*");
}

void InertialNavigation::SetAngleError(double pitch, double roll, double yaw)
{
	JUDGE_IS_START;
	RS422SendString("$set misali " + to_string((long long)pitch) + " " +  
		to_string((long long)roll) + " " + to_string((long long)yaw) + "*");
}

void InertialNavigation::SetAccOffset(double x, double y, double z)
{
	JUDGE_IS_START;
	RS422SendString("$set acc " + to_string((long long)x) + " " + 
		to_string((long long)y) + " " + to_string((long long)z) + "*");
}

void InertialNavigation::SetGyroOffset(double x, double y, double z)
{
	JUDGE_IS_START;
	RS422SendString("$set gyro " + to_string((long long)x) + " " + 
		to_string((long long)y) + " " + to_string((long long)z) + " *");
}

void InertialNavigation::SetDataRefreshFreq(DataRefreshFreq freq)
{
	JUDGE_IS_START;
	RS422SendString("$set fre " + to_string((long long)freq) + " *");
}

void InertialNavigation::SetRS422BaudRate(RS422BaudRate bps)
{
	JUDGE_IS_START;
	RS422SendString("$set bps " + to_string((long long)bps) + " *");
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
	static unsigned char ucstr[RS422_BUFFER_LENGTH] = {0}; 
	unsigned int length = strs.length();
	const char* cstr = strs.c_str();
	memcpy(ucstr, cstr, sizeof(unsigned char) * length);
	serialPort.WriteData(ucstr, length);
	//SendUARTMessageLength(RS422_PORT_NUMBER, strs.c_str(), strs.length());
	//serialPort.SendCOMCode(ucstr, length);
}

void InertialNavigation::DecodeData()
{
	//1�ȵ���60�֣�1�ֵ���60��
	Pitch = -data.Roll * ANGLE_SCALE / 3600.0;
	Roll = -data.Pitch * ANGLE_SCALE / 3600.0;
	Yaw = data.Yaw * ANGLE_SCALE / 3600.0 - YawOffset;
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
	p = config::ParseDoubleJsonFromFile(JSON_PARA_FILE_NAME, JSON_NAVI_P_KEY);
	i = config::ParseDoubleJsonFromFile(JSON_PARA_FILE_NAME, JSON_NAVI_I_KEY);
	d = config::ParseDoubleJsonFromFile(JSON_PARA_FILE_NAME, JSON_NAVI_D_KEY);
	MyControllerSetPidPara(&rollPid, p, i, d);
	MyControllerSetPidPara(&pitchPid, p, i, d);
	MyControllerSetPidPara(&yawPid, p, i, d);
	Roll = 0;
	Yaw = 0;
	Pitch = 0;
	YawOffset = 0;
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

void InertialNavigation::JudgeYawOffset()
{
	YawOffset = data.Yaw * ANGLE_SCALE / 3600.0;
}

void InertialNavigation::PidInit()
{
	MyPidParaInit(&rollPid);
	MyPidParaInit(&pitchPid);
	MyPidParaInit(&yawPid);
}

void InertialNavigation::PidOut(double* roll, double *yaw, double* pitch)
{
	const double finalRoll = 0;
	const double finalPitch = 0;
	const double finalYaw = 0;
	JUDGE_IS_RECIEVE;
#if IS_USE_DELTA_PID
	*pitch = MyDeltaPID_Real(&pitchPid, Pitch, finalPitch);
	*roll = MyDeltaPID_Real(&rollPid, Roll, finalRoll);
	//*yaw = MyDeltaPID_Real(&yawPid, Yaw, finalYaw);
#else
	*roll = finalRoll - Roll;
	*pitch = finalPitch - Pitch;
	*yaw = finalYaw + Yaw;
#endif
}

