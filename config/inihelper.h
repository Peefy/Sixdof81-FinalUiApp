#pragma once

#ifndef __INI_HELPER_H_
#define __INI_HELPER_H_

#include <Windows.h> 
#include <fstream>

#include "../TYPE_DEF.H"
#include "../communication/sixdof.h"

namespace config {
    void GenerateDefaultConfigFile();
    void ReadAll(bool& result, int& baud, int& portnum);
	int ReadScale();
	void RecordStatusAndPulse(char* status, int statusInt, I32* pulse);
	void RecordStatusAndPulse(char* status, int statusInt, double* pulse);
	void ReadStatusAndPulse(int& statusInt, I32* pulse);
	void ReadStatusAndPulse(int& statusInt, double* pulse);
	bool ReadIsAutoStopAndMiddle();
}

#endif // !__INI_HELPER_H_

