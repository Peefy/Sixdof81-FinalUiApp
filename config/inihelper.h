#pragma once

#ifndef __INI_HELPER_H_
#define __INI_HELPER_H_

#include <Windows.h> 
#include <fstream>
#include <string>

using namespace std;

#include "../TYPE_DEF.H"
#include "../communication/sixdof.h"

#define JSON_FILE_NAME                "config.json"
#define JSON_PARA_FILE_NAME           "paraconfig.json"

#define JSON_STOP_AND_MIDDLE_KEY      "stopAndMiddle"
#define JSON_UDP_IP_KEY               "udpip"
#define JSON_UDP_PORT_KEY             "udpport"
#define JSON_UDP_SELF_IP_KEY          "udpselfip"
#define JSON_UDP_SELF_PORT_KEY        "udpselfport"

#define JSON_HPF_ACC_WN_KEY           "hpfAccWn"
#define JSON_LPF_ACC_WN_KEY           "lpfAccWn"
#define JSON_ANG_SPD_WN_KEY           "hpfAngleSpdWn"
#define JSON_ROLL_SCALE_KEY           "rollScale"
#define JSON_YAW_SCALE_KEY            "yawScale"
#define JSON_PITCH_SCALE_KEY          "pitchScale"
#define JSON_ROLL_FILTER_LEVEL_KEY    "rollFilterLevel"
#define JSON_YAW_FILTER_LEVEL_KEY     "yawFilterLevel"
#define JSON_PITCH_FILTER_LEVEL_KEY   "pitchFilterLevel"

#define JSON_X_SCALE_KEY              "xScale"
#define JSON_Y_SCALE_KEY              "yScale"
#define JSON_Z_SCALE_KEY              "zScale"
#define JSON_X_FILTER_LEVEL_KEY       "xFilterLevel"
#define JSON_Y_FILTER_LEVEL_KEY       "yFilterLevel"
#define JSON_Z_FILTER_LEVEL_KEY       "zFilterLevel"

#define JSON_NAVI_P_KEY               "naviP"
#define JSON_NAVI_I_KEY               "naviI"
#define JSON_NAVI_D_KEY               "naviD"

namespace config {
    void GenerateDefaultConfigFile();
    void ReadAll(bool& result, int& baud, int& portnum);
	int ReadScale();
	void RecordStatusAndPulse(char* status, int statusInt, I32* pulse);
	void RecordStatusAndPulse(char* status, int statusInt, double* pulse);
	void ReadStatusAndPulse(int& statusInt, I32* pulse);
	void ReadStatusAndPulse(int& statusInt, double* pulse);
	bool ReadIsAutoStopAndMiddle();
	template<typename T>
	T ParseJsonFromFile(const char* filename, const char* key);
	string ParseStringJsonFromFile(const char* filename, const char* key);
	int ParseIntJsonFromFile(const char* filename, const char* key);
	double ParseDoubleJsonFromFile(const char* filename, const char* key);
}

#endif // !__INI_HELPER_H_

