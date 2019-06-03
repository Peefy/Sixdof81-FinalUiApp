
#ifndef _PLATFORM_API_H_
#define _PLATFORM_API_H_

#include <stdint.h>
#include "../communication/SerialPort.h"

// 串口API控制端口号
#define API_PORT_NUMBER          6
// 串口API控制波特率
#define API_PORT_BAUDRATE        115200
// 串口API数据帧包头1
#define API_DATA_HEAD_ONE        0xAA
// 串口API数据帧包头2
#define API_DATA_HEAD_TWO        0xBB
// 串口API数据帧包尾1
#define API_DATA_TAIL_ONE        0xCC
// 串口API数据帧包尾2
#define API_DATA_TAIL_TWO        0xDD
// 串口API数据帧包长
#define API_DATA_PACKAGE_LEGNTH  80

// 串口API数据缩放系数 整形数*0.0001=浮点数
#define API_ANGLE_SCALE          0.001

// 平台控制指令
enum class ApiControlCommandInt32
{
	API_CTL_CMD_NONE             =  0,   //串口API控制指令：空
	API_CTL_CMD_RISE_INT32       =  11,  //串口API控制指令：上升
	API_CTL_CMD_DOWN_INT32       =  22,  //串口API控制指令：下降
	API_CTL_CMD_CONNECT_INT32    =  33,  //串口API控制指令：连接
	API_CTL_CMD_DISCONNECT_INT32 =  44,  //串口API控制指令：断开
	API_CTL_CMD_PAUSE_INT32      =  55,  //串口API控制指令：暂停
	API_CTL_CMD_RECOVER_INT32    =  66,  //串口API控制指令：暂停恢复
	API_CTL_CMD_POWER_ON_INT32   =  77,  //串口API控制指令：电源开
	API_CTL_CMD_POWER_OFF_INT32  =  88,  //串口API控制指令：电源关
	API_CTL_CMD_CHECK_ON_INT32   =  99,  //串口API控制指令：检修开
	API_CTL_CMD_CHECK_OFF_INT32  =  100  //串口API控制指令：检修关
};

#pragma pack (1)
typedef struct
{
	uint8_t HeadOne;            //1.      包头 0xAA
	uint8_t HeadTwo;            //2.      包头 0xBB
	int32_t X;                  //3-6.    X线位移 0.001
	int32_t Y;                  //7-10.   Y线位移 0.001
	int32_t Z;                  //11-14.  Z线位移 0.001
	int32_t Roll;               //15-18.  横滚角 0.001
	int32_t Pitch;              //19-22.  俯仰角 0.001
	int32_t Yaw;                //23-16.  偏航角 0.001
	uint32_t ReservedData1[6];  //27-50.  6个保留位 0.001  
	uint32_t ReservedData2[6];  //51-74.  6个保留位 0.001  
	uint8_t NoneByte;           //75      空字节
	uint8_t ControlCommand;     //76.     平台控制指令 111上升 222下降 333运行 444断开
	uint8_t StateByte;          //77.     状态字
	uint8_t CheckByte;          //78.     其前所有的字节的按位或
	uint8_t TailOne;            //79.     包尾 0xCC
	uint8_t TailTwo;            //80.     包尾 0xDD
} ApiDataPackage;
#pragma pack () 

class ApiControl
{
public:
	ApiControl();
	~ApiControl();
	// 打开串口
	bool Open();
	// 关闭串口
	bool Close();
	// 接收数据
	void GatherData();
	// 串口是否打开
	bool IsStart;
	// 串口是否收到数据帧
	bool IsRecievedData;
	// 串口收到的数据
	ApiDataPackage Data;
	// 平台控制指令
	ApiControlCommandInt32 ControlCommand;
private:
	// 串口类
	CSerialPort serialPort;
	bool JudgeCheckByte(UCHAR* pData, UCHAR check, int startindex, int length);
protected:
};

#endif
