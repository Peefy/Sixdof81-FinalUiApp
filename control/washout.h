
#ifndef __WASHOUT_H_
#define __WASHOUT_H_

class WashoutAlgorithm
{
public:
	WashoutAlgorithm();
	~WashoutAlgorithm();
	void Do(double xacc,double yacc, double zacc, 
		double rollAngleSpeed, double pitchAngleSpeed, double yawAngleSpeed,
		double roll, double yaw, double pitch);
	double WashX;
	double WashY;
	double WashZ;
	double WashRoll;
	double WashYaw;
	double WashPitch;
private:
};



#endif
