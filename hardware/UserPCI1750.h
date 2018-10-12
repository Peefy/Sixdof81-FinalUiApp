
#ifndef _PCI1750_H_
#define _PCI1750_H_

#include "UserPCICard.h"

#include "../bdaqctrl.h"

using namespace Automation::BDaq;

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
	string GetIntroduction();
	bool Init();
	bool Close();
	void WriteBit(UserPCI1750_OutputPort port, bool bit);
	void ReadBit(UserPCI1750_InputPort port, bool* bit);
	void WriteAllBits(bool* bits);
	void ReadAllBits(bool* bits);
private:
	bool disposed;
	InstantDoCtrl * instantDoCtrl;
	InstantDiCtrl * instantDiCtrl;
};

#endif
