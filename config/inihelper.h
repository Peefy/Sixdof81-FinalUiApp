#pragma once

#ifndef __INI_HELPER_H_
#define __INI_HELPER_H_

#include <Windows.h> 
#include <fstream>
#include <string>

using namespace std;

#include "../TYPE_DEF.H"
#include "../communication/sixdof.h"

#define JSON_PARA_FILE_NAME           "paraconfig.json"

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
	string ParseStringJsonFromFile(const char* filename, const char* key);
	int ParseIntJsonFromFile(const char* filename, const char* key);
	double ParseDoubleJsonFromFile(const char* filename, const char* key);
}

#endif // !__INI_HELPER_H_

