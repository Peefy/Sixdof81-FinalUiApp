
#include "stdafx.h"
#include "landvision.h"
#include "Com.h"

LandVision::LandVision() : BaseCom(VISION_HAEDER_ONE, VISION_HEADER_TWO)
{

}

LandVision::~LandVision()
{
}

void LandVision::RenewVisionData()
{
	auto data = this->GetDataFromCom();
	X = data->X * VISION_XYZ_SCALE;
	X = data->Y * VISION_XYZ_SCALE;
	X = data->Z * VISION_XYZ_SCALE;
	Roll = data->Roll * VISION_ANGLE_SCALE;
	Pitch = data->Pitch * VISION_ANGLE_SCALE;
	Yaw = data->Yaw * VISION_ANGLE_SCALE;
}
