// COM.h: interface for the CCOM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_)
#define AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ���ڶ�ȡ�����С
#define READBUFFER 10240
// ����д�뻺���С
#define WRITEBUFFER 10240
// �������˿ں�
#define MAX_COMNUM 50

class CCOM  
{
public:
	CCOM();
	virtual ~CCOM();
	// �򿪴���,�˿ں�,������,ֹͣλ,У��λ,����λ
	BOOL InitCOM(int nPort, int nBaud, int nStop, int nV, int nData);
	// ���ڷ�������
	BOOL SendCOMCode(unsigned char chCode[],int nNum);
	// �Ӵ��ڻ�ȡ����
	DWORD GetCOMData(unsigned char* pchBuffer);
	// �رմ���
	void closeCOM();
	// ��ȡ������Ϣ
	int GetCOMInfo(void);
private:
	HANDLE hCOM;
	int nComNum;
};

#endif // !defined(AFX_COM_H__99E44280_0F56_47FD_9584_338768C44625__INCLUDED_)
