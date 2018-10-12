#ifndef _PCI2394_DEVICE_
#define _PCI2394_DEVICE_

#include "windows.h"
#include "stdio.h"
#include "conio.h"

// ############################### PCI2394功能简介说明 ############################################
// PCI2394是一款pci总线的4轴正交编码器和计数器.该卡带有四个32位四元AB相位编码计数器,多时间范围选择的8位定时器,
// 4路隔离数字量输入和4路隔离数字量输出.它灵活的中断元非常适合由于运动控制和位置监控\4个32位加/减计数器\单端或
// 差压输入\卡上带宽范围时间选择器的8位定时器\可选采样速率的4级数字滤波器\每个编码器循环x1, x2, x4计数\脉冲/方向
// 和加/减计数器\光隔离电压2,500 VDC 

//################# 用于计数器的实际硬件参数以及各成员使用选项###################################
// 计数器的实际硬件参数
typedef struct _PCI2394_PARA_CNT
{
	LONG lCNTMode;		// 计数器输入控制模式(CM)
	LONG lResetMode;	// 计数器复位值(RM)
	LONG bOverflowLock;	// 是否计数器上溢锁定控制(OL) TRUE=锁定 
	LONG bUnderflowLock;// 是否计数器下溢锁定控制(UL) TRUE=锁定
	LONG bDigitFilter;	// 差分输入是否进行数字滤波(DF) TRUE=过滤
	LONG lLatchMode;	// 锁存模式设置(7种模式)
	LONG lIndexReset;	// 索引复位
} PCI2394_PARA_CNT, *PPCI2394_PARA_CNT;

//***********************************************************
// PCI2394_PARA_CNT参数结构体各成员使用的选项

const ULONG MAX_CHANNEL_COUNT = 4;  // 通道个数

// lCNTMode  计数器输入控制模式的成员
#define PCI2394_CNTMODE_DISABLE			0x00	// 计数器输入控制模式无效, 但可以访问所有的寄存器
#define PCI2394_CNTMODE_QUADRATURE_X1	0x01	// 计数器差分输入，Channel A上升沿有效开始计数
#define PCI2394_CNTMODE_QUADRATURE_X2	0x02	// 计数器差分输入，Channel A只要有跳变就开始计数
#define PCI2394_CNTMODE_QUADRATURE_X4	0x03	// 计数器差分输入，Channel A或Channel B只要有跳变就开始计数
#define PCI2394_CNTMODE_2_PULSE			0x04	// 双脉冲模式,一个做顺时针计数，另一个做逆时针计数, 当Channel B在上升沿时有效
#define PCI2394_CNTMODE_1_PULSE			0x05	// A线为脉冲，B线为方向。例：如果Channel B 是 1，则Channel A在上升沿有效开始减数
// 如果Channel B 是 0， 则Channel A在上升沿有效开始递增加数
// lResetMode  计数器复位值的成员
#define PCI2394_RESETMODE_MIDDLE		0x00	// 计数器复位到0x80000000
#define PCI2394_RESETMODE_ZERO			0x01	// 计数器复位到0x00000000

// lLatchMode  锁存模式设置(7种模式) 各项功能通过"或(|)"方式组合
#define PCI2394_LATCHMODE_SOFT			0x01	// 软件锁存计数器数据 SoftWare
#define PCI2394_LATCHMODE_IDX			0x02	// 索引锁存计数器数据 Index
#define PCI2394_LATCHMODE_TM			0x04	// 定时器锁存计数器数据 Time
#define PCI2394_LATCHMODE_DI0			0x10	// 开关量输入0通道锁存计数器数据
#define PCI2394_LATCHMODE_DI1			0x20	// 开关量输入1通道锁存计数器数据
#define PCI2394_LATCHMODE_DI2			0x40	// 开关量输入2通道锁存计数器数据
#define PCI2394_LATCHMODE_DI3			0x80	// 开关量输入3通道锁存计数器数据

// lSampClockSrc  选择采样时钟源
#define PCI2394_CLOCKSRC_8MHz			0x00	// 8Mhz时钟
#define PCI2394_CLOCKSRC_4MHz			0x01	// 4Mhz时钟
#define PCI2394_CLOCKSRC_2MHz			0x02	// 2Mhz时钟
#define PCI2394_CLOCKSRC_1MHz			0x03	// 1Mhz时钟

// ####################### 中断参数结构体 ##############################################
typedef struct _PCI2394_PARA_INT
{
	LONG bEnableInt;			// 总中断使能
	LONG bTimerInt;				// 定时器中断
	LONG bCNTOverflowInt[MAX_CHANNEL_COUNT];		// 上溢中断
	LONG bCNTUnderflowInt[MAX_CHANNEL_COUNT];		// 通道下溢中断
	LONG bCNTOverCompInt[MAX_CHANNEL_COUNT];	//
	LONG bCNTUnderCompInt[MAX_CHANNEL_COUNT];
	LONG bCNTIndexInt[MAX_CHANNEL_COUNT];
	LONG bDIInt[MAX_CHANNEL_COUNT];
} PCI2394_PARA_INT, *PPCI2394_PARA_INT;

//***********************************************************
// PCI2394_PARA_INT参数结构体各成员使用的选项
// INTOVn  上溢中断控制使能
#define PCI2394_OV_DISABLE		0x00	// 中断上溢不允许
#define PCI2394_OV_ENABLE		0x01	// 中断上溢允许

// INTUNn  下溢中断控制使能
#define PCI2394_UN_DISABLE		0x00	// 中断下溢不允许
#define PCI2394_UN_ENABLE		0x01	// 中断下溢允许

// INTIXn  索引状态中断使能
#define PCI2394_IX_DISABLE		0x00	// 索引状态中断不允许
#define PCI2394_IX_ENABLE		0x01	// 索引状态中断允许

// INTDIn  数字输入中断使能
#define PCI2394_DI_DISABLE		0x00	// 数字输入中断不允许
#define PCI2394_DI_ENABLE		0x01	// 数字输入中断允许

// INTOCn  计数器大于比较值中断使能
#define PCI2394_OC_DISABLE		0x00	// 计数器大于比较值中断不允许
#define PCI2394_OC_ENABLE		0x01	// 计数器大于比较值中断允许

// INTUCn  计数器小于比较值中断使能
#define PCI2394_UC_DISABLE		0x00	// 计数器小于比较值中断不允许
#define PCI2394_UC_ENABLE		0x01	// 计数器小于比较值中断允许

// INTTM  定时器脉冲中断使能
#define PCI2394_TM_DISABLE		0x00	// 定时器脉冲中断不允许
#define PCI2394_TM_ENABLE		0x01	// 定时器脉冲中断允许

// INTIE  全部中断使能
#define PCI2394_IE_DISABLE		0x00	// 全部中断不允许
#define PCI2394_IE_ENABLE		0x01	// 全部中断允许


// ####################### 开关量参数结构设置 ##############################################
// 数字量输出模式设置结构体
typedef struct  _PCI2394_PARA_MODE_DO
{
	BYTE bDOManualCtrl;		// (DM)是否直接输出开关量 =TRUE: byDOSts 有效; =FALSE: 除byDOSts以外有效
	BYTE byDOSts;			// 当 bDOManualCtrl=1 有效
	BYTE bOverCompare;		// (OC)设置数字量输出通道是否置大于比较寄存器的值(0: N/A，1: 置大于)
	BYTE bUnderCompare;		// (UC)设置数字量输出通道是否置小于比较寄存器的值(0: N/A，1: 置小于)
	BYTE Level;				// (LE)设置数字量输出 0 Pulse with counter clock, 1 Level with clear interrupt
} PCI2394_PARA_MODE_DO, *PPCI2394_PARA_MODE_DO;

//***********************************************************
// 用于数字量输出PCI2394_PARA_DO结构体参数设置
// LEn  数字量输出模式控制(脉冲、中断)
#define PCI2394_LE_PULSE			0x00		// Pulse with counter clock
#define PCI2394_LE_LEVEL			0x01		// Level with clear interrupt

// DMn  数字量输出模式控制
#define PCI2394_DM_NORMAL			0x00		// Normal
#define PCI2394_DM_INDICATED		0x01		// Indicated

//***********************************************************
// 定时器设定使用 PCI2394_SetTimer
// TimerDiviBase  选择定时器时钟基源
#define PCI2394_TIMER_BASE_50KHz	0x00	// 50KHz时钟基源
#define PCI2394_TIMER_BASE_5KHz		0x01	// 5KHz时钟基源
#define PCI2394_TIMER_BASE_500Hz	0x02	// 500Hz时钟基源
#define PCI2394_TIMER_BASE_50Hz		0x03	// 50Hz时钟基源
#define PCI2394_TIMER_BASE_5Hz		0x04	// 5Hz时钟基源

//***********************************************************
// 用户函数接口
#ifndef _PCI2394_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## 常规通用函数 #################################
	// 适用于本设备的最基本操作
	DEVAPI HANDLE FAR PASCAL PCI2394_CreateDevice(int DeviceLgcID=0);		// 创建设备对象
	HANDLE DEVAPI FAR PASCAL PCI2394_CreateDeviceEx(int DevicePhysID = 0);  // 用物理号创建设备对象
	DEVAPI LONG FAR PASCAL PCI2394_GetDeviceCount(HANDLE hDevice);			// 取得设备总台数
	DEVAPI BOOL FAR PASCAL PCI2394_ListDeviceDlg(HANDLE hDevice);			// 列表系统当中的所有的该PCI设备
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID);		// 得到设备的逻辑物理ID
    DEVAPI BOOL FAR PASCAL PCI2394_ReleaseDevice(HANDLE hDevice);			// 关闭设备,禁止传输,且释放资源

	//####################### 计数器与定时器操作函数 #########################
	// 时钟源设置
	DEVAPI BOOL FAR PASCAL PCI2394_SetDeviceClock(HANDLE hDevice,  			// 设备句柄
												  LONG lSampClockSrc);		// 选择采样时钟源

	DEVAPI LONG FAR PASCAL PCI2394_GetDeviceClock(HANDLE hDevice) ; 		// 设备句柄

	//  初始化指定通道计数器
	DEVAPI BOOL FAR PASCAL PCI2394_InitDeviceCNT(							// 初始化各路计数器
												HANDLE hDevice,				// 设备句柄
												PPCI2394_PARA_CNT pCNTPara,	// 计数器控制参数
												int nCNTChannel = 0);		// 计数器通道号（0-3）
	
	// 设置和取得计数器输入模式
	DEVAPI BOOL FAR PASCAL PCI2394_SetCNTMode(  
											  HANDLE hDevice,				// 设备句柄									
											  LONG   lCNTMode, 				// 计数模式
											  int nCNTChannel = 0);			// 计数器通道号（0-3）
	
	DEVAPI LONG FAR PASCAL PCI2394_GetCNTMode(
											  HANDLE hDevice,				// 设备句柄									
											  int nCNTChannel = 0);			// 计数器通道号（0-3）
	
	// 设置和得到 锁存模式 非互斥的 
	DEVAPI BOOL FAR PASCAL PCI2394_SetLatchMode(  
											HANDLE hDevice, 				// 设备句柄	
											LONG   lLatchMode,				// 设备句柄									
											int    nCNTChannel  = 0);		// 计数器通道号（0-3）
	
	DEVAPI LONG FAR PASCAL PCI2394_GetLatchMode( 
											HANDLE hDevice,					// 设备句柄									
											int nCNTChannel = 0);			// 计数器通道号（0-3）
	
	// 计数器上溢锁定设定	
	DEVAPI BOOL FAR PASCAL PCI2394_EnableOverflowLock(
											HANDLE hDevice,					// 设备句柄
											BOOL bOverflowLock, 
											int nCNTChannel = 0);
	DEVAPI BOOL FAR PASCAL PCI2394_IsOverflowLock(
											HANDLE hDevice,					// 设备句柄
											int nCNTChannel = 0);
	// 计数器下溢锁定	
	DEVAPI BOOL FAR PASCAL PCI2394_EnableUnderflowLock(
											HANDLE hDevice,					// 设备句柄
											BOOL bUnOverflowLock, 
											int nCNTChannel = 0);
	DEVAPI BOOL FAR PASCAL PCI2394_IsUnderflowLock(
											HANDLE hDevice,					// 设备句柄
											int nCNTChannel = 0);
	// 数字滤波
	DEVAPI BOOL FAR PASCAL PCI2394_EnableDigitFilter(
											HANDLE hDevice,					// 设备句柄
											BOOL bDigitFilter, 
											int nCNTChannel = 0);
	DEVAPI BOOL FAR PASCAL PCI2394_IsDigitFilter(
											HANDLE hDevice,					// 设备句柄
											int nCNTChannel = 0);	

	// 取得指定通道计数器的值
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceCNT(					
											HANDLE hDevice,					// 设备句柄
											PULONG pCNTValue,
											int nCNTChannel = 0);			// 所有计数器的状态信息
	
	// 预置复位模式
	DEVAPI BOOL FAR PASCAL PCI2394_SetResetMode(
											HANDLE hDevice,					// 设备句柄									
											LONG   lResetMode,				// 预置复位模式
											int nCNTChannel = 0);			// 计数器通道号（0-3）
	
	DEVAPI LONG FAR PASCAL PCI2394_GetResetMode(
											HANDLE hDevice,					// 设备句柄									
											int nCNTChannel = 0);			// 计数器通道号（0-3）

	// 复位计数器
	DEVAPI BOOL FAR PASCAL PCI2394_ResetDeviceCNT(
											HANDLE hDevice,					// 设备句柄
											int nCNTChannel = 0);			//  复位计数器到预置模式(由SetResetMode预置)

	// 设置(0-3)路计数器比较值
	DEVAPI BOOL FAR PASCAL PCI2394_SetDevCompValue(
											HANDLE hDevice,					// 设备句柄
											ULONG CNTCompValue,				// 计数器比较值	
											int nCNTChannel = 0);			// 设置(0-3)路计数器比较值
	
	DEVAPI BOOL FAR PASCAL PCI2394_GetDevCompValue(
											HANDLE hDevice,					// 设备句柄
											PULONG pCNTCompValue, 
											int nCNTChannel = 0);			// 取得(0-3)路计数器比较值
	
	// 设置定时器
	DEVAPI BOOL FAR PASCAL PCI2394_SetTimer(
											HANDLE hDevice,					// 设备句柄
											LONG   lTimerDivider,			// 时钟分频数(1-255)(DV)
											LONG   lTimerDiviBase);			// 分频时钟基准源选择(TB)	
	// 20 microseconds ~ 51 second
	// 读取定时器 返回单位为 microsecond
	DEVAPI ULONG FAR PASCAL PCI2394_GetTimer(
											HANDLE hDevice,					// 设备句柄
											PLONG pTimerDivider,			// 时钟分频数(1-255)(DV)
											PLONG pTimerBaseSel);
	
	//##################### 中断实现计数器控制函数 ###################################	
	DEVAPI BOOL FAR PASCAL PCI2394_InitDeviceInt(
											HANDLE hDevice,					// 设备句柄
											HANDLE hEventInt,
											PPCI2394_PARA_INT pIntPara);    // 中断配置参数
	DEVAPI BOOL FAR PASCAL PCI2394_ReleaseDeviceInt(HANDLE hDevice);		// 释放中断资源

	DEVAPI BOOL FAR PASCAL PCI2394_ModifyDeviceInt(							// 修改中断 必修在初始化中断成功后才可以调用这个函数
											HANDLE hDevice,					// 设备句柄	
											PPCI2394_PARA_INT pIntPara);	// 中断配置参数

	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceIntSrc(
											HANDLE hDevice,					// 设备句柄
											PPCI2394_PARA_INT pIntPara);
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceIntCount(HANDLE hDevice, PULONG pIntSrc);// 得到中断次数	
	DEVAPI BOOL FAR PASCAL PCI2394_ResetDeviceIntSrc(HANDLE hDevice);		//断源

	//##################### 数字量输出状态模式控制函数 ###################################	
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceDI(
											HANDLE hDevice,					// 设备句柄
											BYTE byDISts[MAX_CHANNEL_COUNT]);// 数字量输入
	
	DEVAPI BOOL FAR PASCAL PCI2394_SetDevDOMode(
											HANDLE hDevice,					// 设备句柄
											PCI2394_PARA_MODE_DO DOMode[MAX_CHANNEL_COUNT]);
	
	DEVAPI BOOL FAR PASCAL PCI2394_GetDevDOMode(
											HANDLE hDevice,						// 设备句柄
											PCI2394_PARA_MODE_DO DOMode[MAX_CHANNEL_COUNT]);// 获得DO模式
					
	//#################### CNT硬件参数保存、读取函数(上层用户函数) ###########################
	DEVAPI BOOL FAR PASCAL PCI2394_SaveDevicePara(											// 保存PCI2394计数器所有通道参数
											HANDLE hDevice,									// 设备句柄	
											PCI2394_PARA_CNT CNTPara[MAX_CHANNEL_COUNT],	// 保存计数器参数结构体
											PCI2394_PARA_MODE_DO DOPara[MAX_CHANNEL_COUNT],	// 保存数字量输入/输出参数结构体											  
											int nChannelCount);
	
	DEVAPI BOOL FAR PASCAL PCI2394_LoadDevicePara(											// 取得PCI2394计数器所有通道参数
											HANDLE hDevice,									// 设备句柄
											PCI2394_PARA_CNT CNTPara[MAX_CHANNEL_COUNT],	// 保存计数器参数结构体
											PCI2394_PARA_MODE_DO DOPara[MAX_CHANNEL_COUNT],	// 保存数字量输入/输出参数结构体											  
											int nChannelCount);	
	// 保存中断设置
	DEVAPI BOOL FAR PASCAL PCI2394_SaveDeviceINTPara(										// 取得PCI2394计数器所有通道参数
											HANDLE hDevice,									// 设备句柄
											PPCI2394_PARA_INT pINTPara);					// 保存计数器参数结构体		
	
	// 载入中断设置
    DEVAPI BOOL FAR PASCAL PCI2394_LoadDeviceINTPara(	
											HANDLE hDevice,									// 设备句柄
											PPCI2394_PARA_INT pINTPara);					// 保存计数器参数结构体
	//################# I/O端口直接操作及读写函数 ########################
	// 适用于用户对本设备更直接、更特殊、更低层、更复杂的控制。比如根据特殊的
	// 控制对象需要特殊的控制流程和控制效率时，则用户可以使用这些接口予以实现。
	// 但这些函数主要适用于传统设备，如ISA总线、并口、串口等设备，不能用于本PCI设备
	DEVAPI BOOL FAR PASCAL PCI2394_GetDeviceAddr(					// 取得指定的指定设备ID号的映射寄存器的线性基地址，返回设备总数
												HANDLE hDevice,		// 设备对象句柄
												PUCHAR* LinearAddr,	// 返回指定映射寄存器的线性地址
											    PUCHAR* PhysAddr,	//  返回指定映射寄存器的物理地址
												int RegisterID);	// 设备映射寄存器的ID号（0-5）

    DEVAPI BOOL FAR PASCAL PCI2394_WritePortByte(HANDLE hDevice, PCHAR nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI2394_WritePortWord(HANDLE hDevice, PCHAR nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI2394_WritePortULongEx(HANDLE hDevice, PCHAR nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI2394_ReadPortByte(HANDLE hDevice, PCHAR nPort);
    DEVAPI WORD FAR PASCAL PCI2394_ReadPortWord(HANDLE hDevice, PCHAR nPort);
    DEVAPI ULONG FAR PASCAL PCI2394_ReadPortULongEx(HANDLE hDevice, PCHAR nPort);

   	//######################### 文件操作函数 ##############################
    DEVAPI HANDLE FAR PASCAL PCI2394_CreateFileObject(			// 初始文件系统
										  HANDLE hDevice,		// 设备对象
										  LPCTSTR NewFileName,	// 新文件名
										  int Mode);			// 文件操作方式    
    DEVAPI BOOL FAR PASCAL PCI2394_WriteFile(					// 保存用户空间中数据
										HANDLE hFileObject,		// 设备对象
										PVOID pDataBuffer,		// 用户数据空间地址
										ULONG nWriteSizeBytes); // 缓冲区大小(字节)

    DEVAPI BOOL FAR PASCAL PCI2394_ReadFile(					// 读数据
										  HANDLE hFileObject,	// 设备对象
										  PVOID pDataBuffer,	// 接受文件数据的用户内存缓冲区
										  ULONG OffsetBytes,	// 从文件前端开始的偏移位置
										  ULONG nReadSizeBytes); // 从偏移位置开始读的字节数

	DEVAPI BOOL FAR PASCAL PCI2394_SetFileOffset(				// 设置文件偏移指针
										  HANDLE hFileObject,   // 文件对象
										  ULONG nOffsetBytes);  // 文件偏移位置（以字为单位）  

	DEVAPI ULONG FAR PASCAL PCI2394_GetFileLength(HANDLE hFileObject); // 取得指定文件长度（字节）

    DEVAPI BOOL FAR PASCAL PCI2394_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI2394_GetDiskFreeBytes(		// 获得指定盘符的磁盘空间(注意使用64位变量)
								      LPCTSTR DiskName);		// 盘符名,如C盘为"C:\\"), D盘为"D:\\"

	//########################### 线程操作函数 ######################################
	DEVAPI HANDLE FAR PASCAL PCI2394_CreateSystemEvent(void);			// 创建内核事件对象，供InitDeviceInt和VB子线程等函数使用
	DEVAPI BOOL FAR PASCAL PCI2394_ReleaseSystemEvent(HANDLE hEvent);	// 释放内核事件对象
	
#ifdef __cplusplus
}
#endif

// 自动包含驱动函数导入库
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
