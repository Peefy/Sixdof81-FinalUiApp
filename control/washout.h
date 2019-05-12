
#ifndef __WASHOUT_H_
#define __WASHOUT_H_

// 洗出滤波算法
class WashoutAlgorithm
{
public:
	WashoutAlgorithm();
	~WashoutAlgorithm();
	// 执行洗出滤波算法
	void Do(double xacc,double yacc, double zacc, 
		double rollAngleSpeed, double pitchAngleSpeed, double yawAngleSpeed,
		double roll, double yaw, double pitch);
	// 洗出滤波算法计算后的X线位移
	double WashX;
	// 洗出滤波算法计算后的Y线位移
	double WashY;
	// 洗出滤波算法计算后的Z线位移
	double WashZ;
	// 洗出滤波算法计算后的横滚角
	double WashRoll;
	// 洗出滤波算法计算后的俯仰角
	double WashPitch;
	// 洗出滤波算法计算后的偏航角
	double WashYaw;
private:
};



#endif
