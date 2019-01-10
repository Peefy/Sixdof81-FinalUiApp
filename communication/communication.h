
#ifndef COMMUNICATION_H_  
#define COMMUNICATION_H_  

#include <stdint.h>
#include <vector>
#include <string>

#define PI 3.1415926

//��λ����
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

#define DOWN_RANGE(x, min) ( (x)<(min) ? (min) : (x) )

#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   
#define BIT_SET(var,n)          (var) |=  (1<<(n))   
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  
#define BIT_SETval(var,n,val)   ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

#define SIN_INFO_T_DELTA 0.2

typedef struct 
{
	//��λ0.1mm
    int16_t X;
	//��λ0.1mm
    int16_t Y;
	//��λ0.1mm
    int16_t Z;
	//��λ0.01��
    int16_t Yaw;
	//��λ0.01��
    int16_t Roll;
	//��λ0.01��
    int16_t Pitch;
}DataPackage;

void ResetDefaultData(DataPackage * data);
void PrintDataPackageToString(DataPackage data);

#endif

