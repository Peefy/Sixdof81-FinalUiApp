
#ifndef _PCI_CARD_H_
#define _PCI_CARD_H_

#include <string>

#include "../config/appconfig.h"

#define VAR_BIT_CLEAN(var, n)        (var) &= ~(1 << (n))   
#define VAR_BIT_SETONE(var, n)       (var) |=  (1 << (n))   
#define VAR_BIT_GET(var, n)          (((var) >> (n)) & 0x01)  
#define VAR_BIT_SETval(var, n, val)  ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

#define VAR_RANGE(x, min, max)		 (((x) < (min) ? (min) : ( (x) > (max) ? (max) : (x) )))

#define DI_BIT_PORT_COUNT 16
#define DO_BIT_PORT_COUNT 16

#define DI_GROUP_PORT_COUNT 2
#define DO_GROUP_PORT_COUNT 2

#define DI_GROUP_PORT_START_INDEX 0 
#define DO_GROUP_PORT_START_INDEX 0 

using namespace std;

__interface UserPCICard
{
public:
	string GetIntroduction();
	bool Init();
	bool Close();
};

#endif
