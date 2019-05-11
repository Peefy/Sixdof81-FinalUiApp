
#include "stdafx.h"
#include "platformapi.h"

#define API_BUFFER_QUEUE_LENGTH   10000
#define READ_BUFFER_LENGTH        4096

ApiControl::ApiControl() : 
	IsRecievedData(false), 
	IsStart(false),
	ControlCommand(ApiControlCommandInt32::API_CTL_CMD_NONE)
{
	Open();
}

ApiControl::~ApiControl()
{
	Close();
}

bool ApiControl::Open()
{
	IsStart = serialPort.InitPort(API_PORT_NUMBER, API_PORT_BAUDRATE) == true;
	return IsStart;
}

bool ApiControl::Close()
{
	return true;
}

void ApiControl::GatherData()
{
	if (IsStart == false)
	{
		return;
	}
	static int uiRemainLength = 0;
	static int length = sizeof(ApiDataPackage);
	static UCHAR chData[API_BUFFER_QUEUE_LENGTH] = {0};
	static UCHAR *pch = chData;
	int i;
	UCHAR chReadData[READ_BUFFER_LENGTH] = {0};
	unsigned int uiReceived = serialPort.GetBytesInCOM();
	unsigned char cRecved = 0;
	for (int i = 0; i < uiReceived; ++i)
	{
		serialPort.ReadChar(cRecved);
		chReadData[i] = cRecved;
	}
	if(uiReceived == 0)
	{
		return;		
	}
	memcpy(pch, chReadData, uiReceived);    //将数据置于chData[]中
	i = 0;
	int j = uiRemainLength + uiReceived - length;
	while(i <= j)
	{
		UCHAR *pData = &chData[i];
		if((pData[0] == API_DATA_HEAD_ONE) && 
			(pData[1] == API_DATA_HEAD_TWO) && 
			(pData[length - 2] == API_DATA_TAIL_ONE) && 
			(pData[length - 1] == API_DATA_TAIL_TWO) &&
			JudgeCheckByte(pData, pData[length - 3], 0, length - 4))
		{       	
			memcpy(&Data, &pData[0], length);
			IsRecievedData = true;
			ControlCommand = static_cast<ApiControlCommandInt32>(Data.ControlCommand);
			i += length;		
			continue;
		}
		else
		{
			i += 1;
		}
	}
	uiRemainLength += uiReceived - i;
	if(uiRemainLength != 0)
	{
		memcpy(chReadData, &chData[i], uiRemainLength);
		memcpy(chData, chReadData, uiRemainLength);
	}
	pch = &chData[uiRemainLength];
}

bool ApiControl::JudgeCheckByte(UCHAR* pData, UCHAR check, int startindex, int length)
{
	UCHAR b = 0;
	for (int i = startindex; i < length + startindex; ++i)
	{
		b |= pData[startindex];
	}
	return true;
	//return b == check;
}