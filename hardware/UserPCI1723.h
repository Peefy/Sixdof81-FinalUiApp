
#ifndef _PCI1723_H_
#define _PCI1723_H_

#include "UserPCICard.h"

#include "../bdaqctrl.h"

#define AO_V_OUT_CHANNEL_COUNT 6
#define AO_V_OUT_GROUP_START_INDEX 0

#define AO_I_OUT_CHANNEL_COUNT 8
#define AO_I_OUT_GROUP_START_INDEX 0

#define ANALOG_OUT_DIR -1

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

using namespace Automation::BDaq;

class UserPCI1723 : public UserPCICard
{
public:
	UserPCI1723();
	~UserPCI1723();
	string GetIntroduction();
	bool Init();
	bool Close();
	void WriteAnalogVotiageData(UserPCI1723_AVO_Channel channel, double value);
	void WriteAnalogVotiageData(double* values);
	void WriteBit(UserPCI1723_DIO_Channel port, bool bit);
	void ReadBit(UserPCI1723_DIO_Channel port, bool* bit);
	void WriteAllBits(bool* bits);
	void ReadAllBits(bool* bits);
private:
	InstantAoCtrl * instantAoCtrl;
	InstantDoCtrl * instantDoCtrl;
	InstantDiCtrl * instantDiCtrl;
	bool disposed;
};



#endif
