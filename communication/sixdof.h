
#ifndef _SIXDOF_H_
#define _SIXDOF_H_

#include <Windows.h> 

#include "../config/inihelper.h"
#include "../TYPE_DEF.H"

//平台运动最大角度
#define MAX_DEG 28
#define DEG_SCALE 0.01
//平台运动最大位移
#define MAX_XYZ 60
#define XYZ_SCALE 0.1
// 平台运动最大频率
#define MAX_HZ 5
#define MAX_PHASE 360

#define DLL_NAME "Sixdofdll2010.dll"
#define FUNC_NAME "Control"
#define FUNC_NAGIN  6
#define FUNC_NAGOUT 6

//缸的数量
#define AXES_COUNT 6

#define FREEDOM_X_INDEX     0
#define FREEDOM_Y_INDEX     1
#define FREEDOM_Z_INDEX     2
#define FREEDOM_ROLL_INDEX  3
#define FREEDOM_PITCH_INDEX 4
#define FREEDOM_YAW_INDEX   5

//限位函数
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

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


#endif

