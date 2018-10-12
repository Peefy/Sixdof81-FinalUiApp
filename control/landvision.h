
#ifndef _LAND_VISION_H_
#define _LAND_VISION_H_

#include "stdint.h"
#include "Com.h"

#define VISION_HAEDER_ONE 'p'
#define VISION_HEADER_TWO 146

#define VISION_XYZ_SCALE    0.1
#define VISION_ANGLE_SCALE  0.01

#define VISION_PORT        2
#define VISION_BAUDRATE    57600

#pragma pack (1)
typedef struct 
{
	byte HeaderOne;
	byte HeaderTwo;
	//单位0.1mm
	int16_t X;
	//单位0.1mm
	int16_t Y;
	//单位0.1mm
	int16_t Z;
	//单位0.01度
	int16_t Yaw;
	//单位0.01度
	int16_t Roll;
	//单位0.01度
	int16_t Pitch;
	//单位mm/s
	int16_t XYZSpeed;
	//单位0.1度/s
	int16_t AngleSpeed;
	byte ConsoleInitial;
	byte Reserved;
	byte CmdPcDataAck;
	byte Function;
	byte Crc;
}LandVisionPackage;
#pragma pack () 

class LandVision : public BaseCom<LandVisionPackage>
{
public:
	LandVision();
	~LandVision();
	void RenewVisionData();
	double X;
	double Y;
	double Z;
	double Roll;
	double Yaw;
	double Pitch;	
private:

};



#endif 
