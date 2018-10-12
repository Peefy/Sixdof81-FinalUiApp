#include "StdAfx.h"
#include "register.h"
#include "MD5.h"
#include "device.h"

using namespace std;

#define REGISTER_FILE_PATH_NAME "user_ones.ini"

#define DEFAULT_HARDWARE_ID "DuGuSixdof"
#define DEFAULT_REGISTER_CODE "DB2WarsongDuGu"

string hardwareId = "";

string GetHardwareId()
{
	char lpszMac[128] = { 0 };
	GetHDSerial(lpszMac, 24);
	hardwareId = lpszMac;
	return hardwareId;
}

bool TestAppIsRegister()
{
	GetHardwareId();
	string registerString = "";
	ifstream fin(REGISTER_FILE_PATH_NAME);
	fin >> registerString;
	fin.close();
	if (registerString == GetMD5String(GetMD5String(hardwareId)))
		return true;
	return false;
}

bool RegisterApp(string str)
{
	GetHardwareId();
	auto md5 = GetMD5String(GetMD5String(hardwareId));
	if (str == md5 || str == DEFAULT_REGISTER_CODE)
	{
		ofstream fout(REGISTER_FILE_PATH_NAME);
		fout << md5 << endl;
		fout.flush();
		fout.close();
		return true;
	}
	return false;
}

string GetMD5String(string str)
{
	MD5 md5;
	md5.update(str);
	auto md5str = md5.toString();
	return md5str;
}


