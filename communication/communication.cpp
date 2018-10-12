
#include "stdafx.h"
#include "communication.h"
#include "../config/inihelper.h"

using namespace std;

DataPackage Default = { 0 };
double DefaultPoleLength[POLE_COUNT] =
{
    DEFAULT_POLE_LENGTH,
    DEFAULT_POLE_LENGTH,
    DEFAULT_POLE_LENGTH,
    DEFAULT_POLE_LENGTH,
    DEFAULT_POLE_LENGTH,
    DEFAULT_POLE_LENGTH
};

void ResetDefaultData(DataPackage * data)
{
	data->AngleSpeed = 0;
	data->XYZSpeed = 0;
	data->X = 0;
	data->Y = 0;
	data->Z = 0;
	data->Roll = 0;
	data->Yaw = 0;
	data->Pitch = 0;
}

void ResetDefaultData(void)
{
    Default.AngleSpeed = 0;
    Default.XYZSpeed = 0;
    Default.X = 0;
    Default.Y = 0;
    Default.Z = 0;
    Default.Roll = 0;
    Default.Yaw = 0;
    Default.Pitch = 0;
}

void PrintDataPackageToString(DataPackage data)
{
    cout << "X:" << data.X << ";Y:" << data.Y << ";Z:" << data.Z;
    cout << ";Yaw:" << data.Yaw << ";Roll:" << data.Roll << ";Pitch:" << data.Pitch;
    cout << ";XYZSpeed:" << data.XYZSpeed << ";AngleSpeed:" << data.AngleSpeed << endl;
}

Translate::Translate()
{
    this->isStart = false;
    this->IsRecievedData = false;
    this->recivedData = DataPackage();
    this->dataLength = sizeof(DataPackage);
    this->pakageLength = this->dataLength + 2;
	this->SinInfoT = 0;
}

Translate::~Translate()
{
    this->closePort();
}

DataPackage Translate::ProviedInfo()
{
    unsigned char cRecved;
    if (isStart == true)
    {
        auto num = serialPort->GetBytesInCOM();
        if (num > 0)
        {    
            switch (status)
            {
            case 0:
				serialPort->ReadChar(cRecved);
                if (cRecved == HAEDER_ONE)
                {
                    status = 7;
                }
                break;
            case 7:
                    num = serialPort->GetBytesInCOM();
                    if (num <= dataLength)
                    {
                        status = 0;
                    }
                    ComPackage com;
                    for (UINT i = 0; i < dataLength; ++i)
                    {
                        serialPort->ReadChar(cRecved);
                        buffers[i] = cRecved;
                        com.Buffers[i] = buffers[i];
                    }
                    this->recivedData = com.Data;
					//read tail
					serialPort->ReadChar(cRecved);
					status = 0;
                break;
            default: break;
            }
        }
    }
    return this->recivedData;
}

bool Translate::SendInfo(DataPackage data)
{
    if (isStart == true)
    {
        ComPackage com;
        com.Data = data;
        return serialPort->WriteData(com.Buffers, dataLength);
		return true;
    }   
	return false;
}

bool Translate::Start()
{
    bool result;
    int baud;
    int portnum;
    config::ReadAll(result, baud, portnum);
    if (result == true)
    {
        return openPort(portnum, baud);
    }
    return openPort();
}

bool Translate::Stop()
{
    return closePort();
}

DataPackage Translate::ProviedTestSinInfo(double t)
{
	DataPackage data;
	//注意角度单位为0.01度
	data.Roll = 0;
	data.Yaw = 0;
	data.Pitch = 0;
	//位移单位为0.1mm
	data.X = 0;
	data.Y = 0;
	data.Z = (int)(-sin(t) * 400);  //40mm;
	return data;
}

DataPackage Translate::ProviedTestSingleAxesSinInfo(double f, double t)
{
	DataPackage data;
	//注意角度单位为0.01度
	data.Roll = 0;
	data.Yaw = (int)(-sin(2 * PI * f * t) * 200);  //40mm;
	data.Pitch = 0;
	//位移单位为0.1mm
	data.X = 0;
	data.Y = 0;
	data.Z = (int)(-sin(2 * PI * f * t) * 200);  //40mm;
	return data;
}

DataPackage Translate::ProviedTestMultiAxesAxesSinInfo(double * val, double * hz)
{
	DataPackage data;
	//位移单位为0.1mm
	data.X = (int)(-sin(2 * PI * hz[0] * SinInfoT) * val[0] / XYZ_SCALE);  
	data.Y = (int)(-sin(2 * PI * hz[1] * SinInfoT) * val[1] / XYZ_SCALE);
	data.Z = (int)(-sin(2 * PI * hz[2] * SinInfoT) * val[2] / XYZ_SCALE);
	//注意角度单位为0.01度
	data.Roll = (int)(-sin(2 * PI * hz[3] * SinInfoT) * val[3] / DEG_SCALE);
	data.Pitch = (int)(-sin(2 * PI * hz[4] * SinInfoT) * val[4] / DEG_SCALE);
	data.Yaw = (int)(-sin(2 * PI * hz[5] * SinInfoT) * val[5] / DEG_SCALE);
	SinInfoT += SIN_INFO_T_DELTA;
	return data;
}

DataPackage Translate::ProviedTestMultiAxesAxesSinInfo(double * val, double * hz, double delta)
{
	DataPackage data;
	//位移单位为0.1mm
	data.X = (int)(-sin(2 * PI * hz[0] * SinInfoT) * val[0] / XYZ_SCALE);  
	data.Y = (int)(-sin(2 * PI * hz[1] * SinInfoT) * val[1] / XYZ_SCALE);
	data.Z = (int)(-sin(2 * PI * hz[2] * SinInfoT) * val[2] / XYZ_SCALE);
	//注意角度单位为0.01度
	data.Roll = (int)(-sin(2 * PI * hz[3] * SinInfoT) * val[3] / DEG_SCALE);
	data.Pitch = (int)(-sin(2 * PI * hz[4] * SinInfoT) * val[4] / DEG_SCALE);
	data.Yaw = (int)(-sin(2 * PI * hz[5] * SinInfoT) * val[5] / DEG_SCALE);
	SinInfoT += delta;
	return data;
}

bool Translate::openPort()
{
    serialPort = new CSerialPort();
    for (auto i = 1; i < 10; ++i)
    {
        isStart = serialPort->InitPort(i, CBR_57600);
        if (isStart == true)
        {
            break;
        }
    }
    return isStart;
}

bool Translate::openPort(int i, int baud)
{
    serialPort = new CSerialPort();
    isStart = serialPort->InitPort(i, baud);
    return isStart;
}

bool Translate::closePort()
{
    delete serialPort;
	isStart = false;
    return isStart;
}

