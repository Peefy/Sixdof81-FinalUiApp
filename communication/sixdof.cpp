#include "stdAfx.h"
#include "sixdof.h"

#include "math.h"

#include "../Sixdofdll2010.h"

char * SixDofStatusText[] = {
	"bottom",
	"ready",
	"middle"
	"run",
	"isrising",
	"isfalling",
};

typedef double *(*PeefyControl)(double, double, double, double, double, double);
PeefyControl func;
HMODULE hDll;

SixDof::SixDof()
{
	this->DataInit();
	this->DllInit();
}

SixDof::~SixDof()
{
}

void  SixDof::DataInit()
{
	this->IsRegister = false;
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
	this->Roll = 0;
	this->Yaw = 0;
	this->Pitch = 0;
	for (auto i = 0;i < AXES_COUNT;++i)
	{
		PoleLength[i] = 0;
		pulses[i] = 0;
	}
}

void SixDof::DllInit()
{
	hDll = LoadLibrary(_T(DLL_NAME));
	if (hDll != NULL)
	{
		printf("ok\r\n");
		this->IsRegister = true;
		func = PeefyControl(GetProcAddress(hDll, FUNC_NAME));
	}
}

double* SixDof::DuGuControl(double x, double y, double z, double roll, double pitch, double yaw)
{
	auto xyz_scale = XYZ_SCALE;
	auto angle_scale = DEG_SCALE;
	// 客户传过来的数据位移单位为0.1mm,角度单位为0.01度
	x = RANGE(x * xyz_scale, -MAX_XYZ, MAX_XYZ);
	y = RANGE(y * xyz_scale, -MAX_XYZ, MAX_XYZ);
	z = RANGE(z * xyz_scale, -MAX_XYZ, MAX_XYZ);
	roll = RANGE(roll * angle_scale, -MAX_DEG, MAX_DEG);
	pitch = RANGE(pitch * angle_scale, -MAX_DEG, MAX_DEG);
	yaw = RANGE(yaw * angle_scale, -MAX_DEG, MAX_DEG);
	return Control(x, y, z, roll, yaw, pitch);
}

void SixDof::GetSixServoPulseNum(I32 * pulse_arr, double * data)
{
	X = data[0];
	Y = data[1];
	Z = data[2];
	Roll = data[3];
	Pitch = data[4];
	Yaw = data[5];
	auto result = DuGuControl(X, Y, Z, Roll, Pitch, Yaw);
	for (auto i = 0; i < AXES_COUNT; ++i)
	{
		PoleLength[i] = result[i];
		pulse_arr[i] = (I32)(result[i] * LENGTH_TO_PULSE_SCALE);
	}
}

void SixDof::GetSixServoPulseNum(double * pulse_arr, double * data)
{
	X = data[0];
	Y = data[1];
	Z = data[2];
	Roll = data[3];
	Pitch = data[4];
	Yaw = data[5];
	auto result = DuGuControl(X, Y, Z, Roll, Pitch, Yaw);
	for (auto i = 0; i < AXES_COUNT; ++i)
	{
		PoleLength[i] = result[i];
		pulse_arr[i] = (result[i] * LENGTH_TO_PULSE_SCALE);
	}
}

void SixDof::GetSixServoPulseNum(double * pole_length, SixdofPackage * data)
{
	X = data->X;
	Y = data->Y;
	Z = data->Z;
	Roll = data->Roll;
	Pitch = data->Pitch;
	Yaw = data->Yaw;
	double* pulse_dugu = Control(X, Y, Z, Roll, Yaw, Pitch);
	for (auto i = 0; i < AXES_COUNT; ++i)
	{
		pole_length[i] = pulse_dugu[i];
	}
}

