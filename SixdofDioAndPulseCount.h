
#ifndef _SIXDOF_DIO_AND_PULSE_COUNT_H_
#define _SIXDOF_DIO_AND_PULSE_COUNT_H_

#include <memory>

#include "UserPCI1723.h"
#include "UserPCI1750.h"
#include "UserPCI2394.h"

using namespace std;

#define SIXDOF_PCI2394_NUM 2

#define SXIDOF_MOTION_NUM 6

class SixdofDioAndCount
{
public:
	SixdofDioAndCount();
	~SixdofDioAndCount();
	bool Init();
	bool Close();
	long * ReadPulseCount();
private:
	void DataInit();
	long pulseCounts[SXIDOF_MOTION_NUM];
	unique_ptr<UserPCI2394> pci2394Cards[SIXDOF_PCI2394_NUM];
	unique_ptr<UserPCI1723> pci1723Card;
	unique_ptr<UserPCI1750> pci1750Card;
};

using namespace std;