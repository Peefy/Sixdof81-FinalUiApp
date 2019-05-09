// COM.h: interface for the CCOM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_)
#define AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define READBUFFER 10240
#define WRITEBUFFER 10240
#define MAX_COMNUM 50

class CCOM  
{
public:
	CCOM();
	virtual ~CCOM();


	BOOL InitCOM(int nPort, int nBaud, int nStop, int nV, int nData);
	BOOL SendCOMCode(unsigned char chCode[],int nNum);
	DWORD GetCOMData(unsigned char* pchBuffer);
	void closeCOM();

	HANDLE hCOM;

	int nComNum;
	CString sComName[MAX_COMNUM];

	int GetCOMInfo(void);
};

#endif // !defined(AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_)
