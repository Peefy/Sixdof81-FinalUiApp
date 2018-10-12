#ifndef _PCI2394_DEVICE_
#define _PCI2394_DEVICE_

#include "windows.h"
#include "stdio.h"
#include "conio.h"

// ############################### PCI2394���ܼ��˵�� ############################################
// PCI2394��һ��pci���ߵ�4�������������ͼ�����.�ÿ������ĸ�32λ��ԪAB��λ���������,��ʱ�䷶Χѡ���8λ��ʱ��,
// 4·���������������4·�������������.�������ж�Ԫ�ǳ��ʺ������˶����ƺ�λ�ü��\4��32λ��/��������\���˻�
// ��ѹ����\���ϴ���Χʱ��ѡ������8λ��ʱ��\��ѡ�������ʵ�4�������˲���\ÿ��������ѭ��x1, x2, x4����\����/����
// �ͼ�/��������\������ѹ2,500 VDC 

//################# ���ڼ�������ʵ��Ӳ�������Լ�����Աʹ��ѡ��###################################
// ��������ʵ��Ӳ������
typedef struct _PCI2394_PARA_CNT
{
	LONG lCNTMode;		// �������������ģʽ(CM)
	LONG lResetMode;	// ��������λֵ(RM)
	LONG bOverflowLock;	// �Ƿ������������������(OL) TRUE=���� 
	LONG bUnderflowLock;// �Ƿ������������������(UL) TRUE=����
	LONG bDigitFilter;	// ��������Ƿ���������˲�(DF) TRUE=����
	LONG lLatchMode;	// ����ģʽ����(7��ģʽ)
	LONG lIndexReset;	// ������λ
} PCI2394_PARA_CNT, *PPCI2394_PARA_CNT;

//***********************************************************
// PCI2394_PARA_CNT�����ṹ�����Աʹ�õ�ѡ��

const ULONG MAX_CHANNEL_COUNT = 4;  // ͨ������

// lCNTMode  �������������ģʽ�ĳ�Ա
#define PCI2394_CNTMODE_DISABLE			0x00	// �������������ģʽ��Ч, �����Է������еļĴ���
#define PCI2394_CNTMODE_QUADRATURE_X1	0x01	// ������������룬Channel A��������Ч��ʼ����
#define PCI2394_CNTMODE_QUADRATURE_X2	0x02	// ������������룬Channel AֻҪ������Ϳ�ʼ����
#define PCI2394_CNTMODE_QUADRATURE_X4	0x03	// ������������룬Channel A��Channel BֻҪ������Ϳ�ʼ����
#define PCI2394_CNTMODE_2_PULSE			0x04	// ˫����ģʽ,һ����˳ʱ���������һ������ʱ�����, ��Channel B��������ʱ��Ч
#define PCI2394_CNTMODE_1_PULSE			0x05	// A��Ϊ���壬B��Ϊ�����������Channel B �� 1����Channel A����������Ч��ʼ����
// ���Channel B �� 0�� ��Channel A����������Ч��ʼ��������
// lResetMode  ��������λֵ�ĳ�Ա
#define PCI2394_RESETMODE_MIDDLE		0x00	// ��������λ��0x80000000
#define PCI2394_RESETMODE_ZERO			0x01	// ��������λ��0x00000000

// lLatchMode  ����ģʽ����(7��ģʽ) �����ͨ��"��(|)"��ʽ���
#define PCI2394_LATCHMODE_SOFT			0x01	// ���������������� SoftWare
#define PCI2394_LATCHMODE_IDX			0x02	// ����������������� Index
#define PCI2394_LATCHMODE_TM			0x04	// ��ʱ��������������� Time
#define PCI2394_LATCHMODE_DI0			0x10	// ����������0ͨ���������������
#define PCI2394_LATCHMODE_DI1			0x20	// ����������1ͨ���������������
#define PCI2394_LATCHMODE_DI2			0x40	// ����������2ͨ���������������
#define PCI2394_LATCHMODE_DI3			0x80	// ����������3ͨ���������������

// lSampClockSrc  ѡ�����ʱ��Դ
#define PCI2394_CLOCKSRC_8MHz			0x00	// 8Mhzʱ��
#define PCI2394_CLOCKSRC_4MHz			0x01	// 4Mhzʱ��
#define PCI2394_CLOCKSRC_2MHz			0x02	// 2Mhzʱ��
#define PCI2394_CLOCKSRC_1MHz			0x03	// 1Mhzʱ��

// ####################### �жϲ����ṹ�� ##############################################
typedef struct _PCI2394_PARA_INT
{
	LONG bEnableInt;			// ���ж�ʹ��
	LONG bTimerInt;				// ��ʱ���ж�
	LONG bCNTOverflowInt[MAX_CHANNEL_COUNT];		// �����ж�
	LONG bCNTUnderflowInt[MAX_CHANNEL_COUNT];		// ͨ�������ж�
	LONG bCNTOverCompInt[MAX_CHANNEL_COUNT];	//
	LONG bCNTUnderCompInt[MAX_CHANNEL_COUNT];
	LONG bCNTIndexInt[MAX_CHANNEL_COUNT];
	LONG bDIInt[MAX_CHANNEL_COUNT];
} PCI2394_PARA_INT, *PPCI2394_PARA_INT;

//***********************************************************
// PCI2394_PARA_INT�����ṹ�����Աʹ�õ�ѡ��
// INTOVn  �����жϿ���ʹ��
#define PCI2394_OV_DISABLE		0x00	// �ж����粻����
#define PCI2394_OV_ENABLE		0x01	// �ж���������

// INTUNn  �����жϿ���ʹ��
#define PCI2394_UN_DISABLE		0x00	// �ж����粻����
#define PCI2394_UN_ENABLE		0x01	// �ж���������

// INTIXn  ����״̬�ж�ʹ��
#define PCI2394_IX_DISABLE		0x00	// ����״̬�жϲ�����
#define PCI2394_IX_ENABLE		0x01	// ����״̬�ж�����

// INTDIn  ���������ж�ʹ��
#define PCI2394_DI_DISABLE		0x00	// ���������жϲ�����
#define PCI2394_DI_ENABLE		0x01	// ���������ж�����

// INTOCn  ���������ڱȽ�ֵ�ж�ʹ��
#define PCI2394_OC_DISABLE		0x00	// ���������ڱȽ�ֵ�жϲ�����
#define PCI2394_OC_ENABLE		0x01	// ���������ڱȽ�ֵ�ж�����

// INTUCn  ������С�ڱȽ�ֵ�ж�ʹ��
#define PCI2394_UC_DISABLE		0x00	// ������С�ڱȽ�ֵ�жϲ�����
#define PCI2394_UC_ENABLE		0x01	// ������С�ڱȽ�ֵ�ж�����

// INTTM  ��ʱ�������ж�ʹ��
#define PCI2394_TM_DISABLE		0x00	// ��ʱ�������жϲ�����
#define PCI2394_TM_ENABLE		0x01	// ��ʱ�������ж�����

// INTIE  ȫ���ж�ʹ��
#define PCI2394_IE_DISABLE		0x00	// ȫ���жϲ�����
#define PCI2394_IE_ENABLE		0x01	// ȫ���ж�����


// ####################### �����������ṹ���� ##############################################
// ���������ģʽ���ýṹ��
typedef struct  _PCI2394_PARA_MODE_DO
{
	BYTE bDOManualCtrl;		// (DM)�Ƿ�ֱ����������� =TRUE: byDOSts ��Ч; =FALSE: ��byDOSts������Ч
	BYTE byDOSts;			// �� bDOManualCtrl=1 ��Ч
	BYTE bOverCompare;		// (OC)�������������ͨ���Ƿ��ô��ڱȽϼĴ�����ֵ(0: N/A��1: �ô���)
	BYTE bUnderCompare;		// (UC)�������������ͨ���Ƿ���С�ڱȽϼĴ�����ֵ(0: N/A��1: ��С��)
	BYTE Level;				// (LE)������������� 0 Pulse with counter clock, 1 Level with clear interrupt
} PCI2394_PARA_MODE_DO, *PPCI2394_PARA_MODE_DO;

//***********************************************************
// �������������PCI2394_PARA_DO�ṹ���������
// LEn  ���������ģʽ����(���塢�ж�)
#define PCI2394_LE_PULSE			0x00		// Pulse with counter clock
#define PCI2394_LE_LEVEL			0x01		// Level with clear interrupt

// DMn  ���������ģʽ����
#define PCI2394_DM_NORMAL			0x00		// Normal
#define PCI2394_DM_INDICATED		0x01		// Indicated

//***********************************************************
// ��ʱ���趨ʹ�� PCI2394_SetTimer
// TimerDiviBase  ѡ��ʱ��ʱ�ӻ�Դ
#define PCI2394_TIMER_BASE_50KHz	0x00	// 50KHzʱ�ӻ�Դ
#define PCI2394_TIMER_BASE_5KHz		0x01	// 5KHzʱ�ӻ�Դ
#define PCI2394_TIMER_BASE_500Hz	0x02	// 500Hzʱ�ӻ�Դ
#define PCI2394_TIMER_BASE_50Hz		0x03	// 50Hzʱ�ӻ�Դ
#define PCI2394_TIMER_BASE_5Hz		0x04	// 5Hzʱ�ӻ�Դ

//***********************************************************
// �û������ӿ�
#ifndef _PCI2394_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## ����ͨ�ú��� #################################
	// �����ڱ��豸�����������
	DEVAPI HANDLE FAR PASCAL PCI2394_CreateDevice(int DeviceLgcID=0);		// �����豸����
	HANDLE DEVAPI FAR PASCAL PCI2394_CreateDeviceEx(int DevicePhysID = 0);  // ������Ŵ����豸����
	DEVAPI LONG FAR PASCAL PCI2394_GetDeviceCount(HANDLE hDevice);			// ȡ���豸��̨��
	DEVAPI BOOL FAR PASCAL PCI2394_ListDeviceDlg(HANDLE hDevice);			// �б�ϵͳ���е����еĸ�PCI�豸
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID);		// �õ��豸���߼�����ID
    DEVAPI BOOL FAR PASCAL PCI2394_ReleaseDevice(HANDLE hDevice);			// �ر��豸,��ֹ����,���ͷ���Դ

	//####################### �������붨ʱ���������� #########################
	// ʱ��Դ����
	DEVAPI BOOL FAR PASCAL PCI2394_SetDeviceClock(HANDLE hDevice,  			// �豸���
												  LONG lSampClockSrc);		// ѡ�����ʱ��Դ

	DEVAPI LONG FAR PASCAL PCI2394_GetDeviceClock(HANDLE hDevice) ; 		// �豸���

	//  ��ʼ��ָ��ͨ��������
	DEVAPI BOOL FAR PASCAL PCI2394_InitDeviceCNT(							// ��ʼ����·������
												HANDLE hDevice,				// �豸���
												PPCI2394_PARA_CNT pCNTPara,	// ���������Ʋ���
												int nCNTChannel = 0);		// ������ͨ���ţ�0-3��
	
	// ���ú�ȡ�ü���������ģʽ
	DEVAPI BOOL FAR PASCAL PCI2394_SetCNTMode(  
											  HANDLE hDevice,				// �豸���									
											  LONG   lCNTMode, 				// ����ģʽ
											  int nCNTChannel = 0);			// ������ͨ���ţ�0-3��
	
	DEVAPI LONG FAR PASCAL PCI2394_GetCNTMode(
											  HANDLE hDevice,				// �豸���									
											  int nCNTChannel = 0);			// ������ͨ���ţ�0-3��
	
	// ���ú͵õ� ����ģʽ �ǻ���� 
	DEVAPI BOOL FAR PASCAL PCI2394_SetLatchMode(  
											HANDLE hDevice, 				// �豸���	
											LONG   lLatchMode,				// �豸���									
											int    nCNTChannel  = 0);		// ������ͨ���ţ�0-3��
	
	DEVAPI LONG FAR PASCAL PCI2394_GetLatchMode( 
											HANDLE hDevice,					// �豸���									
											int nCNTChannel = 0);			// ������ͨ���ţ�0-3��
	
	// ���������������趨	
	DEVAPI BOOL FAR PASCAL PCI2394_EnableOverflowLock(
											HANDLE hDevice,					// �豸���
											BOOL bOverflowLock, 
											int nCNTChannel = 0);
	DEVAPI BOOL FAR PASCAL PCI2394_IsOverflowLock(
											HANDLE hDevice,					// �豸���
											int nCNTChannel = 0);
	// ��������������	
	DEVAPI BOOL FAR PASCAL PCI2394_EnableUnderflowLock(
											HANDLE hDevice,					// �豸���
											BOOL bUnOverflowLock, 
											int nCNTChannel = 0);
	DEVAPI BOOL FAR PASCAL PCI2394_IsUnderflowLock(
											HANDLE hDevice,					// �豸���
											int nCNTChannel = 0);
	// �����˲�
	DEVAPI BOOL FAR PASCAL PCI2394_EnableDigitFilter(
											HANDLE hDevice,					// �豸���
											BOOL bDigitFilter, 
											int nCNTChannel = 0);
	DEVAPI BOOL FAR PASCAL PCI2394_IsDigitFilter(
											HANDLE hDevice,					// �豸���
											int nCNTChannel = 0);	

	// ȡ��ָ��ͨ����������ֵ
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceCNT(					
											HANDLE hDevice,					// �豸���
											PULONG pCNTValue,
											int nCNTChannel = 0);			// ���м�������״̬��Ϣ
	
	// Ԥ�ø�λģʽ
	DEVAPI BOOL FAR PASCAL PCI2394_SetResetMode(
											HANDLE hDevice,					// �豸���									
											LONG   lResetMode,				// Ԥ�ø�λģʽ
											int nCNTChannel = 0);			// ������ͨ���ţ�0-3��
	
	DEVAPI LONG FAR PASCAL PCI2394_GetResetMode(
											HANDLE hDevice,					// �豸���									
											int nCNTChannel = 0);			// ������ͨ���ţ�0-3��

	// ��λ������
	DEVAPI BOOL FAR PASCAL PCI2394_ResetDeviceCNT(
											HANDLE hDevice,					// �豸���
											int nCNTChannel = 0);			//  ��λ��������Ԥ��ģʽ(��SetResetModeԤ��)

	// ����(0-3)·�������Ƚ�ֵ
	DEVAPI BOOL FAR PASCAL PCI2394_SetDevCompValue(
											HANDLE hDevice,					// �豸���
											ULONG CNTCompValue,				// �������Ƚ�ֵ	
											int nCNTChannel = 0);			// ����(0-3)·�������Ƚ�ֵ
	
	DEVAPI BOOL FAR PASCAL PCI2394_GetDevCompValue(
											HANDLE hDevice,					// �豸���
											PULONG pCNTCompValue, 
											int nCNTChannel = 0);			// ȡ��(0-3)·�������Ƚ�ֵ
	
	// ���ö�ʱ��
	DEVAPI BOOL FAR PASCAL PCI2394_SetTimer(
											HANDLE hDevice,					// �豸���
											LONG   lTimerDivider,			// ʱ�ӷ�Ƶ��(1-255)(DV)
											LONG   lTimerDiviBase);			// ��Ƶʱ�ӻ�׼Դѡ��(TB)	
	// 20 microseconds ~ 51 second
	// ��ȡ��ʱ�� ���ص�λΪ microsecond
	DEVAPI ULONG FAR PASCAL PCI2394_GetTimer(
											HANDLE hDevice,					// �豸���
											PLONG pTimerDivider,			// ʱ�ӷ�Ƶ��(1-255)(DV)
											PLONG pTimerBaseSel);
	
	//##################### �ж�ʵ�ּ��������ƺ��� ###################################	
	DEVAPI BOOL FAR PASCAL PCI2394_InitDeviceInt(
											HANDLE hDevice,					// �豸���
											HANDLE hEventInt,
											PPCI2394_PARA_INT pIntPara);    // �ж����ò���
	DEVAPI BOOL FAR PASCAL PCI2394_ReleaseDeviceInt(HANDLE hDevice);		// �ͷ��ж���Դ

	DEVAPI BOOL FAR PASCAL PCI2394_ModifyDeviceInt(							// �޸��ж� �����ڳ�ʼ���жϳɹ���ſ��Ե����������
											HANDLE hDevice,					// �豸���	
											PPCI2394_PARA_INT pIntPara);	// �ж����ò���

	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceIntSrc(
											HANDLE hDevice,					// �豸���
											PPCI2394_PARA_INT pIntPara);
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceIntCount(HANDLE hDevice, PULONG pIntSrc);// �õ��жϴ���	
	DEVAPI BOOL FAR PASCAL PCI2394_ResetDeviceIntSrc(HANDLE hDevice);		//��Դ

	//##################### ���������״̬ģʽ���ƺ��� ###################################	
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceDI(
											HANDLE hDevice,					// �豸���
											BYTE byDISts[MAX_CHANNEL_COUNT]);// ����������
	
	DEVAPI BOOL FAR PASCAL PCI2394_SetDevDOMode(
											HANDLE hDevice,					// �豸���
											PCI2394_PARA_MODE_DO DOMode[MAX_CHANNEL_COUNT]);
	
	DEVAPI BOOL FAR PASCAL PCI2394_GetDevDOMode(
											HANDLE hDevice,						// �豸���
											PCI2394_PARA_MODE_DO DOMode[MAX_CHANNEL_COUNT]);// ���DOģʽ
					
	//#################### CNTӲ���������桢��ȡ����(�ϲ��û�����) ###########################
	DEVAPI BOOL FAR PASCAL PCI2394_SaveDevicePara(											// ����PCI2394����������ͨ������
											HANDLE hDevice,									// �豸���	
											PCI2394_PARA_CNT CNTPara[MAX_CHANNEL_COUNT],	// ��������������ṹ��
											PCI2394_PARA_MODE_DO DOPara[MAX_CHANNEL_COUNT],	// ��������������/��������ṹ��											  
											int nChannelCount);
	
	DEVAPI BOOL FAR PASCAL PCI2394_LoadDevicePara(											// ȡ��PCI2394����������ͨ������
											HANDLE hDevice,									// �豸���
											PCI2394_PARA_CNT CNTPara[MAX_CHANNEL_COUNT],	// ��������������ṹ��
											PCI2394_PARA_MODE_DO DOPara[MAX_CHANNEL_COUNT],	// ��������������/��������ṹ��											  
											int nChannelCount);	
	// �����ж�����
	DEVAPI BOOL FAR PASCAL PCI2394_SaveDeviceINTPara(										// ȡ��PCI2394����������ͨ������
											HANDLE hDevice,									// �豸���
											PPCI2394_PARA_INT pINTPara);					// ��������������ṹ��		
	
	// �����ж�����
    DEVAPI BOOL FAR PASCAL PCI2394_LoadDeviceINTPara(	
											HANDLE hDevice,									// �豸���
											PPCI2394_PARA_INT pINTPara);					// ��������������ṹ��
	//################# I/O�˿�ֱ�Ӳ�������д���� ########################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	// ����Щ������Ҫ�����ڴ�ͳ�豸����ISA���ߡ����ڡ����ڵ��豸���������ڱ�PCI�豸
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceAddr(					// ȡ��ָ����ָ���豸ID�ŵ�ӳ��Ĵ��������Ի���ַ�������豸����
												HANDLE hDevice,		// �豸������
												PUCHAR* LinearAddr,	// ����ָ��ӳ��Ĵ��������Ե�ַ
											    PUCHAR* PhysAddr,	//  ����ָ��ӳ��Ĵ����������ַ
												int RegisterID);	// �豸ӳ��Ĵ�����ID�ţ�0-5��

    DEVAPI BOOL FAR PASCAL PCI2394_WritePortByte(HANDLE hDevice, PCHAR nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI2394_WritePortWord(HANDLE hDevice, PCHAR nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI2394_WritePortULongEx(HANDLE hDevice, PCHAR nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI2394_ReadPortByte(HANDLE hDevice, PCHAR nPort);
    DEVAPI WORD FAR PASCAL PCI2394_ReadPortWord(HANDLE hDevice, PCHAR nPort);
    DEVAPI ULONG FAR PASCAL PCI2394_ReadPortULongEx(HANDLE hDevice, PCHAR nPort);

   	//######################### �ļ��������� ##############################
    DEVAPI HANDLE FAR PASCAL PCI2394_CreateFileObject(			// ��ʼ�ļ�ϵͳ
										  HANDLE hDevice,		// �豸����
										  LPCTSTR NewFileName,	// ���ļ���
										  int Mode);			// �ļ�������ʽ    
    DEVAPI BOOL FAR PASCAL PCI2394_WriteFile(					// �����û��ռ�������
										HANDLE hFileObject,		// �豸����
										PVOID pDataBuffer,		// �û����ݿռ��ַ
										ULONG nWriteSizeBytes); // ��������С(�ֽ�)

    DEVAPI BOOL FAR PASCAL PCI2394_ReadFile(					// ������
										  HANDLE hFileObject,	// �豸����
										  PVOID pDataBuffer,	// �����ļ����ݵ��û��ڴ滺����
										  ULONG OffsetBytes,	// ���ļ�ǰ�˿�ʼ��ƫ��λ��
										  ULONG nReadSizeBytes); // ��ƫ��λ�ÿ�ʼ�����ֽ���

	DEVAPI BOOL FAR PASCAL PCI2394_SetFileOffset(				// �����ļ�ƫ��ָ��
										  HANDLE hFileObject,   // �ļ�����
										  ULONG nOffsetBytes);  // �ļ�ƫ��λ�ã�����Ϊ��λ��  

	DEVAPI ULONG FAR PASCAL PCI2394_GetFileLength(HANDLE hFileObject); // ȡ��ָ���ļ����ȣ��ֽڣ�

    DEVAPI BOOL FAR PASCAL PCI2394_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI2394_GetDiskFreeBytes(		// ���ָ���̷��Ĵ��̿ռ�(ע��ʹ��64λ����)
								      LPCTSTR DiskName);		// �̷���,��C��Ϊ"C:\\"), D��Ϊ"D:\\"

	//########################### �̲߳������� ######################################
	DEVAPI HANDLE FAR PASCAL PCI2394_CreateSystemEvent(void);			// �����ں��¼����󣬹�InitDeviceInt��VB���̵߳Ⱥ���ʹ��
	DEVAPI BOOL FAR PASCAL PCI2394_ReleaseSystemEvent(HANDLE hEvent);	// �ͷ��ں��¼�����
	
#ifdef __cplusplus
}
#endif

// �Զ������������������
#ifndef _PCI2394_DRIVER_
	#ifndef _WIN64
		#pragma comment(lib, "PCI2394.lib")
		#pragma message("======== Welcome to use our art company's products!")
		#pragma message("======== Automatically linking with PCI2394.dll...")
		#pragma message("======== Successfully linked with PCI2394.dll")
	#else
		#pragma comment(lib, "PCI2394_64.lib")
		#pragma message("======== Welcome to use our art company's products!")
		#pragma message("======== Automatically linking with PCI2394_64.dll...")
		#pragma message("======== Successfully linked with PCI2394_64.dll")
	#endif
#endif

#endif // _PCI2394_DEVICE_
