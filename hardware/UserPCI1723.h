
#ifndef _PCI1723_H_
#define _PCI1723_H_

#include "UserPCICard.h"

#include "../bdaqctrl.h"

// 电压模拟量输出通道数
#define AO_V_OUT_CHANNEL_COUNT 6
// 电压模拟量输出端口组索引
#define AO_V_OUT_GROUP_START_INDEX 0

// 电流模拟量输出通道数
#define AO_I_OUT_CHANNEL_COUNT 8
// 电流模拟量输出端口组索引
#define AO_I_OUT_GROUP_START_INDEX 0

// 模拟量输出正负，取1或者-1
#define ANALOG_OUT_DIR -1

// PCI1723板卡电压模拟量输出端口定义
typedef enum 
{
	UserPCI1723_AVO_Channel0,
	UserPCI1723_AVO_Channel1,
	UserPCI1723_AVO_Channel2,
	UserPCI1723_AVO_Channel3,
	UserPCI1723_AVO_Channel4,
	UserPCI1723_AVO_Channel5,
	UserPCI1723_AVO_Channel6,
	UserPCI1723_AVO_Channel7,
}UserPCI1723_AVO_Channel;

// PCI1723板卡电流模拟量输出端口定义
typedef enum 
{
	UserPCI1723_AIO_Channel0,
	UserPCI1723_AIO_Channel1,
	UserPCI1723_AIO_Channel2,
	UserPCI1723_AIO_Channel3,
	UserPCI1723_AIO_Channel4,
	UserPCI1723_AIO_Channel5,
	UserPCI1723_AIO_Channel6,
	UserPCI1723_AIO_Channel7,
}UserPCI1723_AIO_Channel;

// PCI1723板卡数字端口输入输出定义
typedef enum 
{
	UserPCI1723_DIO_Channel0,
	UserPCI1723_DIO_Channel1,
	UserPCI1723_DIO_Channel2,
	UserPCI1723_DIO_Channel3,
	UserPCI1723_DIO_Channel4,
	UserPCI1723_DIO_Channel5,
	UserPCI1723_DIO_Channel6,
	UserPCI1723_DIO_Channel7,
	UserPCI1723_DIO_Channel8,
	UserPCI1723_DIO_Channel9,
	UserPCI1723_DIO_Channel10,
	UserPCI1723_DIO_Channel11,
	UserPCI1723_DIO_Channel12,
	UserPCI1723_DIO_Channel13,
	UserPCI1723_DIO_Channel14,
	UserPCI1723_DIO_Channel15,
}UserPCI1723_DIO_Channel;

// 包含研华命名空间
using namespace Automation::BDaq;

class UserPCI1723 : public UserPCICard
{
public:
	UserPCI1723();
	~UserPCI1723();
	// 获取简介
	string GetIntroduction();
	// 初始化
	bool Init();
	// 关闭板卡
	bool Close();
	// 向通道写入电压
	void WriteAnalogVotiageData(UserPCI1723_AVO_Channel channel, double value);
	// 向所有通道写入电压
	void WriteAnalogVotiageData(double* values);
	// 读数字端口
	void WriteBit(UserPCI1723_DIO_Channel port, bool bit);
	// 写数字端口
	void ReadBit(UserPCI1723_DIO_Channel port, bool* bit);
	// 读所有数字端口
	void WriteAllBits(bool* bits);
	// 写所有数字端口
	void ReadAllBits(bool* bits);
private:
	InstantAoCtrl * instantAoCtrl;
	InstantDoCtrl * instantDoCtrl;
	InstantDiCtrl * instantDiCtrl;
	bool disposed;
};



#endif
