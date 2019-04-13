
#include "stdafx.h"
#include "washout.h"

#include "../Sixdofdll2010.h"

WashoutAlgorithm::WashoutAlgorithm()
{

}

WashoutAlgorithm::~WashoutAlgorithm()
{

}

void WashoutAlgorithm::Do(double xacc,double yacc, double zacc, 
		double rollAngleSpeed, double pitchAngleSpeed, double yawAngleSpeed,
		double roll, double yaw, double pitch)
{
	auto* results = WashOutFiltering(0, 0, 0, roll, yaw, pitch, xacc, yacc, zacc, 
		rollAngleSpeed, yawAngleSpeed, pitchAngleSpeed);
	WashX = results[0];      // mm
	WashY = results[1];      // mm
	WashZ = results[2];      // mm
	WashRoll = results[3];   // deg
	WashPitch = results[4];  // deg
	WashYaw = results[5];    // deg
}

