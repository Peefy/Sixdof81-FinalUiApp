// COM.h: interface for the CCOM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_)
#define AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 串口读取缓存大小
#define READBUFFER 10240
// 串口写入缓存大小
#define WRITEBUFFER 10240
// 串口最大端口号
#define MAX_COMNUM 50

class CCOM  
{
public:
	CCOM();
	virtual ~CCOM();
	// 打开串口,端口号,波特率,停止位,校验位,数据位
	BOOL InitCOM(int nPort, int nBaud, int nStop, int nV, int nData);
	// 串口发送数据
	BOOL SendCOMCode(unsigned char chCode[],int nNum);
	// 从串口获取数据
	DWORD GetCOMData(unsigned char* pchBuffer);
	// 关闭串口
	void closeCOM();
	// 获取串口信息
	int GetCOMInfo(void);
private:
	HANDLE hCOM;
	int nComNum;
};

#endif // !defined(AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_)
