
#include "stdafx.h"
#include "recordpath.h"

#include <fstream>

using namespace std;

namespace config {

	void RecordPath(const char * filename, double x, double y, double z, double roll, double yaw, double pitch)
	{
		ofstream fout(filename, ios::app);
		fout << "0 ";fout << "0 ";fout << "0 ";fout << "0 ";fout << "0 ";fout << "0 ";
		fout << "0 ";fout << "0 ";fout << "0 ";fout << "0 ";fout << "0 ";fout << "0 ";
		fout << x << " ";
		fout << y << " ";
		fout << z << " ";
		fout << roll << " ";
		fout << yaw << " ";
		fout << pitch << " ";
		fout << endl;
		fout.flush();
		fout.close();
	}

	void RecordData(const char * filename, double XAcc,double YAcc,double ZAcc,double RollSpeed,
		double PitchSpeed,double YawSpeed, double Roll, double Pitch,double Yaw, int type)
	{
		ofstream fout(filename, ios::app);
		fout << XAcc << " ";
		fout << YAcc << " ";
		fout << ZAcc << " ";
		fout << RollSpeed << " ";
		fout << PitchSpeed << " ";
		fout << YawSpeed << " ";
		fout << Roll << " ";
		fout << Pitch << " ";
		fout << Yaw << " ";
		fout << type << " ";
		fout << endl;
		fout.flush();
		fout.close();
	}

}
