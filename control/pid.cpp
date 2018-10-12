
#include "stdafx.h"
#include "pid.h"

double MyLocationPID_Real(PID_Type *This, double now, double set)
{
	This->Now = now;
	This->Set = set;
	This->Error = This->Set - This->Now;
	This->ErrorSum += This->Error;
	if (This->ErrorSum >= This->ErrorIMax) This->ErrorSum = This->ErrorIMax;
	if (This->ErrorSum <= This->ErrorIMin) This->ErrorSum = This->ErrorIMin;
	This->Out = This->Real_P * This->Error
		+ This->Real_I * This->ErrorSum
		+ This->Real_D * (This->Error - This->LastError);
	This->PrevError = This->LastError;
	This->LastError = This->Error;
	This->Delta = This->Out;
	if (This->Delta >= This->OutMax) This->Delta = This->OutMax;
	if (This->Delta <= This->OutMin) This->Delta = This->OutMin;
	return This->Delta;
}

double MyDeltaPID_Real(PID_Type *This, double now, double set)
{
	This->Now = now;
	This->Set = set;
	This->Error = This->Set - This->Now;
	This->Out = This->Real_P * (This->Error - This->LastError)
		+ This->Real_I * This->Error
		+ This->Real_D * (This->Error - 2 * This->LastError + This->PrevError);
	This->PrevError = This->LastError;
	This->LastError = This->Error;
	This->Delta += This->Out;
	if (This->Delta >= This->OutMax) This->Delta = This->OutMax;
	if (This->Delta <= This->OutMin) This->Delta = This->OutMin;
	return This->Delta;
}

double MyDeltaPIDWithNoDelta(PID_Type *This, double now, double set)
{
	This->Now = now;
	This->Set = set;
	This->Error = This->Set - This->Now;
	This->Out = This->Real_P * (This->Error - This->LastError)
		+ This->Real_I * This->Error
		+ This->Real_D * (This->Error - 2 * This->LastError + This->PrevError);
	This->PrevError = This->LastError;
	This->LastError = This->Error;
	return This->Out;
}


void MyPidParaInit(PID_Type *This)
{
	This->Delta = 0;
	This->Out = 0;
	This->ErrorSum = 0;
	This->PrevError = 0;
	This->LastError = 0;
	This->Error = 0;
}