
#ifndef __RECORD_PATH_H_
#define __RECORD_PATH_H_

namespace config {
	// 记录平台参数到文件 const char * filename
	void RecordPath(const char * filename, double x, double y, double z, double roll, double yaw, double pitch);
	// 记录平台参数到文件 const char * filename
	void RecordData(const char * filename, double XAcc,double YAcc,double ZAcc,double RollSpeed,
		double PitchSpeed,double YawSpeed, double Roll, double Pitch,double Yaw, int type);
}

#endif // !__RECORD_PATH_H_

