
#include "stdafx.h"

#include "memory.h"

#include "landvision.h"
#include "Com.h"
#include "../util/crc.h"

inline int16_t ExchangeBit8(int16_t data)
{
	return (uint16_t)((((uint8_t)data) << 8) + (uint8_t)(data >> 8));
}

inline uint16_t CalCrc(LandVisionPackage *data)
{
	uint16_t crc = 0;
	crc += (uint8_t)data->X;
	crc += (uint8_t)(data->X >> 8);
	crc += (uint8_t)data->Y;
	crc += (uint8_t)(data->Y >> 8);
	crc += (uint8_t)data->Z;
	crc += (uint8_t)(data->Z >> 8);
	crc += (uint8_t)data->XAcc;
	crc += (uint8_t)(data->XAcc >> 8);
	crc += (uint8_t)data->YAcc;
	crc += (uint8_t)(data->YAcc >> 8);
	crc += (uint8_t)data->RoadTypeBefore;
	crc += (uint8_t)data->RoadType;
	crc += (uint8_t)data->Pitch;
	crc += (uint8_t)(data->Pitch >> 8);
	crc += (uint8_t)data->Roll;
	crc += (uint8_t)(data->Roll >> 8);
	crc += (uint8_t)data->ControlByte;
	crc += (uint8_t)data->NoneByte;
	crc += (uint8_t)data->CmdPcDataAcksByte;
	crc += (uint8_t)data->FunctionsByte;
	return crc;
}

inline uint16_t CalCrc(LandVisionSendPackage *data)
{
	uint16_t crc = 0;
	crc += (uint8_t)(data->PulseCount1 >> 8);
	crc += (uint8_t)data->PulseCount1;
	crc += (uint8_t)(data->PulseCount2 >> 8);
	crc += (uint8_t)data->PulseCount2;
	crc += (uint8_t)(data->PulseCount3 >> 8);
	crc += (uint8_t)data->PulseCount3;
	crc += (uint8_t)(data->PulseCount4 >> 8);
	crc += (uint8_t)data->PulseCount4;
	crc += (uint8_t)(data->PulseCount5 >> 8);
	crc += (uint8_t)data->PulseCount5;
	crc += (uint8_t)(data->PulseCount6 >> 8);
	crc += (uint8_t)data->PulseCount6;
	crc += (uint8_t)data->StateByteOne;
	crc += (uint8_t)data->StateByteTwo;
	crc += (uint8_t)data->StateByteThree;
	crc += (uint8_t)data->StateByteFour;
	return crc;
}

LandVision::LandVision() : BaseCom(VISION_RECIEVE_HAEDER, VISION_RECIEVE_HAEDER)
{
	RecievePackageLength = sizeof(LandVisionPackage);
	SendPackageLength = sizeof(LandVisionSendPackage);
	DataInit();
}

LandVision::~LandVision()
{

}

void LandVision::DataInit()
{
	X = 0;
	Y = 0;
	Z = 0;
	XAcc = 0;
	YAcc = 0;
	ZAcc = 0;
	Roll = 0;
	Yaw = 0;
	Pitch = 0;	
}

void LandVision::RenewVisionData()
{
	auto data = this->GetDataFromCom();
	if (this->IsRecievedData == false)
		return;
	auto crc = CalCrc(&data);
	auto recieveCrc = (uint16_t)ExchangeBit8(data.Crc);
	if (data.Header == VISION_RECIEVE_HAEDER && data.Tail == VISION_RECIEVE_TAIL && crc == recieveCrc)
	{
		Y = -ExchangeBit8(data.X) * VISION_XYZ_SCALE;
		X = ExchangeBit8(data.Y) * VISION_XYZ_SCALE;
		Z = ExchangeBit8(data.Z) * VISION_XYZ_SCALE;
		YAcc = -ExchangeBit8(data.XAcc) * VISION_ACC_SCALE;
		XAcc = ExchangeBit8(data.YAcc) * VISION_ACC_SCALE;
		ZAcc = 0;
		Roll = ExchangeBit8(data.Pitch) * VISION_ANGLE_SCALE;
		Pitch = -ExchangeBit8(data.Roll) * VISION_ANGLE_SCALE;
		Yaw = 0;
		NowRoadType = (RoadType)data.RoadType;
		RecieveState.IsConsoleInitial = VISION_BIT_GET(data.ControlByte, 0);
		RecieveState.IsConsoleZero = VISION_BIT_GET(data.ControlByte, 1);
		RecieveState.IsServoAck = VISION_BIT_GET(data.ControlByte, 2);
		RecieveState.IsAlaAck = VISION_BIT_GET(data.ControlByte, 3);
		RecieveState.IsPwrOn = VISION_BIT_GET(data.ControlByte, 6);
		RecieveState.IsPwrOff = VISION_BIT_GET(data.ControlByte, 7);
		RecieveState.CmdPcDataAcksByte = data.CmdPcDataAcksByte;
		RecieveState.FunctionsByte = data.FunctionsByte;
	}
}

void LandVision::SendVisionData()
{
	auto sendBytes = new char[SendPackageLength];

	LandVisionSendPackage sendPackage;
	sendPackage.Header = VISION_SEND_HAEDER;
	sendPackage.Tail = VISION_SEND_TAIL;
	sendPackage.PulseCount1 = ExchangeBit8(SendState.PoleLength[0]);
	sendPackage.PulseCount2 = ExchangeBit8(SendState.PoleLength[1]);
	sendPackage.PulseCount3 = ExchangeBit8(SendState.PoleLength[2]);
	sendPackage.PulseCount4 = ExchangeBit8(SendState.PoleLength[3]);
	sendPackage.PulseCount5 = ExchangeBit8(SendState.PoleLength[4]);
	sendPackage.PulseCount6 = ExchangeBit8(SendState.PoleLength[5]);

	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 0, SendState.IsServoAlarm[0]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 1, SendState.IsServoAlarm[1]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 2, SendState.IsServoAlarm[2]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 3, SendState.IsServoAlarm[3]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 4, SendState.IsServoAlarm[4]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 5, SendState.IsServoAlarm[5]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 6, SendState.IsServoFitRange[0]);
	VISION_BIT_SET_VAL(sendPackage.StateByteOne, 7, SendState.IsServoFitRange[1]);

	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 0, SendState.IsServoFitRange[2]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 1, SendState.IsServoFitRange[3]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 2, SendState.IsServoFitRange[4]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 3, SendState.IsServoFitRange[5]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 4, SendState.IsDeclination[0]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 5, SendState.IsDeclination[1]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 6, SendState.IsDeclination[2]);
	VISION_BIT_SET_VAL(sendPackage.StateByteTwo, 7, SendState.IsDeclination[3]);

	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 0, SendState.IsDeclination[4]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 1, SendState.IsDeclination[5]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 2, SendState.IsServoInit[0]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 3, SendState.IsServoInit[1]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 4, SendState.IsServoInit[2]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 5, SendState.IsServoInit[3]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 6, SendState.IsServoInit[4]);
	VISION_BIT_SET_VAL(sendPackage.StateByteThree, 7, SendState.IsServoInit[5]);

	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 0, SendState.IsLengthAlarm);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 1, SendState.IsTotalAlarm);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 2, SendState.IsServoShrinkAlarm);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 3, SendState.IsEMAlarm);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 4, SendState.IsAlarmNormal);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 5, SendState.IsAlarmHeavy);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 6, SendState.IsLockAlarm);
	VISION_BIT_SET_VAL(sendPackage.StateByteFour, 7, SendState.IsServoPowerAlarm);

	sendPackage.Crc = ExchangeBit8(CalCrc(&sendPackage)); 
	memcpy(sendBytes, &sendPackage, SendPackageLength);

	SendUARTMessageLength(VISION_PORT, sendBytes, SendPackageLength);
	delete[] sendBytes;
}

bool LandVision::GetIsShock()
{
	bool enableShock = false;
	if (RecieveState.IsShockOff == true)
	{
		enableShock = false;
	}
	else if(RecieveState.IsShockOn == true)
	{
		enableShock = true;
	}
	return enableShock;
}

double LandVision::GetShockHzFromRoadType()
{
	switch (NowRoadType)
	{
		//平地
		case RoadTypeFlatLand:
			return 8.0;
			//山路
		case RoadTypeMountain:
			return 5.0;
			//卵石路
		case RoadTypeStone:
			return 7.0;
			//草地1
		case RoadTypeGrass1:
			return 1.0;
			//草地2
		case RoadTypeGrass2:
			return 2.0;
			//草地3
		case RoadTypeGrass3:
			return 3.0;
			//草地4
		case RoadTypeGrass4:
			return 4.0;
			//草地5
        case RoadTypeGrass5:
			return 5.0;
			//柏油路
		case RoadTypeAsphalt:
			return 8.0;
			//水泥路
		case RoadTypeCement:
			return 0.5;
		default:
			return 0.0;
	}
	return 0.0;
}

double LandVision::GetShockValFromRoadType()
{
	switch (NowRoadType)
	{
		//平地
	case RoadTypeFlatLand:
		return 0.03;
		//山路
	case RoadTypeMountain:
		return 0.08;
		//卵石路
	case RoadTypeStone:
		return 0.05;
		//草地1
	case RoadTypeGrass1:
		return 0.04;
		//草地2
	case RoadTypeGrass2:
		return 0.04;
		//草地3
	case RoadTypeGrass3:
		return 0.04;
		//草地4
	case RoadTypeGrass4:
		return 0.04;
		//草地5
	case RoadTypeGrass5:
		return 0.04;
		//柏油路
	case RoadTypeAsphalt:
		return 0.05;
		//水泥路
	case RoadTypeCement:
		return 0.8;
	default:
		return 0.0;
	}
	return 0.0;
}
