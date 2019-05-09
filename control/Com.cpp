// COM.cpp: implementation of the CCOM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCOM::CCOM()
{
	hCOM = NULL;
}

CCOM::~CCOM()
{
	if(hCOM)
	{
		CloseHandle(hCOM);
		hCOM = NULL;
	}
}

BOOL CCOM::InitCOM(int nPort, int nBaud, int nStop, int nParity, int nData)
{
	DCB dCB;
	COMMTIMEOUTS ct;
	char szPort[50];
	sprintf_s(szPort, "\\\\.\\COM%d", nPort);
	hCOM = CreateFileA(szPort, GENERIC_READ|GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,0,NULL);
	if(hCOM == INVALID_HANDLE_VALUE)
		return FALSE;

	SetupComm(hCOM,READBUFFER,WRITEBUFFER);
	PurgeComm(hCOM,PURGE_TXCLEAR|PURGE_RXCLEAR);

	if(!GetCommState(hCOM,&dCB))
	{
		closeCOM();
		return FALSE;
	}

	dCB.BaudRate = nBaud;
	dCB.ByteSize = nData;
	dCB.Parity = nParity;
	dCB.StopBits = nStop;
	if(!SetCommState(hCOM,&dCB))
	{
		closeCOM();
		return FALSE;
	}

	ct.ReadIntervalTimeout = MAXDWORD;
	ct.ReadTotalTimeoutConstant = 0;
	ct.ReadTotalTimeoutMultiplier = 0;
	ct.WriteTotalTimeoutConstant = 0;
	ct.WriteTotalTimeoutMultiplier = 0;

	if(!SetCommTimeouts(hCOM,&ct))
	{
		closeCOM();
		return FALSE;
	}

	// Çå»º³åÇø
	UCHAR chReadData[READBUFFER];
	GetCOMData(chReadData);

	return TRUE;
}

BOOL CCOM::SendCOMCode(unsigned char chCode[],int nNum)
{
	DWORD dwWritenNum;
	return WriteFile(hCOM,chCode,nNum,&dwWritenNum,NULL);
}

DWORD CCOM::GetCOMData(unsigned char* pchBuffer)
{
	DWORD dwReadNum;
	ReadFile(hCOM,pchBuffer,READBUFFER,&dwReadNum,NULL);
	return dwReadNum;
}

void CCOM::closeCOM()
{
	if(hCOM)
	{
		CloseHandle(hCOM);
		hCOM = NULL;
	}
}

int CCOM::GetCOMInfo(void)
{
	return -1;
}
