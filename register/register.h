
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>
#include <fstream>

using namespace std;

string GetHardwareId();
bool TestAppIsRegister();
bool RegisterApp(string str);
string GetMD5String(string str = "DuGuSixdof");

#endif
