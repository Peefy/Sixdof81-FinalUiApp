
#ifndef __WASHOUT_H_
#define __WASHOUT_H_

// ϴ���˲��㷨
class WashoutAlgorithm
{
public:
	WashoutAlgorithm();
	~WashoutAlgorithm();
	// ִ��ϴ���˲��㷨
	void Do(double xacc,double yacc, double zacc, 
		double rollAngleSpeed, double pitchAngleSpeed, double yawAngleSpeed,
		double roll, double yaw, double pitch);
	// ϴ���˲��㷨������X��λ��
	double WashX;
	// ϴ���˲��㷨������Y��λ��
	double WashY;
	// ϴ���˲��㷨������Z��λ��
	double WashZ;
	// ϴ���˲��㷨�����ĺ����
	double WashRoll;
	// ϴ���˲��㷨�����ĸ�����
	double WashPitch;
	// ϴ���˲��㷨������ƫ����
	double WashYaw;
private:
};



#endif
