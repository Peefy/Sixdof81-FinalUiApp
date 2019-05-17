
#ifndef _PCI1750_H_
#define _PCI1750_H_

#include "UserPCICard.h"

#include "../bdaqctrl.h"

// 包含研华命名空间
using namespace Automation::BDaq;

// PCI1750板卡数字量输出端口定义
typedef enum 
{
	UserPCI1750_IDI0,
	UserPCI1750_IDI1,
	UserPCI1750_IDI2,
	UserPCI1750_IDI3,
	UserPCI1750_IDI4,
	UserPCI1750_IDI5,
	UserPCI1750_IDI6,
	UserPCI1750_IDI7,
	UserPCI1750_IDI8,
	UserPCI1750_IDI9,
	UserPCI1750_IDI10,
	UserPCI1750_IDI11,
	UserPCI1750_IDI12,
	UserPCI1750_IDI13,
	UserPCI1750_IDI14,
	UserPCI1750_IDI15,
}UserPCI1750_InputPort;

// PCI1750板卡数字量输入端口定义
typedef enum 
{
	UserPCI1750_IDO0,
	UserPCI1750_IDO1,
	UserPCI1750_IDO2,
	UserPCI1750_IDO3,
	UserPCI1750_IDO4,
	UserPCI1750_IDO5,
	UserPCI1750_IDO6,
	UserPCI1750_IDO7,
	UserPCI1750_IDO8,
	UserPCI1750_IDO9,
	UserPCI1750_IDO10,
	UserPCI1750_IDO11,
	UserPCI1750_IDO12,
	UserPCI1750_IDO13,
	UserPCI1750_IDO14,
	UserPCI1750_IDO15,
}UserPCI1750_OutputPort;

class UserPCI1750 : public UserPCICard
{
public:
	UserPCI1750();
	~UserPCI1750();
	// 获取简介
	string GetIntroduction();
	// 初始化
	bool Init();
	// 关闭板卡
	bool Close();
	// 写端口
	void WriteBit(UserPCI1750_OutputPort port, bool bit);
	// 读端口
	void ReadBit(UserPCI1750_InputPort port, bool* bit);
	// 写所有端口
	void WriteAllBits(bool* bits);
	// 读所有端口
	void ReadAllBits(bool* bits);
private:
	bool disposed;
	InstantDoCtrl * instantDoCtrl;
	InstantDiCtrl * instantDiCtrl;
};

#endif
