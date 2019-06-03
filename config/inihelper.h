#pragma once

#ifndef __INI_HELPER_H_
#define __INI_HELPER_H_

#include <Windows.h> 
#include <fstream>
#include <string>

using namespace std;

#include "../TYPE_DEF.H"
#include "../communication/sixdof.h"

// 软件参数json配置文件名称
#define JSON_FILE_NAME                "config.json"
// 平台算法json配置文件名称
#define JSON_PARA_FILE_NAME           "paraconfig.json"
// 平台参数json配置文件名称
#define JSON_PARA_FILE_NAME           "platformconfig.json"

// json-key:是否停止回中
#define JSON_STOP_AND_MIDDLE_KEY      "stopAndMiddle"
// json-key:UDP通信对方IP地址
#define JSON_UDP_IP_KEY               "udpip"
// json-key:UDP通信对方IP端口号
#define JSON_UDP_PORT_KEY             "udpport"
// json-key:UDP通信自身IP地址
#define JSON_UDP_SELF_IP_KEY          "udpselfip"
// json-key:UDP通信自身IP端口号
#define JSON_UDP_SELF_PORT_KEY        "udpselfport"

// json-key:洗出算法加速度高通滤波器参数
#define JSON_HPF_ACC_WN_KEY           "hpfAccWn"
// json-key:洗出算法加速度低通滤波器参数
#define JSON_LPF_ACC_WN_KEY           "lpfAccWn"
// json-key:洗出算法角速度高通滤波器参数
#define JSON_ANG_SPD_WN_KEY           "hpfAngleSpdWn"
// json-key:横滚角增益
#define JSON_ROLL_SCALE_KEY           "rollScale"
// json-key:偏航角增益
#define JSON_YAW_SCALE_KEY            "yawScale"
// json-key:俯仰角增益
#define JSON_PITCH_SCALE_KEY          "pitchScale"
// json-key:横滚角平滑系数
#define JSON_ROLL_FILTER_LEVEL_KEY    "rollFilterLevel"
// json-key:偏航角平滑系数
#define JSON_YAW_FILTER_LEVEL_KEY     "yawFilterLevel"
// json-key:俯仰角平滑系数
#define JSON_PITCH_FILTER_LEVEL_KEY   "pitchFilterLevel"

// json-key:x线位移增益
#define JSON_X_SCALE_KEY              "xScale"
// json-key:y线位移增益
#define JSON_Y_SCALE_KEY              "yScale"
// json-key:z线位移增益
#define JSON_Z_SCALE_KEY              "zScale"
// json-key:x线位移平滑系数
#define JSON_X_FILTER_LEVEL_KEY       "xFilterLevel"
// json-key:y线位移平滑系数
#define JSON_Y_FILTER_LEVEL_KEY       "yFilterLevel"
// json-key:z线位移平滑系数
#define JSON_Z_FILTER_LEVEL_KEY       "zFilterLevel"

// json-key:直控X加速度增益
#define JSON_DIRECT_ACC_X_SCALE_KEY        "directAccXScale"
//  json-key:直控X加速度增益
#define JSON_DIRECT_ACC_Y_SCALE_KEY        "directAccYScale"
//  json-key:直控X加速度增益
#define JSON_DIRECT_ACC_Z_SCALE_KEY        "directAccZScale"
//  json-key:直控横滚角速度增益
#define JSON_DIRECT_SPEED_ROLL_SCALE_KEY   "directSpeedRollScale"
//  json-key:直控俯仰角速度增益
#define JSON_DIRECT_SPPED_PITCH_SCALE_KEY  "directSpeedPitchScale"
//  json-key:直控偏航角速度增益
#define JSON_DIRECT_SPEED_YAW_SCALE_KEY    "directSpeedYawScale"
//  json-key:直控横滚角增益	
#define JSON_DIRECT_ANGLE_ROLL_SCALE_KEY   "directAngleRollScale"
//  json-key:直控俯仰角增益
#define JSON_DIRECT_ANGLE_PITCH_SCALE_KEY  "directAnglePitchScale"
//  json-key:直控偏航角增益
#define JSON_DIRECT_ANGLE_YAW_SCALE_KEY    "directAngleYawScale"

// json-key:惯导稳定PID控制器P
#define JSON_NAVI_P_KEY               "naviP"
// json-key:惯导稳定PID控制器I
#define JSON_NAVI_I_KEY               "naviI"
// json-key:惯导稳定PID控制器D
#define JSON_NAVI_D_KEY               "naviD"

namespace config {
	// 产生默认的config.ini文件
    void GenerateDefaultConfigFile();
	// 读取config.ini文件中的串口端口号和波特率
    void ReadAll(bool& result, int& baud, int& portnum);
	// 读取config.ini文件中的增益系数
	int ReadScale();
	// 记录recorddouble.txt中记录的平台状态和编码器读数
	void RecordStatusAndPulse(char* status, int statusInt, I32* pulse);
	// 记录recorddouble.txt中记录的平台状态和编码器读数
	void RecordStatusAndPulse(char* status, int statusInt, double* pulse);
	// 读取recorddouble.txt中记录的平台状态和编码器读数
	void ReadStatusAndPulse(int& statusInt, I32* pulse);
	// 读取recorddouble.txt中记录的平台状态和编码器读数
	void ReadStatusAndPulse(int& statusInt, double* pulse);
	// 读取是否停止并回中的配置
	bool ReadIsAutoStopAndMiddle();
	// 读取json文件-value类型：范形
	template<typename T>
	T ParseJsonFromFile(const char* filename, const char* key);
	// 读取json文件-value类型：字符串类型 std::string
	string ParseStringJsonFromFile(const char* filename, const char* key);
	// 读取json文件-value类型：32位整数类型 int
	int ParseIntJsonFromFile(const char* filename, const char* key);
	// 读取json文件-value类型：64位双精度浮点型 double
	double ParseDoubleJsonFromFile(const char* filename, const char* key);
	// 记录姿态数据
	void RecordData(const char * filename, double roll, double pitch, double yaw);
}

#endif // !__INI_HELPER_H_

