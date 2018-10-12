
#ifndef _PID_H_
#define _PID_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/********PID*******/
/* Sample usage:
PID_Type MyPID = {1,1,0,1,1,1,-100,100,1000,-1000}
MyDeltaPID(&MyPID ,now,10);
*/
typedef
struct
{
	//public:
	double Real_P;
	double Real_I;
	double Real_D;
	double OutMin;
	double OutMax;
	uint16_t HMI_P;
	uint16_t HMI_I;
	uint16_t HMI_D;
	float ReductionFactor_P;
	float ReductionFactor_I;
	float ReductionFactor_D;
	double ErrorIMin;
	double ErrorIMax;
	//private:    		
	double LastError;
	double PrevError;
	double Error;
	double ErrorSum;
	double Delta;
	double Out;
	double Now;
	double Set;
}PID_Type;

double MyLocationPID_Real(PID_Type *This, double now, double set);
double MyDeltaPID_Real(PID_Type *This, double now, double set);
double MyDeltaPIDWithNoDelta(PID_Type *This, double now, double set);
void MyPidParaInit(PID_Type *This);

#ifdef __cplusplus
}
#endif

#endif
