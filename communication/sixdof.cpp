#include "stdAfx.h"
#include "sixdof.h"

#include "math.h"
#include <iostream>

using namespace std;

char * SixDofStatusText[] = {
	"bottom",
	"ready",
	"middle"
	"run",
	"isrising",
	"isfalling",
};

void ResetDefaultData(DataPackage * data)
{
	data->X = 0;
	data->Y = 0;
	data->Z = 0;
	data->Roll = 0;
	data->Yaw = 0;
	data->Pitch = 0;
}

void PrintDataPackageToString(DataPackage data)
{
	cout << "X:" << data.X << ";Y:" << data.Y << ";Z:" << data.Z;
	cout << ";Yaw:" << data.Yaw << ";Roll:" << data.Roll << ";Pitch:" << data.Pitch;
	cout << endl;
}

