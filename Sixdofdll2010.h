#ifndef _PEEFY_SIXDOF_H_
#define _PEEFY_SIXDOF_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef SIXDOFDLL2010_EXPORTS
#define SIXDOFDLL2010_API __declspec(dllexport)
#else
#define SIXDOFDLL2010_API __declspec(dllimport)
#endif

/*
由姿态角获取缸的伸长行程，位移单位为毫米(mm)，角度单位为角度(deg),适用于3-3结构的Gough-Stewart六自由度平台
@para
x : X轴位移 mm
y : y轴位移 mm
z : z轴位移 mm
roll : 横滚角 deg
yaw : 偏航角 deg
pitch : 俯仰角 deg
@return
double[0] 杆1的伸长量
double[1] 杆2的伸长量
double[2] 杆3的伸长量
double[3] 杆4的伸长量
double[4] 杆5的伸长量
double[5] 杆6的伸长量
*/
SIXDOFDLL2010_API double* Control(double x, double y, double z, double roll, double yaw, double pitch);

/*
由缸的伸长行程获取姿态角，位移单位为毫米(mm)，角度单位为角度(deg)
@para
lengths[0] 杆1的伸长量 
lengths[1] 杆2的伸长量
lengths[2] 杆3的伸长量
lengths[3] 杆4的伸长量
lengths[4] 杆5的伸长量
lengths[5] 杆6的伸长量
@return
x : X轴位移 mm
y : y轴位移 mm
z : z轴位移 mm
a = roll : 横滚角 deg
b = pitch : 俯仰角 deg
c = yaw : 偏航角 deg
*/
SIXDOFDLL2010_API double* FromLengthToPose(double * lengths);

/*
获取 顶部铰链的空间坐标，坐标原点为平台升起后中立位顶部平台中心，单位为毫米(mm)
@return
double[0] x位移 mm
double[1] y位移 mm
double[2] z位移 mm
*/
SIXDOFDLL2010_API double* GetTopPosition(int index);
/*
获取 底部铰链的空间坐标，坐标原点为平台升起后中立位顶部平台中心，单位为毫米(mm)
@para
index : 杆的索引号
@return
double[0] x位移 mm
double[1] y位移 mm
double[2] z位移 mm
*/
SIXDOFDLL2010_API double* GetBottomPosition(int index);
/*
设置 顶部铰链的空间坐标，坐标原点为平台升起后中立位顶部平台中心，单位为毫米(mm)
@para
index : 杆的索引号
x : x坐标
y : y坐标
z : z坐标
@return
bool 是否设置成功
*/
SIXDOFDLL2010_API bool SetTopPosition(int index, double x, double y, double z);
/*
设置 底部铰链的空间坐标，坐标原点为平台升起后中立位顶部平台中心，单位为毫米(mm)
@para
index : 杆的索引号
x : x坐标
y : y坐标
z : z坐标
@return
bool 是否设置成功
*/
SIXDOFDLL2010_API bool SetBottomPosition(int index, double x, double y, double z);

/*
设置 六自由度平台的结构参数，单位为毫米(mm)
@para
planeAboveHingeLength : 上平台上表面距离上平台铰链的垂直距离
planeAboveBottomLength : 上平台上表面距离地面的垂直距离
circleTopRadius : 上平台圆圈半径
circleBottomRadius : 下平台圆圈半径
distanceBetweenHingeTop ： 上平台同一组两个铰链的中心距离
distanceBetweenHingeBottom : 下平台同一组两个铰链的中心距离
@return
bool 是否设置成功
*/
SIXDOFDLL2010_API void SetPlatformPara(double planeAboveHingeLength, double planeAboveBottomLength, double circleTopRadius, 
									   double circleBottomRadius, double distanceBetweenHingeTop, double distanceBetweenHingeBottom);


/*
六自由度平台的洗出算法
@para
x : x轴的位移 mm
y : y轴的位移 mm
z : z轴的位移 mm
roll  : 横滚角，绕x轴旋转的姿态角 deg
yaw   : 偏航角，绕z轴旋转的姿态角 deg
pitch : 俯仰角，绕z轴旋转的姿态角 deg
xacc : x轴的加速度 m/s^2
yacc : y轴的加速度 m/s^2
zacc : z轴的加速度 m/s^2
rollSpeed  : 横滚角角速度，绕x轴旋转的姿态角角速度 deg/s
yawSpeed   : 偏航角角速度，绕z轴旋转的姿态角角速度 deg/s
pitchSpeed : 俯仰角角速度，绕z轴旋转的姿态角角速度 deg/s
@return
x : X轴位移 mm
y : y轴位移 mm
z : z轴位移 mm
roll :  横滚角 deg
pitch : 俯仰角 deg
yaw :   偏航角 deg
*/
SIXDOFDLL2010_API double* WashOutFiltering(double x, double y, double z,
										   double roll, double yaw, double pitch,
										   double xacc, double yacc, double zacc, 
										   double rollSpeed, double yawSpeed, double pitchSpeed);

/*
设置 六自由度平台的洗出算法的参数
@para
hpfAccWn : 线加速度高通滤波器截止频率
lpfAccWn : 线加速度低通滤波器截止频率
hpfAngleSpdWn : 角速度低通滤波器截止频率
@return
null
*/
SIXDOFDLL2010_API void SetWashOutFilterPara(double hpfAccWn, double lpfAccWn, double hpfAngleSpdWn, double sampleTime);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !_PEEFY_SIXDOF_H_
