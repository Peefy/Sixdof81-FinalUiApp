
#ifndef _SIXDOF_H_
#define _SIXDOF_H_

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include <Windows.h> 

#include "../config/inihelper.h"
#include "../TYPE_DEF.H"

#define PI 3.1415926

#define DLL_NAME "Sixdofdll2010.dll"
#define FUNC_NAME "Control"
#define FUNC_NAGIN  6
#define FUNC_NAGOUT 6

//�׵�����
#define AXES_COUNT 6

#define FREEDOM_X_INDEX     0
#define FREEDOM_Y_INDEX     1
#define FREEDOM_Z_INDEX     2
#define FREEDOM_ROLL_INDEX  3
#define FREEDOM_PITCH_INDEX 4
#define FREEDOM_YAW_INDEX   5

//��λ����
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

//��λ����
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

#define DOWN_RANGE(x, min) ( (x)<(min) ? (min) : (x) )

#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   
#define BIT_SET(var,n)          (var) |=  (1<<(n))   
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  
#define BIT_SETval(var,n,val)   ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

typedef struct 
{
	//��λ0.1mm
	int16_t X;
	//��λ0.1mm
	int16_t Y;
	//��λ0.1mm
	int16_t Z;
	//��λ0.01��
	int16_t Yaw;
	//��λ0.01��
	int16_t Roll;
	//��λ0.01��
	int16_t Pitch;
}DataPackage;

typedef struct 
{
	//��λ1mm
	double X;
	//��λ1mm
	double Y;
	//��λ1mm
	double Z;
	//��λ1��
	double Roll;
	//��λ1��
	double Pitch;
	//��λ1��
	double Yaw;
}DataPackageDouble;

template<typename T>
class DataPackageType
{
public:
	unique_ptr<T> X;
	unique_ptr<T> Y;
	unique_ptr<T> Z;
	unique_ptr<T> Roll;
	unique_ptr<T> Pitch;
	unique_ptr<T> Yaw;
	DataPackageType()
	{
		X = make_unique<T>(new T);
		Y = make_unique<T>(new T);
		Z = make_unique<T>(new T);
		Roll = make_unique<T>(new T);
		Pitch = make_unique<T>(new T);
		Yaw = make_unique<T>(new T);
	}
	~DataPackageType()
	{
		auto ptrX = X.release();
		delete ptrX;
		ptrX = nullptr;
		auto ptrY = Y.release();
		delete ptrY;
		ptrY = nullptr;
		auto ptrZ = Z.release();
		delete ptrZ;
		ptrZ = nullptr;
		auto ptrRoll = Roll.release();
		delete ptrRoll;
		ptrRoll = nullptr;
		auto ptrPitch = Pitch.release();
		delete ptrPitch;
		ptrPitch = nullptr;
		auto ptrYaw = Yaw.release();
		delete ptrYaw;
		ptrYaw = nullptr;
	}
};

typedef enum
{
	SIXDOF_STATUS_BOTTOM,
	SIXDOF_STATUS_READY,
	SIXDOF_STATUS_MIDDLE,
	SIXDOF_STATUS_RUN,
	SIXDOF_STATUS_ISRISING,
	SIXDOF_STATUS_ISFALLING,
}SixDofPlatformStatus;

extern char * SixDofStatusText[];

void ResetDefaultData(DataPackage * data);
void PrintDataPackageToString(DataPackage data);

#endif

