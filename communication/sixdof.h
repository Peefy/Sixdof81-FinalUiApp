
#ifndef _SIXDOF_H_
#define _SIXDOF_H_

#include <Windows.h> 

#include "../config/inihelper.h"
#include "../TYPE_DEF.H"

//ƽ̨�˶����Ƕ�
#define MAX_DEG 10
#define DEG_SCALE 0.01
//ƽ̨�˶����λ��
#define MAX_XYZ 100
#define XYZ_SCALE 0.1
// ƽ̨�˶����Ƶ��
#define MAX_HZ 20

#define DLL_NAME "Sixdofdll2010.dll"
#define FUNC_NAME "Control"
#define FUNC_NAGIN  6
#define FUNC_NAGOUT 6

//�׵�����
#define AXES_COUNT 6

//�����˿�ܵĵ��� һȦ�����6mm, ������쳤��Ϊ700mm
#define PULSE_PER_R 1024
#define MM_PER_R 7.50

#define LENGTH_TO_PULSE_SCALE (PULSE_PER_R / MM_PER_R)

#define FREEDOM_X_INDEX     0
#define FREEDOM_Y_INDEX     1
#define FREEDOM_Z_INDEX     2
#define FREEDOM_ROLL_INDEX  3
#define FREEDOM_PITCH_INDEX 4
#define FREEDOM_YAW_INDEX   5

//��λ����
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

typedef struct 
{
	//��λ1mm
	double X;
	//��λ1mm
	double Y;
	//��λ1mm
	double Z;
	//��λ1��
	double Yaw;
	//��λ1��
	double Roll;
	//��λ1��
	double Pitch;
}SixdofPackage;

class SixDof
{
public:
	SixDof();
	~SixDof();
	bool IsRegister;
	void GetSixServoPulseNum(I32 * pulse_arr, double * data);
	void GetSixServoPulseNum(double * pulse_arr, double * data);
	void GetSixServoPulseNum(double * pulse_arr, SixdofPackage * data);
	double X;
	double Y;
	double Z;
	double Roll;
	double Yaw;
	double Pitch;
	double PoleLength[AXES_COUNT];
private:
	double pulses[AXES_COUNT];
	void DataInit();
	void DllInit();
	double* DuGuControl(double x, double y, double z, double roll, double pitch, double yaw);
};



#endif

