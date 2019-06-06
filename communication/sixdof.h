
#ifndef _SIXDOF_H_
#define _SIXDOF_H_

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include <Windows.h> 

#include "../config/inihelper.h"
#include "../TYPE_DEF.H"

//圆周率
#define PI 3.1415926

//六自由度核心算法库dll程序集名称
#define DLL_NAME "Sixdofdll2010.dll"
//六自由度反解算法函数名称
#define FUNC_NAME "Control"
//输入参数个数
#define FUNC_NAGIN  6
//输出参数个数
#define FUNC_NAGOUT 6

//缸的数量
#define AXES_COUNT 6

//六自由度X索引号
#define FREEDOM_X_INDEX     0
//六自由度Y索引号
#define FREEDOM_Y_INDEX     1
//六自由度Z索引号
#define FREEDOM_Z_INDEX     2
//六自由度ROLL索引号
#define FREEDOM_ROLL_INDEX  3
//六自由度PITCH索引号
#define FREEDOM_PITCH_INDEX 4
//六自由度YAW索引号
#define FREEDOM_YAW_INDEX   5

//限位函数
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

//上限位函数
#define UP_RANGE(x, max) ( (x)>(max) ? (max) : (x) )

//下限位函数
#define DOWN_RANGE(x, min) ( (x)<(min) ? (min) : (x) )

//是否超出范围
#define IS_OUT_OF_RANGE(x, min, max)   ((x) <= (min) || (x) >= (max)) 

//将数字var的第n位清零
#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   
//将数字var的第n位置1
#define BIT_SET(var,n)          (var) |=  (1<<(n))   
//获取数字var的第n位置1
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  
//将数字var的第n位置1或置0
#define BIT_SETval(var,n,val)   ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

//整数类型六自由度变量
typedef struct 
{
	//单位0.1mm
	int16_t X;
	//单位0.1mm
	int16_t Y;
	//单位0.1mm
	int16_t Z;
	//单位0.01度
	int16_t Roll;
	//单位0.01度
	int16_t Pitch;
	//单位0.01度
	int16_t Yaw;
}DataPackage;

//浮点型六自由度变量
typedef struct 
{
	//单位1mm
	double X;
	//单位1mm
	double Y;
	//单位1mm
	double Z;
	//单位1度
	double Roll;
	//单位1度
	double Pitch;
	//单位1度
	double Yaw;
}DataPackageDouble;

//六自由度变量模板类
template<class T>
class DataPackageType
{
public:
	// X线位移
	unique_ptr<T> X;
	// Y线位移
	unique_ptr<T> Y;
	// Z线位移
	unique_ptr<T> Z;
	// 横滚角
	unique_ptr<T> Roll;
	//俯仰角
	unique_ptr<T> Pitch;
	// 偏航角
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

//六自由度平台状态
typedef enum
{
	SIXDOF_STATUS_BOTTOM,	  //六自由度平台状态_底部
	SIXDOF_STATUS_READY,	  //六自由度平台状态_中立位
	SIXDOF_STATUS_MIDDLE,	  //六自由度平台状态_正在回中
	SIXDOF_STATUS_RUN,	      //六自由度平台状态_正在运行
	SIXDOF_STATUS_ISRISING,	  //六自由度平台状态_正在上升
	SIXDOF_STATUS_ISFALLING   //六自由度平台状态_正在下降
}SixDofPlatformStatus;

//六自由度平台状态字符串数组
extern char * SixDofStatusText[];

//将DataPackage清零
void ResetDefaultData(DataPackage * data);
//将DataPackage打印为字符串输出
void PrintDataPackageToString(DataPackage data);

#endif

